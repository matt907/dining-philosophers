#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#define N           5
#define LEFT  (i-1)%N
#define RIGHT (i+1)%N
#define THINKING    0
#define HUNGRY      1
#define EATING      2

int state[N]; //starts as THINKING
semaphore mutex = 1;
semaphore s[N]; //initial values of zero

void philosopher(int i){
   while(true){
      think();
      take_forks(i); 
      eat();
      put_forks(i);
   }
}

void take_forks(int i){
   wait(mutex);
   state[i] = HUNGRY;
   test(i);
   signal(mutex);
   wait(s[i]);
}

void put_forks(int i){
   wait(mutex);
   state[i] = THINKING;
   test(LEFT);
   test(RIGHT);
   signal(mutex);
}

void test(int i){
   if(state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING){
      state[i] = EATING;
      signal(s[i]);
   }
}