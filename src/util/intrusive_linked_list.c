#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "intrusive_linked_list.h"

struct intrusiveList {
    IntrusiveListNode root;
} internalIntrusiveList;

IntrusiveListNode CreateIntrusiveListNode(void) {
    return CreateIntrusiveListNodeWithDebugDescriptor("");
}

IntrusiveListNode CreateIntrusiveListNodeWithDebugDescriptor(char* debugDescriptor) {
    IntrusiveListNode node;

    node.debugDescriptor = debugDescriptor;
    node.next = NULL;
    node.prev = NULL;

    return node;
}

IntrusiveList CreateIntrusiveList() {
    IntrusiveList list = malloc(sizeof(internalIntrusiveList));

    list->root.debugDescriptor = "ROOT_NODE";
    list->root.next = &(list->root);
    list->root.prev = &(list->root);

    return list;
}

void FreeIntrusiveList(IntrusiveList intrusiveList) {
    IntrusiveListNodePtr root = &(intrusiveList->root);
    assert( (root == root->next) && (root == root->prev));
    free(intrusiveList);
}

void AddHead(IntrusiveList intrusiveList, IntrusiveListNodePtr node) {
    Add(node, &(intrusiveList->root), intrusiveList->root.next);
}

void Add(IntrusiveListNodePtr node, IntrusiveListNodePtr prev, IntrusiveListNodePtr next) {
    node->next = next;
    node->prev = prev;
    next->prev = node;
    prev->next = node;
}

void Remove(IntrusiveListNodePtr node) {
    node->next->prev = node->prev;
    node->prev->next = node->next;
    node->next = NULL;
    node->prev = NULL;
}

IntrusiveListNodePtr Head(IntrusiveList intrusiveList) {
    return &(intrusiveList->root);
}

IntrusiveListNodePtr Next(IntrusiveListNodePtr node) {
    return node->next;
}

void DebugListNode(IntrusiveListNodePtr node) {
    printf("IntrusiveListNodeDebug: %s\n", node->debugDescriptor);
}
