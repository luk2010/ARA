
file(
    GLOB DEVICEMTL_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.mm)

find_library(
    DEVICEMTL_LIB_METAL 
    Metal 
    REQUIRED) 

add_library(
    DeviceMTL 
    SHARED 
    ${DEVICEMTL_SOURCES})

target_link_libraries(
    DeviceMTL 
    PUBLIC 
        ${DEVICEMTL_LIB_METAL}
        ARACore 
        ARAHri)

if(XCODE)
    set_target_properties(
        DeviceMTL
        PROPERTIES 
        XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES
        XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC_EXCEPTIONS YES)
endif()

install(
    TARGETS DeviceMTL
    LIBRARY DESTINATION ${ARA_INSTALL_PREFIX})
