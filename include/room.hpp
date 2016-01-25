/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2016-01-25
 *
 * This C++ header file contains implementations of a Room class, which is a
 * template to create a Labyrinth.
 *
 */

#pragma once

#include "room_properties.hpp"

class Room
{
  public:

    // Default constructor
    // This constructor sets a basic, walled, empty Room.
    Room();

    // Parameterized constructor
    // This constructor sets the necessary properties of a Room.
    Room( const Inhabitant dark_thing,
          const Item object,
          const Direction exit,
          const bool wall_north,
          const bool wall_east,
          const bool wall_south,
          const bool wall_west );

    // This method returns the current inhabitant of the Room.
    Inhabitant GetInhabitant() const;

    // This method sets the current inhabitant of the Room.
    void SetInhabitant( const Inhabitant inh );

    // This method returns the current item in the Room.
    Item GetItem() const;

    // This method sets the current item in the Room.
    void SetItem( const Item itm );

    // This method removes the Wall in the given direction so that the Room
    // may be connected to another, or to set the exit.
    // An exception is thrown if:
    //   The Wall has already been removed (logic_error)
    //   Direction d is null (i.e. Direction::kNone) (invalid_argument)
    void BreakWall( const Direction d );

    // This method creates an exit in the given direction. The Wall
    // should be intact (BreakWall() not called on it beforehand).
    // An exception is thrown if:
    //   Direction d is null (i.e. Direction::kNone) (invalid_argument)
    //   The Exit has already been created (logic_error)
    //   The Wall has already been removed (logic_error)
    void CreateExit( const Direction d );

    // This method returns the type of RoomBorder in the given direction.
    // An exception is thrown if:
    //   Direction d is kNone (invalid_argument)
    RoomBorder DirectionCheck( const Direction d ) const;

  private:
    // The exit direction does not count as a wall.
    Inhabitant dark_thing_ = Inhabitant::kNone;
    Item object_ = Item::kNone;
    Direction exit_  = Direction::kNone;
    bool wall_north_ = true;
    bool wall_east_  = true;
    bool wall_south_ = true;
    bool wall_west_  = true;
};
