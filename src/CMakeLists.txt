set(CXX_FLAGS
 -g
 # -DVALGRIND
 # -DMUDUO_STD_STRING
 -DCHECK_PTHREAD_RETURN_VALUE
 -D_FILE_OFFSET_BITS=64
 -Wall
 -Wextra
 -Werror
 # -Wconversion
 -Wno-unused-parameter
 #-Wold-style-cast
 -Woverloaded-virtual
 -Wpointer-arith
 #-Wshadow
 -Wwrite-strings
 -march=native
 # -MMD
 # -std=c++0x
 -rdynamic
 )


include_directories(${PROJECT_BINARY_DIR})
file(GLOB SRCS "*.cc")
add_executable(exe ${SRCS})
target_link_libraries(exe ns cgroup gflags cap)
set_target_properties(exe PROPERTIES COMPILE_FLAGS "-std=c++11")



