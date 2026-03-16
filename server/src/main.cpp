// LCEServer — Entry point
// Minecraft Legacy Console Edition dedicated server
#include "core/Types.h"
#include "core/Server.h"
#include "core/Logger.h"
#include "core/Protocol.h"
#include <csignal>

static LCEServer::Server* g_server = nullptr;

static BOOL WINAPI ConsoleCtrlHandler(DWORD ctrlType)
{
    switch (ctrlType)
    {
    case CTRL_C_EVENT:
    case CTRL_BREAK_EVENT:
    case CTRL_CLOSE_EVENT:
        if (g_server)
        {
            LCEServer::Logger::Info("Server", "Caught shutdown signal");
            g_server->RequestShutdown();
        }
        return TRUE;
    }
    return FALSE;
}

int main(int argc, char* argv[])
{
    // Enable ANSI colours on Windows console
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    // Banner
    std::printf("\n");
    std::printf("  \033[36m _     ____ _____ ____\033[0m\n");
    std::printf("  \033[36m| |   / ___| ____/ ___|\033[0m  ___  _ ____   _____ _ __\n");
    std::printf("  \033[36m| |  | |   |  _| \\___ \\\033[0m / _ \\| '__\\ \\ / / _ \\ '__|\n");
    std::printf("  \033[36m| |__| |___| |___ ___) |\033[0m  __/ |   \\ V /  __/ |\n");
    std::printf("  \033[36m|_____\\____|_____|____/\033[0m \\___|_|    \\_/ \\___|_|\n");
    std::printf("\n");
    std::printf("  Minecraft LCE Dedicated Server\n");
    std::printf("  Net version: %d | Protocol: %d\n",
        LCEServer::MINECRAFT_NET_VERSION,
        LCEServer::NETWORK_PROTOCOL_VERSION);
    std::printf("\n");

    // Initialize file logging (logs/latest.log + gzip rotation)
    LCEServer::Logger::Initialize();

    // Register Ctrl+C handler
    SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);

    LCEServer::Server server;
    g_server = &server;

    if (!server.Start())
    {
        LCEServer::Logger::Error("Server", "Failed to start server");
        LCEServer::Logger::Shutdown();
        return 1;
    }

    // Blocks until shutdown
    server.Run();

    g_server = nullptr;
    LCEServer::Logger::Shutdown();
    return 0;
}
