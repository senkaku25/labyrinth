# labyrinth
C++ implementation of a game played with a mappable set of connected rooms.

### Object Structure:
The **Room** class is a single room and its contents.  
The **Labyrinth** class is a 2-d maze of Rooms, and uses the Room class.  
The **LabyrinthMap** class is a 2-d depiction of a given Labyrinth which can be updated, and uses the Labyrinth class.  
The **Player class** is a description of the inventory, location, and status of the given player.  
The **PlayLabyrinth** class is the implementation of the game Labyrinth according to the file *GameInstructions.txt*, and uses the Labyrinth, LabyrinthMap, and Player classes.

### TODO:

#### Labyrinth:
1. Test all methods (Currently underway in the laby-testing branch)

#### Miscellaneous:
1. Implement the Player class with inventory and location.
1. Implement the PlayLabyrinth class to execute the game.
1. Use [NCurses](http://hughm.cs.ukzn.ac.za/~murrellh/os/notes/ncurses.html) to play the game in an isolated terminal.
