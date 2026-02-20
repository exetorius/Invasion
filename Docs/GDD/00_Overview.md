# Invasion - Game Design Document

**Version:** 1.0  
**Last Updated:** 2025-02-16  
**Status:** Pre-Production / Design Phase

---

## Executive Summary

**Genre:** Turn-based Tactical Strategy / Base Management  
**Platform:** PC (Steam)  
**Multiplayer:** 2-4 Players (Co-op/Competitive - TBD)  
**Inspiration:** XCOM, Phoenix Point, Phantom Brigade  
**USP:** Multiplayer XCOM-like with competitive/cooperative elements

---

## Core Vision

> Players manage a secret organization defending Earth from alien invasion. Each player operates their own base (or shares one - TBD), recruits soldiers, researches alien technology, and deploys tactical squads to combat the alien threat.

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

### 3. **Multiplayer Tension** (Design Pending)
- Competitive: Race to defeat aliens first
- Co-op: Shared threat, individual bases
- Asymmetric: Different regions, different challenges

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
- ⏳ Core base management UI
- ⏳ Resource economy

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

## Critical Design Decisions Needed

### 🚨 **HIGH PRIORITY - Must Decide Soon:**

1. **Multiplayer Model**
   - [ ] Competitive (players race to complete objectives)
   - [ ] Co-op (players help each other)
   - [ ] Asymmetric (different roles/regions)
   - [ ] Hybrid (competitive with co-op elements)

2. **Base Ownership**
   - [ ] Per-Player Bases (current architecture)
   - [ ] Shared Global Base (requires refactor)

3. **Resource Economy**
   - [ ] Individual resources per player
   - [ ] Shared resource pool
   - [ ] Tradeable resources between players

4. **Mission System**
   - [ ] Solo missions (each player fights separately)
   - [ ] Combined squads (players can team up)
   - [ ] Competitive missions (PvP or race)

---

## Next Steps

1. Complete critical design decisions above
2. Create detailed system designs (see `/GDD` folder)
3. Build Product Backlog in `/Agile`
4. Prioritize features for MVP

---

## Document Structure

This GDD is split into multiple documents:

- `00_Overview.md` (this file) - High-level vision
- `01_CoreLoop.md` - Gameplay loop and progression
- `02_BaseManagement.md` - Base building and workers
- `03_TacticalCombat.md` - Combat system design
- `04_Multiplayer.md` - Multiplayer mechanics
- `05_Progression.md` - Tech tree, unlocks, upgrades
- `06_Economy.md` - Resources, costs, balance
- `07_UI_UX.md` - Interface and user experience
- `08_TechnicalDesign.md` - Architecture and implementation

**Note:** Design documents should drive code, not the other way around!
