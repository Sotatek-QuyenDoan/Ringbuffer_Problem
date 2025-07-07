//
// Created by Nitro Tiger on 7/7/2025.
//
#include "ringbuffer.h"
#include <pthread.h>

// Không dùng malloc: dùng mảng tĩnh tối đa 1024 (bạn có thể adjust)
#define MAX_RB_SIZE 1024

static int buffer[MAX_RB_SIZE];
static int head, tail, count, capacity;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void ringbuffer_init(int size) {
    if (size > MAX_RB_SIZE) size = MAX_RB_SIZE;
    pthread_mutex_lock(&lock);
    capacity = size;
    head = tail = count = 0;
    pthread_mutex_unlock(&lock);
}

int ringbuffer_add(int value) {
    pthread_mutex_lock(&lock);
    if (count == capacity) {
        pthread_mutex_unlock(&lock);
        return -1;
    }
    buffer[tail] = value;
    tail = (tail + 1) % capacity;
    ++count;
    pthread_mutex_unlock(&lock);
    return 0;
}

int ringbuffer_remove(int *value) {
    pthread_mutex_lock(&lock);
    if (count == 0) {
        pthread_mutex_unlock(&lock);
        return -1;
    }
    *value = buffer[head];
    head = (head + 1) % capacity;
    --count;
    pthread_mutex_unlock(&lock);
    return 0;
}

int ringbuffer_is_full(void) {
    pthread_mutex_lock(&lock);
    int res = (count == capacity);
    pthread_mutex_unlock(&lock);
    return res;
}

int ringbuffer_is_empty(void) {
    pthread_mutex_lock(&lock);
    int res = (count == 0);
    pthread_mutex_unlock(&lock);
    return res;
}

int ringbuffer_size(void) {
    pthread_mutex_lock(&lock);
    int res = count;
    pthread_mutex_unlock(&lock);
    return res;
}
