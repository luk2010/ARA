cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(ARA_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(ARA_HEADERS_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/Core/src)

set(ARA_MODULES_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/Modules/Controls/src
                       ${CMAKE_CURRENT_SOURCE_DIR}/Modules/Text/src)

project(ARA-SDK
    VERSION 0.0.1
    DESCRIPTION "Another Rendering Abstraction"
    HOMEPAGE_URL "https://github.com/luk2010/ARA") 

add_subdirectory(Core)

include_directories(${ARA_HEADERS_PREFIX} ${ARA_MODULES_PREFIX})
link_libraries(ARACore)

add_subdirectory(Modules)
add_subdirectory(Plugins)

add_subdirectory(Examples)
