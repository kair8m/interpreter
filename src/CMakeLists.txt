include_directories(
        ${PROJECT_SOURCE_DIR}/include/interpreter
        ${PROJECT_SOURCE_DIR}/include/lexer
        ${PROJECT_SOURCE_DIR}/include/parser
)

add_executable(
        interpreter
        ${PROJECT_SOURCE_DIR}/src/main.cpp
        ${PROJECT_SOURCE_DIR}/src/interpreter/interpreter.cpp
        ${PROJECT_SOURCE_DIR}/src/lexer/lexer.cpp
        ${PROJECT_SOURCE_DIR}/src/parser/parser.cpp
        )