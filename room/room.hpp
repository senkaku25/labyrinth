/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-09-17
 *
 * This header file contains implementations of a Room class, which is the template to create a Labyrinth.
 *
 */

#pragma once

#include "room_properties.hpp"

// Labyrinth - method to check for errors
// Rooms: Spawn (1 respawn), treasure, exit

class Room
{
  public:
    Room( Inhabitant dark_thing,
          Item object,
          Direction exit,
          Room* north,
          Room* east,
          Room* south,
          Room* west );

    int DirectionCheck( Direction d );  // Returns 0 if facing a wall, 1 if facing a room,
                                        // 2 if facing the exit.
    Room* DirectionEnter( Direction d );  // Returns the address of the next room.
                                          // Will not allow exiting; should be done in Labyrinth.

  private:
    Inhabitant dark_thing_;
    Item object_;
    Direction exit_;
    Room* north_;
    Room* east_;
    Room* south_;
    Room* west_;
};
