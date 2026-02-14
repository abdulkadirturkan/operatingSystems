#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;
int out = 0;

sem_t empty;   // Boş slot sayısı
sem_t full;    // Dolu slot sayısı
pthread_mutex_t mutex;

void* producer(void* arg) {
    int item;

    while (1) {
        item = rand() % 100;   // Rastgele veri üret

        sem_wait(&empty);      // Boş yer bekle
        pthread_mutex_lock(&mutex); // Kritik bölge

        buffer[in] = item;
        printf("Üretildi: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);       // Dolu sayısını artır

        sleep(1);
    }
}

void* consumer(void* arg) {
    int item;

    while (1) {
        sem_wait(&full);       // Dolu yer bekle
        pthread_mutex_lock(&mutex); // Kritik bölge

        item = buffer[out];
        printf("Tüketildi: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);      // Boş sayısını artır

        sleep(2);
    }
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
