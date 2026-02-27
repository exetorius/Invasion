# Product Backlog

**Last Updated:** 2026-02-27
**Sprint History:** Sprint 0 ✅ (9 SP) · Sprint 1 ✅ (10 SP)
**Current Sprint:** Sprint 2 — in progress

> ⚠️ **Maintenance Note:** After finalising any sprint plan or roadmap, re-verify this document
> still reflects current priorities. See reminder in CLAUDE.md → Task Management.

---

## Priority Levels

- 🔴 P0 — Blocking (nothing else can proceed without this)
- 🟠 P1 — High (needed for a coherent, feeling game loop)
- 🟡 P2 — Medium (important, not blocking)
- 🟢 P3 — Low (nice to have)

---

## Open Design Questions

These must be answered before the relevant items below can be scoped or estimated.

| Question | Blocks |
|---|---|
| Campaign clock format — Day/Month/Year? Abstract timer? | Persistent Top Bar, Campaign Clock |
| Is campaign time pausable in base management, or real-time? | Persistent Top Bar, Campaign Clock |

**Resolved (Feb 25, 2026):**
- Income sources → Passive subsidies from regional command (reputation-based) + inventory sales. See `06_Economy.md`.
- Research output → Directly unlocks Engineering tasks (no blueprint item). Unblocks Task Completion Rewards.

---

## Epic 1: Base Management — Loop Completion

The existing screens are structurally complete (Sprint 0–1). This epic finishes the loop:
making economy real, replacing grey-box auto-assign with meaningful worker selection,
and giving task completion an output.

### 🟠 P1

- [ ] **Worker Pane — Manual Assignment** (~5 SP) — **C++ complete, Blueprint + PIE test remaining**
  As a player, I want to select a specific worker to assign to a task so that the choice feels meaningful.
  - `UWorkerTileBase` created — abstract tile base, role-specific display via Blueprint subclass
  - `UWorkerPaneWidget` implemented — filters idle workers by role, callback-driven assignment
  - Research + Engineering screens wired — auto-assign replaced with pane call
  - Blueprint work remaining: `WBP_WorkerPane`, tile Blueprint subclass, PIE test
  - Roster screen uses the same widget with no role filter (future)
  - Multiplayer test required (+1 SP)
  - _Design: `02_BaseManagement.md` → Worker Pane Pattern_

- [ ] **Nation Selection Screen** (~3 SP)
  As a player, I want to choose a national identity for my base before a campaign starts so that I have a sense of ownership.
  - UI only — no mechanical bonuses yet
  - Shown at campaign start, before entering base management
  - Adds `FName NationID` to `ABaseManagerState`
  - Nation selection screen widget (new screen slot or pre-game flow)
  - _Design: `04_Multiplayer.md` → Nationality / Sovereignty Flavour (Sprint 1-2 target)_

- [ ] **Economy — Hire Costs** (~3 SP)
  As a player, I want hiring workers to cost Credits so that workforce decisions have weight.
  - Wire Credits deduction to `Server_RequestHireWorker`
  - Show hire cost per worker on `UHiringWorkerTileWidget`
  - Prevent hire if insufficient Credits (grey out button + message)
  - _Depends on: Economy — Income Sources (or at minimum seed starting Credits to a non-zero value)_

- [ ] **Economy — Income Sources** (~5 SP)
  As a player, I want to earn Credits over time so that the economy has a loop.
  - _Design decision required: see Open Design Questions above_
  - Options: funding per active base region (passive income), mission rewards, worker productivity, or combination

- [ ] **Task Completion Rewards** (~3 SP)
  As a player, I want Research and Engineering tasks to produce something on completion so that assigning workers feels purposeful.
  - Research completing → unlock flag or placeholder output (stub for tech tree)
  - Engineering completing → item added to Warehouse (or placeholder log until Warehouse exists)
  - Timer resets to 0 currently with no output — this fixes that
  - _Design decision required: does Research output a blueprint or unlock directly?_

### 🟡 P2

- [ ] **Persistent Top Bar** (~3 SP)
  As a player, I want to always see my Credits and a campaign clock so that I feel time and economic pressure.
  - Always-visible Credits balance
  - Campaign date/time tick (real-time or driven by a server timer)
  - _Design decisions required: clock format, pause behaviour — see Open Design Questions_
  - _Design: `07_UI_UX.md` → Top Bar_

