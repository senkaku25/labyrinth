/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-11-06
 *
 * This C++ header file contains the LabyrinthMap class which creates, updates,
 * and displays a map of a given Labyrinth.
 *
 */

#include <stdexcept>

#include "../include/labyrinth_map.hpp"

// This method creates the Wall of a given Wall coordinate.
// May be used to set a Wall which has already been set.
// An exception is thrown if:
//   d is kNone (invalid_argument)
void LabyrinthMapCoordinateBorder::SetWall( Direction d )
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

//TODO Implementation of labyrinth_map.hpp
