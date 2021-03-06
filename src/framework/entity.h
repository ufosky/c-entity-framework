/**
 * entity.h
 *
 * Methods for creating and manipulating entities
 */

#ifndef ENTITY_HEADER_SEEN
#define ENTITY_HEADER_SEEN

#include "bitset.h"
#include "intrusive_linked_list.h"

enum {
    MAX_ENTITY_NUM = 100
};

typedef struct entity* Entity;
typedef BitSet ComponentDescriptor;

struct entity {
    ComponentDescriptor componentDescriptor;
    unsigned int id;
    IntrusiveListNode renderSystemListNode;
    IntrusiveListNode keyboardInputSystemListNode;
};

#endif
