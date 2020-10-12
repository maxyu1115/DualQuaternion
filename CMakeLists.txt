cmake_minimum_required(VERSION 3.17)
project(DualQuaternion)

set(CMAKE_CXX_STANDARD 14)

include_directories("D:/cpp libraries/glew-2.1.0/include")
include_directories("D:/cpp libraries/glfw-3.3.2/include")
link_directories("D:/cpp libraries/glew-2.1.0/lib/Release/Win32")
link_directories("D:/cpp libraries/glfw-3.3.2/lib-vc2019")

add_executable(DualQuaternion src/main.cpp src/CubeApp.cpp src/CubeApp.h src/DualQuaternionBasics.c src/DualQuaternionBasics.h src/DualQuaternionGeometry.h src/DualQuaternionGeometry.c)

target_link_libraries(DualQuaternion "glew32.lib" "glew32s.lib")
target_link_libraries(DualQuaternion "glfw3.lib")
target_link_libraries(DualQuaternion "opengl32.lib")