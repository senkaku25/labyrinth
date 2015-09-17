/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-09-17
 *
 * This program contains implementations of a Room class, which is a template
 * to create a Labyrinth.
 *
 */

#include <iostream>

#include "room_properties.hpp"
#include "room.hpp"

// Parameterized constructor
// This constructor sets the necessary properties of a Room.
Room::Room( Inhabitant dark_thing,
            Item object,
            Direction exit,
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

// This method returns 0 if the direction has a wall, 1 if the direction has
// another room, and 2 if the direction has the exit.
int Room::DirectionCheck( Direction d )
{
  if( d == Direction::kNone )
  {
    std::cout << "Error: DirectionCheck() was given the direction 'none'.\n" ;
    exit( 1 );
  }

  if( d == exit_ )
  {
    return 2;
  }

  else if( ( d == Direction::kNorth && north_ != NULL ) ||
           ( d == Direction::kEast  && east_  != NULL ) ||
           ( d == Direction::kSouth && south_ != NULL ) ||
           ( d == Direction::kWest  && west_  != NULL ) )
  {
    return 1;
  }

  else
  {
    return 0;
  }
}

// This method returns the address of the Room in the given direction, or NULL
// if no Room exists.
// Should not be given an exit; exits should be checked with DirectionCheck
// and then handled by Labyrinth.
Room* Room::DirectionEnter( Direction d )
{
  if( ( d == Direction::kNorth && exit_ == Direction::kNorth ) ||
      ( d == Direction::kEast  && exit_ == Direction::kEast  ) ||
      ( d == Direction::kSouth && exit_ == Direction::kSouth ) ||
      ( d == Direction::kWest  && exit_ == Direction::kWest  ) )
  {
    std::cout << "Error: DirectionEnter() was told to go through the exit but "\
                 " cannot.\n This should be done by Labyrinth (detected by "\
                 "DirectionCheck() and handled accordingly).\n" ;
    exit( 1 );
  }

  if( d == Direction::kNorth )
  {
    return north_;
  }
  else if( d == Direction::kEast )
  {
    return east_;
  }
  else if( d == Direction::kSouth )
  {
    return south_;
  }
  else
  {
    return west_;
  }

}
