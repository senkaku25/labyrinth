/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2016-02-01
 *
 * This C++ file contains the implementation of the Labyrinth class, which uses
 * the Room class to create a 2-d mapping for a game.
 *
 */

#include <cmath>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "../include/room_properties.hpp"
#include "../include/room.hpp"
#include "../include/coordinate.hpp"
#include "../include/labyrinth.hpp"

// CONSTRUCTOR/DESTRUCTOR:

// Parameterized constructor
// An exception is thrown if:
//   A size of 0 is given (domain_error)
//   An x or y size greater than the maximum is given (domain_error)
Labyrinth::Labyrinth( const size_t x_size, const size_t y_size ) :
  x_size_(x_size), y_size_(y_size)
{
  if( x_size == 0 )
  {
    if( y_size == 0 )
    {
      throw std::domain_error( "Error: Labyrinth() was given empty x and "\
        "y sizes.\n" );
    }
    else
    {
      throw std::domain_error( "Error: Labyrinth() was given an empty "\
        "x size.\n" );
    }
  }
  else if( y_size == 0 )
  {
    throw std::domain_error( "Error: Labyrinth() was given an empty "\
      "y size.\n" );
  }

  if( x_size > MAX_X_SIZE_ )
  {
    if( y_size > MAX_Y_SIZE_ )
    {
      throw std::domain_error( "Error: Labyrinth() was given x and y sizes "\
        "greater than the maximum (20).\n" );
    }
    else
    {
      throw std::domain_error( "Error: Labyrinth() was given an x size "\
        "greater than the maximum (20).\n" );
    }
  }
  else if( y_size > MAX_Y_SIZE_ )
  {
    throw std::domain_error( "Error: Labyrinth() was given a y size "\
      "greater than the maximum (20).\n" );
  }

  auto rooms_temp_1 = std::make_unique<std::unique_ptr<Room[]>[]>(y_size);

  rooms_ = std::move( rooms_temp_1 );
  for( size_t i = 0; i < y_size; ++i )
  {
    auto rooms_temp_2 = std::make_unique<Room[]>(x_size);
    rooms_[i] = std::move( rooms_temp_2 );
  }

}

// SETUP:

// This method connects two Rooms by breaking their walls.
// An exception is thrown if:
//   One or both Rooms are outside the Labyrinth (domain_error)
//   The Rooms are not adjacent (logic_error)
//   The Rooms are the same (logic_error)
//   The Rooms are already connected (logic_error)
void Labyrinth::ConnectRooms( const Coordinate rm_1, const Coordinate rm_2 )
{
  if( !WithinBounds(rm_1) || !WithinBounds(rm_2) )
  {
    if( !WithinBounds(rm_1) )
    {
      if( !WithinBounds(rm_2) )
      {
        throw std::domain_error( "Error: ConnectRooms() was given invalid "\
          "coordinates for both rm_1 and rm_2.\n" );
      }
      else
      {
        throw std::domain_error( "Error: ConnectRooms() was given "\
          "an invalid coordinate for rm_1.\n" );
      }
    }

    else
    {
      throw std::domain_error( "Error: ConnectRooms() was given an "\
        "invalid coordinate for rm_2.\n" );
    }
  }
  else if( !IsAdjacent(rm_1, rm_2) )
  {
    throw std::logic_error( "Error: ConnectRooms() was given two coordinates "\
      "which are not adjacent, and therefore cannot be connected.\n" );
  }
  else if( rm_1 == rm_2 )
  {
    throw std::logic_error( "Error: ConnectRooms() was given the same "\
      "coordinate for the two Rooms.\n" );
  }

  int x_distance = (int)(rm_2.x) - (int)(rm_1.x);
  int y_distance = (int)(rm_2.y) - (int)(rm_1.y);

  Direction break_wall_1;
  Direction break_wall_2;

  if( x_distance == 0 )
  {
    if( y_distance > 0 )  // rm_1 is north of rm_2
    {
      break_wall_1 = Direction::kSouth;
      break_wall_2 = Direction::kNorth;
    }
    else  // rm_1 is south of rm_2
    {
      break_wall_1 = Direction::kNorth;
      break_wall_2 = Direction::kSouth;
    }
  }

  else if( y_distance == 0 )
  {
    if( x_distance > 0 )  // rm_1 is west of rm_2
    {
      break_wall_1 = Direction::kEast;
      break_wall_2 = Direction::kWest;
    }
    else  // rm_1 is east of rm_2
    {
      break_wall_1 = Direction::kWest;
      break_wall_2 = Direction::kEast;
    }
  }

  if( RoomAt(rm_1).DirectionCheck(break_wall_1) == RoomBorder::kRoom )
  {
    throw std::logic_error( "Error: ConnectRooms() was given two Rooms "\
      "which are already connected.\n" );
  }

  RoomAt(rm_1).BreakWall(break_wall_1);
  RoomAt(rm_2).BreakWall(break_wall_2);
  return;
}

