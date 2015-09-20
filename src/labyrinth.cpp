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

#include "../include/room_properties.hpp"
#include "../include/room.hpp"
#include "../include/labyrinth.hpp"

// Parameterized constructor
Labyrinth::Labyrinth( unsigned int x_size, unsigned int y_size )
{
  rooms_ = new Room*[ y_size ];
  for( unsigned int i = 0; i < x_size; ++i )
  {
    rooms_[i] = new Room[ x_size ];
  }
  
  x_size_ = x_size;
  y_size_ = y_size;
}
