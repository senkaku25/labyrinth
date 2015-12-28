/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-12-28
 *
 * This C++ header file contains the LabyrinthMap class which creates, updates,
 * and displays a map of a given Labyrinth.
 *
 */

#include <cstring>
#include <iostream>
#include <stdexcept>

#include "../include/room_properties.hpp"
#include "../include/labyrinth.hpp"
#include "../include/labyrinth_map.hpp"

// This method returns whether a given Wall coordinate has a wall in the
// given direction.
// An exception is thrown if:
//   d is kNone (invalid_argument)
bool LabyrinthMapCoordinateBorder::IsWall( Direction d ) const
{
  switch( d )
  {
    case Direction::kNorth:
      return wall_north_;
    case Direction::kEast:
      return wall_east_;
    case Direction::kSouth:
      return wall_south_;
    case Direction::kWest:
      return wall_west_;
    default:
      throw std::invalid_argument( "Error: IsWall() was given an invalid " \
        "direction (kNone).\n" );
  }
}

// This method creates the Wall of a given Wall coordinate.
// May be used to set a Wall which has already been set.
// An exception is thrown if:
//   d is kNone (invalid_argument)
void LabyrinthMapCoordinateBorder::RemoveWall( Direction d )
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
        "direction (kNone).\n" );
  }
  return;
}

// This method returns whether a given Wall coordinate has the exit.
bool LabyrinthMapCoordinateBorder::IsExit() const
{
  return exit_;
}

// This method sets whether or not a given Wall coordinate has the exit.
// May be used to set an exit where the exit already exists, or to remove
// an exit where none exists.
void LabyrinthMapCoordinateBorder::SetExit( bool b )
{
  exit_ = b;
}

// This method returns the inhabitant of the current Room.
Inhabitant LabyrinthMapCoordinateRoom::HasInhabitant() const
{
  return i_;
}

// This method sets the current inhabitant of the map's Room.
// May be used to set the inhabitant to the same inhabitant, or to
// no inhabitant.
void LabyrinthMapCoordinateRoom::SetInhabitant( Inhabitant inh )
{
  i_ = inh;
}

// This method returns whether the treasure is in a given Room.
bool LabyrinthMapCoordinateRoom::HasTreasure() const
{
  return treasure_;
}

// This method sets whether or not the treasure is in the given map's Room.
// May be used to set the treasure when there is already a treasure in
// the Room, or to remove the treasure when there is no treasure already.
void LabyrinthMapCoordinateRoom::SetTreasure( bool b )
{
  treasure_ = b;
}

