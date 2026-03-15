cmake_minimum_required(VERSION 3.20)
project(LCEServer)

set(CMAKE_CXX_STANDARD 17)

# Reference source tree
set(LCE_SOURCE_ROOT "${CMAKE_SOURCE_DIR}/../Minecraft-LegacyConsoleEdition")

# Include paths
include_directories(
    src/
)

# LCEServer sources
add_executable(LCEServer
    src/main.cpp
    src/core/Logger.cpp
    src/core/Server.cpp
    src/core/ServerConfig.cpp
    src/core/TcpLayer.cpp
    src/core/ConnectionManager.cpp
    src/core/Connection.cpp
    src/core/PacketHandler.cpp
    src/console/Console.cpp
    src/world/Nbt.cpp
    src/world/RegionFile.cpp
    src/world/World.cpp
    src/world/SaveManager.cpp
    src/world/LceSaveFile.cpp
    # Milestone 4: Access control + JSON utilities
    src/access/JsonUtil.cpp
    src/access/BanList.cpp
    src/access/Whitelist.cpp
    src/access/OpsList.cpp
)

# This is a standalone server — we do NOT link against Minecraft.World
# or pull in the LCE stdafx.h. All packet serialisation is reimplemented
# in PacketHandler using the exact same wire format.

# Find zlib for chunk compression (RLE + zlib matches Win64 CompressLZXRLE)
find_package(ZLIB QUIET)
if(NOT ZLIB_FOUND)
    # Fetch zlib if not installed
    include(FetchContent)
    FetchContent_Declare(zlib
        GIT_REPOSITORY https://github.com/madler/zlib.git
        GIT_TAG v1.3.1
    )
    FetchContent_MakeAvailable(zlib)
    set(ZLIB_LIB zlibstatic)
    # FetchContent puts zlib headers in both source and binary dirs
    target_include_directories(LCEServer PRIVATE
        ${zlib_SOURCE_DIR}
        ${zlib_BINARY_DIR}
    )
else()
    set(ZLIB_LIB ZLIB::ZLIB)
endif()

target_link_libraries(LCEServer
    Ws2_32
    ${ZLIB_LIB}
)
