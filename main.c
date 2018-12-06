#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
  key_t key = ftok("mykey", 'f');
  int id = shmget(key, 100, IPC_CREAT | 0777);
  char * data = shmat(id, 0, 0);


  if(!(*data)) printf("There's nothing here yet, it's a new segment!\n");
  else printf("Here's what the data is: \"%s\"\n", data);

  char choice[3], input[100];

  printf("Do you want to change the data? (y/n)\n");
  fgets(choice, 3, stdin);

  if (choice[0] == 'y'){
    printf("Enter new data: ");
    fgets(input, 100, stdin);
    input[strlen(input) - 1] = '\0';
    strcpy(data, input);
  }
  shmdt(data);


  printf("Do you want to delete the shared memory? (y/n)\n");
  fgets(choice, 2, stdin);
  if(choice[0] == 'y'){
    shmctl(id, IPC_RMID, 0);
    printf("Memory has been deleted!\n");
  }

  return 0;
}
