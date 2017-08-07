# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -c") # compile, but no linking
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
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
  -std=c++14 \
  -fmessage-length=80 \
  -fdiagnostics-color=always \
  -fdiagnostics-show-location=once \
")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG_MODE=1") # a switch for additional debug stuff in the code
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
