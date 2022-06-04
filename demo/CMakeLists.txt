add_executable(oiseau_nodaldg nodaldg.cpp)
target_link_libraries(oiseau_nodaldg xtensor_stack blaze)

add_executable(oiseau_mesh mesh.cpp)
target_link_libraries(oiseau_mesh xtensor_stack blaze oiseau Boost::math)
