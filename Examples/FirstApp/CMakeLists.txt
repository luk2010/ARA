
add_executable(FirstApp main.cpp)

target_link_libraries(
    FirstApp
    PUBLIC 
        ARAText   
        ARAControls
)

install(TARGETS FirstApp DESTINATION ${ARA_INSTALL_PREFIX})