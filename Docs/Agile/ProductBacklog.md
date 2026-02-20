# Product Backlog

**Last Updated:** 2025-02-16

---

## How to Use This Backlog

**Priority Levels:**
- 🔴 P0 - Critical (blocking other work)
- 🟠 P1 - High (needed for MVP)
- 🟡 P2 - Medium (important but not blocking)
- 🟢 P3 - Low (nice to have)

**Story Points:** Rough estimate (1 = few hours, 5 = few days, 13 = week+)

---

## Epic 1: Core Base Management

### 🔴 P0 - Design Decisions

- [ ] **[DECISION] Finalize Multiplayer Model** (0 SP - design only)
  - As a developer, I need to decide on competitive vs co-op vs hybrid
  - Blocks: Mission system, economy, tactical combat
  - **Action:** Review `/GDD/04_Multiplayer.md` and decide

- [ ] **[DECISION] Resource Economy Model** (0 SP - design only)
  - As a developer, I need to define how resources work
  - Options: Individual, shared, tradeable
  - Blocks: Trading UI, mission rewards

---

### 🟠 P1 - Base Management MVP

- [x] **Worker Data Structure** (3 SP)
  - As a player, I can see worker stats (health, combat skill, etc.)
  - ✅ Done - Full replication working

- [x] **Hire Workers (Debug Command)** (2 SP)
  - As a developer, I can test worker hiring via cheat commands
  - ✅ Done - `HireWorkersFromPool` command

- [x] **Worker Roster UI** (3 SP)
  - As a player, I can view my hired workers in a scrollable list
  - ✅ Done - `URosterScreenWidget` with tiles

- [ ] **Hire Workers (UI Button)** (5 SP)
  - As a player, I can hire workers from a hiring pool via UI
  - Acceptance Criteria:
    - [ ] Button opens hiring screen
    - [ ] Shows available workers with stats
    - [ ] Shows cost to hire
    - [ ] Hire button functional (calls Server RPC)
    - [ ] Works in multiplayer (tested with 2 clients)
  - Dependencies: Hiring UI design

- [ ] **Fire Workers** (2 SP)
  - As a player, I can fire workers to free up roster space
  - Acceptance Criteria:
    - [ ] "Fire" button on worker tile
    - [ ] Confirmation dialog
    - [ ] Worker returns to regional pool
    - [ ] Works in multiplayer

- [ ] **Worker Sorting/Filtering** (3 SP)
  - As a player, I can sort/filter my worker roster
  - Options: By role, by combat skill, by name
  - Nice-to-have for MVP, but helps with large rosters

---

### 🟡 P2 - Base Management Polish

- [ ] **Worker Name Customization** (2 SP)
  - As a player, I can rename my workers
  - Adds attachment to characters

- [ ] **Worker Stat Tooltips** (1 SP)
  - As a player, I can hover over stats to see explanations
  - "Combat Skill: 75 - Affects accuracy and damage"

- [ ] **Resource Display** (2 SP)
  - As a player, I can see my Credits and Supplies on all screens
  - Persistent header UI element

---

## Epic 2: Multiplayer Foundation

### 🟠 P1 - Essential Multiplayer

- [ ] **Trading System** (8 SP) - IF hybrid model chosen
  - As a player, I can trade resources with other players
  - Acceptance Criteria:
    - [ ] Open trade UI with player list
    - [ ] Select player and resource type
    - [ ] Input amount
    - [ ] Confirm trade (both players approve)
    - [ ] 10% tax applied
    - [ ] Replicated correctly to all clients
  - Dependencies: Multiplayer model decision

- [ ] **Global Threat Tracker** (5 SP) - IF hybrid model chosen
  - As a player, I can see the global alien threat level
  - Server-owned `AGlobalThreatState` actor
  - UI widget showing threat %
  - Auto-increments over time
  - Decreases on mission success (future)

- [ ] **Player Score System** (3 SP) - IF hybrid/competitive model chosen
  - Track player score in BaseManagerState
  - Display on UI
  - Award points for missions, research, etc.

---

### 🟡 P2 - Multiplayer QoL

- [ ] **Player List UI** (2 SP)
  - Show all connected players
  - See their region, score, threat level

- [ ] **Chat System** (5 SP)
  - Text chat between players
  - Use Unreal's built-in chat or custom

- [ ] **Ready Check System** (3 SP)
  - For mission start, turn-based sync, etc.

---

## Epic 3: Mission System (Future)

### 🟠 P1 - Mission Core

- [ ] **Mission Data Structure** (3 SP)
  - Define mission types, rewards, difficulty
  - `UMissionData` class

- [ ] **Mission Selection UI** (5 SP)
  - Geoscape-style map
  - Click region to see available missions
  - Accept mission button

- [ ] **Deploy Squad** (8 SP)
  - Select workers to send on mission
  - Validate squad composition
  - Launch mission (transitions to tactical map)

---

## Epic 4: Tactical Combat (Future - Large)

**Note:** This is a massive epic. Break down further once mission system is done.

- [ ] **Turn-Based Combat System** (40+ SP)
- [ ] **Cover System** (13 SP)
- [ ] **AI Enemies** (20 SP)
- [ ] **Abilities & Skills** (13 SP)

---

## Epic 5: Research & Tech Tree (Future)

- [ ] **Research Data Structure** (3 SP)
- [ ] **Research UI** (5 SP)
- [ ] **Tech Tree Unlocks** (8 SP)

---

## Epic 6: Polish & Steam Integration

### 🟡 P2 - Steam Features

- [ ] **Session Browser** (8 SP)
  - Find and join games via Steam
  - Wrap AdvancedSteamSessions plugin

- [ ] **Lobby System** (5 SP)
  - Pre-game lobby where players ready up
  - Choose region, see other players

- [ ] **Steam Achievements** (3 SP)
  - Define achievements
  - Hook into progression system

---

## Backlog Items (Unestimated)

**Ideas to Flesh Out Later:**
- Base building / room upgrades
- Worker progression / XP system
- Injury recovery mechanics
- Death/memorial system
- Save/Load system
- Settings menu (graphics, audio, keybindings)
- Tutorial / onboarding
- AI difficulty settings
- Modding support

---

## Definition of Done (General)

For any user story to be "Done":
- [ ] Code compiles without warnings
- [ ] Functionality works in single-player
- [ ] Functionality works in multiplayer (2 clients tested)
- [ ] No critical bugs
- [ ] Code reviewed (if working with team)
- [ ] CLAUDE.md updated if architecture changed
- [ ] Committed to main branch

---

## Sprint Planning

**Current Sprint:** Sprint 0 - Design & Foundation  
**Sprint Goal:** Finalize core design decisions, complete worker hiring UI

**Next Sprint:** TBD based on design decisions
