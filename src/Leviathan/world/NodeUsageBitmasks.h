/*! \file NodeUsageBitmasks.h
 *  \brief Bitmasken für optimierte Szenenknotensuche.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_WORLD_NODEUSAGEBITMASKS_H
#define LEVIATHAN_WORLD_NODEUSAGEBITMASKS_H

#define ID_WALKABLE_ROOT 0xffffffd
#define ID_RESPONSIVE_ROOT 0xffffffe
#define ID_WORLD_ROOT 0xfffffff

#define NODE_FLAG_RESPONSIVE 0x10000000  // Bit 29
#define NODE_FLAG_COLLIDEABLE 0x20000000  // Bit 30
#define NODE_FLAG_WALKABLE 0x40000000  // Bit 31

#define BITMASK_WALKABLE 0x40000000

#endif
