/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2016-01-22
 *
 * This C++ header file contains the implementation of the Labyrinth class,
 * which uses the Room class to create a 2-d mapping for a game.
 *
 */

#pragma once

#include <memory>

#include "room_properties.hpp"
#include "room.hpp"
#include "coordinate.hpp"

// Rooms are indexed first with the y-coordinate, then with the x-coordinate.
class Labyrinth
{
  public:

    // The Coordinates of a Labyrinth begin at (0, 0) at the top left, and
    // end at (x_size-1, y_size-1) at the bottom right.

    // CONSTRUCTOR/DESTRUCTOR:

      // Parameterized constructor
      // An exception is thrown if:
      //   A size of 0 is given (domain_error)
      //   An x or y size greater than the maximum is given (domain_error)
      Labyrinth( const size_t x_size, const size_t y_size );

    // SETUP:

      // This method connects two Rooms by breaking their walls.
      // An exception is thrown if:
      //   One or both Rooms are outside the Labyrinth (domain_error)
      //   The Rooms are not adjacent (logic_error)
      //   The Rooms are the same (logic_error)
      //   The Rooms are already connected (logic_error)
      void ConnectRooms( const Coordinate rm_1, const Coordinate rm_2 );

      // This method sets the primary (initial) spawn Room.
      // An exception is thrown if:
      //   The Room is outside the Labyrinth (domain_error)
      void SetSpawn1( const Coordinate rm );

      // This method sets the secondary spawn Room.
      // An exception is thrown if:
      //   The Room is outside the Labyrinth (domain_error)
      void SetSpawn2( const Coordinate rm );

      // This method sets the exit of the Labyrinth on a Wall.
      // An exception is thrown if:
      //   The Room is outside the Labyrinth (domain_error)
      //   The Direction is invalid (kNone) (invalid_argument)
      //   The Direction has another Room (invalid_argument)
      //   The Exit has already been set (logic_error)
      void SetExit( const Coordinate rm, const Direction d );

      // This method places an Inhabitant in a Room.
      // Cannot change an existing Inhabitant; use the EnemyAttacked() method
      // for that.
      // An exception is thrown if:
      //   The Room is outside the Labyrinth (domain_error)
      //   Inhabitant inh is a null Inhabitant (i.e. Inhabitant::kNone)
      //     (invalid_argument)
      //   The Inhabitant of the Room has already been set (logic_error)
      void SetInhabitant( const Coordinate rm, const Inhabitant inh );

      // This method places an Item in a Room.
      // Cannot change an existing Item; use the TakeItem() method for that.
      // An exception is thrown if:
      //   The Room is outside the Labyrinth (domain_error)
      //   Item itm is a null Item (i.e. Item::kNone) (invalid_argument)
      //   The Item of the Room has already been set (logic_error)
      //   Item itm is a Treasure but the Treasure has already been placed
      //     in another room (logic_error)
      void SetItem( Coordinate rm, Item itm );

    // PLAY:

      // This method returns the current Inhabitant of the Room.
      // An exception is thrown if:
      //   The Room is outside the Labyrinth (domain_error)
      Inhabitant GetInhabitant( const Coordinate rm ) const;

      // This method attacks the Inhabitant of the Room, and sets the resultant
      // Inhabitant.
      // The bullet is not removed from the Player.
      // True is returned if:
      //   The Inhabitant was a Minotaur
      // False is returned if:
      //   The Inhabitant was a Mirror
      // An exception is thrown if:
      //   The Room is outside the Labyrinth (domain_error)
      //   There is no enemy to attack (i.e. Inhabitant::kNone, dead Minotaur,
      //     or cracked Mirror) (invalid_argument)
      bool EnemyAttacked( const Coordinate rm );

      // This method returns the current Item in the room, but does not
      // change it.
      // An exception is thrown if:
      //   The Room is outside the Labyrinth (domain_error)
      Item GetItem( const Coordinate rm ) const;

      // This method takes the Item from the Room.
      // An exception is thrown if:
      //   The Room is outside the Labyrinth (domain_error)
      //   There is no Item to take (i.e. Item::kNone or Item taken already)
      //     (logic_error)
      void TakeItem( const Coordinate rm );

      // This method drops the Treasure in the given room.
      // An exception is thrown if:
      //   The Room is outside the Labyrinth (domain_error)
      void DropTreasure( const Coordinate rm );

      // This method returns the type of RoomBorder in the given direction.
      // An exception is thrown if:
      //   The Room is outside the Labyrinth (domain_error)
      //   Direction d is kNone (invalid_argument)
      RoomBorder DirectionCheck( const Coordinate rm,
                                 const Direction d ) const;

  private:

    std::unique_ptr< std::unique_ptr<Room[]>[] > rooms_;
    const size_t x_size_;
    const size_t y_size_;
    const size_t MAX_X_SIZE_ = 20;
    const size_t MAX_Y_SIZE_ = 20;

    // Special rooms:
    //   Should be set before the game begins
    //   Spawns will default to (0, 0) otherwise
    Coordinate spawn_1_;
    Coordinate spawn_2_;
    bool exit_set_ = false;
    bool treasure_set_ = false;  // Is also false when the treasure is held
                                 // by a Player

    // This private method returns a reference to the Room at the given
    // coordinate.
    // An exception is thrown if:
    //   The Room is outside the Labyrinth (domain_error)
    Room& RoomAt( const Coordinate rm ) const;

    // This private method returns true if the Room is within the bounds of
    // the Labyrinth, and false otherwise.
    bool WithinBounds( const Coordinate rm ) const;

    // This private method returns true if the two Rooms are adjacent, and
    // false otherwise.
    // An exception is thrown if:
    //   One or both Rooms are outside the Labyrinth (domain_error)
    //   The same Room is given twice (logic_error)
    bool IsAdjacent( const Coordinate rm_1, const Coordinate rm_2 ) const;

};
