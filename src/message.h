/**
 * message.h
 */
#ifndef MESSAGE_HEADER_SEEN
#define MESSAGE_HEADER_SEEN

#include "intrusive_linked_list.h"

typedef enum {
    SYSTEM,
    MOVEMENT,
    NUM_MESSAGE_TYPES
} MessageType;


typedef struct messageBuffer* MessageBuffer;

typedef struct message* Message;

struct message {
    char* value;
    MessageType type;
    IntrusiveListNode messageBufferNode;
};

MessageBuffer CreateMessageBuffer(void);
void FreeMessageBuffer(MessageBuffer buffer);

void AddSystemMessage(MessageBuffer buffer, char* message);
void AddMessage(MessageBuffer buffer, Message message);
Message GetFirstMessage(MessageBuffer buffer);

#endif
