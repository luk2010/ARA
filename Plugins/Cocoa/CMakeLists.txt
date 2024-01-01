
option(MODULE_OSX_WITH_METAL "ARA.Cocoa.WithMetal: compiles with Metal and provide a RenderView for the Metal API." OFF)
option(MODULE_OSX_WITH_OPENGL "ARA.Cocoa.WithOpenGL: compiles with OpenGL supports." OFF)

file(GLOB ARA_COCOA_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/ARA/Cocoa/*.mm)
file(GLOB ARA_COCOA_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/ARA/Cocoa/*.h)

find_library(ARA_COCOA_LIB Cocoa REQUIRED)
find_library(ARA_COREFOUNDATION_LIB CoreFoundation REQUIRED)
find_library(ARA_CORETEXT_LIB CoreText REQUIRED)

add_library(ARACocoa SHARED 
    ${ARA_COCOA_HEADERS}
    ${ARA_COCOA_SOURCES})

target_include_directories(
    ARACocoa
    PUBLIC ${ARA_HEADERS_PREFIX})

target_link_libraries(
    ARACocoa
    PUBLIC 
        ARACore
        ${ARA_COCOA_LIB} 
        ${ARA_COREFOUNDATION_LIB} 
        ${ARA_CORETEXT_LIB})

if(MODULE_OSX_WITH_METAL)

    file(GLOB ARA_OSX_METAL_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/ARA/Cocoa/Metal/*.h)
    file(GLOB ARA_OSX_METAL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/ARA/Cocoa/Metal/*.mm)
    find_library(QuartzCore QuartzCore REQUIRED)
    find_library(Metal Metal REQUIRED)
    
    target_sources(
        ARACocoa
        PUBLIC 
            ${ARA_OSX_METAL_HEADERS}
            ${ARA_OSX_METAL_SOURCES})
    target_link_libraries(
        ARACocoa
        PRIVATE 
            ${QuartzCore}
            ${Metal})
    target_compile_definitions(
        ARACocoa
        PUBLIC 
            "ARA_OSX_WITH_METAL=1")

    message(STATUS "libARACocoa: Metal support found.")

endif()

if(MODULE_OSX_WITH_OPENGL)

    file(GLOB ARA_OSX_GL_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/src/ARA/Cocoa/Gl/*.h)
    file(GLOB ARA_OSX_GL_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/ARA/Cocoa/Gl/*.mm)
    find_library(QuartzCore QuartzCore REQUIRED)
    find_library(OpenGL OpenGL REQUIRED)
    
    target_sources(
        ARACocoa
        PUBLIC 
            ${ARA_OSX_GL_HEADERS}
            ${ARA_OSX_GL_SOURCES})
    target_link_libraries(
        ARACocoa
        PRIVATE 
            ${QuartzCore}
            ${OpenGL})
    target_compile_definitions(
        ARACocoa
        PUBLIC 
            "ARA_OSX_WITH_OPENGL=1")

    message(STATUS "libARACocoa: OpenGL support found.")

endif()

if(XCODE)
    set_target_properties(
        ARACocoa 
        PROPERTIES 
        XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC YES
        XCODE_ATTRIBUTE_CLANG_ENABLE_OBJC_ARC_EXCEPTIONS YES)
endif()

install(
    TARGETS ARACocoa
    LIBRARY DESTINATION ${ARA_INSTALL_PREFIX})