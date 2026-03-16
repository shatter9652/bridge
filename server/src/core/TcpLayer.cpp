// LCEServer — TCP layer implementation
// Closely follows WinsockNetLayer from the LCE source
#include "TcpLayer.h"

namespace LCEServer
{
    // Helper: receive exactly len bytes
    static bool RecvExact(SOCKET sock, uint8_t* buf, int len)
    {
        int total = 0;
        while (total < len)
        {
            int r = recv(sock, (char*)buf + total, len - total, 0);
            if (r <= 0) return false;
            total += r;
        }
        return true;
    }

    TcpLayer::TcpLayer() {}

    TcpLayer::~TcpLayer()
    {
        Shutdown();
    }

    bool TcpLayer::Initialize()
    {
        if (m_initialized) return true;

        WSADATA wsaData;
        int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (result != 0)
        {
            Logger::Error("TCP", "WSAStartup failed: %d", result);
            return false;
        }

        InitializeCriticalSection(&m_connectionsLock);
        InitializeCriticalSection(&m_freeSmallIdLock);
        InitializeCriticalSection(&m_smallIdToSocketLock);
        InitializeCriticalSection(&m_sendLock);
        InitializeCriticalSection(&m_disconnectLock);
        InitializeCriticalSection(&m_ipCacheLock);

        for (int i = 0; i < 256; i++)
            m_smallIdToSocket[i] = INVALID_SOCKET;

        m_initialized = true;
        return true;
    }

    void TcpLayer::Shutdown()
    {
        m_active = false;

        if (m_listenSocket != INVALID_SOCKET)
        {
            closesocket(m_listenSocket);
            m_listenSocket = INVALID_SOCKET;
        }

        if (m_acceptThread != NULL)
        {
            WaitForSingleObject(m_acceptThread, 3000);
            CloseHandle(m_acceptThread);
            m_acceptThread = NULL;
        }

        // Close all connections and wait for recv threads
        std::vector<HANDLE> recvThreads;
        EnterCriticalSection(&m_connectionsLock);
        for (auto& c : m_connections)
        {
            c.active = false;
            if (c.socket != INVALID_SOCKET)
            {
                closesocket(c.socket);
                c.socket = INVALID_SOCKET;
            }
            if (c.recvThread != NULL)
            {
                recvThreads.push_back(c.recvThread);
                c.recvThread = NULL;
            }
        }
        m_connections.clear();
        LeaveCriticalSection(&m_connectionsLock);

        for (auto h : recvThreads)
        {
            WaitForSingleObject(h, 2000);
            CloseHandle(h);
        }

        if (m_initialized)
        {
            DeleteCriticalSection(&m_connectionsLock);
            DeleteCriticalSection(&m_freeSmallIdLock);
            DeleteCriticalSection(&m_smallIdToSocketLock);
            DeleteCriticalSection(&m_sendLock);
            DeleteCriticalSection(&m_disconnectLock);
            DeleteCriticalSection(&m_ipCacheLock);
            WSACleanup();
            m_initialized = false;
        }
    }

