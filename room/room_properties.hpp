/*
 * Author: Jeffrey Leung
 * Last edited: 2015-05-20
 *
 * This header files contains enums necessary to create and navigate a Room.
 *
 */

#pragma once

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
