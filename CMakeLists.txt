
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Toolchain do VCPKG")
endif()

cmake_minimum_required(VERSION 3.10)
project(meu_crow_app)

set(CMAKE_CXX_STANDARD 17)


find_package(Crow CONFIG REQUIRED)
find_package(Boost CONFIG REQUIRED COMPONENTS system filesystem asio)

add_executable(meu_crow_app main.cpp)

target_link_libraries(meu_crow_app PRIVATE Crow::Crow Boost::system Boost::filesystem Boost::asio)
