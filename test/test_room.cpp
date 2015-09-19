/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-09-17
 *
 * This C++ file tests the functionality of room.cpp.
 *
 */

#include <iostream>

#include "../room/room_properties.hpp"
#include "../room/room.hpp"

// This function returns the given type of room border as a string.
std::string RoomBorderPrint( RoomBorder r )
{
  if( r == RoomBorder::kWall )
  {
    return "Wall";
  }
  else if( r == RoomBorder::kRoom )
  {
    return "Room";
  }
  else
  {
    return "Exit";
  }
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
  std::cout << "  A wall to the south of the room" << std::endl;
  std::cout << "  Entrances to other rooms to the east and west of the room "
            << std::endl;
  
  Room rm_1( Inhabitant::kMinotaur,
             Item::kBullet,
             Direction::kNorth,
             false, false, true, false );
  std::cout << "Completed." << std::endl;
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
