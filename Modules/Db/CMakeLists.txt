file(GLOB ARA_DB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/ARA/Db/*.cpp)
file(GLOB ARA_DB_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/ARA/Db/*.h)

add_library(ARADb SHARED 
    ${ARA_DB_HEADERS}
    ${ARA_DB_SOURCES})

set_property(
    TARGET ARADb
    PROPERTY PUBLIC_HEADER ${ARA_DB_HEADERS})

target_include_directories(
    ARADb
    PUBLIC 
        ${ARA_HEADERS_PREFIX}
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(
    ARADb
    PUBLIC ARACore)

install(
    TARGETS ARADb
    LIBRARY DESTINATION ${ARA_INSTALL_PREFIX}
    PUBLIC_HEADER DESTINATION ${ARA_INSTALL_PREFIX}/ARA/Db)