    bool TcpLayer::Host(int port, const char* bindIp)
    {
        if (!m_initialized && !Initialize()) return false;

        // Reserve smallIds 0-3 for host local pads. The real dedicated
        // server uses the game's IQNet player array where 0-3 are local
        // pad slots. External clients must start at 4+ to avoid the
        // client's GameNetworkManager treating them as local splitscreen.
        m_nextSmallId = 4;

        EnterCriticalSection(&m_freeSmallIdLock);
        m_freeSmallIds.clear();
        LeaveCriticalSection(&m_freeSmallIdLock);

        EnterCriticalSection(&m_smallIdToSocketLock);
        for (int i = 0; i < 256; i++)
            m_smallIdToSocket[i] = INVALID_SOCKET;
        LeaveCriticalSection(&m_smallIdToSocketLock);

        struct addrinfo hints = {};
        struct addrinfo* result = NULL;
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = (bindIp == nullptr || bindIp[0] == 0)
                         ? AI_PASSIVE : 0;

        char portStr[16];
        sprintf_s(portStr, "%d", port);
        const char* resolvedIp = (bindIp && bindIp[0]) ? bindIp : NULL;

        int iResult = getaddrinfo(resolvedIp, portStr, &hints, &result);
        if (iResult != 0)
        {
            Logger::Error("TCP", "getaddrinfo failed for %s:%d - %d",
                resolvedIp ? resolvedIp : "*", port, iResult);
            return false;
        }

        m_listenSocket = socket(result->ai_family,
                                result->ai_socktype,
                                result->ai_protocol);
        if (m_listenSocket == INVALID_SOCKET)
        {
            Logger::Error("TCP", "socket() failed: %d", WSAGetLastError());
            freeaddrinfo(result);
            return false;
        }

        int opt = 1;
        setsockopt(m_listenSocket, SOL_SOCKET, SO_REUSEADDR,
                   (const char*)&opt, sizeof(opt));

        iResult = ::bind(m_listenSocket, result->ai_addr,
                         (int)result->ai_addrlen);
        freeaddrinfo(result);

        if (iResult == SOCKET_ERROR)
        {
            Logger::Error("TCP", "bind() failed: %d", WSAGetLastError());
            closesocket(m_listenSocket);
            m_listenSocket = INVALID_SOCKET;
            return false;
        }

        iResult = listen(m_listenSocket, SOMAXCONN);
        if (iResult == SOCKET_ERROR)
        {
            Logger::Error("TCP", "listen() failed: %d", WSAGetLastError());
            closesocket(m_listenSocket);
            m_listenSocket = INVALID_SOCKET;
            return false;
        }

        m_active = true;
        m_acceptThread = CreateThread(NULL, 0, AcceptThreadProc,
                                      this, 0, NULL);

        Logger::Info("TCP", "Listening on %s:%d",
            resolvedIp ? resolvedIp : "*", port);
        return true;
    }

    bool TcpLayer::SendOnSocket(SOCKET sock, const void* data, int dataSize)
    {
        if (sock == INVALID_SOCKET || dataSize <= 0) return false;

        // 4-byte big-endian length header (matches WinsockNetLayer) (matches WinsockNetLayer)
        uint8_t header[4];
        header[0] = (uint8_t)((dataSize >> 24) & 0xFF);
        header[1] = (uint8_t)((dataSize >> 16) & 0xFF);
        header[2] = (uint8_t)((dataSize >> 8) & 0xFF);
        header[3] = (uint8_t)(dataSize & 0xFF);

        int totalSent = 0;
        while (totalSent < 4)
        {
            int s = send(sock, (const char*)header + totalSent,
                         4 - totalSent, 0);
            if (s == SOCKET_ERROR || s == 0) return false;
            totalSent += s;
        }

        totalSent = 0;
        while (totalSent < dataSize)
        {
            int s = send(sock, (const char*)data + totalSent,
                         dataSize - totalSent, 0);
            if (s == SOCKET_ERROR || s == 0) return false;
            totalSent += s;
        }
        return true;
    }

    bool TcpLayer::SendToSmallId(uint8_t smallId,
                                  const void* data, int dataSize)
    {
        if (!m_active) return false;
        SOCKET sock = GetSocketForSmallId(smallId);
        if (sock == INVALID_SOCKET) return false;

        EnterCriticalSection(&m_sendLock);
        bool ok = SendOnSocket(sock, data, dataSize);
        LeaveCriticalSection(&m_sendLock);
        return ok;
    }

    void TcpLayer::SendReject(SOCKET sock, DisconnectReason reason)
    {
        // Matches WinsockNetLayer: 0xFF sentinel + packet id 255 +
        // 4-byte big-endian reason
        uint8_t buf[6];
        buf[0] = SMALLID_REJECT;
        buf[1] = 255; // DisconnectPacket id
        int r = (int)reason;
        buf[2] = (uint8_t)((r >> 24) & 0xFF);
        buf[3] = (uint8_t)((r >> 16) & 0xFF);
        buf[4] = (uint8_t)((r >> 8) & 0xFF);
        buf[5] = (uint8_t)(r & 0xFF);
        send(sock, (const char*)buf, sizeof(buf), 0);
    }

    SOCKET TcpLayer::GetSocketForSmallId(uint8_t smallId)
    {
        EnterCriticalSection(&m_smallIdToSocketLock);
        SOCKET s = m_smallIdToSocket[smallId];
        LeaveCriticalSection(&m_smallIdToSocketLock);
        return s;
    }

