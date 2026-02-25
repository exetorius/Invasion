# Invasion - Economy Design

**Version:** 0.1
**Last Updated:** 2026-02-25
**Status:** Early Design — income model decided, implementation not yet started

---

## Overview

Economy is the primary driver of strategic tension. Credits and Supplies create scarcity that
forces genuine player decisions: hire the scientist or fund the weapon prototype, research alien
alloys or manufacture more armour. Without a wired economy, base management has no friction.

Current state: Credits and Supplies exist as replicated fields on `ABaseManagerState`. No
constraints are applied — hiring is free, manufacturing is free. This is intentional grey-boxing.

---

## Resources

| Resource | Purpose |
|---|---|
| Credits | Primary currency. Pays for hiring, manufacturing, future base construction. |
| Supplies | Secondary resource. Consumed by manufacturing tasks. Source TBD. |

---

## Income Sources (Decided Feb 25, 2026)

### 1. Regional Subsidies (Passive)

The player's regional command (the same pool from which workers are hired) provides a periodic
subsidy based on the player's **reputation**. This is the primary passive income stream —
analogous to XCOM's monthly council funding.

- Ticks on a server-side timer (cadence TBD — daily? weekly in campaign time?)
- Amount scales with reputation (TBD: what actions build reputation? Mission success, research progress, low casualties?)
- Provides predictable baseline income that the player can plan around

**Implementation note:** Reputation is not yet a system. For the economy sprint, stub a fixed
subsidy amount. Reputation scaling is wired when the reputation system exists.

### 2. Inventory Sales (Active)

Manufactured items from Engineering tasks can be sold for Credits. Inspired by X-COM's base
economy where surplus equipment was a cash source.

- Player selects items from the Warehouse to sell
- Sale price TBD (balance pass required)
- Creates a meaningful decision: keep the item for a soldier or sell it for Credits?

**Implementation note:** Depends on the Warehouse existing. Deferred until Warehouse screen is
built (Epic 4 scope).

### 3. Performance Bonuses (Future)

Possible bonus payments for mission success, rapid research completion, or maintaining low
regional threat. Not yet designed. Do not implement until base income is stable and balanced.

---

## Costs

### Hiring
- Each worker has a hire cost in Credits (TBD by role — Scientists more expensive than Soldiers?)
- Insufficient Credits should grey out the hire button on `UHiringWorkerTileWidget`
- Implementation tracked in backlog: **Economy — Hire Costs**

### Manufacturing
- Engineering tasks consume Credits and/or Supplies on start
- Amounts TBD (balance pass required)
- Implementation deferred until Warehouse and inventory sales exist

---

## Open Design Questions

- [ ] What is the subsidy cadence? (Campaign days? Real-time minutes?)
- [ ] What actions build reputation, and how does it scale subsidy amount?
- [ ] What are hire costs per role?
- [ ] What are manufacturing costs per task type?
- [ ] What is the sale price formula for inventory items?
- [ ] What are the sources of Supplies (the secondary resource)?

---

## Implementation Order

1. Seed non-zero starting Credits on `ABaseManagerState::InitializeBase()`
2. Wire hire costs to `Server_RequestHireWorker` (backlog: Economy — Hire Costs)
3. Implement subsidy tick on a server timer (backlog: Economy — Income Sources)
4. Implement inventory sales when Warehouse exists (Epic 4 dependency)
5. Balance pass once all sources and costs are wired
