### `Valgrind`

```c
valgrind --leak-check=yes ./executável
```

### `Bibliotecas`
```c
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
```

### `Semáforos`
```c
struct semaforos {
    sem_t barrier;
    sem_t sem_t2, sem_t3, sem_t4;



};
```

### `Mutex`
```c
struct semaforos {
    pthread_mutex_t mutex;
};

    pthread_mutex_lock(&sems->mutex);
    printf("A\n");
    pthread_mutex_unlock(&sems->mutex);

```



### `Mutex`
```c
    sem_init(&sems.barrier, 0, 0);
    sem_init(&sems.sem_t2, 0, 0);
    sem_init(&sems.sem_t3, 0, 0);
    sem_init(&sems.sem_t4, 0, 0);

```




