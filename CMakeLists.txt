cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)
project(guiraptor VERSION 0.0.1 DESCRIPTION "C/C++ GUI library using SFML.")
include_directories(src)
set(COMMON_SOURCES
        src/core/core.cpp
        src/core/core.hpp
        src/core/Event.hpp
        src/core/patterns/complexPatterns.hpp
        src/core/patterns/DrawingType.hpp
        src/core/patterns/Pattern.hpp
        src/core/patterns/patterns.cpp
        src/core/patterns/simplePatterns.hpp
        src/core/Window.hpp
        src/fonts/monospace.cpp
        src/fonts/sansSerif.cpp
        src/fonts/serif.cpp
        src/guiRaptor.cpp
        src/guiRaptor.hpp
        src/internal/ellipseShape.hpp
        src/lib/utf/utf.hpp
        src/core/unicode.hpp
        src/core/patterns/PatternTextInfo.hpp)
set(TEST_SOURCES
        src/test.cpp
        src/core/patterns/_wrappers.hpp)
add_library(guiRaptor MODULE ${COMMON_SOURCES})
add_executable(testGui ${COMMON_SOURCES} ${TEST_SOURCES})
target_link_libraries(guiRaptor sfml-graphics sfml-window sfml-system)
target_link_libraries(testGui sfml-graphics sfml-window sfml-system)
set_target_properties(guiRaptor PROPERTIES PREFIX "")
set_target_properties(guiRaptor PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(guiRaptor PROPERTIES SOVERSION 1)
install(TARGETS guiRaptor LIBRARY DESTINATION $ENV{BIN_PATH})
