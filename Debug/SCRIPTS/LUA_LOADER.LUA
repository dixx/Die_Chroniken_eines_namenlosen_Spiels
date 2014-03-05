require "LUA_SUBS"


---------------------------------------------------------
--
-- Funktion zum Auslesen einer beliebigen Objekte-Datei
-- nach dem Schema
--
--  [START_OBJECT]
--  SCHLUESSELWORT = wert
--  SCHLUESSELWORT = wert
--  ...
--  [ENDE_OBJEKT]
--
--  [START_OBJECT]
--  ...
--
--  Folgende Zeichen duerfen nicht zwischen "" enthalten 
--  sein:   '#'  '@'
--  Diese Zeichen werden automatisch entfernt.
--  Inline-Kommentare werden nicht unterstuetzt!
--
---------------------------------------------------------
function getObjectDataFromScript( filename )
    local alles       = {} -- NOTE: use {n = 0} in Lua-5.0
    local objectFound = 0
    local object      = ""
    local value       = ""

    local file    = io.open( filename, "r" )
    local content = file:read( "*a" )
    file:close()

    for i, zeile in pairs(split(content, "\n" )) do
        if isComment( zeile ) then
            --io.write( "[parser]: kommentar gefunden: <"..zeile..">\n" )
        else
            if string.find( zeile, "^%s*%[ENDE_OBJECT%]" ) then
                objectFound = 0
                table.insert( alles, "ENDE_OBJECT" )
            elseif string.find( zeile, "^%s*%[START_OBJECT%]" ) then
                objectFound = 1
                table.insert( alles, "START_OBJECT" )
            elseif objectFound == 1 and string.find( zeile, "=" ) and countSubstring( zeile, '"' ) > 1 then
                local valueConcat = ""
                for k,v in ipairs( split( zeile, "=" ) ) do
                    if k == 1 then 
                        object = string.match( v, "([%w_]*[^%s])" )
                    elseif k == 2 then
                        valueConcat = valueConcat..v
                    else
                        valueConcat = valueConcat.."="..v
                    end
                end
                value = string.match( valueConcat, "^[%s]*\"(.*)\"[%s]*" )
                if countSubstring( zeile, '"' ) > 1 then
                    value = removeInvalidChars( value )
                    table.insert( alles, object )
                    table.insert( alles, value )
                end
            end
        end
    end
    return alles
end


---------------------------------------------------------
--
-- Funktion zum Auslesen einer Datei, welche die Pfade
-- und Dateinamen weiterer Scriptdateien enthaelt, nach
-- dem Schema
--
--  <pfad>/<dateiname>.script
--  <pfad>/<dateiname>.script
--  ...
--
---------------------------------------------------------
function getScriptFiles( filename )
    local alles   = {} -- NOTE: use {n = 0} in Lua-5.0
    local file    = io.open( filename, "r" )
    local content = file:read( "*a" )
    file:close()
    for i, zeile in pairs(split(content, "\n" )) do
        if isComment( zeile ) then
            --io.write( "[parser]: kommentar gefunden: "..zeile.."\n" )
        else
            table.insert( alles, zeile )
        end
    end
    return alles
end

