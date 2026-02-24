# Invasion - Tactical Combat Design

**Version:** 0.1
**Last Updated:** 2026-02-24
**Status:** Pre-Production / Design Phase

---

## Overview

Tactical combat is the action layer of Invasion. When the strategic situation demands it —
alien incursion, mission objective, regional defence — a player deploys a squad from their
base and resolves the engagement in turn-based tactical combat.

**Relationship to base management:**
- Workers assigned to combat roles (Soldiers) are the squad pool
- Casualties feed back into the base layer (injury system, death consequences)
- Research and engineering outputs unlock squad equipment and tactical options

**Multiplayer context:**
- Each player's tactical mission is **independent** — sovereign model applies here too
- Players do not share squads or fight in the same tactical space (v1.0)
- Difficulty scales per number of players (see `04_Multiplayer.md`)
- Future: mission cooperation (send units to assist another player) is architecturally possible,
  not scheduled — do not design around it now

> This document captures early design thinking. Nothing here is final. Decisions are tracked
> in the Open Design Questions section below.

---

## Movement Mode

**Status:** ⏳ Pending — community research in progress

### The Question

> *"For a turn-based tactical game (XCOM-style), which movement approach would you prefer:*
> *grid-based tiles, free-form movement within a range, or a hybrid (free visual movement*
> *but snapping to cover/combat positions)?"*

Posted to:
- r/TurnBasedTactics (link TBD once posted)
- r/gamedesign (link TBD once posted)
- Additional community TBD

### Options Considered

| Option | Summary | Pros | Cons |
|---|---|---|---|
| **Grid** | Classic tile-based movement (XCOM 2014 style) | Cheap cover lookups, easy multiplayer sync, clear player communication, well-understood pattern | World geometry must conform to grid, coarser positioning, can feel mechanical |
| **Free-form** | Move anywhere within AP range (Phantom Brigade style) | Natural feel, uses real world geometry for cover, expressive positioning | Raycasting cost for cover, navmesh complexity, float sync across network, higher solo-dev scope |
| **Hybrid** | Visually free movement, but snaps to discrete cover/action points | Combines visual fluidity with calculation simplicity | More complex to implement than pure grid, requires authoring cover points in levels |

### Design Intent

The goal is **clarity** first. Players need to understand at a glance what a move means,
whether cover is valid, and what range they have. A solo developer budget favours the option
that minimises bespoke tooling and network edge cases.

Grid is the safe default — it is what the inspirations (XCOM, Phoenix Point) use and is
well-understood. Free-form and hybrid are more ambitious and should only be chosen if the
design benefit is clear and the scope is manageable.

### Community Research Results

> ⏳ **Placeholder — to be filled once Reddit feedback is gathered.**
>
> Summary of responses:
> - r/TurnBasedTactics: TBD
> - r/gamedesign: TBD
>
> Key themes from feedback: TBD

### Decision

> ⏳ **Pending community feedback.**
> Decision will be recorded here with rationale once the research phase is complete.
> Do not begin implementation until this is resolved.

---

## Open Design Questions

- [ ] **Movement mode** — awaiting Reddit community feedback (see above)
- [ ] **Mission structure** — how does a tactical mission start and end per player? (trigger, objectives, extraction)
- [ ] **Squad size** — how many units does a player field per mission? (XCOM default is 4–6)
- [ ] **Action point system** — AP per turn? Move + action? Full timeline (Phantom Brigade)?
- [ ] **Cover system** — full/half cover using geometry, or authored cover objects?
- [ ] **Line of sight** — tile-based visibility or true raycasting?
- [ ] **Multiplayer tactical** — simultaneous turns (async), or strictly one-at-a-time?
- [ ] **Does tactical combat exist in Sprint 2 scope, or is it later?**

---

## Future Sections (stubs — fill as decisions are made)

- **Mission Types** — what kinds of tactical engagements exist?
- **Enemy AI** — behaviour, difficulty tiers, alien types
- **Environmental Interaction** — destructible cover, hazards, verticality
- **Squad Composition Rules** — role requirements, limits
- **Outcome Consequences** — how mission results feed back into base state
