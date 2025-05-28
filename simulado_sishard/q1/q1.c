// Leia o PDF ou MD antes de iniciar este exercício!
// gcc q1.c -o q1 -pthread


// Faça os includes necessários aqui
// #include ...
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// Defina o tipo semt como semáforo
typedef sem_t semt;

// SÓ PODE USAR A ESTRUTURA ABAIXO, NAO PODE USAR VARIAVEIS GLOBAIS
struct semaforos {
    // Declare aqui os campos da sua sua estrutura para passar como argumento para as threads
    semt semaphore1;
    semt semaphore2;
    semt semaphore3;
    semt semaphore4;
    pthread_mutex_t mutex;
};

void *thread1(void *_arg) {
    struct semaforos *sems = (struct semaforos *)_arg;

    pthread_mutex_lock(&sems->mutex);
    printf("A\n");
    phthread_mutex_unlock(&sems->mutex);

    sem_post(&sems->semaphore2);
    sem_post(&sems->semaphore3);
    sem_post(&sems->semaphore4);


    sem_wait(&sems->semaphore1);
    sem_wait(&sems->semaphore1);
    sem_wait(&sems->semaphore1);
    
    phthread_mutex_lock(&sems->mutex);
    printf("E\n");
    pthread_mutex_unlock(&sems->mutex);

    return NULL;
}

void *thread2(void *_arg) {
    struct semaforos *sems = (struct semaforos *)_arg;
    sem_wait(&sems->semaphore2);

    pthread_mutex_lock(&sems->mutex);
    printf("B\n");
    pthread_mutex_unlock(&sems->mutex);

    sem_post(&sems->semaphore1);

    return NULL;
}

void *thread3(void *_arg) {
    struct semaforos *sems = (struct semaforos *)_arg;
    sem_wait(&sems->semaphore3);
    pthread_mutex_lock(&sems->mutex);
    printf("C\n");
    pthread_mutex_unlock(&sems->mutex);

    sem_post(&sems->semaphore1);

    return NULL;
}

void *thread4(void *_arg) {
    struct semaforos *sems = (struct semaforos *)_arg;
    sem_wait(&sems->semaphore4);
    pthread_mutex_lock(&sems->mutex);

    printf("D\n");
    pthread_mutex_unlock(&sems->mutex);
    sem_post(&sems->semaphore1);

    return NULL;
}

int main(int argc, char *argv[]) {

    // Crie TODAS as threads, voce deve utilizar semaforos para sincronizacao.
    pthread_t t1, t2, t3, t4;
    struct semaforos sems;
    sem_init(&sems.semaphore1, 0, 0);
    sem_init(&sems.semaphore2, 0, 0);
    sem_init(&sems.semaphore3, 0, 0);
    sem_init(&sems.semaphore4, 0, 0);
    pthread_mutex_init(&sems.mutex, NULL);
    pthread_create(&t1, NULL, thread1, &sems);
    pthread_create(&t2, NULL, thread2, &sems);
    pthread_create(&t3, NULL, thread3, &sems);
    pthread_create(&t4, NULL, thread4, &sems);

    // Espere por TODAS as threads
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    
    // Destrua os semáforos e mutex 
    sem_destroy(&sems.semaphore1);
    sem_destroy(&sems.semaphore2);
    sem_destroy(&sems.semaphore3);
    sem_destroy(&sems.semaphore4);
    pthread_mutex_destroy(&sems.mutex);
    
    return 0;
}
