// LCEServer — Console implementation (Milestone 4)
// Full ServerCliEngine with tokenised command dispatch
#include "Console.h"
#include "../core/Server.h"
#include "../core/Logger.h"
#include "../core/ConnectionManager.h"
#include "../core/Connection.h"
#include "../core/PacketHandler.h"
#include "../world/World.h"
#include "../world/SaveManager.h"
#include "../access/BanList.h"
#include "../access/Whitelist.h"
#include "../access/OpsList.h"

namespace LCEServer
{
    Console::Console(Server* server)
        : m_server(server) {}

    Console::~Console() { Stop(); }

    void Console::Start()
    {
        m_running = true;
        m_inputThread = CreateThread(NULL, 0,
            InputThreadProc, this, 0, NULL);
        Logger::Info("Console",
            "Console input ready. Type 'help' for commands.");
    }

    void Console::Stop()
    {
        m_running = false;
        if (m_inputThread != NULL)
        {
            WaitForSingleObject(m_inputThread, 500);
            CloseHandle(m_inputThread);
            m_inputThread = NULL;
        }
    }

    void Console::EnqueueCommand(const std::string& line)
    {
        std::lock_guard<std::mutex> lock(m_queueMutex);
        m_commandQueue.push_back(line);
    }

    void Console::Tick()
    {
        std::vector<std::string> commands;
        {
            std::lock_guard<std::mutex> lock(m_queueMutex);
            commands.swap(m_commandQueue);
        }
        for (auto& cmd : commands)
            ProcessCommand(cmd);
    }

    DWORD WINAPI Console::InputThreadProc(LPVOID param)
    {
        Console* self = (Console*)param;
        char buf[1024];
        while (self->m_running)
        {
            std::printf("> ");
            std::fflush(stdout);
            if (!std::fgets(buf, sizeof(buf), stdin))
                break;
            std::string line(buf);
            while (!line.empty() &&
                   (line.back()=='\n'||line.back()=='\r'))
                line.pop_back();
            if (line.empty()) continue;
            self->EnqueueCommand(line);
        }
        return 0;
    }

    // --- Utilities ---

    std::vector<std::string> Console::Tokenise(
        const std::string& line)
    {
        std::vector<std::string> tokens;
        std::istringstream iss(line);
        std::string tok;
        while (iss >> tok) tokens.push_back(tok);
        return tokens;
    }

    std::string Console::GetRest(const std::string& line)
    {
        size_t pos = line.find_first_of(" \t");
        if (pos == std::string::npos) return "";
        pos = line.find_first_not_of(" \t", pos);
        if (pos == std::string::npos) return "";
        return line.substr(pos);
    }

    std::wstring Console::ToWide(const std::string& s)
    {
        if (s.empty()) return L"";
        int n = MultiByteToWideChar(CP_UTF8, 0,
            s.c_str(), (int)s.size(), nullptr, 0);
        std::wstring out(n, 0);
        MultiByteToWideChar(CP_UTF8, 0,
            s.c_str(), (int)s.size(), &out[0], n);
        return out;
    }

    std::string Console::ToNarrow(const std::wstring& s)
    {
        if (s.empty()) return "";
        int n = WideCharToMultiByte(CP_UTF8, 0,
            s.c_str(), (int)s.size(),
            nullptr, 0, nullptr, nullptr);
        std::string out(n, 0);
        WideCharToMultiByte(CP_UTF8, 0,
            s.c_str(), (int)s.size(),
            &out[0], n, nullptr, nullptr);
        return out;
    }

    // --- Command dispatcher ---