// Parameterized constructor
// An exception is thrown if:
//   l is null (invalid_argument)
LabyrinthMap::LabyrinthMap( Labyrinth* l,
                            unsigned int x_size,
                            unsigned int y_size )
{
  if( l == nullptr )
  {
    throw std::invalid_argument( "Error: LabyrinthMap() was given an "\
      "invalid (null) pointer for the Labyrinth.\n" );
  }

  l_ = l;
  x_size_ = x_size;
  y_size_ = y_size;

  map_x_size_ = x_size * 2 + 1;
  map_y_size_ = y_size * 2 + 1;

  // Creation of the map array
  map_ = new LabyrinthMapCoordinate**[ map_y_size_ ];
  Coordinate c;
  for( unsigned int y = 0; y < map_y_size_; ++y )
  {
    map_[y] = new LabyrinthMapCoordinate*[ map_x_size_ ];
    for( unsigned int x = 0; x < map_x_size_; ++x )
    {
      c.x = x;
      c.y = y;
      if( IsRoom(c) )
      {
        map_[y][x] = new LabyrinthMapCoordinateRoom;
      }
      else
      {
        map_[y][x] = new LabyrinthMapCoordinateBorder;
      }
    }
  }

  // Removing excess bounds on the exterior of the Labyrinth
  for( unsigned int x = 0; x < map_x_size_; ++x )
  {
    map_[0][x]->RemoveWall( Direction::kNorth );
    map_[map_y_size_-1][x]->RemoveWall( Direction::kSouth );
  }
  for( unsigned int y = 0; y < map_y_size_; ++y )
  {
    map_[y][0]->RemoveWall( Direction::kWest );
    map_[y][map_x_size_-1]->RemoveWall( Direction::kEast );
  }

  // Sets the Borders to emulate the Labyrinth
  Coordinate c_laby;
  Coordinate c_map;
  Coordinate c_mapborder_remove;
  RoomBorder rb;
  // Loops through the labyrinth
  for( unsigned int y = 0; y < y_size_; ++y )
  {
    for( unsigned int x = 0; x < x_size_; ++x )
    {
      c_laby.x = x;
      c_laby.y = y;
      c_map = c_laby;
      try
      {
        LabyrinthToMap(c_map);
      }
      catch( const std::exception& e )
      {
        std::cout << e.what();
      }

      // Removes the east border of the relevant Map coordinate if necessary
      try
      {
        rb = l_->DirectionCheck(c_laby, Direction::kEast);
      }
      catch( const std::exception& e )
      {
        std::cout << e.what();
      }
      if( rb == RoomBorder::kRoom )
      {
        c_mapborder_remove = c_map;
        (c_mapborder_remove.x)++;

        (c_mapborder_remove.y)--;
        (MapCoordinateAt(c_mapborder_remove)).RemoveWall( Direction::kSouth );

        (c_mapborder_remove.y)++;
        (MapCoordinateAt(c_mapborder_remove)).RemoveWall( Direction::kNorth );
        (MapCoordinateAt(c_mapborder_remove)).RemoveWall( Direction::kSouth );

        (c_mapborder_remove.y)++;
        (MapCoordinateAt(c_mapborder_remove)).RemoveWall( Direction::kNorth );
      }

      // Removes the south border of the relevant Map coordinate if necessary
      try
      {
        rb = l_->DirectionCheck(c_laby, Direction::kSouth);
      }
      catch( const std::exception& e )
      {
        std::cout << e.what();
      }
      if( rb == RoomBorder::kRoom )
      {
        c_mapborder_remove = c_map;
        (c_mapborder_remove.y)++;

        (c_mapborder_remove.x)--;
        (MapCoordinateAt(c_mapborder_remove)).RemoveWall( Direction::kEast );

        (c_mapborder_remove.x)++;
        (MapCoordinateAt(c_mapborder_remove)).RemoveWall( Direction::kWest );
        (MapCoordinateAt(c_mapborder_remove)).RemoveWall( Direction::kEast );

        (c_mapborder_remove.x)++;
        (MapCoordinateAt(c_mapborder_remove)).RemoveWall( Direction::kWest );
      }
    }
  }

  //Update();  //TODO Uncomment when Update() is implemented
}

// Destructor
LabyrinthMap::~LabyrinthMap()
{
  for( unsigned int y = 0; y < map_y_size_; ++y )
  {
    for( unsigned int x = 0; x < map_x_size_; ++x )
    {
      delete map_[y][x];
    }
    delete [] map_[y];
  }
  delete [] map_;
}

// This method displays a map of the current Labyrinth.
void LabyrinthMap::Display()
{
  Coordinate c;
  for( unsigned int y = 0; y < map_y_size_; ++y )
  {
    for( unsigned int x = 0; x < map_x_size_; ++x )
    {
      c.x = x;
      c.y = y;
      if( IsRoom(c) )
      {
        std::cout << " ";
      }
      else
      {
        std::cout << DisplayBorder(c);
      }
    }
    std::cout << std::endl;
  }

  return;
}

// This private method returns true if the Coordinate is within the bounds
// of the Map, and false otherwise.
bool LabyrinthMap::WithinBoundsOfMap( const Coordinate c ) const
{
  return ( c.x < map_x_size_ &&
           c.y < map_y_size_ );
}

// This private method returns true if the Coordinate designates a Room
// in the map, and false if it designates a Border.
// An exception is thrown if:
//   The Coordinate is outside of the Map (domain_error)
bool LabyrinthMap::IsRoom( const Coordinate c ) const
{
  if( WithinBoundsOfMap(c) )
  {
    return c.x % 2 == 1 && c.y % 2 == 1;
  }
  else
  {
    throw std::domain_error( "Error: IsRoom() was given a Coordinate "\
      "outside of the Map.\n" );
  }
}

// This private method returns a reference to the Map Coordinate at
// the given Coordinate.
// An exception is thrown if:
//   The Coordinate is outside of the Map (domain_error)
LabyrinthMapCoordinate&
LabyrinthMap::MapCoordinateAt( const Coordinate c ) const
{
  if( !WithinBoundsOfMap(c) )
  {
    throw std::domain_error( "Error: MapCoordinateAt() was given a "\
      "Coordinate outside of the Map.\n" );
  }

  return *(map_[c.y][c.x]);
}

