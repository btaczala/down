find_package(Threads REQUIRED)
add_executable(aria2_backend_tests aria2_backend_tests.cpp)
target_link_libraries(
  aria2_backend_tests PUBLIC catch2 downservercore aria-backend
                             ${CMAKE_THREAD_LIBS_INIT})


add_test(NAME aria2_backend_tests COMMAND aria2_backend_tests
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
