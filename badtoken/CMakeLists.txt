add_contract(badtoken badtoken ${CMAKE_CURRENT_SOURCE_DIR}/src/badtoken.cpp)
target_include_directories(badtoken.wasm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(badtoken.wasm PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian)