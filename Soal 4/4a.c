#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
//Each thread computes single element in the resultant matrix
void *mult(void* arg)
{
  int *data = (int *)arg;
  int k = 0, i = 0;

  int x = data[0];
  for (i = 1; i <= x; i++)
    k += data[i]*data[i+x];

  int *p = (int*)malloc(sizeof(int));
  *p = k;

  pthread_exit(p);
}

int main()
{
  key_t exchangeKey = 1112;
   int shmid = shmget(exchangeKey,22,0666| IPC_CREAT);
   //Attach SharedMemory
   int *value =  shmat(shmid,NULL,0);

  int matA[4][2] = {{1,1},{1,2},{1,3},{2, 4}};
  int matB[2][5] = {{1,2,3,4,2},{2,2,2,2,2}};

  int r1=4,c1=2,r2=2,c2=5,i,j,k;






  printf("Matrix A:\n");
  for (i = 0; i < r1; i++){
    for(j = 0; j < c1; j++)
     printf("%d ",matA[i][j]);
    printf("\n");
  }

  printf("\n");

  printf("Matrix B:\n");
  for (i = 0; i < r2; i++){
    for(j = 0; j < c2; j++)
      printf("%d ",matB[i][j]);
    printf("\n");
  }
  printf("\n");

  /*
    Acces Shared Memory
  */
int max = 20;

  /*
    Make thread array
  */
  pthread_t *threads;
  threads = (pthread_t*)malloc(max*sizeof(pthread_t));

  int threadCount = 0;
  int* data = NULL;
  /*
    Untuk tiap baris dan kolom lakukan perkalian pada thread
  */
  for (i = 0; i < r1; i++)
    for (j = 0; j < c2; j++)
    {

      data = (int *)malloc((20)*sizeof(int));
      data[0] = c1;

      for (k = 0; k < c1; k++) data[k+1] = matA[i][k];
      for (k = 0; k < r2; k++) data[k+c1+1] = matB[k][j];

      pthread_create(&threads[threadCount++], NULL,
      mult, (void*)(data));
    }


  printf("Matrix hasil :\n");
  for (i = 0; i < max; i++)
  {
    void *k;
    pthread_join(threads[i], &k);
    int *p = (int *)k;
    printf("%d ",*p);
    *value = *p;
    sleep(1);
  

    if ((i + 1) % c2 == 0)
      printf("\n");
  }
  shmdt(value);
  shmctl(shmid, IPC_RMID, NULL);
  return 0;


    }
