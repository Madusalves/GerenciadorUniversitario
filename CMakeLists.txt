set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
cmake_minimum_required(VERSION 3.10)
project(meu_crow_app)

set(CMAKE_CXX_STANDARD 17)


set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}/debug;${CMAKE_SOURCE_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}/release;${CMAKE_SOURCE_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}/share/crow;${CMAKE_PREFIX_PATH}")

find_package(Crow CONFIG REQUIRED)
find_package(Boost CONFIG REQUIRED COMPONENTS system filesystem asio)
add_executable(meu_crow_app main.cpp)
target_include_directories(meu_crow_app PRIVATE "${CMAKE_SOURCE_DIR}/vcpkg_installed/${VCPKG_TARGET_TRIPLET}/include")

target_link_libraries(meu_crow_app PRIVATE Crow::Crow Boost::system Boost::filesystem Boost::asio)