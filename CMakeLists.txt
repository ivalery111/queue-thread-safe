cmake_minimum_required(VERSION 3.15)

project(queue C)

set(C_STANDARD 11)

include(cmake/CompilerWarnings.cmake)
add_library(project_warnings INTERFACE)
set_project_warnings(project_warnings)

include(cmake/EnableTests.cmake)
include(cmake/BuildType.cmake)

include(cmake/Sanitizers.cmake)
add_library(sanitizers INTERFACE)
set_sanitizers(sanitizers)

add_library(queue)
add_library(utils::queue ALIAS queue)

target_sources(queue
    PUBLIC
            src/queue/_enqueue.c
            src/queue/enqueue.c
            src/queue/_dequeue.c
            src/queue/dequeue.c
)

target_include_directories(queue
    PUBLIC ${CMAKE_SOURCE_DIR}/include
           ${CMAKE_SOURCE_DIR}/src/internal
)

find_package(Threads REQUIRED)

target_link_libraries(queue
    PRIVATE project_warnings sanitizers Threads::Threads
)
