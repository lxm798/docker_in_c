file(GLOB SRCS "*.cc")
#set(SRCS SRC)

add_library(cgroup ${SRCS})
set_target_properties(cgroup PROPERTIES COMPILE_FLAGS "-std=c++0x")

install(TARGETS cgroup DESTINATION lib)
