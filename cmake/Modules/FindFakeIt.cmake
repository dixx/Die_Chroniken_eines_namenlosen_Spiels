# TODO use https://github.com/philsquared/Catch/blob/master/docs/build-systems.md
include_directories("${3RDPARTY_DIR}/fakeit")

# to suppress warnings from libs:
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -isystem\"${3RDPARTY_DIR}/fakeit/\"")
