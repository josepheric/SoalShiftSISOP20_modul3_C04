# SoalShiftSISOP20_modul3_C04

#Nomer 4
4a
Diminta untuk membuat program yang mampu melakukan perkalian matriks dengan multithreading dan membagikan jawabannya ke shared memory untuk digunakan program 4b
```
/Each thread computes single element in the resultant matrix
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
```
Bagian diatas adalah fungsi untuk menghitung perkalian matriks dengan multithread
```
 key_t exchangeKey = 1112;
   int shmid = shmget(exchangeKey,22,0666| IPC_CREAT);
   //Attach SharedMemory
   int *value =  shmat(shmid,NULL,0);
```
Bagian ini adalah bagian dimana shared memory dibuat
```
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
  ```
  Bagian diatas adalah dimana value dari matriks hasil dikirimkan melalui shared memory
  
  
  #4b
  ```
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
  ```
  Pada soal 4b, matriks hasil didapatkan dengan mengakses shared memory dengan key yang sama.
  
  #4c
  Pada 4c, dibuat program dengan 2 pipes untuk menjalankan perintah yang diminta
  ```
  pid_t pid;
    int status;
    int p[2];
    pipe(p);
    pid=fork();
    if(pid<0){
        exit(EXIT_FAILURE);
    }
    else if(pid==0){
        dup2(p[1],STDOUT_FILENO);//child
        close(p[0]);
        close(p[1]);
        char *argv[]={"ls",NULL};
        execv("/bin/ls",argv);
    }
    else{ //parent
        while(wait(&status)>0);
        dup2(p[0],STDIN_FILENO);
        close(p[1]);
        close(p[0]);
        char *argv1[]={"wc","-l",NULL};
        execv("/usr/bin/wc",argv1);
    }
    return 0;
}
```
Kesulitan mengerjakan:
Soal nomer 1 dan 2 terlalu kompleks dan sangat sulit untuk dikerjakan, apalagi dengan batas waktu yang hanya 5 hari
Soal nomer 3 masih banyak ditemukan bug pada program dikarenakan syarat2 soal yang sangat detail , sehingga masih sangat sulit untuk dikerjakan
Pada soal nomer 4 ada kesulitan dalam menggunakan shared memory
  
