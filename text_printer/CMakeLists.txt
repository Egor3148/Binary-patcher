cmake_minimum_required(VERSION 3.10)
project(TextPrinter LANGUAGES CXX)

option(USE_FLTK "Build with FLTK GUI" ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/CMakeCache.txt) # CMake cache force clean

include_directories(inc)

set(SOURCES
    src/buffer.h
    src/text_printer.cpp
)

if(USE_FLTK)
    message(STATUS "Building with FLTK GUI")
    
    # list(APPEND SOURCES src/gui_interface.cpp)
    
    add_subdirectory(fltk)
    
    add_executable(TextPrinter ${SOURCES})
    
    target_link_libraries(TextPrinter
        fltk
        fltk_images  
        fltk_gl     
    )
    
    target_compile_definitions(TextPrinter PRIVATE USE_FLTK)
else()
    message(STATUS "Building in pure CLI mode (no FLTK)")
    add_executable(TextPrinter ${SOURCES})
endif()