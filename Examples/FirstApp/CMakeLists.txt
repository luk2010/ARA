
add_executable(FirstApp main.cpp)

target_link_libraries(
    FirstApp
    PUBLIC 
        ARAText   
        ARAControls
        ARADb
)

set_target_properties(
    FirstApp
    PROPERTIES 
        XCODE_GENERATE_SCHEME TRUE
        XCODE_SCHEME_WORKING_DIRECTORY ${ARA_INSTALL_PREFIX})

install(TARGETS FirstApp DESTINATION ${ARA_INSTALL_PREFIX})