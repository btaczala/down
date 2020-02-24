add_library(aria2 INTERFACE)
target_include_directories(aria2 INTERFACE ${ARIA2_INCLUDE_DIRS})
target_link_libraries(aria2 INTERFACE ${ARIA2_LIBRARIES})

add_library(aria-backend STATIC aria2fetcher.cpp)
target_link_libraries(aria-backend PUBLIC aria2 spdlog)
target_compile_definitions(aria-backend PUBLIC BACKEND=ARIA2)
target_include_directories(aria-backend PUBLIC ${CMAKE_SOURCE_DIR}/src/server ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(tests)
