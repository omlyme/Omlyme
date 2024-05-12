cmake_minimum_required(VERSION 3.5)

project(cpmnuker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(cpmnuker
    main.cpp
    include/asker.hpp
    include/json.hpp
    include/cpmnuker.hpp
    cpmnuker.cpp
    # include/base64.hpp
    # base64.cpp
)

include(FetchContent)

FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG f88fd7737de3e640c61703eb57a0fa0ce00c60cd)
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(termcolor GIT_REPOSITORY https://github.com/anas-ov/termcolor.git
                               GIT_TAG 977da1b5e33483c9f67b5423fda2b5ab76697d4f)
FetchContent_MakeAvailable(termcolor)

target_link_libraries(cpmnuker PRIVATE cpr::cpr)
target_link_libraries(cpmnuker PRIVATE termcolor::termcolor)

# if(WIN32) # Install dlls in the same directory as the executable on Windows
#     set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
#     set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
# endif()

# include(GNUInstallDirs)
# install(TARGETS cpmnuker
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
