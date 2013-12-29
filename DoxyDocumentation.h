/*! \file "DoxyDocumentation.h"
  \brief Dokumentation für das Spiel
*/

/*! \mainpage Die Chroniken eines namenlosen Spiels

Dieses Manual betrifft das Spiel selbst, die Codebasis und verwendete Werkzeuge.

Dementsprechend die Aufteilung:
- \subpage game
- \subpage code
- \subpage tools
*/

//-----------------------------------------------------------

/*! \page game Das Spiel
*/

//-----------------------------------------------------------

/*! \page code Die Codebasis

Das Spiel selbst ist in C++ geschrieben, die Scripte in LUA.
Die Konfiguration ist in einem eigenen INI-Dialekt verfasst.
Dem C++-Code liegen bestimmte \subpage code_conventions zu Grunde.

Für das Spiel werden folgende Externa verwendet:
- <a href="http://irrlicht.sourceforge.net/">Irrlicht</a>
- <a href="http://www.ambiera.com/irrklang/">irrKlang</a>
- <a href="http://www.lua.org/">Lua</a>
- <a href="http://www.mingw.org/">MinGW</a> GCC Header

Auf Verwendung der STD-Lib wurde verzichtet, da Irrlicht so gut wie alle
Container selbst mitbringt. Und um die Kompatibilität zu verschiedenen OSs zu
gewährleisten. Und weil ich die STD-Lib nicht mag.
*/

//-----------------------------------------------------------

/*! \page code_conventions Coding Conventions

Für die Codeformatierung gelten die Regeln, die direkt im Code abgeschaut werden
können. Für die Architektur gelten weitere Regeln:

- Variablen Initialisieren direkt nach der Deklaration
- lokale Variablen im kleinstmöglichen Scope erstellen, außer für Loops:
  hier muss die Variable direkt vor dem Loop erstellt werden.
- Nutze ++myVar in Loops, nutze myVar++ wenn myVar der Rückgabewert einer
  Funktion ist
- Nutze ClassA += ClassB wenn der Constructor von ClassA oder ClassB sehr
  "teuer" ist
- Versuche, keine lokalen Variablen zu erstellen, wenn diese direkt danach
  von der Funktion zurückgegeben werden
- Nutze Initialisierungslisten für Klassen, vermeide Member-Assignment wo es
  geht
- Für nicht-Integrale Datentypen, versuche Referenzen statt Zeigern zu nutzen
- Für Konstruktoren mit nur einem Parameter, benutze Schlüsselwort "explicit";
  außer es ist ein Copy-Constructor
- "const-ness" (nicht übertreiben damit ;)
  - const type method() --> Rückgabewert der Funktion kann nicht verändert werden
  - type* const method() --> Zeiger auf Rückgabewert kann nicht verändert werden
  - type method(const type& param) --> Parameterwert kann nicht verändert werden
  - type method() const --> Funktion wird keine Membervariablen verändern und
    wird keine Funktionen aufrufen, die ihrerseits Membervariablen verändern
*/

//-----------------------------------------------------------

/*! \page tools Verwendete Werkzeuge

- <a href="http://www.eclipse.org/">Eclipse</a>
- <a href="http://git-scm.com/">Git</a>
- <a href="www.doxygen.org/‎">DoxyGen</a>
- <a href="www.blender.org/‎">Blender</a>
*/
