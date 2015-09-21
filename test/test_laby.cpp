/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-09-19
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

int main()
{
  std::cout << std::endl
            << "TESTING LABYRINTH.CPP IMPLEMENTATION" << std::endl
            << "________________________________________________" << std::endl
            << std::endl;
  
  
  
  std::cout << "Creating a basic, empty Labyrinth with:" << std::endl
            << "  x size = 3" << std::endl
            << "  y size = 5" << std::endl;
  
  Labyrinth l1( 3, 5 );
  std::cout << "Completed." << std::endl;
  std::cout << std::endl;
  
  
  
  std::cout << "Type 1 to attempt to create a Labyrinth with x size = 0."
            << std::endl
            << "Type 2 to attempt to create a Labyrinth with y size = 0."
            << std::endl
            << "Type 3 to attempt to create a Labyrinth with x size = "
            << "y size = 0."
            << std::endl
            << "Type 0 to continue."
            << std::endl
            << "> ";
        
  char c = ' ';
  while ( c < '0' || c > '3' )
  {
    std::cin >> c;
    switch( c )
    {
      case( '1' ):
        try
        {
          Labyrinth l_empty( 0, 10 );
        }
        catch( std::exception& e )
        {
          std::cout << e.what() << std::endl;
        }
        break;
      
      case( '2' ):
        try
        {
          Labyrinth l_empty( 10, 0 );
        }
        catch( std::exception& e )
        {
          std::cout << e.what() << std::endl;
        }
        break;
        
      case( '3' ):
        try
        {
          Labyrinth l_empty( 0, 0 );
        }
        catch( std::exception& e )
        {
          std::cout << e.what() << std::endl;
        }
        break;
        
      case( '0' ):
        break;
        
      default:
        std::cout << std::endl
                  << "Error: That was not a valid input; please try again: ";
        break;
    }
  }
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
