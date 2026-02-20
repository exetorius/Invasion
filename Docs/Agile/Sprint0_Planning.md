# Sprint 0: Design & Foundation

**Sprint Duration:** 2025-02-16 to 2025-02-23 (1 week)  
**Sprint Goal:** Make critical design decisions and complete worker hiring UI

---

## Sprint Backlog

### 🎯 Critical Design Decisions

- [ ] **Finalize Multiplayer Model** (0 SP)
  - Review `/GDD/04_Multiplayer.md`
  - Decide: Competitive, Co-op, or Hybrid
  - Document decision in GDD
  - Update ProductBacklog.md based on decision

- [ ] **Define Resource Economy** (0 SP)
  - Decide: Individual, Shared, or Tradeable
  - Document in `/GDD/06_Economy.md` (create if needed)
  - Update CLAUDE.md if architecture changes

---

### 💻 Development Tasks

- [ ] **Create Hire Workers UI** (5 SP)
  - Design mockup (can be rough)
  - Implement `UHiringScreenWidget`
  - Display available workers from RegionalPool
  - Show worker stats (name, role, combat, work efficiency)
  - "Hire" button calls Server RPC
  - Cost display (deduct credits on hire)
  - Test in multiplayer (2 clients)

- [ ] **Fire Workers** (2 SP)
  - "Fire" button on worker roster tile
  - Confirmation dialog
  - Server RPC to return worker to pool
  - Update UI automatically

---

### 📋 Documentation

- [ ] **Create GDD: Economy** (1 hour)
  - Define resource types
  - Define costs (worker hiring, base building future, etc.)
  - Define income sources (mission rewards, etc.)

- [ ] **Create GDD: Core Loop** (1 hour)
  - Define minute-to-minute gameplay
  - Define session structure (what does 1 "game" look like?)
  - Win/loss conditions

---

## Sprint Review (End of Week)

**Questions to Answer:**
1. Is multiplayer model finalized?
2. Can players hire workers via UI in multiplayer?
3. Can players fire workers?
4. Are design docs up to date?

---

## Retrospective Topics

- Was 1 week enough for design + implementation?
- Are design decisions clear and documented?
- Is the backlog well-structured?
- What blockers came up?

---

## Notes

- Focus on design first, then code
- Don't over-engineer - MVP is key
- Test multiplayer frequently
- Keep CLAUDE.md updated
