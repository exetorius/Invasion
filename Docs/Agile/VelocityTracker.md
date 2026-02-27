# Velocity Tracker

Track your story point velocity over time to improve sprint planning accuracy.

---

## Current Sprint

### Sprint 2 — Worker Assignment & Identity (March 2–6, 2026)
- **Goal:** Give players meaningful worker assignment choices and national identity before campaign start
- **Planned:** 8 SP
- **Status:** In Progress

| Issue # | Task | Story Points | Notes |
|---------|------|--------------|-------|
| #15 | Worker Pane — Manual Assignment | 5 | C++ complete. Blueprint + PIE test remaining |
| #16 | Nation Selection Screen | 3 | Not started |
| **TOTAL** | | **8** | |

---

## Velocity History

### Sprint 1 — Base Activity (Feb 19–25, 2026)
- **Planned:** 7 SP
- **Completed:** 10 SP (7 planned + 3 mid-sprint additions)
- **Velocity:** 10
- **Issues:** #7 ✅, #8 ✅, #9 ✅, #10 ✅, #11 ✅ (mid-sprint), #12 ✅ (mid-sprint)

| Issue # | Task | Story Points | Notes |
|---------|------|--------------|-------|
| 7 | Worker Hiring UI — Stat Display on Tiles | 1 | Carry-over from Sprint 0 |
| 8 | Task Foundation + Research Screen | 3 | |
| 9 | Engineering Screen | 1 | |
| 10 | Base Overview Dashboard | 2 | |
| 11 | UWorkerData Refactor — Private Members & Accessors | 2 | Mid-sprint, dependency for #10 |
| 12 | OnScreenDataReady pattern — base class retry | 1 | Mid-sprint, dependency for #10 |
| **TOTAL** | | **10** | |

- **What went well:** All goals delivered. Multiplayer tested in PIE. UWorkerData refactor clean. Task system and all four screens functional.
- **Scope bleed:** #11 and #12 justified as blockers for #10. Pattern discussion resolved — non-blockers go to backlog in future.
- **Bug found:** `GetRegionID()` returned by value — privatisation caused silent regression in `ManagementGameMode`. Assignment-to-temporary compiles without warning. Fixed via `SetRegionID()` setter.
- **Action items:** Raise non-blocker cleanup tasks as issues rather than absorbing into the sprint.

---

### Sprint 0 — Foundation (Feb 16–18, 2026)
- **Planned:** 9 SP
- **Completed:** 9 SP
- **Velocity:** 9
- **Notes:** First sprint. Delivered hire + fire worker UI end-to-end including multiplayer. Two mid-sprint bugs (#5, #6) resolved same sprint. Issue #7 deferred (stat display, Blueprint-only). Actual calendar time: 3 days (faster than 1-week estimate).

### Sprint Summary
- **Average Velocity:** 9.5 SP (2 sprints — Sprint 0: 9, Sprint 1: 10)
- **Trend:** Consistent. Sprint 2 planned at 8 SP (80% buffer).

---

## Story Point Reference Guide

Use this as your baseline for estimating:

| Points | Complexity | Time Estimate | Examples |
|--------|------------|---------------|----------|
| **1** | Trivial | 15-30 min | Fix typo, update comment, change color value |
| **2** | Simple | 1-2 hours | Add simple button, create data struct, simple bug fix |
| **3** | Moderate | Half day | Implement simple UI screen, add RPC function, write unit test |
| **5** | Medium | Full day | Create complex UI with multiple components, new gameplay feature |
| **8** | Large | 2-3 days | System refactor, complex multiplayer feature, new game mode |
| **13** | Very Large | Week | Major subsystem, tactical combat basics, save system |
| **21** | Epic | 2+ weeks | **Break this down!** Complete tactical combat, full research tree |

### Your Personal Baseline
**Reference Task:** "Add a simple UI button with click handler" = **2 SP**

Compare all tasks to this baseline:
- Simpler? → 1 SP
- Same? → 2 SP
- 2x more complex? → 3-5 SP
- Much more complex? → 8+ SP

---

## How to Use This Tracker

### At Sprint Start:
1. Create issues in GitHub with story point estimates
2. Update "Current Sprint" section above with planned tasks
3. Add issue numbers once created in GitHub

### During Sprint:
1. Move tasks between columns on GitHub board
2. Update "Status" column here when tasks complete
3. Track any blockers or scope changes

### At Sprint End:
1. Count completed story points
2. Calculate velocity (completed SP)
3. Move sprint to "Velocity History" section
4. Reflect: Were estimates accurate? What took longer than expected?
5. Adjust future estimates based on learnings

### Planning Next Sprint:
1. Use your average velocity (or last sprint if < 3 sprints)
2. Don't over-commit! Plan for ~80% of velocity to leave buffer
3. Example: If velocity = 9 SP, plan for ~7 SP of work

---

## Estimation Tips

### When to Increase Points:
- ✅ Multiplayer testing required (add +1 SP)
- ✅ New system/pattern (first time doing something)
- ✅ Unclear requirements (risk/uncertainty)
- ✅ Multiple files/systems involved
- ✅ Needs documentation updates

### When to Decrease Points:
- ✅ Reusing existing pattern (done this before)
- ✅ Clear requirements
- ✅ Simple copy-paste-modify
- ✅ No testing needed

### Red Flags (Break Down the Task):
- 🚩 Task is > 13 points
- 🚩 Description says "implement entire X system"
- 🚩 Can't clearly describe what "done" looks like
- 🚩 Multiple unrelated things in one task
- 🚩 You're not sure how to start

---

## Retrospective Questions

Ask yourself at end of each sprint:

1. **What went well?**
   - Which tasks were estimated accurately?
   - What patterns/techniques worked?

2. **What went poorly?**
   - Which tasks took way longer than expected?
   - What caused delays?

3. **What surprised you?**
   - Unexpected complexity?
   - Easier than thought?

4. **Action Items:**
   - What will you do differently next sprint?
   - Any process improvements?

---

## Notes

- **First 3 sprints:** Velocity will be unstable (learning curve)
- **After 3 sprints:** Average velocity becomes reliable
- **Burnout prevention:** Don't plan 100% capacity, leave 20% buffer
- **Consistency:** Better to complete 8 SP reliably than plan 15 and complete 6
