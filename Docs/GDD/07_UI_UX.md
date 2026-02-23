# Invasion - UI/UX Design

**Version:** 1.0
**Last Updated:** 2026-02-22
**Status:** Active Design

---

## Visual Style

**Direction:** Sci-fi, industrial, utilitarian. Dark palette with functional chrome — this is a
command centre, not a consumer app. Reference points: XCOM Apocalypse, militaristic HUDs,
cold war bunker aesthetic.

The UI should feel like hardware the player is operating, not a menu they are clicking through.
Every screen is a panel in a command console.

---

## Layout

```
┌─────────────────────────────────────────────────────┐
│  TOP BAR — Campaign date | Credits | News Ticker    │
├─────────────────────────────────────────────────────┤
│                                                     │
│                                                     │
│               SCREEN CONTENT AREA                   │
│                                                     │
│                                                     │
├─────────────────────────────────────────────────────┤
│  BOTTOM NAV — Main screen tabs (control panel)      │
└─────────────────────────────────────────────────────┘
```

**Top bar** — information only, always visible:
- Campaign date/time (see Campaign Clock)
- Credits (current balance, always visible for economic pressure)
- Interactive news ticker (see below)
- Settings accessible via ESC key or a dedicated settings icon — not part of main nav

**Bottom nav** — primary navigation, styled as a control panel:
- Tabs are physical-feeling controls, not flat buttons
- Controller-friendly by design — bumpers or D-pad cycle through tabs
- Tab order (left to right):

| # | Tab | Screen |
|---|-----|--------|
| 1 | Overview | Base Overview Dashboard |
| 2 | World Map | Global situation map |
| 3 | Roster | All hired workers |
| 4 | Hiring | Regional worker pool |
| 5 | Research | Research tasks |
| 6 | Engineering | Manufacturing tasks |

---

## Campaign Clock

A campaign date and time ticks continuously. It is always visible in the top bar.

**Design intent:** Time pressure is a core fear mechanic. The player should never feel idle.
Research completes on a date. UFOs arrive on a date. Credits drain on a schedule. Sitting on
your hands has consequences.

- Displayed as campaign date (e.g. Day 14 / March 2031) — exact format TBD
- Drives task completion (research, engineering progress tied to time)
- Drives world events (UFO appearances, alien activity, funding deadlines)
- May be pausable in base management — TBD (XCOM allows pause, real-time adds pressure)

---

## Interactive News Ticker

A scrolling feed of game events displayed permanently in the top bar.

**Behaviour:**
- Events scroll passively when unread
- Each item is **clickable** — clicking navigates directly to the relevant screen
- Examples:
  - "Research Complete: Alien Autopsy" → navigates to Research screen
  - "Engineering Complete: Plasma Rifle x3" → navigates to Engineering screen
  - "Agent Injured: Sgt. Harris" → navigates to Roster screen
  - "UFO Detected Over Europe" → navigates to World Map
- Critical events may **flash or highlight** to demand attention without forcing navigation
- The game does not hard-navigate the player without consent — the ticker is the prompt,
  the player chooses when to act

**Design intent:** The ticker is the nervous system of the UI. It replaces the need for
modal interruptions on routine events while still surfacing everything the player needs to
know. It makes the Base Overview feel less essential as a mandatory stop and more like a
deeper summary for players who want it.

---

## Sub-Navigation

Some screens contain internal navigation for contextual depth without leaving the screen.

Examples:
- Research/Engineering screens: worker pane for assigning individual workers
- Future: Research screen sub-filter by type (Medical / Weaponry / Materials)
- Future: Roster screen filter by role or status

Sub-nav should feel like a secondary control tier — visually subordinate to the bottom nav
but consistent in style.

---

## Modals and Popups

**Philosophy:** Power to the player. Popups serve the player, not the game.

**Rules:**
- All confirmation popups have a "Don't show again" option
- Popups are non-blocking where possible — the game does not pause waiting for the player
  to dismiss routine notifications
- Critical confirmations (firing a worker, abandoning a mission) retain the popup but
  respect the disable toggle

**Input slot popups (future):**
When a Research or Engineering task has an optional or required input slot, clicking the
empty slot opens a selection popup:
- Available inputs shown normally
- Acquired but unassigned inputs shown normally and selectable
- Known but not yet acquired inputs shown greyed out (player knows they exist)
- Undiscovered inputs shown as a greyed-out question mark (tantalising, not frustrating)

This pattern creates informed decision-making — the player always knows what they're missing
and why they might want it.

---

## Controller Support

Controller support is a first-class requirement, not a post-launch addition.

**Rationale:** Steam Deck compatibility and couch play are target use cases. A controller
player should be able to navigate all base management screens without friction.

**Approach:**
- Bottom nav: bumpers (LB/RB) cycle through tabs
- D-pad / left stick: navigate within a screen (tile lists, panes)
- A/Cross: confirm / interact
- B/Circle: back / cancel
- Y/Triangle: contextual action (e.g. assign worker, open details)
- Start / Menu: open settings

Implementation via Unreal Enhanced Input — same action mappings support both mouse/keyboard
and controller. Do not implement separate controller-only code paths.

**Note:** Full controller navigation requires UI focus management to be designed into widgets
from the start. Do not retrofit this later — ensure all interactive widgets are focusable and
navigable via gamepad.

---

## Keyboard Shortcuts

- **ESC** — Open settings / close current popup
- **Tab / Shift+Tab** — Cycle nav tabs (keyboard equivalent of bumpers)
- **Future:** Hotkeys for each nav tab (e.g. 1-6)

Full keybinding remapping via Enhanced Input remapping API (see Settings architecture in CLAUDE.md).

---

## Open Design Questions

- [ ] Is campaign time pausable in base management, or does it run in real-time?
- [ ] Campaign date format — Day/Month/Year? Mission count? Abstract timer?
- [ ] Does the news ticker persist across sessions (save/load), or is it session-only?
- [ ] Maximum news ticker history — how many events are retained?
- [ ] Are there screen transitions / animations between tabs, or instant cuts?
