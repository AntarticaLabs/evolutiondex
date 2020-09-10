add_contract(evolutiondex evolutiondex ${CMAKE_CURRENT_SOURCE_DIR}/src/evolutiondex.cpp)
target_include_directories(evolutiondex PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(evolutiondex PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}")
target_compile_options( evolutiondex PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian -R${CMAKE_CURRENT_BINARY_DIR}/ricardian )