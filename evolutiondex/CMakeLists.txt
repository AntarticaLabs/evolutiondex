add_contract(evolutiondex evolutiondex ${CMAKE_CURRENT_SOURCE_DIR}/src/evolutiondex.cpp)
target_include_directories(evolutiondex.wasm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(evolutiondex.wasm PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian)