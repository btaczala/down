find_package(Threads REQUIRED)
find_package(Aria2)

add_library(downservercore
    downserver.cpp)
target_include_directories(downservercore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(downservercore PUBLIC spdlog)

add_executable(down-server main.cpp)
target_link_libraries(down-server PUBLIC rpc  ${CMAKE_THREAD_LIBS_INIT} nlohmann_json downservercore)

if(ARIA2_FOUND)
    add_subdirectory(backends/aria2)
    target_link_libraries(down-server PUBLIC aria-backend)
endif()
