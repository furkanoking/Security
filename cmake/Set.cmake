target_include_directories(SecurityLib PUBLIC ${CMAKE_SOURCE_DIR}/include)


file(GLOB_RECURSE sources ${CMAKE_SOURCE_DIR}/src/*.cpp
                          ${CMAKE_SOURCE_DIR}/src/*.cxx
                          ${CMAKE_SOURCE_DIR}/src/*.c)

set(lib_sources ${sources})


file(GLOB_RECURSE headers ${CMAKE_SOURCE_DIR}/include/*.h
                          ${CMAKE_SOURCE_DIR}/include/*.hpp)

set(lib_headers ${headers})

set_target_properties(SecurityLib PROPERTIES
PUBLIC_HEADER      ${lib_headers})