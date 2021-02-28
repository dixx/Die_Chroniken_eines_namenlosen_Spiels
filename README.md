[![BCH compliance](https://bettercodehub.com/edge/badge/dixx/Die_Chroniken_eines_namenlosen_Spiels?branch=master)](https://bettercodehub.com/)
[![CodeFactor](https://www.codefactor.io/repository/github/dixx/die_chroniken_eines_namenlosen_spiels/badge)](https://www.codefactor.io/repository/github/dixx/die_chroniken_eines_namenlosen_spiels)

# Die Chroniken eines namenlosen Spiels

bladibladibla RPG yaddayadda Eigenbau blafasel.
Wir wollen all die falschen Entscheidungen selber treffen, all den schlechten Code selber schreiben, all die Bugs selber beheben, sprich: lernen.

#### Installation
Der Einfachheit halber benutzen wir Makefiles, und für deren Erstellung CMake.

[**Irrlicht**](https://sourceforge.net/projects/irrlicht/files/), [**IrrKlang**](http://www.ambiera.com/irrklang/downloads.html) und [**Lua**](https://sourceforge.net/projects/luabinaries/files/) in den entsprechenden Versionen **und passend zum Betriebssystem (32Bit/64Bit)** holen (siehe `CMakeLists.txt`) und nach `./external` entpacken. Dann einen Ordner `./_build` anlegen, in diesen wechseln, dort eine Konsole öffnen...

###### Windows:
...und `cmake -G "MinGW Makefiles" ..` eingeben. Das erstellt ein Makefile für genau dein System. Damit kannst du dann machen was du willst, z.B. ein Eclipse-Projekt erstellen oder einfach `make` ausführen.
Hinweis: Wir nutzen gern Ninja anstelle von Make.

###### Linux:
...und dann noch flink die gerade entpackten Bibliotheken compilen. (siehe **Troubleshooting**). Dann kannst du `cmake ..` eingeben, danach `make`.

###### OS-X:
- todo

#### Tests
Die *Leviathan Game Engine* wird komplett testgetrieben entwickelt. Die Unit-Tests werden mit den Frameworks [**Catch2**](https://github.com/catchorg/Catch2) und [**FakeIt**](https://github.com/eranpeer/FakeIt) erstellt.
Beim Builden wird auch ein Binary `unit_tests` angelegt, welches die Tests in der Konsole abfährt.

#### Code Style
Für einheitlichen Code nutzen wir **clang-formatter**, die Regeln sind in `.clang-format` festgelegt.

#### Troubleshooting

##### Lua
Windows: `make generic`
Linux: `sudo make linux install`
- fatal error: readline/readline.h: No such file or directory --> `sudo apt-get install libreadline-dev`

##### Irrlicht
`sudo make linux install`
- fatal error: GL/gl.h: No such file or directory -->
```
  sudo apt-get install apt-file
  apt-file update
  apt-file search "GL/gl.h"
```
Nun suche das am besten passende Package raus und installiere es.
- fatal error: X11/extensions/xf86vmode.h: No such file or directory --> `sudo apt-get install libxxf86vm-dev`

#### CREDITS
A thousand thanks to:
- the *Irrlicht 3D Engine* creators and maintainers, as well as to the great community!
  - According to the prophecy, I hereby acknowledge that, by using Irrlicht, I’ve used the IJG code, the zlib and libpng.
- the *irrKlang Sound Library* creators and maintainers
- the *LUA* people
- Dimitri van Heesch for *Doxygen*
- Mastiff Odit for his *MastEventReceiver*, giving me a great start with EventReceivers
- Phil Nash for the nice and easy unit test framework *Catch*
- Eran Pe'er for his marvellous mocking framework *FakeIt*
- the wonderful community around *stackoverflow.com* for many many many hints
- the awesome people behind and around *GitHub*
- all GNUs and Ninjas
- and all the others silently involved.
