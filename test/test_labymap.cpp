/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-12-28
 *
 * This C++ file tests the Labyrinth Map class implementation.
 *
 */

#include <exception>
#include <iostream>
#include <stdexcept>

#include "../include/room_properties.hpp"
#include "../include/coordinate.hpp"
#include "../include/labyrinth.hpp"
#include "../include/labyrinth_map.hpp"

int main()
{
  std::cout << std::endl
            << "TESTING LABYRINTH_MAP.CPP IMPLEMENTATION" << std::endl
            << "________________________________________________" << std::endl
            << std::endl;


  const unsigned int l1_xsize = 3;
  const unsigned int l1_ysize = 2;

  std::cout << "Creating a basic, empty Labyrinth with:" << std::endl
            << "  x size = " << l1_xsize << std::endl
            << "  y size = " << l1_ysize << std::endl;

  Labyrinth l1( l1_xsize, l1_ysize );
  std::cout << "Completed." << std::endl;
  std::cout << std::endl;



  std::cout << "Setting the Labyrinth to be a snake from the top left "
            << "to the bottom right." << std::endl;
  Coordinate c1(0, 0);
  Coordinate c2(0, 1);
  Coordinate c3(1, 1);
  Coordinate c4(1, 0);
  Coordinate c5(2, 0);
  Coordinate c6(2, 1);
  try
  {
    l1.ConnectRooms( c1, c2 );
    l1.ConnectRooms( c2, c3 );
    l1.ConnectRooms( c3, c4 );
    l1.ConnectRooms( c4, c5 );
    l1.ConnectRooms( c5, c6 );
  }
  catch( const std::exception& e )
  {
    std::cout << e.what();
  }
  std::cout << "Completed." << std::endl;
  std::cout << std::endl;



  std::cout << "Creating and displaying a Map from the Labyrinth." << std::endl;
  try
  {
    LabyrinthMap l1_map( &l1, l1_xsize, l1_ysize );
    std::cout << "Creation completed." << std::endl;

    l1_map.Display();
  }
  catch( const std::exception& e )
  {
    std::cout << e.what();
  }
  std::cout << "Completed." << std::endl;
  std::cout << std::endl;



  std::cout << "________________________________________________" << std::endl;
  std::cout << std::endl;
  std::cout << "All tests completed." << std::endl;
  std::cout << std::endl;
  std::cout << "Press enter to exit.";
  getchar();
  std::cout << std::endl;

  return 0;
}
