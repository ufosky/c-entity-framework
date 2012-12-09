/**
 * intrusive_linked_list.h
 */
#ifndef INTRUSIVELIST_HEADER_SEEN
#define INTRUSIVELIST_HEADER_SEEN

#include <stddef.h>

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:        the pointer to the member.
 * @type:       the type of the container struct this is embedded in.
 * @member:     the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({ \
                const typeof( ((type *)0)->member ) *__mptr = (ptr); \
                (type *)( (char *)__mptr - offsetof(type,member) );})

struct intrusiveListNode {
    char* debugDescriptor;
    struct intrusiveListNode* next;
    struct intrusiveListNode* prev;
};

typedef struct intrusiveListNode IntrusiveListNode;
typedef struct intrusiveListNode* IntrusiveListNodePtr;
typedef struct intrusiveList* IntrusiveList;

IntrusiveListNode CreateIntrusiveListNode(void);
IntrusiveListNode CreateIntrusiveListNodeWithDebugDescriptor(char* debugDescriptor);

IntrusiveList CreateIntrusiveList();
void FreeIntrusiveList(IntrusiveList intrusiveList);

void AddHead(IntrusiveList intrusiveList, IntrusiveListNodePtr node);
void Add(IntrusiveListNodePtr node, IntrusiveListNodePtr prev, IntrusiveListNodePtr next);
void Remove(IntrusiveListNodePtr node);

IntrusiveListNodePtr Head(IntrusiveList intrusiveList);
IntrusiveListNodePtr Next(IntrusiveListNodePtr node);

void DebugListNode(IntrusiveListNodePtr node);

#endif
