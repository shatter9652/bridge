// LCEServer — SaveManager implementation
#include "SaveManager.h"
#include "../core/Logger.h"

namespace LCEServer
{
    SaveManager::SaveManager(World* world, int intervalSeconds)
        : m_world(world)
        , m_intervalTicks(intervalSeconds * 20) // 20 TPS
    {
        if (m_intervalTicks <= 0)
            m_intervalTicks = 300 * 20; // default 5 minutes
    }

    void SaveManager::Tick()
    {
        m_tickCounter++;
        if (m_tickCounter >= m_intervalTicks)
        {
            m_tickCounter = 0;
            SaveNow();
        }
    }

    void SaveManager::SaveNow()
    {
        m_saving = true;
        Logger::Info("World", "Autosaving...");
        m_world->SaveAll();
        m_saving = false;
    }
}
