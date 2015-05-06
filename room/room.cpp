/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-05-05
 *
 * This program contains implementations of a basic Room class, the building block of a game.
 *
 */

#include <iostream>

#include "room_properties.hpp"
#include "room.hpp"

// This constructor sets the necessary properties of a Room.
Room::Room( inhabitant dark_thing,
            item object,
            direction exit,
            Room* north,
            Room* east,
            Room* south,
            Room* west )
{
  dark_thing_ = dark_thing;
  object_     = object;
  exit_       = exit;
  north_      = north;
  east_       = east;
  south_      = south;
  west_       = west;
}

// This method returns 0 if the direction has a wall, 1 if the direction has another room, and 2 if
// the direction has the exit.
int Room::DirectionCheck( direction d )
{
  if( d == none )
  {
    std::cout << "Error: DirectionCheck() was given the direction 'none'.\n" ;
    exit( 1 );
  }

  if( d == exit_ )
  {
    return 2;
  }

  else if( ( d == north && north_ != NULL ) ||
           ( d == east  && east_  != NULL ) ||
           ( d == south && south_ != NULL ) ||
           ( d == west  && west_  != NULL )
  {
    return 1;
  }

  else
  {
    return 0;
  }

// This method returns the address of the Room in the given direction, or NULL if no Room exists.
// Should not be given an exit; exits should be checked with DirectionCheck and then handled
// by Labyrinth.
Room* DirectionEnter( direction d )
{
  if( d == north && exit_ == north ||
      d == east  && exit_ == east  ||
      d == south && exit_ == south ||
      d == west  && exit_ == west  )
  {
    std::cout << "Error: DirectionEnter() was told to go through the exit but cannot.\n" \
                 "This should be done by Labyrinth (detected by DirectionCheck() and " \
                 "handled accordingly).\n" ;
    exit( 1 );
  }

  if( d == north )
  {
    return north_;
  }
  else if( d == east )
  {
    return east_;
  }
  else if( d == south )
  {
    return south_;
  }
  else if( d == west )
  {
    return west_;
  }

}