    std::string TcpLayer::GetRemoteIp(uint8_t smallId)
    {
        EnterCriticalSection(&m_ipCacheLock);
        std::string ip = m_ipCache[smallId];
        LeaveCriticalSection(&m_ipCacheLock);
        return ip;
    }

    void TcpLayer::CloseConnection(uint8_t smallId)
    {
        EnterCriticalSection(&m_connectionsLock);
        for (auto& c : m_connections)
        {
            if (c.smallId == smallId && c.active &&
                c.socket != INVALID_SOCKET)
            {
                closesocket(c.socket);
                c.socket = INVALID_SOCKET;
                break;
            }
        }
        LeaveCriticalSection(&m_connectionsLock);
    }

    void TcpLayer::PushFreeSmallId(uint8_t smallId)
    {
        EnterCriticalSection(&m_freeSmallIdLock);
        m_freeSmallIds.push_back(smallId);
        LeaveCriticalSection(&m_freeSmallIdLock);

        // Clear the socket mapping
        EnterCriticalSection(&m_smallIdToSocketLock);
        m_smallIdToSocket[smallId] = INVALID_SOCKET;
        LeaveCriticalSection(&m_smallIdToSocketLock);

        // Clear IP cache
        EnterCriticalSection(&m_ipCacheLock);
        m_ipCache[smallId].clear();
        LeaveCriticalSection(&m_ipCacheLock);
    }

    // Accept loop — mirrors WinsockNetLayer::AcceptThreadProc
    DWORD WINAPI TcpLayer::AcceptThreadProc(LPVOID param)
    {
        TcpLayer* self = (TcpLayer*)param;

        while (self->m_active)
        {
            sockaddr_in remoteAddr;
            ZeroMemory(&remoteAddr, sizeof(remoteAddr));
            int addrLen = sizeof(remoteAddr);
            SOCKET clientSock = accept(self->m_listenSocket,
                (sockaddr*)&remoteAddr, &addrLen);

            if (clientSock == INVALID_SOCKET)
            {
                if (self->m_active)
                    Logger::Error("TCP", "accept() failed: %d",
                                  WSAGetLastError());
                break;
            }

            int noDelay = 1;
            setsockopt(clientSock, IPPROTO_TCP, TCP_NODELAY,
                       (const char*)&noDelay, sizeof(noDelay));

            // Resolve remote IP
            char ipBuf[64] = {};
            inet_ntop(AF_INET, &remoteAddr.sin_addr, ipBuf, sizeof(ipBuf));
            std::string remoteIp = ipBuf;

            Logger::Debug("TCP", "Incoming connection from %s", ipBuf);

            // IP ban check
            if (self->m_ipBanCheck && self->m_ipBanCheck(remoteIp))
            {
                Logger::Info("TCP", "Rejected %s: IP banned", ipBuf);
                SendReject(clientSock, DisconnectReason::Banned);
                closesocket(clientSock);
                continue;
            }

            // Server full check
            if (self->m_canAcceptCheck && !self->m_canAcceptCheck())
            {
                Logger::Info("TCP", "Rejected %s: server full", ipBuf);
                SendReject(clientSock, DisconnectReason::ServerFull);
                closesocket(clientSock);
                continue;
            }

            // Allocate a smallId
            uint8_t assignedId;
            EnterCriticalSection(&self->m_freeSmallIdLock);
            if (!self->m_freeSmallIds.empty())
            {
                assignedId = self->m_freeSmallIds.back();
                self->m_freeSmallIds.pop_back();
            }
            else if (self->m_nextSmallId < (unsigned)MAX_PLAYERS_HARD)
            {
                assignedId = (uint8_t)self->m_nextSmallId++;
            }
            else
            {
                LeaveCriticalSection(&self->m_freeSmallIdLock);
                Logger::Info("TCP", "Rejected %s: no smallIds", ipBuf);
                SendReject(clientSock, DisconnectReason::ServerFull);
                closesocket(clientSock);
                continue;
            }
            LeaveCriticalSection(&self->m_freeSmallIdLock);

            // Send the assigned smallId (1 byte) — client expects this
            uint8_t assignBuf[1] = { assignedId };
            int sent = send(clientSock, (const char*)assignBuf, 1, 0);
            if (sent != 1)
            {
                Logger::Warn("TCP", "Failed to send smallId to %s", ipBuf);
                closesocket(clientSock);
                continue;
            }

            // Register connection
            TcpConnection conn;
            conn.socket = clientSock;
            conn.smallId = assignedId;
            conn.remoteIp = remoteIp;
            conn.active = true;
            conn.recvThread = NULL;

            EnterCriticalSection(&self->m_connectionsLock);
            self->m_connections.push_back(conn);
            int connIdx = (int)self->m_connections.size() - 1;
            LeaveCriticalSection(&self->m_connectionsLock);

            // Register in lookup tables
            EnterCriticalSection(&self->m_smallIdToSocketLock);
            self->m_smallIdToSocket[assignedId] = clientSock;
            LeaveCriticalSection(&self->m_smallIdToSocketLock);

            EnterCriticalSection(&self->m_ipCacheLock);
            self->m_ipCache[assignedId] = remoteIp;
            LeaveCriticalSection(&self->m_ipCacheLock);

            Logger::Info("TCP", "Accepted %s -> smallId=%d",
                         ipBuf, assignedId);

            // Spawn recv thread — pass connIdx + self pointer
            struct RecvParam { TcpLayer* self; int idx; };
            RecvParam* rp = new RecvParam{ self, connIdx };
            HANDLE hThread = CreateThread(NULL, 0, RecvThreadProc,
                                          rp, 0, NULL);

            EnterCriticalSection(&self->m_connectionsLock);
            if (connIdx < (int)self->m_connections.size())
                self->m_connections[connIdx].recvThread = hThread;
            LeaveCriticalSection(&self->m_connectionsLock);
        }
        return 0;
    }

