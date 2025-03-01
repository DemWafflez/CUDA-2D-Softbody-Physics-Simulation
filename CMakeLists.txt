cmake_minimum_required(VERSION 3.10)

# Declare project with both C++ and CUDA support
project(CudaPhysics LANGUAGES CXX CUDA)

# Set C++ and CUDA standards to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

# Find external packages
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED) 
find_package(CUBLAS)  # Optional: only if your code uses cuBLAS

# Gather all .cpp and .cu source files recursively from the src/ directory
file(GLOB_RECURSE CPP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE CUDA_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cu")
set(SOURCES ${CPP_SOURCES} ${CUDA_SOURCES})

# Create the executable target from all source files
add_executable(CudaPhysics ${SOURCES})

# Set the include directories for the target
target_include_directories(CudaPhysics PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Set optimization flag for CUDA files (only applies to CUDA compilation)
target_compile_options(CudaPhysics PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:-O3>)

# Link required libraries
target_link_libraries(CudaPhysics PRIVATE
    GLEW::GLEW
    glfw
    glm::glm
    OpenGL::GL  
)

# If cuBLAS is found, link it too
if(CUBLAS_FOUND)
    target_link_libraries(CudaPhysics PRIVATE ${CUBLAS_LIBRARIES})
endif()

# Post-build: Copy the resources directory to the build directory (next to the executable)
add_custom_command(TARGET CudaPhysics POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/resources"
    "$<TARGET_FILE_DIR:CudaPhysics>/resources"
)
