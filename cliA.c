#include <stdio.h> 
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>

typedef struct my_msg1{
    long priority;
    char buf[1024];
     int temp;
      int pid;
       int stable;
}msgp;
int msqid,cliA,cliB;

int createMsgQueue()
{
   int stat;
   //Create cliA mailbox
   if ((msqid = msgget(0070, 0666)) < 0) {
      perror("msgget");
      return 1;
   }
//   else 
  //    (void) fprintf(stderr,"KDC msgget: msgget succeeded: msqid = %d\n", msqid);

   if ((cliA= msgget(0060, 0666)) < 0) {
      perror("msgget");
      return 1;
   }
//   else 
  //    (void) fprintf(stderr,"cliA msgget: msgget succeeded: cliA= %d\n", cliA);

   if ((cliB= msgget(0050, 0666)) < 0) {
      perror("msgget");
      return 1;
   }
//   else 
  //    (void) fprintf(stderr,"cliA msgget: msgget succeeded: cliB = %d\n", cliB);

   return 0;
}
int main(int argc, char *argv[])
{
   int sharedkeyA=11;
   int sharedkeyB=22;
   msgp msgp;
   msgp.priority=2;
   msgp.temp=(int) argv[1];
   msgp.pid=(int) argv[2];
   msgp.stable=0;

   int stat;

   if(createMsgQueue() == 1)
   {
      printf("msg queue creation failed \n");
      return 0;
      }


   //1. Send a message containing the identities of itself and the other client (A, B) to the KDC
   sprintf(msgp.buf,"A:%d B:%d",sharedkeyA,sharedkeyB);
   printf(">>>Sending client (A, B) to the KDC :%s \n",msgp.buf);
   stat = msgsnd(msqid, &msgp, sizeof(msgp) - sizeof(long), 0);
      if ( stat < 0) {
      perror("msgsnd");
      exit(1);
   }
   sleep(5);

   //Wait to receive the message including (KA,KDC(KA,B) from the KDC
   if (msgrcv(cliA, &msgp, sizeof(msgp)-sizeof(long), 2, 0) < 0) {
      perror("msgrcv failed");
      exit(1);
   }
   printf("<<<cli A received  (KA,KDC(KA,B) from the KDC:%s \n",msgp.buf);

   printf(">>>cli A send Request to B\n");
   //3. Send a message including Request to B
   strcpy(msgp.buf,"Request");
   stat = msgsnd(cliB, &msgp, sizeof(msgp) - sizeof(long), 0);
    if ( stat < 0) {
      perror("msgsnd");
      exit(1);
   }

   //Wait to receive the response from B
   if (msgrcv(cliA, &msgp, sizeof(msgp)-sizeof(long), 2, 0) < 0) {
      perror("msgrcv failed");
      exit(1);
   }
   printf("<<<cliA Received response from B:%s\n",msgp.buf);

   return 0;

}