    void Console::ProcessCommand(const std::string& line)
    {
        auto args = Tokenise(line);
        if (args.empty()) return;

        std::string cmd = args[0];
        std::transform(cmd.begin(), cmd.end(),
            cmd.begin(), ::tolower);

        if      (cmd == "help")      CmdHelp(args);
        else if (cmd == "stop")      CmdStop(args);
        else if (cmd == "list")      CmdList(args);
        else if (cmd == "say")       CmdSay(GetRest(line));
        else if (cmd == "save-all")  CmdSaveAll(args);
        else if (cmd == "tp")        CmdTp(args);
        else if (cmd == "gamemode")  CmdGamemode(args);
        else if (cmd == "ban")       CmdBan(GetRest(line));
        else if (cmd == "ban-ip")    CmdBanIp(GetRest(line));
        else if (cmd == "pardon")    CmdPardon(args);
        else if (cmd == "pardon-ip") CmdPardonIp(args);
        else if (cmd == "banlist")   CmdBanlist(args);
        else if (cmd == "whitelist") CmdWhitelist(args);
        else if (cmd == "op")        CmdOp(args);
        else if (cmd == "deop")      CmdDeop(args);
        else if (cmd == "time")      CmdTime(args);
        else if (cmd == "weather")   CmdWeather(args);
        else if (cmd == "kill")      CmdKill(args);
        else if (cmd == "give")      CmdGive(args);
        else if (cmd == "plugins")   CmdPlugins(args);
        else if (cmd == "reload")    CmdReload(args);
        else
            Logger::Warn("Console",
                "Unknown command: '%s'. Type 'help'.",
                args[0].c_str());
    }

    // ========== help ==========
    void Console::CmdHelp(
        const std::vector<std::string>& /*args*/)
    {
        Logger::Info("Console", "--- Available Commands ---");
        Logger::Info("Console", "  help             - Show this help");
        Logger::Info("Console", "  stop             - Shut down the server");
        Logger::Info("Console", "  list             - Show online players");
        Logger::Info("Console", "  say <msg>        - Broadcast as [Server]");
        Logger::Info("Console", "  save-all         - Force world save");
        Logger::Info("Console", "  tp <a> <b>       - Teleport player a to b");
        Logger::Info("Console", "  gamemode <m> <p> - Set gamemode");
        Logger::Info("Console", "  ban <player> [r] - Ban a player");
        Logger::Info("Console", "  ban-ip <ip> [r]  - Ban an IP");
        Logger::Info("Console", "  pardon <player>  - Unban a player");
        Logger::Info("Console", "  pardon-ip <ip>   - Unban an IP");
        Logger::Info("Console", "  banlist [type]   - List bans");
        Logger::Info("Console", "  whitelist <sub>  - Manage whitelist");
        Logger::Info("Console", "  op <player>      - Grant operator");
        Logger::Info("Console", "  deop <player>    - Revoke operator");
        Logger::Info("Console", "  time <set|add> v - Set world time");
        Logger::Info("Console", "  weather <type>   - Set weather");
        Logger::Info("Console", "  kill <player>    - Kill a player");
        Logger::Info("Console", "  give <p> <id> .. - Give item");
        Logger::Info("Console", "  plugins          - List plugins");
        Logger::Info("Console", "  reload           - Reload configs");
    }

    // ========== stop ==========
    void Console::CmdStop(
        const std::vector<std::string>& /*args*/)
    {
        Logger::Info("Console", "Stopping the server...");
        m_server->RequestShutdown();
    }

    // ========== list ==========
    void Console::CmdList(
        const std::vector<std::string>& /*args*/)
    {
        auto names = m_server->GetConnectionManager()
            ->GetPlayerNames();
        if (names.empty()) {
            Logger::Info("Console",
                "There are 0 players online.");
        } else {
            Logger::Info("Console",
                "There are %d player(s) online:",
                (int)names.size());
            for (auto& n : names)
                Logger::Info("Console", "  - %ls",
                    n.c_str());
        }
    }

    // ========== say ==========
    void Console::CmdSay(const std::string& rest)
    {
        if (rest.empty()) {
            Logger::Info("Console", "Usage: say <message>");
            return;
        }
        std::wstring wmsg = ToWide(rest);
        std::wstring formatted = L"[Server] " + wmsg;
        Logger::Info("Chat", "[Server] %s", rest.c_str());
        m_server->GetConnectionManager()
            ->BroadcastChat(formatted);
    }

    // ========== save-all ==========
    void Console::CmdSaveAll(
        const std::vector<std::string>& /*args*/)
    {
        if (!m_server->GetSaveManager()) {
            Logger::Warn("Console", "Saving is disabled.");
            return;
        }
        Logger::Info("Console", "Forcing world save...");
        m_server->GetSaveManager()->SaveNow();
        Logger::Info("Console", "World saved.");
    }

