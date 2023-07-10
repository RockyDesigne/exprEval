project(eval)
cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 17)
find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS} include)
add_definitions(${LLVM_DEFINITIONS})
set(SOURCES
        src/main.cpp
        src/ASTNodes.cpp
        src/lexer.cpp
        src/parser.cpp
)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
llvm_map_components_to_libnames(llvm_libs support core irreader bitwriter passes transformutils native linker bitreader executionengine interpreter mcjit)
target_link_libraries(${PROJECT_NAME} ${llvm_libs})
