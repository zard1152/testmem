cmake_minimum_required(VERSION 3.10)
project(testmem C)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Create the executable
add_executable(testmem testmem.c)

# Install target
install(TARGETS testmem
        RUNTIME DESTINATION bin)

# Add platform-specific settings
if(UNIX)
    target_link_libraries(testmem PRIVATE m)  # Link math library on Unix-like systems
endif()
