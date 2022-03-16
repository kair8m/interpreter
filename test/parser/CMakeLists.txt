file(GLOB SRCS *.cpp)

add_executable(parser_test ${SRCS})

add_test(NAME parser_test COMMAND parser_test)