# Agile Workflow Guide

Your step-by-step guide to using the Agile system for Invasion development.

---

## 🗓️ Sprint Cycle (1 Week)

### **Monday: Sprint Planning**

1. **Review Velocity**
   - Check `VelocityTracker.md` for last sprint's velocity
   - Example: Last sprint completed 8 SP

2. **Plan Sprint Capacity**
   - Plan for ~80% of velocity (buffer for unknowns)
   - Example: If velocity = 8 SP, plan for 6-7 SP

3. **Select Tasks from Backlog**
   - Open `ProductBacklog.md`
   - Pick highest priority tasks that fit capacity
   - Move to "Current Sprint" in `VelocityTracker.md`

4. **Create GitHub Issues**
   - Use `TaskEstimationTemplate.md` as guide
   - Create issues in GitHub with labels
   - Add to GitHub Project board in "To Do" column
   - Create Milestone for the sprint (e.g., "Sprint 1")
   - Assign issues to milestone

---

### **Tuesday-Friday: Daily Work**

**Each Morning:**
1. Review GitHub board
2. Pick one task from "To Do"
3. Move to "In Progress" (only 1-2 tasks in progress max!)
4. Work on task

**When Task Complete:**
1. Test thoroughly (especially multiplayer!)
2. Move to "Testing" column
3. Final validation
4. Move to "Done"
5. Close GitHub issue
6. Update `VelocityTracker.md` (mark as ✅ Done)

**If Blocked:**
1. Add comment to GitHub issue explaining blocker
2. Move to "Blocked" column (if you have one)
3. Pick different task to work on
4. Resolve blocker when possible

---

### **Friday: Sprint Review & Retrospective**

**Sprint Review (15 min):**
1. Count completed story points
2. Update `VelocityTracker.md`:
   - Set "Completed SP" value
   - Calculate velocity
   - Move sprint to "Velocity History"

3. Demo completed work (if team, show each other)

**Retrospective (15 min):**
1. Answer retrospective questions in `VelocityTracker.md`
2. Review estimates vs actuals:
   - Which tasks took longer than expected?
   - Which were easier?
3. Identify improvements for next sprint
4. Update estimation approach if needed

**Plan Next Sprint:**
1. Use average velocity to plan capacity
2. Select tasks from backlog
3. Repeat cycle!

**Update README.md:**
1. Update the sprint table in `README.md` on GitHub:
   - Mark completed issues as ✅
   - Add any new issues created during the sprint
   - Update **Planned** and **Completed** SP totals
2. Update the Roadmap checkboxes for any newly completed features
3. Commit message: `docs: update README for Sprint X completion`

---

## 📝 Creating New Tasks

### **Step 1: Use Template**
Copy `TaskEstimationTemplate.md` content

### **Step 2: Estimate Story Points**
1. Read task description
2. Compare to baseline (simple button = 2 SP)
3. Break down into sub-tasks
4. Add up sub-task estimates
5. Add +1 if multiplayer testing needed
6. Add +1-2 if new pattern/uncertainty

### **Step 3: Create GitHub Issue**
1. Go to GitHub Issues → New Issue
2. Paste template
3. Fill in all sections
4. Add labels (`user-story`, `ui`, `multiplayer`, etc.)
5. Add to Project board
6. Assign to Milestone if part of current sprint

### **Step 4: Add to Backlog**
If not in current sprint:
- Add to `ProductBacklog.md` under appropriate epic
- Leave in "Backlog" column on GitHub board

---

## 🎯 Working on Tasks

### **Starting a Task:**
1. Move GitHub issue to "In Progress"
2. Create feature branch: `git checkout -b feature/issue-123-task-name`
3. Start coding!

### **During Work:**
- Commit frequently with clear messages
- Reference issue: `git commit -m "feat: add hiring UI (#123)"`
- If scope changes, update issue description
- If taking longer than estimated, note why in issue comments

### **Completing a Task:**
1. Test locally (PIE with 2+ players if multiplayer)
2. Run through acceptance criteria checklist
3. Update CLAUDE.md if architecture changed
4. Commit and push
5. Move to "Testing" or "Done" on board
6. Close issue with comment: "Completed in [commit hash]"
7. Update `VelocityTracker.md` actual SP if different

