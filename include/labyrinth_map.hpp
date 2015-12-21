/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-12-12
 *
 * This C++ header file contains classes related to creating a LabyrinthMap
 * which creates, updates, and displays a map of a given Labyrinth.
 *
 */

#pragma once

#include <iostream>

#include "coordinate.hpp"
#include "room_properties.hpp"
#include "labyrinth.hpp"

// This class is a template for LabyrinthMapCoordinateBorder and
// LabyrinthMapCoordinateRoom to inherit from, so that an array can be
// made where any given element is either a Border or a Room.
class LabyrinthMapCoordinate
{
};

// This class contains necessary information about a given Border coordinate,
// so that a map can be displayed.
//
// A Border is the boundary between 2 Rooms, the corner between
// 4 Rooms, or a coordinate of the outermost wall.
// Borders/Walls are true by default to avoid working explicitly with:
//   The outer wall
class LabyrinthMapCoordinateBorder : public LabyrinthMapCoordinate
{
  public:

    // This method returns whether a given Wall coordinate has a wall in the
    // given direction.
    // An exception is thrown if:
    //   d is kNone (invalid_argument)
    bool IsWall( Direction d ) const;

    // This method removes the Wall of a given Wall coordinate.
    // May be used to remove a Wall which has already been removed.
    // An exception is thrown if:
    //   d is kNone (invalid_argument)
    void RemoveWall( Direction d );

    // This method returns whether a given Wall coordinate has the exit.
    bool IsExit() const;

    // This method sets whether or not a given Wall coordinate has the exit.
    // May be used to set an exit where the exit already exists, or to remove
    // an exit where none exists.
    void SetExit( bool b );

  private:
    bool wall_north_ = true;
    bool wall_east_  = true;
    bool wall_south_ = true;
    bool wall_west_  = true;

    bool exit_       = false;
};

// This class contains necessary information about a given Room coordinate,
// so that a map can be displayed.
class LabyrinthMapCoordinateRoom : public LabyrinthMapCoordinate
{
  public:

    // This method returns the inhabitant of the current Room.
    Inhabitant HasInhabitant() const;

    // This method sets the current inhabitant of the map's Room.
    // May be used to set the inhabitant to the same inhabitant, or to
    // no inhabitant.
    void SetInhabitant( Inhabitant inh );

    // This method returns whether the treasure is in a given Room.
    bool HasTreasure() const;

    // This method sets whether or not the treasure is in the given map's Room.
    // May be used to set the treasure when there is already a treasure in
    // the Room, or to remove the treasure when there is no treasure already.
    void SetTreasure( bool b );

  private:
    Inhabitant i_ = Inhabitant::kNone;
    bool treasure_ = false;
};

// This class contains a map of a Labyrinth.
class LabyrinthMap
{
  public:

    // Parameterized constructor
    // An exception is thrown if:
    //   l is null (invalid_argument)
    LabyrinthMap( Labyrinth* l,
                  unsigned int x_size,
                  unsigned int y_size );

    // Destructor
    ~LabyrinthMap();

    // This method displays a map of the current Labyrinth.
    void Display();

  private:

    Labyrinth* l_;
    unsigned int x_size_;
    unsigned int y_size_;

    // 2-d array of LabyrinthMapCoordinate pointers
    LabyrinthMapCoordinate*** map_;
    unsigned int map_x_size_;
    unsigned int map_y_size_;

    // This method returns true if the Coordinate designates a Room in the map,
    // and false if it designates a Border.
    // An exception is thrown if:
    //   The Coordinate is outside of the Map (domain_error)
    bool IsRoom( const Coordinate c ) const;

    // This method updates the map by checking the contents of the Labyrinth.
    void Update();
};