// This method sets the primary (initial) spawn Room.
// An exception is thrown if:
//   The Room is outside the Labyrinth (domain_error)
void Labyrinth::SetSpawn1( const Coordinate rm )
{
  if( !WithinBounds(rm) )
  {
    throw std::domain_error( "Error: SetSpawn1() was given an "\
      "invalid Coordinate.\n" );
  }

  spawn_1_ = rm;
  return;
}


// This method sets the secondary spawn Room.
// An exception is thrown if:
//   The Room is outside the Labyrinth (domain_error)
void Labyrinth::SetSpawn2( const Coordinate rm )
{
  if( !WithinBounds(rm) )
  {
    throw std::domain_error( "Error: SetSpawn2() was given an "\
      "invalid Coordinate.\n" );
  }

  spawn_2_ = rm;
  return;
}

// This method sets the exit of the Labyrinth on a Wall.
// An exception is thrown if:
//   The Room is outside the Labyrinth (domain_error)
//   The Direction is invalid (kNone) (invalid_argument)
//   The Direction has another Room (invalid_argument)
//   The Exit has already been set (logic_error)
void Labyrinth::SetExit( const Coordinate rm, const Direction d )
{
  if( !WithinBounds(rm) )
  {
    throw std::domain_error( "Error: SetExit() was given an "\
      "invalid Coordinate.\n" );
  }
  else if( d == Direction::kNone )
  {
    throw std::invalid_argument( "Error: SetExit() was given an "\
      "invalid direction (kNone).\n" );
  }

  auto rb = RoomBorder::kRoom;
  try
  {
    rb = RoomAt(rm).DirectionCheck(d);
  }
  catch( const std::exception& e )
  {
    std::cout << e.what();
    return;
  }
  if (rb == RoomBorder::kRoom)
  {
    throw std::invalid_argument( "Error: SetExit() was given a "\
      "direction with a Room, not a Wall.\n" );
  }

  if( exit_set_ )
  {
    throw std::logic_error( "Error: SetExit() was called when an exit "\
      "already exists.\n" );
  }

  try
  {
    RoomAt(rm).CreateExit(d);
  }
  catch( const std::exception& e )
  {
    std::cout << e.what();
    return;
  }

  exit_set_ = true;
  return;
}

// This method places an Inhabitant in a Room.
// Cannot change an existing Inhabitant; use the EnemyAttacked() method
// for that.
// An exception is thrown if:
//   The Room is outside the Labyrinth (domain_error)
//   Inhabitant inh is a null Inhabitant (i.e. Inhabitant::kNone)
//     (invalid_argument)
//   The Inhabitant of the Room has already been set (logic_error)
void Labyrinth::SetInhabitant( const Coordinate rm, const Inhabitant inh )
{
  if( !WithinBounds(rm) )
  {
    throw std::domain_error( "Error: SetInhabitant() was given an "\
      "invalid Coordinate.\n" );
  }
  else if( inh == Inhabitant::kNone )
  {
    throw std::invalid_argument( "Error: SetInhabitant() was given a null "\
      "Inhabitant.\n" );
  }
  else if( RoomAt(rm).GetInhabitant() != Inhabitant::kNone )
  {
    throw std::logic_error( "Error: SetInhabitant() cannot replace an "\
      "existing Inhabitant; EnemyAttacked() should be used instead.\n" );
  }

  RoomAt(rm).SetInhabitant(inh);
  return;
}