    // ========== tp ==========
    void Console::CmdTp(
        const std::vector<std::string>& args)
    {
        if (args.size() < 3) {
            Logger::Info("Console",
                "Usage: tp <player> <target>");
            return;
        }
        auto* cm = m_server->GetConnectionManager();
        auto* src = cm->FindPlayerByName(ToWide(args[1]));
        if (!src) {
            Logger::Warn("Console",
                "Player not found: %s", args[1].c_str());
            return;
        }
        auto* dst = cm->FindPlayerByName(ToWide(args[2]));
        if (!dst) {
            Logger::Warn("Console",
                "Target not found: %s", args[2].c_str());
            return;
        }
        // Teleport src to dst's position
        double x = dst->GetX();
        double y = dst->GetY();
        double z = dst->GetZ();
        auto pkt = PacketHandler::WriteMovePlayerPosRot(
            x, y, y + 1.62, z, 0.0f, 0.0f, true, false);
        src->SendPacket(pkt);
        Logger::Info("Console",
            "Teleported %s to %s (%.1f, %.1f, %.1f)",
            args[1].c_str(), args[2].c_str(), x, y, z);
    }

    // ========== gamemode ==========
    void Console::CmdGamemode(
        const std::vector<std::string>& args)
    {
        if (args.size() < 3) {
            Logger::Info("Console",
                "Usage: gamemode <mode> <player>");
            return;
        }
        // Parse mode
        std::string modeStr = args[1];
        std::transform(modeStr.begin(), modeStr.end(),
            modeStr.begin(), ::tolower);
        int mode = -1;
        if (modeStr == "0" || modeStr == "survival"
            || modeStr == "s")       mode = 0;
        else if (modeStr == "1" || modeStr == "creative"
            || modeStr == "c")       mode = 1;
        else if (modeStr == "2" || modeStr == "adventure"
            || modeStr == "a")       mode = 2;
        if (mode < 0) {
            Logger::Warn("Console",
                "Unknown gamemode: %s", args[1].c_str());
            return;
        }
        auto* cm = m_server->GetConnectionManager();
        auto* player = cm->FindPlayerByName(
            ToWide(args[2]));
        if (!player) {
            Logger::Warn("Console",
                "Player not found: %s", args[2].c_str());
            return;
        }
        // Send GameEvent CHANGE_GAME_MODE (event=3)
        // to actually switch the client's gamemode
        player->SendPacket(
            PacketHandler::WriteGameEvent(3, mode));
        // Also send PlayerAbilities for flight flags
        bool creative = (mode == 1);
        player->SendPacket(
            PacketHandler::WritePlayerAbilities(
                creative, false, creative, creative,
                0.05f, 0.1f));
        // Update server-side gamemode so HandlePlayerAction uses the
        // correct break logic: creative=instant on START, survival=STOP only
        player->SetGameMode(mode);
        Logger::Info("Console",
            "Set %s's gamemode to %d",
            args[2].c_str(), mode);
    }

    // ========== ban ==========
    void Console::CmdBan(const std::string& rest)
    {
        auto args = Tokenise(rest);
        if (args.empty()) {
            Logger::Info("Console",
                "Usage: ban <player> [reason]");
            return;
        }
        std::string playerName = args[0];
        std::string reason;
        for (size_t i = 1; i < args.size(); i++) {
            if (!reason.empty()) reason += " ";
            reason += args[i];
        }

        auto* cm = m_server->GetConnectionManager();
        auto* conn = cm->FindPlayerByName(
            ToWide(playerName));
        if (!conn) {
            Logger::Warn("Console",
                "Player not found: %s (only online "
                "players can be banned)",
                playerName.c_str());
            return;
        }
        PlayerUID xuid = conn->GetPrimaryXuid();
        std::string narrowName =
            ToNarrow(conn->GetPlayerName());

        if (m_server->GetBanList()->IsPlayerBanned(xuid))
        {
            Logger::Warn("Console",
                "That player is already banned.");
            return;
        }

        m_server->GetBanList()->AddPlayerBan(
            xuid, narrowName, reason, "Console");

        // Disconnect with banned reason
        cm->KickPlayer(conn, DisconnectReason::Banned);
        Logger::Info("Console",
            "Banned player %s.", narrowName.c_str());
    }

