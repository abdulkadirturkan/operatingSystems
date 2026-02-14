#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5  // Filozof sayısı

sem_t chopsticks[N]; // Her çubuk için semaphore

void* philosopher(void* num) {
    int id = *(int*)num;

    while(1) {
        printf("Filozof %d düşünüyor 🍵\n", id);
        sleep(rand() % 3 + 1); // Düşünme süresi

        // Deadlock önlemek için küçük filozof ID önce küçük çubuğu alır
        int left = id;
        int right = (id + 1) % N;

        if (id % 2 == 0) {  // Çift ID önce sağ çubuğu alır
            sem_wait(&chopsticks[right]);
            sem_wait(&chopsticks[left]);
        } else {            // Tek ID önce sol çubuğu alır
            sem_wait(&chopsticks[left]);
            sem_wait(&chopsticks[right]);
        }

        printf("Filozof %d yiyor 🍝\n", id);
        sleep(rand() % 2 + 1); // Yemek süresi

        sem_post(&chopsticks[left]);
        sem_post(&chopsticks[right]);
    }
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    // Semaphore’ları başlat
    for (int i = 0; i < N; i++)
        sem_init(&chopsticks[i], 0, 1);

    // Threadleri başlat
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Threadleri bekle (sonsuz döngüde çalışıyorlar)
    for (int i = 0; i < N; i++)
        pthread_join(philosophers[i], NULL);

    return 0;
}
