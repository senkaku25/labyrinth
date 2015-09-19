/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-09-19
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
  
    // Default constructor
    // This constructor sets a basic, walled, empty Room.
    Room();
  
    // Parameterized constructor
    // This constructor sets the necessary properties of a Room.
    Room( Inhabitant dark_thing,
          Item object,
          Direction exit,
          bool wall_north,
          bool wall_east,
          bool wall_south,
          bool wall_west );
          
    // This method returns the current inhabitant of the Room.
    Inhabitant GetInhabitant();
    
    // This method changes the current inhabitant of the Room.
    void SetInhabitant( Inhabitant inh );
    
    // This method returns the current item in the Room.
    Item GetItem();
    
    // This method changes the current item in the Room.
    void SetItem( Item itm );

    // This method returns:
    //   RoomBorder::kExit if the direction has the exit,
    //   RoomBorder::kRoom if the direction has another room, or
    //   RoomBorder::kWall if the direction has a wall.
    // An exception is thrown if:
    //   Direction d is kNone (invalid_argument)
    RoomBorder DirectionCheck( Direction d );

  private:
    // The exit direction does not count as a wall.
    // Room* containing a nullptr represents a wall.
    Inhabitant dark_thing_;
    Item object_;
    Direction exit_;
    bool wall_north_;
    bool wall_east_;
    bool wall_south_;
    bool wall_west_;
};