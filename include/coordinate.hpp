/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-12-25
 *
 * This C++ header file contains the implementation of a Coordinate struct
 * used by the Labyrinth class.
 *
 */

#pragma once

struct Coordinate
{
  unsigned int x;
  unsigned int y;

  // Default constructor
  Coordinate()
  {
    x = 0;
    y = 0;
  }

  // Parameterized constructor
  Coordinate( unsigned int x_coordinate,
              unsigned int y_coordinate )
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
