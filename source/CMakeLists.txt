add_library(fennecs)

file(GLOB_RECURSE FENNECS_INCLUDE *.hpp)
file(GLOB_RECURSE FENNECS_SOURCE *.cpp)

target_include_directories(fennecs
    PUBLIC
        .
    )

target_sources(fennecs
    PUBLIC
        ${FENNECS_INCLUDE}
    PRIVATE
        ${FENNECS_SOURCE}
    )