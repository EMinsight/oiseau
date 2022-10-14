add_executable(oiseau_nodaldg nodaldg.cpp)
target_link_libraries(oiseau_nodaldg PRIVATE oiseau)

add_executable(oiseau_mesh mesh.cpp)
target_link_libraries(oiseau_mesh PRIVATE oiseau)
