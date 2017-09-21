### key map

There is a link between an _action_, an _input_, and it's _state_.

- _actions_ have a meaning
  - may be enums
- _inputs_ have a state
  - may not only be integers
  - must be stored in an appropriate way
- one _action_ can have multiple _inputs_, like keys, mouse actions...
- _actions_ could be the keys for the map

The key map must not be part of the engine, but part of a GameState.
