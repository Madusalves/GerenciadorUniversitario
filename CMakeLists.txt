cmake_minimum_required(VERSION 3.10)
project(meu_crow_app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")


find_package(Crow CONFIG REQUIRED)

add_executable(meu_crow_app main.cpp)
target_link_libraries(meu_crow_app PRIVATE Crow::Crow)


target_link_libraries(meu_crow_app PRIVATE Boost::system Boost::filesystem)
