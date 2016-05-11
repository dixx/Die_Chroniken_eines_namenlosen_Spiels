# Die Chroniken eines namenlosen Spiels

bladibladibla RPG yaddayadda Eigenbau blafasel.
Wir wollen all die falschen Entscheidungen selber treffen, all den schlechten Code selber schreiben, all die Bugs selber beheben, sprich: lernen.

#### Installation
Der Einfachheit halber benutzen wir Makefiles, und für deren Erstellung CMake.

**Irrlicht**, **IrrKlang** und **Lua** in den entsprechenden Versionen **und passend zum Betriebssystem (32Bit/64Bit)** holen (siehe `CMakeLists.txt`) und nach `./Debug/dependencies` entpacken. Dann einen Ordner `./_build` anlegen, in diesen wechseln, dort eine Konsole öffnen...

###### Windows:
...und `cmake -G "MinGW Makefiles" ..` eingeben. Das erstellt ein Makefile für genau dein System. Damit kannst du dann machen was du willst, z.B. ein Eclipse-Projekt erstellen oder einfach `make` ausführen.

###### Linux:
...und dann noch flink die gerade entpackten Bibliotheken compilen. (siehe **Troubleshooting**). Dann kannst du `cmake ..` eingeben, danach `make`.

###### OS-X:
- todo

#### Troubleshooting

##### Lua
`sudo make linux install`
- fatal error: readline/readline.h: No such file or directory --> `sudo apt-get install libreadline-dev`

##### Irrlicht
`sudo make linux install`
- fatal error: GL/gl.h: No such file or directory --> ```
sudo apt-get install apt-file
apt-file update
apt-file search "GL/gl.h"
```
Nun suche das am besten passende Package raus und installiere es.
- fatal error: X11/extensions/xf86vmode.h: No such file or directory --> `sudo apt-get install libxxf86vm-dev`
#### CREDITS
A thousand thanks to:
- the *Irrlicht 3D Engine* creators and maintainers, as well as to the great community!
- the *irrKlang Sound Library* creators and maintainers
- Dimitri van Heesch for *Doxygen*
- Mastiff Odit for his *MastEventReceiver*, giving me a great start with EventReceivers
- the wonderful community around *stackoverflow.com* for many many many hints
- the awesome people behind and around *GitHub*
- and all the others silently involved.
