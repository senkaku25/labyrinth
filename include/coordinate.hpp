/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-09-19
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
  
  // Operator overload for ==
  bool operator==( const Coordinate& c ) const
  {
    return( x == c.x &&
            y == c.y );
  }
};
