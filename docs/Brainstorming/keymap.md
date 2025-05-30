### key map

There is a link between an _action_, an _input_, and its _state_.

# the action
- _actions_ have a meaning
  - may be enums
  - could be the keys for the mappings
  - must have the type of input
- _inputs_ have a state
  - may not only be integers
  - must be stored in an appropriate way
- one _action_ can have multiple _inputs_, like keys, mouse actions...
- action must have a default for at least one input
- may hold a name to display for the user
- action:
  - id: enum (WALKING, ATTACKING_PRIMARY, TALKING, ...)
  - name: string
  - state: enum (active, inactive, started, stopped)
  - input1:
    - name: string
    - type: enum (Keyboard, Mouse, ...)
    - id: enum (LMB, KEY_X, Joystick_moved_right, ...)
  - input2:
    - name: string
    - type: enum (Keyboard, Mouse, ...)
    - id: enum (LMB, KEY_X, Joystick_moved_right, ...)
- possible actions in-game:
  - attack_primary, use, talk, pick_up, move_to, run, ...
- possible actions in menu:
  - toggle, choose, go_back, highlight/hover/mark?, ...


# the action map
- must have a unchangeable section for menu actions and the like
  - values may be hard-coded
- should have a customizable section that holds actions necessary for gameplay
  - this section must not be part of the engine, but part of a GameState.
- should be able to handle every kind of input
- should somehow "collect" available actions from the game states


# flow
1. input goes from OS to Irrlicht device
2. available as keyboard- and mouse events
3. is consumed by Leviathan eventreceiver
4. eventreceiver pushes inputs to action mappings
5. game state polls several action states


# access

`leviathan.Actions().started(TALKING)`
`leviathan.Actions().is(ATTACKING_PRIMARY)`
`leviathan.Actions().stopped(RUNNING)`
~~`leviathan.Actions().isNot(ATTACKING_PRIMARY)`~~
