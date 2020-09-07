# eng

Boilerplate code for SDL 2.0 game engine

## Build Instructions

### Unix
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

### Windows
```
> mkdir build
> cd build
> cmake -G "MinGW Makefiles" ..
> make
```

### Emscripten
```
$ mkdir build-emc
$ cd build-emc
$ emcmake cmake ..
$ make
```