/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2016-01-01
 *
 * This C++ header file contains the implementation of a Coordinate struct
 * used by the Labyrinth and LabyrinthMap classes.
 *
 */

#pragma once

struct Coordinate
{
  size_t x;
  size_t y;

  // Default constructor
  Coordinate()
  {
    x = 0;
    y = 0;
  }

  // Parameterized constructor
  Coordinate( const size_t x_coordinate,
              const size_t y_coordinate )
  {
    x = x_coordinate;
    y = y_coordinate;
  }

  // Operator overload for ==
  bool operator==( const Coordinate& c ) const
  {
    return( x == c.x &&
            y == c.y );
  }

  // Operator overload for =
  Coordinate& operator=( const Coordinate& c )
  {
    x = c.x;
    y = c.y;
    return *this;
  }
};
