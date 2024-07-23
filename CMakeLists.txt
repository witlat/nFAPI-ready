project (pnf_ready)

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -std=c99")

add_executable(PNF PNF.cpp PNF.hpp)