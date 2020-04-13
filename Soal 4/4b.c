#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>

#define MAX 500

int jumlah(int *n){
    int i,sum=1;
    for (i=n;i>=1;i--){
        sum=sum*i;
    }
    return sum;
}


void *penjumlahan(int *ptr)
{
    printf("%d\t",jumlah(ptr));
    pthread_exit(0);
}

void main()
{
    int arr[4][5], angka;
     int thread_counter = 0;
    key_t key = 1112;
    int *value;
    int i, j;
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    value = shmat(shmid, NULL, 0);

    //PRINT HASIL
    int index;

    pthread_t workers[20];
    pthread_attr_t attr;

    for(i = 0; i < 4; i++){
        for(j = 0; j < 5; j++){
            arr[i][j] = *value;
            angka = arr[i][j];
            pthread_attr_init(&attr);
            pthread_create(&workers[thread_counter], &attr, penjumlahan, (void *)angka);
            thread_counter++;
            sleep(1);
        }
        printf("\n");
    }


    for (i = 0; i < thread_counter; i++)
    {
        pthread_join(workers[i], NULL);

    }

       shmdt(value);
       shmctl(shmid, IPC_RMID, NULL);
}
