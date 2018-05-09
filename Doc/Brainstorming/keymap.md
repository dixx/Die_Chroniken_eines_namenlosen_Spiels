### key map

There is a link between an _action_, an _input_, and it's _state_.

- _actions_ have a meaning
  - may be enums
- _inputs_ have a state
  - may not only be integers
  - must be stored in an appropriate way
- one _action_ can have multiple _inputs_, like keys, mouse actions...
- _actions_ could be the keys for the map

- the _action_ map
  - must have a unchangeable section for menu _actions_ and the like
  - should have a customizable section that holds _actions_ necessary for gameplay
    - this section must not be part of the engine, but part of a GameState.


-> 
