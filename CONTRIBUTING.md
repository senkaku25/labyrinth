# How to Contribute

## Setup

### Dependencies

The Makefile compiles using either **g++** or **Clang++**. When submitting code, please make sure it is warning-free and error-free with both compilers.

#### Install or Update g++

Provide your root password when prompted.

Add the repository with the latest version of g++:
> sudo add-apt-repository ppa:ubuntu-toolchain-r/test

Update the repository's version list:
> sudo apt-get update

Install the latest version of g++:
> sudo apt-get install g++-4.9

#### Install or Update Clang++

Provide your root password when prompted.

Add the repositories with the latest version of Clang++:
> sudo apt-get install llvm  
> sudo apt-get install build-essential

Update your repository's version list:
> sudo apt-get update

Install the latest version of Clang++:
> sudo apt-get install clang-3.5

### Executing the code

Fork the repository through GitHub.  

Navigate to the directory in which you want the code to be stored in, and create a local copy by cloning your repository:
> $ git clone https://github.com/YOUR_USERNAME_HERE/labyrinth.git

Navigate into the *test/* directory and take a look at the possible make options:
> $ cd labyrinth/test/  
> $ make

Run any of the given make commands from the test folder.  
Make sure the all test cases compile without warnings or errors on both g++ and Clang (see **Dependencies**, above).

Well done, you've set up your development environment successfully!  
Now you can make changes, test them, check that it compiles cleanly on both g++ and Clang, then commit them to your repository. If you think you've got

## File Structure
* *src/* contains the C++ source files.
* *include/* contains the C++ header files.
* *test/* contains all tools needed for testing and compilation.

## Object Structure <a id="object-structure">
* The **Room** class is a single room and its contents.
* The **Labyrinth** class is a 2-d maze of Rooms, and uses the Room class.
* The **LabyrinthMap** class is a 2-d depiction of a given Labyrinth which can be updated, and uses the Labyrinth, LabyrinthMapCoordinateRoom, and LabyrinthMapCoordinateBorder classes.
  * The **LabyrinthMapCoordinateRoom** class is a single coordinate in the map which refers to a Room and its contents.
  * The **LabyrinthMapCoordinateBorder** class is a single coordinate in the map which refers to a Border (which may border 1 or more Rooms).
* The **Player class** is a description of the inventory, location, and status of the given player.
* The **PlayLabyrinth** class is the implementation of the game Labyrinth according to the file *GameInstructions.txt*, and uses the Labyrinth, LabyrinthMap, and Player classes.

## LabyrinthMap
This is a 2-d mapping of a Labyrinth which is updated and printed whenever Display() is called.

### Example
```
         X
       0  1  2
     ┌──┬─────┐
   0 │M•│   O │
Y    │  ╵  ╷  │
   1 │m   T│0 │
     └─────┴──┘
```

In a coordinate, inhabitants are on the left and items are on the right.

At coordinate (0, 0) is a live Minotaur and a bullet.  
At coordinate (0, 1) is a dead minotaur.  
At coordinate (1, 1) is a Treasure.  
At coordinate (2, 0) is an intact mirror.  
At coordinate (2, 1) is a broken mirror.

## Design Decisions/Constraints

* PlayLabyrinth:
  * Items are automatically picked up by the player since a Room can currently only hold a single item, so a Treasure cannot be dropped in the same Room in which another Item already exists

## Task List

### Labyrinth
1. Test all methods (Currently underway in the laby-testing branch)

### Miscellaneous
1. Implement the Player class with inventory and location.
1. Implement the PlayLabyrinth class to execute the game.
1. Use [NCurses](http://hughm.cs.ukzn.ac.za/~murrellh/os/notes/ncurses.html) to play the game in an isolated terminal.
