/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-09-19
 *
 * This C++ file contains the implementation of the Labyrinth class, which uses
 * the Room class to create a 2-d mapping for a game.
 *
 */
 
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
