

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Конфигурация потоков
typedef struct {
    int num;     // порядковый номер
    int timer;   // время паузы в сек.
} ThreadCfg;

// Основная функция потока
void* thread_work(void* arg) {
    ThreadCfg* cfg = (ThreadCfg*)arg;
    sleep(cfg->timer); // задержка
    printf("[Поток %d] Выполнено за %d сек.\n", cfg->num+1, cfg->timer);
    free(arg); // освобождаем конфиг
    return NULL;
}

int main() {
    char user_cmd;
    do {
        pthread_t pool[5]; // массив из 5 потоков
        int delays[5];     // массив задержек

        // Настройка параметров
        for(int i = 0; i < 5; i++) {
            printf("Задержка потока %d (сек): ", i+1);
            scanf("%d", &delays[i]);
        }

        // Запуск потоков
        for(int i = 0; i < 5; i++) {
            ThreadCfg* cfg = malloc(sizeof(ThreadCfg));
            cfg->num = i;
            cfg->timer = delays[i];
            
            if(pthread_create(&pool[i], NULL, thread_work, cfg)) {
                puts("Ошибка инициализации!");
                return 1;
            }
            printf("> Поток %d запущен\n", i+1);
        }

     

        // Ожидание завершения
        for(int i = 0; i < 5; i++) {
            pthread_join(pool[i], NULL);
        }

        puts("Все операции завершены!\n");
        printf("Повторить? (x - выход, др. клавиша - повтор): ");
        scanf(" %c", &user_cmd);
        
    } while(user_cmd != 'x');

    return 0;
}
