cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(ARA_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(ARA_HEADERS_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/Core/src)

project(ARA-SDK
    VERSION 0.0.1
    DESCRIPTION "Another Rendering Abstraction"
    HOMEPAGE_URL "https://github.com/luk2010/ARA") 

add_subdirectory(Core)
add_subdirectory(Modules)
add_subdirectory(Plugins)
add_subdirectory(Examples)
