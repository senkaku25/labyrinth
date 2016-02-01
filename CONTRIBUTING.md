# Contributing

## TODO:

### Labyrinth:
1. Test all methods (Currently underway in the laby-testing branch)
1. Write more documentation for this document...

### Miscellaneous
1. Implement the Player class with inventory and location.
1. Implement the PlayLabyrinth class to execute the game.
1. Use [NCurses](http://hughm.cs.ukzn.ac.za/~murrellh/os/notes/ncurses.html) to play the game in an isolated terminal.

## Object Structure
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
