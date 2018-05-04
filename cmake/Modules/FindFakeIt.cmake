add_library(fakeit INTERFACE)
target_include_directories(fakeit INTERFACE "${3RDPARTY_DIR}/fakeit")

# to suppress warnings from libs:
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem\"${3RDPARTY_DIR}/fakeit/\"")
