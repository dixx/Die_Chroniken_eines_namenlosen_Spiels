set(IRRLICHT_DIR "${CMAKE_SOURCE_DIR}/dependencies/irrlicht-1.8.4")
set(IRRLICHT_INCLUDE_DIR "${IRRLICHT_DIR}/include")
set(IRRLICHT_SOURCES_DIR "${IRRLICHT_DIR}/source/Irrlicht") # this is a workaround for an Irrlicht issue with ShadowVolumeSceneNodes
set(IRRLICHT_INCLUDE_DIRS ${IRRLICHT_INCLUDE_DIR} ${IRRLICHT_SOURCES_DIR})

if(${CMAKE_SYSTEM_NAME} MATCHES Windows)
  set(IRRLICHT_LIBRARY "${IRRLICHT_DIR}/lib/Win32-gcc/libIrrlicht.a")
  set(IRRLICHT_BINARY_LIBRARY "${IRRLICHT_DIR}/bin/Win32-gcc/Irrlicht.dll")
endif(${CMAKE_SYSTEM_NAME} MATCHES Windows)

if(${CMAKE_SYSTEM_NAME} MATCHES Linux)
  set(IRRLICHT_LIBRARY "${IRRLICHT_DIR}/lib/Linux/libIrrlicht.a" GL Xxf86vm X11)
endif(${CMAKE_SYSTEM_NAME} MATCHES Linux)

#if(APPLE)
#endif(APPLE)

# to suppress warnings from libs:
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem\"${IRRLICHT_INCLUDE_DIR}/\" -isystem\"${IRRLICHT_SOURCES_DIR}/\"")
