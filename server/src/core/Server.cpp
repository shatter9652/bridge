// LCEServer — Server implementation
#include "Server.h"

namespace LCEServer
{
    Server::Server() {}
    Server::~Server() { RequestShutdown(); }

    bool Server::Start()
    {
        Logger::Info("Server", "Loading server.properties...");
        m_config = ServerConfig::Load();
        Logger::SetLevel(m_config.logLevel);

        Logger::Info("Server", "Starting LCEServer on %s:%d",
            m_config.serverIp.c_str(), m_config.serverPort);
        Logger::Info("Server", "Max players: %d",
            m_config.maxPlayers);
        Logger::Info("Server", "MOTD: %s",
            m_config.motd.c_str());

        // Load access control files
        Logger::Info("Server", "Loading access control...");
        m_banList.Load();
        m_whitelist.Load();
        m_opsList.Load();
        if (m_config.whiteList)
            Logger::Info("Server", "Whitelist is ENABLED");

        // Initialise TCP layer
        m_tcp = std::make_unique<TcpLayer>();
        if (!m_tcp->Initialize())
        {
            Logger::Error("Server",
                "Failed to initialise TCP layer");
            return false;
        }

        // Wire IP ban check into TcpLayer
        m_tcp->SetIpBanCheck(
            [this](const std::string& ip) {
                return m_banList.IsIpBanned(ip);
            });

        // Start listening
        const char* bindIp = m_config.serverIp.empty()
            ? nullptr : m_config.serverIp.c_str();
        if (!m_tcp->Host(m_config.serverPort, bindIp))
        {
            Logger::Error("Server",
                "Failed to bind on port %d",
                m_config.serverPort);
            return false;
        }

        // Create connection manager and wire callbacks
        m_connMgr = std::make_unique<ConnectionManager>(
            m_tcp.get(), &m_config);
        m_connMgr->SetBanList(&m_banList);
        m_connMgr->SetWhitelist(&m_whitelist);
        m_connMgr->SetOpsList(&m_opsList);
        m_connMgr->Start();

        // Initialise world
        m_world = std::make_unique<World>();
        if (!m_world->Initialize(m_config))
        {
            Logger::Error("Server",
                "Failed to initialise world");
            return false;
        }

        // Pass world to connection manager
        m_connMgr->SetWorld(m_world.get());

        // Autosave manager
        if (!m_config.disableSaving)
        {
            m_saveMgr = std::make_unique<SaveManager>(
                m_world.get(), m_config.autosaveInterval);
            Logger::Info("Server", "Autosave every %d seconds",
                         m_config.autosaveInterval);
        }

        m_running = true;

        // Start console input
        m_console = std::make_unique<Console>(this);
        m_console->Start();

        Logger::Info("Server",
            "Server is ready! Listening for connections.");
        return true;
    }

    void Server::Run()
    {
        using clock = std::chrono::steady_clock;
        constexpr auto TICK_DURATION =
            std::chrono::milliseconds(50);
        auto nextTick = clock::now();

        while (m_running)
        {
            auto now = clock::now();
            if (now >= nextTick)
            {
                Tick();
                nextTick += TICK_DURATION;
                if (clock::now() > nextTick)
                    nextTick = clock::now() + TICK_DURATION;
            }
            else
            {
                std::this_thread::sleep_until(nextTick);
            }
        }

        // Shutdown sequence
        Logger::Info("Server", "Shutting down...");

        // Persist world state before network/console teardown. If shutdown
        // gets interrupted later, player edits are still on disk.
        if (m_world && !m_config.disableSaving) {
            Logger::Info("Server", "Saving world...");
            m_world->SaveAll();
            Logger::Info("Server", "World save complete.");
        }

        if (m_console) {
            m_console->Stop();
            m_console.reset();
        }
        if (m_connMgr) {
            m_connMgr->Shutdown();
            m_connMgr.reset();
        }
        if (m_tcp) {
            m_tcp->Shutdown();
            m_tcp.reset();
        }
        m_saveMgr.reset();
        m_world.reset();

        Logger::Info("Server", "Server stopped.");
    }

    void Server::RequestShutdown()
    {
        m_running = false;
    }

    void Server::Tick()
    {
        m_tickCount++;
        if (m_console) m_console->Tick();
        if (m_connMgr) m_connMgr->Tick();
        if (m_world)   m_world->TickTime();
        if (m_saveMgr) m_saveMgr->Tick();
    }

} // namespace LCEServer
