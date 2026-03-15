// LCEServer — Save manager (autosave timer + manual save)
#pragma once

#include "../core/Types.h"
#include "World.h"

namespace LCEServer
{
    class SaveManager
    {
    public:
        SaveManager(World* world, int intervalSeconds);

        // Call every server tick (20 TPS)
        void Tick();

        // Force immediate save
        void SaveNow();

        bool IsSaving() const { return m_saving; }

    private:
        World* m_world;
        int m_intervalTicks;  // autosave interval in ticks
        int m_tickCounter = 0;
        bool m_saving = false;
    };
}
