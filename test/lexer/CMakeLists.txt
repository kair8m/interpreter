file(
        GLOB SRCS
        ${PROJECT_SOURCE_DIR}/src/lexer/*.cpp
        ${PROJECT_SOURCE_DIR}/test/lexer/*.cpp
)

add_executable(lexer_test ${SRCS})

include_directories(${PROJECT_SOURCE_DIR}/include/lexer)

target_link_libraries(lexer_test libgtest)

add_test(NAME lexer_test COMMAND lexer_test)