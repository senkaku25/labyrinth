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

// This method sets the current inhabitant of the map's Room.
// May be used to set the inhabitant to the same inhabitant, or to
// no inhabitant.
void LabyrinthMapCoordinateRoom::SetInhabitant( Inhabitant inh )
{
  i_ = inh;
}

// This method places the treasure in the map's Room.
// May be used when there is already a treasure in the map's Room.
void LabyrinthMapCoordinateRoom::SetTreasure()
{
  treasure_ = true;
}

// This method removes the treasure from the Room.
// May be used when there is no treasure in the map's Room.
void LabyrinthMapCoordinateRoom::RemoveTreasure()
{
  treasure_ = false;
}

//TODO Implementation of labyrinth_map.hpp
