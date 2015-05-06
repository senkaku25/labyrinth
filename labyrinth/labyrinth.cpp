/*
 *
 * Author: Jeffrey Leung
 * Date: 2015-05-05
 *
 * This program contains the implementation of a Labyrinth class, a maze which uses the
 * Room class as a building block.
 *
 */

#include <iostream>

#include "../room/room_properties.hpp"
#include "../room/room.hpp"
#include "labyrinth.hpp"

// This function recursively removes each room in the labyrinth, given a single arbitrary room.
static void LabyrinthDestroy( Room* r );

Labyrinth::Labyrinth()
{
  spawn1_ = NULL;
  spawn2_ = NULL;
}

// This function recursively removes each room in the labyrinth, given a single arbitrary room.
static void LabyrinthDestroy( Room* r )
{
  // Removing links to adjacent rooms

  if( r->north_ != NULL )
  {
    (r->north_)->south_ = NULL;
    LabyrinthDestroy( &func(), r->north_ );
  }

  if( r->east_ != NULL )
  {
    (r->east_)->west_ = NULL;
    LabyrinthDestroy( &func(), r->east_ );
  }

  if( r->south_ != NULL )
  {
    (r->south_)->north_ = NULL;
    LabyrinthDestroy( &func(), r->south_ );
  }

  if( r->west_ != NULL )
  {
    (r->west_)->east_ = NULL;
    LabyrinthDestroy( &func(), r->west_ );
  }

  delete r;
  return;
}

// This destructor utilizes the LabyrinthDestroy() function 
Labyrinth::~Labyrinth()
{
  LabyrinthSweep( spawn1_ );
}

// This method creates a single Room in heap memory and returns its address.
Room* Labyrinth::RoomCreate( inhabitant dark_thing,
                             item object,
                             direction exit )
{
  Room* r = new Room( dark_thing, object, exit, NULL, NULL, NULL, NULL );
  return r;
}

// This method connects two Rooms, which have not yet been connected in their directions.
void Labyrinth::ConnectRooms( Room* a, Room* b, direction a_to_b )
{
  unsigned int already_connected = 0;  // Flag variable

  if( a_to_b == north )
  {
    if( a->north_ == NULL && b->south_ == NULL )
    {
      a->north_ = b;
      b->south_ = a;
    }
    else
    {
      already_connected++;
    }
  }

  else if( a_to_b == east )
  {
    if( a->east_ == NULL && b->west_ == NULL )
    {
      a->east_ = b;
      b->west_ = a;
    }
    else
    {
      already_connected++;
    }
  }

  else if( a_to_b == south )
  {
    if( a->south_ == NULL && b->north_ == NULL )
    {
      a->south_ = b;
      b->north_ = a;
    }
    else
    {
      already_connected++;
    }
  }

  else if( a_to_b == west )
  {
    if( a->west_ == NULL && b->west_ == NULL )
    {
      a->west_ = b;
      b->south_ = a;
    }
    else
    {
      already_connected++;
    }
  }

  if( already_connected != 0 )
  {
    std::cout << "Error: ConnectRooms() was given two Rooms, at least one which was already " \
                 "connected to a Room in the intended direction of the new Room.\n" ;
    exit( 1 );
  }

  return;
}

// This method sets the spawn Rooms for a Labyrinth.
void Labyrinth::SetSpawnLocation( spawn_location s, Room* r )
{
  if( s == first )
  {
    spawn1_ = r;
  }
  else if( s == second )
  {
    spawn2_ = r;
  }

  return;
}

// This method sets a previous wall to become an exit.
void Labyrinth::SetExit( Room* r, direction d )
{
  if( d == north && r->north_ == NULL )
  {
    r->exit_ = north;
  }
  else if( d == east && r->east_ == NULL )
  {
    r->exit_ = east;
  }
  else if( d == south && r->south_ == NULL )
  {
    r->exit_ = south;
  }
  else if( d == west && r->west_ == NULL )
  {
    r->exit_ = west;
  }
  else
  {
    std::cout << "Error: SetExit() was told to place an exit where a Room connects " \
                 "to another Room.\n" ;
    exit( 1 );
  }

  return;
}

// This private method checks that the Labyrinth is properly created with two spawns,
// a treasure room, and an exit room.
void Labyrinth::Check( unsigned int num_of_rooms )
{
  unsigned int treasure = 0;
  unsigned int exit = 0;

  //TODO: Requires a expandable array of long integers to store the addresses of the Rooms.

  return;
}

// This method executes a game of Labyrinth.
void Labyrinth::StartGame()
{
  if( spawn1_ == NULL )
  {
    std::cout << "Error: StartGame() detected that spawn1_ was not set.\n" ;
    exit( 1 );
  }
  else if( spawn2_ == NULL )
  {
    std::cout << "Error: StartGame() detected that spawn2_ was not set.\n" ;
    exit( 1 );
  }

  //TODO

}
