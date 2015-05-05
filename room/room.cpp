/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-05-05
 *
 * This program contains implementations of a Room class, which is the template to create a Labyrinth.
 *
 */

#include <iostream>

#include "room_properties.hpp"
#include "room.hpp"

// This constructor sets the necessary properties of a Room.
Room::Room( inhabitant dark_thing,
            item object,
            exit get_out,
            Room* north,
            Room* east,
            Room* south,
            Room* west )
{
  dark_thing_ = dark_thing;
  object_     = object;
  get_out_    = get_out;
  north_      = north;
  east_       = east;
  south_      = south;
  west_       = west;
}

// This method returns 0 if the direction has a wall, 1 if the direction has another room, and 2 if
// the direction has the exit.
int Room::DirectionCheck( direction d )
{
  if( d == north )
  {
    if( exit_ == north )
    {
      return 2;
    }
    else if( north_ == NULL )
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }

  else if( d == east )
  {
    if( exit_ == east )
    {
      return 2;
    }
    else if( east_ == NULL )
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }

  else if( d == south )
  {
    if( exit_ == south )
    {
      return 2;
    }
    else if( south_ == NULL )
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }

  else if( d == west )
  {
    if( exit_ == west )
    {
      return 2;
    }
    else if( west_ == NULL )
    {
      return 0;
    }
    else
    {
      return 1;
    }
  }

}

// This method returns the address of the Room in the given direction.
// Should not be given an exit; exits should be checked with DirectionCheck and then handled
// by Labyrinth.
Room* DirectionEnter( direction d )
{
  if( d == north && exit_ == north ||
      d == east  && exit_ == east  ||
      d == south && exit_ == south ||
      d == west  && exit_ == west  )
  {
    std::cout << "Error: DirectionEnter() was told to go through the exit but cannot.\n\
                  This should be done by Labyrinth (detected by DirectionCheck() and\
                  handled accordingly).\n" ;
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
