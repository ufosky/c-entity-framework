#include "message.h"

#include <stdlib.h>

typedef struct messageBuffer {
    IntrusiveList messages;
} internalMessageBuffer;

Message CreateMessage(void) {
    Message obj = (Message)malloc(sizeof(struct message));
    obj->value = NULL;
    obj->messageBufferNode = CreateIntrusiveListNode();

    return obj;
}

void FreeMessage(Message message) {
    Remove(&(message->messageBufferNode));
    free(message);
}

MessageBuffer CreateMessageBuffer(void) {
    MessageBuffer obj = (MessageBuffer)malloc(sizeof(internalMessageBuffer));
    obj->messages = CreateIntrusiveList();

    return obj;
}

void FreeMessageBuffer(MessageBuffer buffer) {
    IntrusiveListNodePtr iter = Next(Head(buffer->messages));
    IntrusiveListNodePtr head = Head(buffer->messages);

    while (iter != head) {
        Message message =  container_of(iter, struct message, messageBufferNode);
        iter = Next(iter);
        FreeMessage(message);
    }

    FreeIntrusiveList(buffer->messages);
    free(buffer);
}

void AddMessage(MessageBuffer buffer, Message message) {

}

Message GetFirstMessage(MessageBuffer buffer) {

}
