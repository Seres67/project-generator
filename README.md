# Project Generator

## Languages

- C
- C++

## Prerequisites

- A C compiler with C++20 standard
- ninja
- meson

## How to build

Clone the project `git clone https://github.com/Seres67/project-generator.git`  
Build it using meson & ninja:
```
cd project-generator
meson setup build
cd build
ninja
```
Then use it like this:
`./project-generator <language> <project name>`
This will create a new folder with a meson.build file, src & include folders, and src/main.c with a hello world.
