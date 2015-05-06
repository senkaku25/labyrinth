/*
 *
 * Author: Jeffrey Leung
 * Date: 2015-05-05
 *
 * This header file contains the implementation of a Labyrinth class, a maze which uses the
 * Room class as a building block.
 *
 */

#ifndef LABYRINTH_HPP
#define LABYRINTH_HPP

#include "../room/room_properties.hpp"
#include "../room/room.hpp"

// Method to check for errors
/*
struct Labyrinth
{
  Room* spawn1,
  Room* spawn2
}*/

enum class spawn_location
{
  first,
  second
};

class Labyrinth
{
  public:
    Labyrinth();
    ~Labyrinth();

    Room* RoomCreate( inhabitant dark_thing,
                      item object,
                      direction exit );
    void ConnectRooms( Room* a, Room* b, direction a_to_b );

    void SetSpawnLocation( spawn_location s, Room* r );
    void SetExit( Room* r, direction d );  // Can only be executed on a wall.

    void StartGame();

  private:
    Room* spawn1_;
    Room* spawn2_;

    void Check( unsigned int num_of_rooms );  // Only to be used by StartGame().
};

#endif
