#include <stdio.h> 
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <stdlib.h>
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
 //  else 
   //   (void) fprintf(stderr,"cliA msgget: msgget succeeded: cliB = %d\n", cliB);

   return 0;
}
int main(int argc, char *argv[])
{
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

{

   sleep(5);

   //Wait to receive the message from KDC
   if (msgrcv(cliB, &msgp, sizeof(msgp)-sizeof(long), 2, 0) < 0) {
      perror("msgrcv failed");
      exit(1);
   }
   sleep(5);

   printf("<<<cli B received rom the KDC :%s \n",msgp.buf);
   
   //Wait to receive the request message from cliA 
   if (msgrcv(cliB, &msgp, sizeof(msgp)-sizeof(long), 2, 0) < 0) {
      perror("msgrcv failed");
      exit(1);
   }
   printf("<<<cli B received %s from cliA \n",msgp.buf);

   strcpy(msgp.buf,"OK");

   stat = msgsnd(cliA, &msgp, sizeof(msgp) - sizeof(long), 0);
    if ( stat < 0) {
      perror("msgsnd");
      exit(1);
   }
   printf(">>>CliB send OK msg to cliA\n");


}
   return 0;
}
