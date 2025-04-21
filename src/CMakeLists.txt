aux_source_directory(. SRC)
include_directories(.)
add_executable(zkpot ${SRC})

target_link_libraries(zkpot mcl mclbn384_256 gmp XKCP)
