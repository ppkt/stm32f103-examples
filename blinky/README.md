# How to build

```sh
$ git submodule update --init --recursive
$ mkdir build/
$ cd build/
$ cmake -DCMAKE_TOOLCHAIN_FILE=../arm-none-eabi.cmake ..
$ make libopencm3
$ make 
$ make upload
```
