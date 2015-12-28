/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-12-28
 *
 * This C++ header file contains the implementation of the Labyrinth class,
 * which uses the Room class to create a 2-d mapping for a game.
 *
 */

#pragma once

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
      //   A size of 0 is given (invalid_argument)
      Labyrinth( unsigned int x_size, unsigned int y_size );

      // Destructor
      ~Labyrinth();

    // SETUP:

      // This method connects two Rooms by breaking their walls.
      // An exception is thrown if:
      //   The Rooms are already connected (logic_error)
      //   The Rooms are the same (logic_error)
      //   The Rooms are not adjacent (logic_error)
      //   One or both Rooms are outside the Labyrinth (invalid_argument)
      void ConnectRooms( Coordinate rm_1, Coordinate rm_2 );

      // This method sets the primary (initial) spawn Room.
      //   The Room is outside the Labyrinth (invalid_argument)
      void SetSpawn1( Coordinate rm );

      // This method sets the secondary spawn Room.
      //   The Room is outside the Labyrinth (invalid_argument)
      void SetSpawn2( Coordinate rm );

      // This method sets the exit of the Labyrinth on a Wall.
      // An exception is thrown if:
      //   The Direction has another Room (invalid_argument)
      //   The Exit has already been set (logic_error)
      //   The Room is outside the Labyrinth (invalid_argument)
      void SetExit( Coordinate rm, Direction d );

      // This method places the Labyrinth treasure in a Room.
      // May be used to drop the Treasure if a Player is dead.
      // An exception is thrown if:
      //   The Treasure has already been placed in another Room (logic_error)
      //   The Room is outside the Labyrinth (invalid_argument)
      void SetTreasure( Coordinate rm );

      // This method places an Inhabitant in a Room.
      // Cannot change an existing Inhabitant; use the EnemyAttacked() method
      // for that.
      // An exception is thrown if:
      //   The Inhabitant of the Room has already been set (logic_error)
      //   Inhabitant inh is a null Inhabitant (i.e. Inhabitant::kNone)
      //     (invalid_argument)
      //   The Room is outside the Labyrinth (invalid_argument)
      void SetInhabitant( Coordinate rm, Inhabitant inh );

      // This method places an Item in a Room.
      // Cannot change an existing Item; use the TakeItem() method for that.
      // An exception is thrown if:
      //   The Item of the Room has already been set (logic_error)
      //   Item itm is a null Item (i.e. Item::kNone) (invalid_argument)
      //   The Room is outside the Labyrinth (invalid_argument)
      void SetItem( Coordinate rm, Item itm );

    // PLAY:

      // This method returns the current Inhabitant of the Room.
      // An exception is thrown if:
      //   The Room is outside the Labyrinth (invalid_argument)
      Inhabitant GetInhabitant( Coordinate rm ) const;

      // This method attacks the Inhabitant of the Room, and sets the resultant
      // Inhabitant.
      // The bullet is not removed from the Player.
      // True is returned if:
      //   The Inhabitant was a Minotaur
      // False is returned if:
      //   The Inhabitant was a Mirror
      // An exception is thrown if:
      //   There is no enemy to attack (i.e. Inhabitant::kNone, dead Minotaur,
      //     or cracked Mirror) (invalid_argument)
      //   The Room is outside the Labyrinth (invalid_argument)
      bool EnemyAttacked( Coordinate rm );

      // This method returns the current Item in the room, but does not
      // change it.
      // An exception is thrown if:
      //   The Room is outside the Labyrinth (invalid_argument)
      Item GetItem( Coordinate rm ) const;

      // This method takes the Item from the Room.
      // An exception is thrown if:
      //   There is no Item to take (i.e. Item::kNone or Item taken already)
      //     (logic_error)
      //   The Room is outside the Labyrinth (invalid_argument)
      void TakeItem( Coordinate rm );

      // This method returns the type of RoomBorder in the given direction.
      // An exception is thrown if:
      //   The Room is outside the Labyrinth (invalid_argument)
      //   Direction d is kNone (invalid_argument)
      RoomBorder DirectionCheck( Coordinate rm, Direction d ) const;

  private:

    Room** rooms_;
    unsigned int x_size_;
    unsigned int y_size_;

    // Special rooms:
    //   Must be set before the game begins
    Coordinate spawn_1_;
    Coordinate spawn_2_;
    bool exit_set_ = false;
    bool treasure_set_ = false;  // Changed to false when the treasure is held
                                 // by a Player

    // This private method returns a reference to the Room at the given
    // coordinate.
    // An exception is thrown if:
    //   The Room is outside the Labyrinth (invalid_argument)
    Room& RoomAt( Coordinate rm ) const;

    // This private method returns true if the Room is within the bounds of
    // the Labyrinth, and false otherwise.
    bool WithinBounds( Coordinate rm ) const;

    // This private method returns true if the two Rooms are adjacent, and
    // false otherwise.
    // An exception is thrown if:
    //   One or both Rooms are outside the Labyrinth (invalid_argument)
    //   The same Room is given twice (logic_error)
    bool IsAdjacent( Coordinate rm_1, Coordinate rm_2 ) const;

};
