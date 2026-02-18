# Invasion

A strategic base management and tactical combat game built in **Unreal Engine 5** using **C++**.

You command a sovereign national base in a world under alien threat. Recruit and manage personnel, research technologies, engineer equipment, and deploy squads to defend against escalating incursions.

---

## Overview

| | |
|---|---|
| **Engine** | Unreal Engine 5 |
| **Language** | C++ (with Blueprint for UI) |
| **Multiplayer** | Optional, session-based via Steam (AdvancedSteamSessions) |
| **Solo** | First-class, complete experience |
| **Status** | Early development — Sprint 0 in progress |

---

## Core Design Philosophy

**Solo play is a complete, first-class experience.** Multiplayer is opt-in and session-based — not a requirement.

In multiplayer, each player commands a **sovereign national base**. Players share a game world and face a common threat, but each base belongs entirely to its owner. Players start a campaign together; no hot-dropping mid-campaign. The world is host-owned and persistent via Steam sessions.

Difficulty scales with diminishing returns per additional player (100% / 130% / 155% / 175%) so multiplayer is pressure, not punishment.

---

## Architecture

The project uses a modular architecture with focused modules per system, designed for fast iteration and explicit dependencies.

```
Source/
├── InvasionCore/               # Core types, interfaces, GameInstance
├── InvasionBaseManagement/     # Base management UI and logic
├── InvasionOnline/             # Sessions, matchmaking, Steam (stub)
├── InvasionGameSettings/       # Graphics, audio, keybindings (stub)
├── InvasionSaveSystem/         # Save/load, slot management (stub)
├── InvasionProgression/        # Unlocks, achievements, stats (stub)
└── InvasionTactical/           # Tactical battle module (stub)
```

### Key Patterns

- **GameInstance Subsystems** — primary pattern for all game systems
- **Per-player BaseManagerState** — replicated actor holding each player's base data
- **Event-driven UI** — tiles fire delegates upward, screens coordinate and call RPCs
- **Wrapped third-party plugins** — game code never calls AdvancedSteamSessions directly

---

## Base Management System

The first fully implemented system. Players hire, manage and deploy a roster of personnel across five roles:

| Role | Combat Skill | Work Efficiency |
|---|---|---|
| Soldier | High (50–90) | Moderate (40–75) |
| Scientist | Low (10–50) | High (60–95) |
| Engineer | Low (10–50) | High (60–95) |
| Medic | Moderate (30–60) | Moderate (40–75) |
| Pilot | Low (10–50) | Moderate (40–75) |

Workers have health, morale, injury severity, and status. Stats use float ranges to support future buff/debuff systems.

### Worker Replication

`UWorkerData` is a replicated `UObject`. Key implementation details:
- `bReplicateUsingRegisteredSubObjectList = true` on `ABaseManagerState`
- Workers registered via `AddReplicatedSubObject()` when hired
- `ReplicatedUsing=OnRep_WorkerRoster` triggers UI updates on clients
- Pool workers don't need subobject registration — their stats are static while available

---

## Current Sprint

**Sprint 0 — Foundation** | Feb 16–23, 2026

| # | Task | Points | Status |
|---|---|---|---|
| #2 | Finalise Multiplayer Model | 2 | ✅ Done |
| #3 | Worker Hiring UI | 5 | ⏳ In Progress |
| #4 | Fire Workers Feature | 2 | ⏳ To Do |
| #5 | Bug: Player 2 tile lists empty | — | 🐛 Blocked |
| #6 | Fix WorkerTileClass null on client | 2 | 🔧 To Do |

**Planned:** 9 SP | **Completed:** 2 SP

---

## Dev Notes

This project is built solo. Development follows a lightweight Agile process — 1-week sprints, Fibonacci story points, GitHub Issues for tracking.

Architecture decisions are documented in `/Docs/GDD/` and captured in `CLAUDE.md` for AI-assisted pair programming sessions.

Notable decisions logged so far:
- [Multiplayer Model: Sovereign Bases](/Docs/GDD/04_Multiplayer.md) — each player owns their base, solo is first-class
- Worker replication via `UObject` subobject list — avoids struct limitations while keeping data modular

---

## Roadmap (High Level)

- [x] Core module structure
- [x] Worker data model + replication
- [x] Per-player BaseManagerState
- [x] Regional worker pools
- [x] Hiring UI (single player)
- [ ] Hiring UI (multiplayer fix)
- [ ] Fire workers
- [ ] Nation selection screen
- [ ] Save system
- [ ] Research system
- [ ] Engineering system
- [ ] Tactical combat (long term)

---

## Setup

1. Clone the repo
2. Right-click `Invasion.uproject` → **Generate Visual Studio / Rider project files**
3. Build in your IDE
4. Open in Unreal Engine 5

> Requires **AdvancedSteamSessions** plugin. Steam must be running for multiplayer sessions.
