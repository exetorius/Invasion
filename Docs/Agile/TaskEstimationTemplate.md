# Task Estimation Template

Copy this template when creating new GitHub issues to ensure consistent estimation.

---

## Task Title
[5 SP] Example: Create Worker Hiring UI

---

## User Story / Description
As a [role], I want [goal] so that [benefit].

OR

Technical task: [Brief description]

---

## Story Point Estimate: **5**

### Breakdown:
- UI Design & Layout: 1 SP
- Worker Data Display: 1 SP  
- Server RPC Implementation: 1 SP
- Credits/Cost System: 1 SP
- Multiplayer Testing: 1 SP
- **TOTAL: 5 SP**

### Reasoning:
- Similar to baseline but more complex because [reason]
- Involves multiplayer, adding +1 SP
- New pattern, slight uncertainty

### Assumptions:
- RegionalWorkerPool already exists ✅
- BaseManagerState can handle hiring ✅
- UI framework is set up ✅

---

## Acceptance Criteria
- [ ] Criterion 1
- [ ] Criterion 2
- [ ] Criterion 3
- [ ] Multiplayer tested (2 clients)

---

## Technical Notes
- Extend `UBaseManagementScreenWidget`
- Server RPC pattern: `Server_HireWorker()`
- Reference existing `RosterScreenWidget` for patterns

---

## Dependencies
- Requires: [List any blocking tasks]
- Blocks: [List any tasks waiting on this]

---

## Definition of Done
- [ ] Code compiles
- [ ] Feature works as described
- [ ] Multiplayer tested
- [ ] No new warnings/errors
- [ ] CLAUDE.md updated (if architecture change)
- [ ] GitHub issue closed

---

## Actual Effort (Fill after completion)
**Actual Story Points:** [Leave blank, fill after]  
**Time Spent:** [Rough estimate in hours]  
**Was Estimate Accurate?** [Over/Under/Accurate]

### Lessons Learned:
- What took longer than expected?
- What was easier than expected?
- Would you estimate differently next time?

---

## Labels
Add in GitHub:
- `user-story` OR `task` OR `bug`
- `ui` (if UI work)
- `multiplayer` (if MP work)
- `backend` (if server/logic work)
