#PROJECT NAME
project(BoidsDemo)
cmake_minimum_required(VERSION 2.8)

#EXTERNAL PACKAGES (IRRLICHT)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(Irrlicht REQUIRED)

#INCLUDES & SRC FILES
include_directories(
    ${Irrlicht_INCLUDE_DIRECTORY}
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/../hierarchical-fighting-boids/include
)
file(GLOB SRCS src/*.cpp)
file(GLOB HDRS include/*.h)

file(GLOB LIBSRCS ../hierarchical-fighting-boids/src/*.cpp)
file(GLOB LIBHDRS ../hierarchical-fighting-boids/include/*.h)

#LINKING AND EXECUTABLE
add_executable(${PROJECT_NAME} ${SRCS} ${HDRS} ${LIBSRCS} ${LIBHDRS})
target_link_libraries(${PROJECT_NAME} ${IRRLICHT_LIBRARIES})
