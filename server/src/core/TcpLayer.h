// LCEServer — TCP networking layer
// Extracted from WinsockNetLayer: accept loop, per-connection recv, length-prefixed framing
#pragma once

#include "Types.h"
#include "Protocol.h"
#include "Logger.h"
#include <functional>

namespace LCEServer
{
    // Raw data callback: (smallId, data, size)
    using DataReceivedCallback = std::function<void(uint8_t, const uint8_t*, int)>;

    // Disconnect callback: (smallId)
    using DisconnectCallback = std::function<void(uint8_t)>;

    struct TcpConnection
    {
        SOCKET      socket      = INVALID_SOCKET;
        uint8_t     smallId     = 0;
        HANDLE      recvThread  = NULL;
        std::string remoteIp;
        volatile bool active    = false;
    };

    class TcpLayer
    {
    public:
        TcpLayer();
        ~TcpLayer();

        bool Initialize();
        void Shutdown();

        // Start hosting on the given port/bind address
        bool Host(int port, const char* bindIp = nullptr);

        // Send length-prefixed data to a specific smallId
        bool SendToSmallId(uint8_t smallId, const void* data, int dataSize);

        // Send raw bytes on a specific socket (with length prefix)
        static bool SendOnSocket(SOCKET sock, const void* data, int dataSize);

        // Send a reject handshake (0xFF + disconnect packet)
        static void SendReject(SOCKET sock, DisconnectReason reason);

        // Close a connection by smallId
        void CloseConnection(uint8_t smallId);

        // Recycle a smallId for reuse
        void PushFreeSmallId(uint8_t smallId);

        // Get the socket for a smallId
        SOCKET GetSocketForSmallId(uint8_t smallId);

        // Get the remote IP for a smallId
        std::string GetRemoteIp(uint8_t smallId);

        // Callbacks
        void SetDataCallback(DataReceivedCallback cb) { m_dataCallback = cb; }
        void SetDisconnectCallback(DisconnectCallback cb) { m_disconnectCallback = cb; }

        // Ban check callback: return true if IP should be rejected
        using IpBanCheck = std::function<bool(const std::string&)>;
        void SetIpBanCheck(IpBanCheck cb) { m_ipBanCheck = cb; }

        // Max connections check
        using CanAcceptCheck = std::function<bool()>;
        void SetCanAcceptCheck(CanAcceptCheck cb) { m_canAcceptCheck = cb; }

        bool IsActive() const { return m_active; }

    private:
        static DWORD WINAPI AcceptThreadProc(LPVOID param);
        static DWORD WINAPI RecvThreadProc(LPVOID param);

        SOCKET              m_listenSocket = INVALID_SOCKET;
        HANDLE              m_acceptThread = NULL;
        std::atomic<bool>   m_active{false};
        bool                m_initialized = false;
        unsigned int        m_nextSmallId = 1;

        CRITICAL_SECTION    m_connectionsLock;
        std::vector<TcpConnection> m_connections;

        CRITICAL_SECTION    m_freeSmallIdLock;
        std::vector<uint8_t> m_freeSmallIds;

        CRITICAL_SECTION    m_smallIdToSocketLock;
        SOCKET              m_smallIdToSocket[256];

        CRITICAL_SECTION    m_sendLock;

        CRITICAL_SECTION    m_disconnectLock;
        std::vector<uint8_t> m_disconnectedSmallIds;

        // Remote IP cache per smallId
        CRITICAL_SECTION    m_ipCacheLock;
        std::string         m_ipCache[256];

        DataReceivedCallback m_dataCallback;
        DisconnectCallback   m_disconnectCallback;
        IpBanCheck           m_ipBanCheck;
        CanAcceptCheck       m_canAcceptCheck;
    };
}
