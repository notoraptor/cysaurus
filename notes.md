# Old installation notes

```
md build

cd build

g++ -c ..\core\*.cpp ..\videoRaptorBatch\*.cpp ..\lib\lodepng\*.cpp  -I .. -I %CPATH% -L %LIBRARY_PATH% -lavcodec -lavformat -lavutil -lswscale -O3

g++ -shared -o videoRaptorBatch.dll *.o -fPIC -I .. -I %CPATH% -L %LIBRARY_PATH% -lavcodec -lavformat -lavutil -lswscale -O3
```

# Linux installations notes (Ubuntu)

- Poetry 
- Miniconda 
- git 
- cmake

For ffmpeg compilation:
- yasm
  - sudo apt install yasm
