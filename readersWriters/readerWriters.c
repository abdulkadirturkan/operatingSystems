#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define READERS 5
#define WRITERS 2

int data = 0;            // Ortak veri
int read_count = 0;      // Okuyucu sayısı

sem_t rw_mutex;          // Kaynağa erişim için (writers ve first reader)
pthread_mutex_t mutex;   // read_count için

void* reader(void* id) {
    int r_id = *(int*)id;

    while(1) {
        // Okuyucu giriş kısmı
        pthread_mutex_lock(&mutex);
        read_count++;
        if (read_count == 1)
            sem_wait(&rw_mutex);  // İlk okuyucu yazıcıyı bloke eder
        pthread_mutex_unlock(&mutex);

        // Okuma bölgesi
        printf("Okuyucu %d okuyor: %d\n", r_id, data);
        sleep(rand() % 2 + 1);

        // Okuyucu çıkış kısmı
        pthread_mutex_lock(&mutex);
        read_count--;
        if (read_count == 0)
            sem_post(&rw_mutex);  // Son okuyucu kaynağı bırakır
        pthread_mutex_unlock(&mutex);

        sleep(rand() % 2 + 1);
    }
}

void* writer(void* id) {
    int w_id = *(int*)id;

    while(1) {
        sem_wait(&rw_mutex);   // Kaynağa tek erişim
        data = rand() % 100;
        printf("Yazıcı %d yazdı: %d\n", w_id, data);
        sleep(rand() % 3 + 1);
        sem_post(&rw_mutex);

        sleep(rand() % 2 + 1);
    }
}

int main() {
    pthread_t r[READERS], w[WRITERS];
    int r_ids[READERS], w_ids[WRITERS];

    sem_init(&rw_mutex, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    // Okuyucu threadleri
    for (int i = 0; i < READERS; i++) {
        r_ids[i] = i+1;
        pthread_create(&r[i], NULL, reader, &r_ids[i]);
    }

    // Yazıcı threadleri
    for (int i = 0; i < WRITERS; i++) {
        w_ids[i] = i+1;
        pthread_create(&w[i], NULL, writer, &w_ids[i]);
    }

    // Sonsuz döngü, join ile bekleme
    for (int i = 0; i < READERS; i++)
        pthread_join(r[i], NULL);
    for (int i = 0; i < WRITERS; i++)
        pthread_join(w[i], NULL);

    sem_destroy(&rw_mutex);
    pthread_mutex_destroy(&mutex);

    return 0;
}
