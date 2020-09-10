add_contract(wevotethefee wevotethefee ${CMAKE_CURRENT_SOURCE_DIR}/src/wevotethefee.cpp)
target_include_directories(wevotethefee PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(wevotethefee PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
target_compile_options( wevotethefee PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )