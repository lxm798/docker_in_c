file(GLOB SRCS "*.cc")
#set(SRCS SRC)

add_library(ns ${SRCS})
set_target_properties(ns PROPERTIES COMPILE_FLAGS "-std=c++0x")

install(TARGETS ns DESTINATION lib)
