# TODO find existing LUA

set(LUA_DIR ${CMAKE_SOURCE_DIR}/dependencies/lua-5.3.2)
set(LUA_INCLUDE_DIRS ${LUA_DIR}/include)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
  set(LUA_LIBRARY ${LUA_DIR}/liblua53.a) # the one >200kB! If not exist, build it.
  set(LUA_BINARY_LIBRARY ${LUA_DIR}/bin/lua53.dll)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  set(LUA_INCLUDE_DIRS /usr/local/include)
  set(LUA_LIBRARY lua dl)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

#if(APPLE)
#endif(APPLE)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNULL=0") # sadly this is required by LUA
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLUA_C89_NUMBERS") # I totally have NO CLUE. "luaconf.h:551:27: error: ISO C++ 1998 does not support 'long long' [-Werror=long-long]"
