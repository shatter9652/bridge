// LCEServer — Console CLI with ServerCliEngine design
// Background thread reads stdin, dispatches through
// a tokenised command registry
#pragma once

#include "../core/Types.h"

namespace LCEServer
{
    class Server;

    class Console
    {
    public:
        Console(Server* server);
        ~Console();

        void Start();
        void Stop();

        // Queue a command line for processing on tick
        void EnqueueCommand(const std::string& line);

        // Process queued commands (main tick thread)
        void Tick();

    private:
        static DWORD WINAPI InputThreadProc(
            LPVOID param);

        // Tokenise and dispatch one command line
        void ProcessCommand(const std::string& line);

        // --- Built-in command handlers ---
        void CmdHelp(const std::vector<std::string>& args);
        void CmdStop(const std::vector<std::string>& args);
        void CmdList(const std::vector<std::string>& args);
        void CmdSay(const std::string& rest);
        void CmdSaveAll(const std::vector<std::string>& args);
        void CmdTp(const std::vector<std::string>& args);
        void CmdGamemode(const std::vector<std::string>& args);
        void CmdBan(const std::string& rest);
        void CmdBanIp(const std::string& rest);
        void CmdPardon(const std::vector<std::string>& args);
        void CmdPardonIp(const std::vector<std::string>& args);
        void CmdBanlist(const std::vector<std::string>& args);
        void CmdWhitelist(const std::vector<std::string>& args);
        void CmdOp(const std::vector<std::string>& args);
        void CmdDeop(const std::vector<std::string>& args);
        void CmdTime(const std::vector<std::string>& args);
        void CmdWeather(const std::vector<std::string>& args);
        void CmdKill(const std::vector<std::string>& args);
        void CmdGive(const std::vector<std::string>& args);
        void CmdPlugins(const std::vector<std::string>& args);
        void CmdReload(const std::vector<std::string>& args);

        // Tokenise a command line into args
        static std::vector<std::string> Tokenise(
            const std::string& line);
        // Get rest-of-line after first token
        static std::string GetRest(
            const std::string& line);
        // Convert wstring <-> string
        static std::wstring ToWide(const std::string& s);
        static std::string ToNarrow(const std::wstring& s);

        Server*             m_server;
        HANDLE              m_inputThread = NULL;
        std::atomic<bool>   m_running{false};
        std::mutex          m_queueMutex;
        std::vector<std::string> m_commandQueue;
    };
}
