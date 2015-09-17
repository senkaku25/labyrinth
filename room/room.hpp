/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-05-20
 *
 * This header file contains implementations of a basic Room class, the building block of a game.
 *
 */

#pragma once

#include "room_properties.hpp"

class Room
{
  public:
    Room( inhabitant dark_thing,
          item object,
          direction exit,
          Room* north,  // NULL Room address represents a wall.
          Room* east,
          Room* south,
          Room* west );

    int DirectionCheck( direction d );  // Returns 0 if facing a wall, 1 if facing a room,
                                        // 2 if facing the exit.
    Room* DirectionEnter( direction d );  // Returns the address of the next room.
                                          // Will not allow exiting; should be done in Labyrinth.

  private:
    inhabitant dark_thing_;
    item object_;
    direction exit_;
    Room* north_;
    Room* east_;
    Room* south_;
    Room* west_;
};
