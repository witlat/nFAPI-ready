cmake_minimum_required ( VERSION 2.8 )

project (sctp_sandbox)

set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -std=c99")

add_executable(PNF PNF.cpp common.h)