// This method places an Item in a Room.
// Cannot change an existing Item; use the TakeItem() method for that.
// An exception is thrown if:
//   The Room is outside the Labyrinth (domain_error)
//   Item itm is a null Item (i.e. Item::kNone) (invalid_argument)
//   The Item of the Room has already been set (logic_error)
//   Item itm is a Treasure but the Treasure has already been placed
//     in another room (logic_error)
void Labyrinth::SetItem( const Coordinate rm, const Item itm )
{
  if( !WithinBounds(rm) )
  {
    throw std::domain_error("Error: SetItem() was given an invalid "\
      "Coordinate.\n");
  }
  else if( itm == Item::kNone )
  {
    throw std::invalid_argument( "Error: SetItem() was given an invalid "\
      "Item.\n" );
  }
  else if( RoomAt(rm).GetItem() != Item::kNone )
  {
    throw std::logic_error("Error: SetItem() cannot replace an existing "\
      "Item.\n");
  }
  else if( itm == Item::kTreasure && treasure_set_ )
  {
    throw std::logic_error( "Error: SetItem() was given a Treasure, "\
      "but the Treasure has already been set in the Labyrinth.\n" );
  }

  try
  {
    RoomAt(rm).SetItem(itm);
  }
  catch( const std::exception& e )
  {
    std::cout << e.what();
  }

  if( itm == Item::kTreasure )
  {
    treasure_set_ = true;
  }
}

// PLAY:

// This method returns the current Inhabitant of the Room.
// An exception is thrown if:
//   The Room is outside the Labyrinth (domain_error)
Inhabitant Labyrinth::GetInhabitant( const Coordinate rm ) const
{
  if( !WithinBounds(rm) )
  {
    throw std::domain_error( "Error: GetInhabitant() was given a "\
      "Coordinate outside of the Labyrinth.\n" );
  }
  return RoomAt(rm).GetInhabitant();
}

// This method attacks the Inhabitant of the Room, and sets the resultant
// Inhabitant.
// The bullet is not removed from the Player.
// An exception is thrown if:
//   The Room is outside the Labyrinth (domain_error)
//   There is no enemy to attack (i.e. Inhabitant::kNone, dead Minotaur,
//     or cracked Mirror) (invalid_argument)
void Labyrinth::AttackEnemy( const Coordinate rm )
{
  if( !WithinBounds(rm) )
  {
    throw std::domain_error( "Error: AttackEnemy() was given an invalid "\
      "Coordinate.\n" );
  }

  auto inh = Inhabitant::kNone;
  try
  {
    inh = RoomAt(rm).GetInhabitant();
  }
  catch( const std::exception& e )
  {
    std::cout << e.what();
    return;
  }

  switch( inh )
  {
    case Inhabitant::kNone:
      throw std::invalid_argument( "Error: AttackEnemy() was given a "\
        "Coordinate with an invalid Inhabitant (kNone).\n" );
      break;

    case Inhabitant::kMinotaurDead:
      throw std::invalid_argument( "Error: AttackEnemy() was given a "\
        "Coordinate with an invalid Inhabitant (a dead Minotaur).\n" );
      break;

    case Inhabitant::kMirrorCracked:
      throw std::invalid_argument( "Error: AttackEnemy() was given a "\
        "Coordinate with an invalid Inhabitant (a cracked mirror).\n" );
      break;

    // Actual code, not error-checking
    case Inhabitant::kMinotaur:
      try
      {
        RoomAt(rm).SetInhabitant(Inhabitant::kMinotaurDead);
      }
      catch( const std::exception& e )
      {
        std::cout << e.what();
        return;
      }
      break;

    case Inhabitant::kMirror:
      try
      {
        RoomAt(rm).SetInhabitant(Inhabitant::kMirrorCracked);
      }
      catch( const std::exception& e )
      {
        std::cout << e.what();
        return;
      }
      break;
  }
}

// This method returns the current Item in the given Room, but does not
// change it.
// An exception is thrown if:
//   The Room is outside the Labyrinth (domain_error)
Item Labyrinth::ItemAt( const Coordinate rm ) const
{
  if( !WithinBounds(rm) )
  {
    throw std::domain_error( "Error: ItemAt() was given a "\
      "Coordinate outside of the Labyrinth.\n" );
  }
  return RoomAt(rm).GetItem();
}

// This method takes the Item from the Room.
// An exception is thrown if:
//   The Room is outside the Labyrinth (domain_error)
//   There is no Item to take (i.e. Item::kNone or Item taken already)
//     (logic_error)
void Labyrinth::TakeItem( const Coordinate rm )
{
  if( !WithinBounds(rm) )
  {
    throw std::domain_error( "Error: TakeItem() was given an "\
      "invalid Coordinate.\n" );
  }

  auto itm = Item::kNone;

  try
  {
    itm = RoomAt(rm).GetItem();
  }
  catch( const std::exception& e )
  {
    std::cout << e.what();
    return;
  }

  auto itm_new = Item::kNone;

  switch( itm )
  {
    case Item::kNone:
      throw std::logic_error( "Error: TakeItem() cannot take "\
        "no item (kNone).\n" );
      break;

    case Item::kTreasureGone:
      throw std::logic_error( "Error: TakeItem() attempted to take "\
        "the Treasure, but the Treasure is gone from this Room.\n" );
      break;

    case Item::kBullet:
      itm_new = Item::kNone;
      break;

    case Item::kTreasure:
      itm_new = Item::kTreasureGone;
      break;
  }

  try
  {
    RoomAt(rm).SetItem(itm_new);
  }
  catch( const std::exception& e )
  {
    std::cout << e.what();
    return;
  }

  // treasure_set_ is not changed upon failure in the try/catch block.
  if( itm_new == Item::kTreasureGone )
  {
    treasure_set_ = false;
  }
}

