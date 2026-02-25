# Invasion - Game Design Document

**Version:** 1.1
**Last Updated:** 2026-02-24
**Status:** Active Development — Sprint 2 Planning

---

## Executive Summary

**Genre:** Turn-based Tactical Strategy / Base Management
**Platform:** PC (Steam)
**Multiplayer:** 2-4 Players — Sovereign Bases model (see `04_Multiplayer.md`)
**Inspiration:** XCOM, Phoenix Point, Phantom Brigade
**USP:** Multiplayer XCOM-like where each player commands a sovereign national base

---

## Core Vision

> Players manage a secret organization defending Earth from alien invasion. Each player operates their own sovereign national base, recruits personnel, researches alien technology, and deploys tactical squads to combat the alien threat.

---

## Game Pillars

### 1. **Strategic Depth**
- Meaningful choices in base management
- Resource scarcity forces prioritization
- Long-term planning vs short-term survival

### 2. **Tactical Combat** (Future)
- Turn-based squad tactics
- Environmental interaction
- Risk vs reward positioning

### 3. **Multiplayer Tension**
- Sovereign bases — each player commands their own national HQ
- Shared global threat creates cooperative pressure without shared dependency
- Difficulty scales per additional player (diminishing returns) — pressure, not punishment
- Future: trading, facility sharing, mission cooperation (not yet scheduled)

### 4. **Progression & Customization**
- Worker specialization and growth
- Tech tree unlocks
- Base upgrades

---

## Target Audience

**Primary:**
- XCOM fans aged 25-40
- PC strategy gamers
- Players wanting XCOM with friends

**Secondary:**
- Tactics enthusiasts
- Base-building fans
- Competitive strategy players

---

## Scope & Phases

### **Phase 1: Foundation (Current)**
- ✅ Worker management system
- ✅ Multiplayer replication
- ✅ Core base management UI (hire, fire, research, engineering, overview — Sprint 0–1)
- ⏳ Resource economy (Credits/Supplies exist, constraints not yet applied)
- ⏳ Nation selection screen (UI only — Sprint 2 target)

### **Phase 2: Core Loop**
- Mission system
- Basic tactical combat
- Research tree
- Base building

### **Phase 3: Polish & Expand**
- Advanced tactical features
- Mission variety
- Multiplayer balancing
- Steam integration

### **Phase 4: Post-Launch**
- Additional content
- Community feedback iteration
- Balance patches

---

## Design Decision Status

| Decision | Status | Detail |
|---|---|---|
| Multiplayer model | ✅ Decided | Sovereign Bases — see `04_Multiplayer.md` |
| Base ownership | ✅ Decided | Per-player, sovereign — no shared base |
| Resource economy | ⚠️ Partial | Income model decided (subsidies + inventory sales — see `06_Economy.md`). Hire costs and income tick not yet implemented. |
| Mission system | ⏳ Open | Solo missions per player is the intent; specifics not yet designed |
| Movement mode (tactical) | ⏳ Open | Awaiting design decision — see `03_TacticalCombat.md` |

---

## Document Structure

This GDD is split into multiple documents. Architecture and implementation patterns live in `CLAUDE.md`.

| File | Status | Contents |
|---|---|---|
| `00_Overview.md` | ✅ This file | High-level vision, phases, design status |
| `01_CoreLoop.md` | ❌ Not created | Gameplay loop, session structure, win/loss |
| `02_BaseManagement.md` | ✅ Active | Base screens, worker system, economy design |
| `03_TacticalCombat.md` | ✅ Active (pre-prod) | Combat design — many open questions |
| `04_Multiplayer.md` | ✅ Locked | Sovereign Bases model — final decision |
| `05_Progression.md` | ❌ Not created | Tech tree, unlocks, worker progression |
| `06_Economy.md` | ❌ Not created | Resources, costs, income sources |
| `07_UI_UX.md` | ✅ Active | Layout, navigation, interaction patterns |
| `08_TechnicalDesign.md` | ❌ Not created | Architecture lives in `CLAUDE.md` instead |
