---------------------------------------------------------
--
-- SPLIT-Funktion
--
---------------------------------------------------------
function split( pString, pPattern )
    local Table     = {} -- NOTE: use {n = 0} in Lua-5.0
    local fpat      = "(.-)" .. pPattern
    local last_end  = 1
    local s, e, cap = pString:find( fpat, 1 )
    while s do
        if s ~= 1 or cap ~= "" then
            table.insert( Table, cap )
        end
        last_end  = e + 1
        s, e, cap = pString:find( fpat, last_end )
    end
    if last_end <= #pString then
        cap = pString:sub( last_end )
        table.insert( Table, cap )
    end
    return Table
end
 

---------------------------------------------------------
--
-- Zaehle die Vorkommen von s2 in s1
--
---------------------------------------------------------
function countSubstring( s1, s2 )
    local magic =  "[%^%$%(%)%%%.%[%]%*%+%-%?]"
    local percent = function(s)return "%"..s end
    return select( 2, s1:gsub( s2:gsub(magic,percent), "" ) )
end


---------------------------------------------------------
--
-- Gibt TRUE zurueck, wenn der uebergebene String nur ein
-- Kommentar ist.
-- Inline-Kommentare werden nicht beachtet!
--
---------------------------------------------------------
function isComment( zeile )
    if string.find( zeile, "^[%s]*//[.]*" ) 
    or string.find( zeile, "^[%s]*%-%-[.]*" )
    or string.find( zeile, "^[%s]*#[.]*" ) then
        return true
    end
end


---------------------------------------------------------
--
-- Entfernt @ und #.
--
---------------------------------------------------------
function removeInvalidChars( str )
   return string.gsub( string.gsub( str, "@", "" ), "#", "" )
end

