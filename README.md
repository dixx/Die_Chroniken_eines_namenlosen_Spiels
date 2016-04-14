# Die Chroniken eines namenlosen Spiels

bladibladibla RPG yaddayadda Eigenbau blafasel.
Wir wollen all die falschen Entscheidungen selber treffen, all den schlechten Code selber schreiben, all die Bugs selber beheben, sprich: lernen.

#### Installation
Der Einfachheit halber benutzen wir Makefiles, und für deren Erstellung CMake.

###### Windows:
**Irrlicht**, **IrrKlang** und **Lua** in den entsprechenden Versionen holen (siehe `CMakeLists.txt`) und nach `./Debug/dependencies` entpacken.
Einen Ordner `./_build` anlegen, in diesen wechseln, dort eine Konsole öffnen und `cmake -G "MinGW Makefiles" ..` eingeben. Das erstellt ein Makefile für genau dein System. Damit kannst du dann machen was du willst, z.B. ein Eclipse-Projekt erstellen oder einfach `make` ausführen.

#### CREDITS
A thousand thanks to:
- the *Irrlicht 3D Engine* creators and maintainers, as well as to the great community!
- the *irrKlang Sound Library* creators and maintainers
- Dimitri van Heesch for *Doxygen*
- Mastiff Odit for his *MastEventReceiver*, giving me a great start with EventReceivers
- the wonderful community around *stackoverflow.com* for many many many hints
- the awesome people behind and around *GitHub*
- and all the others silently involved.
