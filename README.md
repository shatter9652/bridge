# Minecraft Legacy Console Edition

<p align="center">
  <img src="https://img.shields.io/badge/Minecraft-Legacy%20Console%20Edition-62B47A?style=for-the-badge&logo=minecraft&logoColor=white" alt="Minecraft LCE" />
  <img src="https://img.shields.io/badge/LCE%20Protocol-v78%20%7C%20Net%20560-2E7D32?style=for-the-badge" alt="LCE Protocol" />
  <img src="https://img.shields.io/badge/Platform-Windows%20x64-0078D6?style=for-the-badge&logo=windows&logoColor=white" alt="Platform" />
  <img src="https://img.shields.io/github/license/veroxsity/MinecraftLCE?style=for-the-badge" alt="License" />
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Server-C%2B%2B%2017-00599C?style=flat-square&logo=c%2B%2B&logoColor=white" alt="C++17" />
  <img src="https://img.shields.io/badge/Bridge-Java%2021-ED8B00?style=flat-square&logo=openjdk&logoColor=white" alt="Java 21" />
  <img src="https://img.shields.io/badge/Client-C%2B%2B%20%7C%20DirectX-68217A?style=flat-square&logo=visualstudio&logoColor=white" alt="Client" />
  <img src="https://img.shields.io/badge/Build-CMake%203.20%2B-064F8C?style=flat-square&logo=cmake&logoColor=white" alt="CMake" />
  <img src="https://img.shields.io/badge/Build-Gradle-02303A?style=flat-square&logo=gradle&logoColor=white" alt="Gradle" />
</p>

<p align="center">
  <a href="https://ko-fi.com/veroxsity"><img src="https://img.shields.io/badge/Ko--fi-Support%20Development-FF5E5B?style=for-the-badge&logo=ko-fi&logoColor=white" alt="Ko-fi" /></a>
  <a href="https://github.com/veroxsity/MinecraftLCE/issues"><img src="https://img.shields.io/github/issues/veroxsity/MinecraftLCE?style=for-the-badge&color=orange" alt="Issues" /></a>
  <a href="https://github.com/veroxsity/MinecraftLCE/commits/main"><img src="https://img.shields.io/github/last-commit/veroxsity/MinecraftLCE?style=for-the-badge&color=blue" alt="Last Commit" /></a>
</p>

---

A monorepo for **Minecraft Legacy Console Edition** tooling and infrastructure — a from-scratch dedicated server, a modified game client, a protocol bridge for joining Java servers, and a launcher.

## Project Status

| Component | Description | Status |
|-----------|-------------|--------|
| **LCEServer** | Custom C++17 dedicated server | 🟢 P1 & P2 complete — playable multiplayer |
| **LCE Client** | Editable fork with KB/M input & LAN | 🟢 Buildable & functional |
| **LCEBridge** | LCE → Java Edition protocol translator | 🟡 In development |
| **Launcher** | LCE game launcher | ⚪ Planned |

---

## 🖥️ LCEServer

<p>
  <img src="https://img.shields.io/badge/C%2B%2B-17-00599C?style=flat-square&logo=c%2B%2B&logoColor=white" />
  <img src="https://img.shields.io/badge/CMake-3.20%2B-064F8C?style=flat-square&logo=cmake&logoColor=white" />
  <img src="https://img.shields.io/badge/Platform-Windows-0078D6?style=flat-square&logo=windows&logoColor=white" />
</p>

A custom, from-scratch dedicated server written in C++17. Speaks the native LCE TCP protocol (net version 560, protocol 78) so unmodified legacy console clients can connect directly.

**Highlights:**
- Native TCP server with LCE-style length-prefixed packet framing
- Full login handshake with version validation
- Spiral chunk streaming sorted nearest-first with lazy loading
- Block breaking and placing with broadcast
- Health, fall damage, death, and respawn cycle
- Multiplayer: player spawning, despawning, and entity movement broadcasting
- Skylight and block light BFS with cross-chunk propagation
- 20+ console commands, RCON, persistent ban/whitelist/ops lists
- Configurable view distance and chunk send rate

See [`server/README.md`](server/README.md) for build/run instructions.

---

## 🎮 LCE Client

<p>
  <img src="https://img.shields.io/badge/C%2B%2B-MSVC-00599C?style=flat-square&logo=c%2B%2B&logoColor=white" />
  <img src="https://img.shields.io/badge/Visual%20Studio-2022-5C2D91?style=flat-square&logo=visualstudio&logoColor=white" />
  <img src="https://img.shields.io/badge/DirectX-11-68217A?style=flat-square&logo=windows&logoColor=white" />
</p>

An editable fork of [MinecraftConsoles](https://github.com/kuwacom/MinecraftConsoles) with keyboard/mouse input and LAN multiplayer support. Used for testing the dedicated server and bridge.

See [`client/README.md`](client/README.md) for build instructions.

---

## 🌉 LCEBridge

<p>
  <img src="https://img.shields.io/badge/Java-21-ED8B00?style=flat-square&logo=openjdk&logoColor=white" />
  <img src="https://img.shields.io/badge/Gradle-Kotlin%20DSL-02303A?style=flat-square&logo=gradle&logoColor=white" />
  <img src="https://img.shields.io/badge/MCProtocolLib-GeyserMC-4B8BBE?style=flat-square" />
  <img src="https://img.shields.io/badge/Netty-NIO-333333?style=flat-square" />
</p>

A protocol translator that allows **unmodified LCE clients to join any Minecraft Java Edition server** — the LCE equivalent of [Geyser](https://geysermc.org/) for Bedrock Edition.

```
LCE Client ←── LCE TCP ──→ LCEBridge ←── Java Protocol ──→ Java Server
                            (translator)
```

**Key features:**
- Translates the full LCE TCP protocol (94 packet types) into modern Java Edition protocol
- Runs as a **standalone proxy** or as a **Velocity plugin** for server networks
- Mixed lobbies — LCE, Java, and Bedrock (via Geyser) players on the same server
- [Floodgate](https://github.com/GeyserMC/Floodgate) integration for identity and auth
- Multi-version Java backend support via [ViaVersion](https://github.com/ViaVersion/ViaVersion)
- **Phantom item system** — items that don't exist in LCE are displayed as renamed visual equivalents while preserving the real Java item data for lossless round-trips
- Real-time chunk translation: Java palette sections → LCE reordered format with RLE+zlib

**Deployment options:**

| Mode | Setup |
|------|-------|
| Standalone | LCEBridge JAR → connects to any Java server (Paper, Fabric, Vanilla, etc.) |
| Velocity plugin | Runs inside Velocity alongside Geyser + Floodgate for full cross-platform networks |

---

## 🚀 Launcher

Planned — a custom launcher for managing LCE client installations and server connections.

---

## Contributing

Contributions are welcome! Feel free to open issues or pull requests. If you're interested in helping with a specific component, check the open issues for that area.

## Support the Project

<p align="center">
  <a href="https://ko-fi.com/veroxsity"><img src="https://ko-fi.com/img/githubbutton_sm.svg" alt="Support on Ko-fi" /></a>
</p>
