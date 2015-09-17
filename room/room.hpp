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
          Room* north,
          Room* east,
          Room* south,
          Room* west );

    // This method returns 0 if the direction has a wall, 1 if the direction has
    // another room, and 2 if the direction has the exit.
    int DirectionCheck( Direction d );
    
    // This method returns the address of the Room in the given direction, or
    // NULL if no Room exists.
    // Should not be given an exit; exits should be checked with DirectionCheck
    // and then handled by Labyrinth.
    Room* DirectionEnter( Direction d );

  private:
    Inhabitant dark_thing_;
    Item object_;
    Direction exit_;
    Room* north_;
    Room* east_;
    Room* south_;
    Room* west_;
};