// This private method converts a Labyrinth Coordinate to the same
// location in the Map.
// An exception is thrown if:
//   The Coordinate is outside of the Labyrinth (invalid_argument)
void LabyrinthMap::LabyrinthToMap( Coordinate c ) const
{
  if( c.x < x_size_ &&
      c.y < y_size_ )
  {
    c.x = c.x * 2 + 1;
    c.y = c.y * 2 + 1;
  }
  else
  {
    throw std::invalid_argument( "Error: LabyrinthToMap() was given a "\
      "Coordinate outside of the Labyrinth.\n" );
  }
}

// This private method converts a Map Room Coordinate to the same
// Room in the Labyrinth.
// An exception is thrown if:
//   The Coordinate is outside of the Labyrinth (domain_error)
//   The Coordinate designates a border (logic_error)
void LabyrinthMap::MapToLabyrinth( Coordinate c ) const
{
  if( !WithinBoundsOfMap(c) )
  {
    throw std::domain_error( "Error: MapToLabyrinth() was given a "\
      "Coordinate outside of the LabyrinthMap.\n" );
  }
  else if( !IsRoom(c) )
  {
    throw std::logic_error( "Error: MapToLabyrinth() was given a "\
      "Coordinate designating a Border, not a Room.\n" );
  }
  else
  {
    c.x = (c.x - 1) / 2;
    c.y = (c.y - 1) / 2;
  }
}

// This private method returns a character representing the given
// Border Coordinate.
// An exception is thrown if:
//   The Coordinate is outside of the Labyrinth (domain_error)
//   The Coordinate designates a Room (logic_error)
std::string LabyrinthMap::DisplayBorder( const Coordinate c ) const
{
  if( !WithinBoundsOfMap(c) )
  {
    throw std::domain_error( "Error: DisplayBorder() was given an invalid "\
      "Coordinate.\n" );
  }
  else if( IsRoom(c) )
  {
    throw std::logic_error( "Error: DisplayBorder() was given a "\
      "Room Coordinate.\n" );
  }

  RoomBorder rb_n;
  RoomBorder rb_e;
  RoomBorder rb_s;
  RoomBorder rb_w;

  try
  {
    MapToLabyrinth( c );
    rb_n = l_->DirectionCheck( c, Direction::kNorth );
    rb_e = l_->DirectionCheck( c, Direction::kEast );
    rb_s = l_->DirectionCheck( c, Direction::kSouth );
    rb_w = l_->DirectionCheck( c, Direction::kWest );
  }
  catch( std::exception& e )
  {
    std::cout << e.what();
  }

  char borders_nesw[5] = "0000";

  if( rb_n != RoomBorder::kRoom )
  {
    borders_nesw[0] = '1';
  }
  if( rb_e != RoomBorder::kRoom )
  {
    borders_nesw[1] = '1';
  }
  if( rb_s != RoomBorder::kRoom )
  {
    borders_nesw[2] = '1';
  }
  if( rb_w != RoomBorder::kRoom )
  {
    borders_nesw[3] = '1';
  }

  // A true abomination lies ahead.
  // Please let me know if you have any alternative ideas so I can put this
  // out of its misery.
  //
  // Characters taken from the Unicode section of:
  // https://en.wikipedia.org/wiki/Box-drawing_character

  if( strcmp(borders_nesw, "0000") ) return " ";

  else if( strcmp(borders_nesw, "1000") ) return u8"╵";
  else if( strcmp(borders_nesw, "0100") ) return u8"╶";
  else if( strcmp(borders_nesw, "0010") ) return u8"╷";
  else if( strcmp(borders_nesw, "0001") ) return u8"╴";

  else if( strcmp(borders_nesw, "1100") ) return u8"└";
  else if( strcmp(borders_nesw, "1010") ) return u8"│";
  else if( strcmp(borders_nesw, "1001") ) return u8"┘";
  else if( strcmp(borders_nesw, "0110") ) return u8"┌";
  else if( strcmp(borders_nesw, "0101") ) return u8"─";
  else if( strcmp(borders_nesw, "0011") ) return u8"┐";

  else if( strcmp(borders_nesw, "1110") ) return u8"├";
  else if( strcmp(borders_nesw, "1101") ) return u8"┴";
  else if( strcmp(borders_nesw, "1011") ) return u8"┤";
  else if( strcmp(borders_nesw, "0111") ) return u8"┬";

  else if( strcmp(borders_nesw, "1111") ) return u8"┼";

  else
  {
    throw std::logic_error( "Error: DisplayBorder()'s check for "\
      "NESW values missed a possible value.\n" );
  }
}
//TODO Implementation of labyrinth_map.hpp
