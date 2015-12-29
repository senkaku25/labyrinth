# labyrinth
C++ template for a mappable set of connected rooms for playing a game.

The Room class contains a template for creating a single room and its contents.
The Labyrinth class contains a template for creating and playing a maze according to the rules of the game Labyrinth (see the file _Instructions_), and uses the Room class.

### LabyrinthMap TODO:
1. Rename Update() to UpdateRooms().
1. Split the constructor into separate (private) methods.
  1. UpdateBorders().
1. Implement displaying of Room contents.
  1. Numbering of all Rooms with Cartesian coordinates.
    1. Set a maximum Labyrinth size.
1. Implement UpdateRooms().
1. Test UpdateRooms().

### Labyrinth TODO:
1. Test ConnectRooms().

###TODO:
1. Branch out and implement the Labyrinth class, using a 2-d array to store the rooms.
1. Implement the Player class with inventory and location.
1. Implement the PlayLabyrinth class to execute the game.
1. Use [NCurses](http://hughm.cs.ukzn.ac.za/~murrellh/os/notes/ncurses.html) to play the game in an isolated terminal.
