#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>


int main() {
	// 'a' = ASCII value of "a" given as proj_id and "." will be string used to create key
	int key = ftok(".", 'a');
	msgid = msgget(key, IPC_CREAT|IPC_EXCL|0744);
	// %0x for Hexadecimal value
	printf("key=0x%0x\t msgid=%d\n", key, msgid);
	return 0;
}
