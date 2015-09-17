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
#include <stdexcept>

#include "room_properties.hpp"
#include "room.hpp"

// Parameterized constructor
// This constructor sets the necessary properties of a Room.
Room::Room( Inhabitant dark_thing,
            Item object,
            Direction exit,
            bool wall_north,
            bool wall_east,
            bool wall_south,
            bool wall_west )
{
  dark_thing_ = dark_thing;
  object_     = object;
  exit_       = exit;
  wall_north_ = wall_north;
  wall_east_  = wall_east;
  wall_south_ = wall_south;
  wall_west_  = wall_west;
}

// This method returns:
//   RoomBorder::kExit if the direction has the exit,
//   RoomBorder::kRoom if the direction has another room, or
//   RoomBorder::kWall if the direction has a wall.
// An exception is thrown if:
//   Direction d is kNone (invalid_argument)
RoomBorder Room::DirectionCheck( Direction d )
{
  if( d == Direction::kNone )
  {
    throw std::invalid_argument( "Error: DirectionCheck() was given the "\
      "direction kNone.\n" ) ;
  }

  if( d == exit_ )
  {
    return RoomBorder::kExit;
  }

  else if( ( d == Direction::kNorth && !(wall_north_) ) ||
           ( d == Direction::kEast  && !(wall_east_)  ) ||
           ( d == Direction::kSouth && !(wall_south_) ) ||
           ( d == Direction::kWest  && !(wall_west_)  ) )
  {
    return RoomBorder::kRoom;
  }

  else
  {
    return RoomBorder::kWall;
  }
}
