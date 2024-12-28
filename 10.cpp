#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_SIZE 100

// Define a message structure
struct msg_buffer {
    long msg_type; // Type of the message, used to filter messages
    char msg_text[MSG_SIZE];
};

int main() {
    struct msg_buffer message; 
    int msgid;


    msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    printf("Message Queue ID: %d\n", msgid);



    strcpy(message.msg_text, "Hello, this is a message from IPC!");
    
    if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
        perror("msgsnd failed");
        exit(1);
    }

    printf("Message sent: %s\n", message.msg_text);


    if (msgrcv(msgid, &message, sizeof(message.msg_text), 1, 0) == -1) {
        perror("msgrcv failed");
        exit(1);
    }

    printf("Message received: %s\n", message.msg_text);


    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl failed");
        exit(1);
    }

    printf("Message Queue deleted.\n");

    return 0;
}