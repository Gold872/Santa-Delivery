# Santa Delivery Game

A game made with C++ and the SDL2 library.

In the game you drop presents into houses while dodging obstacles in the air.

# How to Play

Press Space to drop a present, use the arrow keys to move Santa around, and press Esc. to pause the game.

# Compiling

First you have to download [Mingw32](https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-win32/seh/x86_64-8.1.0-release-win32-seh-rt_v6-rev0.7z/download), [SDL2](https://www.libsdl.org/download-2.0.php), [SDL2_image](https://www.libsdl.org/projects/SDL_image/), [SDL_TTF](https://www.libsdl.org/projects/SDL_ttf/), and [SDL_Mixer](https://www.libsdl.org/projects/SDL_mixer/). Extract these into the MinGW folder. After this perform the following steps based on your OS.

# Windows

Execute the following command in the project folder:

```
g++ -c src/*.cpp -std=c++14 -O3 -Wall -m64 -I include -I C:/SDL2-w32/include && g++ *.o -o bin/release/main -s -L C:/SDL2-w32/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer && start bin/release/main
```

# Linux

```
g++ -c src/*.cpp -std=c++14 -O3 -Wall -m64 -I include && mkdir -p bin/release && g++ *.o -o bin/release/main -s -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer
```

# Compiling Errors

You may need to change a few settings in the compiling command depending on where you stored the SDL2 libaries. Some extra help on compiling can be found [here](https://www.cs.fsu.edu/~lacher/lectures/Output/compiler/index.html?$$$compiler2.html$$$)