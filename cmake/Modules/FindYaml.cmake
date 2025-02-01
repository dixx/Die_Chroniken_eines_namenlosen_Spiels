set(YAML_DIR "${3RDPARTY_DIR}/yaml-cpp")
set(YAML_INCLUDE_DIRS "${YAML_DIR}/include")

set(YAML_LIBRARY "${YAML_DIR}/build/libyaml-cpp.a")

# to suppress warnings from libs:
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem\"${YAML_INCLUDE_DIRS}/\"")
