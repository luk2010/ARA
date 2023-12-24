
add_executable(FirstApp main.cpp)

target_link_libraries(
    FirstApp
    PUBLIC 
        ARAText   
        ARAControls
        ARADb
)

install(TARGETS FirstApp DESTINATION ${ARA_INSTALL_PREFIX})