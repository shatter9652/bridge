# Java 1.21.11 → Legacy Console / 1.6.4 Complete Metadata Mapping (Best-Effort)

Generated from the uploaded **1.21.11 client jar** by scanning every blockstate JSON in `assets/minecraft/blockstates/`.

This file is designed as a **converter template**: every modern block is force-mapped to an older block, and blocks with useful metadata get explicit metadata rules.

## Wildcard rules used in this file

- `[*]` = catch-all / default mapping for the block.
- Extra modern properties not represented in LCE are intentionally ignored.
- Where modern state space is larger than legacy metadata allows, the mapping collapses to the closest old form.
- This is **best-effort and lossy by design** for blocks that did not exist in 1.6.4.

## Table

| Java blockstate pattern | Legacy equivalent | ID:Meta | Notes |
|---|---|---:|---|
| `minecraft:acacia_button[face=floor,*]` | `wooden_button` | `143:1` |  |
| `minecraft:acacia_button[face=wall,facing=east,*]` | `wooden_button` | `143:2` |  |
| `minecraft:acacia_button[face=wall,facing=west,*]` | `wooden_button` | `143:1` |  |
| `minecraft:acacia_button[face=wall,facing=south,*]` | `wooden_button` | `143:3` |  |
| `minecraft:acacia_button[face=wall,facing=north,*]` | `wooden_button` | `143:4` |  |
| `minecraft:acacia_button[powered=true,*]` | `wooden_button` | `143:9` | powered bit approximated (+8) |
| `minecraft:acacia_button[*]` | `wooden_button` | `143:1` |  |
| `minecraft:acacia_door[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:acacia_door[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:acacia_door[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:acacia_door[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:acacia_door[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:acacia_door[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:acacia_door[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:acacia_door[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:acacia_door[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:acacia_door[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:acacia_door[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:acacia_fence[*]` | `fence` | `85:0` |  |
| `minecraft:acacia_fence_gate[facing=south,open=false,*]` | `fence_gate` | `107:0` |  |
| `minecraft:acacia_fence_gate[facing=south,open=true,*]` | `fence_gate` | `107:4` |  |
| `minecraft:acacia_fence_gate[facing=west,open=false,*]` | `fence_gate` | `107:1` |  |
| `minecraft:acacia_fence_gate[facing=west,open=true,*]` | `fence_gate` | `107:5` |  |
| `minecraft:acacia_fence_gate[facing=north,open=false,*]` | `fence_gate` | `107:2` |  |
| `minecraft:acacia_fence_gate[facing=north,open=true,*]` | `fence_gate` | `107:6` |  |
| `minecraft:acacia_fence_gate[facing=east,open=false,*]` | `fence_gate` | `107:3` |  |
| `minecraft:acacia_fence_gate[facing=east,open=true,*]` | `fence_gate` | `107:7` |  |
| `minecraft:acacia_fence_gate[*]` | `fence_gate` | `107:0` |  |
| `minecraft:acacia_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:acacia_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:acacia_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:acacia_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:acacia_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:acacia_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:acacia_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:acacia_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:acacia_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:acacia_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:acacia_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:acacia_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:acacia_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:acacia_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:acacia_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:acacia_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:acacia_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:acacia_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:acacia_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:acacia_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:acacia_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:acacia_leaves[*]` | `leaves` | `18:3` |  |
| `minecraft:acacia_log[axis=y,*]` | `log` | `17:3` |  |
| `minecraft:acacia_log[axis=x,*]` | `log` | `17:7` |  |
| `minecraft:acacia_log[axis=z,*]` | `log` | `17:11` |  |
| `minecraft:acacia_log[*]` | `log` | `17:3` |  |
| `minecraft:acacia_planks[*]` | `planks` | `5:3` |  |
| `minecraft:acacia_pressure_plate[*]` | `wooden_pressure_plate` | `72:0` |  |
| `minecraft:acacia_sapling[*]` | `sapling` | `6:3` |  |
| `minecraft:acacia_shelf[*]` | `stone` | `1:0` | fallback |
| `minecraft:acacia_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:acacia_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:acacia_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:acacia_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:acacia_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:acacia_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:acacia_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:acacia_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:acacia_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:acacia_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:acacia_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:acacia_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:acacia_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:acacia_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:acacia_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:acacia_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:acacia_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:acacia_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:acacia_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:acacia_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:acacia_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:acacia_slab[type=bottom,*]` | `wooden_slab` | `126:3` |  |
| `minecraft:acacia_slab[type=top,*]` | `wooden_slab` | `126:11` |  |
| `minecraft:acacia_slab[type=double,*]` | `wooden_slab` | `125:3` | double slab |
| `minecraft:acacia_slab[*]` | `wooden_slab` | `126:3` |  |
| `minecraft:acacia_stairs[facing=east,half=bottom,*]` | `jungle_stairs` | `136:0` |  |
| `minecraft:acacia_stairs[facing=east,half=top,*]` | `jungle_stairs` | `136:4` |  |
| `minecraft:acacia_stairs[facing=west,half=bottom,*]` | `jungle_stairs` | `136:1` |  |
| `minecraft:acacia_stairs[facing=west,half=top,*]` | `jungle_stairs` | `136:5` |  |
| `minecraft:acacia_stairs[facing=south,half=bottom,*]` | `jungle_stairs` | `136:2` |  |
| `minecraft:acacia_stairs[facing=south,half=top,*]` | `jungle_stairs` | `136:6` |  |
| `minecraft:acacia_stairs[facing=north,half=bottom,*]` | `jungle_stairs` | `136:3` |  |
| `minecraft:acacia_stairs[facing=north,half=top,*]` | `jungle_stairs` | `136:7` |  |
| `minecraft:acacia_stairs[*]` | `jungle_stairs` | `136:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:acacia_trapdoor[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:acacia_trapdoor[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:acacia_trapdoor[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:acacia_trapdoor[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:acacia_trapdoor[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:acacia_trapdoor[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:acacia_trapdoor[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:acacia_trapdoor[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:acacia_trapdoor[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:acacia_trapdoor[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:acacia_trapdoor[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:acacia_wall_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:acacia_wall_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:acacia_wall_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:acacia_wall_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:acacia_wall_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:acacia_wall_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:acacia_wall_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:acacia_wall_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:acacia_wall_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:acacia_wall_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:acacia_wall_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:acacia_wall_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:acacia_wall_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:acacia_wall_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:acacia_wall_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:acacia_wall_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:acacia_wall_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:acacia_wall_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:acacia_wall_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:acacia_wall_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:acacia_wall_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:acacia_wall_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:acacia_wall_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:acacia_wall_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:acacia_wall_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:acacia_wall_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:acacia_wall_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:acacia_wall_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:acacia_wall_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:acacia_wall_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:acacia_wall_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:acacia_wall_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:acacia_wall_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:acacia_wall_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:acacia_wall_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:acacia_wall_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:acacia_wall_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:acacia_wall_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:acacia_wall_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:acacia_wall_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:acacia_wall_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:acacia_wall_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:acacia_wood[axis=y,*]` | `log` | `17:3` |  |
| `minecraft:acacia_wood[axis=x,*]` | `log` | `17:7` |  |
| `minecraft:acacia_wood[axis=z,*]` | `log` | `17:11` |  |
| `minecraft:acacia_wood[*]` | `log` | `17:3` |  |
| `minecraft:activator_rail[shape=north_south,powered=false,*]` | `powered_rail` | `27:0` | unpowered |
| `minecraft:activator_rail[shape=north_south,powered=true,*]` | `powered_rail` | `27:8` | powered |
| `minecraft:activator_rail[shape=east_west,powered=false,*]` | `powered_rail` | `27:1` | unpowered |
| `minecraft:activator_rail[shape=east_west,powered=true,*]` | `powered_rail` | `27:9` | powered |
| `minecraft:activator_rail[shape=ascending_east,powered=false,*]` | `powered_rail` | `27:2` | unpowered |
| `minecraft:activator_rail[shape=ascending_east,powered=true,*]` | `powered_rail` | `27:10` | powered |
| `minecraft:activator_rail[shape=ascending_west,powered=false,*]` | `powered_rail` | `27:3` | unpowered |
| `minecraft:activator_rail[shape=ascending_west,powered=true,*]` | `powered_rail` | `27:11` | powered |
| `minecraft:activator_rail[shape=ascending_north,powered=false,*]` | `powered_rail` | `27:4` | unpowered |
| `minecraft:activator_rail[shape=ascending_north,powered=true,*]` | `powered_rail` | `27:12` | powered |
| `minecraft:activator_rail[shape=ascending_south,powered=false,*]` | `powered_rail` | `27:5` | unpowered |
| `minecraft:activator_rail[shape=ascending_south,powered=true,*]` | `powered_rail` | `27:13` | powered |
| `minecraft:activator_rail[*]` | `powered_rail` | `27:0` | curved shapes collapse to straight |
| `minecraft:air[*]` | `air` | `0:0` |  |
| `minecraft:allium[*]` | `red_flower` | `38:0` |  |
| `minecraft:amethyst_block[*]` | `obsidian` | `49:0` |  |
| `minecraft:amethyst_cluster[*]` | `obsidian` | `49:0` |  |
| `minecraft:ancient_debris[*]` | `stone` | `1:0` | fallback |
| `minecraft:andesite[*]` | `stone` | `1:0` | fallback |
| `minecraft:andesite_slab[type=bottom,*]` | `stone_slab` | `44:0` |  |
| `minecraft:andesite_slab[type=top,*]` | `stone_slab` | `44:8` |  |
| `minecraft:andesite_slab[type=double,*]` | `stone_slab` | `43:0` | double slab |
| `minecraft:andesite_slab[*]` | `stone_slab` | `44:0` |  |
| `minecraft:andesite_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:andesite_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:andesite_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:andesite_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:andesite_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:andesite_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:andesite_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:andesite_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:andesite_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:andesite_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:anvil[facing=north,*]` | `anvil` | `145:0` | anvil orientation/damage |
| `minecraft:anvil[facing=south,*]` | `anvil` | `145:0` | anvil orientation/damage |
| `minecraft:anvil[facing=west,*]` | `anvil` | `145:1` | anvil orientation/damage |
| `minecraft:anvil[facing=east,*]` | `anvil` | `145:1` | anvil orientation/damage |
| `minecraft:anvil[*]` | `anvil` | `145:0` |  |
| `minecraft:attached_melon_stem[*]` | `melon_block` | `103:0` |  |
| `minecraft:attached_pumpkin_stem[*]` | `stone` | `1:0` | fallback |
| `minecraft:azalea[*]` | `stone` | `1:0` | fallback |
| `minecraft:azalea_leaves[*]` | `leaves` | `18:0` |  |
| `minecraft:azure_bluet[*]` | `red_flower` | `38:0` |  |
| `minecraft:bamboo[*]` | `sapling` | `6:2` |  |
| `minecraft:bamboo_block[*]` | `sapling` | `6:2` |  |
| `minecraft:bamboo_button[face=floor,*]` | `wooden_button` | `143:1` |  |
| `minecraft:bamboo_button[face=wall,facing=east,*]` | `wooden_button` | `143:2` |  |
| `minecraft:bamboo_button[face=wall,facing=west,*]` | `wooden_button` | `143:1` |  |
| `minecraft:bamboo_button[face=wall,facing=south,*]` | `wooden_button` | `143:3` |  |
| `minecraft:bamboo_button[face=wall,facing=north,*]` | `wooden_button` | `143:4` |  |
| `minecraft:bamboo_button[powered=true,*]` | `wooden_button` | `143:9` | powered bit approximated (+8) |
| `minecraft:bamboo_button[*]` | `wooden_button` | `143:1` |  |
| `minecraft:bamboo_door[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:bamboo_door[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:bamboo_door[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:bamboo_door[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:bamboo_door[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:bamboo_door[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:bamboo_door[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:bamboo_door[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:bamboo_door[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:bamboo_door[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:bamboo_door[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:bamboo_fence[*]` | `fence` | `85:0` |  |
| `minecraft:bamboo_fence_gate[facing=south,open=false,*]` | `fence_gate` | `107:0` |  |
| `minecraft:bamboo_fence_gate[facing=south,open=true,*]` | `fence_gate` | `107:4` |  |
| `minecraft:bamboo_fence_gate[facing=west,open=false,*]` | `fence_gate` | `107:1` |  |
| `minecraft:bamboo_fence_gate[facing=west,open=true,*]` | `fence_gate` | `107:5` |  |
| `minecraft:bamboo_fence_gate[facing=north,open=false,*]` | `fence_gate` | `107:2` |  |
| `minecraft:bamboo_fence_gate[facing=north,open=true,*]` | `fence_gate` | `107:6` |  |
| `minecraft:bamboo_fence_gate[facing=east,open=false,*]` | `fence_gate` | `107:3` |  |
| `minecraft:bamboo_fence_gate[facing=east,open=true,*]` | `fence_gate` | `107:7` |  |
| `minecraft:bamboo_fence_gate[*]` | `fence_gate` | `107:0` |  |
| `minecraft:bamboo_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:bamboo_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:bamboo_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:bamboo_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:bamboo_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:bamboo_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:bamboo_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:bamboo_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:bamboo_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:bamboo_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:bamboo_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:bamboo_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:bamboo_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:bamboo_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:bamboo_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:bamboo_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:bamboo_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:bamboo_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:bamboo_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:bamboo_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:bamboo_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:bamboo_mosaic[*]` | `sapling` | `6:2` |  |
| `minecraft:bamboo_mosaic_slab[type=bottom,*]` | `wooden_slab` | `126:2` |  |
| `minecraft:bamboo_mosaic_slab[type=top,*]` | `wooden_slab` | `126:10` |  |
| `minecraft:bamboo_mosaic_slab[type=double,*]` | `wooden_slab` | `125:2` | double slab |
| `minecraft:bamboo_mosaic_slab[*]` | `wooden_slab` | `126:2` |  |
| `minecraft:bamboo_mosaic_stairs[facing=east,half=bottom,*]` | `birch_stairs` | `135:0` |  |
| `minecraft:bamboo_mosaic_stairs[facing=east,half=top,*]` | `birch_stairs` | `135:4` |  |
| `minecraft:bamboo_mosaic_stairs[facing=west,half=bottom,*]` | `birch_stairs` | `135:1` |  |
| `minecraft:bamboo_mosaic_stairs[facing=west,half=top,*]` | `birch_stairs` | `135:5` |  |
| `minecraft:bamboo_mosaic_stairs[facing=south,half=bottom,*]` | `birch_stairs` | `135:2` |  |
| `minecraft:bamboo_mosaic_stairs[facing=south,half=top,*]` | `birch_stairs` | `135:6` |  |
| `minecraft:bamboo_mosaic_stairs[facing=north,half=bottom,*]` | `birch_stairs` | `135:3` |  |
| `minecraft:bamboo_mosaic_stairs[facing=north,half=top,*]` | `birch_stairs` | `135:7` |  |
| `minecraft:bamboo_mosaic_stairs[*]` | `birch_stairs` | `135:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:bamboo_planks[*]` | `planks` | `5:2` |  |
| `minecraft:bamboo_pressure_plate[*]` | `wooden_pressure_plate` | `72:0` |  |
| `minecraft:bamboo_sapling[*]` | `sapling` | `6:2` |  |
| `minecraft:bamboo_shelf[*]` | `sapling` | `6:2` |  |
| `minecraft:bamboo_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:bamboo_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:bamboo_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:bamboo_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:bamboo_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:bamboo_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:bamboo_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:bamboo_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:bamboo_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:bamboo_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:bamboo_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:bamboo_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:bamboo_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:bamboo_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:bamboo_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:bamboo_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:bamboo_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:bamboo_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:bamboo_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:bamboo_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:bamboo_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:bamboo_slab[type=bottom,*]` | `wooden_slab` | `126:2` |  |
| `minecraft:bamboo_slab[type=top,*]` | `wooden_slab` | `126:10` |  |
| `minecraft:bamboo_slab[type=double,*]` | `wooden_slab` | `125:2` | double slab |
| `minecraft:bamboo_slab[*]` | `wooden_slab` | `126:2` |  |
| `minecraft:bamboo_stairs[facing=east,half=bottom,*]` | `birch_stairs` | `135:0` |  |
| `minecraft:bamboo_stairs[facing=east,half=top,*]` | `birch_stairs` | `135:4` |  |
| `minecraft:bamboo_stairs[facing=west,half=bottom,*]` | `birch_stairs` | `135:1` |  |
| `minecraft:bamboo_stairs[facing=west,half=top,*]` | `birch_stairs` | `135:5` |  |
| `minecraft:bamboo_stairs[facing=south,half=bottom,*]` | `birch_stairs` | `135:2` |  |
| `minecraft:bamboo_stairs[facing=south,half=top,*]` | `birch_stairs` | `135:6` |  |
| `minecraft:bamboo_stairs[facing=north,half=bottom,*]` | `birch_stairs` | `135:3` |  |
| `minecraft:bamboo_stairs[facing=north,half=top,*]` | `birch_stairs` | `135:7` |  |
| `minecraft:bamboo_stairs[*]` | `birch_stairs` | `135:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:bamboo_trapdoor[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:bamboo_trapdoor[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:bamboo_trapdoor[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:bamboo_trapdoor[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:bamboo_trapdoor[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:bamboo_trapdoor[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:bamboo_trapdoor[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:bamboo_trapdoor[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:bamboo_trapdoor[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:bamboo_trapdoor[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:bamboo_trapdoor[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:bamboo_wall_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:bamboo_wall_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:bamboo_wall_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:bamboo_wall_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:bamboo_wall_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:bamboo_wall_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:bamboo_wall_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:bamboo_wall_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:bamboo_wall_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:bamboo_wall_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:bamboo_wall_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:bamboo_wall_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:bamboo_wall_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:bamboo_wall_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:bamboo_wall_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:bamboo_wall_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:bamboo_wall_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:bamboo_wall_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:bamboo_wall_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:bamboo_wall_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:bamboo_wall_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:bamboo_wall_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:bamboo_wall_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:bamboo_wall_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:bamboo_wall_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:bamboo_wall_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:bamboo_wall_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:bamboo_wall_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:bamboo_wall_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:bamboo_wall_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:bamboo_wall_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:bamboo_wall_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:bamboo_wall_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:bamboo_wall_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:bamboo_wall_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:bamboo_wall_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:bamboo_wall_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:bamboo_wall_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:bamboo_wall_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:bamboo_wall_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:bamboo_wall_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:bamboo_wall_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:barrel[facing=north,*]` | `chest` | `54:2` |  |
| `minecraft:barrel[facing=south,*]` | `chest` | `54:3` |  |
| `minecraft:barrel[facing=west,*]` | `chest` | `54:4` |  |
| `minecraft:barrel[facing=east,*]` | `chest` | `54:5` |  |
| `minecraft:barrel[*]` | `chest` | `54:2` |  |
| `minecraft:barrier[*]` | `glass` | `20:0` |  |
| `minecraft:basalt[*]` | `stone` | `1:0` |  |
| `minecraft:beacon[*]` | `beacon` | `138:0` |  |
| `minecraft:bedrock[*]` | `stone` | `1:0` | fallback |
| `minecraft:bee_nest[*]` | `chest` | `54:0` |  |
| `minecraft:beehive[*]` | `chest` | `54:0` |  |
| `minecraft:beetroots[age=0,*]` | `carrots` | `141:0` | beetroot collapsed to carrots |
| `minecraft:beetroots[age=1,*]` | `carrots` | `141:1` | beetroot collapsed to carrots |
| `minecraft:beetroots[age=2,*]` | `carrots` | `141:2` | beetroot collapsed to carrots |
| `minecraft:beetroots[age=3,*]` | `carrots` | `141:3` | beetroot collapsed to carrots |
| `minecraft:beetroots[age=4,*]` | `carrots` | `141:4` | beetroot collapsed to carrots |
| `minecraft:beetroots[age=5,*]` | `carrots` | `141:5` | beetroot collapsed to carrots |
| `minecraft:beetroots[age=6,*]` | `carrots` | `141:6` | beetroot collapsed to carrots |
| `minecraft:beetroots[age=7,*]` | `carrots` | `141:7` | beetroot collapsed to carrots |
| `minecraft:beetroots[*]` | `carrots` | `141:0` | beetroot collapsed to carrots |
| `minecraft:bell[*]` | `gold_block` | `41:0` |  |
| `minecraft:big_dripleaf[*]` | `stone` | `1:0` | fallback |
| `minecraft:big_dripleaf_stem[*]` | `stone` | `1:0` | fallback |
| `minecraft:birch_button[face=floor,*]` | `wooden_button` | `143:1` |  |
| `minecraft:birch_button[face=wall,facing=east,*]` | `wooden_button` | `143:2` |  |
| `minecraft:birch_button[face=wall,facing=west,*]` | `wooden_button` | `143:1` |  |
| `minecraft:birch_button[face=wall,facing=south,*]` | `wooden_button` | `143:3` |  |
| `minecraft:birch_button[face=wall,facing=north,*]` | `wooden_button` | `143:4` |  |
| `minecraft:birch_button[powered=true,*]` | `wooden_button` | `143:9` | powered bit approximated (+8) |
| `minecraft:birch_button[*]` | `wooden_button` | `143:1` |  |
| `minecraft:birch_door[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:birch_door[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:birch_door[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:birch_door[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:birch_door[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:birch_door[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:birch_door[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:birch_door[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:birch_door[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:birch_door[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:birch_door[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:birch_fence[*]` | `fence` | `85:0` |  |
| `minecraft:birch_fence_gate[facing=south,open=false,*]` | `fence_gate` | `107:0` |  |
| `minecraft:birch_fence_gate[facing=south,open=true,*]` | `fence_gate` | `107:4` |  |
| `minecraft:birch_fence_gate[facing=west,open=false,*]` | `fence_gate` | `107:1` |  |
| `minecraft:birch_fence_gate[facing=west,open=true,*]` | `fence_gate` | `107:5` |  |
| `minecraft:birch_fence_gate[facing=north,open=false,*]` | `fence_gate` | `107:2` |  |
| `minecraft:birch_fence_gate[facing=north,open=true,*]` | `fence_gate` | `107:6` |  |
| `minecraft:birch_fence_gate[facing=east,open=false,*]` | `fence_gate` | `107:3` |  |
| `minecraft:birch_fence_gate[facing=east,open=true,*]` | `fence_gate` | `107:7` |  |
| `minecraft:birch_fence_gate[*]` | `fence_gate` | `107:0` |  |
| `minecraft:birch_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:birch_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:birch_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:birch_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:birch_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:birch_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:birch_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:birch_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:birch_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:birch_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:birch_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:birch_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:birch_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:birch_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:birch_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:birch_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:birch_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:birch_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:birch_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:birch_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:birch_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:birch_leaves[*]` | `leaves` | `18:2` |  |
| `minecraft:birch_log[axis=y,*]` | `log` | `17:2` |  |
| `minecraft:birch_log[axis=x,*]` | `log` | `17:6` |  |
| `minecraft:birch_log[axis=z,*]` | `log` | `17:10` |  |
| `minecraft:birch_log[*]` | `log` | `17:2` |  |
| `minecraft:birch_planks[*]` | `planks` | `5:2` |  |
| `minecraft:birch_pressure_plate[*]` | `wooden_pressure_plate` | `72:0` |  |
| `minecraft:birch_sapling[*]` | `sapling` | `6:2` |  |
| `minecraft:birch_shelf[*]` | `stone` | `1:0` | fallback |
| `minecraft:birch_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:birch_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:birch_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:birch_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:birch_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:birch_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:birch_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:birch_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:birch_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:birch_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:birch_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:birch_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:birch_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:birch_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:birch_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:birch_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:birch_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:birch_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:birch_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:birch_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:birch_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:birch_slab[type=bottom,*]` | `wooden_slab` | `126:2` |  |
| `minecraft:birch_slab[type=top,*]` | `wooden_slab` | `126:10` |  |
| `minecraft:birch_slab[type=double,*]` | `wooden_slab` | `125:2` | double slab |
| `minecraft:birch_slab[*]` | `wooden_slab` | `126:2` |  |
| `minecraft:birch_stairs[facing=east,half=bottom,*]` | `birch_stairs` | `135:0` |  |
| `minecraft:birch_stairs[facing=east,half=top,*]` | `birch_stairs` | `135:4` |  |
| `minecraft:birch_stairs[facing=west,half=bottom,*]` | `birch_stairs` | `135:1` |  |
| `minecraft:birch_stairs[facing=west,half=top,*]` | `birch_stairs` | `135:5` |  |
| `minecraft:birch_stairs[facing=south,half=bottom,*]` | `birch_stairs` | `135:2` |  |
| `minecraft:birch_stairs[facing=south,half=top,*]` | `birch_stairs` | `135:6` |  |
| `minecraft:birch_stairs[facing=north,half=bottom,*]` | `birch_stairs` | `135:3` |  |
| `minecraft:birch_stairs[facing=north,half=top,*]` | `birch_stairs` | `135:7` |  |
| `minecraft:birch_stairs[*]` | `birch_stairs` | `135:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:birch_trapdoor[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:birch_trapdoor[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:birch_trapdoor[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:birch_trapdoor[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:birch_trapdoor[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:birch_trapdoor[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:birch_trapdoor[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:birch_trapdoor[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:birch_trapdoor[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:birch_trapdoor[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:birch_trapdoor[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:birch_wall_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:birch_wall_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:birch_wall_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:birch_wall_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:birch_wall_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:birch_wall_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:birch_wall_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:birch_wall_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:birch_wall_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:birch_wall_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:birch_wall_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:birch_wall_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:birch_wall_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:birch_wall_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:birch_wall_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:birch_wall_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:birch_wall_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:birch_wall_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:birch_wall_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:birch_wall_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:birch_wall_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:birch_wall_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:birch_wall_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:birch_wall_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:birch_wall_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:birch_wall_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:birch_wall_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:birch_wall_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:birch_wall_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:birch_wall_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:birch_wall_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:birch_wall_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:birch_wall_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:birch_wall_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:birch_wall_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:birch_wall_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:birch_wall_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:birch_wall_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:birch_wall_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:birch_wall_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:birch_wall_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:birch_wall_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:birch_wood[axis=y,*]` | `log` | `17:2` |  |
| `minecraft:birch_wood[axis=x,*]` | `log` | `17:6` |  |
| `minecraft:birch_wood[axis=z,*]` | `log` | `17:10` |  |
| `minecraft:birch_wood[*]` | `log` | `17:2` |  |
| `minecraft:black_banner[*]` | `wool` | `35:15` | banner collapsed to wool |
| `minecraft:black_bed[part=foot,facing=south,occupied=false,*]` | `bed` | `26:0` | bed color ignored |
| `minecraft:black_bed[part=head,facing=south,occupied=false,*]` | `bed` | `26:8` | bed color ignored |
| `minecraft:black_bed[part=foot,facing=south,occupied=true,*]` | `bed` | `26:4` | occupied bit; color ignored |
| `minecraft:black_bed[part=head,facing=south,occupied=true,*]` | `bed` | `26:12` | occupied+head bits; color ignored |
| `minecraft:black_bed[part=foot,facing=west,occupied=false,*]` | `bed` | `26:1` | bed color ignored |
| `minecraft:black_bed[part=head,facing=west,occupied=false,*]` | `bed` | `26:9` | bed color ignored |
| `minecraft:black_bed[part=foot,facing=west,occupied=true,*]` | `bed` | `26:5` | occupied bit; color ignored |
| `minecraft:black_bed[part=head,facing=west,occupied=true,*]` | `bed` | `26:13` | occupied+head bits; color ignored |
| `minecraft:black_bed[part=foot,facing=north,occupied=false,*]` | `bed` | `26:2` | bed color ignored |
| `minecraft:black_bed[part=head,facing=north,occupied=false,*]` | `bed` | `26:10` | bed color ignored |
| `minecraft:black_bed[part=foot,facing=north,occupied=true,*]` | `bed` | `26:6` | occupied bit; color ignored |
| `minecraft:black_bed[part=head,facing=north,occupied=true,*]` | `bed` | `26:14` | occupied+head bits; color ignored |
| `minecraft:black_bed[part=foot,facing=east,occupied=false,*]` | `bed` | `26:3` | bed color ignored |
| `minecraft:black_bed[part=head,facing=east,occupied=false,*]` | `bed` | `26:11` | bed color ignored |
| `minecraft:black_bed[part=foot,facing=east,occupied=true,*]` | `bed` | `26:7` | occupied bit; color ignored |
| `minecraft:black_bed[part=head,facing=east,occupied=true,*]` | `bed` | `26:15` | occupied+head bits; color ignored |
| `minecraft:black_bed[*]` | `bed` | `26:0` | legacy bed ignores color |
| `minecraft:black_candle[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:black_candle_cake[bites=0,*]` | `cake` | `92:0` |  |
| `minecraft:black_candle_cake[bites=1,*]` | `cake` | `92:1` |  |
| `minecraft:black_candle_cake[bites=2,*]` | `cake` | `92:2` |  |
| `minecraft:black_candle_cake[bites=3,*]` | `cake` | `92:3` |  |
| `minecraft:black_candle_cake[bites=4,*]` | `cake` | `92:4` |  |
| `minecraft:black_candle_cake[bites=5,*]` | `cake` | `92:5` |  |
| `minecraft:black_candle_cake[bites=6,*]` | `cake` | `92:6` |  |
| `minecraft:black_candle_cake[*]` | `cake` | `92:0` |  |
| `minecraft:black_carpet[*]` | `carpet` | `171:15` |  |
| `minecraft:black_concrete[*]` | `stained_hardened_clay` | `159:15` |  |
| `minecraft:black_concrete_powder[*]` | `stained_hardened_clay` | `159:15` |  |
| `minecraft:black_glazed_terracotta[*]` | `stained_hardened_clay` | `159:15` |  |
| `minecraft:black_shulker_box[*]` | `wool` | `35:15` | shulker box collapsed to wool |
| `minecraft:black_stained_glass[*]` | `stained_glass` | `95:15` |  |
| `minecraft:black_stained_glass_pane[*]` | `stained_glass_pane` | `160:15` |  |
| `minecraft:black_terracotta[*]` | `stained_hardened_clay` | `159:15` |  |
| `minecraft:black_wall_banner[*]` | `wool` | `35:15` | banner collapsed to wool |
| `minecraft:black_wool[*]` | `wool` | `35:15` |  |
| `minecraft:blackstone[*]` | `cobblestone` | `4:0` |  |
| `minecraft:blackstone_slab[type=bottom,*]` | `stone_slab` | `44:6` |  |
| `minecraft:blackstone_slab[type=top,*]` | `stone_slab` | `44:14` |  |
| `minecraft:blackstone_slab[type=double,*]` | `stone_slab` | `43:6` | double slab |
| `minecraft:blackstone_slab[*]` | `stone_slab` | `44:6` |  |
| `minecraft:blackstone_stairs[facing=east,half=bottom,*]` | `nether_brick_stairs` | `114:0` |  |
| `minecraft:blackstone_stairs[facing=east,half=top,*]` | `nether_brick_stairs` | `114:4` |  |
| `minecraft:blackstone_stairs[facing=west,half=bottom,*]` | `nether_brick_stairs` | `114:1` |  |
| `minecraft:blackstone_stairs[facing=west,half=top,*]` | `nether_brick_stairs` | `114:5` |  |
| `minecraft:blackstone_stairs[facing=south,half=bottom,*]` | `nether_brick_stairs` | `114:2` |  |
| `minecraft:blackstone_stairs[facing=south,half=top,*]` | `nether_brick_stairs` | `114:6` |  |
| `minecraft:blackstone_stairs[facing=north,half=bottom,*]` | `nether_brick_stairs` | `114:3` |  |
| `minecraft:blackstone_stairs[facing=north,half=top,*]` | `nether_brick_stairs` | `114:7` |  |
| `minecraft:blackstone_stairs[*]` | `nether_brick_stairs` | `114:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:blackstone_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:blast_furnace[lit=false,facing=north,*]` | `furnace` | `61:2` | furnace |
| `minecraft:blast_furnace[lit=true,facing=north,*]` | `furnace` | `62:2` | lit furnace |
| `minecraft:blast_furnace[lit=false,facing=south,*]` | `furnace` | `61:3` | furnace |
| `minecraft:blast_furnace[lit=true,facing=south,*]` | `furnace` | `62:3` | lit furnace |
| `minecraft:blast_furnace[lit=false,facing=west,*]` | `furnace` | `61:4` | furnace |
| `minecraft:blast_furnace[lit=true,facing=west,*]` | `furnace` | `62:4` | lit furnace |
| `minecraft:blast_furnace[lit=false,facing=east,*]` | `furnace` | `61:5` | furnace |
| `minecraft:blast_furnace[lit=true,facing=east,*]` | `furnace` | `62:5` | lit furnace |
| `minecraft:blast_furnace[*]` | `furnace` | `61:2` | defaults north-facing |
| `minecraft:blue_banner[*]` | `wool` | `35:11` | banner collapsed to wool |
| `minecraft:blue_bed[part=foot,facing=south,occupied=false,*]` | `bed` | `26:0` | bed color ignored |
| `minecraft:blue_bed[part=head,facing=south,occupied=false,*]` | `bed` | `26:8` | bed color ignored |
| `minecraft:blue_bed[part=foot,facing=south,occupied=true,*]` | `bed` | `26:4` | occupied bit; color ignored |
| `minecraft:blue_bed[part=head,facing=south,occupied=true,*]` | `bed` | `26:12` | occupied+head bits; color ignored |
| `minecraft:blue_bed[part=foot,facing=west,occupied=false,*]` | `bed` | `26:1` | bed color ignored |
| `minecraft:blue_bed[part=head,facing=west,occupied=false,*]` | `bed` | `26:9` | bed color ignored |
| `minecraft:blue_bed[part=foot,facing=west,occupied=true,*]` | `bed` | `26:5` | occupied bit; color ignored |
| `minecraft:blue_bed[part=head,facing=west,occupied=true,*]` | `bed` | `26:13` | occupied+head bits; color ignored |
| `minecraft:blue_bed[part=foot,facing=north,occupied=false,*]` | `bed` | `26:2` | bed color ignored |
| `minecraft:blue_bed[part=head,facing=north,occupied=false,*]` | `bed` | `26:10` | bed color ignored |
| `minecraft:blue_bed[part=foot,facing=north,occupied=true,*]` | `bed` | `26:6` | occupied bit; color ignored |
| `minecraft:blue_bed[part=head,facing=north,occupied=true,*]` | `bed` | `26:14` | occupied+head bits; color ignored |
| `minecraft:blue_bed[part=foot,facing=east,occupied=false,*]` | `bed` | `26:3` | bed color ignored |
| `minecraft:blue_bed[part=head,facing=east,occupied=false,*]` | `bed` | `26:11` | bed color ignored |
| `minecraft:blue_bed[part=foot,facing=east,occupied=true,*]` | `bed` | `26:7` | occupied bit; color ignored |
| `minecraft:blue_bed[part=head,facing=east,occupied=true,*]` | `bed` | `26:15` | occupied+head bits; color ignored |
| `minecraft:blue_bed[*]` | `bed` | `26:0` | legacy bed ignores color |
| `minecraft:blue_candle[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:blue_candle_cake[bites=0,*]` | `cake` | `92:0` |  |
| `minecraft:blue_candle_cake[bites=1,*]` | `cake` | `92:1` |  |
| `minecraft:blue_candle_cake[bites=2,*]` | `cake` | `92:2` |  |
| `minecraft:blue_candle_cake[bites=3,*]` | `cake` | `92:3` |  |
| `minecraft:blue_candle_cake[bites=4,*]` | `cake` | `92:4` |  |
| `minecraft:blue_candle_cake[bites=5,*]` | `cake` | `92:5` |  |
| `minecraft:blue_candle_cake[bites=6,*]` | `cake` | `92:6` |  |
| `minecraft:blue_candle_cake[*]` | `cake` | `92:0` |  |
| `minecraft:blue_carpet[*]` | `carpet` | `171:11` |  |
| `minecraft:blue_concrete[*]` | `stained_hardened_clay` | `159:11` |  |
| `minecraft:blue_concrete_powder[*]` | `stained_hardened_clay` | `159:11` |  |
| `minecraft:blue_glazed_terracotta[*]` | `stained_hardened_clay` | `159:11` |  |
| `minecraft:blue_ice[*]` | `packed_ice` | `174:0` |  |
| `minecraft:blue_orchid[*]` | `red_flower` | `38:0` |  |
| `minecraft:blue_shulker_box[*]` | `wool` | `35:11` | shulker box collapsed to wool |
| `minecraft:blue_stained_glass[*]` | `stained_glass` | `95:11` |  |
| `minecraft:blue_stained_glass_pane[*]` | `stained_glass_pane` | `160:11` |  |
| `minecraft:blue_terracotta[*]` | `stained_hardened_clay` | `159:11` |  |
| `minecraft:blue_wall_banner[*]` | `wool` | `35:11` | banner collapsed to wool |
| `minecraft:blue_wool[*]` | `wool` | `35:11` |  |
| `minecraft:bone_block[*]` | `stone` | `1:0` | fallback |
| `minecraft:bookshelf[*]` | `bookshelf` | `47:0` |  |
| `minecraft:brain_coral[*]` | `wool` | `35:11` |  |
| `minecraft:brain_coral_block[*]` | `wool` | `35:11` |  |
| `minecraft:brain_coral_fan[*]` | `wool` | `35:11` |  |
| `minecraft:brain_coral_wall_fan[*]` | `wool` | `35:11` |  |
| `minecraft:brewing_stand[*]` | `brewing_stand` | `117:0` |  |
| `minecraft:brick_slab[type=bottom,*]` | `stone_slab` | `44:4` |  |
| `minecraft:brick_slab[type=top,*]` | `stone_slab` | `44:12` |  |
| `minecraft:brick_slab[type=double,*]` | `stone_slab` | `43:4` | double slab |
| `minecraft:brick_slab[*]` | `stone_slab` | `44:4` |  |
| `minecraft:brick_stairs[facing=east,half=bottom,*]` | `brick_stairs` | `108:0` |  |
| `minecraft:brick_stairs[facing=east,half=top,*]` | `brick_stairs` | `108:4` |  |
| `minecraft:brick_stairs[facing=west,half=bottom,*]` | `brick_stairs` | `108:1` |  |
| `minecraft:brick_stairs[facing=west,half=top,*]` | `brick_stairs` | `108:5` |  |
| `minecraft:brick_stairs[facing=south,half=bottom,*]` | `brick_stairs` | `108:2` |  |
| `minecraft:brick_stairs[facing=south,half=top,*]` | `brick_stairs` | `108:6` |  |
| `minecraft:brick_stairs[facing=north,half=bottom,*]` | `brick_stairs` | `108:3` |  |
| `minecraft:brick_stairs[facing=north,half=top,*]` | `brick_stairs` | `108:7` |  |
| `minecraft:brick_stairs[*]` | `brick_stairs` | `108:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:brick_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:bricks[*]` | `brick_block` | `45:0` |  |
| `minecraft:brown_banner[*]` | `wool` | `35:12` | banner collapsed to wool |
| `minecraft:brown_bed[part=foot,facing=south,occupied=false,*]` | `bed` | `26:0` | bed color ignored |
| `minecraft:brown_bed[part=head,facing=south,occupied=false,*]` | `bed` | `26:8` | bed color ignored |
| `minecraft:brown_bed[part=foot,facing=south,occupied=true,*]` | `bed` | `26:4` | occupied bit; color ignored |
| `minecraft:brown_bed[part=head,facing=south,occupied=true,*]` | `bed` | `26:12` | occupied+head bits; color ignored |
| `minecraft:brown_bed[part=foot,facing=west,occupied=false,*]` | `bed` | `26:1` | bed color ignored |
| `minecraft:brown_bed[part=head,facing=west,occupied=false,*]` | `bed` | `26:9` | bed color ignored |
| `minecraft:brown_bed[part=foot,facing=west,occupied=true,*]` | `bed` | `26:5` | occupied bit; color ignored |
| `minecraft:brown_bed[part=head,facing=west,occupied=true,*]` | `bed` | `26:13` | occupied+head bits; color ignored |
| `minecraft:brown_bed[part=foot,facing=north,occupied=false,*]` | `bed` | `26:2` | bed color ignored |
| `minecraft:brown_bed[part=head,facing=north,occupied=false,*]` | `bed` | `26:10` | bed color ignored |
| `minecraft:brown_bed[part=foot,facing=north,occupied=true,*]` | `bed` | `26:6` | occupied bit; color ignored |
| `minecraft:brown_bed[part=head,facing=north,occupied=true,*]` | `bed` | `26:14` | occupied+head bits; color ignored |
| `minecraft:brown_bed[part=foot,facing=east,occupied=false,*]` | `bed` | `26:3` | bed color ignored |
| `minecraft:brown_bed[part=head,facing=east,occupied=false,*]` | `bed` | `26:11` | bed color ignored |
| `minecraft:brown_bed[part=foot,facing=east,occupied=true,*]` | `bed` | `26:7` | occupied bit; color ignored |
| `minecraft:brown_bed[part=head,facing=east,occupied=true,*]` | `bed` | `26:15` | occupied+head bits; color ignored |
| `minecraft:brown_bed[*]` | `bed` | `26:0` | legacy bed ignores color |
| `minecraft:brown_candle[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:brown_candle_cake[bites=0,*]` | `cake` | `92:0` |  |
| `minecraft:brown_candle_cake[bites=1,*]` | `cake` | `92:1` |  |
| `minecraft:brown_candle_cake[bites=2,*]` | `cake` | `92:2` |  |
| `minecraft:brown_candle_cake[bites=3,*]` | `cake` | `92:3` |  |
| `minecraft:brown_candle_cake[bites=4,*]` | `cake` | `92:4` |  |
| `minecraft:brown_candle_cake[bites=5,*]` | `cake` | `92:5` |  |
| `minecraft:brown_candle_cake[bites=6,*]` | `cake` | `92:6` |  |
| `minecraft:brown_candle_cake[*]` | `cake` | `92:0` |  |
| `minecraft:brown_carpet[*]` | `carpet` | `171:12` |  |
| `minecraft:brown_concrete[*]` | `stained_hardened_clay` | `159:12` |  |
| `minecraft:brown_concrete_powder[*]` | `stained_hardened_clay` | `159:12` |  |
| `minecraft:brown_glazed_terracotta[*]` | `stained_hardened_clay` | `159:12` |  |
| `minecraft:brown_mushroom[*]` | `brown_mushroom` | `39:0` |  |
| `minecraft:brown_mushroom_block[*]` | `brown_mushroom_block` | `99:0` |  |
| `minecraft:brown_shulker_box[*]` | `wool` | `35:12` | shulker box collapsed to wool |
| `minecraft:brown_stained_glass[*]` | `stained_glass` | `95:12` |  |
| `minecraft:brown_stained_glass_pane[*]` | `stained_glass_pane` | `160:12` |  |
| `minecraft:brown_terracotta[*]` | `stained_hardened_clay` | `159:12` |  |
| `minecraft:brown_wall_banner[*]` | `wool` | `35:12` | banner collapsed to wool |
| `minecraft:brown_wool[*]` | `wool` | `35:12` |  |
| `minecraft:bubble_column[*]` | `stone` | `1:0` | fallback |
| `minecraft:bubble_coral[*]` | `wool` | `35:11` |  |
| `minecraft:bubble_coral_block[*]` | `wool` | `35:11` |  |
| `minecraft:bubble_coral_fan[*]` | `wool` | `35:11` |  |
| `minecraft:bubble_coral_wall_fan[*]` | `wool` | `35:11` |  |
| `minecraft:budding_amethyst[*]` | `obsidian` | `49:0` |  |
| `minecraft:bush[*]` | `stone` | `1:0` | fallback |
| `minecraft:cactus[*]` | `cactus` | `81:0` |  |
| `minecraft:cactus_flower[*]` | `red_flower` | `38:0` |  |
| `minecraft:cake[bites=0,*]` | `cake` | `92:0` |  |
| `minecraft:cake[bites=1,*]` | `cake` | `92:1` |  |
| `minecraft:cake[bites=2,*]` | `cake` | `92:2` |  |
| `minecraft:cake[bites=3,*]` | `cake` | `92:3` |  |
| `minecraft:cake[bites=4,*]` | `cake` | `92:4` |  |
| `minecraft:cake[bites=5,*]` | `cake` | `92:5` |  |
| `minecraft:cake[bites=6,*]` | `cake` | `92:6` |  |
| `minecraft:cake[*]` | `cake` | `92:0` |  |
| `minecraft:calcite[*]` | `stone` | `1:0` |  |
| `minecraft:calibrated_sculk_sensor[*]` | `obsidian` | `49:0` |  |
| `minecraft:campfire[*]` | `netherrack` | `87:0` |  |
| `minecraft:candle[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:candle_cake[bites=0,*]` | `cake` | `92:0` |  |
| `minecraft:candle_cake[bites=1,*]` | `cake` | `92:1` |  |
| `minecraft:candle_cake[bites=2,*]` | `cake` | `92:2` |  |
| `minecraft:candle_cake[bites=3,*]` | `cake` | `92:3` |  |
| `minecraft:candle_cake[bites=4,*]` | `cake` | `92:4` |  |
| `minecraft:candle_cake[bites=5,*]` | `cake` | `92:5` |  |
| `minecraft:candle_cake[bites=6,*]` | `cake` | `92:6` |  |
| `minecraft:candle_cake[*]` | `cake` | `92:0` |  |
| `minecraft:carrots[age=0,*]` | `carrots` | `141:0` |  |
| `minecraft:carrots[age=1,*]` | `carrots` | `141:1` |  |
| `minecraft:carrots[age=2,*]` | `carrots` | `141:2` |  |
| `minecraft:carrots[age=3,*]` | `carrots` | `141:3` |  |
| `minecraft:carrots[age=4,*]` | `carrots` | `141:4` |  |
| `minecraft:carrots[age=5,*]` | `carrots` | `141:5` |  |
| `minecraft:carrots[age=6,*]` | `carrots` | `141:6` |  |
| `minecraft:carrots[age=7,*]` | `carrots` | `141:7` |  |
| `minecraft:carrots[*]` | `carrots` | `141:0` |  |
| `minecraft:cartography_table[*]` | `crafting_table` | `58:0` |  |
| `minecraft:carved_pumpkin[facing=north,*]` | `pumpkin` | `86:2` |  |
| `minecraft:carved_pumpkin[facing=south,*]` | `pumpkin` | `86:3` |  |
| `minecraft:carved_pumpkin[facing=west,*]` | `pumpkin` | `86:4` |  |
| `minecraft:carved_pumpkin[facing=east,*]` | `pumpkin` | `86:5` |  |
| `minecraft:carved_pumpkin[*]` | `pumpkin` | `86:2` |  |
| `minecraft:cauldron[level=0,*]` | `cauldron` | `118:0` |  |
| `minecraft:cauldron[level=1,*]` | `cauldron` | `118:1` |  |
| `minecraft:cauldron[level=2,*]` | `cauldron` | `118:2` |  |
| `minecraft:cauldron[level=3,*]` | `cauldron` | `118:3` |  |
| `minecraft:cauldron[*]` | `cauldron` | `118:0` | lava/powder-snow cauldrons collapse to cauldron levels |
| `minecraft:cave_air[*]` | `air` | `0:0` |  |
| `minecraft:cave_vines[*]` | `stone` | `1:0` | fallback |
| `minecraft:cave_vines_plant[*]` | `stone` | `1:0` | fallback |
| `minecraft:chain_command_block[facing=down,*]` | `dispenser` | `23:0` | modern logic block collapsed to dispenser |
| `minecraft:chain_command_block[facing=up,*]` | `dispenser` | `23:1` | modern logic block collapsed to dispenser |
| `minecraft:chain_command_block[facing=north,*]` | `dispenser` | `23:2` | modern logic block collapsed to dispenser |
| `minecraft:chain_command_block[facing=south,*]` | `dispenser` | `23:3` | modern logic block collapsed to dispenser |
| `minecraft:chain_command_block[facing=west,*]` | `dispenser` | `23:4` | modern logic block collapsed to dispenser |
| `minecraft:chain_command_block[facing=east,*]` | `dispenser` | `23:5` | modern logic block collapsed to dispenser |
| `minecraft:chain_command_block[*]` | `dispenser` | `23:2` | modern logic block collapsed to dispenser |
| `minecraft:cherry_button[face=floor,*]` | `wooden_button` | `143:1` |  |
| `minecraft:cherry_button[face=wall,facing=east,*]` | `wooden_button` | `143:2` |  |
| `minecraft:cherry_button[face=wall,facing=west,*]` | `wooden_button` | `143:1` |  |
| `minecraft:cherry_button[face=wall,facing=south,*]` | `wooden_button` | `143:3` |  |
| `minecraft:cherry_button[face=wall,facing=north,*]` | `wooden_button` | `143:4` |  |
| `minecraft:cherry_button[powered=true,*]` | `wooden_button` | `143:9` | powered bit approximated (+8) |
| `minecraft:cherry_button[*]` | `wooden_button` | `143:1` |  |
| `minecraft:cherry_door[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:cherry_door[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:cherry_door[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:cherry_door[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:cherry_door[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:cherry_door[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:cherry_door[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:cherry_door[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:cherry_door[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:cherry_door[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:cherry_door[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:cherry_fence[*]` | `fence` | `85:0` |  |
| `minecraft:cherry_fence_gate[facing=south,open=false,*]` | `fence_gate` | `107:0` |  |
| `minecraft:cherry_fence_gate[facing=south,open=true,*]` | `fence_gate` | `107:4` |  |
| `minecraft:cherry_fence_gate[facing=west,open=false,*]` | `fence_gate` | `107:1` |  |
| `minecraft:cherry_fence_gate[facing=west,open=true,*]` | `fence_gate` | `107:5` |  |
| `minecraft:cherry_fence_gate[facing=north,open=false,*]` | `fence_gate` | `107:2` |  |
| `minecraft:cherry_fence_gate[facing=north,open=true,*]` | `fence_gate` | `107:6` |  |
| `minecraft:cherry_fence_gate[facing=east,open=false,*]` | `fence_gate` | `107:3` |  |
| `minecraft:cherry_fence_gate[facing=east,open=true,*]` | `fence_gate` | `107:7` |  |
| `minecraft:cherry_fence_gate[*]` | `fence_gate` | `107:0` |  |
| `minecraft:cherry_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:cherry_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:cherry_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:cherry_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:cherry_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:cherry_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:cherry_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:cherry_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:cherry_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:cherry_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:cherry_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:cherry_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:cherry_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:cherry_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:cherry_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:cherry_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:cherry_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:cherry_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:cherry_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:cherry_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:cherry_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:cherry_leaves[*]` | `leaves` | `18:2` |  |
| `minecraft:cherry_log[axis=y,*]` | `log` | `17:2` |  |
| `minecraft:cherry_log[axis=x,*]` | `log` | `17:6` |  |
| `minecraft:cherry_log[axis=z,*]` | `log` | `17:10` |  |
| `minecraft:cherry_log[*]` | `log` | `17:2` |  |
| `minecraft:cherry_planks[*]` | `planks` | `5:2` |  |
| `minecraft:cherry_pressure_plate[*]` | `wooden_pressure_plate` | `72:0` |  |
| `minecraft:cherry_sapling[*]` | `sapling` | `6:2` |  |
| `minecraft:cherry_shelf[*]` | `stone` | `1:0` | fallback |
| `minecraft:cherry_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:cherry_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:cherry_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:cherry_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:cherry_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:cherry_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:cherry_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:cherry_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:cherry_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:cherry_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:cherry_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:cherry_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:cherry_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:cherry_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:cherry_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:cherry_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:cherry_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:cherry_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:cherry_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:cherry_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:cherry_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:cherry_slab[type=bottom,*]` | `wooden_slab` | `126:2` |  |
| `minecraft:cherry_slab[type=top,*]` | `wooden_slab` | `126:10` |  |
| `minecraft:cherry_slab[type=double,*]` | `wooden_slab` | `125:2` | double slab |
| `minecraft:cherry_slab[*]` | `wooden_slab` | `126:2` |  |
| `minecraft:cherry_stairs[facing=east,half=bottom,*]` | `birch_stairs` | `135:0` |  |
| `minecraft:cherry_stairs[facing=east,half=top,*]` | `birch_stairs` | `135:4` |  |
| `minecraft:cherry_stairs[facing=west,half=bottom,*]` | `birch_stairs` | `135:1` |  |
| `minecraft:cherry_stairs[facing=west,half=top,*]` | `birch_stairs` | `135:5` |  |
| `minecraft:cherry_stairs[facing=south,half=bottom,*]` | `birch_stairs` | `135:2` |  |
| `minecraft:cherry_stairs[facing=south,half=top,*]` | `birch_stairs` | `135:6` |  |
| `minecraft:cherry_stairs[facing=north,half=bottom,*]` | `birch_stairs` | `135:3` |  |
| `minecraft:cherry_stairs[facing=north,half=top,*]` | `birch_stairs` | `135:7` |  |
| `minecraft:cherry_stairs[*]` | `birch_stairs` | `135:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:cherry_trapdoor[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:cherry_trapdoor[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:cherry_trapdoor[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:cherry_trapdoor[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:cherry_trapdoor[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:cherry_trapdoor[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:cherry_trapdoor[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:cherry_trapdoor[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:cherry_trapdoor[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:cherry_trapdoor[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:cherry_trapdoor[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:cherry_wall_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:cherry_wall_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:cherry_wall_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:cherry_wall_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:cherry_wall_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:cherry_wall_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:cherry_wall_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:cherry_wall_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:cherry_wall_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:cherry_wall_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:cherry_wall_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:cherry_wall_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:cherry_wall_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:cherry_wall_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:cherry_wall_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:cherry_wall_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:cherry_wall_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:cherry_wall_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:cherry_wall_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:cherry_wall_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:cherry_wall_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:cherry_wall_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:cherry_wall_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:cherry_wall_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:cherry_wall_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:cherry_wall_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:cherry_wall_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:cherry_wall_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:cherry_wall_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:cherry_wall_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:cherry_wall_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:cherry_wall_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:cherry_wall_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:cherry_wall_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:cherry_wall_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:cherry_wall_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:cherry_wall_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:cherry_wall_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:cherry_wall_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:cherry_wall_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:cherry_wall_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:cherry_wall_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:cherry_wood[axis=y,*]` | `log` | `17:2` |  |
| `minecraft:cherry_wood[axis=x,*]` | `log` | `17:6` |  |
| `minecraft:cherry_wood[axis=z,*]` | `log` | `17:10` |  |
| `minecraft:cherry_wood[*]` | `log` | `17:2` |  |
| `minecraft:chest[facing=north,*]` | `chest` | `54:2` |  |
| `minecraft:chest[facing=south,*]` | `chest` | `54:3` |  |
| `minecraft:chest[facing=west,*]` | `chest` | `54:4` |  |
| `minecraft:chest[facing=east,*]` | `chest` | `54:5` |  |
| `minecraft:chest[*]` | `chest` | `54:2` |  |
| `minecraft:chipped_anvil[facing=north,*]` | `anvil` | `145:4` | anvil orientation/damage |
| `minecraft:chipped_anvil[facing=south,*]` | `anvil` | `145:4` | anvil orientation/damage |
| `minecraft:chipped_anvil[facing=west,*]` | `anvil` | `145:5` | anvil orientation/damage |
| `minecraft:chipped_anvil[facing=east,*]` | `anvil` | `145:5` | anvil orientation/damage |
| `minecraft:chipped_anvil[*]` | `anvil` | `145:4` |  |
| `minecraft:chiseled_bookshelf[*]` | `bookshelf` | `47:0` |  |
| `minecraft:chiseled_copper[*]` | `iron_block` | `42:0` |  |
| `minecraft:chiseled_deepslate[*]` | `stonebrick` | `98:0` |  |
| `minecraft:chiseled_nether_bricks[*]` | `nether_brick` | `112:0` |  |
| `minecraft:chiseled_polished_blackstone[*]` | `stonebrick` | `98:0` |  |
| `minecraft:chiseled_quartz_block[axis=y,*]` | `quartz_block` | `155:2` | pillar quartz vertical |
| `minecraft:chiseled_quartz_block[axis=x,*]` | `quartz_block` | `155:3` | pillar quartz horizontal |
| `minecraft:chiseled_quartz_block[axis=z,*]` | `quartz_block` | `155:4` | pillar quartz horizontal |
| `minecraft:chiseled_quartz_block[*]` | `quartz_block` | `155:0` | smooth/chiseled collapse to plain quartz block |
| `minecraft:chiseled_red_sandstone[*]` | `sandstone` | `24:0` |  |
| `minecraft:chiseled_resin_bricks[*]` | `stonebrick` | `98:0` |  |
| `minecraft:chiseled_sandstone[*]` | `sandstone` | `24:0` |  |
| `minecraft:chiseled_stone_bricks[*]` | `stonebrick` | `98:0` |  |
| `minecraft:chiseled_tuff[*]` | `stone` | `1:0` |  |
| `minecraft:chiseled_tuff_bricks[*]` | `stonebrick` | `98:0` |  |
| `minecraft:chorus_flower[*]` | `red_flower` | `38:0` |  |
| `minecraft:chorus_plant[*]` | `stone` | `1:0` | fallback |
| `minecraft:clay[*]` | `clay` | `82:0` |  |
| `minecraft:closed_eyeblossom[*]` | `red_flower` | `38:0` |  |
| `minecraft:coal_block[*]` | `coal_block` | `173:0` |  |
| `minecraft:coal_ore[*]` | `coal_ore` | `16:0` |  |
| `minecraft:coarse_dirt[*]` | `dirt` | `3:0` |  |
| `minecraft:cobbled_deepslate[*]` | `cobblestone` | `4:0` |  |
| `minecraft:cobbled_deepslate_slab[type=bottom,*]` | `stone_slab` | `44:3` |  |
| `minecraft:cobbled_deepslate_slab[type=top,*]` | `stone_slab` | `44:11` |  |
| `minecraft:cobbled_deepslate_slab[type=double,*]` | `stone_slab` | `43:3` | double slab |
| `minecraft:cobbled_deepslate_slab[*]` | `stone_slab` | `44:3` |  |
| `minecraft:cobbled_deepslate_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:cobbled_deepslate_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:cobbled_deepslate_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:cobbled_deepslate_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:cobbled_deepslate_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:cobbled_deepslate_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:cobbled_deepslate_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:cobbled_deepslate_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:cobbled_deepslate_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:cobbled_deepslate_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:cobblestone[*]` | `cobblestone` | `4:0` |  |
| `minecraft:cobblestone_slab[type=bottom,*]` | `stone_slab` | `44:3` |  |
| `minecraft:cobblestone_slab[type=top,*]` | `stone_slab` | `44:11` |  |
| `minecraft:cobblestone_slab[type=double,*]` | `stone_slab` | `43:3` | double slab |
| `minecraft:cobblestone_slab[*]` | `stone_slab` | `44:3` |  |
| `minecraft:cobblestone_stairs[facing=east,half=bottom,*]` | `cobblestone_stairs` | `67:0` |  |
| `minecraft:cobblestone_stairs[facing=east,half=top,*]` | `cobblestone_stairs` | `67:4` |  |
| `minecraft:cobblestone_stairs[facing=west,half=bottom,*]` | `cobblestone_stairs` | `67:1` |  |
| `minecraft:cobblestone_stairs[facing=west,half=top,*]` | `cobblestone_stairs` | `67:5` |  |
| `minecraft:cobblestone_stairs[facing=south,half=bottom,*]` | `cobblestone_stairs` | `67:2` |  |
| `minecraft:cobblestone_stairs[facing=south,half=top,*]` | `cobblestone_stairs` | `67:6` |  |
| `minecraft:cobblestone_stairs[facing=north,half=bottom,*]` | `cobblestone_stairs` | `67:3` |  |
| `minecraft:cobblestone_stairs[facing=north,half=top,*]` | `cobblestone_stairs` | `67:7` |  |
| `minecraft:cobblestone_stairs[*]` | `cobblestone_stairs` | `67:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:cobblestone_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:cobweb[*]` | `web` | `30:0` |  |
| `minecraft:cocoa[facing=north,age=0,*]` | `cocoa` | `127:0` |  |
| `minecraft:cocoa[facing=north,age=1,*]` | `cocoa` | `127:4` |  |
| `minecraft:cocoa[facing=north,age=2,*]` | `cocoa` | `127:8` |  |
| `minecraft:cocoa[facing=east,age=0,*]` | `cocoa` | `127:1` |  |
| `minecraft:cocoa[facing=east,age=1,*]` | `cocoa` | `127:5` |  |
| `minecraft:cocoa[facing=east,age=2,*]` | `cocoa` | `127:9` |  |
| `minecraft:cocoa[facing=south,age=0,*]` | `cocoa` | `127:2` |  |
| `minecraft:cocoa[facing=south,age=1,*]` | `cocoa` | `127:6` |  |
| `minecraft:cocoa[facing=south,age=2,*]` | `cocoa` | `127:10` |  |
| `minecraft:cocoa[facing=west,age=0,*]` | `cocoa` | `127:3` |  |
| `minecraft:cocoa[facing=west,age=1,*]` | `cocoa` | `127:7` |  |
| `minecraft:cocoa[facing=west,age=2,*]` | `cocoa` | `127:11` |  |
| `minecraft:cocoa[*]` | `cocoa` | `127:0` | ages above 2 clamp |
| `minecraft:command_block[facing=down,*]` | `dispenser` | `23:0` | modern logic block collapsed to dispenser |
| `minecraft:command_block[facing=up,*]` | `dispenser` | `23:1` | modern logic block collapsed to dispenser |
| `minecraft:command_block[facing=north,*]` | `dispenser` | `23:2` | modern logic block collapsed to dispenser |
| `minecraft:command_block[facing=south,*]` | `dispenser` | `23:3` | modern logic block collapsed to dispenser |
| `minecraft:command_block[facing=west,*]` | `dispenser` | `23:4` | modern logic block collapsed to dispenser |
| `minecraft:command_block[facing=east,*]` | `dispenser` | `23:5` | modern logic block collapsed to dispenser |
| `minecraft:command_block[*]` | `dispenser` | `23:2` | modern logic block collapsed to dispenser |
| `minecraft:comparator[facing=north,mode=compare,powered=false,*]` | `comparator` | `149:0` | comparator off |
| `minecraft:comparator[facing=north,mode=compare,powered=true,*]` | `comparator` | `150:0` | comparator on |
| `minecraft:comparator[facing=north,mode=subtract,powered=false,*]` | `comparator` | `149:4` | comparator off |
| `minecraft:comparator[facing=north,mode=subtract,powered=true,*]` | `comparator` | `150:4` | comparator on |
| `minecraft:comparator[facing=east,mode=compare,powered=false,*]` | `comparator` | `149:1` | comparator off |
| `minecraft:comparator[facing=east,mode=compare,powered=true,*]` | `comparator` | `150:1` | comparator on |
| `minecraft:comparator[facing=east,mode=subtract,powered=false,*]` | `comparator` | `149:5` | comparator off |
| `minecraft:comparator[facing=east,mode=subtract,powered=true,*]` | `comparator` | `150:5` | comparator on |
| `minecraft:comparator[facing=south,mode=compare,powered=false,*]` | `comparator` | `149:2` | comparator off |
| `minecraft:comparator[facing=south,mode=compare,powered=true,*]` | `comparator` | `150:2` | comparator on |
| `minecraft:comparator[facing=south,mode=subtract,powered=false,*]` | `comparator` | `149:6` | comparator off |
| `minecraft:comparator[facing=south,mode=subtract,powered=true,*]` | `comparator` | `150:6` | comparator on |
| `minecraft:comparator[facing=west,mode=compare,powered=false,*]` | `comparator` | `149:3` | comparator off |
| `minecraft:comparator[facing=west,mode=compare,powered=true,*]` | `comparator` | `150:3` | comparator on |
| `minecraft:comparator[facing=west,mode=subtract,powered=false,*]` | `comparator` | `149:7` | comparator off |
| `minecraft:comparator[facing=west,mode=subtract,powered=true,*]` | `comparator` | `150:7` | comparator on |
| `minecraft:comparator[*]` | `comparator` | `149:0` |  |
| `minecraft:composter[*]` | `stone` | `1:0` | fallback |
| `minecraft:conduit[*]` | `beacon` | `138:0` |  |
| `minecraft:copper_bars[*]` | `iron_block` | `42:0` |  |
| `minecraft:copper_block[*]` | `iron_block` | `42:0` |  |
| `minecraft:copper_bulb[lit=false,*]` | `redstone_lamp` | `123:0` |  |
| `minecraft:copper_bulb[lit=true,*]` | `redstone_lamp` | `124:0` | lit redstone lamp |
| `minecraft:copper_bulb[*]` | `redstone_lamp` | `123:0` |  |
| `minecraft:copper_chain[*]` | `iron_block` | `42:0` |  |
| `minecraft:copper_chest[*]` | `iron_block` | `42:0` |  |
| `minecraft:copper_door[half=lower,facing=east,open=false,*]` | `iron_door` | `71:0` |  |
| `minecraft:copper_door[half=lower,facing=east,open=true,*]` | `iron_door` | `71:4` |  |
| `minecraft:copper_door[half=lower,facing=south,open=false,*]` | `iron_door` | `71:1` |  |
| `minecraft:copper_door[half=lower,facing=south,open=true,*]` | `iron_door` | `71:5` |  |
| `minecraft:copper_door[half=lower,facing=west,open=false,*]` | `iron_door` | `71:2` |  |
| `minecraft:copper_door[half=lower,facing=west,open=true,*]` | `iron_door` | `71:6` |  |
| `minecraft:copper_door[half=lower,facing=north,open=false,*]` | `iron_door` | `71:3` |  |
| `minecraft:copper_door[half=lower,facing=north,open=true,*]` | `iron_door` | `71:7` |  |
| `minecraft:copper_door[half=upper,hinge=left,*]` | `iron_door` | `71:8` | upper half |
| `minecraft:copper_door[half=upper,hinge=right,*]` | `iron_door` | `71:9` | upper half |
| `minecraft:copper_door[*]` | `iron_door` | `71:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:copper_golem_statue[*]` | `iron_block` | `42:0` |  |
| `minecraft:copper_grate[*]` | `iron_bars` | `101:0` |  |
| `minecraft:copper_lantern[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:copper_ore[*]` | `iron_ore` | `15:0` | copper ore collapsed to iron ore |
| `minecraft:copper_torch[facing=east,*]` | `torch` | `50:1` |  |
| `minecraft:copper_torch[facing=west,*]` | `torch` | `50:2` |  |
| `minecraft:copper_torch[facing=south,*]` | `torch` | `50:3` |  |
| `minecraft:copper_torch[facing=north,*]` | `torch` | `50:4` |  |
| `minecraft:copper_torch[floor=*]` | `torch` | `50:5` |  |
| `minecraft:copper_torch[*]` | `torch` | `50:5` |  |
| `minecraft:copper_trapdoor[half=lower,facing=east,open=false,*]` | `iron_door` | `71:0` |  |
| `minecraft:copper_trapdoor[half=lower,facing=east,open=true,*]` | `iron_door` | `71:4` |  |
| `minecraft:copper_trapdoor[half=lower,facing=south,open=false,*]` | `iron_door` | `71:1` |  |
| `minecraft:copper_trapdoor[half=lower,facing=south,open=true,*]` | `iron_door` | `71:5` |  |
| `minecraft:copper_trapdoor[half=lower,facing=west,open=false,*]` | `iron_door` | `71:2` |  |
| `minecraft:copper_trapdoor[half=lower,facing=west,open=true,*]` | `iron_door` | `71:6` |  |
| `minecraft:copper_trapdoor[half=lower,facing=north,open=false,*]` | `iron_door` | `71:3` |  |
| `minecraft:copper_trapdoor[half=lower,facing=north,open=true,*]` | `iron_door` | `71:7` |  |
| `minecraft:copper_trapdoor[half=upper,hinge=left,*]` | `iron_door` | `71:8` | upper half |
| `minecraft:copper_trapdoor[half=upper,hinge=right,*]` | `iron_door` | `71:9` | upper half |
| `minecraft:copper_trapdoor[*]` | `iron_door` | `71:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:copper_wall_torch[facing=east,*]` | `torch` | `50:1` |  |
| `minecraft:copper_wall_torch[facing=west,*]` | `torch` | `50:2` |  |
| `minecraft:copper_wall_torch[facing=south,*]` | `torch` | `50:3` |  |
| `minecraft:copper_wall_torch[facing=north,*]` | `torch` | `50:4` |  |
| `minecraft:copper_wall_torch[floor=*]` | `torch` | `50:5` |  |
| `minecraft:copper_wall_torch[*]` | `torch` | `50:5` |  |
| `minecraft:cornflower[*]` | `red_flower` | `38:0` |  |
| `minecraft:cracked_deepslate_bricks[*]` | `stonebrick` | `98:0` |  |
| `minecraft:cracked_deepslate_tiles[*]` | `stonebrick` | `98:0` |  |
| `minecraft:cracked_nether_bricks[*]` | `nether_brick` | `112:0` |  |
| `minecraft:cracked_polished_blackstone_bricks[*]` | `stonebrick` | `98:0` |  |
| `minecraft:cracked_stone_bricks[*]` | `stonebrick` | `98:0` |  |
| `minecraft:crafter[facing=down,*]` | `dispenser` | `23:0` | modern logic block collapsed to dispenser |
| `minecraft:crafter[facing=up,*]` | `dispenser` | `23:1` | modern logic block collapsed to dispenser |
| `minecraft:crafter[facing=north,*]` | `dispenser` | `23:2` | modern logic block collapsed to dispenser |
| `minecraft:crafter[facing=south,*]` | `dispenser` | `23:3` | modern logic block collapsed to dispenser |
| `minecraft:crafter[facing=west,*]` | `dispenser` | `23:4` | modern logic block collapsed to dispenser |
| `minecraft:crafter[facing=east,*]` | `dispenser` | `23:5` | modern logic block collapsed to dispenser |
| `minecraft:crafter[*]` | `dispenser` | `23:2` | modern logic block collapsed to dispenser |
| `minecraft:crafting_table[*]` | `crafting_table` | `58:0` |  |
| `minecraft:creaking_heart[*]` | `stone` | `1:0` | fallback |
| `minecraft:creeper_head[rotation=0,*]` | `mob_head` | `144:0` | standing head |
| `minecraft:creeper_head[rotation=1,*]` | `mob_head` | `144:1` | standing head |
| `minecraft:creeper_head[rotation=2,*]` | `mob_head` | `144:2` | standing head |
| `minecraft:creeper_head[rotation=3,*]` | `mob_head` | `144:3` | standing head |
| `minecraft:creeper_head[rotation=4,*]` | `mob_head` | `144:4` | standing head |
| `minecraft:creeper_head[rotation=5,*]` | `mob_head` | `144:5` | standing head |
| `minecraft:creeper_head[rotation=6,*]` | `mob_head` | `144:6` | standing head |
| `minecraft:creeper_head[rotation=7,*]` | `mob_head` | `144:7` | standing head |
| `minecraft:creeper_head[rotation=8,*]` | `mob_head` | `144:8` | standing head |
| `minecraft:creeper_head[rotation=9,*]` | `mob_head` | `144:9` | standing head |
| `minecraft:creeper_head[rotation=10,*]` | `mob_head` | `144:10` | standing head |
| `minecraft:creeper_head[rotation=11,*]` | `mob_head` | `144:11` | standing head |
| `minecraft:creeper_head[rotation=12,*]` | `mob_head` | `144:12` | standing head |
| `minecraft:creeper_head[rotation=13,*]` | `mob_head` | `144:13` | standing head |
| `minecraft:creeper_head[rotation=14,*]` | `mob_head` | `144:14` | standing head |
| `minecraft:creeper_head[rotation=15,*]` | `mob_head` | `144:15` | standing head |
| `minecraft:creeper_head[facing=north,*]` | `mob_head` | `144:2` | wall head |
| `minecraft:creeper_head[facing=south,*]` | `mob_head` | `144:3` | wall head |
| `minecraft:creeper_head[facing=west,*]` | `mob_head` | `144:4` | wall head |
| `minecraft:creeper_head[facing=east,*]` | `mob_head` | `144:5` | wall head |
| `minecraft:creeper_head[*]` | `mob_head` | `144:0` | head type collapsed |
| `minecraft:creeper_wall_head[rotation=0,*]` | `mob_head` | `144:0` | standing head |
| `minecraft:creeper_wall_head[rotation=1,*]` | `mob_head` | `144:1` | standing head |
| `minecraft:creeper_wall_head[rotation=2,*]` | `mob_head` | `144:2` | standing head |
| `minecraft:creeper_wall_head[rotation=3,*]` | `mob_head` | `144:3` | standing head |
| `minecraft:creeper_wall_head[rotation=4,*]` | `mob_head` | `144:4` | standing head |
| `minecraft:creeper_wall_head[rotation=5,*]` | `mob_head` | `144:5` | standing head |
| `minecraft:creeper_wall_head[rotation=6,*]` | `mob_head` | `144:6` | standing head |
| `minecraft:creeper_wall_head[rotation=7,*]` | `mob_head` | `144:7` | standing head |
| `minecraft:creeper_wall_head[rotation=8,*]` | `mob_head` | `144:8` | standing head |
| `minecraft:creeper_wall_head[rotation=9,*]` | `mob_head` | `144:9` | standing head |
| `minecraft:creeper_wall_head[rotation=10,*]` | `mob_head` | `144:10` | standing head |
| `minecraft:creeper_wall_head[rotation=11,*]` | `mob_head` | `144:11` | standing head |
| `minecraft:creeper_wall_head[rotation=12,*]` | `mob_head` | `144:12` | standing head |
| `minecraft:creeper_wall_head[rotation=13,*]` | `mob_head` | `144:13` | standing head |
| `minecraft:creeper_wall_head[rotation=14,*]` | `mob_head` | `144:14` | standing head |
| `minecraft:creeper_wall_head[rotation=15,*]` | `mob_head` | `144:15` | standing head |
| `minecraft:creeper_wall_head[facing=north,*]` | `mob_head` | `144:2` | wall head |
| `minecraft:creeper_wall_head[facing=south,*]` | `mob_head` | `144:3` | wall head |
| `minecraft:creeper_wall_head[facing=west,*]` | `mob_head` | `144:4` | wall head |
| `minecraft:creeper_wall_head[facing=east,*]` | `mob_head` | `144:5` | wall head |
| `minecraft:creeper_wall_head[*]` | `mob_head` | `144:0` | head type collapsed |
| `minecraft:crimson_button[face=floor,*]` | `wooden_button` | `143:1` |  |
| `minecraft:crimson_button[face=wall,facing=east,*]` | `wooden_button` | `143:2` |  |
| `minecraft:crimson_button[face=wall,facing=west,*]` | `wooden_button` | `143:1` |  |
| `minecraft:crimson_button[face=wall,facing=south,*]` | `wooden_button` | `143:3` |  |
| `minecraft:crimson_button[face=wall,facing=north,*]` | `wooden_button` | `143:4` |  |
| `minecraft:crimson_button[powered=true,*]` | `wooden_button` | `143:9` | powered bit approximated (+8) |
| `minecraft:crimson_button[*]` | `wooden_button` | `143:1` |  |
| `minecraft:crimson_door[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:crimson_door[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:crimson_door[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:crimson_door[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:crimson_door[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:crimson_door[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:crimson_door[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:crimson_door[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:crimson_door[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:crimson_door[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:crimson_door[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:crimson_fence[*]` | `fence` | `85:0` |  |
| `minecraft:crimson_fence_gate[facing=south,open=false,*]` | `fence_gate` | `107:0` |  |
| `minecraft:crimson_fence_gate[facing=south,open=true,*]` | `fence_gate` | `107:4` |  |
| `minecraft:crimson_fence_gate[facing=west,open=false,*]` | `fence_gate` | `107:1` |  |
| `minecraft:crimson_fence_gate[facing=west,open=true,*]` | `fence_gate` | `107:5` |  |
| `minecraft:crimson_fence_gate[facing=north,open=false,*]` | `fence_gate` | `107:2` |  |
| `minecraft:crimson_fence_gate[facing=north,open=true,*]` | `fence_gate` | `107:6` |  |
| `minecraft:crimson_fence_gate[facing=east,open=false,*]` | `fence_gate` | `107:3` |  |
| `minecraft:crimson_fence_gate[facing=east,open=true,*]` | `fence_gate` | `107:7` |  |
| `minecraft:crimson_fence_gate[*]` | `fence_gate` | `107:0` |  |
| `minecraft:crimson_fungus[*]` | `stone` | `1:0` | fallback |
| `minecraft:crimson_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:crimson_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:crimson_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:crimson_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:crimson_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:crimson_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:crimson_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:crimson_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:crimson_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:crimson_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:crimson_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:crimson_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:crimson_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:crimson_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:crimson_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:crimson_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:crimson_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:crimson_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:crimson_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:crimson_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:crimson_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:crimson_hyphae[*]` | `stone` | `1:0` | fallback |
| `minecraft:crimson_nylium[*]` | `stone` | `1:0` | fallback |
| `minecraft:crimson_planks[*]` | `planks` | `5:1` |  |
| `minecraft:crimson_pressure_plate[*]` | `wooden_pressure_plate` | `72:0` |  |
| `minecraft:crimson_roots[*]` | `stone` | `1:0` | fallback |
| `minecraft:crimson_shelf[*]` | `stone` | `1:0` | fallback |
| `minecraft:crimson_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:crimson_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:crimson_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:crimson_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:crimson_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:crimson_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:crimson_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:crimson_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:crimson_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:crimson_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:crimson_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:crimson_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:crimson_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:crimson_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:crimson_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:crimson_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:crimson_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:crimson_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:crimson_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:crimson_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:crimson_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:crimson_slab[type=bottom,*]` | `wooden_slab` | `126:1` |  |
| `minecraft:crimson_slab[type=top,*]` | `wooden_slab` | `126:9` |  |
| `minecraft:crimson_slab[type=double,*]` | `wooden_slab` | `125:1` | double slab |
| `minecraft:crimson_slab[*]` | `wooden_slab` | `126:1` |  |
| `minecraft:crimson_stairs[facing=east,half=bottom,*]` | `spruce_stairs` | `134:0` |  |
| `minecraft:crimson_stairs[facing=east,half=top,*]` | `spruce_stairs` | `134:4` |  |
| `minecraft:crimson_stairs[facing=west,half=bottom,*]` | `spruce_stairs` | `134:1` |  |
| `minecraft:crimson_stairs[facing=west,half=top,*]` | `spruce_stairs` | `134:5` |  |
| `minecraft:crimson_stairs[facing=south,half=bottom,*]` | `spruce_stairs` | `134:2` |  |
| `minecraft:crimson_stairs[facing=south,half=top,*]` | `spruce_stairs` | `134:6` |  |
| `minecraft:crimson_stairs[facing=north,half=bottom,*]` | `spruce_stairs` | `134:3` |  |
| `minecraft:crimson_stairs[facing=north,half=top,*]` | `spruce_stairs` | `134:7` |  |
| `minecraft:crimson_stairs[*]` | `spruce_stairs` | `134:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:crimson_stem[*]` | `stone` | `1:0` | fallback |
| `minecraft:crimson_trapdoor[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:crimson_trapdoor[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:crimson_trapdoor[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:crimson_trapdoor[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:crimson_trapdoor[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:crimson_trapdoor[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:crimson_trapdoor[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:crimson_trapdoor[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:crimson_trapdoor[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:crimson_trapdoor[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:crimson_trapdoor[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:crimson_wall_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:crimson_wall_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:crimson_wall_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:crimson_wall_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:crimson_wall_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:crimson_wall_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:crimson_wall_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:crimson_wall_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:crimson_wall_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:crimson_wall_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:crimson_wall_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:crimson_wall_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:crimson_wall_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:crimson_wall_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:crimson_wall_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:crimson_wall_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:crimson_wall_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:crimson_wall_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:crimson_wall_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:crimson_wall_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:crimson_wall_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:crimson_wall_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:crimson_wall_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:crimson_wall_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:crimson_wall_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:crimson_wall_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:crimson_wall_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:crimson_wall_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:crimson_wall_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:crimson_wall_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:crimson_wall_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:crimson_wall_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:crimson_wall_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:crimson_wall_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:crimson_wall_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:crimson_wall_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:crimson_wall_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:crimson_wall_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:crimson_wall_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:crimson_wall_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:crimson_wall_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:crimson_wall_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:crying_obsidian[*]` | `obsidian` | `49:0` |  |
| `minecraft:cut_copper[*]` | `iron_block` | `42:0` |  |
| `minecraft:cut_copper_slab[type=bottom,*]` | `stone_slab` | `44:0` |  |
| `minecraft:cut_copper_slab[type=top,*]` | `stone_slab` | `44:8` |  |
| `minecraft:cut_copper_slab[type=double,*]` | `stone_slab` | `43:0` | double slab |
| `minecraft:cut_copper_slab[*]` | `stone_slab` | `44:0` |  |
| `minecraft:cut_copper_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:cut_copper_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:cut_copper_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:cut_copper_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:cut_copper_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:cut_copper_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:cut_copper_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:cut_copper_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:cut_copper_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:cut_red_sandstone[*]` | `sandstone` | `24:0` |  |
| `minecraft:cut_red_sandstone_slab[type=bottom,*]` | `stone_slab` | `44:1` |  |
| `minecraft:cut_red_sandstone_slab[type=top,*]` | `stone_slab` | `44:9` |  |
| `minecraft:cut_red_sandstone_slab[type=double,*]` | `stone_slab` | `43:1` | double slab |
| `minecraft:cut_red_sandstone_slab[*]` | `stone_slab` | `44:1` |  |
| `minecraft:cut_sandstone[*]` | `sandstone` | `24:0` |  |
| `minecraft:cut_sandstone_slab[type=bottom,*]` | `stone_slab` | `44:1` |  |
| `minecraft:cut_sandstone_slab[type=top,*]` | `stone_slab` | `44:9` |  |
| `minecraft:cut_sandstone_slab[type=double,*]` | `stone_slab` | `43:1` | double slab |
| `minecraft:cut_sandstone_slab[*]` | `stone_slab` | `44:1` |  |
| `minecraft:cyan_banner[*]` | `wool` | `35:9` | banner collapsed to wool |
| `minecraft:cyan_bed[part=foot,facing=south,occupied=false,*]` | `bed` | `26:0` | bed color ignored |
| `minecraft:cyan_bed[part=head,facing=south,occupied=false,*]` | `bed` | `26:8` | bed color ignored |
| `minecraft:cyan_bed[part=foot,facing=south,occupied=true,*]` | `bed` | `26:4` | occupied bit; color ignored |
| `minecraft:cyan_bed[part=head,facing=south,occupied=true,*]` | `bed` | `26:12` | occupied+head bits; color ignored |
| `minecraft:cyan_bed[part=foot,facing=west,occupied=false,*]` | `bed` | `26:1` | bed color ignored |
| `minecraft:cyan_bed[part=head,facing=west,occupied=false,*]` | `bed` | `26:9` | bed color ignored |
| `minecraft:cyan_bed[part=foot,facing=west,occupied=true,*]` | `bed` | `26:5` | occupied bit; color ignored |
| `minecraft:cyan_bed[part=head,facing=west,occupied=true,*]` | `bed` | `26:13` | occupied+head bits; color ignored |
| `minecraft:cyan_bed[part=foot,facing=north,occupied=false,*]` | `bed` | `26:2` | bed color ignored |
| `minecraft:cyan_bed[part=head,facing=north,occupied=false,*]` | `bed` | `26:10` | bed color ignored |
| `minecraft:cyan_bed[part=foot,facing=north,occupied=true,*]` | `bed` | `26:6` | occupied bit; color ignored |
| `minecraft:cyan_bed[part=head,facing=north,occupied=true,*]` | `bed` | `26:14` | occupied+head bits; color ignored |
| `minecraft:cyan_bed[part=foot,facing=east,occupied=false,*]` | `bed` | `26:3` | bed color ignored |
| `minecraft:cyan_bed[part=head,facing=east,occupied=false,*]` | `bed` | `26:11` | bed color ignored |
| `minecraft:cyan_bed[part=foot,facing=east,occupied=true,*]` | `bed` | `26:7` | occupied bit; color ignored |
| `minecraft:cyan_bed[part=head,facing=east,occupied=true,*]` | `bed` | `26:15` | occupied+head bits; color ignored |
| `minecraft:cyan_bed[*]` | `bed` | `26:0` | legacy bed ignores color |
| `minecraft:cyan_candle[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:cyan_candle_cake[bites=0,*]` | `cake` | `92:0` |  |
| `minecraft:cyan_candle_cake[bites=1,*]` | `cake` | `92:1` |  |
| `minecraft:cyan_candle_cake[bites=2,*]` | `cake` | `92:2` |  |
| `minecraft:cyan_candle_cake[bites=3,*]` | `cake` | `92:3` |  |
| `minecraft:cyan_candle_cake[bites=4,*]` | `cake` | `92:4` |  |
| `minecraft:cyan_candle_cake[bites=5,*]` | `cake` | `92:5` |  |
| `minecraft:cyan_candle_cake[bites=6,*]` | `cake` | `92:6` |  |
| `minecraft:cyan_candle_cake[*]` | `cake` | `92:0` |  |
| `minecraft:cyan_carpet[*]` | `carpet` | `171:9` |  |
| `minecraft:cyan_concrete[*]` | `stained_hardened_clay` | `159:9` |  |
| `minecraft:cyan_concrete_powder[*]` | `stained_hardened_clay` | `159:9` |  |
| `minecraft:cyan_glazed_terracotta[*]` | `stained_hardened_clay` | `159:9` |  |
| `minecraft:cyan_shulker_box[*]` | `wool` | `35:9` | shulker box collapsed to wool |
| `minecraft:cyan_stained_glass[*]` | `stained_glass` | `95:9` |  |
| `minecraft:cyan_stained_glass_pane[*]` | `stained_glass_pane` | `160:9` |  |
| `minecraft:cyan_terracotta[*]` | `stained_hardened_clay` | `159:9` |  |
| `minecraft:cyan_wall_banner[*]` | `wool` | `35:9` | banner collapsed to wool |
| `minecraft:cyan_wool[*]` | `wool` | `35:9` |  |
| `minecraft:damaged_anvil[facing=north,*]` | `anvil` | `145:8` | anvil orientation/damage |
| `minecraft:damaged_anvil[facing=south,*]` | `anvil` | `145:8` | anvil orientation/damage |
| `minecraft:damaged_anvil[facing=west,*]` | `anvil` | `145:9` | anvil orientation/damage |
| `minecraft:damaged_anvil[facing=east,*]` | `anvil` | `145:9` | anvil orientation/damage |
| `minecraft:damaged_anvil[*]` | `anvil` | `145:8` |  |
| `minecraft:dandelion[*]` | `red_flower` | `38:0` |  |
| `minecraft:dark_oak_button[face=floor,*]` | `wooden_button` | `143:1` |  |
| `minecraft:dark_oak_button[face=wall,facing=east,*]` | `wooden_button` | `143:2` |  |
| `minecraft:dark_oak_button[face=wall,facing=west,*]` | `wooden_button` | `143:1` |  |
| `minecraft:dark_oak_button[face=wall,facing=south,*]` | `wooden_button` | `143:3` |  |
| `minecraft:dark_oak_button[face=wall,facing=north,*]` | `wooden_button` | `143:4` |  |
| `minecraft:dark_oak_button[powered=true,*]` | `wooden_button` | `143:9` | powered bit approximated (+8) |
| `minecraft:dark_oak_button[*]` | `wooden_button` | `143:1` |  |
| `minecraft:dark_oak_door[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:dark_oak_door[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:dark_oak_door[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:dark_oak_door[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:dark_oak_door[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:dark_oak_door[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:dark_oak_door[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:dark_oak_door[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:dark_oak_door[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:dark_oak_door[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:dark_oak_door[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:dark_oak_fence[*]` | `fence` | `85:0` |  |
| `minecraft:dark_oak_fence_gate[facing=south,open=false,*]` | `fence_gate` | `107:0` |  |
| `minecraft:dark_oak_fence_gate[facing=south,open=true,*]` | `fence_gate` | `107:4` |  |
| `minecraft:dark_oak_fence_gate[facing=west,open=false,*]` | `fence_gate` | `107:1` |  |
| `minecraft:dark_oak_fence_gate[facing=west,open=true,*]` | `fence_gate` | `107:5` |  |
| `minecraft:dark_oak_fence_gate[facing=north,open=false,*]` | `fence_gate` | `107:2` |  |
| `minecraft:dark_oak_fence_gate[facing=north,open=true,*]` | `fence_gate` | `107:6` |  |
| `minecraft:dark_oak_fence_gate[facing=east,open=false,*]` | `fence_gate` | `107:3` |  |
| `minecraft:dark_oak_fence_gate[facing=east,open=true,*]` | `fence_gate` | `107:7` |  |
| `minecraft:dark_oak_fence_gate[*]` | `fence_gate` | `107:0` |  |
| `minecraft:dark_oak_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:dark_oak_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:dark_oak_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:dark_oak_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:dark_oak_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:dark_oak_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:dark_oak_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:dark_oak_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:dark_oak_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:dark_oak_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:dark_oak_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:dark_oak_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:dark_oak_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:dark_oak_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:dark_oak_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:dark_oak_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:dark_oak_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:dark_oak_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:dark_oak_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:dark_oak_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:dark_oak_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:dark_oak_leaves[*]` | `leaves` | `18:1` |  |
| `minecraft:dark_oak_log[axis=y,*]` | `log` | `17:1` |  |
| `minecraft:dark_oak_log[axis=x,*]` | `log` | `17:5` |  |
| `minecraft:dark_oak_log[axis=z,*]` | `log` | `17:9` |  |
| `minecraft:dark_oak_log[*]` | `log` | `17:1` |  |
| `minecraft:dark_oak_planks[*]` | `planks` | `5:1` |  |
| `minecraft:dark_oak_pressure_plate[*]` | `wooden_pressure_plate` | `72:0` |  |
| `minecraft:dark_oak_sapling[*]` | `sapling` | `6:1` |  |
| `minecraft:dark_oak_shelf[*]` | `stone` | `1:0` | fallback |
| `minecraft:dark_oak_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:dark_oak_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:dark_oak_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:dark_oak_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:dark_oak_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:dark_oak_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:dark_oak_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:dark_oak_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:dark_oak_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:dark_oak_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:dark_oak_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:dark_oak_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:dark_oak_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:dark_oak_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:dark_oak_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:dark_oak_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:dark_oak_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:dark_oak_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:dark_oak_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:dark_oak_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:dark_oak_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:dark_oak_slab[type=bottom,*]` | `wooden_slab` | `126:1` |  |
| `minecraft:dark_oak_slab[type=top,*]` | `wooden_slab` | `126:9` |  |
| `minecraft:dark_oak_slab[type=double,*]` | `wooden_slab` | `125:1` | double slab |
| `minecraft:dark_oak_slab[*]` | `wooden_slab` | `126:1` |  |
| `minecraft:dark_oak_stairs[facing=east,half=bottom,*]` | `spruce_stairs` | `134:0` |  |
| `minecraft:dark_oak_stairs[facing=east,half=top,*]` | `spruce_stairs` | `134:4` |  |
| `minecraft:dark_oak_stairs[facing=west,half=bottom,*]` | `spruce_stairs` | `134:1` |  |
| `minecraft:dark_oak_stairs[facing=west,half=top,*]` | `spruce_stairs` | `134:5` |  |
| `minecraft:dark_oak_stairs[facing=south,half=bottom,*]` | `spruce_stairs` | `134:2` |  |
| `minecraft:dark_oak_stairs[facing=south,half=top,*]` | `spruce_stairs` | `134:6` |  |
| `minecraft:dark_oak_stairs[facing=north,half=bottom,*]` | `spruce_stairs` | `134:3` |  |
| `minecraft:dark_oak_stairs[facing=north,half=top,*]` | `spruce_stairs` | `134:7` |  |
| `minecraft:dark_oak_stairs[*]` | `spruce_stairs` | `134:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:dark_oak_trapdoor[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:dark_oak_trapdoor[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:dark_oak_trapdoor[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:dark_oak_trapdoor[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:dark_oak_trapdoor[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:dark_oak_trapdoor[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:dark_oak_trapdoor[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:dark_oak_trapdoor[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:dark_oak_trapdoor[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:dark_oak_trapdoor[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:dark_oak_trapdoor[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:dark_oak_wall_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:dark_oak_wall_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:dark_oak_wall_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:dark_oak_wall_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:dark_oak_wall_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:dark_oak_wall_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:dark_oak_wall_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:dark_oak_wall_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:dark_oak_wall_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:dark_oak_wall_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:dark_oak_wall_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:dark_oak_wall_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:dark_oak_wall_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:dark_oak_wall_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:dark_oak_wall_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:dark_oak_wall_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:dark_oak_wall_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:dark_oak_wall_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:dark_oak_wall_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:dark_oak_wall_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:dark_oak_wall_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:dark_oak_wall_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:dark_oak_wall_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:dark_oak_wall_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:dark_oak_wall_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:dark_oak_wall_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:dark_oak_wall_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:dark_oak_wall_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:dark_oak_wall_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:dark_oak_wall_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:dark_oak_wall_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:dark_oak_wall_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:dark_oak_wall_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:dark_oak_wall_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:dark_oak_wall_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:dark_oak_wall_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:dark_oak_wall_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:dark_oak_wall_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:dark_oak_wall_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:dark_oak_wall_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:dark_oak_wall_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:dark_oak_wall_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:dark_oak_wood[axis=y,*]` | `log` | `17:1` |  |
| `minecraft:dark_oak_wood[axis=x,*]` | `log` | `17:5` |  |
| `minecraft:dark_oak_wood[axis=z,*]` | `log` | `17:9` |  |
| `minecraft:dark_oak_wood[*]` | `log` | `17:1` |  |
| `minecraft:dark_prismarine[*]` | `stone` | `1:0` | fallback |
| `minecraft:dark_prismarine_slab[type=bottom,*]` | `stone_slab` | `44:0` |  |
| `minecraft:dark_prismarine_slab[type=top,*]` | `stone_slab` | `44:8` |  |
| `minecraft:dark_prismarine_slab[type=double,*]` | `stone_slab` | `43:0` | double slab |
| `minecraft:dark_prismarine_slab[*]` | `stone_slab` | `44:0` |  |
| `minecraft:dark_prismarine_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:dark_prismarine_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:dark_prismarine_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:dark_prismarine_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:dark_prismarine_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:dark_prismarine_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:dark_prismarine_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:dark_prismarine_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:dark_prismarine_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:daylight_detector[*]` | `daylight_detector` | `151:0` |  |
| `minecraft:dead_brain_coral[*]` | `wool` | `35:11` |  |
| `minecraft:dead_brain_coral_block[*]` | `wool` | `35:11` |  |
| `minecraft:dead_brain_coral_fan[*]` | `wool` | `35:11` |  |
| `minecraft:dead_brain_coral_wall_fan[*]` | `wool` | `35:11` |  |
| `minecraft:dead_bubble_coral[*]` | `wool` | `35:11` |  |
| `minecraft:dead_bubble_coral_block[*]` | `wool` | `35:11` |  |
| `minecraft:dead_bubble_coral_fan[*]` | `wool` | `35:11` |  |
| `minecraft:dead_bubble_coral_wall_fan[*]` | `wool` | `35:11` |  |
| `minecraft:dead_bush[*]` | `dead_bush` | `32:0` |  |
| `minecraft:dead_fire_coral[*]` | `wool` | `35:11` |  |
| `minecraft:dead_fire_coral_block[*]` | `wool` | `35:11` |  |
| `minecraft:dead_fire_coral_fan[*]` | `wool` | `35:11` |  |
| `minecraft:dead_fire_coral_wall_fan[*]` | `wool` | `35:11` |  |
| `minecraft:dead_horn_coral[*]` | `wool` | `35:11` |  |
| `minecraft:dead_horn_coral_block[*]` | `wool` | `35:11` |  |
| `minecraft:dead_horn_coral_fan[*]` | `wool` | `35:11` |  |
| `minecraft:dead_horn_coral_wall_fan[*]` | `wool` | `35:11` |  |
| `minecraft:dead_tube_coral[*]` | `wool` | `35:11` |  |
| `minecraft:dead_tube_coral_block[*]` | `wool` | `35:11` |  |
| `minecraft:dead_tube_coral_fan[*]` | `wool` | `35:11` |  |
| `minecraft:dead_tube_coral_wall_fan[*]` | `wool` | `35:11` |  |
| `minecraft:decorated_pot[*]` | `flower_pot` | `140:0` |  |
| `minecraft:deepslate[*]` | `stone` | `1:0` |  |
| `minecraft:deepslate_brick_slab[type=bottom,*]` | `stone_slab` | `44:5` |  |
| `minecraft:deepslate_brick_slab[type=top,*]` | `stone_slab` | `44:13` |  |
| `minecraft:deepslate_brick_slab[type=double,*]` | `stone_slab` | `43:5` | double slab |
| `minecraft:deepslate_brick_slab[*]` | `stone_slab` | `44:5` |  |
| `minecraft:deepslate_brick_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:deepslate_brick_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:deepslate_brick_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:deepslate_brick_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:deepslate_brick_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:deepslate_brick_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:deepslate_brick_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:deepslate_brick_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:deepslate_brick_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:deepslate_brick_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:deepslate_bricks[*]` | `stonebrick` | `98:0` |  |
| `minecraft:deepslate_coal_ore[*]` | `coal_ore` | `16:0` |  |
| `minecraft:deepslate_copper_ore[*]` | `iron_ore` | `15:0` | copper ore collapsed to iron ore |
| `minecraft:deepslate_diamond_ore[*]` | `diamond_ore` | `56:0` |  |
| `minecraft:deepslate_emerald_ore[*]` | `emerald_ore` | `129:0` |  |
| `minecraft:deepslate_gold_ore[*]` | `gold_ore` | `14:0` |  |
| `minecraft:deepslate_iron_ore[*]` | `iron_ore` | `15:0` |  |
| `minecraft:deepslate_lapis_ore[*]` | `lapis_ore` | `21:0` |  |
| `minecraft:deepslate_redstone_ore[*]` | `redstone_ore` | `73:0` |  |
| `minecraft:deepslate_tile_slab[type=bottom,*]` | `stone_slab` | `44:5` |  |
| `minecraft:deepslate_tile_slab[type=top,*]` | `stone_slab` | `44:13` |  |
| `minecraft:deepslate_tile_slab[type=double,*]` | `stone_slab` | `43:5` | double slab |
| `minecraft:deepslate_tile_slab[*]` | `stone_slab` | `44:5` |  |
| `minecraft:deepslate_tile_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:deepslate_tile_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:deepslate_tile_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:deepslate_tile_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:deepslate_tile_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:deepslate_tile_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:deepslate_tile_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:deepslate_tile_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:deepslate_tile_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:deepslate_tile_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:deepslate_tiles[*]` | `stonebrick` | `98:0` |  |
| `minecraft:detector_rail[shape=north_south,powered=false,*]` | `detector_rail` | `28:0` | unpowered |
| `minecraft:detector_rail[shape=north_south,powered=true,*]` | `detector_rail` | `28:8` | powered |
| `minecraft:detector_rail[shape=east_west,powered=false,*]` | `detector_rail` | `28:1` | unpowered |
| `minecraft:detector_rail[shape=east_west,powered=true,*]` | `detector_rail` | `28:9` | powered |
| `minecraft:detector_rail[shape=ascending_east,powered=false,*]` | `detector_rail` | `28:2` | unpowered |
| `minecraft:detector_rail[shape=ascending_east,powered=true,*]` | `detector_rail` | `28:10` | powered |
| `minecraft:detector_rail[shape=ascending_west,powered=false,*]` | `detector_rail` | `28:3` | unpowered |
| `minecraft:detector_rail[shape=ascending_west,powered=true,*]` | `detector_rail` | `28:11` | powered |
| `minecraft:detector_rail[shape=ascending_north,powered=false,*]` | `detector_rail` | `28:4` | unpowered |
| `minecraft:detector_rail[shape=ascending_north,powered=true,*]` | `detector_rail` | `28:12` | powered |
| `minecraft:detector_rail[shape=ascending_south,powered=false,*]` | `detector_rail` | `28:5` | unpowered |
| `minecraft:detector_rail[shape=ascending_south,powered=true,*]` | `detector_rail` | `28:13` | powered |
| `minecraft:detector_rail[*]` | `detector_rail` | `28:0` | curved shapes collapse to straight |
| `minecraft:diamond_block[*]` | `diamond_block` | `57:0` |  |
| `minecraft:diamond_ore[*]` | `diamond_ore` | `56:0` |  |
| `minecraft:diorite[*]` | `stone` | `1:0` | fallback |
| `minecraft:diorite_slab[type=bottom,*]` | `stone_slab` | `44:0` |  |
| `minecraft:diorite_slab[type=top,*]` | `stone_slab` | `44:8` |  |
| `minecraft:diorite_slab[type=double,*]` | `stone_slab` | `43:0` | double slab |
| `minecraft:diorite_slab[*]` | `stone_slab` | `44:0` |  |
| `minecraft:diorite_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:diorite_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:diorite_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:diorite_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:diorite_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:diorite_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:diorite_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:diorite_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:diorite_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:diorite_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:dirt[*]` | `dirt` | `3:0` |  |
| `minecraft:dirt_path[*]` | `dirt` | `3:0` |  |
| `minecraft:dispenser[facing=down,*]` | `dispenser` | `23:0` |  |
| `minecraft:dispenser[facing=up,*]` | `dispenser` | `23:1` |  |
| `minecraft:dispenser[facing=north,*]` | `dispenser` | `23:2` |  |
| `minecraft:dispenser[facing=south,*]` | `dispenser` | `23:3` |  |
| `minecraft:dispenser[facing=west,*]` | `dispenser` | `23:4` |  |
| `minecraft:dispenser[facing=east,*]` | `dispenser` | `23:5` |  |
| `minecraft:dispenser[*]` | `dispenser` | `23:2` |  |
| `minecraft:dragon_egg[*]` | `dragon_egg` | `122:0` |  |
| `minecraft:dragon_head[rotation=0,*]` | `mob_head` | `144:0` | standing head |
| `minecraft:dragon_head[rotation=1,*]` | `mob_head` | `144:1` | standing head |
| `minecraft:dragon_head[rotation=2,*]` | `mob_head` | `144:2` | standing head |
| `minecraft:dragon_head[rotation=3,*]` | `mob_head` | `144:3` | standing head |
| `minecraft:dragon_head[rotation=4,*]` | `mob_head` | `144:4` | standing head |
| `minecraft:dragon_head[rotation=5,*]` | `mob_head` | `144:5` | standing head |
| `minecraft:dragon_head[rotation=6,*]` | `mob_head` | `144:6` | standing head |
| `minecraft:dragon_head[rotation=7,*]` | `mob_head` | `144:7` | standing head |
| `minecraft:dragon_head[rotation=8,*]` | `mob_head` | `144:8` | standing head |
| `minecraft:dragon_head[rotation=9,*]` | `mob_head` | `144:9` | standing head |
| `minecraft:dragon_head[rotation=10,*]` | `mob_head` | `144:10` | standing head |
| `minecraft:dragon_head[rotation=11,*]` | `mob_head` | `144:11` | standing head |
| `minecraft:dragon_head[rotation=12,*]` | `mob_head` | `144:12` | standing head |
| `minecraft:dragon_head[rotation=13,*]` | `mob_head` | `144:13` | standing head |
| `minecraft:dragon_head[rotation=14,*]` | `mob_head` | `144:14` | standing head |
| `minecraft:dragon_head[rotation=15,*]` | `mob_head` | `144:15` | standing head |
| `minecraft:dragon_head[facing=north,*]` | `mob_head` | `144:2` | wall head |
| `minecraft:dragon_head[facing=south,*]` | `mob_head` | `144:3` | wall head |
| `minecraft:dragon_head[facing=west,*]` | `mob_head` | `144:4` | wall head |
| `minecraft:dragon_head[facing=east,*]` | `mob_head` | `144:5` | wall head |
| `minecraft:dragon_head[*]` | `mob_head` | `144:0` | head type collapsed |
| `minecraft:dragon_wall_head[rotation=0,*]` | `mob_head` | `144:0` | standing head |
| `minecraft:dragon_wall_head[rotation=1,*]` | `mob_head` | `144:1` | standing head |
| `minecraft:dragon_wall_head[rotation=2,*]` | `mob_head` | `144:2` | standing head |
| `minecraft:dragon_wall_head[rotation=3,*]` | `mob_head` | `144:3` | standing head |
| `minecraft:dragon_wall_head[rotation=4,*]` | `mob_head` | `144:4` | standing head |
| `minecraft:dragon_wall_head[rotation=5,*]` | `mob_head` | `144:5` | standing head |
| `minecraft:dragon_wall_head[rotation=6,*]` | `mob_head` | `144:6` | standing head |
| `minecraft:dragon_wall_head[rotation=7,*]` | `mob_head` | `144:7` | standing head |
| `minecraft:dragon_wall_head[rotation=8,*]` | `mob_head` | `144:8` | standing head |
| `minecraft:dragon_wall_head[rotation=9,*]` | `mob_head` | `144:9` | standing head |
| `minecraft:dragon_wall_head[rotation=10,*]` | `mob_head` | `144:10` | standing head |
| `minecraft:dragon_wall_head[rotation=11,*]` | `mob_head` | `144:11` | standing head |
| `minecraft:dragon_wall_head[rotation=12,*]` | `mob_head` | `144:12` | standing head |
| `minecraft:dragon_wall_head[rotation=13,*]` | `mob_head` | `144:13` | standing head |
| `minecraft:dragon_wall_head[rotation=14,*]` | `mob_head` | `144:14` | standing head |
| `minecraft:dragon_wall_head[rotation=15,*]` | `mob_head` | `144:15` | standing head |
| `minecraft:dragon_wall_head[facing=north,*]` | `mob_head` | `144:2` | wall head |
| `minecraft:dragon_wall_head[facing=south,*]` | `mob_head` | `144:3` | wall head |
| `minecraft:dragon_wall_head[facing=west,*]` | `mob_head` | `144:4` | wall head |
| `minecraft:dragon_wall_head[facing=east,*]` | `mob_head` | `144:5` | wall head |
| `minecraft:dragon_wall_head[*]` | `mob_head` | `144:0` | head type collapsed |
| `minecraft:dried_ghast[*]` | `stone` | `1:0` | fallback |
| `minecraft:dried_kelp_block[*]` | `stone` | `1:0` | fallback |
| `minecraft:dripstone_block[*]` | `stone` | `1:0` |  |
| `minecraft:dropper[facing=down,*]` | `dropper` | `158:0` |  |
| `minecraft:dropper[facing=up,*]` | `dropper` | `158:1` |  |
| `minecraft:dropper[facing=north,*]` | `dropper` | `158:2` |  |
| `minecraft:dropper[facing=south,*]` | `dropper` | `158:3` |  |
| `minecraft:dropper[facing=west,*]` | `dropper` | `158:4` |  |
| `minecraft:dropper[facing=east,*]` | `dropper` | `158:5` |  |
| `minecraft:dropper[*]` | `dropper` | `158:2` |  |
| `minecraft:emerald_block[*]` | `emerald_block` | `133:0` |  |
| `minecraft:emerald_ore[*]` | `emerald_ore` | `129:0` |  |
| `minecraft:enchanting_table[*]` | `enchanting_table` | `116:0` |  |
| `minecraft:end_gateway[*]` | `stone` | `1:0` | fallback |
| `minecraft:end_portal[*]` | `portal` | `90:0` |  |
| `minecraft:end_portal_frame[facing=north,eye=false,*]` | `end_portal_frame` | `120:0` | no eye |
| `minecraft:end_portal_frame[facing=north,eye=true,*]` | `end_portal_frame` | `120:4` | with eye |
| `minecraft:end_portal_frame[facing=east,eye=false,*]` | `end_portal_frame` | `120:1` | no eye |
| `minecraft:end_portal_frame[facing=east,eye=true,*]` | `end_portal_frame` | `120:5` | with eye |
| `minecraft:end_portal_frame[facing=south,eye=false,*]` | `end_portal_frame` | `120:2` | no eye |
| `minecraft:end_portal_frame[facing=south,eye=true,*]` | `end_portal_frame` | `120:6` | with eye |
| `minecraft:end_portal_frame[facing=west,eye=false,*]` | `end_portal_frame` | `120:3` | no eye |
| `minecraft:end_portal_frame[facing=west,eye=true,*]` | `end_portal_frame` | `120:7` | with eye |
| `minecraft:end_portal_frame[*]` | `end_portal_frame` | `120:0` |  |
| `minecraft:end_rod[facing=east,*]` | `torch` | `50:1` |  |
| `minecraft:end_rod[facing=west,*]` | `torch` | `50:2` |  |
| `minecraft:end_rod[facing=south,*]` | `torch` | `50:3` |  |
| `minecraft:end_rod[facing=north,*]` | `torch` | `50:4` |  |
| `minecraft:end_rod[floor=*]` | `torch` | `50:5` |  |
| `minecraft:end_rod[*]` | `torch` | `50:5` |  |
| `minecraft:end_stone[*]` | `stone` | `1:0` | fallback |
| `minecraft:end_stone_brick_slab[type=bottom,*]` | `stone_slab` | `44:4` |  |
| `minecraft:end_stone_brick_slab[type=top,*]` | `stone_slab` | `44:12` |  |
| `minecraft:end_stone_brick_slab[type=double,*]` | `stone_slab` | `43:4` | double slab |
| `minecraft:end_stone_brick_slab[*]` | `stone_slab` | `44:4` |  |
| `minecraft:end_stone_brick_stairs[facing=east,half=bottom,*]` | `brick_stairs` | `108:0` |  |
| `minecraft:end_stone_brick_stairs[facing=east,half=top,*]` | `brick_stairs` | `108:4` |  |
| `minecraft:end_stone_brick_stairs[facing=west,half=bottom,*]` | `brick_stairs` | `108:1` |  |
| `minecraft:end_stone_brick_stairs[facing=west,half=top,*]` | `brick_stairs` | `108:5` |  |
| `minecraft:end_stone_brick_stairs[facing=south,half=bottom,*]` | `brick_stairs` | `108:2` |  |
| `minecraft:end_stone_brick_stairs[facing=south,half=top,*]` | `brick_stairs` | `108:6` |  |
| `minecraft:end_stone_brick_stairs[facing=north,half=bottom,*]` | `brick_stairs` | `108:3` |  |
| `minecraft:end_stone_brick_stairs[facing=north,half=top,*]` | `brick_stairs` | `108:7` |  |
| `minecraft:end_stone_brick_stairs[*]` | `brick_stairs` | `108:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:end_stone_brick_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:end_stone_bricks[*]` | `stonebrick` | `98:0` |  |
| `minecraft:ender_chest[facing=north,*]` | `chest` | `54:2` |  |
| `minecraft:ender_chest[facing=south,*]` | `chest` | `54:3` |  |
| `minecraft:ender_chest[facing=west,*]` | `chest` | `54:4` |  |
| `minecraft:ender_chest[facing=east,*]` | `chest` | `54:5` |  |
| `minecraft:ender_chest[*]` | `chest` | `54:2` |  |
| `minecraft:exposed_chiseled_copper[*]` | `iron_block` | `42:0` |  |
| `minecraft:exposed_copper[*]` | `iron_block` | `42:0` |  |
| `minecraft:exposed_copper_bars[*]` | `iron_block` | `42:0` |  |
| `minecraft:exposed_copper_bulb[lit=false,*]` | `redstone_lamp` | `123:0` |  |
| `minecraft:exposed_copper_bulb[lit=true,*]` | `redstone_lamp` | `124:0` | lit redstone lamp |
| `minecraft:exposed_copper_bulb[*]` | `redstone_lamp` | `123:0` |  |
| `minecraft:exposed_copper_chain[*]` | `iron_block` | `42:0` |  |
| `minecraft:exposed_copper_chest[*]` | `iron_block` | `42:0` |  |
| `minecraft:exposed_copper_door[half=lower,facing=east,open=false,*]` | `iron_door` | `71:0` |  |
| `minecraft:exposed_copper_door[half=lower,facing=east,open=true,*]` | `iron_door` | `71:4` |  |
| `minecraft:exposed_copper_door[half=lower,facing=south,open=false,*]` | `iron_door` | `71:1` |  |
| `minecraft:exposed_copper_door[half=lower,facing=south,open=true,*]` | `iron_door` | `71:5` |  |
| `minecraft:exposed_copper_door[half=lower,facing=west,open=false,*]` | `iron_door` | `71:2` |  |
| `minecraft:exposed_copper_door[half=lower,facing=west,open=true,*]` | `iron_door` | `71:6` |  |
| `minecraft:exposed_copper_door[half=lower,facing=north,open=false,*]` | `iron_door` | `71:3` |  |
| `minecraft:exposed_copper_door[half=lower,facing=north,open=true,*]` | `iron_door` | `71:7` |  |
| `minecraft:exposed_copper_door[half=upper,hinge=left,*]` | `iron_door` | `71:8` | upper half |
| `minecraft:exposed_copper_door[half=upper,hinge=right,*]` | `iron_door` | `71:9` | upper half |
| `minecraft:exposed_copper_door[*]` | `iron_door` | `71:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:exposed_copper_golem_statue[*]` | `iron_block` | `42:0` |  |
| `minecraft:exposed_copper_grate[*]` | `iron_bars` | `101:0` |  |
| `minecraft:exposed_copper_lantern[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:exposed_copper_trapdoor[half=lower,facing=east,open=false,*]` | `iron_door` | `71:0` |  |
| `minecraft:exposed_copper_trapdoor[half=lower,facing=east,open=true,*]` | `iron_door` | `71:4` |  |
| `minecraft:exposed_copper_trapdoor[half=lower,facing=south,open=false,*]` | `iron_door` | `71:1` |  |
| `minecraft:exposed_copper_trapdoor[half=lower,facing=south,open=true,*]` | `iron_door` | `71:5` |  |
| `minecraft:exposed_copper_trapdoor[half=lower,facing=west,open=false,*]` | `iron_door` | `71:2` |  |
| `minecraft:exposed_copper_trapdoor[half=lower,facing=west,open=true,*]` | `iron_door` | `71:6` |  |
| `minecraft:exposed_copper_trapdoor[half=lower,facing=north,open=false,*]` | `iron_door` | `71:3` |  |
| `minecraft:exposed_copper_trapdoor[half=lower,facing=north,open=true,*]` | `iron_door` | `71:7` |  |
| `minecraft:exposed_copper_trapdoor[half=upper,hinge=left,*]` | `iron_door` | `71:8` | upper half |
| `minecraft:exposed_copper_trapdoor[half=upper,hinge=right,*]` | `iron_door` | `71:9` | upper half |
| `minecraft:exposed_copper_trapdoor[*]` | `iron_door` | `71:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:exposed_cut_copper[*]` | `iron_block` | `42:0` |  |
| `minecraft:exposed_cut_copper_slab[type=bottom,*]` | `stone_slab` | `44:0` |  |
| `minecraft:exposed_cut_copper_slab[type=top,*]` | `stone_slab` | `44:8` |  |
| `minecraft:exposed_cut_copper_slab[type=double,*]` | `stone_slab` | `43:0` | double slab |
| `minecraft:exposed_cut_copper_slab[*]` | `stone_slab` | `44:0` |  |
| `minecraft:exposed_cut_copper_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:exposed_cut_copper_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:exposed_cut_copper_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:exposed_cut_copper_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:exposed_cut_copper_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:exposed_cut_copper_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:exposed_cut_copper_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:exposed_cut_copper_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:exposed_cut_copper_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:exposed_lightning_rod[*]` | `stone` | `1:0` | fallback |
| `minecraft:farmland[moisture=0,*]` | `farmland` | `60:0` |  |
| `minecraft:farmland[moisture=1,*]` | `farmland` | `60:1` |  |
| `minecraft:farmland[moisture=2,*]` | `farmland` | `60:2` |  |
| `minecraft:farmland[moisture=3,*]` | `farmland` | `60:3` |  |
| `minecraft:farmland[moisture=4,*]` | `farmland` | `60:4` |  |
| `minecraft:farmland[moisture=5,*]` | `farmland` | `60:5` |  |
| `minecraft:farmland[moisture=6,*]` | `farmland` | `60:6` |  |
| `minecraft:farmland[moisture=7,*]` | `farmland` | `60:7` |  |
| `minecraft:farmland[*]` | `farmland` | `60:0` |  |
| `minecraft:fern[*]` | `tallgrass` | `31:1` |  |
| `minecraft:fire[*]` | `stone` | `1:0` | fallback |
| `minecraft:fire_coral[*]` | `wool` | `35:11` |  |
| `minecraft:fire_coral_block[*]` | `wool` | `35:11` |  |
| `minecraft:fire_coral_fan[*]` | `wool` | `35:11` |  |
| `minecraft:fire_coral_wall_fan[*]` | `wool` | `35:11` |  |
| `minecraft:firefly_bush[*]` | `stone` | `1:0` | fallback |
| `minecraft:fletching_table[*]` | `crafting_table` | `58:0` |  |
| `minecraft:flower_pot[*]` | `red_flower` | `38:0` |  |
| `minecraft:flowering_azalea[*]` | `red_flower` | `38:0` |  |
| `minecraft:flowering_azalea_leaves[*]` | `leaves` | `18:0` |  |
| `minecraft:frogspawn[*]` | `stone` | `1:0` | fallback |
| `minecraft:frosted_ice[*]` | `ice` | `79:0` |  |
| `minecraft:furnace[lit=false,facing=north,*]` | `furnace` | `61:2` | furnace |
| `minecraft:furnace[lit=true,facing=north,*]` | `furnace` | `62:2` | lit furnace |
| `minecraft:furnace[lit=false,facing=south,*]` | `furnace` | `61:3` | furnace |
| `minecraft:furnace[lit=true,facing=south,*]` | `furnace` | `62:3` | lit furnace |
| `minecraft:furnace[lit=false,facing=west,*]` | `furnace` | `61:4` | furnace |
| `minecraft:furnace[lit=true,facing=west,*]` | `furnace` | `62:4` | lit furnace |
| `minecraft:furnace[lit=false,facing=east,*]` | `furnace` | `61:5` | furnace |
| `minecraft:furnace[lit=true,facing=east,*]` | `furnace` | `62:5` | lit furnace |
| `minecraft:furnace[*]` | `furnace` | `61:2` | defaults north-facing |
| `minecraft:gilded_blackstone[*]` | `cobblestone` | `4:0` |  |
| `minecraft:glass[*]` | `glass` | `20:0` |  |
| `minecraft:glass_pane[*]` | `thin_glass` | `102:0` |  |
| `minecraft:glow_item_frame[*]` | `stone` | `1:0` | fallback |
| `minecraft:glow_lichen[*]` | `stone` | `1:0` | fallback |
| `minecraft:glowstone[*]` | `glowstone` | `89:0` |  |
| `minecraft:gold_block[*]` | `gold_block` | `41:0` |  |
| `minecraft:gold_ore[*]` | `gold_ore` | `14:0` |  |
| `minecraft:granite[*]` | `stone` | `1:0` | fallback |
| `minecraft:granite_slab[type=bottom,*]` | `stone_slab` | `44:0` |  |
| `minecraft:granite_slab[type=top,*]` | `stone_slab` | `44:8` |  |
| `minecraft:granite_slab[type=double,*]` | `stone_slab` | `43:0` | double slab |
| `minecraft:granite_slab[*]` | `stone_slab` | `44:0` |  |
| `minecraft:granite_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:granite_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:granite_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:granite_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:granite_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:granite_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:granite_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:granite_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:granite_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:granite_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:grass_block[*]` | `grass` | `2:0` |  |
| `minecraft:gravel[*]` | `gravel` | `13:0` |  |
| `minecraft:gray_banner[*]` | `wool` | `35:7` | banner collapsed to wool |
| `minecraft:gray_bed[part=foot,facing=south,occupied=false,*]` | `bed` | `26:0` | bed color ignored |
| `minecraft:gray_bed[part=head,facing=south,occupied=false,*]` | `bed` | `26:8` | bed color ignored |
| `minecraft:gray_bed[part=foot,facing=south,occupied=true,*]` | `bed` | `26:4` | occupied bit; color ignored |
| `minecraft:gray_bed[part=head,facing=south,occupied=true,*]` | `bed` | `26:12` | occupied+head bits; color ignored |
| `minecraft:gray_bed[part=foot,facing=west,occupied=false,*]` | `bed` | `26:1` | bed color ignored |
| `minecraft:gray_bed[part=head,facing=west,occupied=false,*]` | `bed` | `26:9` | bed color ignored |
| `minecraft:gray_bed[part=foot,facing=west,occupied=true,*]` | `bed` | `26:5` | occupied bit; color ignored |
| `minecraft:gray_bed[part=head,facing=west,occupied=true,*]` | `bed` | `26:13` | occupied+head bits; color ignored |
| `minecraft:gray_bed[part=foot,facing=north,occupied=false,*]` | `bed` | `26:2` | bed color ignored |
| `minecraft:gray_bed[part=head,facing=north,occupied=false,*]` | `bed` | `26:10` | bed color ignored |
| `minecraft:gray_bed[part=foot,facing=north,occupied=true,*]` | `bed` | `26:6` | occupied bit; color ignored |
| `minecraft:gray_bed[part=head,facing=north,occupied=true,*]` | `bed` | `26:14` | occupied+head bits; color ignored |
| `minecraft:gray_bed[part=foot,facing=east,occupied=false,*]` | `bed` | `26:3` | bed color ignored |
| `minecraft:gray_bed[part=head,facing=east,occupied=false,*]` | `bed` | `26:11` | bed color ignored |
| `minecraft:gray_bed[part=foot,facing=east,occupied=true,*]` | `bed` | `26:7` | occupied bit; color ignored |
| `minecraft:gray_bed[part=head,facing=east,occupied=true,*]` | `bed` | `26:15` | occupied+head bits; color ignored |
| `minecraft:gray_bed[*]` | `bed` | `26:0` | legacy bed ignores color |
| `minecraft:gray_candle[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:gray_candle_cake[bites=0,*]` | `cake` | `92:0` |  |
| `minecraft:gray_candle_cake[bites=1,*]` | `cake` | `92:1` |  |
| `minecraft:gray_candle_cake[bites=2,*]` | `cake` | `92:2` |  |
| `minecraft:gray_candle_cake[bites=3,*]` | `cake` | `92:3` |  |
| `minecraft:gray_candle_cake[bites=4,*]` | `cake` | `92:4` |  |
| `minecraft:gray_candle_cake[bites=5,*]` | `cake` | `92:5` |  |
| `minecraft:gray_candle_cake[bites=6,*]` | `cake` | `92:6` |  |
| `minecraft:gray_candle_cake[*]` | `cake` | `92:0` |  |
| `minecraft:gray_carpet[*]` | `carpet` | `171:7` |  |
| `minecraft:gray_concrete[*]` | `stained_hardened_clay` | `159:7` |  |
| `minecraft:gray_concrete_powder[*]` | `stained_hardened_clay` | `159:7` |  |
| `minecraft:gray_glazed_terracotta[*]` | `stained_hardened_clay` | `159:7` |  |
| `minecraft:gray_shulker_box[*]` | `wool` | `35:7` | shulker box collapsed to wool |
| `minecraft:gray_stained_glass[*]` | `stained_glass` | `95:7` |  |
| `minecraft:gray_stained_glass_pane[*]` | `stained_glass_pane` | `160:7` |  |
| `minecraft:gray_terracotta[*]` | `stained_hardened_clay` | `159:7` |  |
| `minecraft:gray_wall_banner[*]` | `wool` | `35:7` | banner collapsed to wool |
| `minecraft:gray_wool[*]` | `wool` | `35:7` |  |
| `minecraft:green_banner[*]` | `wool` | `35:13` | banner collapsed to wool |
| `minecraft:green_bed[part=foot,facing=south,occupied=false,*]` | `bed` | `26:0` | bed color ignored |
| `minecraft:green_bed[part=head,facing=south,occupied=false,*]` | `bed` | `26:8` | bed color ignored |
| `minecraft:green_bed[part=foot,facing=south,occupied=true,*]` | `bed` | `26:4` | occupied bit; color ignored |
| `minecraft:green_bed[part=head,facing=south,occupied=true,*]` | `bed` | `26:12` | occupied+head bits; color ignored |
| `minecraft:green_bed[part=foot,facing=west,occupied=false,*]` | `bed` | `26:1` | bed color ignored |
| `minecraft:green_bed[part=head,facing=west,occupied=false,*]` | `bed` | `26:9` | bed color ignored |
| `minecraft:green_bed[part=foot,facing=west,occupied=true,*]` | `bed` | `26:5` | occupied bit; color ignored |
| `minecraft:green_bed[part=head,facing=west,occupied=true,*]` | `bed` | `26:13` | occupied+head bits; color ignored |
| `minecraft:green_bed[part=foot,facing=north,occupied=false,*]` | `bed` | `26:2` | bed color ignored |
| `minecraft:green_bed[part=head,facing=north,occupied=false,*]` | `bed` | `26:10` | bed color ignored |
| `minecraft:green_bed[part=foot,facing=north,occupied=true,*]` | `bed` | `26:6` | occupied bit; color ignored |
| `minecraft:green_bed[part=head,facing=north,occupied=true,*]` | `bed` | `26:14` | occupied+head bits; color ignored |
| `minecraft:green_bed[part=foot,facing=east,occupied=false,*]` | `bed` | `26:3` | bed color ignored |
| `minecraft:green_bed[part=head,facing=east,occupied=false,*]` | `bed` | `26:11` | bed color ignored |
| `minecraft:green_bed[part=foot,facing=east,occupied=true,*]` | `bed` | `26:7` | occupied bit; color ignored |
| `minecraft:green_bed[part=head,facing=east,occupied=true,*]` | `bed` | `26:15` | occupied+head bits; color ignored |
| `minecraft:green_bed[*]` | `bed` | `26:0` | legacy bed ignores color |
| `minecraft:green_candle[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:green_candle_cake[bites=0,*]` | `cake` | `92:0` |  |
| `minecraft:green_candle_cake[bites=1,*]` | `cake` | `92:1` |  |
| `minecraft:green_candle_cake[bites=2,*]` | `cake` | `92:2` |  |
| `minecraft:green_candle_cake[bites=3,*]` | `cake` | `92:3` |  |
| `minecraft:green_candle_cake[bites=4,*]` | `cake` | `92:4` |  |
| `minecraft:green_candle_cake[bites=5,*]` | `cake` | `92:5` |  |
| `minecraft:green_candle_cake[bites=6,*]` | `cake` | `92:6` |  |
| `minecraft:green_candle_cake[*]` | `cake` | `92:0` |  |
| `minecraft:green_carpet[*]` | `carpet` | `171:13` |  |
| `minecraft:green_concrete[*]` | `stained_hardened_clay` | `159:13` |  |
| `minecraft:green_concrete_powder[*]` | `stained_hardened_clay` | `159:13` |  |
| `minecraft:green_glazed_terracotta[*]` | `stained_hardened_clay` | `159:13` |  |
| `minecraft:green_shulker_box[*]` | `wool` | `35:13` | shulker box collapsed to wool |
| `minecraft:green_stained_glass[*]` | `stained_glass` | `95:13` |  |
| `minecraft:green_stained_glass_pane[*]` | `stained_glass_pane` | `160:13` |  |
| `minecraft:green_terracotta[*]` | `stained_hardened_clay` | `159:13` |  |
| `minecraft:green_wall_banner[*]` | `wool` | `35:13` | banner collapsed to wool |
| `minecraft:green_wool[*]` | `wool` | `35:13` |  |
| `minecraft:grindstone[*]` | `stone` | `1:0` |  |
| `minecraft:hanging_roots[*]` | `stone` | `1:0` | fallback |
| `minecraft:hay_block[axis=y,*]` | `hay_block` | `170:0` |  |
| `minecraft:hay_block[axis=x,*]` | `hay_block` | `170:4` |  |
| `minecraft:hay_block[axis=z,*]` | `hay_block` | `170:8` |  |
| `minecraft:hay_block[*]` | `hay_block` | `170:0` |  |
| `minecraft:heavy_core[*]` | `stone` | `1:0` | fallback |
| `minecraft:heavy_weighted_pressure_plate[*]` | `stone_pressure_plate` | `70:0` |  |
| `minecraft:honey_block[*]` | `stone` | `1:0` | fallback |
| `minecraft:honeycomb_block[*]` | `stone` | `1:0` | fallback |
| `minecraft:hopper[facing=down,*]` | `hopper` | `154:0` |  |
| `minecraft:hopper[facing=north,*]` | `hopper` | `154:2` |  |
| `minecraft:hopper[facing=south,*]` | `hopper` | `154:3` |  |
| `minecraft:hopper[facing=west,*]` | `hopper` | `154:4` |  |
| `minecraft:hopper[facing=east,*]` | `hopper` | `154:5` |  |
| `minecraft:hopper[*]` | `hopper` | `154:2` |  |
| `minecraft:horn_coral[*]` | `wool` | `35:11` |  |
| `minecraft:horn_coral_block[*]` | `wool` | `35:11` |  |
| `minecraft:horn_coral_fan[*]` | `wool` | `35:11` |  |
| `minecraft:horn_coral_wall_fan[*]` | `wool` | `35:11` |  |
| `minecraft:ice[*]` | `ice` | `79:0` |  |
| `minecraft:infested_chiseled_stone_bricks[*]` | `stonebrick` | `98:0` |  |
| `minecraft:infested_cobblestone[*]` | `cobblestone` | `4:0` |  |
| `minecraft:infested_cracked_stone_bricks[*]` | `stonebrick` | `98:0` |  |
| `minecraft:infested_deepslate[*]` | `stone` | `1:0` |  |
| `minecraft:infested_mossy_stone_bricks[*]` | `stonebrick` | `98:0` |  |
| `minecraft:infested_stone[*]` | `stone` | `1:0` |  |
| `minecraft:infested_stone_bricks[*]` | `stonebrick` | `98:0` |  |
| `minecraft:iron_bars[*]` | `iron_bars` | `101:0` |  |
| `minecraft:iron_block[*]` | `iron_block` | `42:0` |  |
| `minecraft:iron_chain[*]` | `stone` | `1:0` | fallback |
| `minecraft:iron_door[half=lower,facing=east,open=false,*]` | `iron_door` | `71:0` |  |
| `minecraft:iron_door[half=lower,facing=east,open=true,*]` | `iron_door` | `71:4` |  |
| `minecraft:iron_door[half=lower,facing=south,open=false,*]` | `iron_door` | `71:1` |  |
| `minecraft:iron_door[half=lower,facing=south,open=true,*]` | `iron_door` | `71:5` |  |
| `minecraft:iron_door[half=lower,facing=west,open=false,*]` | `iron_door` | `71:2` |  |
| `minecraft:iron_door[half=lower,facing=west,open=true,*]` | `iron_door` | `71:6` |  |
| `minecraft:iron_door[half=lower,facing=north,open=false,*]` | `iron_door` | `71:3` |  |
| `minecraft:iron_door[half=lower,facing=north,open=true,*]` | `iron_door` | `71:7` |  |
| `minecraft:iron_door[half=upper,hinge=left,*]` | `iron_door` | `71:8` | upper half |
| `minecraft:iron_door[half=upper,hinge=right,*]` | `iron_door` | `71:9` | upper half |
| `minecraft:iron_door[*]` | `iron_door` | `71:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:iron_ore[*]` | `iron_ore` | `15:0` |  |
| `minecraft:iron_trapdoor[half=lower,facing=east,open=false,*]` | `iron_door` | `71:0` |  |
| `minecraft:iron_trapdoor[half=lower,facing=east,open=true,*]` | `iron_door` | `71:4` |  |
| `minecraft:iron_trapdoor[half=lower,facing=south,open=false,*]` | `iron_door` | `71:1` |  |
| `minecraft:iron_trapdoor[half=lower,facing=south,open=true,*]` | `iron_door` | `71:5` |  |
| `minecraft:iron_trapdoor[half=lower,facing=west,open=false,*]` | `iron_door` | `71:2` |  |
| `minecraft:iron_trapdoor[half=lower,facing=west,open=true,*]` | `iron_door` | `71:6` |  |
| `minecraft:iron_trapdoor[half=lower,facing=north,open=false,*]` | `iron_door` | `71:3` |  |
| `minecraft:iron_trapdoor[half=lower,facing=north,open=true,*]` | `iron_door` | `71:7` |  |
| `minecraft:iron_trapdoor[half=upper,hinge=left,*]` | `iron_door` | `71:8` | upper half |
| `minecraft:iron_trapdoor[half=upper,hinge=right,*]` | `iron_door` | `71:9` | upper half |
| `minecraft:iron_trapdoor[*]` | `iron_door` | `71:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:item_frame[*]` | `stone` | `1:0` | fallback |
| `minecraft:jack_o_lantern[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:jigsaw[*]` | `stone` | `1:0` | fallback |
| `minecraft:jukebox[*]` | `jukebox` | `84:0` |  |
| `minecraft:jungle_button[face=floor,*]` | `wooden_button` | `143:1` |  |
| `minecraft:jungle_button[face=wall,facing=east,*]` | `wooden_button` | `143:2` |  |
| `minecraft:jungle_button[face=wall,facing=west,*]` | `wooden_button` | `143:1` |  |
| `minecraft:jungle_button[face=wall,facing=south,*]` | `wooden_button` | `143:3` |  |
| `minecraft:jungle_button[face=wall,facing=north,*]` | `wooden_button` | `143:4` |  |
| `minecraft:jungle_button[powered=true,*]` | `wooden_button` | `143:9` | powered bit approximated (+8) |
| `minecraft:jungle_button[*]` | `wooden_button` | `143:1` |  |
| `minecraft:jungle_door[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:jungle_door[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:jungle_door[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:jungle_door[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:jungle_door[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:jungle_door[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:jungle_door[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:jungle_door[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:jungle_door[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:jungle_door[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:jungle_door[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:jungle_fence[*]` | `fence` | `85:0` |  |
| `minecraft:jungle_fence_gate[facing=south,open=false,*]` | `fence_gate` | `107:0` |  |
| `minecraft:jungle_fence_gate[facing=south,open=true,*]` | `fence_gate` | `107:4` |  |
| `minecraft:jungle_fence_gate[facing=west,open=false,*]` | `fence_gate` | `107:1` |  |
| `minecraft:jungle_fence_gate[facing=west,open=true,*]` | `fence_gate` | `107:5` |  |
| `minecraft:jungle_fence_gate[facing=north,open=false,*]` | `fence_gate` | `107:2` |  |
| `minecraft:jungle_fence_gate[facing=north,open=true,*]` | `fence_gate` | `107:6` |  |
| `minecraft:jungle_fence_gate[facing=east,open=false,*]` | `fence_gate` | `107:3` |  |
| `minecraft:jungle_fence_gate[facing=east,open=true,*]` | `fence_gate` | `107:7` |  |
| `minecraft:jungle_fence_gate[*]` | `fence_gate` | `107:0` |  |
| `minecraft:jungle_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:jungle_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:jungle_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:jungle_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:jungle_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:jungle_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:jungle_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:jungle_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:jungle_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:jungle_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:jungle_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:jungle_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:jungle_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:jungle_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:jungle_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:jungle_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:jungle_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:jungle_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:jungle_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:jungle_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:jungle_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:jungle_leaves[*]` | `leaves` | `18:3` |  |
| `minecraft:jungle_log[axis=y,*]` | `log` | `17:3` |  |
| `minecraft:jungle_log[axis=x,*]` | `log` | `17:7` |  |
| `minecraft:jungle_log[axis=z,*]` | `log` | `17:11` |  |
| `minecraft:jungle_log[*]` | `log` | `17:3` |  |
| `minecraft:jungle_planks[*]` | `planks` | `5:3` |  |
| `minecraft:jungle_pressure_plate[*]` | `wooden_pressure_plate` | `72:0` |  |
| `minecraft:jungle_sapling[*]` | `sapling` | `6:3` |  |
| `minecraft:jungle_shelf[*]` | `stone` | `1:0` | fallback |
| `minecraft:jungle_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:jungle_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:jungle_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:jungle_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:jungle_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:jungle_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:jungle_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:jungle_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:jungle_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:jungle_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:jungle_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:jungle_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:jungle_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:jungle_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:jungle_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:jungle_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:jungle_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:jungle_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:jungle_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:jungle_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:jungle_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:jungle_slab[type=bottom,*]` | `wooden_slab` | `126:3` |  |
| `minecraft:jungle_slab[type=top,*]` | `wooden_slab` | `126:11` |  |
| `minecraft:jungle_slab[type=double,*]` | `wooden_slab` | `125:3` | double slab |
| `minecraft:jungle_slab[*]` | `wooden_slab` | `126:3` |  |
| `minecraft:jungle_stairs[facing=east,half=bottom,*]` | `jungle_stairs` | `136:0` |  |
| `minecraft:jungle_stairs[facing=east,half=top,*]` | `jungle_stairs` | `136:4` |  |
| `minecraft:jungle_stairs[facing=west,half=bottom,*]` | `jungle_stairs` | `136:1` |  |
| `minecraft:jungle_stairs[facing=west,half=top,*]` | `jungle_stairs` | `136:5` |  |
| `minecraft:jungle_stairs[facing=south,half=bottom,*]` | `jungle_stairs` | `136:2` |  |
| `minecraft:jungle_stairs[facing=south,half=top,*]` | `jungle_stairs` | `136:6` |  |
| `minecraft:jungle_stairs[facing=north,half=bottom,*]` | `jungle_stairs` | `136:3` |  |
| `minecraft:jungle_stairs[facing=north,half=top,*]` | `jungle_stairs` | `136:7` |  |
| `minecraft:jungle_stairs[*]` | `jungle_stairs` | `136:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:jungle_trapdoor[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:jungle_trapdoor[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:jungle_trapdoor[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:jungle_trapdoor[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:jungle_trapdoor[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:jungle_trapdoor[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:jungle_trapdoor[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:jungle_trapdoor[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:jungle_trapdoor[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:jungle_trapdoor[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:jungle_trapdoor[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:jungle_wall_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:jungle_wall_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:jungle_wall_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:jungle_wall_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:jungle_wall_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:jungle_wall_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:jungle_wall_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:jungle_wall_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:jungle_wall_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:jungle_wall_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:jungle_wall_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:jungle_wall_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:jungle_wall_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:jungle_wall_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:jungle_wall_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:jungle_wall_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:jungle_wall_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:jungle_wall_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:jungle_wall_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:jungle_wall_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:jungle_wall_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:jungle_wall_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:jungle_wall_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:jungle_wall_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:jungle_wall_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:jungle_wall_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:jungle_wall_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:jungle_wall_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:jungle_wall_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:jungle_wall_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:jungle_wall_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:jungle_wall_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:jungle_wall_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:jungle_wall_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:jungle_wall_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:jungle_wall_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:jungle_wall_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:jungle_wall_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:jungle_wall_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:jungle_wall_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:jungle_wall_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:jungle_wall_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:jungle_wood[axis=y,*]` | `log` | `17:3` |  |
| `minecraft:jungle_wood[axis=x,*]` | `log` | `17:7` |  |
| `minecraft:jungle_wood[axis=z,*]` | `log` | `17:11` |  |
| `minecraft:jungle_wood[*]` | `log` | `17:3` |  |
| `minecraft:kelp[*]` | `stone` | `1:0` | fallback |
| `minecraft:kelp_plant[*]` | `stone` | `1:0` | fallback |
| `minecraft:ladder[facing=north,*]` | `ladder` | `65:2` |  |
| `minecraft:ladder[facing=south,*]` | `ladder` | `65:3` |  |
| `minecraft:ladder[facing=west,*]` | `ladder` | `65:4` |  |
| `minecraft:ladder[facing=east,*]` | `ladder` | `65:5` |  |
| `minecraft:ladder[*]` | `ladder` | `65:2` |  |
| `minecraft:lantern[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:lapis_block[*]` | `lapis_block` | `22:0` |  |
| `minecraft:lapis_ore[*]` | `lapis_ore` | `21:0` |  |
| `minecraft:large_amethyst_bud[*]` | `obsidian` | `49:0` |  |
| `minecraft:large_fern[*]` | `tallgrass` | `31:1` |  |
| `minecraft:lava[*]` | `lava` | `11:0` |  |
| `minecraft:lava_cauldron[level=0,*]` | `cauldron` | `118:0` |  |
| `minecraft:lava_cauldron[level=1,*]` | `cauldron` | `118:1` |  |
| `minecraft:lava_cauldron[level=2,*]` | `cauldron` | `118:2` |  |
| `minecraft:lava_cauldron[level=3,*]` | `cauldron` | `118:3` |  |
| `minecraft:lava_cauldron[*]` | `cauldron` | `118:0` | lava/powder-snow cauldrons collapse to cauldron levels |
| `minecraft:leaf_litter[*]` | `stone` | `1:0` | fallback |
| `minecraft:lectern[*]` | `bookshelf` | `47:0` |  |
| `minecraft:lever[face=floor,*]` | `lever` | `69:5` |  |
| `minecraft:lever[face=ceiling,*]` | `lever` | `69:7` |  |
| `minecraft:lever[face=wall,facing=east,*]` | `lever` | `69:1` |  |
| `minecraft:lever[face=wall,facing=west,*]` | `lever` | `69:2` |  |
| `minecraft:lever[face=wall,facing=south,*]` | `lever` | `69:3` |  |
| `minecraft:lever[face=wall,facing=north,*]` | `lever` | `69:4` |  |
| `minecraft:lever[powered=true,*]` | `lever` | `69:13` | powered bit approximated (+8) |
| `minecraft:lever[*]` | `lever` | `69:5` |  |
| `minecraft:light[*]` | `torch` | `50:0` |  |
| `minecraft:light_blue_banner[*]` | `wool` | `35:3` | banner collapsed to wool |
| `minecraft:light_blue_bed[part=foot,facing=south,occupied=false,*]` | `bed` | `26:0` | bed color ignored |
| `minecraft:light_blue_bed[part=head,facing=south,occupied=false,*]` | `bed` | `26:8` | bed color ignored |
| `minecraft:light_blue_bed[part=foot,facing=south,occupied=true,*]` | `bed` | `26:4` | occupied bit; color ignored |
| `minecraft:light_blue_bed[part=head,facing=south,occupied=true,*]` | `bed` | `26:12` | occupied+head bits; color ignored |
| `minecraft:light_blue_bed[part=foot,facing=west,occupied=false,*]` | `bed` | `26:1` | bed color ignored |
| `minecraft:light_blue_bed[part=head,facing=west,occupied=false,*]` | `bed` | `26:9` | bed color ignored |
| `minecraft:light_blue_bed[part=foot,facing=west,occupied=true,*]` | `bed` | `26:5` | occupied bit; color ignored |
| `minecraft:light_blue_bed[part=head,facing=west,occupied=true,*]` | `bed` | `26:13` | occupied+head bits; color ignored |
| `minecraft:light_blue_bed[part=foot,facing=north,occupied=false,*]` | `bed` | `26:2` | bed color ignored |
| `minecraft:light_blue_bed[part=head,facing=north,occupied=false,*]` | `bed` | `26:10` | bed color ignored |
| `minecraft:light_blue_bed[part=foot,facing=north,occupied=true,*]` | `bed` | `26:6` | occupied bit; color ignored |
| `minecraft:light_blue_bed[part=head,facing=north,occupied=true,*]` | `bed` | `26:14` | occupied+head bits; color ignored |
| `minecraft:light_blue_bed[part=foot,facing=east,occupied=false,*]` | `bed` | `26:3` | bed color ignored |
| `minecraft:light_blue_bed[part=head,facing=east,occupied=false,*]` | `bed` | `26:11` | bed color ignored |
| `minecraft:light_blue_bed[part=foot,facing=east,occupied=true,*]` | `bed` | `26:7` | occupied bit; color ignored |
| `minecraft:light_blue_bed[part=head,facing=east,occupied=true,*]` | `bed` | `26:15` | occupied+head bits; color ignored |
| `minecraft:light_blue_bed[*]` | `bed` | `26:0` | legacy bed ignores color |
| `minecraft:light_blue_candle[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:light_blue_candle_cake[bites=0,*]` | `cake` | `92:0` |  |
| `minecraft:light_blue_candle_cake[bites=1,*]` | `cake` | `92:1` |  |
| `minecraft:light_blue_candle_cake[bites=2,*]` | `cake` | `92:2` |  |
| `minecraft:light_blue_candle_cake[bites=3,*]` | `cake` | `92:3` |  |
| `minecraft:light_blue_candle_cake[bites=4,*]` | `cake` | `92:4` |  |
| `minecraft:light_blue_candle_cake[bites=5,*]` | `cake` | `92:5` |  |
| `minecraft:light_blue_candle_cake[bites=6,*]` | `cake` | `92:6` |  |
| `minecraft:light_blue_candle_cake[*]` | `cake` | `92:0` |  |
| `minecraft:light_blue_carpet[*]` | `carpet` | `171:3` |  |
| `minecraft:light_blue_concrete[*]` | `stained_hardened_clay` | `159:3` |  |
| `minecraft:light_blue_concrete_powder[*]` | `stained_hardened_clay` | `159:3` |  |
| `minecraft:light_blue_glazed_terracotta[*]` | `stained_hardened_clay` | `159:3` |  |
| `minecraft:light_blue_shulker_box[*]` | `wool` | `35:3` | shulker box collapsed to wool |
| `minecraft:light_blue_stained_glass[*]` | `stained_glass` | `95:3` |  |
| `minecraft:light_blue_stained_glass_pane[*]` | `stained_glass_pane` | `160:3` |  |
| `minecraft:light_blue_terracotta[*]` | `stained_hardened_clay` | `159:3` |  |
| `minecraft:light_blue_wall_banner[*]` | `wool` | `35:3` | banner collapsed to wool |
| `minecraft:light_blue_wool[*]` | `wool` | `35:3` |  |
| `minecraft:light_gray_banner[*]` | `wool` | `35:8` | banner collapsed to wool |
| `minecraft:light_gray_bed[part=foot,facing=south,occupied=false,*]` | `bed` | `26:0` | bed color ignored |
| `minecraft:light_gray_bed[part=head,facing=south,occupied=false,*]` | `bed` | `26:8` | bed color ignored |
| `minecraft:light_gray_bed[part=foot,facing=south,occupied=true,*]` | `bed` | `26:4` | occupied bit; color ignored |
| `minecraft:light_gray_bed[part=head,facing=south,occupied=true,*]` | `bed` | `26:12` | occupied+head bits; color ignored |
| `minecraft:light_gray_bed[part=foot,facing=west,occupied=false,*]` | `bed` | `26:1` | bed color ignored |
| `minecraft:light_gray_bed[part=head,facing=west,occupied=false,*]` | `bed` | `26:9` | bed color ignored |
| `minecraft:light_gray_bed[part=foot,facing=west,occupied=true,*]` | `bed` | `26:5` | occupied bit; color ignored |
| `minecraft:light_gray_bed[part=head,facing=west,occupied=true,*]` | `bed` | `26:13` | occupied+head bits; color ignored |
| `minecraft:light_gray_bed[part=foot,facing=north,occupied=false,*]` | `bed` | `26:2` | bed color ignored |
| `minecraft:light_gray_bed[part=head,facing=north,occupied=false,*]` | `bed` | `26:10` | bed color ignored |
| `minecraft:light_gray_bed[part=foot,facing=north,occupied=true,*]` | `bed` | `26:6` | occupied bit; color ignored |
| `minecraft:light_gray_bed[part=head,facing=north,occupied=true,*]` | `bed` | `26:14` | occupied+head bits; color ignored |
| `minecraft:light_gray_bed[part=foot,facing=east,occupied=false,*]` | `bed` | `26:3` | bed color ignored |
| `minecraft:light_gray_bed[part=head,facing=east,occupied=false,*]` | `bed` | `26:11` | bed color ignored |
| `minecraft:light_gray_bed[part=foot,facing=east,occupied=true,*]` | `bed` | `26:7` | occupied bit; color ignored |
| `minecraft:light_gray_bed[part=head,facing=east,occupied=true,*]` | `bed` | `26:15` | occupied+head bits; color ignored |
| `minecraft:light_gray_bed[*]` | `bed` | `26:0` | legacy bed ignores color |
| `minecraft:light_gray_candle[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:light_gray_candle_cake[bites=0,*]` | `cake` | `92:0` |  |
| `minecraft:light_gray_candle_cake[bites=1,*]` | `cake` | `92:1` |  |
| `minecraft:light_gray_candle_cake[bites=2,*]` | `cake` | `92:2` |  |
| `minecraft:light_gray_candle_cake[bites=3,*]` | `cake` | `92:3` |  |
| `minecraft:light_gray_candle_cake[bites=4,*]` | `cake` | `92:4` |  |
| `minecraft:light_gray_candle_cake[bites=5,*]` | `cake` | `92:5` |  |
| `minecraft:light_gray_candle_cake[bites=6,*]` | `cake` | `92:6` |  |
| `minecraft:light_gray_candle_cake[*]` | `cake` | `92:0` |  |
| `minecraft:light_gray_carpet[*]` | `carpet` | `171:8` |  |
| `minecraft:light_gray_concrete[*]` | `stained_hardened_clay` | `159:8` |  |
| `minecraft:light_gray_concrete_powder[*]` | `stained_hardened_clay` | `159:8` |  |
| `minecraft:light_gray_glazed_terracotta[*]` | `stained_hardened_clay` | `159:8` |  |
| `minecraft:light_gray_shulker_box[*]` | `wool` | `35:8` | shulker box collapsed to wool |
| `minecraft:light_gray_stained_glass[*]` | `stained_glass` | `95:8` |  |
| `minecraft:light_gray_stained_glass_pane[*]` | `stained_glass_pane` | `160:8` |  |
| `minecraft:light_gray_terracotta[*]` | `stained_hardened_clay` | `159:8` |  |
| `minecraft:light_gray_wall_banner[*]` | `wool` | `35:8` | banner collapsed to wool |
| `minecraft:light_gray_wool[*]` | `wool` | `35:8` |  |
| `minecraft:light_weighted_pressure_plate[*]` | `stone_pressure_plate` | `70:0` |  |
| `minecraft:lightning_rod[*]` | `stone` | `1:0` | fallback |
| `minecraft:lilac[*]` | `stone` | `1:0` | fallback |
| `minecraft:lily_of_the_valley[*]` | `red_flower` | `38:0` |  |
| `minecraft:lily_pad[*]` | `waterlily` | `111:0` |  |
| `minecraft:lime_banner[*]` | `wool` | `35:5` | banner collapsed to wool |
| `minecraft:lime_bed[part=foot,facing=south,occupied=false,*]` | `bed` | `26:0` | bed color ignored |
| `minecraft:lime_bed[part=head,facing=south,occupied=false,*]` | `bed` | `26:8` | bed color ignored |
| `minecraft:lime_bed[part=foot,facing=south,occupied=true,*]` | `bed` | `26:4` | occupied bit; color ignored |
| `minecraft:lime_bed[part=head,facing=south,occupied=true,*]` | `bed` | `26:12` | occupied+head bits; color ignored |
| `minecraft:lime_bed[part=foot,facing=west,occupied=false,*]` | `bed` | `26:1` | bed color ignored |
| `minecraft:lime_bed[part=head,facing=west,occupied=false,*]` | `bed` | `26:9` | bed color ignored |
| `minecraft:lime_bed[part=foot,facing=west,occupied=true,*]` | `bed` | `26:5` | occupied bit; color ignored |
| `minecraft:lime_bed[part=head,facing=west,occupied=true,*]` | `bed` | `26:13` | occupied+head bits; color ignored |
| `minecraft:lime_bed[part=foot,facing=north,occupied=false,*]` | `bed` | `26:2` | bed color ignored |
| `minecraft:lime_bed[part=head,facing=north,occupied=false,*]` | `bed` | `26:10` | bed color ignored |
| `minecraft:lime_bed[part=foot,facing=north,occupied=true,*]` | `bed` | `26:6` | occupied bit; color ignored |
| `minecraft:lime_bed[part=head,facing=north,occupied=true,*]` | `bed` | `26:14` | occupied+head bits; color ignored |
| `minecraft:lime_bed[part=foot,facing=east,occupied=false,*]` | `bed` | `26:3` | bed color ignored |
| `minecraft:lime_bed[part=head,facing=east,occupied=false,*]` | `bed` | `26:11` | bed color ignored |
| `minecraft:lime_bed[part=foot,facing=east,occupied=true,*]` | `bed` | `26:7` | occupied bit; color ignored |
| `minecraft:lime_bed[part=head,facing=east,occupied=true,*]` | `bed` | `26:15` | occupied+head bits; color ignored |
| `minecraft:lime_bed[*]` | `bed` | `26:0` | legacy bed ignores color |
| `minecraft:lime_candle[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:lime_candle_cake[bites=0,*]` | `cake` | `92:0` |  |
| `minecraft:lime_candle_cake[bites=1,*]` | `cake` | `92:1` |  |
| `minecraft:lime_candle_cake[bites=2,*]` | `cake` | `92:2` |  |
| `minecraft:lime_candle_cake[bites=3,*]` | `cake` | `92:3` |  |
| `minecraft:lime_candle_cake[bites=4,*]` | `cake` | `92:4` |  |
| `minecraft:lime_candle_cake[bites=5,*]` | `cake` | `92:5` |  |
| `minecraft:lime_candle_cake[bites=6,*]` | `cake` | `92:6` |  |
| `minecraft:lime_candle_cake[*]` | `cake` | `92:0` |  |
| `minecraft:lime_carpet[*]` | `carpet` | `171:5` |  |
| `minecraft:lime_concrete[*]` | `stained_hardened_clay` | `159:5` |  |
| `minecraft:lime_concrete_powder[*]` | `stained_hardened_clay` | `159:5` |  |
| `minecraft:lime_glazed_terracotta[*]` | `stained_hardened_clay` | `159:5` |  |
| `minecraft:lime_shulker_box[*]` | `wool` | `35:5` | shulker box collapsed to wool |
| `minecraft:lime_stained_glass[*]` | `stained_glass` | `95:5` |  |
| `minecraft:lime_stained_glass_pane[*]` | `stained_glass_pane` | `160:5` |  |
| `minecraft:lime_terracotta[*]` | `stained_hardened_clay` | `159:5` |  |
| `minecraft:lime_wall_banner[*]` | `wool` | `35:5` | banner collapsed to wool |
| `minecraft:lime_wool[*]` | `wool` | `35:5` |  |
| `minecraft:lodestone[*]` | `iron_block` | `42:0` |  |
| `minecraft:loom[*]` | `crafting_table` | `58:0` |  |
| `minecraft:magenta_banner[*]` | `wool` | `35:2` | banner collapsed to wool |
| `minecraft:magenta_bed[part=foot,facing=south,occupied=false,*]` | `bed` | `26:0` | bed color ignored |
| `minecraft:magenta_bed[part=head,facing=south,occupied=false,*]` | `bed` | `26:8` | bed color ignored |
| `minecraft:magenta_bed[part=foot,facing=south,occupied=true,*]` | `bed` | `26:4` | occupied bit; color ignored |
| `minecraft:magenta_bed[part=head,facing=south,occupied=true,*]` | `bed` | `26:12` | occupied+head bits; color ignored |
| `minecraft:magenta_bed[part=foot,facing=west,occupied=false,*]` | `bed` | `26:1` | bed color ignored |
| `minecraft:magenta_bed[part=head,facing=west,occupied=false,*]` | `bed` | `26:9` | bed color ignored |
| `minecraft:magenta_bed[part=foot,facing=west,occupied=true,*]` | `bed` | `26:5` | occupied bit; color ignored |
| `minecraft:magenta_bed[part=head,facing=west,occupied=true,*]` | `bed` | `26:13` | occupied+head bits; color ignored |
| `minecraft:magenta_bed[part=foot,facing=north,occupied=false,*]` | `bed` | `26:2` | bed color ignored |
| `minecraft:magenta_bed[part=head,facing=north,occupied=false,*]` | `bed` | `26:10` | bed color ignored |
| `minecraft:magenta_bed[part=foot,facing=north,occupied=true,*]` | `bed` | `26:6` | occupied bit; color ignored |
| `minecraft:magenta_bed[part=head,facing=north,occupied=true,*]` | `bed` | `26:14` | occupied+head bits; color ignored |
| `minecraft:magenta_bed[part=foot,facing=east,occupied=false,*]` | `bed` | `26:3` | bed color ignored |
| `minecraft:magenta_bed[part=head,facing=east,occupied=false,*]` | `bed` | `26:11` | bed color ignored |
| `minecraft:magenta_bed[part=foot,facing=east,occupied=true,*]` | `bed` | `26:7` | occupied bit; color ignored |
| `minecraft:magenta_bed[part=head,facing=east,occupied=true,*]` | `bed` | `26:15` | occupied+head bits; color ignored |
| `minecraft:magenta_bed[*]` | `bed` | `26:0` | legacy bed ignores color |
| `minecraft:magenta_candle[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:magenta_candle_cake[bites=0,*]` | `cake` | `92:0` |  |
| `minecraft:magenta_candle_cake[bites=1,*]` | `cake` | `92:1` |  |
| `minecraft:magenta_candle_cake[bites=2,*]` | `cake` | `92:2` |  |
| `minecraft:magenta_candle_cake[bites=3,*]` | `cake` | `92:3` |  |
| `minecraft:magenta_candle_cake[bites=4,*]` | `cake` | `92:4` |  |
| `minecraft:magenta_candle_cake[bites=5,*]` | `cake` | `92:5` |  |
| `minecraft:magenta_candle_cake[bites=6,*]` | `cake` | `92:6` |  |
| `minecraft:magenta_candle_cake[*]` | `cake` | `92:0` |  |
| `minecraft:magenta_carpet[*]` | `carpet` | `171:2` |  |
| `minecraft:magenta_concrete[*]` | `stained_hardened_clay` | `159:2` |  |
| `minecraft:magenta_concrete_powder[*]` | `stained_hardened_clay` | `159:2` |  |
| `minecraft:magenta_glazed_terracotta[*]` | `stained_hardened_clay` | `159:2` |  |
| `minecraft:magenta_shulker_box[*]` | `wool` | `35:2` | shulker box collapsed to wool |
| `minecraft:magenta_stained_glass[*]` | `stained_glass` | `95:2` |  |
| `minecraft:magenta_stained_glass_pane[*]` | `stained_glass_pane` | `160:2` |  |
| `minecraft:magenta_terracotta[*]` | `stained_hardened_clay` | `159:2` |  |
| `minecraft:magenta_wall_banner[*]` | `wool` | `35:2` | banner collapsed to wool |
| `minecraft:magenta_wool[*]` | `wool` | `35:2` |  |
| `minecraft:magma_block[*]` | `netherrack` | `87:0` |  |
| `minecraft:mangrove_button[face=floor,*]` | `wooden_button` | `143:1` |  |
| `minecraft:mangrove_button[face=wall,facing=east,*]` | `wooden_button` | `143:2` |  |
| `minecraft:mangrove_button[face=wall,facing=west,*]` | `wooden_button` | `143:1` |  |
| `minecraft:mangrove_button[face=wall,facing=south,*]` | `wooden_button` | `143:3` |  |
| `minecraft:mangrove_button[face=wall,facing=north,*]` | `wooden_button` | `143:4` |  |
| `minecraft:mangrove_button[powered=true,*]` | `wooden_button` | `143:9` | powered bit approximated (+8) |
| `minecraft:mangrove_button[*]` | `wooden_button` | `143:1` |  |
| `minecraft:mangrove_door[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:mangrove_door[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:mangrove_door[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:mangrove_door[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:mangrove_door[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:mangrove_door[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:mangrove_door[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:mangrove_door[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:mangrove_door[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:mangrove_door[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:mangrove_door[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:mangrove_fence[*]` | `fence` | `85:0` |  |
| `minecraft:mangrove_fence_gate[facing=south,open=false,*]` | `fence_gate` | `107:0` |  |
| `minecraft:mangrove_fence_gate[facing=south,open=true,*]` | `fence_gate` | `107:4` |  |
| `minecraft:mangrove_fence_gate[facing=west,open=false,*]` | `fence_gate` | `107:1` |  |
| `minecraft:mangrove_fence_gate[facing=west,open=true,*]` | `fence_gate` | `107:5` |  |
| `minecraft:mangrove_fence_gate[facing=north,open=false,*]` | `fence_gate` | `107:2` |  |
| `minecraft:mangrove_fence_gate[facing=north,open=true,*]` | `fence_gate` | `107:6` |  |
| `minecraft:mangrove_fence_gate[facing=east,open=false,*]` | `fence_gate` | `107:3` |  |
| `minecraft:mangrove_fence_gate[facing=east,open=true,*]` | `fence_gate` | `107:7` |  |
| `minecraft:mangrove_fence_gate[*]` | `fence_gate` | `107:0` |  |
| `minecraft:mangrove_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:mangrove_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:mangrove_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:mangrove_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:mangrove_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:mangrove_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:mangrove_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:mangrove_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:mangrove_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:mangrove_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:mangrove_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:mangrove_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:mangrove_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:mangrove_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:mangrove_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:mangrove_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:mangrove_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:mangrove_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:mangrove_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:mangrove_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:mangrove_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:mangrove_leaves[*]` | `leaves` | `18:3` |  |
| `minecraft:mangrove_log[axis=y,*]` | `log` | `17:3` |  |
| `minecraft:mangrove_log[axis=x,*]` | `log` | `17:7` |  |
| `minecraft:mangrove_log[axis=z,*]` | `log` | `17:11` |  |
| `minecraft:mangrove_log[*]` | `log` | `17:3` |  |
| `minecraft:mangrove_planks[*]` | `planks` | `5:3` |  |
| `minecraft:mangrove_pressure_plate[*]` | `wooden_pressure_plate` | `72:0` |  |
| `minecraft:mangrove_propagule[*]` | `stone` | `1:0` | fallback |
| `minecraft:mangrove_roots[*]` | `log` | `17:3` |  |
| `minecraft:mangrove_shelf[*]` | `stone` | `1:0` | fallback |
| `minecraft:mangrove_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:mangrove_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:mangrove_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:mangrove_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:mangrove_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:mangrove_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:mangrove_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:mangrove_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:mangrove_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:mangrove_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:mangrove_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:mangrove_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:mangrove_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:mangrove_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:mangrove_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:mangrove_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:mangrove_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:mangrove_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:mangrove_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:mangrove_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:mangrove_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:mangrove_slab[type=bottom,*]` | `wooden_slab` | `126:3` |  |
| `minecraft:mangrove_slab[type=top,*]` | `wooden_slab` | `126:11` |  |
| `minecraft:mangrove_slab[type=double,*]` | `wooden_slab` | `125:3` | double slab |
| `minecraft:mangrove_slab[*]` | `wooden_slab` | `126:3` |  |
| `minecraft:mangrove_stairs[facing=east,half=bottom,*]` | `jungle_stairs` | `136:0` |  |
| `minecraft:mangrove_stairs[facing=east,half=top,*]` | `jungle_stairs` | `136:4` |  |
| `minecraft:mangrove_stairs[facing=west,half=bottom,*]` | `jungle_stairs` | `136:1` |  |
| `minecraft:mangrove_stairs[facing=west,half=top,*]` | `jungle_stairs` | `136:5` |  |
| `minecraft:mangrove_stairs[facing=south,half=bottom,*]` | `jungle_stairs` | `136:2` |  |
| `minecraft:mangrove_stairs[facing=south,half=top,*]` | `jungle_stairs` | `136:6` |  |
| `minecraft:mangrove_stairs[facing=north,half=bottom,*]` | `jungle_stairs` | `136:3` |  |
| `minecraft:mangrove_stairs[facing=north,half=top,*]` | `jungle_stairs` | `136:7` |  |
| `minecraft:mangrove_stairs[*]` | `jungle_stairs` | `136:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:mangrove_trapdoor[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:mangrove_trapdoor[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:mangrove_trapdoor[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:mangrove_trapdoor[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:mangrove_trapdoor[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:mangrove_trapdoor[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:mangrove_trapdoor[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:mangrove_trapdoor[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:mangrove_trapdoor[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:mangrove_trapdoor[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:mangrove_trapdoor[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:mangrove_wall_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:mangrove_wall_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:mangrove_wall_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:mangrove_wall_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:mangrove_wall_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:mangrove_wall_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:mangrove_wall_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:mangrove_wall_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:mangrove_wall_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:mangrove_wall_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:mangrove_wall_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:mangrove_wall_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:mangrove_wall_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:mangrove_wall_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:mangrove_wall_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:mangrove_wall_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:mangrove_wall_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:mangrove_wall_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:mangrove_wall_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:mangrove_wall_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:mangrove_wall_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:mangrove_wall_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:mangrove_wall_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:mangrove_wall_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:mangrove_wall_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:mangrove_wall_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:mangrove_wall_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:mangrove_wall_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:mangrove_wall_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:mangrove_wall_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:mangrove_wall_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:mangrove_wall_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:mangrove_wall_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:mangrove_wall_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:mangrove_wall_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:mangrove_wall_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:mangrove_wall_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:mangrove_wall_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:mangrove_wall_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:mangrove_wall_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:mangrove_wall_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:mangrove_wall_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:mangrove_wood[axis=y,*]` | `log` | `17:3` |  |
| `minecraft:mangrove_wood[axis=x,*]` | `log` | `17:7` |  |
| `minecraft:mangrove_wood[axis=z,*]` | `log` | `17:11` |  |
| `minecraft:mangrove_wood[*]` | `log` | `17:3` |  |
| `minecraft:medium_amethyst_bud[*]` | `obsidian` | `49:0` |  |
| `minecraft:melon[*]` | `melon_block` | `103:0` |  |
| `minecraft:melon_stem[age=0,*]` | `melon_stem` | `105:0` |  |
| `minecraft:melon_stem[age=1,*]` | `melon_stem` | `105:1` |  |
| `minecraft:melon_stem[age=2,*]` | `melon_stem` | `105:2` |  |
| `minecraft:melon_stem[age=3,*]` | `melon_stem` | `105:3` |  |
| `minecraft:melon_stem[age=4,*]` | `melon_stem` | `105:4` |  |
| `minecraft:melon_stem[age=5,*]` | `melon_stem` | `105:5` |  |
| `minecraft:melon_stem[age=6,*]` | `melon_stem` | `105:6` |  |
| `minecraft:melon_stem[age=7,*]` | `melon_stem` | `105:7` |  |
| `minecraft:melon_stem[*]` | `melon_stem` | `105:0` |  |
| `minecraft:moss_block[*]` | `stone` | `1:0` | fallback |
| `minecraft:moss_carpet[*]` | `carpet` | `171:0` |  |
| `minecraft:mossy_cobblestone[*]` | `cobblestone` | `4:0` |  |
| `minecraft:mossy_cobblestone_slab[type=bottom,*]` | `stone_slab` | `44:3` |  |
| `minecraft:mossy_cobblestone_slab[type=top,*]` | `stone_slab` | `44:11` |  |
| `minecraft:mossy_cobblestone_slab[type=double,*]` | `stone_slab` | `43:3` | double slab |
| `minecraft:mossy_cobblestone_slab[*]` | `stone_slab` | `44:3` |  |
| `minecraft:mossy_cobblestone_stairs[facing=east,half=bottom,*]` | `cobblestone_stairs` | `67:0` |  |
| `minecraft:mossy_cobblestone_stairs[facing=east,half=top,*]` | `cobblestone_stairs` | `67:4` |  |
| `minecraft:mossy_cobblestone_stairs[facing=west,half=bottom,*]` | `cobblestone_stairs` | `67:1` |  |
| `minecraft:mossy_cobblestone_stairs[facing=west,half=top,*]` | `cobblestone_stairs` | `67:5` |  |
| `minecraft:mossy_cobblestone_stairs[facing=south,half=bottom,*]` | `cobblestone_stairs` | `67:2` |  |
| `minecraft:mossy_cobblestone_stairs[facing=south,half=top,*]` | `cobblestone_stairs` | `67:6` |  |
| `minecraft:mossy_cobblestone_stairs[facing=north,half=bottom,*]` | `cobblestone_stairs` | `67:3` |  |
| `minecraft:mossy_cobblestone_stairs[facing=north,half=top,*]` | `cobblestone_stairs` | `67:7` |  |
| `minecraft:mossy_cobblestone_stairs[*]` | `cobblestone_stairs` | `67:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:mossy_cobblestone_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:mossy_stone_brick_slab[type=bottom,*]` | `stone_slab` | `44:4` |  |
| `minecraft:mossy_stone_brick_slab[type=top,*]` | `stone_slab` | `44:12` |  |
| `minecraft:mossy_stone_brick_slab[type=double,*]` | `stone_slab` | `43:4` | double slab |
| `minecraft:mossy_stone_brick_slab[*]` | `stone_slab` | `44:4` |  |
| `minecraft:mossy_stone_brick_stairs[facing=east,half=bottom,*]` | `brick_stairs` | `108:0` |  |
| `minecraft:mossy_stone_brick_stairs[facing=east,half=top,*]` | `brick_stairs` | `108:4` |  |
| `minecraft:mossy_stone_brick_stairs[facing=west,half=bottom,*]` | `brick_stairs` | `108:1` |  |
| `minecraft:mossy_stone_brick_stairs[facing=west,half=top,*]` | `brick_stairs` | `108:5` |  |
| `minecraft:mossy_stone_brick_stairs[facing=south,half=bottom,*]` | `brick_stairs` | `108:2` |  |
| `minecraft:mossy_stone_brick_stairs[facing=south,half=top,*]` | `brick_stairs` | `108:6` |  |
| `minecraft:mossy_stone_brick_stairs[facing=north,half=bottom,*]` | `brick_stairs` | `108:3` |  |
| `minecraft:mossy_stone_brick_stairs[facing=north,half=top,*]` | `brick_stairs` | `108:7` |  |
| `minecraft:mossy_stone_brick_stairs[*]` | `brick_stairs` | `108:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:mossy_stone_brick_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:mossy_stone_bricks[*]` | `stonebrick` | `98:0` |  |
| `minecraft:moving_piston[facing=down,extended=false,*]` | `piston` | `33:0` |  |
| `minecraft:moving_piston[facing=down,extended=true,*]` | `piston` | `33:8` |  |
| `minecraft:moving_piston[facing=up,extended=false,*]` | `piston` | `33:1` |  |
| `minecraft:moving_piston[facing=up,extended=true,*]` | `piston` | `33:9` |  |
| `minecraft:moving_piston[facing=north,extended=false,*]` | `piston` | `33:2` |  |
| `minecraft:moving_piston[facing=north,extended=true,*]` | `piston` | `33:10` |  |
| `minecraft:moving_piston[facing=south,extended=false,*]` | `piston` | `33:3` |  |
| `minecraft:moving_piston[facing=south,extended=true,*]` | `piston` | `33:11` |  |
| `minecraft:moving_piston[facing=west,extended=false,*]` | `piston` | `33:4` |  |
| `minecraft:moving_piston[facing=west,extended=true,*]` | `piston` | `33:12` |  |
| `minecraft:moving_piston[facing=east,extended=false,*]` | `piston` | `33:5` |  |
| `minecraft:moving_piston[facing=east,extended=true,*]` | `piston` | `33:13` |  |
| `minecraft:moving_piston[*]` | `piston` | `33:2` |  |
| `minecraft:mud[*]` | `dirt` | `3:0` |  |
| `minecraft:mud_brick_slab[type=bottom,*]` | `stone_slab` | `44:4` |  |
| `minecraft:mud_brick_slab[type=top,*]` | `stone_slab` | `44:12` |  |
| `minecraft:mud_brick_slab[type=double,*]` | `stone_slab` | `43:4` | double slab |
| `minecraft:mud_brick_slab[*]` | `stone_slab` | `44:4` |  |
| `minecraft:mud_brick_stairs[facing=east,half=bottom,*]` | `brick_stairs` | `108:0` |  |
| `minecraft:mud_brick_stairs[facing=east,half=top,*]` | `brick_stairs` | `108:4` |  |
| `minecraft:mud_brick_stairs[facing=west,half=bottom,*]` | `brick_stairs` | `108:1` |  |
| `minecraft:mud_brick_stairs[facing=west,half=top,*]` | `brick_stairs` | `108:5` |  |
| `minecraft:mud_brick_stairs[facing=south,half=bottom,*]` | `brick_stairs` | `108:2` |  |
| `minecraft:mud_brick_stairs[facing=south,half=top,*]` | `brick_stairs` | `108:6` |  |
| `minecraft:mud_brick_stairs[facing=north,half=bottom,*]` | `brick_stairs` | `108:3` |  |
| `minecraft:mud_brick_stairs[facing=north,half=top,*]` | `brick_stairs` | `108:7` |  |
| `minecraft:mud_brick_stairs[*]` | `brick_stairs` | `108:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:mud_brick_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:mud_bricks[*]` | `brick_block` | `45:0` |  |
| `minecraft:muddy_mangrove_roots[*]` | `dirt` | `3:0` |  |
| `minecraft:mushroom_stem[*]` | `brown_mushroom_block` | `99:0` |  |
| `minecraft:mycelium[*]` | `mycelium` | `110:0` |  |
| `minecraft:nether_brick_fence[*]` | `fence` | `85:0` |  |
| `minecraft:nether_brick_slab[type=bottom,*]` | `stone_slab` | `44:6` |  |
| `minecraft:nether_brick_slab[type=top,*]` | `stone_slab` | `44:14` |  |
| `minecraft:nether_brick_slab[type=double,*]` | `stone_slab` | `43:6` | double slab |
| `minecraft:nether_brick_slab[*]` | `stone_slab` | `44:6` |  |
| `minecraft:nether_brick_stairs[facing=east,half=bottom,*]` | `nether_brick_stairs` | `114:0` |  |
| `minecraft:nether_brick_stairs[facing=east,half=top,*]` | `nether_brick_stairs` | `114:4` |  |
| `minecraft:nether_brick_stairs[facing=west,half=bottom,*]` | `nether_brick_stairs` | `114:1` |  |
| `minecraft:nether_brick_stairs[facing=west,half=top,*]` | `nether_brick_stairs` | `114:5` |  |
| `minecraft:nether_brick_stairs[facing=south,half=bottom,*]` | `nether_brick_stairs` | `114:2` |  |
| `minecraft:nether_brick_stairs[facing=south,half=top,*]` | `nether_brick_stairs` | `114:6` |  |
| `minecraft:nether_brick_stairs[facing=north,half=bottom,*]` | `nether_brick_stairs` | `114:3` |  |
| `minecraft:nether_brick_stairs[facing=north,half=top,*]` | `nether_brick_stairs` | `114:7` |  |
| `minecraft:nether_brick_stairs[*]` | `nether_brick_stairs` | `114:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:nether_brick_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:nether_bricks[*]` | `nether_brick` | `112:0` |  |
| `minecraft:nether_gold_ore[*]` | `gold_ore` | `14:0` |  |
| `minecraft:nether_portal[*]` | `portal` | `90:0` |  |
| `minecraft:nether_quartz_ore[*]` | `quartz_ore` | `153:0` |  |
| `minecraft:nether_sprouts[*]` | `stone` | `1:0` | fallback |
| `minecraft:nether_wart[age=0,*]` | `nether_wart` | `115:0` |  |
| `minecraft:nether_wart[age=1,*]` | `nether_wart` | `115:1` |  |
| `minecraft:nether_wart[age=2,*]` | `nether_wart` | `115:2` |  |
| `minecraft:nether_wart[age=3,*]` | `nether_wart` | `115:3` |  |
| `minecraft:nether_wart[age=4,*]` | `nether_wart` | `115:3` | ages above 3 clamp to mature |
| `minecraft:nether_wart[age=5,*]` | `nether_wart` | `115:3` | ages above 3 clamp to mature |
| `minecraft:nether_wart[age=6,*]` | `nether_wart` | `115:3` | ages above 3 clamp to mature |
| `minecraft:nether_wart[age=7,*]` | `nether_wart` | `115:3` | ages above 3 clamp to mature |
| `minecraft:nether_wart[*]` | `nether_wart` | `115:0` |  |
| `minecraft:nether_wart_block[*]` | `stone` | `1:0` | fallback |
| `minecraft:netherite_block[*]` | `stone` | `1:0` | fallback |
| `minecraft:netherrack[*]` | `netherrack` | `87:0` |  |
| `minecraft:note_block[*]` | `note_block` | `25:0` |  |
| `minecraft:oak_button[face=floor,*]` | `wooden_button` | `143:1` |  |
| `minecraft:oak_button[face=wall,facing=east,*]` | `wooden_button` | `143:2` |  |
| `minecraft:oak_button[face=wall,facing=west,*]` | `wooden_button` | `143:1` |  |
| `minecraft:oak_button[face=wall,facing=south,*]` | `wooden_button` | `143:3` |  |
| `minecraft:oak_button[face=wall,facing=north,*]` | `wooden_button` | `143:4` |  |
| `minecraft:oak_button[powered=true,*]` | `wooden_button` | `143:9` | powered bit approximated (+8) |
| `minecraft:oak_button[*]` | `wooden_button` | `143:1` |  |
| `minecraft:oak_door[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:oak_door[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:oak_door[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:oak_door[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:oak_door[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:oak_door[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:oak_door[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:oak_door[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:oak_door[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:oak_door[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:oak_door[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:oak_fence[*]` | `fence` | `85:0` |  |
| `minecraft:oak_fence_gate[facing=south,open=false,*]` | `fence_gate` | `107:0` |  |
| `minecraft:oak_fence_gate[facing=south,open=true,*]` | `fence_gate` | `107:4` |  |
| `minecraft:oak_fence_gate[facing=west,open=false,*]` | `fence_gate` | `107:1` |  |
| `minecraft:oak_fence_gate[facing=west,open=true,*]` | `fence_gate` | `107:5` |  |
| `minecraft:oak_fence_gate[facing=north,open=false,*]` | `fence_gate` | `107:2` |  |
| `minecraft:oak_fence_gate[facing=north,open=true,*]` | `fence_gate` | `107:6` |  |
| `minecraft:oak_fence_gate[facing=east,open=false,*]` | `fence_gate` | `107:3` |  |
| `minecraft:oak_fence_gate[facing=east,open=true,*]` | `fence_gate` | `107:7` |  |
| `minecraft:oak_fence_gate[*]` | `fence_gate` | `107:0` |  |
| `minecraft:oak_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:oak_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:oak_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:oak_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:oak_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:oak_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:oak_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:oak_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:oak_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:oak_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:oak_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:oak_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:oak_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:oak_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:oak_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:oak_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:oak_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:oak_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:oak_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:oak_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:oak_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:oak_leaves[*]` | `leaves` | `18:0` |  |
| `minecraft:oak_log[axis=y,*]` | `log` | `17:0` |  |
| `minecraft:oak_log[axis=x,*]` | `log` | `17:4` |  |
| `minecraft:oak_log[axis=z,*]` | `log` | `17:8` |  |
| `minecraft:oak_log[*]` | `log` | `17:0` |  |
| `minecraft:oak_planks[*]` | `planks` | `5:0` |  |
| `minecraft:oak_pressure_plate[*]` | `wooden_pressure_plate` | `72:0` |  |
| `minecraft:oak_sapling[*]` | `sapling` | `6:0` |  |
| `minecraft:oak_shelf[*]` | `stone` | `1:0` | fallback |
| `minecraft:oak_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:oak_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:oak_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:oak_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:oak_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:oak_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:oak_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:oak_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:oak_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:oak_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:oak_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:oak_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:oak_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:oak_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:oak_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:oak_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:oak_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:oak_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:oak_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:oak_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:oak_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:oak_slab[type=bottom,*]` | `wooden_slab` | `126:0` |  |
| `minecraft:oak_slab[type=top,*]` | `wooden_slab` | `126:8` |  |
| `minecraft:oak_slab[type=double,*]` | `wooden_slab` | `125:0` | double slab |
| `minecraft:oak_slab[*]` | `wooden_slab` | `126:0` |  |
| `minecraft:oak_stairs[facing=east,half=bottom,*]` | `oak_stairs` | `53:0` |  |
| `minecraft:oak_stairs[facing=east,half=top,*]` | `oak_stairs` | `53:4` |  |
| `minecraft:oak_stairs[facing=west,half=bottom,*]` | `oak_stairs` | `53:1` |  |
| `minecraft:oak_stairs[facing=west,half=top,*]` | `oak_stairs` | `53:5` |  |
| `minecraft:oak_stairs[facing=south,half=bottom,*]` | `oak_stairs` | `53:2` |  |
| `minecraft:oak_stairs[facing=south,half=top,*]` | `oak_stairs` | `53:6` |  |
| `minecraft:oak_stairs[facing=north,half=bottom,*]` | `oak_stairs` | `53:3` |  |
| `minecraft:oak_stairs[facing=north,half=top,*]` | `oak_stairs` | `53:7` |  |
| `minecraft:oak_stairs[*]` | `oak_stairs` | `53:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:oak_trapdoor[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:oak_trapdoor[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:oak_trapdoor[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:oak_trapdoor[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:oak_trapdoor[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:oak_trapdoor[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:oak_trapdoor[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:oak_trapdoor[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:oak_trapdoor[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:oak_trapdoor[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:oak_trapdoor[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:oak_wall_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:oak_wall_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:oak_wall_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:oak_wall_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:oak_wall_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:oak_wall_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:oak_wall_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:oak_wall_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:oak_wall_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:oak_wall_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:oak_wall_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:oak_wall_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:oak_wall_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:oak_wall_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:oak_wall_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:oak_wall_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:oak_wall_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:oak_wall_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:oak_wall_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:oak_wall_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:oak_wall_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:oak_wall_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:oak_wall_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:oak_wall_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:oak_wall_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:oak_wall_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:oak_wall_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:oak_wall_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:oak_wall_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:oak_wall_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:oak_wall_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:oak_wall_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:oak_wall_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:oak_wall_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:oak_wall_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:oak_wall_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:oak_wall_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:oak_wall_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:oak_wall_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:oak_wall_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:oak_wall_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:oak_wall_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:oak_wood[axis=y,*]` | `log` | `17:0` |  |
| `minecraft:oak_wood[axis=x,*]` | `log` | `17:4` |  |
| `minecraft:oak_wood[axis=z,*]` | `log` | `17:8` |  |
| `minecraft:oak_wood[*]` | `log` | `17:0` |  |
| `minecraft:observer[facing=down,*]` | `dispenser` | `23:0` | modern logic block collapsed to dispenser |
| `minecraft:observer[facing=up,*]` | `dispenser` | `23:1` | modern logic block collapsed to dispenser |
| `minecraft:observer[facing=north,*]` | `dispenser` | `23:2` | modern logic block collapsed to dispenser |
| `minecraft:observer[facing=south,*]` | `dispenser` | `23:3` | modern logic block collapsed to dispenser |
| `minecraft:observer[facing=west,*]` | `dispenser` | `23:4` | modern logic block collapsed to dispenser |
| `minecraft:observer[facing=east,*]` | `dispenser` | `23:5` | modern logic block collapsed to dispenser |
| `minecraft:observer[*]` | `dispenser` | `23:2` | modern logic block collapsed to dispenser |
| `minecraft:obsidian[*]` | `obsidian` | `49:0` |  |
| `minecraft:ochre_froglight[*]` | `glowstone` | `89:0` |  |
| `minecraft:open_eyeblossom[*]` | `red_flower` | `38:0` |  |
| `minecraft:orange_banner[*]` | `wool` | `35:1` | banner collapsed to wool |
| `minecraft:orange_bed[part=foot,facing=south,occupied=false,*]` | `bed` | `26:0` | bed color ignored |
| `minecraft:orange_bed[part=head,facing=south,occupied=false,*]` | `bed` | `26:8` | bed color ignored |
| `minecraft:orange_bed[part=foot,facing=south,occupied=true,*]` | `bed` | `26:4` | occupied bit; color ignored |
| `minecraft:orange_bed[part=head,facing=south,occupied=true,*]` | `bed` | `26:12` | occupied+head bits; color ignored |
| `minecraft:orange_bed[part=foot,facing=west,occupied=false,*]` | `bed` | `26:1` | bed color ignored |
| `minecraft:orange_bed[part=head,facing=west,occupied=false,*]` | `bed` | `26:9` | bed color ignored |
| `minecraft:orange_bed[part=foot,facing=west,occupied=true,*]` | `bed` | `26:5` | occupied bit; color ignored |
| `minecraft:orange_bed[part=head,facing=west,occupied=true,*]` | `bed` | `26:13` | occupied+head bits; color ignored |
| `minecraft:orange_bed[part=foot,facing=north,occupied=false,*]` | `bed` | `26:2` | bed color ignored |
| `minecraft:orange_bed[part=head,facing=north,occupied=false,*]` | `bed` | `26:10` | bed color ignored |
| `minecraft:orange_bed[part=foot,facing=north,occupied=true,*]` | `bed` | `26:6` | occupied bit; color ignored |
| `minecraft:orange_bed[part=head,facing=north,occupied=true,*]` | `bed` | `26:14` | occupied+head bits; color ignored |
| `minecraft:orange_bed[part=foot,facing=east,occupied=false,*]` | `bed` | `26:3` | bed color ignored |
| `minecraft:orange_bed[part=head,facing=east,occupied=false,*]` | `bed` | `26:11` | bed color ignored |
| `minecraft:orange_bed[part=foot,facing=east,occupied=true,*]` | `bed` | `26:7` | occupied bit; color ignored |
| `minecraft:orange_bed[part=head,facing=east,occupied=true,*]` | `bed` | `26:15` | occupied+head bits; color ignored |
| `minecraft:orange_bed[*]` | `bed` | `26:0` | legacy bed ignores color |
| `minecraft:orange_candle[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:orange_candle_cake[bites=0,*]` | `cake` | `92:0` |  |
| `minecraft:orange_candle_cake[bites=1,*]` | `cake` | `92:1` |  |
| `minecraft:orange_candle_cake[bites=2,*]` | `cake` | `92:2` |  |
| `minecraft:orange_candle_cake[bites=3,*]` | `cake` | `92:3` |  |
| `minecraft:orange_candle_cake[bites=4,*]` | `cake` | `92:4` |  |
| `minecraft:orange_candle_cake[bites=5,*]` | `cake` | `92:5` |  |
| `minecraft:orange_candle_cake[bites=6,*]` | `cake` | `92:6` |  |
| `minecraft:orange_candle_cake[*]` | `cake` | `92:0` |  |
| `minecraft:orange_carpet[*]` | `carpet` | `171:1` |  |
| `minecraft:orange_concrete[*]` | `stained_hardened_clay` | `159:1` |  |
| `minecraft:orange_concrete_powder[*]` | `stained_hardened_clay` | `159:1` |  |
| `minecraft:orange_glazed_terracotta[*]` | `stained_hardened_clay` | `159:1` |  |
| `minecraft:orange_shulker_box[*]` | `wool` | `35:1` | shulker box collapsed to wool |
| `minecraft:orange_stained_glass[*]` | `stained_glass` | `95:1` |  |
| `minecraft:orange_stained_glass_pane[*]` | `stained_glass_pane` | `160:1` |  |
| `minecraft:orange_terracotta[*]` | `stained_hardened_clay` | `159:1` |  |
| `minecraft:orange_tulip[*]` | `stone` | `1:0` | fallback |
| `minecraft:orange_wall_banner[*]` | `wool` | `35:1` | banner collapsed to wool |
| `minecraft:orange_wool[*]` | `wool` | `35:1` |  |
| `minecraft:oxeye_daisy[*]` | `red_flower` | `38:0` |  |
| `minecraft:oxidized_chiseled_copper[*]` | `iron_block` | `42:0` |  |
| `minecraft:oxidized_copper[*]` | `iron_block` | `42:0` |  |
| `minecraft:oxidized_copper_bars[*]` | `iron_block` | `42:0` |  |
| `minecraft:oxidized_copper_bulb[lit=false,*]` | `redstone_lamp` | `123:0` |  |
| `minecraft:oxidized_copper_bulb[lit=true,*]` | `redstone_lamp` | `124:0` | lit redstone lamp |
| `minecraft:oxidized_copper_bulb[*]` | `redstone_lamp` | `123:0` |  |
| `minecraft:oxidized_copper_chain[*]` | `iron_block` | `42:0` |  |
| `minecraft:oxidized_copper_chest[*]` | `iron_block` | `42:0` |  |
| `minecraft:oxidized_copper_door[half=lower,facing=east,open=false,*]` | `iron_door` | `71:0` |  |
| `minecraft:oxidized_copper_door[half=lower,facing=east,open=true,*]` | `iron_door` | `71:4` |  |
| `minecraft:oxidized_copper_door[half=lower,facing=south,open=false,*]` | `iron_door` | `71:1` |  |
| `minecraft:oxidized_copper_door[half=lower,facing=south,open=true,*]` | `iron_door` | `71:5` |  |
| `minecraft:oxidized_copper_door[half=lower,facing=west,open=false,*]` | `iron_door` | `71:2` |  |
| `minecraft:oxidized_copper_door[half=lower,facing=west,open=true,*]` | `iron_door` | `71:6` |  |
| `minecraft:oxidized_copper_door[half=lower,facing=north,open=false,*]` | `iron_door` | `71:3` |  |
| `minecraft:oxidized_copper_door[half=lower,facing=north,open=true,*]` | `iron_door` | `71:7` |  |
| `minecraft:oxidized_copper_door[half=upper,hinge=left,*]` | `iron_door` | `71:8` | upper half |
| `minecraft:oxidized_copper_door[half=upper,hinge=right,*]` | `iron_door` | `71:9` | upper half |
| `minecraft:oxidized_copper_door[*]` | `iron_door` | `71:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:oxidized_copper_golem_statue[*]` | `iron_block` | `42:0` |  |
| `minecraft:oxidized_copper_grate[*]` | `iron_bars` | `101:0` |  |
| `minecraft:oxidized_copper_lantern[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:oxidized_copper_trapdoor[half=lower,facing=east,open=false,*]` | `iron_door` | `71:0` |  |
| `minecraft:oxidized_copper_trapdoor[half=lower,facing=east,open=true,*]` | `iron_door` | `71:4` |  |
| `minecraft:oxidized_copper_trapdoor[half=lower,facing=south,open=false,*]` | `iron_door` | `71:1` |  |
| `minecraft:oxidized_copper_trapdoor[half=lower,facing=south,open=true,*]` | `iron_door` | `71:5` |  |
| `minecraft:oxidized_copper_trapdoor[half=lower,facing=west,open=false,*]` | `iron_door` | `71:2` |  |
| `minecraft:oxidized_copper_trapdoor[half=lower,facing=west,open=true,*]` | `iron_door` | `71:6` |  |
| `minecraft:oxidized_copper_trapdoor[half=lower,facing=north,open=false,*]` | `iron_door` | `71:3` |  |
| `minecraft:oxidized_copper_trapdoor[half=lower,facing=north,open=true,*]` | `iron_door` | `71:7` |  |
| `minecraft:oxidized_copper_trapdoor[half=upper,hinge=left,*]` | `iron_door` | `71:8` | upper half |
| `minecraft:oxidized_copper_trapdoor[half=upper,hinge=right,*]` | `iron_door` | `71:9` | upper half |
| `minecraft:oxidized_copper_trapdoor[*]` | `iron_door` | `71:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:oxidized_cut_copper[*]` | `iron_block` | `42:0` |  |
| `minecraft:oxidized_cut_copper_slab[type=bottom,*]` | `stone_slab` | `44:0` |  |
| `minecraft:oxidized_cut_copper_slab[type=top,*]` | `stone_slab` | `44:8` |  |
| `minecraft:oxidized_cut_copper_slab[type=double,*]` | `stone_slab` | `43:0` | double slab |
| `minecraft:oxidized_cut_copper_slab[*]` | `stone_slab` | `44:0` |  |
| `minecraft:oxidized_cut_copper_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:oxidized_cut_copper_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:oxidized_cut_copper_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:oxidized_cut_copper_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:oxidized_cut_copper_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:oxidized_cut_copper_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:oxidized_cut_copper_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:oxidized_cut_copper_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:oxidized_cut_copper_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:oxidized_lightning_rod[*]` | `stone` | `1:0` | fallback |
| `minecraft:packed_ice[*]` | `packed_ice` | `174:0` |  |
| `minecraft:packed_mud[*]` | `dirt` | `3:0` |  |
| `minecraft:pale_hanging_moss[*]` | `stone` | `1:0` | fallback |
| `minecraft:pale_moss_block[*]` | `stone` | `1:0` | fallback |
| `minecraft:pale_moss_carpet[*]` | `carpet` | `171:0` |  |
| `minecraft:pale_oak_button[face=floor,*]` | `wooden_button` | `143:1` |  |
| `minecraft:pale_oak_button[face=wall,facing=east,*]` | `wooden_button` | `143:2` |  |
| `minecraft:pale_oak_button[face=wall,facing=west,*]` | `wooden_button` | `143:1` |  |
| `minecraft:pale_oak_button[face=wall,facing=south,*]` | `wooden_button` | `143:3` |  |
| `minecraft:pale_oak_button[face=wall,facing=north,*]` | `wooden_button` | `143:4` |  |
| `minecraft:pale_oak_button[powered=true,*]` | `wooden_button` | `143:9` | powered bit approximated (+8) |
| `minecraft:pale_oak_button[*]` | `wooden_button` | `143:1` |  |
| `minecraft:pale_oak_door[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:pale_oak_door[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:pale_oak_door[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:pale_oak_door[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:pale_oak_door[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:pale_oak_door[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:pale_oak_door[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:pale_oak_door[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:pale_oak_door[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:pale_oak_door[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:pale_oak_door[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:pale_oak_fence[*]` | `fence` | `85:0` |  |
| `minecraft:pale_oak_fence_gate[facing=south,open=false,*]` | `fence_gate` | `107:0` |  |
| `minecraft:pale_oak_fence_gate[facing=south,open=true,*]` | `fence_gate` | `107:4` |  |
| `minecraft:pale_oak_fence_gate[facing=west,open=false,*]` | `fence_gate` | `107:1` |  |
| `minecraft:pale_oak_fence_gate[facing=west,open=true,*]` | `fence_gate` | `107:5` |  |
| `minecraft:pale_oak_fence_gate[facing=north,open=false,*]` | `fence_gate` | `107:2` |  |
| `minecraft:pale_oak_fence_gate[facing=north,open=true,*]` | `fence_gate` | `107:6` |  |
| `minecraft:pale_oak_fence_gate[facing=east,open=false,*]` | `fence_gate` | `107:3` |  |
| `minecraft:pale_oak_fence_gate[facing=east,open=true,*]` | `fence_gate` | `107:7` |  |
| `minecraft:pale_oak_fence_gate[*]` | `fence_gate` | `107:0` |  |
| `minecraft:pale_oak_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:pale_oak_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:pale_oak_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:pale_oak_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:pale_oak_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:pale_oak_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:pale_oak_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:pale_oak_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:pale_oak_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:pale_oak_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:pale_oak_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:pale_oak_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:pale_oak_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:pale_oak_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:pale_oak_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:pale_oak_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:pale_oak_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:pale_oak_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:pale_oak_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:pale_oak_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:pale_oak_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:pale_oak_leaves[*]` | `leaves` | `18:1` |  |
| `minecraft:pale_oak_log[axis=y,*]` | `log` | `17:1` |  |
| `minecraft:pale_oak_log[axis=x,*]` | `log` | `17:5` |  |
| `minecraft:pale_oak_log[axis=z,*]` | `log` | `17:9` |  |
| `minecraft:pale_oak_log[*]` | `log` | `17:1` |  |
| `minecraft:pale_oak_planks[*]` | `planks` | `5:1` |  |
| `minecraft:pale_oak_pressure_plate[*]` | `wooden_pressure_plate` | `72:0` |  |
| `minecraft:pale_oak_sapling[*]` | `sapling` | `6:1` |  |
| `minecraft:pale_oak_shelf[*]` | `stone` | `1:0` | fallback |
| `minecraft:pale_oak_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:pale_oak_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:pale_oak_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:pale_oak_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:pale_oak_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:pale_oak_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:pale_oak_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:pale_oak_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:pale_oak_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:pale_oak_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:pale_oak_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:pale_oak_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:pale_oak_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:pale_oak_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:pale_oak_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:pale_oak_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:pale_oak_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:pale_oak_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:pale_oak_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:pale_oak_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:pale_oak_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:pale_oak_slab[type=bottom,*]` | `wooden_slab` | `126:1` |  |
| `minecraft:pale_oak_slab[type=top,*]` | `wooden_slab` | `126:9` |  |
| `minecraft:pale_oak_slab[type=double,*]` | `wooden_slab` | `125:1` | double slab |
| `minecraft:pale_oak_slab[*]` | `wooden_slab` | `126:1` |  |
| `minecraft:pale_oak_stairs[facing=east,half=bottom,*]` | `spruce_stairs` | `134:0` |  |
| `minecraft:pale_oak_stairs[facing=east,half=top,*]` | `spruce_stairs` | `134:4` |  |
| `minecraft:pale_oak_stairs[facing=west,half=bottom,*]` | `spruce_stairs` | `134:1` |  |
| `minecraft:pale_oak_stairs[facing=west,half=top,*]` | `spruce_stairs` | `134:5` |  |
| `minecraft:pale_oak_stairs[facing=south,half=bottom,*]` | `spruce_stairs` | `134:2` |  |
| `minecraft:pale_oak_stairs[facing=south,half=top,*]` | `spruce_stairs` | `134:6` |  |
| `minecraft:pale_oak_stairs[facing=north,half=bottom,*]` | `spruce_stairs` | `134:3` |  |
| `minecraft:pale_oak_stairs[facing=north,half=top,*]` | `spruce_stairs` | `134:7` |  |
| `minecraft:pale_oak_stairs[*]` | `spruce_stairs` | `134:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:pale_oak_trapdoor[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:pale_oak_trapdoor[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:pale_oak_trapdoor[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:pale_oak_trapdoor[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:pale_oak_trapdoor[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:pale_oak_trapdoor[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:pale_oak_trapdoor[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:pale_oak_trapdoor[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:pale_oak_trapdoor[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:pale_oak_trapdoor[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:pale_oak_trapdoor[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:pale_oak_wall_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:pale_oak_wall_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:pale_oak_wall_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:pale_oak_wall_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:pale_oak_wall_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:pale_oak_wall_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:pale_oak_wall_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:pale_oak_wall_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:pale_oak_wall_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:pale_oak_wall_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:pale_oak_wall_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:pale_oak_wall_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:pale_oak_wall_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:pale_oak_wall_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:pale_oak_wall_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:pale_oak_wall_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:pale_oak_wall_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:pale_oak_wall_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:pale_oak_wall_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:pale_oak_wall_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:pale_oak_wall_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:pale_oak_wall_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:pale_oak_wall_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:pale_oak_wall_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:pale_oak_wall_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:pale_oak_wall_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:pale_oak_wall_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:pale_oak_wall_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:pale_oak_wall_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:pale_oak_wall_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:pale_oak_wall_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:pale_oak_wall_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:pale_oak_wall_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:pale_oak_wall_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:pale_oak_wall_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:pale_oak_wall_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:pale_oak_wall_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:pale_oak_wall_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:pale_oak_wall_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:pale_oak_wall_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:pale_oak_wall_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:pale_oak_wall_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:pale_oak_wood[axis=y,*]` | `log` | `17:1` |  |
| `minecraft:pale_oak_wood[axis=x,*]` | `log` | `17:5` |  |
| `minecraft:pale_oak_wood[axis=z,*]` | `log` | `17:9` |  |
| `minecraft:pale_oak_wood[*]` | `log` | `17:1` |  |
| `minecraft:pearlescent_froglight[*]` | `glowstone` | `89:0` |  |
| `minecraft:peony[*]` | `stone` | `1:0` | fallback |
| `minecraft:petrified_oak_slab[type=bottom,*]` | `wooden_slab` | `126:0` |  |
| `minecraft:petrified_oak_slab[type=top,*]` | `wooden_slab` | `126:8` |  |
| `minecraft:petrified_oak_slab[type=double,*]` | `wooden_slab` | `125:0` | double slab |
| `minecraft:petrified_oak_slab[*]` | `wooden_slab` | `126:0` |  |
| `minecraft:piglin_head[rotation=0,*]` | `mob_head` | `144:0` | standing head |
| `minecraft:piglin_head[rotation=1,*]` | `mob_head` | `144:1` | standing head |
| `minecraft:piglin_head[rotation=2,*]` | `mob_head` | `144:2` | standing head |
| `minecraft:piglin_head[rotation=3,*]` | `mob_head` | `144:3` | standing head |
| `minecraft:piglin_head[rotation=4,*]` | `mob_head` | `144:4` | standing head |
| `minecraft:piglin_head[rotation=5,*]` | `mob_head` | `144:5` | standing head |
| `minecraft:piglin_head[rotation=6,*]` | `mob_head` | `144:6` | standing head |
| `minecraft:piglin_head[rotation=7,*]` | `mob_head` | `144:7` | standing head |
| `minecraft:piglin_head[rotation=8,*]` | `mob_head` | `144:8` | standing head |
| `minecraft:piglin_head[rotation=9,*]` | `mob_head` | `144:9` | standing head |
| `minecraft:piglin_head[rotation=10,*]` | `mob_head` | `144:10` | standing head |
| `minecraft:piglin_head[rotation=11,*]` | `mob_head` | `144:11` | standing head |
| `minecraft:piglin_head[rotation=12,*]` | `mob_head` | `144:12` | standing head |
| `minecraft:piglin_head[rotation=13,*]` | `mob_head` | `144:13` | standing head |
| `minecraft:piglin_head[rotation=14,*]` | `mob_head` | `144:14` | standing head |
| `minecraft:piglin_head[rotation=15,*]` | `mob_head` | `144:15` | standing head |
| `minecraft:piglin_head[facing=north,*]` | `mob_head` | `144:2` | wall head |
| `minecraft:piglin_head[facing=south,*]` | `mob_head` | `144:3` | wall head |
| `minecraft:piglin_head[facing=west,*]` | `mob_head` | `144:4` | wall head |
| `minecraft:piglin_head[facing=east,*]` | `mob_head` | `144:5` | wall head |
| `minecraft:piglin_head[*]` | `mob_head` | `144:0` | head type collapsed |
| `minecraft:piglin_wall_head[rotation=0,*]` | `mob_head` | `144:0` | standing head |
| `minecraft:piglin_wall_head[rotation=1,*]` | `mob_head` | `144:1` | standing head |
| `minecraft:piglin_wall_head[rotation=2,*]` | `mob_head` | `144:2` | standing head |
| `minecraft:piglin_wall_head[rotation=3,*]` | `mob_head` | `144:3` | standing head |
| `minecraft:piglin_wall_head[rotation=4,*]` | `mob_head` | `144:4` | standing head |
| `minecraft:piglin_wall_head[rotation=5,*]` | `mob_head` | `144:5` | standing head |
| `minecraft:piglin_wall_head[rotation=6,*]` | `mob_head` | `144:6` | standing head |
| `minecraft:piglin_wall_head[rotation=7,*]` | `mob_head` | `144:7` | standing head |
| `minecraft:piglin_wall_head[rotation=8,*]` | `mob_head` | `144:8` | standing head |
| `minecraft:piglin_wall_head[rotation=9,*]` | `mob_head` | `144:9` | standing head |
| `minecraft:piglin_wall_head[rotation=10,*]` | `mob_head` | `144:10` | standing head |
| `minecraft:piglin_wall_head[rotation=11,*]` | `mob_head` | `144:11` | standing head |
| `minecraft:piglin_wall_head[rotation=12,*]` | `mob_head` | `144:12` | standing head |
| `minecraft:piglin_wall_head[rotation=13,*]` | `mob_head` | `144:13` | standing head |
| `minecraft:piglin_wall_head[rotation=14,*]` | `mob_head` | `144:14` | standing head |
| `minecraft:piglin_wall_head[rotation=15,*]` | `mob_head` | `144:15` | standing head |
| `minecraft:piglin_wall_head[facing=north,*]` | `mob_head` | `144:2` | wall head |
| `minecraft:piglin_wall_head[facing=south,*]` | `mob_head` | `144:3` | wall head |
| `minecraft:piglin_wall_head[facing=west,*]` | `mob_head` | `144:4` | wall head |
| `minecraft:piglin_wall_head[facing=east,*]` | `mob_head` | `144:5` | wall head |
| `minecraft:piglin_wall_head[*]` | `mob_head` | `144:0` | head type collapsed |
| `minecraft:pink_banner[*]` | `wool` | `35:6` | banner collapsed to wool |
| `minecraft:pink_bed[part=foot,facing=south,occupied=false,*]` | `bed` | `26:0` | bed color ignored |
| `minecraft:pink_bed[part=head,facing=south,occupied=false,*]` | `bed` | `26:8` | bed color ignored |
| `minecraft:pink_bed[part=foot,facing=south,occupied=true,*]` | `bed` | `26:4` | occupied bit; color ignored |
| `minecraft:pink_bed[part=head,facing=south,occupied=true,*]` | `bed` | `26:12` | occupied+head bits; color ignored |
| `minecraft:pink_bed[part=foot,facing=west,occupied=false,*]` | `bed` | `26:1` | bed color ignored |
| `minecraft:pink_bed[part=head,facing=west,occupied=false,*]` | `bed` | `26:9` | bed color ignored |
| `minecraft:pink_bed[part=foot,facing=west,occupied=true,*]` | `bed` | `26:5` | occupied bit; color ignored |
| `minecraft:pink_bed[part=head,facing=west,occupied=true,*]` | `bed` | `26:13` | occupied+head bits; color ignored |
| `minecraft:pink_bed[part=foot,facing=north,occupied=false,*]` | `bed` | `26:2` | bed color ignored |
| `minecraft:pink_bed[part=head,facing=north,occupied=false,*]` | `bed` | `26:10` | bed color ignored |
| `minecraft:pink_bed[part=foot,facing=north,occupied=true,*]` | `bed` | `26:6` | occupied bit; color ignored |
| `minecraft:pink_bed[part=head,facing=north,occupied=true,*]` | `bed` | `26:14` | occupied+head bits; color ignored |
| `minecraft:pink_bed[part=foot,facing=east,occupied=false,*]` | `bed` | `26:3` | bed color ignored |
| `minecraft:pink_bed[part=head,facing=east,occupied=false,*]` | `bed` | `26:11` | bed color ignored |
| `minecraft:pink_bed[part=foot,facing=east,occupied=true,*]` | `bed` | `26:7` | occupied bit; color ignored |
| `minecraft:pink_bed[part=head,facing=east,occupied=true,*]` | `bed` | `26:15` | occupied+head bits; color ignored |
| `minecraft:pink_bed[*]` | `bed` | `26:0` | legacy bed ignores color |
| `minecraft:pink_candle[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:pink_candle_cake[bites=0,*]` | `cake` | `92:0` |  |
| `minecraft:pink_candle_cake[bites=1,*]` | `cake` | `92:1` |  |
| `minecraft:pink_candle_cake[bites=2,*]` | `cake` | `92:2` |  |
| `minecraft:pink_candle_cake[bites=3,*]` | `cake` | `92:3` |  |
| `minecraft:pink_candle_cake[bites=4,*]` | `cake` | `92:4` |  |
| `minecraft:pink_candle_cake[bites=5,*]` | `cake` | `92:5` |  |
| `minecraft:pink_candle_cake[bites=6,*]` | `cake` | `92:6` |  |
| `minecraft:pink_candle_cake[*]` | `cake` | `92:0` |  |
| `minecraft:pink_carpet[*]` | `carpet` | `171:6` |  |
| `minecraft:pink_concrete[*]` | `stained_hardened_clay` | `159:6` |  |
| `minecraft:pink_concrete_powder[*]` | `stained_hardened_clay` | `159:6` |  |
| `minecraft:pink_glazed_terracotta[*]` | `stained_hardened_clay` | `159:6` |  |
| `minecraft:pink_petals[*]` | `stone` | `1:0` | fallback |
| `minecraft:pink_shulker_box[*]` | `wool` | `35:6` | shulker box collapsed to wool |
| `minecraft:pink_stained_glass[*]` | `stained_glass` | `95:6` |  |
| `minecraft:pink_stained_glass_pane[*]` | `stained_glass_pane` | `160:6` |  |
| `minecraft:pink_terracotta[*]` | `stained_hardened_clay` | `159:6` |  |
| `minecraft:pink_tulip[*]` | `stone` | `1:0` | fallback |
| `minecraft:pink_wall_banner[*]` | `wool` | `35:6` | banner collapsed to wool |
| `minecraft:pink_wool[*]` | `wool` | `35:6` |  |
| `minecraft:piston[facing=down,extended=false,*]` | `piston` | `33:0` |  |
| `minecraft:piston[facing=down,extended=true,*]` | `piston` | `33:8` |  |
| `minecraft:piston[facing=up,extended=false,*]` | `piston` | `33:1` |  |
| `minecraft:piston[facing=up,extended=true,*]` | `piston` | `33:9` |  |
| `minecraft:piston[facing=north,extended=false,*]` | `piston` | `33:2` |  |
| `minecraft:piston[facing=north,extended=true,*]` | `piston` | `33:10` |  |
| `minecraft:piston[facing=south,extended=false,*]` | `piston` | `33:3` |  |
| `minecraft:piston[facing=south,extended=true,*]` | `piston` | `33:11` |  |
| `minecraft:piston[facing=west,extended=false,*]` | `piston` | `33:4` |  |
| `minecraft:piston[facing=west,extended=true,*]` | `piston` | `33:12` |  |
| `minecraft:piston[facing=east,extended=false,*]` | `piston` | `33:5` |  |
| `minecraft:piston[facing=east,extended=true,*]` | `piston` | `33:13` |  |
| `minecraft:piston[*]` | `piston` | `33:2` |  |
| `minecraft:piston_head[facing=down,extended=false,*]` | `piston_extension` | `34:0` |  |
| `minecraft:piston_head[facing=down,extended=true,*]` | `piston_extension` | `34:8` |  |
| `minecraft:piston_head[facing=up,extended=false,*]` | `piston_extension` | `34:1` |  |
| `minecraft:piston_head[facing=up,extended=true,*]` | `piston_extension` | `34:9` |  |
| `minecraft:piston_head[facing=north,extended=false,*]` | `piston_extension` | `34:2` |  |
| `minecraft:piston_head[facing=north,extended=true,*]` | `piston_extension` | `34:10` |  |
| `minecraft:piston_head[facing=south,extended=false,*]` | `piston_extension` | `34:3` |  |
| `minecraft:piston_head[facing=south,extended=true,*]` | `piston_extension` | `34:11` |  |
| `minecraft:piston_head[facing=west,extended=false,*]` | `piston_extension` | `34:4` |  |
| `minecraft:piston_head[facing=west,extended=true,*]` | `piston_extension` | `34:12` |  |
| `minecraft:piston_head[facing=east,extended=false,*]` | `piston_extension` | `34:5` |  |
| `minecraft:piston_head[facing=east,extended=true,*]` | `piston_extension` | `34:13` |  |
| `minecraft:piston_head[*]` | `piston_extension` | `34:2` |  |
| `minecraft:pitcher_crop[*]` | `stone` | `1:0` | fallback |
| `minecraft:pitcher_plant[*]` | `stone` | `1:0` | fallback |
| `minecraft:player_head[rotation=0,*]` | `mob_head` | `144:0` | standing head |
| `minecraft:player_head[rotation=1,*]` | `mob_head` | `144:1` | standing head |
| `minecraft:player_head[rotation=2,*]` | `mob_head` | `144:2` | standing head |
| `minecraft:player_head[rotation=3,*]` | `mob_head` | `144:3` | standing head |
| `minecraft:player_head[rotation=4,*]` | `mob_head` | `144:4` | standing head |
| `minecraft:player_head[rotation=5,*]` | `mob_head` | `144:5` | standing head |
| `minecraft:player_head[rotation=6,*]` | `mob_head` | `144:6` | standing head |
| `minecraft:player_head[rotation=7,*]` | `mob_head` | `144:7` | standing head |
| `minecraft:player_head[rotation=8,*]` | `mob_head` | `144:8` | standing head |
| `minecraft:player_head[rotation=9,*]` | `mob_head` | `144:9` | standing head |
| `minecraft:player_head[rotation=10,*]` | `mob_head` | `144:10` | standing head |
| `minecraft:player_head[rotation=11,*]` | `mob_head` | `144:11` | standing head |
| `minecraft:player_head[rotation=12,*]` | `mob_head` | `144:12` | standing head |
| `minecraft:player_head[rotation=13,*]` | `mob_head` | `144:13` | standing head |
| `minecraft:player_head[rotation=14,*]` | `mob_head` | `144:14` | standing head |
| `minecraft:player_head[rotation=15,*]` | `mob_head` | `144:15` | standing head |
| `minecraft:player_head[facing=north,*]` | `mob_head` | `144:2` | wall head |
| `minecraft:player_head[facing=south,*]` | `mob_head` | `144:3` | wall head |
| `minecraft:player_head[facing=west,*]` | `mob_head` | `144:4` | wall head |
| `minecraft:player_head[facing=east,*]` | `mob_head` | `144:5` | wall head |
| `minecraft:player_head[*]` | `mob_head` | `144:0` | head type collapsed |
| `minecraft:player_wall_head[rotation=0,*]` | `mob_head` | `144:0` | standing head |
| `minecraft:player_wall_head[rotation=1,*]` | `mob_head` | `144:1` | standing head |
| `minecraft:player_wall_head[rotation=2,*]` | `mob_head` | `144:2` | standing head |
| `minecraft:player_wall_head[rotation=3,*]` | `mob_head` | `144:3` | standing head |
| `minecraft:player_wall_head[rotation=4,*]` | `mob_head` | `144:4` | standing head |
| `minecraft:player_wall_head[rotation=5,*]` | `mob_head` | `144:5` | standing head |
| `minecraft:player_wall_head[rotation=6,*]` | `mob_head` | `144:6` | standing head |
| `minecraft:player_wall_head[rotation=7,*]` | `mob_head` | `144:7` | standing head |
| `minecraft:player_wall_head[rotation=8,*]` | `mob_head` | `144:8` | standing head |
| `minecraft:player_wall_head[rotation=9,*]` | `mob_head` | `144:9` | standing head |
| `minecraft:player_wall_head[rotation=10,*]` | `mob_head` | `144:10` | standing head |
| `minecraft:player_wall_head[rotation=11,*]` | `mob_head` | `144:11` | standing head |
| `minecraft:player_wall_head[rotation=12,*]` | `mob_head` | `144:12` | standing head |
| `minecraft:player_wall_head[rotation=13,*]` | `mob_head` | `144:13` | standing head |
| `minecraft:player_wall_head[rotation=14,*]` | `mob_head` | `144:14` | standing head |
| `minecraft:player_wall_head[rotation=15,*]` | `mob_head` | `144:15` | standing head |
| `minecraft:player_wall_head[facing=north,*]` | `mob_head` | `144:2` | wall head |
| `minecraft:player_wall_head[facing=south,*]` | `mob_head` | `144:3` | wall head |
| `minecraft:player_wall_head[facing=west,*]` | `mob_head` | `144:4` | wall head |
| `minecraft:player_wall_head[facing=east,*]` | `mob_head` | `144:5` | wall head |
| `minecraft:player_wall_head[*]` | `mob_head` | `144:0` | head type collapsed |
| `minecraft:podzol[*]` | `dirt` | `3:0` |  |
| `minecraft:pointed_dripstone[*]` | `stone` | `1:0` |  |
| `minecraft:polished_andesite[*]` | `stone` | `1:0` | fallback |
| `minecraft:polished_andesite_slab[type=bottom,*]` | `stone_slab` | `44:0` |  |
| `minecraft:polished_andesite_slab[type=top,*]` | `stone_slab` | `44:8` |  |
| `minecraft:polished_andesite_slab[type=double,*]` | `stone_slab` | `43:0` | double slab |
| `minecraft:polished_andesite_slab[*]` | `stone_slab` | `44:0` |  |
| `minecraft:polished_andesite_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:polished_andesite_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:polished_andesite_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:polished_andesite_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:polished_andesite_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:polished_andesite_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:polished_andesite_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:polished_andesite_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:polished_andesite_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:polished_basalt[*]` | `stone` | `1:0` |  |
| `minecraft:polished_blackstone[*]` | `stonebrick` | `98:0` |  |
| `minecraft:polished_blackstone_brick_slab[type=bottom,*]` | `stone_slab` | `44:4` |  |
| `minecraft:polished_blackstone_brick_slab[type=top,*]` | `stone_slab` | `44:12` |  |
| `minecraft:polished_blackstone_brick_slab[type=double,*]` | `stone_slab` | `43:4` | double slab |
| `minecraft:polished_blackstone_brick_slab[*]` | `stone_slab` | `44:4` |  |
| `minecraft:polished_blackstone_brick_stairs[facing=east,half=bottom,*]` | `brick_stairs` | `108:0` |  |
| `minecraft:polished_blackstone_brick_stairs[facing=east,half=top,*]` | `brick_stairs` | `108:4` |  |
| `minecraft:polished_blackstone_brick_stairs[facing=west,half=bottom,*]` | `brick_stairs` | `108:1` |  |
| `minecraft:polished_blackstone_brick_stairs[facing=west,half=top,*]` | `brick_stairs` | `108:5` |  |
| `minecraft:polished_blackstone_brick_stairs[facing=south,half=bottom,*]` | `brick_stairs` | `108:2` |  |
| `minecraft:polished_blackstone_brick_stairs[facing=south,half=top,*]` | `brick_stairs` | `108:6` |  |
| `minecraft:polished_blackstone_brick_stairs[facing=north,half=bottom,*]` | `brick_stairs` | `108:3` |  |
| `minecraft:polished_blackstone_brick_stairs[facing=north,half=top,*]` | `brick_stairs` | `108:7` |  |
| `minecraft:polished_blackstone_brick_stairs[*]` | `brick_stairs` | `108:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:polished_blackstone_brick_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:polished_blackstone_bricks[*]` | `stonebrick` | `98:0` |  |
| `minecraft:polished_blackstone_button[face=floor,*]` | `stone_button` | `77:1` |  |
| `minecraft:polished_blackstone_button[face=wall,facing=east,*]` | `stone_button` | `77:2` |  |
| `minecraft:polished_blackstone_button[face=wall,facing=west,*]` | `stone_button` | `77:1` |  |
| `minecraft:polished_blackstone_button[face=wall,facing=south,*]` | `stone_button` | `77:3` |  |
| `minecraft:polished_blackstone_button[face=wall,facing=north,*]` | `stone_button` | `77:4` |  |
| `minecraft:polished_blackstone_button[powered=true,*]` | `stone_button` | `77:9` | powered bit approximated (+8) |
| `minecraft:polished_blackstone_button[*]` | `stone_button` | `77:1` |  |
| `minecraft:polished_blackstone_pressure_plate[*]` | `stone_pressure_plate` | `70:0` |  |
| `minecraft:polished_blackstone_slab[type=bottom,*]` | `stone_slab` | `44:6` |  |
| `minecraft:polished_blackstone_slab[type=top,*]` | `stone_slab` | `44:14` |  |
| `minecraft:polished_blackstone_slab[type=double,*]` | `stone_slab` | `43:6` | double slab |
| `minecraft:polished_blackstone_slab[*]` | `stone_slab` | `44:6` |  |
| `minecraft:polished_blackstone_stairs[facing=east,half=bottom,*]` | `nether_brick_stairs` | `114:0` |  |
| `minecraft:polished_blackstone_stairs[facing=east,half=top,*]` | `nether_brick_stairs` | `114:4` |  |
| `minecraft:polished_blackstone_stairs[facing=west,half=bottom,*]` | `nether_brick_stairs` | `114:1` |  |
| `minecraft:polished_blackstone_stairs[facing=west,half=top,*]` | `nether_brick_stairs` | `114:5` |  |
| `minecraft:polished_blackstone_stairs[facing=south,half=bottom,*]` | `nether_brick_stairs` | `114:2` |  |
| `minecraft:polished_blackstone_stairs[facing=south,half=top,*]` | `nether_brick_stairs` | `114:6` |  |
| `minecraft:polished_blackstone_stairs[facing=north,half=bottom,*]` | `nether_brick_stairs` | `114:3` |  |
| `minecraft:polished_blackstone_stairs[facing=north,half=top,*]` | `nether_brick_stairs` | `114:7` |  |
| `minecraft:polished_blackstone_stairs[*]` | `nether_brick_stairs` | `114:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:polished_blackstone_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:polished_deepslate[*]` | `stonebrick` | `98:0` |  |
| `minecraft:polished_deepslate_slab[type=bottom,*]` | `stone_slab` | `44:5` |  |
| `minecraft:polished_deepslate_slab[type=top,*]` | `stone_slab` | `44:13` |  |
| `minecraft:polished_deepslate_slab[type=double,*]` | `stone_slab` | `43:5` | double slab |
| `minecraft:polished_deepslate_slab[*]` | `stone_slab` | `44:5` |  |
| `minecraft:polished_deepslate_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:polished_deepslate_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:polished_deepslate_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:polished_deepslate_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:polished_deepslate_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:polished_deepslate_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:polished_deepslate_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:polished_deepslate_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:polished_deepslate_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:polished_deepslate_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:polished_diorite[*]` | `stone` | `1:0` | fallback |
| `minecraft:polished_diorite_slab[type=bottom,*]` | `stone_slab` | `44:0` |  |
| `minecraft:polished_diorite_slab[type=top,*]` | `stone_slab` | `44:8` |  |
| `minecraft:polished_diorite_slab[type=double,*]` | `stone_slab` | `43:0` | double slab |
| `minecraft:polished_diorite_slab[*]` | `stone_slab` | `44:0` |  |
| `minecraft:polished_diorite_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:polished_diorite_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:polished_diorite_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:polished_diorite_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:polished_diorite_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:polished_diorite_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:polished_diorite_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:polished_diorite_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:polished_diorite_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:polished_granite[*]` | `stone` | `1:0` | fallback |
| `minecraft:polished_granite_slab[type=bottom,*]` | `stone_slab` | `44:0` |  |
| `minecraft:polished_granite_slab[type=top,*]` | `stone_slab` | `44:8` |  |
| `minecraft:polished_granite_slab[type=double,*]` | `stone_slab` | `43:0` | double slab |
| `minecraft:polished_granite_slab[*]` | `stone_slab` | `44:0` |  |
| `minecraft:polished_granite_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:polished_granite_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:polished_granite_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:polished_granite_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:polished_granite_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:polished_granite_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:polished_granite_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:polished_granite_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:polished_granite_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:polished_tuff[*]` | `stone` | `1:0` |  |
| `minecraft:polished_tuff_slab[type=bottom,*]` | `stone_slab` | `44:5` |  |
| `minecraft:polished_tuff_slab[type=top,*]` | `stone_slab` | `44:13` |  |
| `minecraft:polished_tuff_slab[type=double,*]` | `stone_slab` | `43:5` | double slab |
| `minecraft:polished_tuff_slab[*]` | `stone_slab` | `44:5` |  |
| `minecraft:polished_tuff_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:polished_tuff_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:polished_tuff_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:polished_tuff_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:polished_tuff_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:polished_tuff_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:polished_tuff_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:polished_tuff_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:polished_tuff_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:polished_tuff_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:poppy[*]` | `red_flower` | `38:0` |  |
| `minecraft:potatoes[age=0,*]` | `potatoes` | `142:0` |  |
| `minecraft:potatoes[age=1,*]` | `potatoes` | `142:1` |  |
| `minecraft:potatoes[age=2,*]` | `potatoes` | `142:2` |  |
| `minecraft:potatoes[age=3,*]` | `potatoes` | `142:3` |  |
| `minecraft:potatoes[age=4,*]` | `potatoes` | `142:4` |  |
| `minecraft:potatoes[age=5,*]` | `potatoes` | `142:5` |  |
| `minecraft:potatoes[age=6,*]` | `potatoes` | `142:6` |  |
| `minecraft:potatoes[age=7,*]` | `potatoes` | `142:7` |  |
| `minecraft:potatoes[*]` | `potatoes` | `142:0` |  |
| `minecraft:potted_acacia_sapling[*]` | `sapling` | `6:3` |  |
| `minecraft:potted_allium[*]` | `red_flower` | `38:0` |  |
| `minecraft:potted_azalea_bush[*]` | `stone` | `1:0` | fallback |
| `minecraft:potted_azure_bluet[*]` | `red_flower` | `38:0` |  |
| `minecraft:potted_bamboo[*]` | `sapling` | `6:2` |  |
| `minecraft:potted_birch_sapling[*]` | `sapling` | `6:2` |  |
| `minecraft:potted_blue_orchid[*]` | `red_flower` | `38:0` |  |
| `minecraft:potted_brown_mushroom[*]` | `brown_mushroom` | `39:0` |  |
| `minecraft:potted_cactus[*]` | `stone` | `1:0` | fallback |
| `minecraft:potted_cherry_sapling[*]` | `sapling` | `6:2` |  |
| `minecraft:potted_closed_eyeblossom[*]` | `red_flower` | `38:0` |  |
| `minecraft:potted_cornflower[*]` | `red_flower` | `38:0` |  |
| `minecraft:potted_crimson_fungus[*]` | `stone` | `1:0` | fallback |
| `minecraft:potted_crimson_roots[*]` | `stone` | `1:0` | fallback |
| `minecraft:potted_dandelion[*]` | `red_flower` | `38:0` |  |
| `minecraft:potted_dark_oak_sapling[*]` | `sapling` | `6:1` |  |
| `minecraft:potted_dead_bush[*]` | `dead_bush` | `32:0` |  |
| `minecraft:potted_fern[*]` | `tallgrass` | `31:1` |  |
| `minecraft:potted_flowering_azalea_bush[*]` | `red_flower` | `38:0` |  |
| `minecraft:potted_jungle_sapling[*]` | `sapling` | `6:3` |  |
| `minecraft:potted_lily_of_the_valley[*]` | `red_flower` | `38:0` |  |
| `minecraft:potted_mangrove_propagule[*]` | `stone` | `1:0` | fallback |
| `minecraft:potted_oak_sapling[*]` | `sapling` | `6:0` |  |
| `minecraft:potted_open_eyeblossom[*]` | `red_flower` | `38:0` |  |
| `minecraft:potted_orange_tulip[*]` | `stone` | `1:0` | fallback |
| `minecraft:potted_oxeye_daisy[*]` | `red_flower` | `38:0` |  |
| `minecraft:potted_pale_oak_sapling[*]` | `sapling` | `6:1` |  |
| `minecraft:potted_pink_tulip[*]` | `stone` | `1:0` | fallback |
| `minecraft:potted_poppy[*]` | `red_flower` | `38:0` |  |
| `minecraft:potted_red_mushroom[*]` | `red_mushroom` | `40:0` |  |
| `minecraft:potted_red_tulip[*]` | `stone` | `1:0` | fallback |
| `minecraft:potted_spruce_sapling[*]` | `sapling` | `6:1` |  |
| `minecraft:potted_torchflower[*]` | `red_flower` | `38:0` |  |
| `minecraft:potted_warped_fungus[*]` | `stone` | `1:0` | fallback |
| `minecraft:potted_warped_roots[*]` | `stone` | `1:0` | fallback |
| `minecraft:potted_white_tulip[*]` | `stone` | `1:0` | fallback |
| `minecraft:potted_wither_rose[*]` | `red_flower` | `38:0` |  |
| `minecraft:powder_snow[*]` | `stone` | `1:0` | fallback |
| `minecraft:powder_snow_cauldron[level=0,*]` | `cauldron` | `118:0` |  |
| `minecraft:powder_snow_cauldron[level=1,*]` | `cauldron` | `118:1` |  |
| `minecraft:powder_snow_cauldron[level=2,*]` | `cauldron` | `118:2` |  |
| `minecraft:powder_snow_cauldron[level=3,*]` | `cauldron` | `118:3` |  |
| `minecraft:powder_snow_cauldron[*]` | `cauldron` | `118:0` | lava/powder-snow cauldrons collapse to cauldron levels |
| `minecraft:powered_rail[shape=north_south,powered=false,*]` | `powered_rail` | `27:0` | unpowered |
| `minecraft:powered_rail[shape=north_south,powered=true,*]` | `powered_rail` | `27:8` | powered |
| `minecraft:powered_rail[shape=east_west,powered=false,*]` | `powered_rail` | `27:1` | unpowered |
| `minecraft:powered_rail[shape=east_west,powered=true,*]` | `powered_rail` | `27:9` | powered |
| `minecraft:powered_rail[shape=ascending_east,powered=false,*]` | `powered_rail` | `27:2` | unpowered |
| `minecraft:powered_rail[shape=ascending_east,powered=true,*]` | `powered_rail` | `27:10` | powered |
| `minecraft:powered_rail[shape=ascending_west,powered=false,*]` | `powered_rail` | `27:3` | unpowered |
| `minecraft:powered_rail[shape=ascending_west,powered=true,*]` | `powered_rail` | `27:11` | powered |
| `minecraft:powered_rail[shape=ascending_north,powered=false,*]` | `powered_rail` | `27:4` | unpowered |
| `minecraft:powered_rail[shape=ascending_north,powered=true,*]` | `powered_rail` | `27:12` | powered |
| `minecraft:powered_rail[shape=ascending_south,powered=false,*]` | `powered_rail` | `27:5` | unpowered |
| `minecraft:powered_rail[shape=ascending_south,powered=true,*]` | `powered_rail` | `27:13` | powered |
| `minecraft:powered_rail[*]` | `powered_rail` | `27:0` | curved shapes collapse to straight |
| `minecraft:prismarine[*]` | `stone` | `1:0` | fallback |
| `minecraft:prismarine_brick_slab[type=bottom,*]` | `stone_slab` | `44:4` |  |
| `minecraft:prismarine_brick_slab[type=top,*]` | `stone_slab` | `44:12` |  |
| `minecraft:prismarine_brick_slab[type=double,*]` | `stone_slab` | `43:4` | double slab |
| `minecraft:prismarine_brick_slab[*]` | `stone_slab` | `44:4` |  |
| `minecraft:prismarine_brick_stairs[facing=east,half=bottom,*]` | `brick_stairs` | `108:0` |  |
| `minecraft:prismarine_brick_stairs[facing=east,half=top,*]` | `brick_stairs` | `108:4` |  |
| `minecraft:prismarine_brick_stairs[facing=west,half=bottom,*]` | `brick_stairs` | `108:1` |  |
| `minecraft:prismarine_brick_stairs[facing=west,half=top,*]` | `brick_stairs` | `108:5` |  |
| `minecraft:prismarine_brick_stairs[facing=south,half=bottom,*]` | `brick_stairs` | `108:2` |  |
| `minecraft:prismarine_brick_stairs[facing=south,half=top,*]` | `brick_stairs` | `108:6` |  |
| `minecraft:prismarine_brick_stairs[facing=north,half=bottom,*]` | `brick_stairs` | `108:3` |  |
| `minecraft:prismarine_brick_stairs[facing=north,half=top,*]` | `brick_stairs` | `108:7` |  |
| `minecraft:prismarine_brick_stairs[*]` | `brick_stairs` | `108:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:prismarine_bricks[*]` | `brick_block` | `45:0` |  |
| `minecraft:prismarine_slab[type=bottom,*]` | `stone_slab` | `44:0` |  |
| `minecraft:prismarine_slab[type=top,*]` | `stone_slab` | `44:8` |  |
| `minecraft:prismarine_slab[type=double,*]` | `stone_slab` | `43:0` | double slab |
| `minecraft:prismarine_slab[*]` | `stone_slab` | `44:0` |  |
| `minecraft:prismarine_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:prismarine_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:prismarine_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:prismarine_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:prismarine_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:prismarine_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:prismarine_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:prismarine_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:prismarine_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:prismarine_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:pumpkin[facing=north,*]` | `pumpkin` | `86:2` |  |
| `minecraft:pumpkin[facing=south,*]` | `pumpkin` | `86:3` |  |
| `minecraft:pumpkin[facing=west,*]` | `pumpkin` | `86:4` |  |
| `minecraft:pumpkin[facing=east,*]` | `pumpkin` | `86:5` |  |
| `minecraft:pumpkin[*]` | `pumpkin` | `86:2` |  |
| `minecraft:pumpkin_stem[age=0,*]` | `pumpkin_stem` | `104:0` |  |
| `minecraft:pumpkin_stem[age=1,*]` | `pumpkin_stem` | `104:1` |  |
| `minecraft:pumpkin_stem[age=2,*]` | `pumpkin_stem` | `104:2` |  |
| `minecraft:pumpkin_stem[age=3,*]` | `pumpkin_stem` | `104:3` |  |
| `minecraft:pumpkin_stem[age=4,*]` | `pumpkin_stem` | `104:4` |  |
| `minecraft:pumpkin_stem[age=5,*]` | `pumpkin_stem` | `104:5` |  |
| `minecraft:pumpkin_stem[age=6,*]` | `pumpkin_stem` | `104:6` |  |
| `minecraft:pumpkin_stem[age=7,*]` | `pumpkin_stem` | `104:7` |  |
| `minecraft:pumpkin_stem[*]` | `pumpkin_stem` | `104:0` |  |
| `minecraft:purple_banner[*]` | `wool` | `35:10` | banner collapsed to wool |
| `minecraft:purple_bed[part=foot,facing=south,occupied=false,*]` | `bed` | `26:0` | bed color ignored |
| `minecraft:purple_bed[part=head,facing=south,occupied=false,*]` | `bed` | `26:8` | bed color ignored |
| `minecraft:purple_bed[part=foot,facing=south,occupied=true,*]` | `bed` | `26:4` | occupied bit; color ignored |
| `minecraft:purple_bed[part=head,facing=south,occupied=true,*]` | `bed` | `26:12` | occupied+head bits; color ignored |
| `minecraft:purple_bed[part=foot,facing=west,occupied=false,*]` | `bed` | `26:1` | bed color ignored |
| `minecraft:purple_bed[part=head,facing=west,occupied=false,*]` | `bed` | `26:9` | bed color ignored |
| `minecraft:purple_bed[part=foot,facing=west,occupied=true,*]` | `bed` | `26:5` | occupied bit; color ignored |
| `minecraft:purple_bed[part=head,facing=west,occupied=true,*]` | `bed` | `26:13` | occupied+head bits; color ignored |
| `minecraft:purple_bed[part=foot,facing=north,occupied=false,*]` | `bed` | `26:2` | bed color ignored |
| `minecraft:purple_bed[part=head,facing=north,occupied=false,*]` | `bed` | `26:10` | bed color ignored |
| `minecraft:purple_bed[part=foot,facing=north,occupied=true,*]` | `bed` | `26:6` | occupied bit; color ignored |
| `minecraft:purple_bed[part=head,facing=north,occupied=true,*]` | `bed` | `26:14` | occupied+head bits; color ignored |
| `minecraft:purple_bed[part=foot,facing=east,occupied=false,*]` | `bed` | `26:3` | bed color ignored |
| `minecraft:purple_bed[part=head,facing=east,occupied=false,*]` | `bed` | `26:11` | bed color ignored |
| `minecraft:purple_bed[part=foot,facing=east,occupied=true,*]` | `bed` | `26:7` | occupied bit; color ignored |
| `minecraft:purple_bed[part=head,facing=east,occupied=true,*]` | `bed` | `26:15` | occupied+head bits; color ignored |
| `minecraft:purple_bed[*]` | `bed` | `26:0` | legacy bed ignores color |
| `minecraft:purple_candle[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:purple_candle_cake[bites=0,*]` | `cake` | `92:0` |  |
| `minecraft:purple_candle_cake[bites=1,*]` | `cake` | `92:1` |  |
| `minecraft:purple_candle_cake[bites=2,*]` | `cake` | `92:2` |  |
| `minecraft:purple_candle_cake[bites=3,*]` | `cake` | `92:3` |  |
| `minecraft:purple_candle_cake[bites=4,*]` | `cake` | `92:4` |  |
| `minecraft:purple_candle_cake[bites=5,*]` | `cake` | `92:5` |  |
| `minecraft:purple_candle_cake[bites=6,*]` | `cake` | `92:6` |  |
| `minecraft:purple_candle_cake[*]` | `cake` | `92:0` |  |
| `minecraft:purple_carpet[*]` | `carpet` | `171:10` |  |
| `minecraft:purple_concrete[*]` | `stained_hardened_clay` | `159:10` |  |
| `minecraft:purple_concrete_powder[*]` | `stained_hardened_clay` | `159:10` |  |
| `minecraft:purple_glazed_terracotta[*]` | `stained_hardened_clay` | `159:10` |  |
| `minecraft:purple_shulker_box[*]` | `wool` | `35:10` | shulker box collapsed to wool |
| `minecraft:purple_stained_glass[*]` | `stained_glass` | `95:10` |  |
| `minecraft:purple_stained_glass_pane[*]` | `stained_glass_pane` | `160:10` |  |
| `minecraft:purple_terracotta[*]` | `stained_hardened_clay` | `159:10` |  |
| `minecraft:purple_wall_banner[*]` | `wool` | `35:10` | banner collapsed to wool |
| `minecraft:purple_wool[*]` | `wool` | `35:10` |  |
| `minecraft:purpur_block[*]` | `quartz_block` | `155:0` |  |
| `minecraft:purpur_pillar[*]` | `quartz_block` | `155:0` |  |
| `minecraft:purpur_slab[type=bottom,*]` | `stone_slab` | `44:7` |  |
| `minecraft:purpur_slab[type=top,*]` | `stone_slab` | `44:15` |  |
| `minecraft:purpur_slab[type=double,*]` | `stone_slab` | `43:7` | double slab |
| `minecraft:purpur_slab[*]` | `stone_slab` | `44:7` |  |
| `minecraft:purpur_stairs[facing=east,half=bottom,*]` | `quartz_stairs` | `156:0` |  |
| `minecraft:purpur_stairs[facing=east,half=top,*]` | `quartz_stairs` | `156:4` |  |
| `minecraft:purpur_stairs[facing=west,half=bottom,*]` | `quartz_stairs` | `156:1` |  |
| `minecraft:purpur_stairs[facing=west,half=top,*]` | `quartz_stairs` | `156:5` |  |
| `minecraft:purpur_stairs[facing=south,half=bottom,*]` | `quartz_stairs` | `156:2` |  |
| `minecraft:purpur_stairs[facing=south,half=top,*]` | `quartz_stairs` | `156:6` |  |
| `minecraft:purpur_stairs[facing=north,half=bottom,*]` | `quartz_stairs` | `156:3` |  |
| `minecraft:purpur_stairs[facing=north,half=top,*]` | `quartz_stairs` | `156:7` |  |
| `minecraft:purpur_stairs[*]` | `quartz_stairs` | `156:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:quartz_block[axis=y,*]` | `quartz_block` | `155:2` | pillar quartz vertical |
| `minecraft:quartz_block[axis=x,*]` | `quartz_block` | `155:3` | pillar quartz horizontal |
| `minecraft:quartz_block[axis=z,*]` | `quartz_block` | `155:4` | pillar quartz horizontal |
| `minecraft:quartz_block[*]` | `quartz_block` | `155:0` | smooth/chiseled collapse to plain quartz block |
| `minecraft:quartz_bricks[axis=y,*]` | `quartz_block` | `155:2` | pillar quartz vertical |
| `minecraft:quartz_bricks[axis=x,*]` | `quartz_block` | `155:3` | pillar quartz horizontal |
| `minecraft:quartz_bricks[axis=z,*]` | `quartz_block` | `155:4` | pillar quartz horizontal |
| `minecraft:quartz_bricks[*]` | `quartz_block` | `155:0` | smooth/chiseled collapse to plain quartz block |
| `minecraft:quartz_pillar[axis=y,*]` | `quartz_block` | `155:2` | pillar quartz vertical |
| `minecraft:quartz_pillar[axis=x,*]` | `quartz_block` | `155:3` | pillar quartz horizontal |
| `minecraft:quartz_pillar[axis=z,*]` | `quartz_block` | `155:4` | pillar quartz horizontal |
| `minecraft:quartz_pillar[*]` | `quartz_block` | `155:0` | smooth/chiseled collapse to plain quartz block |
| `minecraft:quartz_slab[type=bottom,*]` | `stone_slab` | `44:7` |  |
| `minecraft:quartz_slab[type=top,*]` | `stone_slab` | `44:15` |  |
| `minecraft:quartz_slab[type=double,*]` | `stone_slab` | `43:7` | double slab |
| `minecraft:quartz_slab[*]` | `stone_slab` | `44:7` |  |
| `minecraft:quartz_stairs[facing=east,half=bottom,*]` | `quartz_stairs` | `156:0` |  |
| `minecraft:quartz_stairs[facing=east,half=top,*]` | `quartz_stairs` | `156:4` |  |
| `minecraft:quartz_stairs[facing=west,half=bottom,*]` | `quartz_stairs` | `156:1` |  |
| `minecraft:quartz_stairs[facing=west,half=top,*]` | `quartz_stairs` | `156:5` |  |
| `minecraft:quartz_stairs[facing=south,half=bottom,*]` | `quartz_stairs` | `156:2` |  |
| `minecraft:quartz_stairs[facing=south,half=top,*]` | `quartz_stairs` | `156:6` |  |
| `minecraft:quartz_stairs[facing=north,half=bottom,*]` | `quartz_stairs` | `156:3` |  |
| `minecraft:quartz_stairs[facing=north,half=top,*]` | `quartz_stairs` | `156:7` |  |
| `minecraft:quartz_stairs[*]` | `quartz_stairs` | `156:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:rail[shape=north_south,*]` | `rail` | `66:0` |  |
| `minecraft:rail[shape=east_west,*]` | `rail` | `66:1` |  |
| `minecraft:rail[shape=ascending_east,*]` | `rail` | `66:2` |  |
| `minecraft:rail[shape=ascending_west,*]` | `rail` | `66:3` |  |
| `minecraft:rail[shape=ascending_north,*]` | `rail` | `66:4` |  |
| `minecraft:rail[shape=ascending_south,*]` | `rail` | `66:5` |  |
| `minecraft:rail[shape=south_east,*]` | `rail` | `66:6` |  |
| `minecraft:rail[shape=south_west,*]` | `rail` | `66:7` |  |
| `minecraft:rail[shape=north_west,*]` | `rail` | `66:8` |  |
| `minecraft:rail[shape=north_east,*]` | `rail` | `66:9` |  |
| `minecraft:rail[*]` | `rail` | `66:0` |  |
| `minecraft:raw_copper_block[*]` | `iron_block` | `42:0` |  |
| `minecraft:raw_gold_block[*]` | `gold_block` | `41:0` |  |
| `minecraft:raw_iron_block[*]` | `iron_block` | `42:0` |  |
| `minecraft:red_banner[*]` | `wool` | `35:14` | banner collapsed to wool |
| `minecraft:red_bed[part=foot,facing=south,occupied=false,*]` | `bed` | `26:0` | bed color ignored |
| `minecraft:red_bed[part=head,facing=south,occupied=false,*]` | `bed` | `26:8` | bed color ignored |
| `minecraft:red_bed[part=foot,facing=south,occupied=true,*]` | `bed` | `26:4` | occupied bit; color ignored |
| `minecraft:red_bed[part=head,facing=south,occupied=true,*]` | `bed` | `26:12` | occupied+head bits; color ignored |
| `minecraft:red_bed[part=foot,facing=west,occupied=false,*]` | `bed` | `26:1` | bed color ignored |
| `minecraft:red_bed[part=head,facing=west,occupied=false,*]` | `bed` | `26:9` | bed color ignored |
| `minecraft:red_bed[part=foot,facing=west,occupied=true,*]` | `bed` | `26:5` | occupied bit; color ignored |
| `minecraft:red_bed[part=head,facing=west,occupied=true,*]` | `bed` | `26:13` | occupied+head bits; color ignored |
| `minecraft:red_bed[part=foot,facing=north,occupied=false,*]` | `bed` | `26:2` | bed color ignored |
| `minecraft:red_bed[part=head,facing=north,occupied=false,*]` | `bed` | `26:10` | bed color ignored |
| `minecraft:red_bed[part=foot,facing=north,occupied=true,*]` | `bed` | `26:6` | occupied bit; color ignored |
| `minecraft:red_bed[part=head,facing=north,occupied=true,*]` | `bed` | `26:14` | occupied+head bits; color ignored |
| `minecraft:red_bed[part=foot,facing=east,occupied=false,*]` | `bed` | `26:3` | bed color ignored |
| `minecraft:red_bed[part=head,facing=east,occupied=false,*]` | `bed` | `26:11` | bed color ignored |
| `minecraft:red_bed[part=foot,facing=east,occupied=true,*]` | `bed` | `26:7` | occupied bit; color ignored |
| `minecraft:red_bed[part=head,facing=east,occupied=true,*]` | `bed` | `26:15` | occupied+head bits; color ignored |
| `minecraft:red_bed[*]` | `bed` | `26:0` | legacy bed ignores color |
| `minecraft:red_candle[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:red_candle_cake[bites=0,*]` | `cake` | `92:0` |  |
| `minecraft:red_candle_cake[bites=1,*]` | `cake` | `92:1` |  |
| `minecraft:red_candle_cake[bites=2,*]` | `cake` | `92:2` |  |
| `minecraft:red_candle_cake[bites=3,*]` | `cake` | `92:3` |  |
| `minecraft:red_candle_cake[bites=4,*]` | `cake` | `92:4` |  |
| `minecraft:red_candle_cake[bites=5,*]` | `cake` | `92:5` |  |
| `minecraft:red_candle_cake[bites=6,*]` | `cake` | `92:6` |  |
| `minecraft:red_candle_cake[*]` | `cake` | `92:0` |  |
| `minecraft:red_carpet[*]` | `carpet` | `171:14` |  |
| `minecraft:red_concrete[*]` | `stained_hardened_clay` | `159:14` |  |
| `minecraft:red_concrete_powder[*]` | `stained_hardened_clay` | `159:14` |  |
| `minecraft:red_glazed_terracotta[*]` | `stained_hardened_clay` | `159:14` |  |
| `minecraft:red_mushroom[*]` | `red_mushroom` | `40:0` |  |
| `minecraft:red_mushroom_block[*]` | `red_mushroom_block` | `100:0` |  |
| `minecraft:red_nether_brick_slab[type=bottom,*]` | `stone_slab` | `44:6` |  |
| `minecraft:red_nether_brick_slab[type=top,*]` | `stone_slab` | `44:14` |  |
| `minecraft:red_nether_brick_slab[type=double,*]` | `stone_slab` | `43:6` | double slab |
| `minecraft:red_nether_brick_slab[*]` | `stone_slab` | `44:6` |  |
| `minecraft:red_nether_brick_stairs[facing=east,half=bottom,*]` | `nether_brick_stairs` | `114:0` |  |
| `minecraft:red_nether_brick_stairs[facing=east,half=top,*]` | `nether_brick_stairs` | `114:4` |  |
| `minecraft:red_nether_brick_stairs[facing=west,half=bottom,*]` | `nether_brick_stairs` | `114:1` |  |
| `minecraft:red_nether_brick_stairs[facing=west,half=top,*]` | `nether_brick_stairs` | `114:5` |  |
| `minecraft:red_nether_brick_stairs[facing=south,half=bottom,*]` | `nether_brick_stairs` | `114:2` |  |
| `minecraft:red_nether_brick_stairs[facing=south,half=top,*]` | `nether_brick_stairs` | `114:6` |  |
| `minecraft:red_nether_brick_stairs[facing=north,half=bottom,*]` | `nether_brick_stairs` | `114:3` |  |
| `minecraft:red_nether_brick_stairs[facing=north,half=top,*]` | `nether_brick_stairs` | `114:7` |  |
| `minecraft:red_nether_brick_stairs[*]` | `nether_brick_stairs` | `114:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:red_nether_brick_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:red_nether_bricks[*]` | `nether_brick` | `112:0` |  |
| `minecraft:red_sand[*]` | `sand` | `12:1` |  |
| `minecraft:red_sandstone[*]` | `sandstone` | `24:0` |  |
| `minecraft:red_sandstone_slab[type=bottom,*]` | `stone_slab` | `44:1` |  |
| `minecraft:red_sandstone_slab[type=top,*]` | `stone_slab` | `44:9` |  |
| `minecraft:red_sandstone_slab[type=double,*]` | `stone_slab` | `43:1` | double slab |
| `minecraft:red_sandstone_slab[*]` | `stone_slab` | `44:1` |  |
| `minecraft:red_sandstone_stairs[facing=east,half=bottom,*]` | `sandstone_stairs` | `128:0` |  |
| `minecraft:red_sandstone_stairs[facing=east,half=top,*]` | `sandstone_stairs` | `128:4` |  |
| `minecraft:red_sandstone_stairs[facing=west,half=bottom,*]` | `sandstone_stairs` | `128:1` |  |
| `minecraft:red_sandstone_stairs[facing=west,half=top,*]` | `sandstone_stairs` | `128:5` |  |
| `minecraft:red_sandstone_stairs[facing=south,half=bottom,*]` | `sandstone_stairs` | `128:2` |  |
| `minecraft:red_sandstone_stairs[facing=south,half=top,*]` | `sandstone_stairs` | `128:6` |  |
| `minecraft:red_sandstone_stairs[facing=north,half=bottom,*]` | `sandstone_stairs` | `128:3` |  |
| `minecraft:red_sandstone_stairs[facing=north,half=top,*]` | `sandstone_stairs` | `128:7` |  |
| `minecraft:red_sandstone_stairs[*]` | `sandstone_stairs` | `128:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:red_sandstone_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:red_shulker_box[*]` | `wool` | `35:14` | shulker box collapsed to wool |
| `minecraft:red_stained_glass[*]` | `stained_glass` | `95:14` |  |
| `minecraft:red_stained_glass_pane[*]` | `stained_glass_pane` | `160:14` |  |
| `minecraft:red_terracotta[*]` | `stained_hardened_clay` | `159:14` |  |
| `minecraft:red_tulip[*]` | `stone` | `1:0` | fallback |
| `minecraft:red_wall_banner[*]` | `wool` | `35:14` | banner collapsed to wool |
| `minecraft:red_wool[*]` | `wool` | `35:14` |  |
| `minecraft:redstone_block[*]` | `redstone_block` | `152:0` |  |
| `minecraft:redstone_lamp[lit=false,*]` | `redstone_lamp` | `123:0` |  |
| `minecraft:redstone_lamp[lit=true,*]` | `redstone_lamp` | `124:0` | lit redstone lamp |
| `minecraft:redstone_lamp[*]` | `redstone_lamp` | `123:0` |  |
| `minecraft:redstone_ore[*]` | `redstone_ore` | `73:0` |  |
| `minecraft:redstone_torch[lit=false,facing=east,*]` | `redstone_torch` | `75:1` | off |
| `minecraft:redstone_torch[lit=true,facing=east,*]` | `redstone_torch` | `76:1` | on |
| `minecraft:redstone_torch[lit=false,facing=west,*]` | `redstone_torch` | `75:2` | off |
| `minecraft:redstone_torch[lit=true,facing=west,*]` | `redstone_torch` | `76:2` | on |
| `minecraft:redstone_torch[lit=false,facing=south,*]` | `redstone_torch` | `75:3` | off |
| `minecraft:redstone_torch[lit=true,facing=south,*]` | `redstone_torch` | `76:3` | on |
| `minecraft:redstone_torch[lit=false,facing=north,*]` | `redstone_torch` | `75:4` | off |
| `minecraft:redstone_torch[lit=true,facing=north,*]` | `redstone_torch` | `76:4` | on |
| `minecraft:redstone_torch[lit=false,*]` | `redstone_torch` | `75:5` | standing redstone torch off |
| `minecraft:redstone_torch[lit=true,*]` | `redstone_torch` | `76:5` | standing redstone torch on |
| `minecraft:redstone_wall_torch[lit=false,facing=east,*]` | `redstone_torch` | `75:1` | off |
| `minecraft:redstone_wall_torch[lit=true,facing=east,*]` | `redstone_torch` | `76:1` | on |
| `minecraft:redstone_wall_torch[lit=false,facing=west,*]` | `redstone_torch` | `75:2` | off |
| `minecraft:redstone_wall_torch[lit=true,facing=west,*]` | `redstone_torch` | `76:2` | on |
| `minecraft:redstone_wall_torch[lit=false,facing=south,*]` | `redstone_torch` | `75:3` | off |
| `minecraft:redstone_wall_torch[lit=true,facing=south,*]` | `redstone_torch` | `76:3` | on |
| `minecraft:redstone_wall_torch[lit=false,facing=north,*]` | `redstone_torch` | `75:4` | off |
| `minecraft:redstone_wall_torch[lit=true,facing=north,*]` | `redstone_torch` | `76:4` | on |
| `minecraft:redstone_wall_torch[lit=false,*]` | `redstone_torch` | `75:5` | standing redstone torch off |
| `minecraft:redstone_wall_torch[lit=true,*]` | `redstone_torch` | `76:5` | standing redstone torch on |
| `minecraft:redstone_wire[power=0,*]` | `redstone_wire` | `55:0` |  |
| `minecraft:redstone_wire[power=1,*]` | `redstone_wire` | `55:1` |  |
| `minecraft:redstone_wire[power=2,*]` | `redstone_wire` | `55:2` |  |
| `minecraft:redstone_wire[power=3,*]` | `redstone_wire` | `55:3` |  |
| `minecraft:redstone_wire[power=4,*]` | `redstone_wire` | `55:4` |  |
| `minecraft:redstone_wire[power=5,*]` | `redstone_wire` | `55:5` |  |
| `minecraft:redstone_wire[power=6,*]` | `redstone_wire` | `55:6` |  |
| `minecraft:redstone_wire[power=7,*]` | `redstone_wire` | `55:7` |  |
| `minecraft:redstone_wire[power=8,*]` | `redstone_wire` | `55:8` |  |
| `minecraft:redstone_wire[power=9,*]` | `redstone_wire` | `55:9` |  |
| `minecraft:redstone_wire[power=10,*]` | `redstone_wire` | `55:10` |  |
| `minecraft:redstone_wire[power=11,*]` | `redstone_wire` | `55:11` |  |
| `minecraft:redstone_wire[power=12,*]` | `redstone_wire` | `55:12` |  |
| `minecraft:redstone_wire[power=13,*]` | `redstone_wire` | `55:13` |  |
| `minecraft:redstone_wire[power=14,*]` | `redstone_wire` | `55:14` |  |
| `minecraft:redstone_wire[power=15,*]` | `redstone_wire` | `55:15` |  |
| `minecraft:redstone_wire[*]` | `redstone_wire` | `55:0` |  |
| `minecraft:reinforced_deepslate[*]` | `stone` | `1:0` |  |
| `minecraft:repeater[facing=north,delay=1,powered=false,*]` | `repeater` | `93:0` | repeater off |
| `minecraft:repeater[facing=north,delay=1,powered=true,*]` | `repeater` | `94:0` | repeater on |
| `minecraft:repeater[facing=north,delay=2,powered=false,*]` | `repeater` | `93:4` | repeater off |
| `minecraft:repeater[facing=north,delay=2,powered=true,*]` | `repeater` | `94:4` | repeater on |
| `minecraft:repeater[facing=north,delay=3,powered=false,*]` | `repeater` | `93:8` | repeater off |
| `minecraft:repeater[facing=north,delay=3,powered=true,*]` | `repeater` | `94:8` | repeater on |
| `minecraft:repeater[facing=north,delay=4,powered=false,*]` | `repeater` | `93:12` | repeater off |
| `minecraft:repeater[facing=north,delay=4,powered=true,*]` | `repeater` | `94:12` | repeater on |
| `minecraft:repeater[facing=east,delay=1,powered=false,*]` | `repeater` | `93:1` | repeater off |
| `minecraft:repeater[facing=east,delay=1,powered=true,*]` | `repeater` | `94:1` | repeater on |
| `minecraft:repeater[facing=east,delay=2,powered=false,*]` | `repeater` | `93:5` | repeater off |
| `minecraft:repeater[facing=east,delay=2,powered=true,*]` | `repeater` | `94:5` | repeater on |
| `minecraft:repeater[facing=east,delay=3,powered=false,*]` | `repeater` | `93:9` | repeater off |
| `minecraft:repeater[facing=east,delay=3,powered=true,*]` | `repeater` | `94:9` | repeater on |
| `minecraft:repeater[facing=east,delay=4,powered=false,*]` | `repeater` | `93:13` | repeater off |
| `minecraft:repeater[facing=east,delay=4,powered=true,*]` | `repeater` | `94:13` | repeater on |
| `minecraft:repeater[facing=south,delay=1,powered=false,*]` | `repeater` | `93:2` | repeater off |
| `minecraft:repeater[facing=south,delay=1,powered=true,*]` | `repeater` | `94:2` | repeater on |
| `minecraft:repeater[facing=south,delay=2,powered=false,*]` | `repeater` | `93:6` | repeater off |
| `minecraft:repeater[facing=south,delay=2,powered=true,*]` | `repeater` | `94:6` | repeater on |
| `minecraft:repeater[facing=south,delay=3,powered=false,*]` | `repeater` | `93:10` | repeater off |
| `minecraft:repeater[facing=south,delay=3,powered=true,*]` | `repeater` | `94:10` | repeater on |
| `minecraft:repeater[facing=south,delay=4,powered=false,*]` | `repeater` | `93:14` | repeater off |
| `minecraft:repeater[facing=south,delay=4,powered=true,*]` | `repeater` | `94:14` | repeater on |
| `minecraft:repeater[facing=west,delay=1,powered=false,*]` | `repeater` | `93:3` | repeater off |
| `minecraft:repeater[facing=west,delay=1,powered=true,*]` | `repeater` | `94:3` | repeater on |
| `minecraft:repeater[facing=west,delay=2,powered=false,*]` | `repeater` | `93:7` | repeater off |
| `minecraft:repeater[facing=west,delay=2,powered=true,*]` | `repeater` | `94:7` | repeater on |
| `minecraft:repeater[facing=west,delay=3,powered=false,*]` | `repeater` | `93:11` | repeater off |
| `minecraft:repeater[facing=west,delay=3,powered=true,*]` | `repeater` | `94:11` | repeater on |
| `minecraft:repeater[facing=west,delay=4,powered=false,*]` | `repeater` | `93:15` | repeater off |
| `minecraft:repeater[facing=west,delay=4,powered=true,*]` | `repeater` | `94:15` | repeater on |
| `minecraft:repeater[*]` | `repeater` | `93:0` | locked state ignored |
| `minecraft:repeating_command_block[facing=down,*]` | `dispenser` | `23:0` | modern logic block collapsed to dispenser |
| `minecraft:repeating_command_block[facing=up,*]` | `dispenser` | `23:1` | modern logic block collapsed to dispenser |
| `minecraft:repeating_command_block[facing=north,*]` | `dispenser` | `23:2` | modern logic block collapsed to dispenser |
| `minecraft:repeating_command_block[facing=south,*]` | `dispenser` | `23:3` | modern logic block collapsed to dispenser |
| `minecraft:repeating_command_block[facing=west,*]` | `dispenser` | `23:4` | modern logic block collapsed to dispenser |
| `minecraft:repeating_command_block[facing=east,*]` | `dispenser` | `23:5` | modern logic block collapsed to dispenser |
| `minecraft:repeating_command_block[*]` | `dispenser` | `23:2` | modern logic block collapsed to dispenser |
| `minecraft:resin_block[*]` | `brick_block` | `45:0` |  |
| `minecraft:resin_brick_slab[type=bottom,*]` | `stone_slab` | `44:0` |  |
| `minecraft:resin_brick_slab[type=top,*]` | `stone_slab` | `44:8` |  |
| `minecraft:resin_brick_slab[type=double,*]` | `stone_slab` | `43:0` | double slab |
| `minecraft:resin_brick_slab[*]` | `stone_slab` | `44:0` |  |
| `minecraft:resin_brick_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:resin_brick_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:resin_brick_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:resin_brick_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:resin_brick_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:resin_brick_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:resin_brick_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:resin_brick_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:resin_brick_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:resin_brick_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:resin_bricks[*]` | `stonebrick` | `98:0` |  |
| `minecraft:resin_clump[*]` | `brick_block` | `45:0` |  |
| `minecraft:respawn_anchor[*]` | `obsidian` | `49:0` |  |
| `minecraft:rooted_dirt[*]` | `dirt` | `3:0` |  |
| `minecraft:rose_bush[*]` | `stone` | `1:0` | fallback |
| `minecraft:sand[*]` | `sand` | `12:0` |  |
| `minecraft:sandstone[*]` | `sandstone` | `24:0` |  |
| `minecraft:sandstone_slab[type=bottom,*]` | `stone_slab` | `44:1` |  |
| `minecraft:sandstone_slab[type=top,*]` | `stone_slab` | `44:9` |  |
| `minecraft:sandstone_slab[type=double,*]` | `stone_slab` | `43:1` | double slab |
| `minecraft:sandstone_slab[*]` | `stone_slab` | `44:1` |  |
| `minecraft:sandstone_stairs[facing=east,half=bottom,*]` | `sandstone_stairs` | `128:0` |  |
| `minecraft:sandstone_stairs[facing=east,half=top,*]` | `sandstone_stairs` | `128:4` |  |
| `minecraft:sandstone_stairs[facing=west,half=bottom,*]` | `sandstone_stairs` | `128:1` |  |
| `minecraft:sandstone_stairs[facing=west,half=top,*]` | `sandstone_stairs` | `128:5` |  |
| `minecraft:sandstone_stairs[facing=south,half=bottom,*]` | `sandstone_stairs` | `128:2` |  |
| `minecraft:sandstone_stairs[facing=south,half=top,*]` | `sandstone_stairs` | `128:6` |  |
| `minecraft:sandstone_stairs[facing=north,half=bottom,*]` | `sandstone_stairs` | `128:3` |  |
| `minecraft:sandstone_stairs[facing=north,half=top,*]` | `sandstone_stairs` | `128:7` |  |
| `minecraft:sandstone_stairs[*]` | `sandstone_stairs` | `128:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:sandstone_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:scaffolding[*]` | `stone` | `1:0` | fallback |
| `minecraft:sculk[*]` | `obsidian` | `49:0` |  |
| `minecraft:sculk_catalyst[*]` | `obsidian` | `49:0` |  |
| `minecraft:sculk_sensor[*]` | `obsidian` | `49:0` |  |
| `minecraft:sculk_shrieker[*]` | `obsidian` | `49:0` |  |
| `minecraft:sculk_vein[*]` | `obsidian` | `49:0` |  |
| `minecraft:sea_lantern[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:sea_pickle[*]` | `stone` | `1:0` | fallback |
| `minecraft:seagrass[*]` | `tallgrass` | `31:1` |  |
| `minecraft:short_dry_grass[*]` | `tallgrass` | `31:1` |  |
| `minecraft:short_grass[*]` | `tallgrass` | `31:1` |  |
| `minecraft:shroomlight[*]` | `glowstone` | `89:0` |  |
| `minecraft:shulker_box[*]` | `wool` | `35:0` | shulker box collapsed to wool |
| `minecraft:skeleton_skull[rotation=0,*]` | `mob_head` | `144:0` | standing head |
| `minecraft:skeleton_skull[rotation=1,*]` | `mob_head` | `144:1` | standing head |
| `minecraft:skeleton_skull[rotation=2,*]` | `mob_head` | `144:2` | standing head |
| `minecraft:skeleton_skull[rotation=3,*]` | `mob_head` | `144:3` | standing head |
| `minecraft:skeleton_skull[rotation=4,*]` | `mob_head` | `144:4` | standing head |
| `minecraft:skeleton_skull[rotation=5,*]` | `mob_head` | `144:5` | standing head |
| `minecraft:skeleton_skull[rotation=6,*]` | `mob_head` | `144:6` | standing head |
| `minecraft:skeleton_skull[rotation=7,*]` | `mob_head` | `144:7` | standing head |
| `minecraft:skeleton_skull[rotation=8,*]` | `mob_head` | `144:8` | standing head |
| `minecraft:skeleton_skull[rotation=9,*]` | `mob_head` | `144:9` | standing head |
| `minecraft:skeleton_skull[rotation=10,*]` | `mob_head` | `144:10` | standing head |
| `minecraft:skeleton_skull[rotation=11,*]` | `mob_head` | `144:11` | standing head |
| `minecraft:skeleton_skull[rotation=12,*]` | `mob_head` | `144:12` | standing head |
| `minecraft:skeleton_skull[rotation=13,*]` | `mob_head` | `144:13` | standing head |
| `minecraft:skeleton_skull[rotation=14,*]` | `mob_head` | `144:14` | standing head |
| `minecraft:skeleton_skull[rotation=15,*]` | `mob_head` | `144:15` | standing head |
| `minecraft:skeleton_skull[facing=north,*]` | `mob_head` | `144:2` | wall head |
| `minecraft:skeleton_skull[facing=south,*]` | `mob_head` | `144:3` | wall head |
| `minecraft:skeleton_skull[facing=west,*]` | `mob_head` | `144:4` | wall head |
| `minecraft:skeleton_skull[facing=east,*]` | `mob_head` | `144:5` | wall head |
| `minecraft:skeleton_skull[*]` | `mob_head` | `144:0` | head type collapsed |
| `minecraft:skeleton_wall_skull[rotation=0,*]` | `mob_head` | `144:0` | standing head |
| `minecraft:skeleton_wall_skull[rotation=1,*]` | `mob_head` | `144:1` | standing head |
| `minecraft:skeleton_wall_skull[rotation=2,*]` | `mob_head` | `144:2` | standing head |
| `minecraft:skeleton_wall_skull[rotation=3,*]` | `mob_head` | `144:3` | standing head |
| `minecraft:skeleton_wall_skull[rotation=4,*]` | `mob_head` | `144:4` | standing head |
| `minecraft:skeleton_wall_skull[rotation=5,*]` | `mob_head` | `144:5` | standing head |
| `minecraft:skeleton_wall_skull[rotation=6,*]` | `mob_head` | `144:6` | standing head |
| `minecraft:skeleton_wall_skull[rotation=7,*]` | `mob_head` | `144:7` | standing head |
| `minecraft:skeleton_wall_skull[rotation=8,*]` | `mob_head` | `144:8` | standing head |
| `minecraft:skeleton_wall_skull[rotation=9,*]` | `mob_head` | `144:9` | standing head |
| `minecraft:skeleton_wall_skull[rotation=10,*]` | `mob_head` | `144:10` | standing head |
| `minecraft:skeleton_wall_skull[rotation=11,*]` | `mob_head` | `144:11` | standing head |
| `minecraft:skeleton_wall_skull[rotation=12,*]` | `mob_head` | `144:12` | standing head |
| `minecraft:skeleton_wall_skull[rotation=13,*]` | `mob_head` | `144:13` | standing head |
| `minecraft:skeleton_wall_skull[rotation=14,*]` | `mob_head` | `144:14` | standing head |
| `minecraft:skeleton_wall_skull[rotation=15,*]` | `mob_head` | `144:15` | standing head |
| `minecraft:skeleton_wall_skull[facing=north,*]` | `mob_head` | `144:2` | wall head |
| `minecraft:skeleton_wall_skull[facing=south,*]` | `mob_head` | `144:3` | wall head |
| `minecraft:skeleton_wall_skull[facing=west,*]` | `mob_head` | `144:4` | wall head |
| `minecraft:skeleton_wall_skull[facing=east,*]` | `mob_head` | `144:5` | wall head |
| `minecraft:skeleton_wall_skull[*]` | `mob_head` | `144:0` | head type collapsed |
| `minecraft:slime_block[*]` | `wool` | `35:5` |  |
| `minecraft:small_amethyst_bud[*]` | `obsidian` | `49:0` |  |
| `minecraft:small_dripleaf[*]` | `stone` | `1:0` | fallback |
| `minecraft:smithing_table[*]` | `crafting_table` | `58:0` |  |
| `minecraft:smoker[lit=false,facing=north,*]` | `furnace` | `61:2` | furnace |
| `minecraft:smoker[lit=true,facing=north,*]` | `furnace` | `62:2` | lit furnace |
| `minecraft:smoker[lit=false,facing=south,*]` | `furnace` | `61:3` | furnace |
| `minecraft:smoker[lit=true,facing=south,*]` | `furnace` | `62:3` | lit furnace |
| `minecraft:smoker[lit=false,facing=west,*]` | `furnace` | `61:4` | furnace |
| `minecraft:smoker[lit=true,facing=west,*]` | `furnace` | `62:4` | lit furnace |
| `minecraft:smoker[lit=false,facing=east,*]` | `furnace` | `61:5` | furnace |
| `minecraft:smoker[lit=true,facing=east,*]` | `furnace` | `62:5` | lit furnace |
| `minecraft:smoker[*]` | `furnace` | `61:2` | defaults north-facing |
| `minecraft:smooth_basalt[*]` | `stone` | `1:0` |  |
| `minecraft:smooth_quartz[axis=y,*]` | `quartz_block` | `155:2` | pillar quartz vertical |
| `minecraft:smooth_quartz[axis=x,*]` | `quartz_block` | `155:3` | pillar quartz horizontal |
| `minecraft:smooth_quartz[axis=z,*]` | `quartz_block` | `155:4` | pillar quartz horizontal |
| `minecraft:smooth_quartz[*]` | `quartz_block` | `155:0` | smooth/chiseled collapse to plain quartz block |
| `minecraft:smooth_quartz_slab[type=bottom,*]` | `stone_slab` | `44:7` |  |
| `minecraft:smooth_quartz_slab[type=top,*]` | `stone_slab` | `44:15` |  |
| `minecraft:smooth_quartz_slab[type=double,*]` | `stone_slab` | `43:7` | double slab |
| `minecraft:smooth_quartz_slab[*]` | `stone_slab` | `44:7` |  |
| `minecraft:smooth_quartz_stairs[facing=east,half=bottom,*]` | `quartz_stairs` | `156:0` |  |
| `minecraft:smooth_quartz_stairs[facing=east,half=top,*]` | `quartz_stairs` | `156:4` |  |
| `minecraft:smooth_quartz_stairs[facing=west,half=bottom,*]` | `quartz_stairs` | `156:1` |  |
| `minecraft:smooth_quartz_stairs[facing=west,half=top,*]` | `quartz_stairs` | `156:5` |  |
| `minecraft:smooth_quartz_stairs[facing=south,half=bottom,*]` | `quartz_stairs` | `156:2` |  |
| `minecraft:smooth_quartz_stairs[facing=south,half=top,*]` | `quartz_stairs` | `156:6` |  |
| `minecraft:smooth_quartz_stairs[facing=north,half=bottom,*]` | `quartz_stairs` | `156:3` |  |
| `minecraft:smooth_quartz_stairs[facing=north,half=top,*]` | `quartz_stairs` | `156:7` |  |
| `minecraft:smooth_quartz_stairs[*]` | `quartz_stairs` | `156:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:smooth_red_sandstone[*]` | `sandstone` | `24:0` |  |
| `minecraft:smooth_red_sandstone_slab[type=bottom,*]` | `stone_slab` | `44:1` |  |
| `minecraft:smooth_red_sandstone_slab[type=top,*]` | `stone_slab` | `44:9` |  |
| `minecraft:smooth_red_sandstone_slab[type=double,*]` | `stone_slab` | `43:1` | double slab |
| `minecraft:smooth_red_sandstone_slab[*]` | `stone_slab` | `44:1` |  |
| `minecraft:smooth_red_sandstone_stairs[facing=east,half=bottom,*]` | `sandstone_stairs` | `128:0` |  |
| `minecraft:smooth_red_sandstone_stairs[facing=east,half=top,*]` | `sandstone_stairs` | `128:4` |  |
| `minecraft:smooth_red_sandstone_stairs[facing=west,half=bottom,*]` | `sandstone_stairs` | `128:1` |  |
| `minecraft:smooth_red_sandstone_stairs[facing=west,half=top,*]` | `sandstone_stairs` | `128:5` |  |
| `minecraft:smooth_red_sandstone_stairs[facing=south,half=bottom,*]` | `sandstone_stairs` | `128:2` |  |
| `minecraft:smooth_red_sandstone_stairs[facing=south,half=top,*]` | `sandstone_stairs` | `128:6` |  |
| `minecraft:smooth_red_sandstone_stairs[facing=north,half=bottom,*]` | `sandstone_stairs` | `128:3` |  |
| `minecraft:smooth_red_sandstone_stairs[facing=north,half=top,*]` | `sandstone_stairs` | `128:7` |  |
| `minecraft:smooth_red_sandstone_stairs[*]` | `sandstone_stairs` | `128:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:smooth_sandstone[*]` | `sandstone` | `24:0` |  |
| `minecraft:smooth_sandstone_slab[type=bottom,*]` | `stone_slab` | `44:1` |  |
| `minecraft:smooth_sandstone_slab[type=top,*]` | `stone_slab` | `44:9` |  |
| `minecraft:smooth_sandstone_slab[type=double,*]` | `stone_slab` | `43:1` | double slab |
| `minecraft:smooth_sandstone_slab[*]` | `stone_slab` | `44:1` |  |
| `minecraft:smooth_sandstone_stairs[facing=east,half=bottom,*]` | `sandstone_stairs` | `128:0` |  |
| `minecraft:smooth_sandstone_stairs[facing=east,half=top,*]` | `sandstone_stairs` | `128:4` |  |
| `minecraft:smooth_sandstone_stairs[facing=west,half=bottom,*]` | `sandstone_stairs` | `128:1` |  |
| `minecraft:smooth_sandstone_stairs[facing=west,half=top,*]` | `sandstone_stairs` | `128:5` |  |
| `minecraft:smooth_sandstone_stairs[facing=south,half=bottom,*]` | `sandstone_stairs` | `128:2` |  |
| `minecraft:smooth_sandstone_stairs[facing=south,half=top,*]` | `sandstone_stairs` | `128:6` |  |
| `minecraft:smooth_sandstone_stairs[facing=north,half=bottom,*]` | `sandstone_stairs` | `128:3` |  |
| `minecraft:smooth_sandstone_stairs[facing=north,half=top,*]` | `sandstone_stairs` | `128:7` |  |
| `minecraft:smooth_sandstone_stairs[*]` | `sandstone_stairs` | `128:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:smooth_stone[*]` | `stone` | `1:0` |  |
| `minecraft:smooth_stone_slab[type=bottom,*]` | `stone_slab` | `44:0` |  |
| `minecraft:smooth_stone_slab[type=top,*]` | `stone_slab` | `44:8` |  |
| `minecraft:smooth_stone_slab[type=double,*]` | `stone_slab` | `43:0` | double slab |
| `minecraft:smooth_stone_slab[*]` | `stone_slab` | `44:0` |  |
| `minecraft:sniffer_egg[*]` | `dragon_egg` | `122:0` |  |
| `minecraft:snow[layers=1,*]` | `snow_layer` | `78:0` |  |
| `minecraft:snow[layers=2,*]` | `snow_layer` | `78:1` |  |
| `minecraft:snow[layers=3,*]` | `snow_layer` | `78:2` |  |
| `minecraft:snow[layers=4,*]` | `snow_layer` | `78:3` |  |
| `minecraft:snow[layers=5,*]` | `snow_layer` | `78:4` |  |
| `minecraft:snow[layers=6,*]` | `snow_layer` | `78:5` |  |
| `minecraft:snow[layers=7,*]` | `snow_layer` | `78:6` |  |
| `minecraft:snow[layers=8,*]` | `snow_layer` | `78:7` |  |
| `minecraft:snow[*]` | `snow_layer` | `78:0` |  |
| `minecraft:snow_block[*]` | `snow_block` | `80:0` |  |
| `minecraft:soul_campfire[*]` | `netherrack` | `87:0` |  |
| `minecraft:soul_fire[*]` | `stone` | `1:0` | fallback |
| `minecraft:soul_lantern[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:soul_sand[*]` | `sand` | `12:0` |  |
| `minecraft:soul_soil[*]` | `soul_sand` | `88:0` |  |
| `minecraft:soul_torch[facing=east,*]` | `torch` | `50:1` |  |
| `minecraft:soul_torch[facing=west,*]` | `torch` | `50:2` |  |
| `minecraft:soul_torch[facing=south,*]` | `torch` | `50:3` |  |
| `minecraft:soul_torch[facing=north,*]` | `torch` | `50:4` |  |
| `minecraft:soul_torch[floor=*]` | `torch` | `50:5` |  |
| `minecraft:soul_torch[*]` | `torch` | `50:5` |  |
| `minecraft:soul_wall_torch[facing=east,*]` | `torch` | `50:1` |  |
| `minecraft:soul_wall_torch[facing=west,*]` | `torch` | `50:2` |  |
| `minecraft:soul_wall_torch[facing=south,*]` | `torch` | `50:3` |  |
| `minecraft:soul_wall_torch[facing=north,*]` | `torch` | `50:4` |  |
| `minecraft:soul_wall_torch[floor=*]` | `torch` | `50:5` |  |
| `minecraft:soul_wall_torch[*]` | `torch` | `50:5` |  |
| `minecraft:spawner[*]` | `mob_spawner` | `52:0` |  |
| `minecraft:sponge[*]` | `wool` | `35:11` |  |
| `minecraft:spore_blossom[*]` | `stone` | `1:0` | fallback |
| `minecraft:spruce_button[face=floor,*]` | `wooden_button` | `143:1` |  |
| `minecraft:spruce_button[face=wall,facing=east,*]` | `wooden_button` | `143:2` |  |
| `minecraft:spruce_button[face=wall,facing=west,*]` | `wooden_button` | `143:1` |  |
| `minecraft:spruce_button[face=wall,facing=south,*]` | `wooden_button` | `143:3` |  |
| `minecraft:spruce_button[face=wall,facing=north,*]` | `wooden_button` | `143:4` |  |
| `minecraft:spruce_button[powered=true,*]` | `wooden_button` | `143:9` | powered bit approximated (+8) |
| `minecraft:spruce_button[*]` | `wooden_button` | `143:1` |  |
| `minecraft:spruce_door[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:spruce_door[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:spruce_door[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:spruce_door[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:spruce_door[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:spruce_door[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:spruce_door[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:spruce_door[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:spruce_door[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:spruce_door[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:spruce_door[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:spruce_fence[*]` | `fence` | `85:0` |  |
| `minecraft:spruce_fence_gate[facing=south,open=false,*]` | `fence_gate` | `107:0` |  |
| `minecraft:spruce_fence_gate[facing=south,open=true,*]` | `fence_gate` | `107:4` |  |
| `minecraft:spruce_fence_gate[facing=west,open=false,*]` | `fence_gate` | `107:1` |  |
| `minecraft:spruce_fence_gate[facing=west,open=true,*]` | `fence_gate` | `107:5` |  |
| `minecraft:spruce_fence_gate[facing=north,open=false,*]` | `fence_gate` | `107:2` |  |
| `minecraft:spruce_fence_gate[facing=north,open=true,*]` | `fence_gate` | `107:6` |  |
| `minecraft:spruce_fence_gate[facing=east,open=false,*]` | `fence_gate` | `107:3` |  |
| `minecraft:spruce_fence_gate[facing=east,open=true,*]` | `fence_gate` | `107:7` |  |
| `minecraft:spruce_fence_gate[*]` | `fence_gate` | `107:0` |  |
| `minecraft:spruce_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:spruce_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:spruce_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:spruce_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:spruce_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:spruce_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:spruce_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:spruce_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:spruce_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:spruce_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:spruce_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:spruce_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:spruce_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:spruce_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:spruce_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:spruce_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:spruce_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:spruce_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:spruce_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:spruce_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:spruce_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:spruce_leaves[*]` | `leaves` | `18:1` |  |
| `minecraft:spruce_log[axis=y,*]` | `log` | `17:1` |  |
| `minecraft:spruce_log[axis=x,*]` | `log` | `17:5` |  |
| `minecraft:spruce_log[axis=z,*]` | `log` | `17:9` |  |
| `minecraft:spruce_log[*]` | `log` | `17:1` |  |
| `minecraft:spruce_planks[*]` | `planks` | `5:1` |  |
| `minecraft:spruce_pressure_plate[*]` | `wooden_pressure_plate` | `72:0` |  |
| `minecraft:spruce_sapling[*]` | `sapling` | `6:1` |  |
| `minecraft:spruce_shelf[*]` | `stone` | `1:0` | fallback |
| `minecraft:spruce_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:spruce_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:spruce_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:spruce_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:spruce_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:spruce_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:spruce_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:spruce_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:spruce_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:spruce_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:spruce_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:spruce_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:spruce_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:spruce_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:spruce_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:spruce_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:spruce_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:spruce_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:spruce_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:spruce_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:spruce_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:spruce_slab[type=bottom,*]` | `wooden_slab` | `126:1` |  |
| `minecraft:spruce_slab[type=top,*]` | `wooden_slab` | `126:9` |  |
| `minecraft:spruce_slab[type=double,*]` | `wooden_slab` | `125:1` | double slab |
| `minecraft:spruce_slab[*]` | `wooden_slab` | `126:1` |  |
| `minecraft:spruce_stairs[facing=east,half=bottom,*]` | `spruce_stairs` | `134:0` |  |
| `minecraft:spruce_stairs[facing=east,half=top,*]` | `spruce_stairs` | `134:4` |  |
| `minecraft:spruce_stairs[facing=west,half=bottom,*]` | `spruce_stairs` | `134:1` |  |
| `minecraft:spruce_stairs[facing=west,half=top,*]` | `spruce_stairs` | `134:5` |  |
| `minecraft:spruce_stairs[facing=south,half=bottom,*]` | `spruce_stairs` | `134:2` |  |
| `minecraft:spruce_stairs[facing=south,half=top,*]` | `spruce_stairs` | `134:6` |  |
| `minecraft:spruce_stairs[facing=north,half=bottom,*]` | `spruce_stairs` | `134:3` |  |
| `minecraft:spruce_stairs[facing=north,half=top,*]` | `spruce_stairs` | `134:7` |  |
| `minecraft:spruce_stairs[*]` | `spruce_stairs` | `134:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:spruce_trapdoor[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:spruce_trapdoor[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:spruce_trapdoor[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:spruce_trapdoor[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:spruce_trapdoor[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:spruce_trapdoor[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:spruce_trapdoor[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:spruce_trapdoor[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:spruce_trapdoor[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:spruce_trapdoor[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:spruce_trapdoor[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:spruce_wall_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:spruce_wall_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:spruce_wall_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:spruce_wall_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:spruce_wall_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:spruce_wall_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:spruce_wall_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:spruce_wall_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:spruce_wall_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:spruce_wall_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:spruce_wall_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:spruce_wall_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:spruce_wall_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:spruce_wall_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:spruce_wall_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:spruce_wall_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:spruce_wall_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:spruce_wall_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:spruce_wall_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:spruce_wall_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:spruce_wall_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:spruce_wall_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:spruce_wall_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:spruce_wall_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:spruce_wall_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:spruce_wall_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:spruce_wall_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:spruce_wall_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:spruce_wall_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:spruce_wall_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:spruce_wall_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:spruce_wall_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:spruce_wall_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:spruce_wall_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:spruce_wall_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:spruce_wall_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:spruce_wall_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:spruce_wall_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:spruce_wall_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:spruce_wall_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:spruce_wall_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:spruce_wall_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:spruce_wood[axis=y,*]` | `log` | `17:1` |  |
| `minecraft:spruce_wood[axis=x,*]` | `log` | `17:5` |  |
| `minecraft:spruce_wood[axis=z,*]` | `log` | `17:9` |  |
| `minecraft:spruce_wood[*]` | `log` | `17:1` |  |
| `minecraft:sticky_piston[facing=down,extended=false,*]` | `sticky_piston` | `29:0` |  |
| `minecraft:sticky_piston[facing=down,extended=true,*]` | `sticky_piston` | `29:8` |  |
| `minecraft:sticky_piston[facing=up,extended=false,*]` | `sticky_piston` | `29:1` |  |
| `minecraft:sticky_piston[facing=up,extended=true,*]` | `sticky_piston` | `29:9` |  |
| `minecraft:sticky_piston[facing=north,extended=false,*]` | `sticky_piston` | `29:2` |  |
| `minecraft:sticky_piston[facing=north,extended=true,*]` | `sticky_piston` | `29:10` |  |
| `minecraft:sticky_piston[facing=south,extended=false,*]` | `sticky_piston` | `29:3` |  |
| `minecraft:sticky_piston[facing=south,extended=true,*]` | `sticky_piston` | `29:11` |  |
| `minecraft:sticky_piston[facing=west,extended=false,*]` | `sticky_piston` | `29:4` |  |
| `minecraft:sticky_piston[facing=west,extended=true,*]` | `sticky_piston` | `29:12` |  |
| `minecraft:sticky_piston[facing=east,extended=false,*]` | `sticky_piston` | `29:5` |  |
| `minecraft:sticky_piston[facing=east,extended=true,*]` | `sticky_piston` | `29:13` |  |
| `minecraft:sticky_piston[*]` | `sticky_piston` | `29:2` |  |
| `minecraft:stone[*]` | `stone` | `1:0` |  |
| `minecraft:stone_brick_slab[type=bottom,*]` | `stone_slab` | `44:4` |  |
| `minecraft:stone_brick_slab[type=top,*]` | `stone_slab` | `44:12` |  |
| `minecraft:stone_brick_slab[type=double,*]` | `stone_slab` | `43:4` | double slab |
| `minecraft:stone_brick_slab[*]` | `stone_slab` | `44:4` |  |
| `minecraft:stone_brick_stairs[facing=east,half=bottom,*]` | `brick_stairs` | `108:0` |  |
| `minecraft:stone_brick_stairs[facing=east,half=top,*]` | `brick_stairs` | `108:4` |  |
| `minecraft:stone_brick_stairs[facing=west,half=bottom,*]` | `brick_stairs` | `108:1` |  |
| `minecraft:stone_brick_stairs[facing=west,half=top,*]` | `brick_stairs` | `108:5` |  |
| `minecraft:stone_brick_stairs[facing=south,half=bottom,*]` | `brick_stairs` | `108:2` |  |
| `minecraft:stone_brick_stairs[facing=south,half=top,*]` | `brick_stairs` | `108:6` |  |
| `minecraft:stone_brick_stairs[facing=north,half=bottom,*]` | `brick_stairs` | `108:3` |  |
| `minecraft:stone_brick_stairs[facing=north,half=top,*]` | `brick_stairs` | `108:7` |  |
| `minecraft:stone_brick_stairs[*]` | `brick_stairs` | `108:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:stone_brick_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:stone_bricks[*]` | `stonebrick` | `98:0` |  |
| `minecraft:stone_button[face=floor,*]` | `stone_button` | `77:1` |  |
| `minecraft:stone_button[face=wall,facing=east,*]` | `stone_button` | `77:2` |  |
| `minecraft:stone_button[face=wall,facing=west,*]` | `stone_button` | `77:1` |  |
| `minecraft:stone_button[face=wall,facing=south,*]` | `stone_button` | `77:3` |  |
| `minecraft:stone_button[face=wall,facing=north,*]` | `stone_button` | `77:4` |  |
| `minecraft:stone_button[powered=true,*]` | `stone_button` | `77:9` | powered bit approximated (+8) |
| `minecraft:stone_button[*]` | `stone_button` | `77:1` |  |
| `minecraft:stone_pressure_plate[*]` | `stone_pressure_plate` | `70:0` |  |
| `minecraft:stone_slab[type=bottom,*]` | `stone_slab` | `44:0` |  |
| `minecraft:stone_slab[type=top,*]` | `stone_slab` | `44:8` |  |
| `minecraft:stone_slab[type=double,*]` | `stone_slab` | `43:0` | double slab |
| `minecraft:stone_slab[*]` | `stone_slab` | `44:0` |  |
| `minecraft:stone_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:stone_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:stone_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:stone_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:stone_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:stone_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:stone_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:stone_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:stone_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:stonecutter[*]` | `stone` | `1:0` |  |
| `minecraft:stripped_acacia_log[axis=y,*]` | `log` | `17:3` |  |
| `minecraft:stripped_acacia_log[axis=x,*]` | `log` | `17:7` |  |
| `minecraft:stripped_acacia_log[axis=z,*]` | `log` | `17:11` |  |
| `minecraft:stripped_acacia_log[*]` | `log` | `17:3` |  |
| `minecraft:stripped_acacia_wood[axis=y,*]` | `log` | `17:3` |  |
| `minecraft:stripped_acacia_wood[axis=x,*]` | `log` | `17:7` |  |
| `minecraft:stripped_acacia_wood[axis=z,*]` | `log` | `17:11` |  |
| `minecraft:stripped_acacia_wood[*]` | `log` | `17:3` |  |
| `minecraft:stripped_bamboo_block[*]` | `sapling` | `6:2` |  |
| `minecraft:stripped_birch_log[axis=y,*]` | `log` | `17:2` |  |
| `minecraft:stripped_birch_log[axis=x,*]` | `log` | `17:6` |  |
| `minecraft:stripped_birch_log[axis=z,*]` | `log` | `17:10` |  |
| `minecraft:stripped_birch_log[*]` | `log` | `17:2` |  |
| `minecraft:stripped_birch_wood[axis=y,*]` | `log` | `17:2` |  |
| `minecraft:stripped_birch_wood[axis=x,*]` | `log` | `17:6` |  |
| `minecraft:stripped_birch_wood[axis=z,*]` | `log` | `17:10` |  |
| `minecraft:stripped_birch_wood[*]` | `log` | `17:2` |  |
| `minecraft:stripped_cherry_log[axis=y,*]` | `log` | `17:2` |  |
| `minecraft:stripped_cherry_log[axis=x,*]` | `log` | `17:6` |  |
| `minecraft:stripped_cherry_log[axis=z,*]` | `log` | `17:10` |  |
| `minecraft:stripped_cherry_log[*]` | `log` | `17:2` |  |
| `minecraft:stripped_cherry_wood[axis=y,*]` | `log` | `17:2` |  |
| `minecraft:stripped_cherry_wood[axis=x,*]` | `log` | `17:6` |  |
| `minecraft:stripped_cherry_wood[axis=z,*]` | `log` | `17:10` |  |
| `minecraft:stripped_cherry_wood[*]` | `log` | `17:2` |  |
| `minecraft:stripped_crimson_hyphae[*]` | `stone` | `1:0` | fallback |
| `minecraft:stripped_crimson_stem[*]` | `stone` | `1:0` | fallback |
| `minecraft:stripped_dark_oak_log[axis=y,*]` | `log` | `17:1` |  |
| `minecraft:stripped_dark_oak_log[axis=x,*]` | `log` | `17:5` |  |
| `minecraft:stripped_dark_oak_log[axis=z,*]` | `log` | `17:9` |  |
| `minecraft:stripped_dark_oak_log[*]` | `log` | `17:1` |  |
| `minecraft:stripped_dark_oak_wood[axis=y,*]` | `log` | `17:1` |  |
| `minecraft:stripped_dark_oak_wood[axis=x,*]` | `log` | `17:5` |  |
| `minecraft:stripped_dark_oak_wood[axis=z,*]` | `log` | `17:9` |  |
| `minecraft:stripped_dark_oak_wood[*]` | `log` | `17:1` |  |
| `minecraft:stripped_jungle_log[axis=y,*]` | `log` | `17:3` |  |
| `minecraft:stripped_jungle_log[axis=x,*]` | `log` | `17:7` |  |
| `minecraft:stripped_jungle_log[axis=z,*]` | `log` | `17:11` |  |
| `minecraft:stripped_jungle_log[*]` | `log` | `17:3` |  |
| `minecraft:stripped_jungle_wood[axis=y,*]` | `log` | `17:3` |  |
| `minecraft:stripped_jungle_wood[axis=x,*]` | `log` | `17:7` |  |
| `minecraft:stripped_jungle_wood[axis=z,*]` | `log` | `17:11` |  |
| `minecraft:stripped_jungle_wood[*]` | `log` | `17:3` |  |
| `minecraft:stripped_mangrove_log[axis=y,*]` | `log` | `17:3` |  |
| `minecraft:stripped_mangrove_log[axis=x,*]` | `log` | `17:7` |  |
| `minecraft:stripped_mangrove_log[axis=z,*]` | `log` | `17:11` |  |
| `minecraft:stripped_mangrove_log[*]` | `log` | `17:3` |  |
| `minecraft:stripped_mangrove_wood[axis=y,*]` | `log` | `17:3` |  |
| `minecraft:stripped_mangrove_wood[axis=x,*]` | `log` | `17:7` |  |
| `minecraft:stripped_mangrove_wood[axis=z,*]` | `log` | `17:11` |  |
| `minecraft:stripped_mangrove_wood[*]` | `log` | `17:3` |  |
| `minecraft:stripped_oak_log[axis=y,*]` | `log` | `17:0` |  |
| `minecraft:stripped_oak_log[axis=x,*]` | `log` | `17:4` |  |
| `minecraft:stripped_oak_log[axis=z,*]` | `log` | `17:8` |  |
| `minecraft:stripped_oak_log[*]` | `log` | `17:0` |  |
| `minecraft:stripped_oak_wood[axis=y,*]` | `log` | `17:0` |  |
| `minecraft:stripped_oak_wood[axis=x,*]` | `log` | `17:4` |  |
| `minecraft:stripped_oak_wood[axis=z,*]` | `log` | `17:8` |  |
| `minecraft:stripped_oak_wood[*]` | `log` | `17:0` |  |
| `minecraft:stripped_pale_oak_log[axis=y,*]` | `log` | `17:1` |  |
| `minecraft:stripped_pale_oak_log[axis=x,*]` | `log` | `17:5` |  |
| `minecraft:stripped_pale_oak_log[axis=z,*]` | `log` | `17:9` |  |
| `minecraft:stripped_pale_oak_log[*]` | `log` | `17:1` |  |
| `minecraft:stripped_pale_oak_wood[axis=y,*]` | `log` | `17:1` |  |
| `minecraft:stripped_pale_oak_wood[axis=x,*]` | `log` | `17:5` |  |
| `minecraft:stripped_pale_oak_wood[axis=z,*]` | `log` | `17:9` |  |
| `minecraft:stripped_pale_oak_wood[*]` | `log` | `17:1` |  |
| `minecraft:stripped_spruce_log[axis=y,*]` | `log` | `17:1` |  |
| `minecraft:stripped_spruce_log[axis=x,*]` | `log` | `17:5` |  |
| `minecraft:stripped_spruce_log[axis=z,*]` | `log` | `17:9` |  |
| `minecraft:stripped_spruce_log[*]` | `log` | `17:1` |  |
| `minecraft:stripped_spruce_wood[axis=y,*]` | `log` | `17:1` |  |
| `minecraft:stripped_spruce_wood[axis=x,*]` | `log` | `17:5` |  |
| `minecraft:stripped_spruce_wood[axis=z,*]` | `log` | `17:9` |  |
| `minecraft:stripped_spruce_wood[*]` | `log` | `17:1` |  |
| `minecraft:stripped_warped_hyphae[*]` | `stone` | `1:0` | fallback |
| `minecraft:stripped_warped_stem[*]` | `stone` | `1:0` | fallback |
| `minecraft:structure_block[*]` | `stone` | `1:0` | fallback |
| `minecraft:structure_void[*]` | `stone` | `1:0` | fallback |
| `minecraft:sugar_cane[*]` | `stone` | `1:0` | fallback |
| `minecraft:sunflower[*]` | `red_flower` | `38:0` |  |
| `minecraft:suspicious_gravel[*]` | `dirt` | `3:0` |  |
| `minecraft:suspicious_sand[*]` | `sand` | `12:0` |  |
| `minecraft:sweet_berry_bush[*]` | `stone` | `1:0` | fallback |
| `minecraft:tall_dry_grass[*]` | `tallgrass` | `31:1` |  |
| `minecraft:tall_grass[*]` | `tallgrass` | `31:1` |  |
| `minecraft:tall_seagrass[*]` | `tallgrass` | `31:1` |  |
| `minecraft:target[*]` | `wool` | `35:14` |  |
| `minecraft:terracotta[*]` | `stained_hardened_clay` | `159:0` |  |
| `minecraft:test_block[*]` | `stone` | `1:0` | fallback |
| `minecraft:test_instance_block[*]` | `stone` | `1:0` | fallback |
| `minecraft:tinted_glass[*]` | `glass` | `20:0` |  |
| `minecraft:tnt[*]` | `tnt` | `46:0` |  |
| `minecraft:torch[facing=east,*]` | `torch` | `50:1` |  |
| `minecraft:torch[facing=west,*]` | `torch` | `50:2` |  |
| `minecraft:torch[facing=south,*]` | `torch` | `50:3` |  |
| `minecraft:torch[facing=north,*]` | `torch` | `50:4` |  |
| `minecraft:torch[floor=*]` | `torch` | `50:5` |  |
| `minecraft:torch[*]` | `torch` | `50:5` |  |
| `minecraft:torchflower[*]` | `red_flower` | `38:0` |  |
| `minecraft:torchflower_crop[*]` | `red_flower` | `38:0` |  |
| `minecraft:trapped_chest[facing=north,*]` | `chest` | `54:2` |  |
| `minecraft:trapped_chest[facing=south,*]` | `chest` | `54:3` |  |
| `minecraft:trapped_chest[facing=west,*]` | `chest` | `54:4` |  |
| `minecraft:trapped_chest[facing=east,*]` | `chest` | `54:5` |  |
| `minecraft:trapped_chest[*]` | `chest` | `54:2` |  |
| `minecraft:trial_spawner[*]` | `mob_spawner` | `52:0` |  |
| `minecraft:tripwire[*]` | `tripwire` | `132:0` |  |
| `minecraft:tripwire_hook[facing=north,powered=false,*]` | `tripwire_hook` | `131:0` | unpowered |
| `minecraft:tripwire_hook[facing=north,powered=true,*]` | `tripwire_hook` | `131:8` | powered |
| `minecraft:tripwire_hook[facing=east,powered=false,*]` | `tripwire_hook` | `131:1` | unpowered |
| `minecraft:tripwire_hook[facing=east,powered=true,*]` | `tripwire_hook` | `131:9` | powered |
| `minecraft:tripwire_hook[facing=south,powered=false,*]` | `tripwire_hook` | `131:2` | unpowered |
| `minecraft:tripwire_hook[facing=south,powered=true,*]` | `tripwire_hook` | `131:10` | powered |
| `minecraft:tripwire_hook[facing=west,powered=false,*]` | `tripwire_hook` | `131:3` | unpowered |
| `minecraft:tripwire_hook[facing=west,powered=true,*]` | `tripwire_hook` | `131:11` | powered |
| `minecraft:tripwire_hook[*]` | `tripwire_hook` | `131:0` | attached bit ignored |
| `minecraft:tube_coral[*]` | `wool` | `35:11` |  |
| `minecraft:tube_coral_block[*]` | `wool` | `35:11` |  |
| `minecraft:tube_coral_fan[*]` | `wool` | `35:11` |  |
| `minecraft:tube_coral_wall_fan[*]` | `wool` | `35:11` |  |
| `minecraft:tuff[*]` | `stone` | `1:0` |  |
| `minecraft:tuff_brick_slab[type=bottom,*]` | `stone_slab` | `44:4` |  |
| `minecraft:tuff_brick_slab[type=top,*]` | `stone_slab` | `44:12` |  |
| `minecraft:tuff_brick_slab[type=double,*]` | `stone_slab` | `43:4` | double slab |
| `minecraft:tuff_brick_slab[*]` | `stone_slab` | `44:4` |  |
| `minecraft:tuff_brick_stairs[facing=east,half=bottom,*]` | `brick_stairs` | `108:0` |  |
| `minecraft:tuff_brick_stairs[facing=east,half=top,*]` | `brick_stairs` | `108:4` |  |
| `minecraft:tuff_brick_stairs[facing=west,half=bottom,*]` | `brick_stairs` | `108:1` |  |
| `minecraft:tuff_brick_stairs[facing=west,half=top,*]` | `brick_stairs` | `108:5` |  |
| `minecraft:tuff_brick_stairs[facing=south,half=bottom,*]` | `brick_stairs` | `108:2` |  |
| `minecraft:tuff_brick_stairs[facing=south,half=top,*]` | `brick_stairs` | `108:6` |  |
| `minecraft:tuff_brick_stairs[facing=north,half=bottom,*]` | `brick_stairs` | `108:3` |  |
| `minecraft:tuff_brick_stairs[facing=north,half=top,*]` | `brick_stairs` | `108:7` |  |
| `minecraft:tuff_brick_stairs[*]` | `brick_stairs` | `108:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:tuff_brick_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:tuff_bricks[*]` | `stonebrick` | `98:0` |  |
| `minecraft:tuff_slab[type=bottom,*]` | `stone_slab` | `44:5` |  |
| `minecraft:tuff_slab[type=top,*]` | `stone_slab` | `44:13` |  |
| `minecraft:tuff_slab[type=double,*]` | `stone_slab` | `43:5` | double slab |
| `minecraft:tuff_slab[*]` | `stone_slab` | `44:5` |  |
| `minecraft:tuff_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:tuff_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:tuff_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:tuff_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:tuff_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:tuff_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:tuff_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:tuff_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:tuff_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:tuff_wall[*]` | `cobblestone_wall` | `139:0` |  |
| `minecraft:turtle_egg[*]` | `dragon_egg` | `122:0` |  |
| `minecraft:twisting_vines[*]` | `stone` | `1:0` | fallback |
| `minecraft:twisting_vines_plant[*]` | `stone` | `1:0` | fallback |
| `minecraft:vault[*]` | `mob_spawner` | `52:0` |  |
| `minecraft:verdant_froglight[*]` | `glowstone` | `89:0` |  |
| `minecraft:vine[south=true,*]` | `vine` | `106:1` | single-side vine |
| `minecraft:vine[west=true,*]` | `vine` | `106:2` | single-side vine |
| `minecraft:vine[north=true,*]` | `vine` | `106:4` | single-side vine |
| `minecraft:vine[east=true,*]` | `vine` | `106:8` | single-side vine |
| `minecraft:vine[*]` | `vine` | `106:0` | multi-side vines need bitwise merge in code |
| `minecraft:void_air[*]` | `air` | `0:0` |  |
| `minecraft:wall_torch[facing=east,*]` | `torch` | `50:1` |  |
| `minecraft:wall_torch[facing=west,*]` | `torch` | `50:2` |  |
| `minecraft:wall_torch[facing=south,*]` | `torch` | `50:3` |  |
| `minecraft:wall_torch[facing=north,*]` | `torch` | `50:4` |  |
| `minecraft:wall_torch[floor=*]` | `torch` | `50:5` |  |
| `minecraft:wall_torch[*]` | `torch` | `50:5` |  |
| `minecraft:warped_button[face=floor,*]` | `wooden_button` | `143:1` |  |
| `minecraft:warped_button[face=wall,facing=east,*]` | `wooden_button` | `143:2` |  |
| `minecraft:warped_button[face=wall,facing=west,*]` | `wooden_button` | `143:1` |  |
| `minecraft:warped_button[face=wall,facing=south,*]` | `wooden_button` | `143:3` |  |
| `minecraft:warped_button[face=wall,facing=north,*]` | `wooden_button` | `143:4` |  |
| `minecraft:warped_button[powered=true,*]` | `wooden_button` | `143:9` | powered bit approximated (+8) |
| `minecraft:warped_button[*]` | `wooden_button` | `143:1` |  |
| `minecraft:warped_door[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:warped_door[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:warped_door[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:warped_door[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:warped_door[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:warped_door[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:warped_door[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:warped_door[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:warped_door[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:warped_door[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:warped_door[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:warped_fence[*]` | `fence` | `85:0` |  |
| `minecraft:warped_fence_gate[facing=south,open=false,*]` | `fence_gate` | `107:0` |  |
| `minecraft:warped_fence_gate[facing=south,open=true,*]` | `fence_gate` | `107:4` |  |
| `minecraft:warped_fence_gate[facing=west,open=false,*]` | `fence_gate` | `107:1` |  |
| `minecraft:warped_fence_gate[facing=west,open=true,*]` | `fence_gate` | `107:5` |  |
| `minecraft:warped_fence_gate[facing=north,open=false,*]` | `fence_gate` | `107:2` |  |
| `minecraft:warped_fence_gate[facing=north,open=true,*]` | `fence_gate` | `107:6` |  |
| `minecraft:warped_fence_gate[facing=east,open=false,*]` | `fence_gate` | `107:3` |  |
| `minecraft:warped_fence_gate[facing=east,open=true,*]` | `fence_gate` | `107:7` |  |
| `minecraft:warped_fence_gate[*]` | `fence_gate` | `107:0` |  |
| `minecraft:warped_fungus[*]` | `stone` | `1:0` | fallback |
| `minecraft:warped_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:warped_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:warped_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:warped_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:warped_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:warped_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:warped_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:warped_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:warped_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:warped_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:warped_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:warped_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:warped_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:warped_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:warped_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:warped_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:warped_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:warped_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:warped_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:warped_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:warped_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:warped_hyphae[*]` | `stone` | `1:0` | fallback |
| `minecraft:warped_nylium[*]` | `stone` | `1:0` | fallback |
| `minecraft:warped_planks[*]` | `planks` | `5:2` |  |
| `minecraft:warped_pressure_plate[*]` | `wooden_pressure_plate` | `72:0` |  |
| `minecraft:warped_roots[*]` | `stone` | `1:0` | fallback |
| `minecraft:warped_shelf[*]` | `stone` | `1:0` | fallback |
| `minecraft:warped_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:warped_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:warped_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:warped_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:warped_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:warped_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:warped_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:warped_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:warped_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:warped_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:warped_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:warped_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:warped_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:warped_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:warped_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:warped_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:warped_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:warped_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:warped_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:warped_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:warped_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:warped_slab[type=bottom,*]` | `wooden_slab` | `126:2` |  |
| `minecraft:warped_slab[type=top,*]` | `wooden_slab` | `126:10` |  |
| `minecraft:warped_slab[type=double,*]` | `wooden_slab` | `125:2` | double slab |
| `minecraft:warped_slab[*]` | `wooden_slab` | `126:2` |  |
| `minecraft:warped_stairs[facing=east,half=bottom,*]` | `birch_stairs` | `135:0` |  |
| `minecraft:warped_stairs[facing=east,half=top,*]` | `birch_stairs` | `135:4` |  |
| `minecraft:warped_stairs[facing=west,half=bottom,*]` | `birch_stairs` | `135:1` |  |
| `minecraft:warped_stairs[facing=west,half=top,*]` | `birch_stairs` | `135:5` |  |
| `minecraft:warped_stairs[facing=south,half=bottom,*]` | `birch_stairs` | `135:2` |  |
| `minecraft:warped_stairs[facing=south,half=top,*]` | `birch_stairs` | `135:6` |  |
| `minecraft:warped_stairs[facing=north,half=bottom,*]` | `birch_stairs` | `135:3` |  |
| `minecraft:warped_stairs[facing=north,half=top,*]` | `birch_stairs` | `135:7` |  |
| `minecraft:warped_stairs[*]` | `birch_stairs` | `135:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:warped_stem[*]` | `stone` | `1:0` | fallback |
| `minecraft:warped_trapdoor[half=lower,facing=east,open=false,*]` | `wooden_door` | `64:0` |  |
| `minecraft:warped_trapdoor[half=lower,facing=east,open=true,*]` | `wooden_door` | `64:4` |  |
| `minecraft:warped_trapdoor[half=lower,facing=south,open=false,*]` | `wooden_door` | `64:1` |  |
| `minecraft:warped_trapdoor[half=lower,facing=south,open=true,*]` | `wooden_door` | `64:5` |  |
| `minecraft:warped_trapdoor[half=lower,facing=west,open=false,*]` | `wooden_door` | `64:2` |  |
| `minecraft:warped_trapdoor[half=lower,facing=west,open=true,*]` | `wooden_door` | `64:6` |  |
| `minecraft:warped_trapdoor[half=lower,facing=north,open=false,*]` | `wooden_door` | `64:3` |  |
| `minecraft:warped_trapdoor[half=lower,facing=north,open=true,*]` | `wooden_door` | `64:7` |  |
| `minecraft:warped_trapdoor[half=upper,hinge=left,*]` | `wooden_door` | `64:8` | upper half |
| `minecraft:warped_trapdoor[half=upper,hinge=right,*]` | `wooden_door` | `64:9` | upper half |
| `minecraft:warped_trapdoor[*]` | `wooden_door` | `64:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:warped_wall_hanging_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:warped_wall_hanging_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:warped_wall_hanging_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:warped_wall_hanging_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:warped_wall_hanging_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:warped_wall_hanging_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:warped_wall_hanging_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:warped_wall_hanging_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:warped_wall_hanging_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:warped_wall_hanging_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:warped_wall_hanging_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:warped_wall_hanging_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:warped_wall_hanging_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:warped_wall_hanging_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:warped_wall_hanging_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:warped_wall_hanging_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:warped_wall_hanging_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:warped_wall_hanging_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:warped_wall_hanging_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:warped_wall_hanging_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:warped_wall_hanging_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:warped_wall_sign[rotation=0,*]` | `sign` | `63:0` | standing sign |
| `minecraft:warped_wall_sign[rotation=1,*]` | `sign` | `63:1` | standing sign |
| `minecraft:warped_wall_sign[rotation=2,*]` | `sign` | `63:2` | standing sign |
| `minecraft:warped_wall_sign[rotation=3,*]` | `sign` | `63:3` | standing sign |
| `minecraft:warped_wall_sign[rotation=4,*]` | `sign` | `63:4` | standing sign |
| `minecraft:warped_wall_sign[rotation=5,*]` | `sign` | `63:5` | standing sign |
| `minecraft:warped_wall_sign[rotation=6,*]` | `sign` | `63:6` | standing sign |
| `minecraft:warped_wall_sign[rotation=7,*]` | `sign` | `63:7` | standing sign |
| `minecraft:warped_wall_sign[rotation=8,*]` | `sign` | `63:8` | standing sign |
| `minecraft:warped_wall_sign[rotation=9,*]` | `sign` | `63:9` | standing sign |
| `minecraft:warped_wall_sign[rotation=10,*]` | `sign` | `63:10` | standing sign |
| `minecraft:warped_wall_sign[rotation=11,*]` | `sign` | `63:11` | standing sign |
| `minecraft:warped_wall_sign[rotation=12,*]` | `sign` | `63:12` | standing sign |
| `minecraft:warped_wall_sign[rotation=13,*]` | `sign` | `63:13` | standing sign |
| `minecraft:warped_wall_sign[rotation=14,*]` | `sign` | `63:14` | standing sign |
| `minecraft:warped_wall_sign[rotation=15,*]` | `sign` | `63:15` | standing sign |
| `minecraft:warped_wall_sign[facing=north,*]` | `sign` | `68:2` | wall sign |
| `minecraft:warped_wall_sign[facing=south,*]` | `sign` | `68:3` | wall sign |
| `minecraft:warped_wall_sign[facing=west,*]` | `sign` | `68:4` | wall sign |
| `minecraft:warped_wall_sign[facing=east,*]` | `sign` | `68:5` | wall sign |
| `minecraft:warped_wall_sign[*]` | `sign` | `63:0` | defaults to standing sign |
| `minecraft:warped_wart_block[*]` | `stone` | `1:0` | fallback |
| `minecraft:water[*]` | `water` | `9:0` |  |
| `minecraft:water_cauldron[level=0,*]` | `cauldron` | `118:0` |  |
| `minecraft:water_cauldron[level=1,*]` | `cauldron` | `118:1` |  |
| `minecraft:water_cauldron[level=2,*]` | `cauldron` | `118:2` |  |
| `minecraft:water_cauldron[level=3,*]` | `cauldron` | `118:3` |  |
| `minecraft:water_cauldron[*]` | `cauldron` | `118:0` | lava/powder-snow cauldrons collapse to cauldron levels |
| `minecraft:waxed_chiseled_copper[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_copper_bars[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_copper_block[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_copper_bulb[lit=false,*]` | `redstone_lamp` | `123:0` |  |
| `minecraft:waxed_copper_bulb[lit=true,*]` | `redstone_lamp` | `124:0` | lit redstone lamp |
| `minecraft:waxed_copper_bulb[*]` | `redstone_lamp` | `123:0` |  |
| `minecraft:waxed_copper_chain[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_copper_chest[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_copper_door[half=lower,facing=east,open=false,*]` | `iron_door` | `71:0` |  |
| `minecraft:waxed_copper_door[half=lower,facing=east,open=true,*]` | `iron_door` | `71:4` |  |
| `minecraft:waxed_copper_door[half=lower,facing=south,open=false,*]` | `iron_door` | `71:1` |  |
| `minecraft:waxed_copper_door[half=lower,facing=south,open=true,*]` | `iron_door` | `71:5` |  |
| `minecraft:waxed_copper_door[half=lower,facing=west,open=false,*]` | `iron_door` | `71:2` |  |
| `minecraft:waxed_copper_door[half=lower,facing=west,open=true,*]` | `iron_door` | `71:6` |  |
| `minecraft:waxed_copper_door[half=lower,facing=north,open=false,*]` | `iron_door` | `71:3` |  |
| `minecraft:waxed_copper_door[half=lower,facing=north,open=true,*]` | `iron_door` | `71:7` |  |
| `minecraft:waxed_copper_door[half=upper,hinge=left,*]` | `iron_door` | `71:8` | upper half |
| `minecraft:waxed_copper_door[half=upper,hinge=right,*]` | `iron_door` | `71:9` | upper half |
| `minecraft:waxed_copper_door[*]` | `iron_door` | `71:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:waxed_copper_golem_statue[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_copper_grate[*]` | `iron_bars` | `101:0` |  |
| `minecraft:waxed_copper_lantern[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:waxed_copper_trapdoor[half=lower,facing=east,open=false,*]` | `iron_door` | `71:0` |  |
| `minecraft:waxed_copper_trapdoor[half=lower,facing=east,open=true,*]` | `iron_door` | `71:4` |  |
| `minecraft:waxed_copper_trapdoor[half=lower,facing=south,open=false,*]` | `iron_door` | `71:1` |  |
| `minecraft:waxed_copper_trapdoor[half=lower,facing=south,open=true,*]` | `iron_door` | `71:5` |  |
| `minecraft:waxed_copper_trapdoor[half=lower,facing=west,open=false,*]` | `iron_door` | `71:2` |  |
| `minecraft:waxed_copper_trapdoor[half=lower,facing=west,open=true,*]` | `iron_door` | `71:6` |  |
| `minecraft:waxed_copper_trapdoor[half=lower,facing=north,open=false,*]` | `iron_door` | `71:3` |  |
| `minecraft:waxed_copper_trapdoor[half=lower,facing=north,open=true,*]` | `iron_door` | `71:7` |  |
| `minecraft:waxed_copper_trapdoor[half=upper,hinge=left,*]` | `iron_door` | `71:8` | upper half |
| `minecraft:waxed_copper_trapdoor[half=upper,hinge=right,*]` | `iron_door` | `71:9` | upper half |
| `minecraft:waxed_copper_trapdoor[*]` | `iron_door` | `71:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:waxed_cut_copper[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_cut_copper_slab[type=bottom,*]` | `stone_slab` | `44:0` |  |
| `minecraft:waxed_cut_copper_slab[type=top,*]` | `stone_slab` | `44:8` |  |
| `minecraft:waxed_cut_copper_slab[type=double,*]` | `stone_slab` | `43:0` | double slab |
| `minecraft:waxed_cut_copper_slab[*]` | `stone_slab` | `44:0` |  |
| `minecraft:waxed_cut_copper_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:waxed_cut_copper_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:waxed_cut_copper_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:waxed_cut_copper_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:waxed_cut_copper_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:waxed_cut_copper_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:waxed_cut_copper_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:waxed_cut_copper_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:waxed_cut_copper_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:waxed_exposed_chiseled_copper[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_exposed_copper[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_exposed_copper_bars[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_exposed_copper_bulb[lit=false,*]` | `redstone_lamp` | `123:0` |  |
| `minecraft:waxed_exposed_copper_bulb[lit=true,*]` | `redstone_lamp` | `124:0` | lit redstone lamp |
| `minecraft:waxed_exposed_copper_bulb[*]` | `redstone_lamp` | `123:0` |  |
| `minecraft:waxed_exposed_copper_chain[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_exposed_copper_chest[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_exposed_copper_door[half=lower,facing=east,open=false,*]` | `iron_door` | `71:0` |  |
| `minecraft:waxed_exposed_copper_door[half=lower,facing=east,open=true,*]` | `iron_door` | `71:4` |  |
| `minecraft:waxed_exposed_copper_door[half=lower,facing=south,open=false,*]` | `iron_door` | `71:1` |  |
| `minecraft:waxed_exposed_copper_door[half=lower,facing=south,open=true,*]` | `iron_door` | `71:5` |  |
| `minecraft:waxed_exposed_copper_door[half=lower,facing=west,open=false,*]` | `iron_door` | `71:2` |  |
| `minecraft:waxed_exposed_copper_door[half=lower,facing=west,open=true,*]` | `iron_door` | `71:6` |  |
| `minecraft:waxed_exposed_copper_door[half=lower,facing=north,open=false,*]` | `iron_door` | `71:3` |  |
| `minecraft:waxed_exposed_copper_door[half=lower,facing=north,open=true,*]` | `iron_door` | `71:7` |  |
| `minecraft:waxed_exposed_copper_door[half=upper,hinge=left,*]` | `iron_door` | `71:8` | upper half |
| `minecraft:waxed_exposed_copper_door[half=upper,hinge=right,*]` | `iron_door` | `71:9` | upper half |
| `minecraft:waxed_exposed_copper_door[*]` | `iron_door` | `71:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:waxed_exposed_copper_golem_statue[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_exposed_copper_grate[*]` | `iron_bars` | `101:0` |  |
| `minecraft:waxed_exposed_copper_lantern[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:waxed_exposed_copper_trapdoor[half=lower,facing=east,open=false,*]` | `iron_door` | `71:0` |  |
| `minecraft:waxed_exposed_copper_trapdoor[half=lower,facing=east,open=true,*]` | `iron_door` | `71:4` |  |
| `minecraft:waxed_exposed_copper_trapdoor[half=lower,facing=south,open=false,*]` | `iron_door` | `71:1` |  |
| `minecraft:waxed_exposed_copper_trapdoor[half=lower,facing=south,open=true,*]` | `iron_door` | `71:5` |  |
| `minecraft:waxed_exposed_copper_trapdoor[half=lower,facing=west,open=false,*]` | `iron_door` | `71:2` |  |
| `minecraft:waxed_exposed_copper_trapdoor[half=lower,facing=west,open=true,*]` | `iron_door` | `71:6` |  |
| `minecraft:waxed_exposed_copper_trapdoor[half=lower,facing=north,open=false,*]` | `iron_door` | `71:3` |  |
| `minecraft:waxed_exposed_copper_trapdoor[half=lower,facing=north,open=true,*]` | `iron_door` | `71:7` |  |
| `minecraft:waxed_exposed_copper_trapdoor[half=upper,hinge=left,*]` | `iron_door` | `71:8` | upper half |
| `minecraft:waxed_exposed_copper_trapdoor[half=upper,hinge=right,*]` | `iron_door` | `71:9` | upper half |
| `minecraft:waxed_exposed_copper_trapdoor[*]` | `iron_door` | `71:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:waxed_exposed_cut_copper[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_exposed_cut_copper_slab[type=bottom,*]` | `stone_slab` | `44:0` |  |
| `minecraft:waxed_exposed_cut_copper_slab[type=top,*]` | `stone_slab` | `44:8` |  |
| `minecraft:waxed_exposed_cut_copper_slab[type=double,*]` | `stone_slab` | `43:0` | double slab |
| `minecraft:waxed_exposed_cut_copper_slab[*]` | `stone_slab` | `44:0` |  |
| `minecraft:waxed_exposed_cut_copper_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:waxed_exposed_cut_copper_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:waxed_exposed_cut_copper_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:waxed_exposed_cut_copper_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:waxed_exposed_cut_copper_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:waxed_exposed_cut_copper_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:waxed_exposed_cut_copper_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:waxed_exposed_cut_copper_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:waxed_exposed_cut_copper_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:waxed_exposed_lightning_rod[*]` | `stone` | `1:0` | fallback |
| `minecraft:waxed_lightning_rod[*]` | `stone` | `1:0` | fallback |
| `minecraft:waxed_oxidized_chiseled_copper[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_oxidized_copper[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_oxidized_copper_bars[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_oxidized_copper_bulb[lit=false,*]` | `redstone_lamp` | `123:0` |  |
| `minecraft:waxed_oxidized_copper_bulb[lit=true,*]` | `redstone_lamp` | `124:0` | lit redstone lamp |
| `minecraft:waxed_oxidized_copper_bulb[*]` | `redstone_lamp` | `123:0` |  |
| `minecraft:waxed_oxidized_copper_chain[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_oxidized_copper_chest[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_oxidized_copper_door[half=lower,facing=east,open=false,*]` | `iron_door` | `71:0` |  |
| `minecraft:waxed_oxidized_copper_door[half=lower,facing=east,open=true,*]` | `iron_door` | `71:4` |  |
| `minecraft:waxed_oxidized_copper_door[half=lower,facing=south,open=false,*]` | `iron_door` | `71:1` |  |
| `minecraft:waxed_oxidized_copper_door[half=lower,facing=south,open=true,*]` | `iron_door` | `71:5` |  |
| `minecraft:waxed_oxidized_copper_door[half=lower,facing=west,open=false,*]` | `iron_door` | `71:2` |  |
| `minecraft:waxed_oxidized_copper_door[half=lower,facing=west,open=true,*]` | `iron_door` | `71:6` |  |
| `minecraft:waxed_oxidized_copper_door[half=lower,facing=north,open=false,*]` | `iron_door` | `71:3` |  |
| `minecraft:waxed_oxidized_copper_door[half=lower,facing=north,open=true,*]` | `iron_door` | `71:7` |  |
| `minecraft:waxed_oxidized_copper_door[half=upper,hinge=left,*]` | `iron_door` | `71:8` | upper half |
| `minecraft:waxed_oxidized_copper_door[half=upper,hinge=right,*]` | `iron_door` | `71:9` | upper half |
| `minecraft:waxed_oxidized_copper_door[*]` | `iron_door` | `71:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:waxed_oxidized_copper_golem_statue[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_oxidized_copper_grate[*]` | `iron_bars` | `101:0` |  |
| `minecraft:waxed_oxidized_copper_lantern[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:waxed_oxidized_copper_trapdoor[half=lower,facing=east,open=false,*]` | `iron_door` | `71:0` |  |
| `minecraft:waxed_oxidized_copper_trapdoor[half=lower,facing=east,open=true,*]` | `iron_door` | `71:4` |  |
| `minecraft:waxed_oxidized_copper_trapdoor[half=lower,facing=south,open=false,*]` | `iron_door` | `71:1` |  |
| `minecraft:waxed_oxidized_copper_trapdoor[half=lower,facing=south,open=true,*]` | `iron_door` | `71:5` |  |
| `minecraft:waxed_oxidized_copper_trapdoor[half=lower,facing=west,open=false,*]` | `iron_door` | `71:2` |  |
| `minecraft:waxed_oxidized_copper_trapdoor[half=lower,facing=west,open=true,*]` | `iron_door` | `71:6` |  |
| `minecraft:waxed_oxidized_copper_trapdoor[half=lower,facing=north,open=false,*]` | `iron_door` | `71:3` |  |
| `minecraft:waxed_oxidized_copper_trapdoor[half=lower,facing=north,open=true,*]` | `iron_door` | `71:7` |  |
| `minecraft:waxed_oxidized_copper_trapdoor[half=upper,hinge=left,*]` | `iron_door` | `71:8` | upper half |
| `minecraft:waxed_oxidized_copper_trapdoor[half=upper,hinge=right,*]` | `iron_door` | `71:9` | upper half |
| `minecraft:waxed_oxidized_copper_trapdoor[*]` | `iron_door` | `71:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:waxed_oxidized_cut_copper[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_oxidized_cut_copper_slab[type=bottom,*]` | `stone_slab` | `44:0` |  |
| `minecraft:waxed_oxidized_cut_copper_slab[type=top,*]` | `stone_slab` | `44:8` |  |
| `minecraft:waxed_oxidized_cut_copper_slab[type=double,*]` | `stone_slab` | `43:0` | double slab |
| `minecraft:waxed_oxidized_cut_copper_slab[*]` | `stone_slab` | `44:0` |  |
| `minecraft:waxed_oxidized_cut_copper_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:waxed_oxidized_cut_copper_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:waxed_oxidized_cut_copper_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:waxed_oxidized_cut_copper_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:waxed_oxidized_cut_copper_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:waxed_oxidized_cut_copper_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:waxed_oxidized_cut_copper_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:waxed_oxidized_cut_copper_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:waxed_oxidized_cut_copper_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:waxed_oxidized_lightning_rod[*]` | `stone` | `1:0` | fallback |
| `minecraft:waxed_weathered_chiseled_copper[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_weathered_copper[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_weathered_copper_bars[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_weathered_copper_bulb[lit=false,*]` | `redstone_lamp` | `123:0` |  |
| `minecraft:waxed_weathered_copper_bulb[lit=true,*]` | `redstone_lamp` | `124:0` | lit redstone lamp |
| `minecraft:waxed_weathered_copper_bulb[*]` | `redstone_lamp` | `123:0` |  |
| `minecraft:waxed_weathered_copper_chain[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_weathered_copper_chest[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_weathered_copper_door[half=lower,facing=east,open=false,*]` | `iron_door` | `71:0` |  |
| `minecraft:waxed_weathered_copper_door[half=lower,facing=east,open=true,*]` | `iron_door` | `71:4` |  |
| `minecraft:waxed_weathered_copper_door[half=lower,facing=south,open=false,*]` | `iron_door` | `71:1` |  |
| `minecraft:waxed_weathered_copper_door[half=lower,facing=south,open=true,*]` | `iron_door` | `71:5` |  |
| `minecraft:waxed_weathered_copper_door[half=lower,facing=west,open=false,*]` | `iron_door` | `71:2` |  |
| `minecraft:waxed_weathered_copper_door[half=lower,facing=west,open=true,*]` | `iron_door` | `71:6` |  |
| `minecraft:waxed_weathered_copper_door[half=lower,facing=north,open=false,*]` | `iron_door` | `71:3` |  |
| `minecraft:waxed_weathered_copper_door[half=lower,facing=north,open=true,*]` | `iron_door` | `71:7` |  |
| `minecraft:waxed_weathered_copper_door[half=upper,hinge=left,*]` | `iron_door` | `71:8` | upper half |
| `minecraft:waxed_weathered_copper_door[half=upper,hinge=right,*]` | `iron_door` | `71:9` | upper half |
| `minecraft:waxed_weathered_copper_door[*]` | `iron_door` | `71:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:waxed_weathered_copper_golem_statue[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_weathered_copper_grate[*]` | `iron_bars` | `101:0` |  |
| `minecraft:waxed_weathered_copper_lantern[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:waxed_weathered_copper_trapdoor[half=lower,facing=east,open=false,*]` | `iron_door` | `71:0` |  |
| `minecraft:waxed_weathered_copper_trapdoor[half=lower,facing=east,open=true,*]` | `iron_door` | `71:4` |  |
| `minecraft:waxed_weathered_copper_trapdoor[half=lower,facing=south,open=false,*]` | `iron_door` | `71:1` |  |
| `minecraft:waxed_weathered_copper_trapdoor[half=lower,facing=south,open=true,*]` | `iron_door` | `71:5` |  |
| `minecraft:waxed_weathered_copper_trapdoor[half=lower,facing=west,open=false,*]` | `iron_door` | `71:2` |  |
| `minecraft:waxed_weathered_copper_trapdoor[half=lower,facing=west,open=true,*]` | `iron_door` | `71:6` |  |
| `minecraft:waxed_weathered_copper_trapdoor[half=lower,facing=north,open=false,*]` | `iron_door` | `71:3` |  |
| `minecraft:waxed_weathered_copper_trapdoor[half=lower,facing=north,open=true,*]` | `iron_door` | `71:7` |  |
| `minecraft:waxed_weathered_copper_trapdoor[half=upper,hinge=left,*]` | `iron_door` | `71:8` | upper half |
| `minecraft:waxed_weathered_copper_trapdoor[half=upper,hinge=right,*]` | `iron_door` | `71:9` | upper half |
| `minecraft:waxed_weathered_copper_trapdoor[*]` | `iron_door` | `71:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:waxed_weathered_cut_copper[*]` | `iron_block` | `42:0` |  |
| `minecraft:waxed_weathered_cut_copper_slab[type=bottom,*]` | `stone_slab` | `44:0` |  |
| `minecraft:waxed_weathered_cut_copper_slab[type=top,*]` | `stone_slab` | `44:8` |  |
| `minecraft:waxed_weathered_cut_copper_slab[type=double,*]` | `stone_slab` | `43:0` | double slab |
| `minecraft:waxed_weathered_cut_copper_slab[*]` | `stone_slab` | `44:0` |  |
| `minecraft:waxed_weathered_cut_copper_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:waxed_weathered_cut_copper_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:waxed_weathered_cut_copper_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:waxed_weathered_cut_copper_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:waxed_weathered_cut_copper_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:waxed_weathered_cut_copper_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:waxed_weathered_cut_copper_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:waxed_weathered_cut_copper_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:waxed_weathered_cut_copper_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:waxed_weathered_lightning_rod[*]` | `stone` | `1:0` | fallback |
| `minecraft:weathered_chiseled_copper[*]` | `iron_block` | `42:0` |  |
| `minecraft:weathered_copper[*]` | `iron_block` | `42:0` |  |
| `minecraft:weathered_copper_bars[*]` | `iron_block` | `42:0` |  |
| `minecraft:weathered_copper_bulb[lit=false,*]` | `redstone_lamp` | `123:0` |  |
| `minecraft:weathered_copper_bulb[lit=true,*]` | `redstone_lamp` | `124:0` | lit redstone lamp |
| `minecraft:weathered_copper_bulb[*]` | `redstone_lamp` | `123:0` |  |
| `minecraft:weathered_copper_chain[*]` | `iron_block` | `42:0` |  |
| `minecraft:weathered_copper_chest[*]` | `iron_block` | `42:0` |  |
| `minecraft:weathered_copper_door[half=lower,facing=east,open=false,*]` | `iron_door` | `71:0` |  |
| `minecraft:weathered_copper_door[half=lower,facing=east,open=true,*]` | `iron_door` | `71:4` |  |
| `minecraft:weathered_copper_door[half=lower,facing=south,open=false,*]` | `iron_door` | `71:1` |  |
| `minecraft:weathered_copper_door[half=lower,facing=south,open=true,*]` | `iron_door` | `71:5` |  |
| `minecraft:weathered_copper_door[half=lower,facing=west,open=false,*]` | `iron_door` | `71:2` |  |
| `minecraft:weathered_copper_door[half=lower,facing=west,open=true,*]` | `iron_door` | `71:6` |  |
| `minecraft:weathered_copper_door[half=lower,facing=north,open=false,*]` | `iron_door` | `71:3` |  |
| `minecraft:weathered_copper_door[half=lower,facing=north,open=true,*]` | `iron_door` | `71:7` |  |
| `minecraft:weathered_copper_door[half=upper,hinge=left,*]` | `iron_door` | `71:8` | upper half |
| `minecraft:weathered_copper_door[half=upper,hinge=right,*]` | `iron_door` | `71:9` | upper half |
| `minecraft:weathered_copper_door[*]` | `iron_door` | `71:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:weathered_copper_golem_statue[*]` | `iron_block` | `42:0` |  |
| `minecraft:weathered_copper_grate[*]` | `iron_bars` | `101:0` |  |
| `minecraft:weathered_copper_lantern[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:weathered_copper_trapdoor[half=lower,facing=east,open=false,*]` | `iron_door` | `71:0` |  |
| `minecraft:weathered_copper_trapdoor[half=lower,facing=east,open=true,*]` | `iron_door` | `71:4` |  |
| `minecraft:weathered_copper_trapdoor[half=lower,facing=south,open=false,*]` | `iron_door` | `71:1` |  |
| `minecraft:weathered_copper_trapdoor[half=lower,facing=south,open=true,*]` | `iron_door` | `71:5` |  |
| `minecraft:weathered_copper_trapdoor[half=lower,facing=west,open=false,*]` | `iron_door` | `71:2` |  |
| `minecraft:weathered_copper_trapdoor[half=lower,facing=west,open=true,*]` | `iron_door` | `71:6` |  |
| `minecraft:weathered_copper_trapdoor[half=lower,facing=north,open=false,*]` | `iron_door` | `71:3` |  |
| `minecraft:weathered_copper_trapdoor[half=lower,facing=north,open=true,*]` | `iron_door` | `71:7` |  |
| `minecraft:weathered_copper_trapdoor[half=upper,hinge=left,*]` | `iron_door` | `71:8` | upper half |
| `minecraft:weathered_copper_trapdoor[half=upper,hinge=right,*]` | `iron_door` | `71:9` | upper half |
| `minecraft:weathered_copper_trapdoor[*]` | `iron_door` | `71:0` | defaults to lower-east-closed; powered state is ignored |
| `minecraft:weathered_cut_copper[*]` | `iron_block` | `42:0` |  |
| `minecraft:weathered_cut_copper_slab[type=bottom,*]` | `stone_slab` | `44:0` |  |
| `minecraft:weathered_cut_copper_slab[type=top,*]` | `stone_slab` | `44:8` |  |
| `minecraft:weathered_cut_copper_slab[type=double,*]` | `stone_slab` | `43:0` | double slab |
| `minecraft:weathered_cut_copper_slab[*]` | `stone_slab` | `44:0` |  |
| `minecraft:weathered_cut_copper_stairs[facing=east,half=bottom,*]` | `stone_brick_stairs` | `109:0` |  |
| `minecraft:weathered_cut_copper_stairs[facing=east,half=top,*]` | `stone_brick_stairs` | `109:4` |  |
| `minecraft:weathered_cut_copper_stairs[facing=west,half=bottom,*]` | `stone_brick_stairs` | `109:1` |  |
| `minecraft:weathered_cut_copper_stairs[facing=west,half=top,*]` | `stone_brick_stairs` | `109:5` |  |
| `minecraft:weathered_cut_copper_stairs[facing=south,half=bottom,*]` | `stone_brick_stairs` | `109:2` |  |
| `minecraft:weathered_cut_copper_stairs[facing=south,half=top,*]` | `stone_brick_stairs` | `109:6` |  |
| `minecraft:weathered_cut_copper_stairs[facing=north,half=bottom,*]` | `stone_brick_stairs` | `109:3` |  |
| `minecraft:weathered_cut_copper_stairs[facing=north,half=top,*]` | `stone_brick_stairs` | `109:7` |  |
| `minecraft:weathered_cut_copper_stairs[*]` | `stone_brick_stairs` | `109:0` | ignores modern stair shape/waterlogging and defaults to east-bottom |
| `minecraft:weathered_lightning_rod[*]` | `stone` | `1:0` | fallback |
| `minecraft:weeping_vines[*]` | `stone` | `1:0` | fallback |
| `minecraft:weeping_vines_plant[*]` | `stone` | `1:0` | fallback |
| `minecraft:wet_sponge[*]` | `wool` | `35:11` |  |
| `minecraft:wheat[age=0,*]` | `wheat` | `59:0` |  |
| `minecraft:wheat[age=1,*]` | `wheat` | `59:1` |  |
| `minecraft:wheat[age=2,*]` | `wheat` | `59:2` |  |
| `minecraft:wheat[age=3,*]` | `wheat` | `59:3` |  |
| `minecraft:wheat[age=4,*]` | `wheat` | `59:4` |  |
| `minecraft:wheat[age=5,*]` | `wheat` | `59:5` |  |
| `minecraft:wheat[age=6,*]` | `wheat` | `59:6` |  |
| `minecraft:wheat[age=7,*]` | `wheat` | `59:7` |  |
| `minecraft:wheat[*]` | `wheat` | `59:0` |  |
| `minecraft:white_banner[*]` | `wool` | `35:0` | banner collapsed to wool |
| `minecraft:white_bed[part=foot,facing=south,occupied=false,*]` | `bed` | `26:0` | bed color ignored |
| `minecraft:white_bed[part=head,facing=south,occupied=false,*]` | `bed` | `26:8` | bed color ignored |
| `minecraft:white_bed[part=foot,facing=south,occupied=true,*]` | `bed` | `26:4` | occupied bit; color ignored |
| `minecraft:white_bed[part=head,facing=south,occupied=true,*]` | `bed` | `26:12` | occupied+head bits; color ignored |
| `minecraft:white_bed[part=foot,facing=west,occupied=false,*]` | `bed` | `26:1` | bed color ignored |
| `minecraft:white_bed[part=head,facing=west,occupied=false,*]` | `bed` | `26:9` | bed color ignored |
| `minecraft:white_bed[part=foot,facing=west,occupied=true,*]` | `bed` | `26:5` | occupied bit; color ignored |
| `minecraft:white_bed[part=head,facing=west,occupied=true,*]` | `bed` | `26:13` | occupied+head bits; color ignored |
| `minecraft:white_bed[part=foot,facing=north,occupied=false,*]` | `bed` | `26:2` | bed color ignored |
| `minecraft:white_bed[part=head,facing=north,occupied=false,*]` | `bed` | `26:10` | bed color ignored |
| `minecraft:white_bed[part=foot,facing=north,occupied=true,*]` | `bed` | `26:6` | occupied bit; color ignored |
| `minecraft:white_bed[part=head,facing=north,occupied=true,*]` | `bed` | `26:14` | occupied+head bits; color ignored |
| `minecraft:white_bed[part=foot,facing=east,occupied=false,*]` | `bed` | `26:3` | bed color ignored |
| `minecraft:white_bed[part=head,facing=east,occupied=false,*]` | `bed` | `26:11` | bed color ignored |
| `minecraft:white_bed[part=foot,facing=east,occupied=true,*]` | `bed` | `26:7` | occupied bit; color ignored |
| `minecraft:white_bed[part=head,facing=east,occupied=true,*]` | `bed` | `26:15` | occupied+head bits; color ignored |
| `minecraft:white_bed[*]` | `bed` | `26:0` | legacy bed ignores color |
| `minecraft:white_candle[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:white_candle_cake[bites=0,*]` | `cake` | `92:0` |  |
| `minecraft:white_candle_cake[bites=1,*]` | `cake` | `92:1` |  |
| `minecraft:white_candle_cake[bites=2,*]` | `cake` | `92:2` |  |
| `minecraft:white_candle_cake[bites=3,*]` | `cake` | `92:3` |  |
| `minecraft:white_candle_cake[bites=4,*]` | `cake` | `92:4` |  |
| `minecraft:white_candle_cake[bites=5,*]` | `cake` | `92:5` |  |
| `minecraft:white_candle_cake[bites=6,*]` | `cake` | `92:6` |  |
| `minecraft:white_candle_cake[*]` | `cake` | `92:0` |  |
| `minecraft:white_carpet[*]` | `carpet` | `171:0` |  |
| `minecraft:white_concrete[*]` | `stained_hardened_clay` | `159:0` |  |
| `minecraft:white_concrete_powder[*]` | `stained_hardened_clay` | `159:0` |  |
| `minecraft:white_glazed_terracotta[*]` | `stained_hardened_clay` | `159:0` |  |
| `minecraft:white_shulker_box[*]` | `wool` | `35:0` | shulker box collapsed to wool |
| `minecraft:white_stained_glass[*]` | `stained_glass` | `95:0` |  |
| `minecraft:white_stained_glass_pane[*]` | `stained_glass_pane` | `160:0` |  |
| `minecraft:white_terracotta[*]` | `stained_hardened_clay` | `159:0` |  |
| `minecraft:white_tulip[*]` | `stone` | `1:0` | fallback |
| `minecraft:white_wall_banner[*]` | `wool` | `35:0` | banner collapsed to wool |
| `minecraft:white_wool[*]` | `wool` | `35:0` |  |
| `minecraft:wildflowers[*]` | `red_flower` | `38:0` |  |
| `minecraft:wither_rose[*]` | `red_flower` | `38:0` |  |
| `minecraft:wither_skeleton_skull[rotation=0,*]` | `mob_head` | `144:0` | standing head |
| `minecraft:wither_skeleton_skull[rotation=1,*]` | `mob_head` | `144:1` | standing head |
| `minecraft:wither_skeleton_skull[rotation=2,*]` | `mob_head` | `144:2` | standing head |
| `minecraft:wither_skeleton_skull[rotation=3,*]` | `mob_head` | `144:3` | standing head |
| `minecraft:wither_skeleton_skull[rotation=4,*]` | `mob_head` | `144:4` | standing head |
| `minecraft:wither_skeleton_skull[rotation=5,*]` | `mob_head` | `144:5` | standing head |
| `minecraft:wither_skeleton_skull[rotation=6,*]` | `mob_head` | `144:6` | standing head |
| `minecraft:wither_skeleton_skull[rotation=7,*]` | `mob_head` | `144:7` | standing head |
| `minecraft:wither_skeleton_skull[rotation=8,*]` | `mob_head` | `144:8` | standing head |
| `minecraft:wither_skeleton_skull[rotation=9,*]` | `mob_head` | `144:9` | standing head |
| `minecraft:wither_skeleton_skull[rotation=10,*]` | `mob_head` | `144:10` | standing head |
| `minecraft:wither_skeleton_skull[rotation=11,*]` | `mob_head` | `144:11` | standing head |
| `minecraft:wither_skeleton_skull[rotation=12,*]` | `mob_head` | `144:12` | standing head |
| `minecraft:wither_skeleton_skull[rotation=13,*]` | `mob_head` | `144:13` | standing head |
| `minecraft:wither_skeleton_skull[rotation=14,*]` | `mob_head` | `144:14` | standing head |
| `minecraft:wither_skeleton_skull[rotation=15,*]` | `mob_head` | `144:15` | standing head |
| `minecraft:wither_skeleton_skull[facing=north,*]` | `mob_head` | `144:2` | wall head |
| `minecraft:wither_skeleton_skull[facing=south,*]` | `mob_head` | `144:3` | wall head |
| `minecraft:wither_skeleton_skull[facing=west,*]` | `mob_head` | `144:4` | wall head |
| `minecraft:wither_skeleton_skull[facing=east,*]` | `mob_head` | `144:5` | wall head |
| `minecraft:wither_skeleton_skull[*]` | `mob_head` | `144:0` | head type collapsed |
| `minecraft:wither_skeleton_wall_skull[rotation=0,*]` | `mob_head` | `144:0` | standing head |
| `minecraft:wither_skeleton_wall_skull[rotation=1,*]` | `mob_head` | `144:1` | standing head |
| `minecraft:wither_skeleton_wall_skull[rotation=2,*]` | `mob_head` | `144:2` | standing head |
| `minecraft:wither_skeleton_wall_skull[rotation=3,*]` | `mob_head` | `144:3` | standing head |
| `minecraft:wither_skeleton_wall_skull[rotation=4,*]` | `mob_head` | `144:4` | standing head |
| `minecraft:wither_skeleton_wall_skull[rotation=5,*]` | `mob_head` | `144:5` | standing head |
| `minecraft:wither_skeleton_wall_skull[rotation=6,*]` | `mob_head` | `144:6` | standing head |
| `minecraft:wither_skeleton_wall_skull[rotation=7,*]` | `mob_head` | `144:7` | standing head |
| `minecraft:wither_skeleton_wall_skull[rotation=8,*]` | `mob_head` | `144:8` | standing head |
| `minecraft:wither_skeleton_wall_skull[rotation=9,*]` | `mob_head` | `144:9` | standing head |
| `minecraft:wither_skeleton_wall_skull[rotation=10,*]` | `mob_head` | `144:10` | standing head |
| `minecraft:wither_skeleton_wall_skull[rotation=11,*]` | `mob_head` | `144:11` | standing head |
| `minecraft:wither_skeleton_wall_skull[rotation=12,*]` | `mob_head` | `144:12` | standing head |
| `minecraft:wither_skeleton_wall_skull[rotation=13,*]` | `mob_head` | `144:13` | standing head |
| `minecraft:wither_skeleton_wall_skull[rotation=14,*]` | `mob_head` | `144:14` | standing head |
| `minecraft:wither_skeleton_wall_skull[rotation=15,*]` | `mob_head` | `144:15` | standing head |
| `minecraft:wither_skeleton_wall_skull[facing=north,*]` | `mob_head` | `144:2` | wall head |
| `minecraft:wither_skeleton_wall_skull[facing=south,*]` | `mob_head` | `144:3` | wall head |
| `minecraft:wither_skeleton_wall_skull[facing=west,*]` | `mob_head` | `144:4` | wall head |
| `minecraft:wither_skeleton_wall_skull[facing=east,*]` | `mob_head` | `144:5` | wall head |
| `minecraft:wither_skeleton_wall_skull[*]` | `mob_head` | `144:0` | head type collapsed |
| `minecraft:yellow_banner[*]` | `wool` | `35:4` | banner collapsed to wool |
| `minecraft:yellow_bed[part=foot,facing=south,occupied=false,*]` | `bed` | `26:0` | bed color ignored |
| `minecraft:yellow_bed[part=head,facing=south,occupied=false,*]` | `bed` | `26:8` | bed color ignored |
| `minecraft:yellow_bed[part=foot,facing=south,occupied=true,*]` | `bed` | `26:4` | occupied bit; color ignored |
| `minecraft:yellow_bed[part=head,facing=south,occupied=true,*]` | `bed` | `26:12` | occupied+head bits; color ignored |
| `minecraft:yellow_bed[part=foot,facing=west,occupied=false,*]` | `bed` | `26:1` | bed color ignored |
| `minecraft:yellow_bed[part=head,facing=west,occupied=false,*]` | `bed` | `26:9` | bed color ignored |
| `minecraft:yellow_bed[part=foot,facing=west,occupied=true,*]` | `bed` | `26:5` | occupied bit; color ignored |
| `minecraft:yellow_bed[part=head,facing=west,occupied=true,*]` | `bed` | `26:13` | occupied+head bits; color ignored |
| `minecraft:yellow_bed[part=foot,facing=north,occupied=false,*]` | `bed` | `26:2` | bed color ignored |
| `minecraft:yellow_bed[part=head,facing=north,occupied=false,*]` | `bed` | `26:10` | bed color ignored |
| `minecraft:yellow_bed[part=foot,facing=north,occupied=true,*]` | `bed` | `26:6` | occupied bit; color ignored |
| `minecraft:yellow_bed[part=head,facing=north,occupied=true,*]` | `bed` | `26:14` | occupied+head bits; color ignored |
| `minecraft:yellow_bed[part=foot,facing=east,occupied=false,*]` | `bed` | `26:3` | bed color ignored |
| `minecraft:yellow_bed[part=head,facing=east,occupied=false,*]` | `bed` | `26:11` | bed color ignored |
| `minecraft:yellow_bed[part=foot,facing=east,occupied=true,*]` | `bed` | `26:7` | occupied bit; color ignored |
| `minecraft:yellow_bed[part=head,facing=east,occupied=true,*]` | `bed` | `26:15` | occupied+head bits; color ignored |
| `minecraft:yellow_bed[*]` | `bed` | `26:0` | legacy bed ignores color |
| `minecraft:yellow_candle[*]` | `torch` | `50:0` | lantern/candle collapsed to torch |
| `minecraft:yellow_candle_cake[bites=0,*]` | `cake` | `92:0` |  |
| `minecraft:yellow_candle_cake[bites=1,*]` | `cake` | `92:1` |  |
| `minecraft:yellow_candle_cake[bites=2,*]` | `cake` | `92:2` |  |
| `minecraft:yellow_candle_cake[bites=3,*]` | `cake` | `92:3` |  |
| `minecraft:yellow_candle_cake[bites=4,*]` | `cake` | `92:4` |  |
| `minecraft:yellow_candle_cake[bites=5,*]` | `cake` | `92:5` |  |
| `minecraft:yellow_candle_cake[bites=6,*]` | `cake` | `92:6` |  |
| `minecraft:yellow_candle_cake[*]` | `cake` | `92:0` |  |
| `minecraft:yellow_carpet[*]` | `carpet` | `171:4` |  |
| `minecraft:yellow_concrete[*]` | `stained_hardened_clay` | `159:4` |  |
| `minecraft:yellow_concrete_powder[*]` | `stained_hardened_clay` | `159:4` |  |
| `minecraft:yellow_glazed_terracotta[*]` | `stained_hardened_clay` | `159:4` |  |
| `minecraft:yellow_shulker_box[*]` | `wool` | `35:4` | shulker box collapsed to wool |
| `minecraft:yellow_stained_glass[*]` | `stained_glass` | `95:4` |  |
| `minecraft:yellow_stained_glass_pane[*]` | `stained_glass_pane` | `160:4` |  |
| `minecraft:yellow_terracotta[*]` | `stained_hardened_clay` | `159:4` |  |
| `minecraft:yellow_wall_banner[*]` | `wool` | `35:4` | banner collapsed to wool |
| `minecraft:yellow_wool[*]` | `wool` | `35:4` |  |
| `minecraft:zombie_head[rotation=0,*]` | `mob_head` | `144:0` | standing head |
| `minecraft:zombie_head[rotation=1,*]` | `mob_head` | `144:1` | standing head |
| `minecraft:zombie_head[rotation=2,*]` | `mob_head` | `144:2` | standing head |
| `minecraft:zombie_head[rotation=3,*]` | `mob_head` | `144:3` | standing head |
| `minecraft:zombie_head[rotation=4,*]` | `mob_head` | `144:4` | standing head |
| `minecraft:zombie_head[rotation=5,*]` | `mob_head` | `144:5` | standing head |
| `minecraft:zombie_head[rotation=6,*]` | `mob_head` | `144:6` | standing head |
| `minecraft:zombie_head[rotation=7,*]` | `mob_head` | `144:7` | standing head |
| `minecraft:zombie_head[rotation=8,*]` | `mob_head` | `144:8` | standing head |
| `minecraft:zombie_head[rotation=9,*]` | `mob_head` | `144:9` | standing head |
| `minecraft:zombie_head[rotation=10,*]` | `mob_head` | `144:10` | standing head |
| `minecraft:zombie_head[rotation=11,*]` | `mob_head` | `144:11` | standing head |
| `minecraft:zombie_head[rotation=12,*]` | `mob_head` | `144:12` | standing head |
| `minecraft:zombie_head[rotation=13,*]` | `mob_head` | `144:13` | standing head |
| `minecraft:zombie_head[rotation=14,*]` | `mob_head` | `144:14` | standing head |
| `minecraft:zombie_head[rotation=15,*]` | `mob_head` | `144:15` | standing head |
| `minecraft:zombie_head[facing=north,*]` | `mob_head` | `144:2` | wall head |
| `minecraft:zombie_head[facing=south,*]` | `mob_head` | `144:3` | wall head |
| `minecraft:zombie_head[facing=west,*]` | `mob_head` | `144:4` | wall head |
| `minecraft:zombie_head[facing=east,*]` | `mob_head` | `144:5` | wall head |
| `minecraft:zombie_head[*]` | `mob_head` | `144:0` | head type collapsed |
| `minecraft:zombie_wall_head[rotation=0,*]` | `mob_head` | `144:0` | standing head |
| `minecraft:zombie_wall_head[rotation=1,*]` | `mob_head` | `144:1` | standing head |
| `minecraft:zombie_wall_head[rotation=2,*]` | `mob_head` | `144:2` | standing head |
| `minecraft:zombie_wall_head[rotation=3,*]` | `mob_head` | `144:3` | standing head |
| `minecraft:zombie_wall_head[rotation=4,*]` | `mob_head` | `144:4` | standing head |
| `minecraft:zombie_wall_head[rotation=5,*]` | `mob_head` | `144:5` | standing head |
| `minecraft:zombie_wall_head[rotation=6,*]` | `mob_head` | `144:6` | standing head |
| `minecraft:zombie_wall_head[rotation=7,*]` | `mob_head` | `144:7` | standing head |
| `minecraft:zombie_wall_head[rotation=8,*]` | `mob_head` | `144:8` | standing head |
| `minecraft:zombie_wall_head[rotation=9,*]` | `mob_head` | `144:9` | standing head |
| `minecraft:zombie_wall_head[rotation=10,*]` | `mob_head` | `144:10` | standing head |
| `minecraft:zombie_wall_head[rotation=11,*]` | `mob_head` | `144:11` | standing head |
| `minecraft:zombie_wall_head[rotation=12,*]` | `mob_head` | `144:12` | standing head |
| `minecraft:zombie_wall_head[rotation=13,*]` | `mob_head` | `144:13` | standing head |
| `minecraft:zombie_wall_head[rotation=14,*]` | `mob_head` | `144:14` | standing head |
| `minecraft:zombie_wall_head[rotation=15,*]` | `mob_head` | `144:15` | standing head |
| `minecraft:zombie_wall_head[facing=north,*]` | `mob_head` | `144:2` | wall head |
| `minecraft:zombie_wall_head[facing=south,*]` | `mob_head` | `144:3` | wall head |
| `minecraft:zombie_wall_head[facing=west,*]` | `mob_head` | `144:4` | wall head |
| `minecraft:zombie_wall_head[facing=east,*]` | `mob_head` | `144:5` | wall head |
| `minecraft:zombie_wall_head[*]` | `mob_head` | `144:0` | head type collapsed |


Generated rows: **4633** across **1168** blocks.
