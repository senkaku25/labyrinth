/*
 *
 * Author: Jeffrey Leung
 * Last edited: 2015-09-17
 *
 * This header files contains enums necessary to create and navigate a Room.
 *
 */

#pragma once

enum class Direction
{
  kNone,
  kNorth,
  kEast,
  kSouth,
  kWest,
};

enum class RoomBorder
{
  kWall,
  kRoom,
  kExit,
};

enum class Inhabitant
{
  kNone,
  kMinotaur,
  kMinotaurDead,
  kMirror,
  kMirrorCracked,
};

enum class Item
{
  kNone,
  kBullet,
  kTreasure,
  kTreasureGone,
};
