# Invasion - Base Management Design

**Version:** 1.1
**Last Updated:** 2026-02-22
**Status:** Active Design

---

## Overview

Base management is the strategic layer of Invasion. Between missions, the player runs their
base — hiring workers, directing research, manufacturing equipment, and monitoring the health
of their operation. It is the primary loop during the non-tactical phase of the game.

Each player operates a **sovereign base**. There is no shared base in multiplayer. What happens
inside your base is your responsibility.

---

## Screens

### Base Overview (Dashboard)
**Status:** ✅ Done (Sprint 1, Issue #10)

The default screen when entering base management. A read-only dashboard surfacing key
information from across all other screens in one place.

**Intended content:**
- Resource summary (Credits, Supplies)
- Worker counts by status (Idle, Working, On Mission, Injured)
- Active Research task count and progress indicators
- Active Engineering task count and progress indicators
- Recent news/event flashes (future — incident notifications, mission results)
- Graphs and visual indicators (future — pretty, not functional priority)

**Design intent:** The player should be able to glance at this screen and know the state of
their base without navigating elsewhere. It is also the fallback "home" screen — the game
may force-navigate here on critical incidents (worker death, task completion, incoming threat).

---

### Roster
**Status:** Built (Sprint 0–1)

A full list of all hired workers regardless of role. The player's current team.

**Intended content:**
- All hired workers displayed as tiles
- Name, role, key stats visible per tile
- Fire button per worker
- Future: filter/sort by role, status, stat

**Design intent:** Roster is intentionally role-agnostic. It is the catch-all view of the
player's workforce. Role-specific filtering will be added when the list warrants it — not as
separate screens, but as filters on this one.

"Barracks" refers to a physical base room in the future construction system. It is deliberately
not used as a screen name to avoid ambiguity.

---

### Hiring
**Status:** Built (Sprint 0)

Browse and hire workers from a regional pool.

**Intended content:**
- Available workers from the player's region
- Name, role, stats visible per tile
- Hire button per worker
- Future: global recruitment, transport mechanic, hire cost

**Design intent:** Supply is limited — the pool is finite and shared at the region level.
Workers hired by one player are no longer available to others in the same region. Scarcity
is intentional and feeds economic tension.

Hiring is currently free (grey-box phase). Cost will be introduced when the economy sprint runs.

**Regional hiring vision:** Players will eventually recruit globally, not just from their home
region. However, workers and resources do not teleport — they must be physically transported
to the base, with risk of interception or destruction en route. This is a future system and
should not be partially stubbed. Region is flavour only until transport mechanics exist.

---

### Research
**Status:** Built (Sprint 1)

Assign Scientists to research tasks. Tracks progress over time.

**Intended content:**
- Active research tasks displayed as tiles
- Contextual worker pane — Scientists only, individually selectable (see Worker Pane Pattern)
- Assigned worker count, progress bar, task name
- Assign / Unassign worker controls
- Future: research tree, prerequisites, convergent unlocks, alien artefact study, sub-type filtering

**Design intent:** Research is **input-driven and knowledge-producing**. Feed it alien corpses,
artefacts, or samples — it returns unlocks and capabilities. Some tasks need no physical input;
optionally providing one may accelerate progress. Completing Research typically gates Engineering
tasks (you must research it before you can build it).

Not all Research requires input material. Providing optional input may speed completion.

**Tech tree design (settled):**
- Fixed directed graph — structure is deterministic, the same every campaign
- Players learn optimal paths over multiple runs
- Prerequisite convergence — some nodes require two or more prior researches to unlock
- Randomness lives in **input availability** (enemy drops, mission loot), not the tree structure
- Accidental discoveries are a possible mechanic — rare, flavourful, does not restructure the tree
- Sub-types (Medical, Weaponry, Materials etc.) added as filters when the list grows

---

### Engineering (Workshop)
**Status:** Built (Sprint 1)

Assign Engineers to manufacturing tasks. Tracks progress over time.

**Intended content:**
- Active engineering tasks displayed as tiles
- Contextual worker pane — Engineers only, individually selectable (see Worker Pane Pattern)
- Assigned worker count, progress bar, task name
- Assign / Unassign worker controls
- Future: manufacture queue, material costs, vehicle construction, output to Warehouse

**Design intent:** Engineering is **output-driven and resource-consuming**. Consumes materials,
produces physical items. Typically gated by Research completing first. Output goes to the
Warehouse (see below). Sub-types added as filters when the list grows.

---

### Nation Selection Screen
**Status:** Sprint 2 target 🎯

Shown at campaign start, before the player enters base management. A one-time choice that
sets the player's national identity for the campaign.

**Design intent:** This screen is about ownership and identity, not mechanics. The player
should feel like they are *claiming* something, not filling in a form. No bonuses, no
stats — just the flag, the name, and the commitment.

- Player selects a nation from a list (4-6 at launch, expandable)
- Nation determines starting region — they are the same choice, not two separate selectors
- Stores `FName NationID` on `ABaseManagerState`
- Multiple players may select nations from the same region (co-habitation is allowed — see `04_Multiplayer.md`)
- Future: national passive bonuses wire to `NationID` when designed

**Out of scope for Sprint 2:** Bonuses, nation lore, flags/artwork (placeholder acceptable).

---

### Equip Agent
**Status:** Phase 2 — Not Yet Scheduled

Outfit soldiers with weapons and equipment before missions.

**Intended layout (XCOM Apocalypse-inspired):**
- Left pane — soldier list (portrait + name, click to select)
- Centre — soldier body silhouette with equipment slots (hands, armour, belt, etc.)
- Right pane — Warehouse inventory grid of available items to drag on/off

**Design intent:** This screen only becomes meaningful once a mission system and item economy
exist. Deliberately deferred until tactical combat is in scope. Do not stub or partially
implement prematurely.

---

## Warehouse (Inventory)
**Status:** Not Yet Implemented

A base-level inventory pool. All manufactured items land here on Engineering task completion.
The Equip Agent screen draws from it.

**Design intent:** The Warehouse is the catch-all store — mirrors the Roster pattern for workers.
Future subdivisions (Armoury for weapons/armour, Stockpile for materials, Hangar for vehicles)
follow the same pattern — filters on one screen, not separate screens, when the list warrants it.

---

## Worker Pane Pattern
**Status:** Not Yet Implemented — current auto-assign is a grey-box placeholder

Functional screens (Research, Engineering, future Medical etc.) each host a contextual
`UWorkerPaneWidget` — a shared widget filtered by the relevant role for that screen.

- Research screen: Scientists only
- Engineering screen: Engineers only
- Future Medical screen: Medics only

The player selects a specific worker from this pane to assign to a task. The pane draws from
`BaseManagerState.WorkerRoster` with a role filter — it is not bespoke per screen.

The Roster screen shows all workers and uses the same widget with no role filter applied.

---

## Bases & Outposts
**Status:** Phase 2 — Not Yet Scheduled (HQ only for now)

Players begin with a single **HQ** — their primary base, tied to their nation and region.
It is their most prized possession. Losing it is a serious setback, not an inconvenience.

**HQ:** Full base management capability. All screens (Research, Engineering, Roster, etc.)
operate from here. This is where the player's identity lives.

**Outposts:** Lightweight forward bases built in other regions to reduce mission reaction times.
Not a second HQ — no full management screens. Purpose: faster deployment, regional presence.
Scope and capability TBD when the mission system exists.

**Expansion model:** Players expand reach, not redundancy. The HQ remains the strategic heart.
Outposts are tactical tools, not fallback command centres — with one exception (see below).

### Backup HQ — Research-Gated Fallback *(Future Idea — Not Scheduled)*

**Concept (noted Feb 25, 2026):** A mid-to-late research tree unlock that allows a pre-designated
outpost to step up as a degraded HQ if the primary base is overrun. Prevents player elimination
without removing the consequence of losing the HQ.

**Intent:**
- Losing the HQ is painful — the fallback HQ operates at reduced capacity (fewer task slots,
  limited research tiers, reduced worker capacity)
- Players who invested in this research bought insurance; players who didn't gambled and lost
- Counter-attack to reclaim the original HQ is possible — the player is wounded, not out
- Creates a meaningful research choice: defensive resilience vs offensive capability

**Implementation note:** Depends on the outpost system and mission system existing. Do not
design further until both are in scope. This is a research tree node, not a base management
feature.

---

## Base Construction
**Status:** Phase 2 — Not Yet Scheduled

Tile-based room construction inspired by XCOM Apocalypse. Players lay out their base
physically — rooms occupy tiles, rooms provide functionality (labs unlock Research capacity,
workshops unlock Engineering capacity, barracks house soldiers, etc.).

**Design intent:** Construction adds a spatial and economic layer to base management.
Expanding your base costs resources and time. Room adjacency and layout may provide bonuses
(to be designed). This is a significant system — do not begin design until the core management
loop is stable and Phase 1 is complete.

**Reference:** XCOM Apocalypse base construction screen — rooms placed on a grid, each room
type has a build cost, build time, and functional purpose.

---

## Economy
**Status:** Stubbed — Credits and Supplies exist, no constraints yet

Economy is the primary driver of player FOMO and strategic tension. Scarcity of Credits forces
genuine decisions: research the alien weapon *or* manufacture more armour, buy a scientist *or*
fund a fighter jet.

Current state: hiring is free, manufacturing is free. This is intentional grey-boxing — get
the loop visible first, add friction in a dedicated economy sprint.

**Income model (decided Feb 25, 2026):** Passive subsidies from regional command (scaled by
reputation), plus sales of manufactured inventory. Performance bonuses are possible but not yet
designed. Full design in `06_Economy.md`.

Economy sprint scope (future):
- Hire costs wired to Credits
- Manufacturing costs wired to Credits and Supplies
- Subsidy income ticking on a server timer
- Inventory sales flow from Warehouse
- Balance pass

---

## Open Design Questions

- [x] **What are the income sources? How does the player earn Credits between missions?**
  Resolved (Feb 25, 2026): Passive subsidies from regional command based on reputation, plus
  inventory sales (X-COM style). Performance bonuses possible later. Full income system is a
  future sprint — see `06_Economy.md`. Enough to seed starting Credits and unblock hire costs.
- [x] **Does Research output a blueprint item, or does it directly unlock Engineering tasks?**
  Resolved (Feb 25, 2026): Directly unlocks Engineering tasks (option A). No blueprint item,
  no Warehouse dependency. Completing a research task flips an unlock flag on the Engineering task.
- [ ] Transport mechanic for global hiring — how is interception risk calculated and resolved?
- [ ] Room adjacency bonuses in base construction — do these exist and what do they provide?
