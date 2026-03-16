# LCEServer

<p align="center">
  <img alt="Platform" src="https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows" />
  <img alt="C++" src="https://img.shields.io/badge/C%2B%2B-17-00599C?style=for-the-badge&logo=c%2B%2B" />
  <img alt="CMake" src="https://img.shields.io/badge/CMake-3.20%2B-064F8C?style=for-the-badge&logo=cmake" />
  <img alt="LCE Protocol" src="https://img.shields.io/badge/LCE%20Protocol-v78%20%7C%20Net%20560-2E7D32?style=for-the-badge" />
</p>

Standalone dedicated server for **Minecraft Legacy Console Edition**, written in C++17.
Speaks the native LCE TCP protocol so unmodified legacy console clients can connect directly.

## Contents

- [Status](#status)
- [Highlights](#highlights)
- [Repository Layout](#repository-layout)
- [Requirements](#requirements)
- [Build](#build)
- [Run](#run)
- [Configuration](#configuration)
- [World Format](#world-format)
- [Protocol Notes](#protocol-notes)
- [Current Limitations](#current-limitations)

## Status

| Phase | Description | State |
|-------|-------------|-------|
| P1 | Core networking, login, world, block interaction, player state, multiplayer join/leave | ✅ Complete |
| P2 | Entity movement packets (Move/MoveLook/Look/Teleport/HeadRot) | ✅ Implemented |
| P2 | AddPlayer entity data block | 🐛 Bug — crash on second player join (fix in progress) |
| P3 | Inventory system | ❌ Not started |

## Highlights

### Working now
- Native TCP server with LCE-style length-prefixed packet framing
- Pre-login and login handshake for protocol version `78` / net version `560`
- Full join/spawn flow: spawn position, abilities, time sync, spiral chunk streaming, teleport
- World loading: Anvil sections + palette-based (1.13+) + LCE binary format
- Block breaking (ID 14) and placing (ID 15) with TileUpdate broadcast
- SetHealth, fall damage, EntityEvent (hurt/death), death + respawn cycle
- AddPlayer / RemoveEntities for multiplayer join and leave
- Entity movement broadcasting: Move, MoveLook, Look, Teleport, HeadRot
- Arm-swing Animate broadcast
- Skylight BFS + block light BFS — cross-chunk, torches correct
- Spiral chunk loading sorted nearest-first; lazy load in DrainChunkQueue
- Chunk ref-count unloading — evicted only when all viewers have moved away
- Configurable view distance and chunk send rate
- 20 console commands with access control
- RCON server (TCP, Minecraft RCON protocol)
- server.properties loading/saving with defaults
- Persistent ban list, whitelist, and operator list
- Gamemode tracking from LoginPacket; fall damage suppressed in creative

### In progress / planned
- Fix AddPlayer entity data crash (second player join)
- Inventory system (P3)
- Plugin API and DLL loader

## Repository Layout

```
server/
  src/
    core/       Server startup, config, logging, TCP layer, connections, packet handling
    world/      NBT, region files, world bootstrap, chunk generation, autosave
    access/     Ban list, whitelist, and ops persistence/logic
    api/        Public server API surface (plugin-facing scaffolding)
    console/    Interactive server console command system
    plugins/    Plugin loader area (planned)
  build/        Local CMake build output
  PACKETS.md    Full packet tracker with wire format notes
  README.md     This file
  CMakeLists.txt
```

## Requirements

- Windows
- CMake `3.20+`
- C++17-capable compiler
- Visual Studio 2022 Build Tools or Visual Studio 2022

Notes:
- The current code uses Win32 and Winsock APIs directly — builds are Windows-only.
- `zlib` is required for chunk compression. CMake uses a system zlib if available, otherwise
  fetches it automatically.

## Build

From the `server/` directory:

```powershell
cmake -S . -B build
cmake --build build --config Release
```

With a multi-config generator (Visual Studio), the executable is at:
- `build/Release/LCEServer.exe`

## Run

Run from the `server/` directory so relative paths resolve for `server.properties` and `worlds/`:

```powershell
.\build\Release\LCEServer.exe
```

On first start the server will:
- Create `server.properties` if it does not exist
- Create a `worlds/<level-name>/` directory
- Generate a new world if no `level.dat` exists
- Start listening on the configured IP and port

Press `Ctrl+C` to request a clean shutdown.
Type `help` in the server console to list available commands.

## Configuration

The server reads `server.properties` from the working directory.

```properties
# Network
server-port=25565
server-ip=0.0.0.0
server-name=LCEServer
lan-advertise=true

# World
level-name=world
level-id=
level-seed=
level-type=default
max-build-height=256

# Game settings
gamemode=0
difficulty=1
pvp=true
trust-players=false
fire-spreads=true
tnt=true
spawn-animals=true
spawn-npcs=true
spawn-monsters=true
allow-flight=true
allow-nether=true
generate-structures=true
bonus-chest=false
friends-of-friends=true
gamertags=true
bedrock-fog=false
mob-griefing=true
keep-inventory=false
natural-regeneration=true
do-daylight-cycle=true

# Server
max-players=8
motd=A Minecraft LCE Server
autosave-interval=300
log-level=info
disable-saving=false
white-list=false
view-distance=8
chunks-per-tick=10

# RCON
rcon-port=25575
rcon-password=
```

## World Format

LCEServer manages world data itself rather than linking against the original game server runtime.

- `level.dat` is stored using NBT with gzip compression
- Chunk data is stored in classic McRegion `.mcr` files
- Supports loading Anvil (1.13+ palette-based) worlds — used for test world `worlds/stampy`
- Missing chunks are generated as a flat world and saved back to disk

## Protocol Notes

| Constant | Value |
|----------|-------|
| Net version | `560` |
| Protocol version | `78` |
| Default port | `25565` |
| RCON port | `25575` |

Connection flow:
1. Client sends PreLogin — server validates net version and replies.
2. Client sends Login — server validates protocol version, checks bans/whitelist.
3. Server sends login response, spawn data, and nearby chunks via spiral stream.
4. On movement: delta-based entity movement packets broadcast to other players.

## Current Limitations

- AddPlayer entity data crash on second player join (fix in progress)
- No inventory system yet (P3)
- No plugin loading yet (planned)
- Some console commands are scaffolding-only (e.g. `give` logs intent, doesn't deliver items)
- LAN advertising config exists but broadcast is not implemented

This project is in active development. Expect bugs and breaking changes.
