add_executable(fennecs_tests)

file(GLOB_RECURSE FENNECS_TESTS_INCLUDE *.hpp)
file(GLOB_RECURSE FENNECS_TESTS_SOURCE *.cpp)

target_include_directories(fennecs_tests
    PUBLIC
        .
)

target_sources(fennecs_tests
    PUBLIC
        ${FENNECS_TESTS_INCLUDE}
    PRIVATE
        ${FENNECS_TESTS_SOURCE}
    )

target_link_libraries(fennecs_tests
    PUBLIC
        fennecs
    )