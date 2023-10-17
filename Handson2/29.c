#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <errno.h>

int main() {
    key_t key;
    int msqid;
 
    //get the old key
    key = ftok(".", 'b');

    if (key == -1) {
        perror("ftok error");
        exit(1);
    }


    //get message queue id
    msqid = msgget(key, 0);

    if (msqid == -1) {
        perror("msgget errorrr");
        exit(1);
    }


    //remove the message queue
    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl IPC_RMID error");
        exit(1);
    }

    printf("Message queue removed successfully.\n");

    return 0;
}

