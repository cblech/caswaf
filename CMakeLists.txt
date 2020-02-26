cmake_minimum_required(VERSION 3.0)
project(caswaf)

set(CMAKE_CXX_STANDARD 17)

#include the libraries acquired by conan
include(cmake-build-debug/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(src/engine)

add_executable(projectBuilder 
    
    src/ProjectBuilder/main.cpp

    src/ProjectBuilder/Compiler.h
    src/ProjectBuilder/HTMLParser.h
    src/ProjectBuilder/log.h
    
    src/ProjectBuilder/Compiler.cpp
    src/ProjectBuilder/HTMLParser.cpp
    
)
target_link_libraries(projectBuilder ${CONAN_LIBS})

#get_target_property(exefile projectBuilder LOCATION )

#add_custom_command(TARGET projectBuilder POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy ${projectBuilder} ${CMAKE_CURRENT_SOURCE_DIR}/tools
#    COMMENT "Copy projectBuilder to 'tools' directory"
#)

file(GLOB_RECURSE SUB_SOURCES_CONTROLLER "${CMAKE_CURRENT_SOURCE_DIR}/src/webserver/controller/*.cpp")
file(GLOB_RECURSE SUB_HEADER_CONTROLLER "${CMAKE_CURRENT_SOURCE_DIR}/src/webserver/controller/*.h")

file(GLOB_RECURSE SUB_SOURCES_GENERATED "${CMAKE_CURRENT_SOURCE_DIR}/src/generated/*.cpp" )
file(GLOB_RECURSE SUB_HEADER_GENERATED "${CMAKE_CURRENT_SOURCE_DIR}/src/generated/*.h")

file(GLOB_RECURSE SUB_SOURCES_CUSTOMPARTS "${CMAKE_CURRENT_SOURCE_DIR}/src/webserver/customParts/*.cpp")
file(GLOB_RECURSE SUB_HEADER_CUSTOMPARTS "${CMAKE_CURRENT_SOURCE_DIR}/src/webserver/customParts/*.h")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)



add_executable(caswaf 

    src/PocoMainServer.cpp

        ${SUB_SOURCES_GENERATED}
        ${SUB_HEADER_CONTROLLER}
        ${SUB_SOURCES_CONTROLLER}
        ${SUB_HEADER_GENERATED}
        ${SUB_SOURCES_CUSTOMPARTS}
        ${SUB_HEADER_CUSTOMPARTS}

    #Routing
        src/webserver/Routing.h
        src/webserver/Routing.cpp

    #Engine headers
        src/engine/RoutingEngine.h
        src/engine/Controller.h
        src/engine/Route.h
        src/engine/Resources.h
        src/engine/starStringEquals.h
        src/engine/StaticController.h
        src/engine/StaticRecource.h
        src/engine/casTypes.h
        src/engine/part/Part.h
        src/engine/part/StaticPart.h
        src/engine/part/DataPart.h

    #Engine sources
        src/engine/Controller.cpp
        src/engine/RoutingEngine.cpp
        src/engine/Route.cpp
        src/engine/StaticRecource.cpp
        src/engine/part/Part.cpp
        src/engine/part/StaticPart.cpp
        src/engine/part/DataPart.cpp

        )
target_link_libraries(caswaf ${CONAN_LIBS})

add_custom_command(TARGET caswaf PRE_BUILD
    
    COMMAND echo ${CMAKE_CURRENT_SOURCE_DIR}/build/bin/projectBuilder
    ARGS ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_CURRENT_SOURCE_DIR}/src/generated
)


add_dependencies(caswaf projectBuilder)

