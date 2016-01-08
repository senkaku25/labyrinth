/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2016-01-07
 *
 * This C++ file tests the functionality of room.cpp.
 *
 */

#include <iostream>

#include "../include/room_properties.hpp"
#include "../include/room.hpp"

// This function returns the given type of room border as a string.
std::string RoomBorderPrint( RoomBorder r )
{
  switch( r )
  {
    case( RoomBorder::kWall ):
      return "Wall";
    case( RoomBorder::kRoom ):
      return "Room";
    case( RoomBorder::kExit ):
      return "Exit";
  }
  return "Error: RoomBorderPrint() was given a type of RoomBorder which "\
         "could not be detected.";
}

// This function returns the given type of inhabitant as a string.
std::string InhabitantPrint( Inhabitant inh )
{
  switch( inh )
  {
    case( Inhabitant::kNone ):
      return "nothing";
    case( Inhabitant::kMinotaur ):
      return "a Minotaur";
    case( Inhabitant::kMinotaurDead ):
      return "a dead Minotaur";
    case( Inhabitant::kMirror ):
      return "a mirror";
    case( Inhabitant::kMirrorCracked ):
      return "a cracked mirror";
  }
  return "Error: InhabitantPrint() was given a type of Inhabitant which "\
         "could not be detected.";
}

// This function returns the given type of item as a string.
std::string ItemPrint( Item itm )
{
  switch( itm )
  {
    case( Item::kNone ):
      return "nothing";
    case( Item::kBullet ):
      return "a bullet";
    case( Item::kTreasure ):
      return "the treasure";
    case( Item::kTreasureGone ):
      return "a missing treasure";
  }
  return "Error: ItemPrint() was given a type of Item which "\
         "could not be detected.";
}

int main()
{
  std::cout << std::endl;
  std::cout << "TESTING ROOM.CPP IMPLEMENTATION" << std::endl;
  std::cout << "________________________________________________" << std::endl;
  std::cout << std::endl;



  std::cout << "Creating a room with:" << std::endl;
  std::cout << "  A minotaur" << std::endl;
  std::cout << "  A bullet" << std::endl;
  std::cout << "  An exit north of the room" << std::endl;
  std::cout << "  Walls to the south and west of the room" << std::endl;
  std::cout << "  Entrances to other rooms to the east of the room "
            << std::endl;

  Room rm_1( Inhabitant::kMinotaur,
             Item::kBullet,
             Direction::kNorth,
             false, false, true, true );
  std::cout << "Completed." << std::endl;
  std::cout << "________________________________________________" << std::endl;
  std::cout << std::endl;



  std::cout << "Testing GetInhabitant() and SetInhabitant():" << std::endl;

  std::cout << "  The current inhabitant of the room is "
            << InhabitantPrint( rm_1.GetInhabitant() )
            << "." << std::endl;

  rm_1.SetInhabitant( Inhabitant::kMirrorCracked );
  std::cout << "  After changing the inhabitant to a cracked mirror, the "
            << "new inhabitant is (by GetInhabitant()) "
            << InhabitantPrint( rm_1.GetInhabitant() )
            << "." << std::endl;

  std::cout << "________________________________________________" << std::endl;
  std::cout << std::endl;



  std::cout << "Testing GetItem() and SetItem():" << std::endl;

  std::cout << "  The current item in the room is "
            << ItemPrint( rm_1.GetItem() )
            << "." << std::endl;

  rm_1.SetItem( Item::kTreasureGone );
  std::cout << "  After changing the item to a missing treasure, the "
            << "new inhabitant is (by GetItem()) "
            << ItemPrint( rm_1.GetItem() )
            << "." << std::endl;

  std::cout << "________________________________________________" << std::endl;
  std::cout << std::endl;



  std::cout << "Testing BreakWall():" << std::endl;

  std::cout << "  Breaking the west wall... ";
  rm_1.BreakWall( Direction::kWest );
  std::cout << "Completed."
            << std::endl;

  std::cout << "________________________________________________" << std::endl;
  std::cout << std::endl;



  std::cout << "Testing DirectionCheck():" << std::endl;

  std::cout << "  To the north of the room is a "
            << RoomBorderPrint( rm_1.DirectionCheck(Direction::kNorth) )
            << "." << std::endl;
  std::cout << "  To the east of the room is a "
            << RoomBorderPrint( rm_1.DirectionCheck(Direction::kEast) )
            << "." << std::endl;
  std::cout << "  To the south of the room is a "
            << RoomBorderPrint( rm_1.DirectionCheck(Direction::kSouth) )
            << "." << std::endl;
  std::cout << "  To the west of the room is a "
            << RoomBorderPrint( rm_1.DirectionCheck(Direction::kWest) )
            << "." << std::endl;



  std::cout << "________________________________________________" << std::endl;
  std::cout << std::endl;
  std::cout << "All tests completed." << std::endl;
  std::cout << std::endl;
  std::cout << "Press enter to exit.";
  getchar();
  std::cout << std::endl;

  return 0;
}
