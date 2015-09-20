/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-09-19
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

// Parameterized constructor
// An exception is thrown if:
//   A size of 0 is given (invalid_argument)
Labyrinth::Labyrinth( unsigned int x_size, unsigned int y_size )
{
  bool x_empty;
  if( x_size == 0 )
  {
    x_empty = true;
  }
  else
  {
    x_empty = false;
  }
  
  bool y_empty;
  if( y_size == 0 )
  {
    y_empty = true;
  }
  else
  {
    y_empty = false;
  }
  
  if( x_empty && y_empty )
  {
    throw std::invalid_argument( "Error: Labyrinth() was given empty x and "\
      "y sizes." );  
  }
  else if( x_empty )
  {
    throw std::invalid_argument( "Error: Labyrinth() was given an empty "\
      "x size." );
  }
  else if( y_empty )
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

// PRIVATE METHODS:

// This private method returns true if the Room is within the bounds of
// the Labyrinth, and false otherwise.
bool Labyrinth::WithinBounds( Coordinate rm )
{
  if(    0 < rm.x    &&
      rm.x < x_size_ &&
         0 < rm.y    &&
      rm.y < y_size_ )
  {
    return true;
  }
  return false;
}

// This private method returns true if the two Rooms are adjacent, and
// false otherwise.
// An exception is thrown if:
//   One or both Rooms are outside the Labyrinth (invalid_argument)
//   The same Room is given twice (logic_error)
bool Labyrinth::IsAdjacent( Coordinate rm_1, Coordinate rm_2 )
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
      "coordinate for the Rooms to connect." );
  }
  
  unsigned int x_distance = abs( rm_1.x - rm_2.x );
  unsigned int y_distance = abs( rm_1.y - rm_2.y );
  
  if( ( x_distance == 0 && y_distance == 1 ) ||
      ( x_distance == 1 && y_distance == 0 ) )
  {
    return true;
  }
  return false; 
}
