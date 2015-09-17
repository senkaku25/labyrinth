/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-09-17
 *
 * This header file contains implementations of a Room class, which is a
 * template to create a Labyrinth.
 *
 */

#pragma once

#include "room_properties.hpp"

// Rooms: Spawn (1 respawn), treasure, exit

class Room
{
  public:
  
    // Parameterized constructor
    // This constructor sets the necessary properties of a Room.
    Room( Inhabitant dark_thing,
          Item object,
          Direction exit,
          bool wall_north,
          bool wall_east,
          bool wall_south,
          bool wall_west );

    // This method returns:
    //   RoomBorder::kExit if the direction has the exit,
    //   RoomBorder::kRoom if the direction has another room, or
    //   RoomBorder::kWall if the direction has a wall.
    RoomBorder DirectionCheck( Direction d );
    
    // This method returns the address of the Room in the given direction, or
    // nullptr if a wall exists.
    // Cannot handle exits, which should be checked with DirectionCheck and
    // handled by Labyrinth.
    // An exception is thrown if:
    //   Direction d is kNone (invalid_argument)
    //   Direction d has an exit (logic_error)
    Room* DirectionEnter( Direction d );

  private:
    // Room* containing a nullptr represents a wall.
    Inhabitant dark_thing_;
    Item object_;
    Direction exit_;
    bool wall_north_;
    bool wall_east_;
    bool wall_south_;
    bool wall_west_;
};
