# Base Management System — Architecture Reference

> Full architecture reference for `InvasionBaseManagement`. Stable — system is complete.
> See CLAUDE.md for active principles and sprint context.

---

## Status
✅ Hire/fire complete (Sprint 0), all screens delivered (Sprint 1), C++ data layer complete (Sprint 2). Multiplayer tested in PIE.

---

## Core Components

- `UWorkerData` — Individual worker data (UObject with replication support)
- `ABaseManagerState` — Per-player worker roster and base state (AInfo actor)
- `ARegionalWorkerPool` — Server-owned hiring pools per region (AInfo actor)
- `AManagementGameMode` — Spawns pools and player states on game start
- `UInvasionCheatManager` — Debug commands for testing
- `UBaseManagementScreenWidget` — Base class for all management screens
- `URosterWorkerTileWidget` / `URosterScreenWidget` — Fire flow UI
- `UHiringWorkerTileWidget` / `UHiringScreenWidget` — Hire flow UI

---

## Worker Data Structure (v1.0)

```cpp
// Identity
FGuid UniqueID;           // Auto-generated, no setter
FString Name;
EWorkerRace Race;         // Human-only for now
EWorkerRole Role;         // Soldier/Scientist/Engineer/Medic/Pilot — set once

// Combat Stats
float Health;             // 0 to MaxHealth
float MaxHealth;          // Base 100, buffable
float CombatSkill;        // 0-100

// Work Stats
float WorkEfficiency;     // 0-100, wired into task progress (summed per assigned worker / 100 per tick)

// State
float Morale;
EWorkerInjurySeverity InjurySeverity;
bool bIsDead;             // Set via Kill() only — never directly
EWorkerStatus CurrentStatus; // via SetCurrentStatus() only
```

---

## Multiplayer Architecture

```
ManagementGameMode (spawns on BeginPlay)
├─ RegionalWorkerPools (Europe, US, Asia)
│  └─ Auto-generates workers with role-based stat ranges
└─ BaseManagerState (one per player)
   ├─ OwningPlayerState
   ├─ BaseRegion (FName, derived from ENation)
   ├─ WorkerRoster[] — replicated
   ├─ Credits
   └─ Supplies
```

---

## Replication Pattern (CRITICAL)

UObjects don't auto-replicate — special setup required:

```cpp
// Constructor
bReplicateUsingRegisteredSubObjectList = true;  // REQUIRED

// AddWorker
WorkerRoster.Add(NewWorker);
AddReplicatedSubObject(NewWorker);
OnWorkerRosterChanged.Broadcast();  // manual — OnRep never fires on server

// RemoveWorker
if (!HasAuthority()) { Server_RemoveWorker(OldWorker); return; }  // authority FIRST
WorkerRoster.Remove(OldWorker);
RemoveReplicatedSubObject(OldWorker);
OnWorkerRosterChanged.Broadcast();

// WorkerData
virtual bool IsSupportedForNetworking() const override { return true; }

// Pool — use Actor as outer, NOT GetTransientPackage()
UWorkerData* NewWorker = NewObject<UWorkerData>(this);
```

**Key lessons:**
1. `bReplicateUsingRegisteredSubObjectList = true` required before `AddReplicatedSubObject` works
2. UObjects need persistent outer (Actor) to replicate
3. `OnRep` never fires on server — always `Broadcast()` manually after mutations
4. Pool workers DO need `AddReplicatedSubObject` — array count replicates, but object refs are null without it
5. Authority check BEFORE contains/null check — clients don't have full server roster
6. Subobject registration transfers with ownership — `Remove` on source, `Add` on destination
7. When already in `_Implementation`, call `Foo_Implementation()` directly — skip RPC machinery

---

## Delegate Pattern

```
DECLARE_DELEGATE                   → Single-cast, C++ only, Execute()
DECLARE_MULTICAST_DELEGATE         → Multi-cast, C++ only, Broadcast() — use for C++ UI
DECLARE_DYNAMIC_MULTICAST_DELEGATE → Multi-cast, Blueprint-assignable, AddDynamic()
```

Rule: `MULTICAST` for C++ widget binding. `DYNAMIC_MULTICAST` only if Blueprint binds directly.

---

## Hiring Flow

1. `RegionalWorkerPool` generates workers on game start → broadcasts `OnAvailableWorkersChanged`
2. `OnRep_AvailableWorkers` → clients refresh hiring UI
3. Player clicks Hire → tile fires `OnHireClicked(WorkerData)`
4. `HiringScreenWidget` → `PC->Server_RequestHireWorker(Worker, Pool)`
   ⚠️ Never call Server RPCs on `ARegionalWorkerPool` from client — no owning connection, silent fail
5. Worker deregistered from pool, registered on `BaseManagerState`
6. `OnRep_WorkerRoster` → `OnWorkerRosterChanged` → roster UI updates

## Firing Flow

1. Player clicks Fire → tile fires `OnFireClicked(WorkerData)`
2. `RosterScreenWidget` → `PC->Server_RequestFireWorker(Worker)`
3. `Server_RequestFireWorker_Implementation` finds pool via `GetAllActorsOfClass` + region match
4. `Base->RemoveWorker` → deregisters, broadcasts
5. `Pool->Server_ReturnWorker_Implementation` (direct — already server-authoritative)
6. Worker re-registered in pool → `OnAvailableWorkersChanged` → hiring UI refreshes

---

## UI Architecture

```
UBaseManagementScreenWidget        ← all screens inherit
    OnScreenDataReady()            ← children override this, NOT NativeConstruct

Tiles are dumb — fire events upward
Screens are coordinators — handle events, call RPCs
```

- Children override `OnScreenDataReady()` only — base class owns the retry loop
- Override that only calls `Super` is noise — remove it (`UBaseOverviewScreenWidget` is the reference)
- `CachedPool` is hiring-screen-local — not on base class

---

## Key Decisions (baked in — do not revisit)

- `FBaseTask` is USTRUCT — replicates natively in TArray, no subobject registration
- `AssignedWorkerIDs` stored as `TArray<FGuid>` — raw UObject pointers not safe across network
- `Progress` in elapsed seconds; timer ticks 1s: `Progress += 1.0f * AssignedWorkerCount`
- Mutating struct fields in TArray requires copy-modify-assign at the task level
- `ENation` enum in `CampaignTypes.h` — `GetRegionNameFromNation()` / `GetAllUniqueRegions()` are free functions
- `PlayerNation` may move to PlayerState when multi-base arrives — TODO in `BaseManagerState.h`
- Nation combo box on Base Overview is temporary — move to pre-campaign screen (#24)

---

## Future Expansion

- Nation selection screen (#24 — design issue open)
- Task completion output model (#21 — design gap open)
- `FInstancedStruct RolePayload` inside `UWorkerData` for role-specific data — do NOT convert UWorkerData itself
- Nationality passive bonuses, difficulty scaling, mission system, facility sharing, resource trading
- Player-named workers, personality traits, injury recovery, death consequences, multi-region hiring

---

## Debug Commands (UInvasionCheatManager)

- `GenerateWorkerPool [soldiers] [scientists] [engineers] [medics] [pilots]`
- `HireWorkersFromPool [count]`
- `AddCredits [amount]`
- `AddSupplies [amount]`

Server/listen host only by design.