    // Per-connection receive loop — mirrors WinsockNetLayer::RecvThreadProc
    DWORD WINAPI TcpLayer::RecvThreadProc(LPVOID param)
    {
        struct RecvParam { TcpLayer* self; int idx; };
        RecvParam rp = *(RecvParam*)param;
        delete (RecvParam*)param;

        TcpLayer* self = rp.self;

        EnterCriticalSection(&self->m_connectionsLock);
        if (rp.idx >= (int)self->m_connections.size())
        {
            LeaveCriticalSection(&self->m_connectionsLock);
            return 0;
        }
        SOCKET sock = self->m_connections[rp.idx].socket;
        uint8_t clientSmallId = self->m_connections[rp.idx].smallId;
        LeaveCriticalSection(&self->m_connectionsLock);

        std::vector<uint8_t> recvBuf(RECV_BUFFER_SIZE);

        while (self->m_active)
        {
            // Read 4-byte big-endian length header
            uint8_t header[4];
            if (!RecvExact(sock, header, 4))
            {
                Logger::Debug("TCP", "Client smallId=%d disconnected (header)",
                              clientSmallId);
                break;
            }

            int packetSize = ((uint32_t)header[0] << 24) |
                             ((uint32_t)header[1] << 16) |
                             ((uint32_t)header[2] << 8) |
                             ((uint32_t)header[3]);

            if (packetSize <= 0 || packetSize > MAX_PACKET_SIZE)
            {
                Logger::Warn("TCP", "Invalid packet size %d from smallId=%d",
                             packetSize, clientSmallId);
                break;
            }

            if ((int)recvBuf.size() < packetSize)
                recvBuf.resize(packetSize);

            if (!RecvExact(sock, &recvBuf[0], packetSize))
            {
                Logger::Debug("TCP", "Client smallId=%d disconnected (body)",
                              clientSmallId);
                break;
            }

            // Deliver to callback
            if (self->m_dataCallback)
                self->m_dataCallback(clientSmallId, &recvBuf[0], packetSize);
        }

        // Mark disconnected
        EnterCriticalSection(&self->m_connectionsLock);
        for (auto& c : self->m_connections)
        {
            if (c.smallId == clientSmallId)
            {
                c.active = false;
                if (c.socket != INVALID_SOCKET)
                {
                    closesocket(c.socket);
                    c.socket = INVALID_SOCKET;
                }
                break;
            }
        }
        LeaveCriticalSection(&self->m_connectionsLock);

        // Notify disconnect
        if (self->m_disconnectCallback)
            self->m_disconnectCallback(clientSmallId);

        return 0;
    }

} // namespace LCEServer
