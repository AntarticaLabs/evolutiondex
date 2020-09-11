add_contract(badtoken badtoken ${CMAKE_CURRENT_SOURCE_DIR}/src/badtoken.cpp)
target_include_directories(badtoken PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(badtoken PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
target_compile_options( badtoken PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )