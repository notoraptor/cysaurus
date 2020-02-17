cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -fopenmp")
set(CMAKE_CXX_FLAGS_RELEASE "-Ofast")

project(cysaurus VERSION 0.0.1 DESCRIPTION "C/C++ utilities with a C interface for easy integration (e.g. in Python).")
include_directories(src)
include_directories($ENV{CPATH})
link_directories($ENV{LIBRARY_PATH})
add_compile_definitions(CJSON_HIDE_SYMBOLS)

set(SRC_GUI_RAPTOR
        src/core/unicode.hpp
        src/gui/core/core.cpp
        src/gui/core/core.hpp
        src/gui/core/Event.hpp
        src/gui/core/patterns/complexPatterns.hpp
        src/gui/core/patterns/DrawingType.hpp
        src/gui/core/patterns/Pattern.hpp
        src/gui/core/patterns/patterns.cpp
        src/gui/core/patterns/PatternTextInfo.hpp
        src/gui/core/patterns/simplePatterns.hpp
        src/gui/core/Window.hpp
        src/gui/fonts/monospace.cpp
        src/gui/fonts/sansSerif.cpp
        src/gui/fonts/serif.cpp
        src/gui/gui.cpp
        src/gui/gui.hpp
        src/gui/internal/ellipseShape.hpp
        src/lib/utf/utf.hpp
        )
set(SRC_VIDEO_RAPTOR
        src/alignment/alignment.cpp
        src/alignment/alignment.hpp
        src/core/unicode.hpp
        src/lib/cjson/cJSON.c
        src/lib/cjson/cJSON.h
        src/lib/lodepng/lodepng.cpp
        src/lib/lodepng/lodepng.h
        src/lib/utf/utf.hpp
        src/video/core/compatWindows.hpp
        src/video/core/core.cpp
        src/video/core/errorCodes.hpp
        src/video/core/ErrorReader.hpp
        src/video/core/FileHandle.hpp
        src/video/core/HWDevices.hpp
        src/video/core/Stream.hpp
        src/video/core/ThumbnailContext.hpp
        src/video/core/utils.hpp
        src/video/core/Video.hpp
        src/video/core/VideoInfo.hpp
        src/video/core/VideoReport.hpp
        src/video/core/VideoThumbnail.hpp
        src/video/videoRaptor.cpp
        src/video/videoRaptor.hpp
        src/video/core/VideoRaptorContext.hpp)
set(TEST_GUI_RAPTOR
        other/test/gui/src/test.cpp
        other/test/gui/src/_wrappers.hpp)
set(TEST_HARDWARE_ACCELERATION
        other/test/hardware_acceleration/hwaccel.c)
set(TEST_VIDEO_RAPTOR
        other/test/video/testVideoRaptor.cpp)
set(SRC_BATCH
        other/test/video/batch.cpp)
set(SRC_RUN_VIDEO_RAPTOR_BATCH
        other/app/runVideoRaptorBatch.cpp)
set(SRC_JSON
        src/lib/cjson/cJSON.h
        src/lib/cjson/cJSON.c
        other/test/general/testJSON.cpp)

add_library(guiRaptor MODULE ${SRC_GUI_RAPTOR})
target_link_libraries(guiRaptor sfml-graphics sfml-window sfml-system)
set_target_properties(guiRaptor PROPERTIES PREFIX "")
set_target_properties(guiRaptor PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(guiRaptor PROPERTIES SOVERSION 1)
install(TARGETS guiRaptor LIBRARY DESTINATION $ENV{BIN_PATH})

add_library(videoRaptorBatch MODULE ${SRC_VIDEO_RAPTOR})
target_link_libraries(videoRaptorBatch avcodec avformat avutil swscale -static-libgcc -static-libstdc++)
set_target_properties(videoRaptorBatch PROPERTIES PREFIX "")
set_target_properties(videoRaptorBatch PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(videoRaptorBatch PROPERTIES SOVERSION 1)
install(TARGETS videoRaptorBatch LIBRARY DESTINATION $ENV{BIN_PATH})

add_executable(testGui ${SRC_GUI_RAPTOR} ${TEST_GUI_RAPTOR})
target_link_libraries(testGui sfml-graphics sfml-window sfml-system -static-libgcc -static-libstdc++)

add_executable(hwaccel ${TEST_HARDWARE_ACCELERATION})
target_link_libraries(hwaccel avcodec avformat avutil swscale -static-libgcc -static-libstdc++)

add_executable(testVideoRaptor ${TEST_VIDEO_RAPTOR} ${SRC_VIDEO_RAPTOR})
target_link_libraries(testVideoRaptor avcodec avformat avutil swscale -static-libgcc -static-libstdc++)

add_executable(batch ${SRC_BATCH} ${SRC_VIDEO_RAPTOR})
target_link_libraries(batch avcodec avformat avutil swscale -static-libgcc -static-libstdc++)

add_executable(testJSON ${SRC_JSON})

add_executable(runVideoRaptorBatch ${SRC_RUN_VIDEO_RAPTOR_BATCH} ${SRC_VIDEO_RAPTOR})
target_link_libraries(runVideoRaptorBatch avcodec avformat avutil swscale -static-libgcc -static-libstdc++)
install(TARGETS runVideoRaptorBatch DESTINATION $ENV{BIN_PATH})
