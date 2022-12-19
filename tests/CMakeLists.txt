add_executable(fennecs_tests)

file(GLOB_RECURSE FENNECS_TESTS_SOURCES *.cpp)

target_sources(fennecs_tests
        PRIVATE
            ${FENNECS_TESTS_SOURCES}
        )

target_link_libraries(fennecs_tests
        PUBLIC
            fennecs
        )
