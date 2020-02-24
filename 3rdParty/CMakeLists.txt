add_subdirectory(rpclib)
set(JSON_BuildTests OFF CACHE BOOL "")
set(JSON_Install OFF CACHE BOOL "")
add_subdirectory(json)

add_subdirectory(catch)
add_subdirectory(spdlog)
