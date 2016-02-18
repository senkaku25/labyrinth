/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2016-02-17
 *
 * This C++ file tests the Labyrinth class implementation.
 *
 */

#include <exception>
#include <iostream>
#include <stdexcept>

#include "../include/room_properties.hpp"
#include "../include/coordinate.hpp"
#include "../include/labyrinth.hpp"

namespace  // Local functions
{

// This local function runs tests for the Labyrinth constructor,
// returning the number of errors found.
unsigned int TestLabyrinthConstructor()
{
  std::cout << "________________________________________________"
            << std::endl << std::endl
            << "TESTING CONSTRUCTOR:"
            << std::endl << std::endl;
  unsigned int error_count = 0;

  std::cout << "Creating a basic, empty Labyrinth with:" << std::endl
            << "  x size = 3" << std::endl
            << "  y size = 5" << std::endl;

  try
  {
    Labyrinth l1( 3, 5 );
  }
  catch( const std::exception& e )
  {
    ++error_count;
    std::cout << e.what();
  }
  std::cout << "Completed."
            << std::endl
            << std::endl;



  std::cout << "Create a Labyrinth with x size = 0: "
            << "(An error should be thrown)"
            << std::endl;
  try
  {
    ++error_count;
    Labyrinth l_trycatch( 0, 10 );
  }
  catch( const std::exception& e )
  {
    --error_count;
    std::cout << e.what();
  }
  std::cout << "Completed."
            << std::endl << std::endl;

  std::cout << "Create a Labyrinth with y size = 0: "
            << "(An error should be thrown)"
            << std::endl;
  try
  {
    ++error_count;
    Labyrinth l_trycatch( 10, 0 );
  }
  catch( const std::exception& e )
  {
    --error_count;
    std::cout << e.what();
  }
  std::cout << "Completed."
            << std::endl << std::endl;

  std::cout << "Create a Labyrinth with x size = "
            << "y size = 0. "
            << "(An error should be thrown)"
            << std::endl;
  try
  {
    ++error_count;
    Labyrinth l_trycatch( 0, 0 );
  }
  catch( const std::exception& e )
  {
    --error_count;
    std::cout << e.what();
  }
  std::cout << "Completed."
            << std::endl << std::endl;

  std::cout << error_count
            << " errors found for Labyrinth constructor."
            << std::endl;
  return error_count;
}

// This local function runs tests for the Labyrinth method ConnectRooms(),
// returning the number of errors found.
unsigned int TestLabyrinthConnectRooms()
{
  std::cout << "________________________________________________"
            << std::endl << std::endl
            << "TESTING CONNECTROOMS():"
            << std::endl << std::endl;
  unsigned int error_count = 0;

  std::cout << "Creating a basic, empty Labyrinth with:" << std::endl
            << "  x size = 3" << std::endl
            << "  y size = 2" << std::endl;

  Labyrinth l1( 3, 2 );
  std::cout << "Completed." << std::endl;
  std::cout << std::endl;

  Coordinate c_0_0(0, 0);
  Coordinate c_0_1(0, 1);
  Coordinate c_1_0(1, 0);
  Coordinate c_1_1(1, 1);
  Coordinate c_2_1(2, 1);

  std::cout << "Connecting horizontally adjacent rooms (0, 0) and (1, 0):"
            << std::endl;
  try
  {
    l1.ConnectRooms( c_0_0, c_1_0 );
  }
  catch( const std::exception& e )
  {
    ++error_count;
    std::cout << e.what();
  }
  std::cout << "Done." << std::endl << std::endl;

  std::cout << "Connecting horizontally adjacent rooms (1, 1) and (0, 1):"
            << std::endl;
  try
  {
    l1.ConnectRooms( c_1_1, c_0_1 );
  }
  catch( const std::exception& e )
  {
    ++error_count;
    std::cout << e.what();
  }
  std::cout << "Done." << std::endl << std::endl;

  std::cout << "Connecting vertically adjacent rooms (0, 0) and (0, 1):"
            << std::endl;
  try
  {
    l1.ConnectRooms(c_0_0, c_0_1);
  }
  catch( const std::exception& e )
  {
    ++error_count;
    std::cout << e.what();
  }
  std::cout << "Done." << std::endl << std::endl;

  std::cout << "Connecting vertically adjacent rooms (1, 1) and (1, 0):"
            << std::endl;
  try
  {
    l1.ConnectRooms(c_1_1, c_1_0);
  }
  catch( const std::exception& e )
  {
    ++error_count;
    std::cout << e.what();
  }
  std::cout << "Done." << std::endl << std::endl;



  std::cout << "Connecting diagonally adjacent rooms (0, 0) and (1, 1) "
            << "(An error should be thrown):"
            << std::endl;
  try
  {
    ++error_count;
    l1.ConnectRooms(c_0_0, c_1_1);
  }
  catch( const std::exception& e )
  {
    --error_count;
    std::cout << e.what();
  }
  std::cout << "Done." << std::endl << std::endl;

  std::cout << "Connecting diagonally adjacent rooms (0, 1) and (1, 0) "
            << "(An error should be thrown):"
            << std::endl;
  try
  {
    ++error_count;
    l1.ConnectRooms(c_0_1, c_1_0);
  }
  catch( const std::exception& e )
  {
    --error_count;
    std::cout << e.what();
  }
  std::cout << "Done." << std::endl << std::endl;

  std::cout << "Connecting diagonally adjacent rooms (0, 1) and (1, 0) "
    << "(An error should be thrown):"
    << std::endl;
  try
  {
    ++error_count;
    l1.ConnectRooms(c_0_1, c_1_0);
  }
  catch( const std::exception& e )
  {
    --error_count;
    std::cout << e.what();
  }
  std::cout << "Done." << std::endl << std::endl;

  std::cout << "Connecting non-adjacent rooms (0, 0) and (2, 1) "
            << "(An error should be thrown):"
            << std::endl;
  try
  {
    ++error_count;
    l1.ConnectRooms(c_0_0, c_2_1);
  }
  catch( const std::exception& e )
  {
    --error_count;
    std::cout << e.what();
  }
  std::cout << "Done." << std::endl;
  std::cout << std::endl;

  std::cout << error_count
            << " errors found for Labyrinth ConnectRooms()."
            << std::endl;
  return error_count;
}

// This local function runs tests for the Labyrinth methods SetSpawn1/2().
void TestLabyrinthSetSpawns()
{
  std::cout << "________________________________________________"
            << std::endl << std::endl
            << "TESTING SETSPAWN1() AND SETSPAWN2():"
            << std::endl << std::endl;

  std::cout << "Creating a basic, empty Labyrinth with:" << std::endl
            << "  x size = 2" << std::endl
            << "  y size = 2" << std::endl;

  Labyrinth l1( 2, 2 );
  std::cout << "Completed."
            << std::endl
            << std::endl;



  Coordinate c_0_0(0, 0);
  Coordinate c_0_1(0, 1);
  Coordinate c_1_0(1, 0);
  Coordinate c_1_1(1, 1);

  std::cout << "Setting Spawn 1 at (0, 0) twice: "
            << std::endl;
  try
  {
    l1.SetSpawn1(c_0_0);
    l1.SetSpawn1(c_0_0);
  }
  catch( const std::exception& e )
  {
    std::cout << e.what();
  }
  std::cout << "Completed."
            << std::endl << std::endl;

  std::cout << "Setting Spawn 2 at (0, 1) twice: "
            << std::endl;
  try
  {
    l1.SetSpawn2(c_0_1);
    l1.SetSpawn2(c_0_1);
  }
  catch( const std::exception& e )
  {
    std::cout << e.what();
  }
  std::cout << "Completed."
            << std::endl << std::endl;

  std::cout << "Setting Spawn 1 at (1, 0): "
            << std::endl;
  try
  {
    l1.SetSpawn1(c_1_0);
  }
  catch( const std::exception& e )
  {
    std::cout << e.what();
  }
  std::cout << "Completed."
            << std::endl << std::endl;

  std::cout << "Setting Spawn 2 at (1, 1): "
            << std::endl;
  try
  {
    l1.SetSpawn2(c_1_1);
  }
  catch( const std::exception& e )
  {
    std::cout << e.what();
  }
  std::cout << "Completed."
            << std::endl << std::endl;
}

}  // End of unnamed namespace (for local functions)

int main()
{
  std::cout << std::endl
            << "TESTING LABYRINTH.CPP IMPLEMENTATION"
            << std::endl
            << std::endl;

  unsigned int error_count = 0;
  try
  {
    error_count += TestLabyrinthConstructor();
    error_count += TestLabyrinthConnectRooms();
    TestLabyrinthSetSpawns();
  }
  catch( const std::exception& e )
  {
    std::cout << e.what();
  }

  std::cout << "________________________________________________"
            << std::endl
            << std::endl
            << "Testing completed; there were "
            << error_count
            << " errors found."
            << std::endl
            << std::endl
            << "Press enter to exit.";
  getchar();
  std::cout << std::endl;

  return 0;
}