- [ ] **Worker Sorting / Filtering on Roster** (~2 SP)
  As a player, I want to filter or sort my roster by role or status so I can find specific workers quickly.
  - Filter by role (All / Soldier / Scientist / Engineer / Medic / Pilot)
  - Filter by status (Idle / Working / On Mission / Injured)

- [ ] **Worker Name Customisation** (~2 SP)
  As a player, I want to rename my workers so I can attach meaning to individuals.
  - Inline edit on Roster tile (click name to edit)
  - `SetWorkerName()` already exists on `UWorkerData` — wire RPC to propagate

- [ ] **Worker Stat Tooltips** (~1 SP)
  As a player, I want to hover stats to see explanations so I understand what each number means.
  - "Combat Skill: 75 — Affects accuracy and damage in tactical missions"
  - Blueprint-only work; C++ data backing already exists

---

## Epic 2: World Presence & Threat

The World screen and global threat give context and urgency to base management.
Without these, the player manages a base with no external pressure or reason to act.

### 🟠 P1

- [ ] **Global Threat Tracker** (~5 SP)
  As a player, I want to see alien threat rising over time so that I feel urgency.
  - Server-owned `AGlobalThreatState` actor (AInfo, replicated to all clients)
  - Auto-increments on a server tick (rate TBD)
  - Visible to all players — multiplayer pressure is shared
  - Future: decremented on successful missions

- [ ] **World Screen — Region Map** (~8 SP)
  As a player, I want a world map showing regions and threat levels so I know where to focus.
  - Replaces `UWorldScreenWidget` stub
  - Displays regions with threat level indicators
  - Click region → future: shows available missions (stub for now)
  - _Depends on: Global Threat Tracker for meaningful data_

### 🟡 P2

- [ ] **News Ticker** (~3 SP)
  As a player, I want a scrolling event feed in the top bar so I'm aware of what's happening without navigating each screen.
  - Clickable items navigate to the relevant screen
  - Events: task completion, worker injury, threat level change, hire/fire
  - _Design: `07_UI_UX.md` → Interactive News Ticker_

---

## Epic 3: Mission System

Missions connect base management to tactical combat. Workers go out, consequences come
back. This is Phase 2 scope — do not begin until Epic 1 loop is stable.

### 🟠 P1

- [ ] **Mission Data Structure** (~3 SP)
  - `FMission` USTRUCT: region, type, difficulty, reward, deadline
  - Server-seeded on `AGlobalThreatState`
  - Replicates natively in TArray (same pattern as `FBaseTask`)

- [ ] **Deploy Squad** (~8 SP)
  As a player, I want to select soldiers and dispatch them on a mission so that tactical combat has a launchpad.
  - Select workers from Roster (Soldiers only, `EWS_Idle` filter)
  - Validate squad composition (min 1, max N TBD)
  - Commit: sets selected workers to `EWS_OnMission`
  - Return on mission completion / failure (with casualties)
  - _Depends on: Mission Data Structure_

### 🟡 P2

- [ ] **Mission Selection UI** (~5 SP)
  - Shown on World screen when a region is selected
  - Lists available missions, difficulty, deadline, reward
  - Accept → triggers Deploy Squad flow
  - _Depends on: World Screen, Mission Data Structure_

---

## Epic 4: Character & Equipment

Worker detail, inventory, and pre-mission loadout. Deferred — only meaningful once
a mission system and item economy exist. Do not partially implement prematurely.

- [ ] **Character Screen** (~5 SP) — Full worker detail: stats, injury history, equipment slots
- [ ] **Warehouse Screen** (~5 SP) — Base inventory: items produced by Engineering tasks
- [ ] **Equip Agent Screen** (~8 SP) — Pre-mission loadout: assign items from Warehouse to soldier slots
  - _Design: `02_BaseManagement.md` → Equip Agent (XCOM Apocalypse-inspired)_
  - _Depends on: Warehouse, Engineering task completion rewards, Mission system_

---

## Epic 5: Research Tree

Real research progression — a fixed directed graph with prerequisite convergence,
outcomes that unlock Engineering tasks, and meaningful player decisions per run.

- [ ] **Research Tree Data Structure** (~5 SP) — Directed graph, fixed structure, convergent prerequisites
- [ ] **Tech Tree UI** (~8 SP) — Visual tree: locked / available / completed nodes
- [ ] **Research → Engineering Unlock** (~3 SP) — Completing a research node enables Engineering tasks
  - _Depends on: Research Tree Data Structure + Task Completion Rewards (Epic 1)_
  - _Design: `02_BaseManagement.md` → Research (settled tech tree design)_

