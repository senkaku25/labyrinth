/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-11-02
 *
 * This C++ header file contains classes related to creating a LabyrinthMap
 * which creates, updates, and displays a map of a given Labyrinth.
 *
 */

#pragma once

#include <iostream>

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
// Borders/Walls are true by default to avoid working explicitly with:
//   The outer wall
class LabyrinthMapCoordinateBorder : LabyrinthMapCoordinate
{
  public:

    // This method removes the Wall of a given Wall coordinate.
    // May be used to remove a Wall which has already been removed.
    // An exception is thrown if:
    //   d is kNone (invalid_argument)
    void SetWall( Direction d );

  private:
    bool wall_north_ = true;
    bool wall_east_  = true;
    bool wall_south_ = true;
    bool wall_west_  = true;

    bool exit_       = false;
};

// This class contains necessary information about a given Room coordinate,
// so that a map can be displayed.
class LabyrinthMapCoordinateRoom : LabyrinthMapCoordinate
{
  public:

    // This method sets the current inhabitant of the map's Room.
    // May be used to set the inhabitant to the same inhabitant, or to
    // no inhabitant.
    void SetInhabitant( Inhabitant inh );

    // This method places the treasure in the map's Room.
    // May be used when there is already a treasure in the map's Room.
    void SetTreasure();

    // This method removes the treasure from the Room.
    // An exception is thrown if:
    //   The treasure is not in the map's Room (logic_error)
    void RemoveTreasure();

  private:
    Inhabitant i_   = Inhabitant::kNone;
    bool treasure_ = false;
};

// This class contains a map of a Labyrinth.
class LabyrinthMap
{
  public:

    // Parameterized constructor
    LabyrinthMap( Labyrinth* l,
                  unsigned int x_size,
                  unsigned int y_size );

    // Destructor
    ~LabyrinthMap();

    // This method displays a map of the current Labyrinth.
    void Display();

  private:

    Labyrinth* l;

    unsigned int x_size_;
    unsigned int y_size_;

    unsigned int map_x_size_;
    unsigned int map_y_size_;

    LabyrinthMapCoordinate** map_;

    // This method returns true if x and y in the map array designate a Room,
    // and false if they designate a Border.
    bool IsRoom( unsigned int x, unsigned int y ) const;

    // This method updates the map by checking the contents of the Labyrinth.
    void Update();
};
