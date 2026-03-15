// LCEServer — Main server class
#pragma once

#include "Types.h"
#include "ServerConfig.h"
#include "TcpLayer.h"
#include "ConnectionManager.h"
#include "../world/World.h"
#include "../world/SaveManager.h"
#include "../console/Console.h"
#include "../access/BanList.h"
#include "../access/Whitelist.h"
#include "../access/OpsList.h"

namespace LCEServer
{
    class Server
    {
    public:
        Server();
        ~Server();

        bool Start();
        void Run();
        void RequestShutdown();

        bool IsRunning() const { return m_running; }
        World* GetWorld() { return m_world.get(); }
        ConnectionManager* GetConnectionManager()
            { return m_connMgr.get(); }
        SaveManager* GetSaveManager()
            { return m_saveMgr.get(); }
        ServerConfig& GetConfig() { return m_config; }
        const ServerConfig& GetConfig() const
            { return m_config; }
        BanList* GetBanList() { return &m_banList; }
        Whitelist* GetWhitelist() { return &m_whitelist; }
        OpsList* GetOpsList() { return &m_opsList; }
        TcpLayer* GetTcpLayer() { return m_tcp.get(); }

    private:
        void Tick();

        ServerConfig                        m_config;
        std::unique_ptr<TcpLayer>           m_tcp;
        std::unique_ptr<ConnectionManager>  m_connMgr;
        std::unique_ptr<World>              m_world;
        std::unique_ptr<SaveManager>        m_saveMgr;
        std::unique_ptr<Console>            m_console;
        BanList                             m_banList;
        Whitelist                           m_whitelist;
        OpsList                             m_opsList;
        std::atomic<bool>                   m_running{false};
        uint64_t                            m_tickCount = 0;
    };
}