// This method drops the Treasure in the given Room.
// An exception is thrown if:
//   The Room is outside the Labyrinth (domain_error)
//   The Treasure has already been set in another Room (logic_error)
void Labyrinth::DropTreasure( const Coordinate rm )
{
  if( !WithinBounds(rm) )
  {
    throw std::domain_error( "Error: DropTreasure() was given an "\
      "invalid Coordinate\n." );
  }
  else if( treasure_set_ )
  {
    throw std::logic_error( "Error: DropTreasure() was called when the "
      "Treasure was already set in a Room of the Labyrinth.\n" );
  }

  try
  {
    RoomAt(rm).SetItem(Item::kTreasure);
  }
  catch( const std::exception& e )
  {
    std::cout << e.what();
    return;
  }

  treasure_set_ = true;  // Not modified upon failure of try/catch block
}

// This method returns the type of RoomBorder in the given direction.
// An exception is thrown if:
//   The Room is outside the Labyrinth (domain_error)
//   Direction d is kNone (invalid_argument)
RoomBorder Labyrinth::DirectionCheck( const Coordinate rm,
                                      const Direction d ) const
{
  if( !WithinBounds(rm) )
  {
    throw std::domain_error( "Error: DirectionCheck() was given a "\
      "Coordinate outside of the Labyrinth.\n" );
  }
  else if( d == Direction::kNone )
  {
    throw std::invalid_argument( "Error: DirectionCheck() was given an "\
      "invalid direction (kNone).\n" );
  }

  return RoomAt(rm).DirectionCheck(d);
}

// PRIVATE METHODS:

// This private method returns a reference to the Room at the given
// coordinate.
// An exception is thrown if:
//   The Room is outside the Labyrinth (domain_error)
Room& Labyrinth::RoomAt( const Coordinate rm ) const
{
  if( !WithinBounds(rm) )
  {
    throw std::domain_error( "Error: RoomAt() was given an invalid "\
      "coordinate for rm.\n" );
  }
  return rooms_[rm.y][rm.x];
}

// This private method returns true if the Room is within the bounds of
// the Labyrinth, and false otherwise.
bool Labyrinth::WithinBounds( const Coordinate rm ) const
{
  return( rm.x < x_size_ && rm.y < y_size_ );
}

// This private method returns true if the two Rooms are adjacent, and
// false otherwise.
// An exception is thrown if:
//   One or both Rooms are outside the Labyrinth (domain_error)
//   The same Room is given twice (logic_error)
bool Labyrinth::IsAdjacent( const Coordinate rm_1, const Coordinate rm_2 ) const
{
  if( !WithinBounds(rm_1) )
  {
    if( !WithinBounds(rm_2) )
    {
      throw std::domain_error( "Error: IsAdjacent() was given invalid "\
      "coordinates for both rm_1 and rm_2.\n" );
    }
    else
    {
      throw std::domain_error( "Error: IsAdjacent() was given an invalid "\
      "coordinate for rm_1.\n" );
    }
  }
  else if( !WithinBounds(rm_2) )
  {
    throw std::domain_error( "Error: IsAdjacent() was given an invalid "\
      "coordinate for rm_2.\n" );
  }

  if( rm_1 == rm_2 )
  {
    throw std::logic_error( "Error: IsAdjacent() was given the same "\
      "coordinate for the Rooms.\n" );
  }

  size_t x_distance;
  if( rm_1.x > rm_2.x )
  {
    x_distance = rm_1.x - rm_2.x;
  }
  else
  {
    x_distance = rm_2.x - rm_1.x;
  }

  size_t y_distance;
  if( rm_1.y > rm_2.y )
  {
    y_distance = rm_1.y - rm_2.y;
  }
  else
  {
    y_distance = rm_2.y - rm_1.y;
  }

  if( ( x_distance == 0 && y_distance == 1 ) ||
      ( x_distance == 1 && y_distance == 0 ) )
  {
    return true;
  }
  return false;
}
