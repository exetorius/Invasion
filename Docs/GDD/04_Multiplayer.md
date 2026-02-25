# Multiplayer Design

**Status:** ✅ FINAL DECISION - v1.0 Locked (Feb 17, 2026)

---

## ✅ Final Multiplayer Model: Sovereign Bases

> *Decided Feb 17, 2026 after full design review.*

### Core Statement

Each player commands a **sovereign national base**. Solo play is a complete, first-class experience. Multiplayer is opt-in and session-based. Players start a campaign together. Players share a game world but not a base. Each base is the owning player's alone. The world is host-owned and persistent. Difficulty scales per additional player with diminishing returns. Deeper cooperation (facility sharing, RBAC) is architecturally possible, not yet scheduled.

### Key Decisions

| Decision | Choice | Rationale |
|---|---|---|
| Solo without server? | ✅ Yes | Solo is first-class, not an afterthought |
| Base ownership | ✅ Per player, sovereign | No shared bases |
| Multiplayer opt-in? | ✅ Yes, session-based | Players start a campaign together |
| Persistent world? | ✅ Yes, host-owned | Host saves, others rejoin when available |
| Hot-drop (join mid-campaign)? | ❌ No | Too many edge cases, too little gain |
| Difficulty scaling? | ✅ Yes, diminishing returns | Each player adds pressure, not punishment |
| Facility sharing / RBAC? | 🔮 Future | Architecturally possible, not scheduled |
| Region exclusivity? | ✅ Shared allowed | Players may co-habit a region — opt-in scarcity. Decided Feb 25, 2026. |

### Difficulty Scaling Formula

```
Base difficulty = Solo tuned (1 player = 100%)

Each additional player scales:
  - Global threat generation rate
  - Enemy spawn rates in tactical

1 player:  100% (baseline)
2 players: 130%
3 players: 155%
4 players: 175%  (diminishing returns by design)
```

> Variable exists in `AManagementGameMode`. Implement multiplier when tactical combat exists.

### Nationality / Sovereignty Flavour

Each player selects a **nation** — their base is that nation's HQ. This:
- Gives instant identity and ownership
- Scales naturally (ship with 4-6 nations, add more over time)
- Opens door to passive national bonuses (future, not blocking anything now)
- Maps cleanly to existing `BaseRegion` enum (rename/expand when ready)

**Nation determines region (decided Feb 25, 2026):** Nation and region are not separate choices.
Picking a nation implicitly sets the player's starting region. If separation is ever needed, it
is a clean additive change — add `RegionID` alongside `NationID` on `ABaseManagerState`.

**Region co-habitation (decided Feb 25, 2026):** Multiple players may start in the same region.
This is intentional — it creates organic tension over a shared worker pool and tighter resource
competition. Cooperation is opt-in. Players in the same region share a hiring pool, face closer
proximity to each other's missions, and may choose to coordinate or compete as they see fit.
Future: inter-player deals, trade agreements, or betrayal mechanics may build on this.

**SMART Scope:**
- Sprint 0: Model decided ✅
- Sprint 2: Nation selection screen (UI only, no mechanics) 🎯
- Sprint 3+: National passive bonuses (optional, additive)

### Session Model

- **Host-owned save.** World state lives on the host's machine/Steam account.
- Others join the host's session via Steam (AdvancedSteamSessions).
- When host is offline, the session is unavailable. Others wait.
- No dedicated server infrastructure required.

### What This Unlocks

- ✅ Hiring UI (Issue #3) — build for solo, works in MP
- ✅ Fire Workers (Issue #4) — same
- ✅ All base management features — sovereign model is consistent
- ✅ Future trading/cooperation — additive, not redesign

---

## Design History & Options Considered

### Option 1: Competitive Race
Players race to defeat the alien threat first. Individual bases, no interaction.
- **Rejected:** Feels isolated, punishes slower players, no thematic fit.

### Option 2: Cooperative Defense
Shared global threat, players defend different regions together.
- **Partially adopted:** Global threat concept kept, but full co-op dependency rejected (solo must work).

### Option 3: Asymmetric Roles
Players take different roles (Commander, Field Officer, Intel).
- **Rejected:** Requires 3+ players, role imbalance issues, massive refactor.

### Option 4: Hybrid (Regional Competition + Global Co-op)
Players compete for score while fighting shared threat.
- **Partially adopted:** Sovereign base model is the foundation. Hybrid scoring/trading deferred to future sprints.

### Hot-Drop (Join Mid-Campaign)
Allow solo players to flip to multiplayer on the fly.
- **Rejected:** Too many variables (what base does the joining player get? catch-up state? fairness?). Start Together is cleaner.

---

## Future Features (Not Scheduled)

These are architecturally possible with the current sovereign model but not planned:

- **Facility Sharing** — lend a spare hangar, share a research lab
- **RBAC Permissions** — Ally/Guest roles with granular facility access
- **Resource Trading** — send Credits/Supplies with a logistics tax
- **Mission Cooperation** — send workers/soldiers to assist another player's mission
- **Cross-session Async** — world accessible without host (requires backend)
- **National Bonuses** — passive buffs per nationality

---

## Technical Implementation Notes

**Already Implemented:**
- ✅ Per-player `BaseManagerState`
- ✅ Regional worker pools
- ✅ Full replication working
- ✅ Per-player architecture fits sovereign model perfectly

**To Implement (when relevant sprints arrive):**
- Difficulty multiplier variable in `AManagementGameMode` (stub now, wire later)
- Nation/nationality selection (UI only first)
- Host-owned save via Steam session (AdvancedSteamSessions already in stack)
