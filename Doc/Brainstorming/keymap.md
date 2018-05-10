### key map

There is a link between an _action_, an _input_, and it's _state_.

# the action
- _actions_ have a meaning
  - may be enums
  - could be the keys for the mappings
- _inputs_ have a state
  - may not only be integers
  - must be stored in an appropriate way
- one _action_ can have multiple _inputs_, like keys, mouse actions...
- action must have a default for at least one input
- may hold a name to display for the user


# the action map
- must have a unchangeable section for menu actions and the like
- should have a customizable section that holds actions necessary for gameplay
  * this section must not be part of the engine, but part of a GameState.
- should be able to handle every kind of input
- should somehow "collect" available actions from the game states


# access

`leviathan.Actions().started(TALKING)`
`leviathan.Actions().is(ATTACKING_PRIMARY)`
`leviathan.Actions().stopped(RUNNING)`
`leviathan.Actions().isNot(ATTACKING_PRIMARY)`