---

## Epic 6: Multiplayer Polish

Quality-of-life for the session experience. All items here are additive — sovereign model
works without them.

- [ ] **Player List UI** (~2 SP) — Show connected players, their nations/regions, threat levels
- [ ] **Ready Check System** (~3 SP) — Campaign start gate: all players ready before world begins
- [ ] **Chat System** (~5 SP) — Text chat between players in session
- [ ] **Steam Session Browser** (~8 SP) — Find and join games via Steam (wraps AdvancedSteamSessions in `UInvasionSessionSubsystem`)
- [ ] **Lobby System** (~5 SP) — Pre-campaign lobby: nation selection, player list, ready check

Note: Trading and Facility Sharing are architecturally possible under the Sovereign model
but are not yet scheduled. See `04_Multiplayer.md` → Future Features.

---

## Epic 7: Save System & Steam Integration

- [ ] **Campaign Save / Load** (~13 SP) — Full save via `UInvasionSaveSubsystem`
  - Saves: `BaseManagerState` (roster, tasks, resources, nation), `AGlobalThreatState`
  - Slot management UI (multiple save slots)
  - _InvasionSaveSystem module stub is ready_

- [ ] **Steam Session Persistence** (~5 SP) — Host-owned session; clients rejoin on reconnect
  - Wraps AdvancedSteamSessions in `UInvasionSessionSubsystem`
  - _InvasionOnline module stub is ready_

---

## Epic 8: Tactical Combat

Large scope. Design decisions in `03_TacticalCombat.md` are still open (movement mode,
AP system, cover, line of sight). Do not begin until Mission System (Epic 3) is stable
and those decisions are resolved.

- [ ] **Movement Mode Decision** — Grid / free-form / hybrid (see `03_TacticalCombat.md`)
- [ ] **Turn-Based Combat System** (~21+ SP) — Break down once movement decision is made
- [ ] **Cover System** (~8 SP)
- [ ] **AI Enemies** (~13 SP)
- [ ] **Abilities & Skills** (~13 SP)

---

## Future / Unscheduled

Good ideas not yet ready to scope. Raise as issues when the relevant system exists.

- Base building / room construction (XCOM Apocalypse tile grid)
- National passive bonuses (after nation selection is stable)
- Worker progression / XP system
- Injury recovery system
- Death consequences and memorial system
- Worker personality traits affecting morale decay
- Multi-region hiring with transport / interception risk
- Facility sharing and RBAC between players
- Resource trading between players
- `FInstancedStruct` role-specific payloads on `UWorkerData` (when roles diverge enough)
- Settings menu — `InvasionGameSettings` module stub is ready
- Steam achievements
- Tutorial / onboarding

---

## Completed Work

### Backlog Cleanup (Feb 24, 2026)

| # | Task |
|---|---|
| #13 | `AddMaxHealth` upper clamp fixed |
| #14 | `BindWidget` properties privatised; redundant `NativeConstruct` overrides stripped |

### Sprint 1 — Base Activity (Feb 19–25, 2026) | 10 SP

| # | Task | SP |
|---|---|---|
| #7 | Hiring + Roster UI — Stat Display on Tiles | 1 |
| #8 | Task Foundation + Research Screen | 3 |
| #9 | Engineering Screen | 1 |
| #10 | Base Overview Dashboard | 2 |
| #11 | UWorkerData Refactor — Private Members & Accessors | 2 |
| #12 | OnScreenDataReady Pattern — base class retry | 1 |

### Sprint 0 — Foundation (Feb 16–18, 2026) | 9 SP

| # | Task | SP |
|---|---|---|
| #2 | Finalise Multiplayer Model (Sovereign Bases) | 2 |
| #3 | Worker Hiring UI | 5 |
| #4 | Fire Workers | 2 |
| #5 | Bug: Player 2 tile lists empty | — |
| #6 | Fix WorkerTileClass null on client | — |

---

## Definition of Done (General)

- [ ] Code compiles without warnings
- [ ] Feature works in single player
- [ ] Feature works in multiplayer (2 clients, PIE tested)
- [ ] No critical bugs introduced
- [ ] CLAUDE.md updated if architecture changed
- [ ] GitHub issue closed
- [ ] VelocityTracker.md updated
