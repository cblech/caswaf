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



add_executable(caswaf 

    src/PocoMainServer.cpp


    #Engine headers
        src/engine/Routing.h
        src/engine/RoutingEngine.h
        src/engine/Controller.h
        src/engine/Part.h
        src/engine/Route.h
        src/engine/starStringEquals.h
        src/engine/StaticController.h
        src/engine/StaticRecource.h
        src/engine/casTypes.h

    #Engine sources
        src/engine/Routing.cpp
        src/engine/Controller.cpp
        src/engine/Part.cpp
        src/engine/RoutingEngine.cpp
        src/engine/Route.cpp
        src/engine/StaticRecource.cpp

        src/generated/StaticRecouces.h

        )
target_link_libraries(caswaf ${CONAN_LIBS})

add_custom_command(TARGET caswaf PRE_BUILD
    
    COMMAND echo ${CMAKE_CURRENT_SOURCE_DIR}/build/bin/projectBuilder
    ARGS ${CMAKE_CURRENT_SOURCE_DIR}/resources ${CMAKE_CURRENT_SOURCE_DIR}/src/generated
)


add_dependencies(caswaf projectBuilder)

