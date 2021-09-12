# Cysaurus

C++ utilities for Pysaurus.

- alignmentRaptor: library to find similar images
- runVideoRaptorBatch: command-line tool to collect videos info
- runVideoRaptorThumbnails: command-line tool to generate videos thumbnails

Use cmake for compilation and installation.

## NB

There is currently a bunch of unused and not updated but still working code,
including some code related to SFML library, as I intended to start developing
a GUI framework, but this project is currently in hiatus (^^).

However, current cmake config will try to compile anything, so SFML library is
required for compilation.

## Requirements

- SFML library
- FFMPEG libraries (avcodec, avformat, avutil, swscale)
