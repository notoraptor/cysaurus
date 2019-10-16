cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)
project(cysaurus VERSION 0.0.1 DESCRIPTION "C/C++ utilities with a C interface for easy integration (e.g. in Python).")
include_directories(src)

set(SRC_GUI_RAPTOR
        src/gui/core/core.cpp
        src/gui/core/core.hpp
        src/gui/core/Event.hpp
        src/gui/core/patterns/complexPatterns.hpp
        src/gui/core/patterns/DrawingType.hpp
        src/gui/core/patterns/Pattern.hpp
        src/gui/core/patterns/patterns.cpp
        src/gui/core/patterns/simplePatterns.hpp
        src/gui/core/Window.hpp
        src/gui/fonts/monospace.cpp
        src/gui/fonts/sansSerif.cpp
        src/gui/fonts/serif.cpp
        src/gui/gui.cpp
        src/gui/gui.hpp
        src/gui/internal/ellipseShape.hpp
        src/lib/utf/utf.hpp
        src/gui/core/unicode.hpp
        src/gui/core/patterns/PatternTextInfo.hpp)
set(TEST_GUI_RAPTOR
        other/test/gui/src/test.cpp
        other/test/gui/src/_wrappers.hpp)

add_library(guiRaptor MODULE ${SRC_GUI_RAPTOR})
target_link_libraries(guiRaptor sfml-graphics sfml-window sfml-system)
set_target_properties(guiRaptor PROPERTIES PREFIX "")
set_target_properties(guiRaptor PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(guiRaptor PROPERTIES SOVERSION 1)
install(TARGETS guiRaptor LIBRARY DESTINATION $ENV{BIN_PATH})

add_executable(testGui ${SRC_GUI_RAPTOR} ${TEST_GUI_RAPTOR})
target_link_libraries(testGui sfml-graphics sfml-window sfml-system)
