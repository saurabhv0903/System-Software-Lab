#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <time.h>

int main() {

	int msqid;
        key_t key;
        struct msqid_ds queue_info;

        // Generate a key for the message queue
        key = ftok("/tmp", 'A');
        if (key == -1) {
        perror("ftok");
        exit(1);
        }

        // Get the message queue ID
        msqid = msgget(key, 0666 | IPC_CREAT);
        if (msqid == -1) {
        perror("msgget");
        exit(1);
        }

        // Get and print the message queue attributes
        if (msgctl(msqid, IPC_STAT, &queue_info) == -1) {
        perror("msgctl");
        exit(1);
        }

        printf("a. Access Permission: 0%o\n", queue_info.msg_perm.mode);
        printf("b. UID: %d, GID: %d\n", queue_info.msg_perm.uid, queue_info.msg_perm.gid);
        printf("c. Time of Last Message Sent: %s", ctime(&queue_info.msg_stime));
        printf("   Time of Last Message Received: %s", ctime(&queue_info.msg_rtime));
        printf("d. Time of Last Change in the Message Queue: %s", ctime(&queue_info.msg_ctime));
        printf("e. Size of the Queue: %lu bytes\n", (unsigned long)queue_info.msg_qbytes);
        printf("f. Number of Messages in the Queue: %lu\n", (unsigned long)queue_info.msg_qnum);
        printf("g. Maximum Number of Bytes Allowed: %lu bytes\n", (unsigned long)queue_info.msg_qbytes);
        printf("h. PID of the last msgsnd: %d\n", queue_info.msg_lspid);
        printf("   PID of the last msgrcv: %d\n", queue_info.msg_lrpid);
}
