This is Jeremiah Yong and Adam Wu's MicroMouse Github repository.

Software:
Goal: Develop, test, and run a floodfill and navigation program in C. 

File Summary:
- The following files consist of the various functions used to successfully deploy the mouse in a maze simulator.

API.cpp
- Accesses an API in order to test the mouse code in a simulator. Allows us to perform API calls within every other file.

Main.cpp
- If micromouse is a cake then Main.cpp is the mixer, where we combine and run functions from every other file.

definitions.hpp
- Where all of the enums, structs, and other variables used across the entire repository are defined.

mazeFunctions.hpp
- Functions pertaining to the maze (such as wall updates, simulation updates, position updates, and more) are defined and written here.

mouseFunctions.hpp
- Functions pertaining to the mouse (such as mouse position calculation, movement, and more) are defined and written here.

floodFill.hpp
- the flood-fill algorithm (function determining how the mouse moves through the maze) is written here

utilityFunctions.hpp
- Functions that allow the flood-fill program to run are defined and written here.

log.hpp
- Allows printing to happen with more efficiency for testing reasons.

testFunctions.hpp
- Functions used to test our program throughout the endeavor are stored here.

