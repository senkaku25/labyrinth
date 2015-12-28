/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-12-27
 *
 * This C++ file contains the implementation of the Labyrinth class, which uses
 * the Room class to create a 2-d mapping for a game.
 *
 */

#include <cmath>
#include <iostream>
#include <stdexcept>

#include "../include/room_properties.hpp"
#include "../include/room.hpp"
#include "../include/coordinate.hpp"
#include "../include/labyrinth.hpp"

// CONSTRUCTOR/DESTRUCTOR:

// Parameterized constructor
// An exception is thrown if:
//   A size of 0 is given (invalid_argument)
Labyrinth::Labyrinth( unsigned int x_size, unsigned int y_size )
{
  if( x_size == 0 )
  {
    if( y_size == 0 )
    {
      throw std::invalid_argument( "Error: Labyrinth() was given empty x and "\
        "y sizes." );
    }
    else
    {
      throw std::invalid_argument( "Error: Labyrinth() was given an empty "\
        "x size." );
    }
  }
  else if( y_size == 0 )
  {
    throw std::invalid_argument( "Error: Labyrinth() was given an empty "\
      "y size." );
  }

  rooms_ = new Room*[ y_size ];
  for( unsigned int i = 0; i < y_size; ++i )
  {
    rooms_[i] = new Room[ x_size ];
  }

  x_size_ = x_size;
  y_size_ = y_size;
}

// Destructor
Labyrinth::~Labyrinth()
{
  for( unsigned int i = 0; i < y_size_; ++i )
  {
    delete [] rooms_[i];
  }
  delete [] rooms_;
}

// SETUP:

// This method connects two Rooms by breaking their walls.
// An exception is thrown if:
//   The Rooms are already connected (logic_error)
//   The Rooms are the same (logic_error)
//   The Rooms are not adjacent (logic_error)
//   One or both Rooms are outside the Labyrinth (invalid_argument)
void Labyrinth::ConnectRooms( Coordinate rm_1, Coordinate rm_2 )
{
  if( rm_1 == rm_2 )
  {
    throw std::logic_error( "Error: ConnectRooms() was given the same "\
      "coordinate for the two Rooms." );
  }

  else if( !WithinBounds(rm_1) || !WithinBounds(rm_2) )
  {
    if( !WithinBounds(rm_1) )
    {
      if( !WithinBounds(rm_2) )
      {
        throw std::invalid_argument( "Error: ConnectRooms() was given invalid "\
          "coordinates for both rm_1 and rm_2." );
      }
      else
      {
        throw std::invalid_argument( "Error: ConnectRooms() was given "\
          "an invalid coordinate for rm_1." );
      }
    }

    else
    {
      throw std::invalid_argument( "Error: ConnectRooms() was given an "\
        "invalid coordinate for rm_2." );
    }
  }

  else if( !IsAdjacent(rm_1, rm_2) )
  {
    throw std::logic_error( "Error: ConnectRooms() was given two coordinates "\
      "which are not adjacent, and therefore cannot be connected." );
  }

  unsigned int x_distance = rm_2.x - rm_1.x;
  unsigned int y_distance = rm_2.y - rm_1.y;

  Direction break_wall_1;
  Direction break_wall_2;

  if( x_distance == 0 )
  {
    if( y_distance > 0 )  // rm_1 is north of rm_2
    {
      break_wall_1 = Direction::kSouth;
      break_wall_2 = Direction::kNorth;
    }
    else  // rm_1 is south of rm_2
    {
      break_wall_1 = Direction::kNorth;
      break_wall_2 = Direction::kSouth;
    }
  }

  else if( y_distance == 0 )
  {
    if( x_distance > 0 )  // rm_1 is west of rm_2
    {
      break_wall_1 = Direction::kEast;
      break_wall_2 = Direction::kWest;
    }
    else  // rm_1 is east of rm_2
    {
      break_wall_1 = Direction::kWest;
      break_wall_2 = Direction::kEast;
    }
  }

  else
  {
    throw std::logic_error( "Error: ConnectRooms() called IsAdjacent(), "\
      "which should have evaluated to false, but did not." );
  }

  RoomAt(rm_1).BreakWall(break_wall_1);
  RoomAt(rm_2).BreakWall(break_wall_2);
  return;
}

// PLAY:

// This method returns the type of RoomBorder in the given direction.
// An exception is thrown if:
//   The Room is outside the Labyrinth (invalid_argument)
//   Direction d is kNone (invalid_argument)
RoomBorder Labyrinth::DirectionCheck( Coordinate rm, Direction d ) const
{
  if( !WithinBounds(rm) )
  {
    throw std::invalid_argument( "Error: DirectionCheck() was given a "\
      "Coordinate outside of the Labyrinth." );
  }
  else if( d == Direction::kNone )
  {
    throw std::invalid_argument( "Error: DirectionCheck() was given an "\
      "invalid direction (kNone)." );
  }

  return RoomAt(rm).DirectionCheck(d);
}

// PRIVATE METHODS:

// This private method returns a reference to the Room at the given
// coordinate.
// An exception is thrown if:
//   The Room is outside the Labyrinth (invalid_argument)
Room& Labyrinth::RoomAt( Coordinate rm ) const
{
  if( !WithinBounds(rm) )
  {
    throw std::invalid_argument( "Error: RoomAt() was given an invalid "\
      "coordinate for rm." );
  }
  return rooms_[rm.x][rm.y];
}

// This private method returns true if the Room is within the bounds of
// the Labyrinth, and false otherwise.
bool Labyrinth::WithinBounds( Coordinate rm ) const
{
  return(    0 < rm.x    &&
          rm.x < x_size_ &&
             0 < rm.y    &&
          rm.y < y_size_ );
}

// This private method returns true if the two Rooms are adjacent, and
// false otherwise.
// An exception is thrown if:
//   One or both Rooms are outside the Labyrinth (invalid_argument)
//   The same Room is given twice (logic_error)
bool Labyrinth::IsAdjacent( Coordinate rm_1, Coordinate rm_2 ) const
{
  if( !WithinBounds(rm_1) )
  {
    if( !WithinBounds(rm_2) )
    {
      throw std::invalid_argument( "Error: IsAdjacent() was given invalid "\
      "coordinates for both rm_1 and rm_2." );
    }
    else
    {
      throw std::invalid_argument( "Error: IsAdjacent() was given an invalid "\
      "coordinate for rm_1." );
    }
  }
  else if( !WithinBounds(rm_2) )
  {
    throw std::invalid_argument( "Error: IsAdjacent() was given an invalid "\
      "coordinate for rm_2." );
  }

  if( rm_1 == rm_2 )
  {
    throw std::logic_error( "Error: IsAdjacent() was given the same "\
      "coordinate for the Rooms." );
  }

  unsigned int x_distance;
  if( rm_1.x > rm_2.x )
  {
    x_distance = rm_1.x - rm_2.x;
  }
  else
  {
    x_distance = rm_2.x - rm_1.x;
  }

  unsigned int y_distance;
  if( rm_1.y > rm_2.y )
  {
    y_distance = rm_1.y - rm_2.y;
  }
  else
  {
    y_distance = rm_2.y - rm_1.y;
  }

  if( ( x_distance == 0 && y_distance == 1 ) ||
      ( x_distance == 1 && y_distance == 0 ) )
  {
    return true;
  }
  return false;
}
