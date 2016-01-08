/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2016-01-08
 *
 * This C++ header file contains the LabyrinthMap class which creates, updates,
 * and displays a map of a given Labyrinth.
 *
 */

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

#include "../include/room_properties.hpp"
#include "../include/labyrinth.hpp"
#include "../include/labyrinth_map.hpp"

// This method returns whether a given Wall coordinate has a wall in the
// given direction.
// An exception is thrown if:
//   d is kNone (invalid_argument)
bool LabyrinthMapCoordinateBorder::IsWall( const Direction d ) const
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

// This method sets the Wall of a given Wall coordinate to either
// exist or not exist.
// May be used to set a wall which already exists, or remove a Wall
// which has already been removed.
// An exception is thrown if:
//   d is kNone (invalid_argument)
void LabyrinthMapCoordinateBorder::SetWall( const Direction d,
                                            const bool exists )
{
  switch( d )
  {
    case Direction::kNorth:
      wall_north_ = exists;
      return;
    case Direction::kEast:
      wall_east_ = exists;
      return;
    case Direction::kSouth:
      wall_south_ = exists;
      return;
    case Direction::kWest:
      wall_west_ = exists;
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
void LabyrinthMapCoordinateBorder::SetExit( const bool b )
{
  exit_ = b;
}

// This method returns the inhabitant of the current Room.
Inhabitant LabyrinthMapCoordinateRoom::GetInhabitant() const
{
  return i_;
}

// This method sets the current inhabitant of the map's Room.
// May be used to set the inhabitant to the same inhabitant, or to
// no inhabitant.
void LabyrinthMapCoordinateRoom::SetInhabitant( const Inhabitant inh )
{
  i_ = inh;
}

// This method returns the item in a given Room.
Item LabyrinthMapCoordinateRoom::GetItem() const
{
  return itm_;
}

// This method sets the item in a given map's Room.
// May be used to set the same item or remove a non-existent item.
void LabyrinthMapCoordinateRoom::SetItem( const Item i )
{
  itm_ = i;
}

// Parameterized constructor
// An exception is thrown if:
//   l is null (invalid_argument)
LabyrinthMap::LabyrinthMap( Labyrinth* l,
                            const size_t x_size,
                            const size_t y_size )
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
  std::unique_ptr<
    std::unique_ptr<std::unique_ptr<LabyrinthMapCoordinate>[]>
  []> map_temp_1 (new
    std::unique_ptr<std::unique_ptr<LabyrinthMapCoordinate>[]>[map_y_size_] );

  map_ = std::move( map_temp_1 );

  Coordinate c;
  for( size_t y = 0; y < map_y_size_; ++y )
  {
    std::unique_ptr<
      std::unique_ptr<LabyrinthMapCoordinate>
    []> map_temp_2 (new
      std::unique_ptr<LabyrinthMapCoordinate>[map_x_size_] );

    map_[y] = std::move( map_temp_2 );

    for( size_t x = 0; x < map_x_size_; ++x )
    {
      c.x = x;
      c.y = y;
      if( IsRoom(c) )
      {
        std::unique_ptr<LabyrinthMapCoordinate> map_temp_3
          (new LabyrinthMapCoordinateRoom);
        map_[y][x] = std::move( map_temp_3 );
      }
      else
      {
        std::unique_ptr<LabyrinthMapCoordinate> map_temp_3
          (new LabyrinthMapCoordinateBorder);
        map_[y][x] = std::move( map_temp_3 );
      }
    }
  }

  CleanBorders();
  UpdateBorders();
  UpdateRooms();
}

// This method displays a map of the current Labyrinth.
void LabyrinthMap::Display()
{
  UpdateBorders();
  UpdateRooms();

  LabelXAxis();

  for( size_t y = 0; y < map_y_size_; ++y )
  {
    LabelYAxis( y );
    for( size_t x = 0; x < map_x_size_; ++x )
    {
      Coordinate c(x, y);
      if( IsRoom(c) )
      {
        std::cout << DisplayRoom(c);
      }
      else
      {
        std::cout << DisplayBorder(c);

        // Doubles the horizontal draw distance of a Map Room (and the Borders
        // directly above/below a Map Room) from 1 to 2 characters
        if( x % 2 == 1 )
        {
          std::cout << DisplayBorder(c);
        }
      }
    }
    std::cout << std::endl;
  }

  std::cout << std::endl << std::endl;
  DisplayLegend();
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
void LabyrinthMap::LabyrinthToMap( Coordinate& c ) const
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
void LabyrinthMap::MapToLabyrinth( Coordinate& c ) const
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

// This private method cleans excess Map Borders.
// i.e.:
//   Borders on the exterior of the Labyrinth
//     ┼┴┼
//     ┼┬┼
//   Borders directly adjacent to a Room
//     ┌┬┐
//     ├ ┤
//     └┴┘
// Borders are NOT matched to the Labyrinth's layout; use UpdateBorders()
// for that.
void LabyrinthMap::CleanBorders()
{
  // Removing excess bounds on the exterior of the Labyrinth
  for( size_t x = 0; x < map_x_size_; ++x )
  {
    map_[0][x]->SetWall( Direction::kNorth, false );
    map_[map_y_size_-1][x]->SetWall( Direction::kSouth, false );
  }
  for( size_t y = 0; y < map_y_size_; ++y )
  {
    map_[y][0]->SetWall( Direction::kWest, false );
    map_[y][map_x_size_-1]->SetWall( Direction::kEast, false );
  }

  // Removing excess bounds directly adjacent to Rooms
  for( size_t y = 0; y < map_y_size_; ++y )
  {
    for( size_t x = 0; x < map_x_size_; ++x )
    {
      Coordinate c(x, y);
      if( !IsRoom(c) )
      {
        if( x % 2 == 1 )
        {
          map_[y][x]->SetWall( Direction::kNorth, false );
          map_[y][x]->SetWall( Direction::kSouth, false );
        }
        else if( y % 2 == 1 )
        {
          map_[y][x]->SetWall( Direction::kWest, false );
          map_[y][x]->SetWall( Direction::kEast, false );
        }
      }
    }
  }

}

// This private method updates the Map Borders by checking the contents
// of the Labyrinth.
// Borders in the Map but not in the Labyrinth will be removed from
// the Map; borders in the Labyrinth but not in the Map will not
// be added to the Map.
void LabyrinthMap::UpdateBorders()
{
  // Loops through the Labyrinth, not the Map
  for( size_t y = 0; y < y_size_; ++y )
  {
    for( size_t x = 0; x < x_size_; ++x )
    {
      Coordinate c_laby(x, y);
      Coordinate c_map = c_laby;
      try
      {
        LabyrinthToMap(c_map);
      }
      catch( const std::exception& e )
      {
        std::cout << e.what();
      }
      Coordinate c_edit_1 = c_map;
      Coordinate c_edit_2 = c_map;
      Coordinate c_edit_3 = c_map;

      RoomBorder rb_east;
      RoomBorder rb_south;
      try
      {
        rb_east  = l_->DirectionCheck( c_laby, Direction::kEast );
        rb_south = l_->DirectionCheck( c_laby, Direction::kSouth );
      }
      catch( const std::exception& e )
      {
        std::cout << e.what();
      }
      const bool east_border = (rb_east != RoomBorder::kRoom) ? true : false;
      const bool south_border = (rb_south != RoomBorder::kRoom) ? true : false;

      // Sets the east border of the relevant Map coordinate
      c_edit_1 = c_map;
      (c_edit_1.x)++;
      (c_edit_1.y)--;

      c_edit_2 = c_map;
      (c_edit_2.x)++;

      c_edit_3 = c_map;
      (c_edit_3.x)++;
      (c_edit_3.y)++;

      try
      {
        (MapCoordinateAt(c_edit_1)).SetWall( Direction::kSouth, east_border );
        (MapCoordinateAt(c_edit_2)).SetWall( Direction::kNorth, east_border );
        (MapCoordinateAt(c_edit_2)).SetWall( Direction::kSouth, east_border );
        (MapCoordinateAt(c_edit_3)).SetWall( Direction::kNorth, east_border );
      }
      catch( const std::exception& e )
      {
        std::cout << e.what();
      }

      // Sets the south border of the relevant Map coordinate
      c_edit_1 = c_map;
      (c_edit_1.y)++;
      (c_edit_1.x)--;

      c_edit_2 = c_map;
      (c_edit_2.y)++;

      c_edit_3 = c_map;
      (c_edit_3.y)++;
      (c_edit_3.x)++;

      try
      {
        (MapCoordinateAt(c_edit_1)).SetWall( Direction::kEast, south_border );
        (MapCoordinateAt(c_edit_2)).SetWall( Direction::kWest, south_border );
        (MapCoordinateAt(c_edit_2)).SetWall( Direction::kEast, south_border );
        (MapCoordinateAt(c_edit_3)).SetWall( Direction::kWest, south_border );
      }
      catch( const std::exception& e )
      {
        std::cout << e.what();
      }

    }  // For loop
  }  // For loop

}

// This private method updates the Map Rooms by checking the contents
// of the Labyrinth.
void LabyrinthMap::UpdateRooms()
{
  for( size_t y = 0; y < y_size_; ++y )
  {
    for( size_t x = 0; x < x_size_; ++x )
    {
      Coordinate c_laby(x, y);
      Coordinate c_map = c_laby;
      try
      {
        LabyrinthToMap(c_map);
      }
      catch( const std::exception& e )
      {
        std::cout << e.what();
      }

      try
      {
        MapCoordinateAt(c_map).SetInhabitant( l_->GetInhabitant(c_laby) );
      }
      catch( const std::exception& e )
      {
        std::cout << e.what();
      }

      try
      {
        MapCoordinateAt(c_map).SetItem( l_->GetItem(c_laby) );
      }
      catch( const std::exception& e )
      {
        std::cout << e.what();
      }
    }
  }

  return;
}

// This private method displays the x-axis label as well as numbering
// of the x-coordinates of Rooms.
// Only to be used by Display().
void LabyrinthMap::LabelXAxis() const
{
  // X label
  //
  // Magic number explanation:
  // Final length of the displayed map is around 3 times the labyrinth length
  // because the final map consists of Rooms which have 1 Border character
  // and 2 space characters.
  const size_t kXMiddle = (x_size_ * 3)/2 + 1;
  for( size_t i = 0; i < kXMiddle; ++i )
  {
    std::cout << " ";
  }
  std::cout << "     ";  // Alignment with y-axis label
  std::cout << "X" << std::endl << std::endl;

  // X-axis marks
  std::cout << "     ";  // Alignment with y-axis label
  for( size_t i = 0; i < x_size_; ++i )
  {
    if( i < 10 )  // Correcting for digit positions
    {
      std::cout << " ";
    }
    std::cout << " " << i;
  }
  std::cout << std::endl;

  return;
}

// This private method displays numbering of the y-coordinates of a Room
// as well as the y-axis label (if in the correct position), or padding
// if the row has no Rooms.
// Only to be used by Display().
// Should be called every time a row of the Map is printed.
void LabyrinthMap::LabelYAxis( const size_t y ) const
{
  // Y-axis label position
  const size_t kYMiddle = (y_size_)/2 + 1;

  // Y label
  if( y == kYMiddle )
  {
    std::cout << "Y";
  }
  else
  {
    std::cout << " ";
  }

  // Numbers rows with Rooms
  if( y % 2 == 1 )
  {
    if( y < 10 )  // Correcting for digit positions
    {
      std::cout << " ";
    }
    Coordinate c(1, y);
    MapToLabyrinth(c);
    std::cout << " " << c.y << " ";
  }
  else
  {
    std::cout << "    ";  // Alignment
  }
}

// This private method returns characters with the contents of the
// given Room Coordinate.
// Legend of symbols:
//   Inhabitants:
//     None:
//     Minotaur (live):  M
//     Minotaur (dead):  m
//     Mirror (intact):  O
//     Mirror (cracked): 0
//   Items:
//     None:
//     Bullet:   •
//     Treasure: T
// An exception is thrown if:
//   The Coordinate is outside of the Labyrinth (domain_error)
//   The Coordinate designates a Border (logic_error)
std::string LabyrinthMap::DisplayRoom( const Coordinate c ) const
{
  if( !WithinBoundsOfMap(c) )
  {
    throw std::domain_error( "Error: DisplayRoom() was given an invalid "\
      "Coordinate.\n" );
  }
  else if( !IsRoom(c) )
  {
    throw std::logic_error( "Error: DisplayRoom() was given a "\
      "Border Coordinate.\n" );
  }

  std::string s;

  Inhabitant inh = Inhabitant::kNone;
  try
  {
    inh = MapCoordinateAt(c).GetInhabitant();
  }
  catch( const std::exception& e )
  {
    std::cout << e.what();
  }
  switch( inh )
  {
    case Inhabitant::kMinotaur:
      s += "M";
      break;
    case Inhabitant::kMinotaurDead:
      s += "m";
      break;
    case Inhabitant::kMirror:
      s += "O";
      break;
    case Inhabitant::kMirrorCracked:
      s += "0";
      break;
    default:
      s += " ";
      break;
  }

  Item itm = Item::kNone;
  try
  {
    itm = MapCoordinateAt(c).GetItem();
  }
  catch( const std::exception& e )
  {
    std::cout << e.what();
  }
  switch( itm )
  {
    case Item::kBullet:
      s += "•";
      break;
    case Item::kTreasure:
      s += "T";
      break;
    default:
      s += " ";
      break;
  }

  return s;
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

  bool n;
  bool e;
  bool s;
  bool w;

  try
  {
    n = MapCoordinateAt(c).IsWall( Direction::kNorth );
    e = MapCoordinateAt(c).IsWall( Direction::kEast );
    s = MapCoordinateAt(c).IsWall( Direction::kSouth );
    w = MapCoordinateAt(c).IsWall( Direction::kWest );
  }
  catch( std::exception& e )
  {
    std::cout << e.what();
  }

  char borders_nesw[5] = "0000";

  if( n )
  {
    borders_nesw[0] = '1';
  }
  if( e )
  {
    borders_nesw[1] = '1';
  }
  if( s )
  {
    borders_nesw[2] = '1';
  }
  if( w )
  {
    borders_nesw[3] = '1';
  }

  // A true abomination lies ahead.
  // Please let me know if you have any alternative ideas so I can put this
  // out of its misery.
  //
  // Characters taken from the Unicode section of:
  // https://en.wikipedia.org/wiki/Box-drawing_character

  if( strcmp(borders_nesw, "0000") == 0 ) return " ";

  else if( strcmp(borders_nesw, "1000") == 0 ) return u8"╵";
  else if( strcmp(borders_nesw, "0100") == 0 ) return u8"╶";
  else if( strcmp(borders_nesw, "0010") == 0 ) return u8"╷";
  else if( strcmp(borders_nesw, "0001") == 0 ) return u8"╴";

  else if( strcmp(borders_nesw, "1100") == 0 ) return u8"└";
  else if( strcmp(borders_nesw, "1010") == 0 ) return u8"│";
  else if( strcmp(borders_nesw, "1001") == 0 ) return u8"┘";
  else if( strcmp(borders_nesw, "0110") == 0 ) return u8"┌";
  else if( strcmp(borders_nesw, "0101") == 0 ) return u8"─";
  else if( strcmp(borders_nesw, "0011") == 0 ) return u8"┐";

  else if( strcmp(borders_nesw, "1110") == 0 ) return u8"├";
  else if( strcmp(borders_nesw, "1101") == 0 ) return u8"┴";
  else if( strcmp(borders_nesw, "1011") == 0 ) return u8"┤";
  else if( strcmp(borders_nesw, "0111") == 0 ) return u8"┬";

  else if( strcmp(borders_nesw, "1111") == 0 ) return u8"┼";

  else
  {
    throw std::logic_error( "Error: DisplayBorder()'s check for "\
      "NESW values missed a possible value.\n" );
  }
}

// This private method displays a legend for the Map symbols.
void LabyrinthMap::DisplayLegend() const
{
  std::cout << "        LEGEND" << std::endl;
  std::cout << "┌─────────────────────┐" << std::endl;

  std::cout << "│ INHABITANTS         │" << std::endl;
  std::cout << "│ Minotaur (live):  M │" << std::endl;
  std::cout << "│ Minotaur (dead):  m │" << std::endl;
  std::cout << "│ Mirror (intact):  O │" << std::endl;
  std::cout << "│ Mirror (cracked): 0 │" << std::endl;

  std::cout << "│                     │" << std::endl;

  std::cout << "│ ITEMS               │" << std::endl;
  std::cout << "│ Bullet:           • │" << std::endl;
  std::cout << "│ Treasure:         T │" << std::endl;

  std::cout << "└─────────────────────┘" << std::endl;
}
