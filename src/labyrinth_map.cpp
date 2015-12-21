/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-12-21
 *
 * This C++ header file contains the LabyrinthMap class which creates, updates,
 * and displays a map of a given Labyrinth.
 *
 */

#include <stdexcept>

#include "../include/labyrinth_map.hpp"

// This method returns whether a given Wall coordinate has a wall in the
// given direction.
// An exception is thrown if:
//   d is kNone (invalid_argument)
bool LabyrinthMapCoordinateBorder::IsWall( Direction d ) const
{
  switch( d )
  {
    case Direction::kNorth:
      return wall_north_;
    case Direction::kEast:
      return wall_east_;
    case Direction::kSouth:
      return wall_south_;
    case Direction::kWest:
      return wall_west_;
    default:
      throw std::invalid_argument( "Error: IsWall() was given an invalid " \
        "direction (kNone)." );
  }
}

// This method creates the Wall of a given Wall coordinate.
// May be used to set a Wall which has already been set.
// An exception is thrown if:
//   d is kNone (invalid_argument)
void LabyrinthMapCoordinateBorder::RemoveWall( Direction d )
{
  switch( d )
  {
    case Direction::kNorth:
      wall_north_ = false;
      return;
    case Direction::kEast:
      wall_east_ = false;
      return;
    case Direction::kSouth:
      wall_south_ = false;
      return;
    case Direction::kWest:
      wall_west_ = false;
      return;
    default:
      throw std::invalid_argument( "Error: SetWall() was given an invalid "\
        "direction (kNone)." );
  }
  return;
}

// This method returns whether a given Wall coordinate has the exit.
bool LabyrinthMapCoordinateBorder::IsExit() const
{
  return exit_;
}

// This method sets whether or not a given Wall coordinate has the exit.
// May be used to set an exit where the exit already exists, or to remove
// an exit where none exists.
void LabyrinthMapCoordinateBorder::SetExit( bool b )
{
  exit_ = b;
}

// This method returns the inhabitant of the current Room.
Inhabitant LabyrinthMapCoordinateRoom::HasInhabitant() const
{
  return i_;
}

// This method sets the current inhabitant of the map's Room.
// May be used to set the inhabitant to the same inhabitant, or to
// no inhabitant.
void LabyrinthMapCoordinateRoom::SetInhabitant( Inhabitant inh )
{
  i_ = inh;
}

// This method returns whether the treasure is in a given Room.
bool LabyrinthMapCoordinateRoom::HasTreasure() const
{
  return treasure_;
}

// This method sets whether or not the treasure is in the given map's Room.
// May be used to set the treasure when there is already a treasure in
// the Room, or to remove the treasure when there is no treasure already.
void LabyrinthMapCoordinateRoom::SetTreasure( bool b )
{
  treasure_ = b;
}

// Parameterized constructor
// An exception is thrown if:
//   l is null (invalid_argument)
LabyrinthMap::LabyrinthMap( Labyrinth* l,
                            unsigned int x_size,
                            unsigned int y_size )
{
  if( l == nullptr )
  {
    throw std::invalid_argument( "Error: LabyrinthMap() was given an "\
      "invalid (null) pointer for the Labyrinth." );
  }

  l_ = l;
  x_size_ = x_size;
  y_size_ = y_size;

  map_x_size_ = x_size * 2 + 1;
  map_y_size_ = y_size * 2 + 1;

  // Creation of the map array
  map_ = new LabyrinthMapCoordinate**[ map_y_size_ ];
  for( unsigned int i = 0; i < map_y_size_; ++i )
  {
    map_[i] = new LabyrinthMapCoordinate*[ map_x_size_ ];
  }

  // Creation of the individual map rooms/borders
  for( unsigned int y = 0; y < map_y_size_; ++y )
  {
    for( unsigned int x = 0; x < map_x_size_; ++x )
    {
      if( IsRoom( x, y ) )
      {
        map_[x][y] = new LabyrinthMapCoordinateRoom;
      }
      else
      {
        map_[x][y] = new LabyrinthMapCoordinateBorder;
      }
    }
  }

  //TODO Remove excess bounds on the exterior of the Labyrinth
  //TODO Initialization of the border coordinates


  //Update();  //TODO Uncomment when Update() is implemented
}

// This method returns true if the Coordinate is within the bounds
// of the Map, and false otherwise.
bool WithinBoundsOfMap( const Coordinate c ) const
{
  return ( -1 < c.x && c.x < map_x_size_ &&
           -1 < c.y && c.y < map_y_size_ );
}

// This private method returns true if the coordinate designates a Room in
// the map, and false if it designates a Border.
// An exception is thrown if:
//   The coordinate is outside of the Map (domain_error)
bool LabyrinthMap::IsRoom( const Coordinate c ) const
{
  if( WithinBoundsOfMap(c) )
  {
    return c.x % 2 == 1 && c.y % 2 == 1;
  }
  else
  {
    throw std::domain_error( "Error: IsRoom() was given a Coordinate "\
      "outside of the Map." );
  }
}

//TODO Implementation of labyrinth_map.hpp
