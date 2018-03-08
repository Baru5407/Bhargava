#include <stdio.h> 
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/msg.h>

typedef struct mymsg1{
    long priority;
    char buf[1024];
     int temp;
      int pid;
       int stable;
}msgp;

int msqid,cliA,cliB;
int createMsgQueue()
{
   //Create cliA mailbox
   int stat;
   if ((msqid = msgget(0070, 0666 | IPC_CREAT)) < 0) {
      perror("msgget");
      return 1;
   }
  // else 
    //  (void) fprintf(stderr,"KDC msgget: msgget succeeded: msqid = %d\n", msqid);

   if ((cliA= msgget(0060, 0666 | IPC_CREAT)) < 0) {
      perror("msgget");
      return 1;
   }
//   else 
     // (void) fprintf(stderr,"cliA msgget: msgget succeeded: cliA= %d\n", cliA);

   if ((cliB= msgget(0050, 0666 | IPC_CREAT)) < 0) {
      perror("msgget");
      return 1;
  }
  // else 
   //   (void) fprintf(stderr,"cliA msgget: msgget succeeded: cliB = %d\n", cliB);

   return 0;
}


int main(int argc, char *argv[])
{
   int stat;
   int keyA,keyB,random;
   msgp msgp;
   msgp.priority=2;
   msgp.temp=(int) argv[1];
   msgp.pid=70;
   msgp.stable=0;

   if(createMsgQueue() == 1)
   {
      printf("msg queue creation failed \n");
      return 0;
      }
{
      //printf("Waiting for the msg \n");
      //1. Wait to receive a message containing the identities of a pair of clients (A, B) from a certain client
       stat = msgrcv(msqid, &msgp, sizeof(msgp)-sizeof(long), 2, 0);
        if (stat < 0) {
         perror("msgrcv failed");
         exit(1);
      }
      sscanf(msgp.buf,"A:%d B:%d",&keyA,&keyB);
      printf("<<<Received keys %d;%d from A\n",keyA,keyB);
     
      //generate random no 
      random=rand()%100;
      printf("sess key %d \n",random);
      //encrypt messages
      keyA=keyA^random;
      keyB=keyB^random;
      
      //send the message to cliA
      sprintf(msgp.buf,"A:%d",keyA);

      printf(">>>KDC send (KA,KDC(KA,B) to A:%s \n",msgp.buf);
      //3. Send a message including (A,KB,KDC(KA,B)) to A
       stat = msgsnd(cliA, &msgp, sizeof(msgp) - sizeof(long), 0);
        if ( stat < 0) {
         perror("msgsnd");
         exit(1);
      }

      //send the message to cliB
      sprintf(msgp.buf,"B:%d",keyB);

      printf(">>>KDC send KB,KDC(KA,B)) to B:%s \n",msgp.buf);
      //3. Send a message including (B,KB,KDC(KA,B)) to B
       stat = msgsnd(cliB, &msgp, sizeof(msgp) - sizeof(long), 0);
        if ( stat < 0) {
         perror("msgsnd");
         exit(1);
      }


   }
   //temp=(2*temp+exTemps)/6;
   return 0;

}
