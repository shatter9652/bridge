# Minecraft Legacy Console Edition

A monorepo workspace for Minecraft Legacy Console Edition (LCE) tooling and infrastructure,
including a from-scratch dedicated server, a modified game client, and a launcher.

## Structure

```
.MinecraftLegacyEdition/
├── source/          # Untouched upstream MinecraftConsoles source (READ-ONLY reference — never edit)
├── server/          # LCE dedicated server (custom C++17 implementation)
├── client/          # LCE client (editable fork of MinecraftConsoles)
└── launcher/        # LCE launcher (planned)
```

### `source/`
The upstream [MinecraftConsoles](https://github.com/kuwacom/MinecraftConsoles) source code, kept
entirely untouched as a read-only reference. Contains `Minecraft.Client`, `Minecraft.World`, CMake
build system, and the Visual Studio solution. **Do not modify any files here.**

### `server/`
A custom, from-scratch LCE dedicated server written in C++17. Speaks the native LCE TCP protocol
(net version 560, protocol 78) so unmodified LCE clients can connect directly.

See [`server/README.md`](server/README.md) for build/run instructions and
[`server/PACKETS.md`](server/PACKETS.md) for the full packet tracker.

**Current status:** P1 complete (player state, health, respawn, entity events, block interaction,
multiplayer join/leave). P2 entity movement implemented; AddPlayer entity data fix in progress.

### `client/`
An editable fork of MinecraftConsoles with keyboard/mouse input and LAN multiplayer support.
Used for testing the dedicated server.

See [`client/README.md`](client/README.md) for build instructions.

### `launcher/`
LCE launcher — planned.

## Rules

- **Never edit files in `source/`** — always work in `client/` or `server/`.
- Read files with Desktop Commander before editing.
- The LCE skill is at `/mnt/skills/user/lce-source/SKILL.md` — consult it when touching LCE source files.
- Design documents and continuation prompts live in `.local/`.
