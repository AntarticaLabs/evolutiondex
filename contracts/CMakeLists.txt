cmake_minimum_required( VERSION 3.5 )

project(contracts)

set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_subdirectory(badtoken)
add_subdirectory(evolutiondex)
add_subdirectory(wevotethefee)