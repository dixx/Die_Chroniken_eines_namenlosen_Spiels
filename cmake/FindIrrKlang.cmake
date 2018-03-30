set(IRRKLANG_DIR "${CMAKE_SOURCE_DIR}/dependencies/irrKlang-1.6.0")
set(IRRKLANG_INCLUDE_DIRS "${IRRKLANG_DIR}/include")

if(${CMAKE_SYSTEM_NAME} MATCHES Windows)
  set(IRRKLANG_LIBRARY "${IRRKLANG_DIR}/lib/Win32-gcc/libirrKlang.a")
  set(IRRKLANG_BINARY_LIBRARY "${IRRKLANG_DIR}/bin/Win32-gcc/irrKlang.dll")
endif(${CMAKE_SYSTEM_NAME} MATCHES Windows)

if(${CMAKE_SYSTEM_NAME} MATCHES Linux)
  set(IRRKLANG_LIBRARY "${IRRKLANG_DIR}/bin/linux-gcc-64/libIrrKlang.so")
endif(${CMAKE_SYSTEM_NAME} MATCHES Linux)

#if(APPLE)
#endif(APPLE)

# to suppress warnings from libs:
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem\"${IRRKLANG_INCLUDE_DIRS}/\"")
