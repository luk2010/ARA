
file(GLOB ARA_CONTROLS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/ARA/Controls/*.cpp)
file(GLOB ARA_CONTROLS_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/ARA/Controls/*.h)

add_library(ARAControls SHARED 
    ${ARA_CONTROLS_HEADERS}
    ${ARA_CONTROLS_SOURCES})

set_property(
    TARGET ARAControls
    PROPERTY PUBLIC_HEADER ${ARA_CONTROLS_HEADERS})

target_include_directories(
    ARAControls
    PUBLIC 
        ${ARA_HEADERS_PREFIX}
        ${CMAKE_CURRENT_SOURCE_DIR}/../Text/src)

target_link_libraries(
    ARAControls
    PUBLIC ARACore ARAText)

install(
    TARGETS ARAControls
    LIBRARY DESTINATION ${ARA_INSTALL_PREFIX}
    PUBLIC_HEADER DESTINATION ${ARA_INSTALL_PREFIX}/ARA/Controls)