add_compile_options("$<$<CONFIG:RELEASE>:/O2>")

project(interview_task LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(backend)
add_subdirectory(loguru)
add_subdirectory(gui)
