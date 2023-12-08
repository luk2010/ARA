
add_executable(FirstApp main.cpp)

target_link_libraries(
    FirstApp
    PUBLIC 
        ARAText   
)

install(TARGETS FirstApp DESTINATION ${ARA_INSTALL_PREFIX})