file(GLOB_RECURSE srcs src/*.cpp include/*.h)

add_library(task STATIC ${srcs})

target_include_directories(task PUBLIC include)