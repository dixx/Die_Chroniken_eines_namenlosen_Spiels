# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -c") # compile, but no linking
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32") # irrKlang 64bit is only available for VisualStudio
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything") # applies only to clang compiler
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
  -Weffc++ \
  -Wall \
  -Wextra \
  -Wpedantic \
  -Wunused \
  -Werror \
  -Wshadow \
  -Winline \
  -Wuninitialized \
  -Wfloat-equal \
  -Wconversion \
  -Wsign-conversion \
  -Wcast-align \
  -Wno-aggregate-return \
  -Woverloaded-virtual \
  -Wold-style-cast \
  -Wnon-virtual-dtor \
  -Wdelete-non-virtual-dtor \
  -Wfatal-errors \
  -std=c++17 \
  -fmessage-length=160 \
  -fdiagnostics-color=always \
  -fdiagnostics-show-location=once \
  -fdiagnostics-generate-patch \
")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb") # use GDB for debugging
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG_MODE=1") # a switch for additional debug stuff in the old code
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=lld") # use another linker (faster Catch linking)
