# Virtual-Routing

Application-layer routing program, using UDP

## Introduction

- self-organized routing
  - Select a virtual topo for members’ computers
  - Build virtual connection between computers according to the virtual topo;
  - Each computer acts as both client and router.
  - Each computer exchanges and updates routing table periodically.
  - A computer can send message to other computers

- centralized routing
  - Like the above self-organized routing
  - Controller determines and distributes routing policy (routing table) to each member

- can choose different topo(the 2 above) & different routing algorithms
  - LS
  - DV

## Coding Doc [Un-completed]

All PC Nodes will run as a `Node`. Before a `Node.Start()`, the `RouteAlgoType` and `ActionMode` MUST be specified. OR it will panic out and exit.

```cpp
Node n;
n.SetRouteAlgoType(RouteAlgoType::LS);
n.SetActionMode(ActionMode::NORMAL);
n.Start();
```

### Classes Hierarchy

- Args [Singleton] : store the args
- Node : Abstract of the Nodes in routing
- RouteAlgo : virtual base class for the Routing-Algorithm
  - RouteLS : Link-State Algorithm
  - RouteDV : Distance-Vector Algorithm

The `RouteLS` or `RouteDV` class will be initialized **automatically** inside a `Node` as soon as `SetRouteAlgoType()` is called. So DON'T init a `RouteAlgo` manually.