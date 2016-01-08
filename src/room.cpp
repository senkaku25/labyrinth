/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-12-28
 *
 * This program contains implementations of a Room class, which is a template
 * to create a Labyrinth.
 *
 */

#include <iostream>
#include <stdexcept>

#include "../include/room_properties.hpp"
#include "../include/room.hpp"

// Default constructor
// This constructor sets a basic, walled, empty Room.
Room::Room()
{
  dark_thing_ = Inhabitant::kNone;
  object_     = Item::kNone;
  exit_       = Direction::kNone;
  wall_north_ = true;
  wall_east_  = true;
  wall_south_ = true;
  wall_west_ = true;
}

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

// This method returns the current inhabitant of the Room.
Inhabitant Room::GetInhabitant() const
{
  return dark_thing_;
}

// This method changes the current inhabitant of the Room.
void Room::SetInhabitant( Inhabitant inh )
{
  dark_thing_ = inh;
  return;
}

// This method returns the current item in the Room.
Item Room::GetItem() const
{
  return object_;
}

// This method changes the current item in the Room.
void Room::SetItem( Item itm )
{
  object_ = itm;
  return;
}

// This method removes the Wall in the given direction so that the Room
// may be connected to another, or to set the exit.
// An exception is thrown if:
//   The Wall has already been removed (logic_error)
//   Direction d is null (i.e. Direction::kNone) (invalid_argument)
void Room::BreakWall( Direction d )
{
  if( d == Direction::kNone )
  {
    throw std::invalid_argument( "Error: BreakWall() was given an "\
      "invalid Direction (kNone).\n");
  }

  try
  {
    if( DirectionCheck(d) == RoomBorder::kRoom )
    {
      throw std::logic_error( "Error: BreakWall() was given an "\
        "already-removed Wall.\n" );
    }
  }
  catch( const std::exception& e )
  {
    std::cout << e.what();
  }

  switch( d )
  {
    case( Direction::kNorth ):
      wall_north_ = false;
      break;
    case( Direction::kEast ):
      wall_east_ = false;
      break;
    case( Direction::kSouth ):
      wall_south_ = false;
      break;
    case( Direction::kWest ):
      wall_west_ = false;
      break;
    default:
      break;
  }
  return;
}

// This method returns:
//   RoomBorder::kExit if the direction has the exit,
//   RoomBorder::kRoom if the direction has another room, or
//   RoomBorder::kWall if the direction has a wall.
// An exception is thrown if:
//   Direction d is kNone (invalid_argument)
RoomBorder Room::DirectionCheck( Direction d ) const
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
