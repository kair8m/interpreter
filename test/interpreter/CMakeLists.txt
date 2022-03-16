file(GLOB SRCS *.cpp)

add_executable(interpreter_test ${SRCS})

add_test(NAME interpreter_test COMMAND interpreter_test)