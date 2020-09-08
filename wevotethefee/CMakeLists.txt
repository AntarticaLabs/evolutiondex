add_contract(wevotethefee wevotethefee ${CMAKE_CURRENT_SOURCE_DIR}/src/wevotethefee.cpp)
target_include_directories(wevotethefee.wasm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(wevotethefee.wasm PUBLIC -R${CMAKE_CURRENT_SOURCE_DIR}/ricardian)