    // ========== ban-ip ==========
    void Console::CmdBanIp(const std::string& rest)
    {
        auto args = Tokenise(rest);
        if (args.empty()) {
            Logger::Info("Console",
                "Usage: ban-ip <ip> [reason]");
            return;
        }
        std::string ip = args[0];
        std::string reason;
        for (size_t i = 1; i < args.size(); i++) {
            if (!reason.empty()) reason += " ";
            reason += args[i];
        }
        if (m_server->GetBanList()->IsIpBanned(ip)) {
            Logger::Warn("Console",
                "That IP is already banned.");
            return;
        }
        m_server->GetBanList()->AddIpBan(
            ip, reason, "Console");
        Logger::Info("Console",
            "Banned IP %s.", ip.c_str());
    }

    // ========== pardon ==========
    void Console::CmdPardon(
        const std::vector<std::string>& args)
    {
        if (args.size() < 2) {
            Logger::Info("Console",
                "Usage: pardon <player>");
            return;
        }
        if (m_server->GetBanList()
                ->RemovePlayerBanByName(args[1]))
            Logger::Info("Console",
                "Unbanned %s.", args[1].c_str());
        else
            Logger::Warn("Console",
                "That player is not banned.");
    }

    // ========== pardon-ip ==========
    void Console::CmdPardonIp(
        const std::vector<std::string>& args)
    {
        if (args.size() < 2) {
            Logger::Info("Console",
                "Usage: pardon-ip <ip>");
            return;
        }
        if (m_server->GetBanList()->RemoveIpBan(args[1]))
            Logger::Info("Console",
                "Unbanned IP %s.", args[1].c_str());
        else
            Logger::Warn("Console",
                "That IP is not banned.");
    }

    // ========== banlist ==========
    void Console::CmdBanlist(
        const std::vector<std::string>& args)
    {
        std::string type = "players";
        if (args.size() >= 2) {
            type = args[1];
            std::transform(type.begin(), type.end(),
                type.begin(), ::tolower);
        }
        if (type == "ips") {
            auto& ips = m_server->GetBanList()
                ->GetBannedIps();
            Logger::Info("Console",
                "There are %d IP ban(s):",
                (int)ips.size());
            for (auto& e : ips)
                Logger::Info("Console", "  %s (%s)",
                    e.ip.c_str(),
                    e.metadata.reason.c_str());
        } else {
            auto& players = m_server->GetBanList()
                ->GetBannedPlayers();
            Logger::Info("Console",
                "There are %d player ban(s):",
                (int)players.size());
            for (auto& e : players)
                Logger::Info("Console", "  %s [%s] (%s)",
                    e.name.c_str(), e.xuid.c_str(),
                    e.metadata.reason.c_str());
        }
    }

    // ========== whitelist ==========
    void Console::CmdWhitelist(
        const std::vector<std::string>& args)
    {
        if (args.size() < 2) {
            Logger::Info("Console",
                "Usage: whitelist <on|off|add|remove|list>");
            return;
        }
        std::string sub = args[1];
        std::transform(sub.begin(), sub.end(),
            sub.begin(), ::tolower);

        if (sub == "on") {
            m_server->GetConfig().whiteList = true;
            m_server->GetConfig().Save();
            Logger::Info("Console",
                "Whitelist is now ENABLED.");
        }
        else if (sub == "off") {
            m_server->GetConfig().whiteList = false;
            m_server->GetConfig().Save();
            Logger::Info("Console",
                "Whitelist is now DISABLED.");
        }
        else if (sub == "add") {
            if (args.size() < 3) {
                Logger::Info("Console",
                    "Usage: whitelist add <player>");
                return;
            }
            // Find online player to get XUID
            auto* cm = m_server->GetConnectionManager();
            auto* conn = cm->FindPlayerByName(
                ToWide(args[2]));
            if (conn) {
                m_server->GetWhitelist()->Add(
                    conn->GetPrimaryXuid(),
                    ToNarrow(conn->GetPlayerName()));
            } else {
                // Add by name only (no XUID)
                m_server->GetWhitelist()->Add(
                    INVALID_XUID, args[2]);
            }
            Logger::Info("Console",
                "Added %s to the whitelist.",
                args[2].c_str());
        }
        else if (sub == "remove") {
            if (args.size() < 3) {
                Logger::Info("Console",
                    "Usage: whitelist remove <player>");
                return;
            }
            if (m_server->GetWhitelist()
                    ->RemoveByName(args[2]))
                Logger::Info("Console",
                    "Removed %s from the whitelist.",
                    args[2].c_str());
            else
                Logger::Warn("Console",
                    "That player is not whitelisted.");
        }
        else if (sub == "list") {
            auto& entries = m_server->GetWhitelist()
                ->GetEntries();
            Logger::Info("Console",
                "There are %d whitelisted player(s):",
                (int)entries.size());
            for (auto& e : entries)
                Logger::Info("Console", "  %s [%s]",
                    e.name.c_str(), e.xuid.c_str());
        }
        else if (sub == "reload") {
            m_server->GetWhitelist()->Reload();
            Logger::Info("Console",
                "Whitelist reloaded.");
        }
        else {
            Logger::Warn("Console",
                "Unknown whitelist subcommand: %s",
                sub.c_str());
        }
    }

    // ========== op ==========
    void Console::CmdOp(
        const std::vector<std::string>& args)
    {
        if (args.size() < 2) {
            Logger::Info("Console",
                "Usage: op <player>");
            return;
        }
        auto* cm = m_server->GetConnectionManager();
        auto* conn = cm->FindPlayerByName(
            ToWide(args[1]));
        if (conn) {
            m_server->GetOpsList()->Add(
                conn->GetPrimaryXuid(),
                ToNarrow(conn->GetPlayerName()));
        } else {
            // Add by name only
            m_server->GetOpsList()->Add(
                INVALID_XUID, args[1]);
        }
        Logger::Info("Console",
            "Opped %s.", args[1].c_str());
    }

    // ========== deop ==========
    void Console::CmdDeop(
        const std::vector<std::string>& args)
    {
        if (args.size() < 2) {
            Logger::Info("Console",
                "Usage: deop <player>");
            return;
        }
        if (m_server->GetOpsList()
                ->RemoveByName(args[1]))
            Logger::Info("Console",
                "De-opped %s.", args[1].c_str());
        else
            Logger::Warn("Console",
                "That player is not an op.");
    }

    // ========== time ==========
    void Console::CmdTime(
        const std::vector<std::string>& args)
    {
        if (args.size() < 3) {
            Logger::Info("Console",
                "Usage: time <set|add> <value>");
            Logger::Info("Console",
                "  0=dawn 6000=noon 12000=dusk "
                "18000=midnight");
            return;
        }
        std::string sub = args[1];
        std::transform(sub.begin(), sub.end(),
            sub.begin(), ::tolower);

        int64_t val;
        // Support named time values
        std::string timeStr = args[2];
        std::string timeLower = timeStr;
        std::transform(timeLower.begin(), timeLower.end(),
            timeLower.begin(), ::tolower);
        if (timeLower == "day" || timeLower == "dawn")
            val = 0;
        else if (timeLower == "noon")
            val = 6000;
        else if (timeLower == "dusk" || timeLower == "sunset")
            val = 12000;
        else if (timeLower == "night" || timeLower == "midnight")
            val = 18000;
        else {
            try { val = std::stoll(timeStr); }
            catch (...) {
                Logger::Warn("Console",
                    "Invalid time value: %s",
                    timeStr.c_str());
                return;
            }
        }

        World* world = m_server->GetWorld();
        if (!world) return;

        int64_t gameTime = world->GetGameTime();
        int64_t dayTime = world->GetDayTime();

        if (sub == "set") {
            dayTime = val;
        } else if (sub == "add") {
            dayTime += val;
            gameTime += val;
        } else {
            Logger::Warn("Console",
                "Usage: time <set|add> <value>");
            return;
        }

        world->SetDayTime(dayTime);
        world->SetGameTime(gameTime);

        // Broadcast time update
        auto pkt = PacketHandler::WriteSetTime(
            gameTime, dayTime);
        m_server->GetConnectionManager()
            ->BroadcastPacket(pkt);

        Logger::Info("Console",
            "Set time to %lld.", (long long)dayTime);
    }

    // ========== weather ==========
    void Console::CmdWeather(
        const std::vector<std::string>& args)
    {
        if (args.size() < 2) {
            Logger::Info("Console",
                "Usage: weather <clear|rain|thunder>");
            return;
        }
        std::string type = args[1];
        std::transform(type.begin(), type.end(),
            type.begin(), ::tolower);

        // GameEvent: 1=BEGIN_RAINING, 2=STOP_RAINING,
        //            7=THUNDER_LEVEL, 8=NO idea (rain?)
        // We use: clear=STOP_RAINING(2),
        //   rain=BEGIN_RAINING(1), thunder=BEGIN_RAINING(1)
        int eventId = 2; // default: stop rain
        int param = 0;

        if (type == "clear") {
            eventId = 2; // STOP_RAINING
        } else if (type == "rain") {
            eventId = 1; // BEGIN_RAINING
        } else if (type == "thunder") {
            eventId = 1; // BEGIN_RAINING (+ thunder)
        } else {
            Logger::Warn("Console",
                "Unknown weather: %s", type.c_str());
            return;
        }

        auto pkt = PacketHandler::WriteGameEvent(
            eventId, param);
        m_server->GetConnectionManager()
            ->BroadcastPacket(pkt);
        Logger::Info("Console",
            "Weather set to %s.", type.c_str());
    }

    // ========== kill ==========
    void Console::CmdKill(
        const std::vector<std::string>& args)
    {
        if (args.size() < 2) {
            Logger::Info("Console",
                "Usage: kill <player>");
            return;
        }
        auto* cm = m_server->GetConnectionManager();
        auto* conn = cm->FindPlayerByName(
            ToWide(args[1]));
        if (!conn) {
            Logger::Warn("Console",
                "Player not found: %s", args[1].c_str());
            return;
        }
        // Route through ApplyDamage so m_isDead is set correctly
        // and EntityEvent(Death) is sent — matches server-side kill behaviour.
        conn->ApplyDamage(conn->GetHealth() + 1.0f);
        Logger::Info("Console", "Killed %s.", args[1].c_str());
    }

    // ========== give ==========
    void Console::CmdGive(
        const std::vector<std::string>& args)
    {
        // give <player> <id> [amount] [aux]
        if (args.size() < 3) {
            Logger::Info("Console",
                "Usage: give <player> <id> [amount] [aux]");
            return;
        }
        auto* cm = m_server->GetConnectionManager();
        auto* conn = cm->FindPlayerByName(
            ToWide(args[1]));
        if (!conn) {
            Logger::Warn("Console",
                "Player not found: %s", args[1].c_str());
            return;
        }
        int itemId = 0, amount = 1, aux = 0;
        try { itemId = std::stoi(args[2]); }
        catch (...) {
            Logger::Warn("Console",
                "Invalid item id: %s",
                args[2].c_str());
            return;
        }
        if (args.size() >= 4) {
            try { amount = std::stoi(args[3]); }
            catch (...) {}
        }
        if (args.size() >= 5) {
            try { aux = std::stoi(args[4]); }
            catch (...) {}
        }

        // NOTE: Actual item giving requires inventory
        // packet support which is M5+. For now, log it.
        Logger::Warn("Console",
            "give: item delivery not yet implemented "
            "(needs inventory packets). "
            "Would give %s x%d of item %d:%d.",
            args[1].c_str(), amount, itemId, aux);
    }

    // ========== plugins ==========
    void Console::CmdPlugins(
        const std::vector<std::string>& /*args*/)
    {
        // M5: PluginLoader not implemented yet
        Logger::Info("Console",
            "Plugins: none loaded "
            "(plugin system is Milestone 5)");
    }

    // ========== reload ==========
    void Console::CmdReload(
        const std::vector<std::string>& /*args*/)
    {
        Logger::Info("Console", "Reloading configs...");
        m_server->GetBanList()->Reload();
        m_server->GetWhitelist()->Reload();
        m_server->GetOpsList()->Reload();
        Logger::Info("Console",
            "Reloaded ban list, whitelist, and ops.");
    }

} // namespace LCEServer
