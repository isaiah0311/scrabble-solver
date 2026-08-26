# Scrabble Solver
A utility designed to help players in a game of Scrabble.

## Overview
Input your Scrabble tiles to generate a list of possible words. Never lose a
game of Scrabble again!

## Project Structure
```
├── .vscode                    <- Settings and configurations
├── build                      <- Compiled binaries and build artifacts
├── res                        <- Resource files
├── src                        <- Source files
├── .gitignore
├── CMakeLists.txt
├── LICENSE
└── README.md
```

## Dependencies
### Build Systems
- **CMake:** Version 3.10+
### Extensions
- **C/C++:** `ms-vscode.cpptools`
- **C/C++ DevTools:** `ms-vscode.cpp-devtools`
- **CMake Tools:** `ms-vscode.cmake-tools`

## How to Build
### VS Code
1. Press `Ctrl + Shift + B` to open the build menu.
2. Select `CMake: Build` or `CMake: Clean Rebuild`.
### Command Line
1. Navigate to the root of the project.
2. Run `cmake -B build`.
3. Run `cmake --build build --config <config>` or
`cmake --build build --config <config> --clean-first`

## How to Run
### VS Code
1. Press `Ctrl + Shift + D` to open the run and debug menu.
2. From the drop-down menu, select `(Windows) Launch` to use the Visual Studio
Debugger, or `(gdb) Launch` to use GDB.
3. Press `F5` or the green play button to the left of the drop-down menu.
### Command Line
1. Navigate to the root of the project.
2. Run the executable found in the `build` directory, followed by the path to
the dictionary file you want to use.


**Note:** A dictionary file has been provided in the `res` folder.

## How to Use
The program will prompt you for your letters. The program is case-insensitive.
Non-letters will be ignored. Use `?` for blanks. The program will then spit out
a list of words that can be made using the given letters along with their point
values.

## License
This project is licensed under the [MIT License](LICENSE).

## Authors
**Isaiah Lateer**\
GitHub: [isaiah0311](https://github.com/isaiah0311)  
Email: isaiahL0311@gmail.com