---

## 📊 Tracking Velocity

### **Why Track Velocity?**
- Know how much you can realistically complete
- Improve estimation accuracy over time
- Prevent burnout from over-committing

### **How to Calculate:**
```
Velocity = Sum of completed story points in sprint
```

Example:
- Sprint 1: Planned 10 SP, Completed 6 SP → Velocity = 6
- Sprint 2: Planned 8 SP, Completed 8 SP → Velocity = 8
- Sprint 3: Planned 9 SP, Completed 7 SP → Velocity = 7
- **Average Velocity = (6 + 8 + 7) / 3 = 7 SP**

### **Using Velocity:**
- Plan next sprint for ~7 SP (your average)
- Leave 20% buffer: Plan for 5-6 SP to be safe
- As velocity stabilizes (after 5+ sprints), confidence increases

---

## 🏷️ GitHub Labels Reference

| Label | When to Use |
|-------|-------------|
| `epic` | Large feature spanning multiple sprints (20+ SP) |
| `user-story` | User-facing feature |
| `task` | Technical/behind-the-scenes work |
| `bug` | Something broken that needs fixing |
| `tech-debt` | Code that needs refactoring |
| `design-decision` | Requires design choice before implementation |
| `multiplayer` | Affects multiplayer functionality |
| `ui` | UI/UX work |
| `backend` | Server/game logic |
| `blocked` | Cannot proceed due to dependency |
| `help-wanted` | Need assistance/discussion |

---

## ⚡ Quick Commands

**Start Sprint:**
```bash
# Update VelocityTracker.md with new sprint
# Create GitHub Milestone
# Create issues for sprint tasks
```

**During Work:**
```bash
git checkout -b feature/issue-123-task-name
# Work on task
git add .
git commit -m "feat: description (#123)"
git push origin feature/issue-123-task-name
```

**End Sprint:**
```bash
# Update VelocityTracker.md with completed SP
# Close completed issues
# Run retrospective
# Plan next sprint
```

---

## 📈 Success Metrics

**Good Signs:**
- ✅ Velocity stable across 3+ sprints
- ✅ Completing 80%+ of planned work
- ✅ Estimates within 1-2 SP of actual
- ✅ Not working evenings/weekends (sustainable pace)

**Warning Signs:**
- ⚠️ Consistently completing <50% of planned work (over-estimating capacity)
- ⚠️ Velocity wildly swinging (10 SP → 3 SP → 15 SP)
- ⚠️ Many tasks blocked
- ⚠️ Burnout / working excessive hours

**Fixes:**
- Reduce planned capacity (plan for less SP)
- Break down large tasks more
- Identify and remove blockers earlier
- Take breaks / sustainable pace

---

## 🎓 Estimation Cheat Sheet

| Your Task | Similar To | Story Points |
|-----------|------------|--------------|
| Fix typo in UI | Simple text change | **1** |
| Add button to screen | Baseline task | **2** |
| Create simple data struct | Basic C++ class | **2** |
| Implement UI screen with 3-4 widgets | Moderate UI work | **3** |
| Add RPC function + client UI | Network + UI | **5** |
| New gameplay system (hiring, firing, etc.) | Multiple files, multiplayer | **8** |
| Refactor major system | Complex, risky | **13** |
| Complete tactical combat | Epic - **Break Down!** | **21+** |

**When in doubt:** Round up (better to over-estimate than under-estimate)

---

## 📞 Need Help?

**Underestimated a task?**
- Normal! Especially in first few sprints
- Note why in retrospective
- Use that knowledge for similar tasks

**Overestimated a task?**
- Also normal!
- Note what made it easier
- Adjust future estimates

**Completely blocked?**
- Document blocker in issue
- Ask for help (GitHub comment, Discord, etc.)
- Move to different task if possible
- Unblock ASAP to keep sprint moving

**Velocity too low?**
- Are you being interrupted? (Context switching kills productivity)
- Too ambitious with planning? (Plan for less SP)
- Estimates too optimistic? (Add buffer to estimates)

**Velocity too high?**
- Great! But don't over-commit next sprint
- Gradually increase planned capacity
- Maintain sustainable pace
