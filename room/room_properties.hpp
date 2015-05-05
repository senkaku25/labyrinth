/*
 * Author: Jeffrey Leung
 * Last edited: 2015-05-05
 *
 * This header files contains enums necessary to create and navigate a Room.
 *
 */

#ifndef ROOM_PROPERTIES_HPP
#define ROOM_PROPERTIES_HPP

enum class direction
{
  none,
  north,
  east,
  south,
  west
};

enum class inhabitant
{
  none,
  minotaur,
  minotaur_dead,
  mirror,
  mirror_cracked
};

enum class item
{
  none,
  bullet,
  treasure,
  treasure_gone
};

#endif
