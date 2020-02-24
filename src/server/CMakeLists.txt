find_package(Threads REQUIRED)

add_executable(down-server main.cpp
    downserver.cpp
    )

target_link_libraries(down-server rpc  ${CMAKE_THREAD_LIBS_INIT} nlohmann_json)
