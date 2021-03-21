#include "partition.h"

// 1MB integer heap partition
uint8_t __int_heap[1024 * 1024];
// 1MB char heap partition
uint8_t __char_heap[1024 * 1024];
// 1MB float heap partition
uint8_t __float_heap[1024 * 1024];
// 1MB generic heap partition
uint8_t __generic_heap[1024 * 1024]; 

uint32_t __int_idx = 0;
uint32_t __char_idx = 0;
uint32_t __float_idx = 0;
uint32_t __generic_idx = 0;

static pthread_mutex_t __lock = PTHREAD_MUTEX_INITIALIZER;

void *__int_malloc(size_t sz) {
    void *mem;
    pthread_mutex_lock(&__lock);
    if(sizeof __int_heap - __int_idx < sz){
        pthread_mutex_unlock(&__lock);
        return NULL;
    }

    mem = &__int_heap[__int_idx];
    __int_idx += sz;
    pthread_mutex_unlock(&__lock);
    return mem;
}

void *__char_malloc(size_t sz) {
    void *mem;
    pthread_mutex_lock(&__lock);
    if(sizeof __char_heap - __char_idx < sz){
        pthread_mutex_unlock(&__lock);
        return NULL;
    }

    mem = &__char_heap[__char_idx];
    __char_idx += sz;
    pthread_mutex_unlock(&__lock);
    return mem;
}

void *__float_malloc(size_t sz) {
    void *mem;
    pthread_mutex_lock(&__lock);
    if(sizeof __float_heap - __float_idx < sz){
        pthread_mutex_unlock(&__lock);
        return NULL;
    }

    mem = &__float_heap[__float_idx];
    __float_idx += sz;
    pthread_mutex_unlock(&__lock);
    return mem;
}

void *__generic_malloc(size_t sz) {
    void *mem;
    pthread_mutex_lock(&__lock);
    if(sizeof __generic_heap - __generic_idx < sz){
        pthread_mutex_unlock(&__lock);
        return NULL;
    }

    mem = &__generic_heap[__generic_idx];
    __generic_idx += sz;
    pthread_mutex_unlock(&__lock);
    return mem;
}

void *__palloc(size_t sz, const char *type) {
    void *mem = NULL;

    if (strstr(type, "char")) {
        mem = __char_malloc(sz);
        return mem;
    }
    
    if (strstr(type, "int") || strstr(type, "long") || strstr(type, "short")) {
        mem = __int_malloc(sz);
        return mem;
    }
    
    if (strstr(type, "float") || strstr(type, "double")) {
        mem = __float_malloc(sz);
        return mem;
    }
    
    mem = __generic_malloc(sz);
    return mem;
}

void __pfree(void *mem, const char *type) {
    // doesn't do anything currently
    // you will have memory leaks
}

void __printpart(const char *type, int max) {
    uint8_t *part = NULL;
    uint8_t iter = 0;
    char fmt[256];

    if (strstr(type, "char")) {
        part = __char_heap;
        iter = sizeof(char);
        strcpy(fmt, "%p: %c\n");
    } else if (strstr(type, "int") || strstr(type, "long") || strstr(type, "short")) {
        part = __int_heap;
        iter = sizeof(int);
        strcpy(fmt, "%p: %02x\n");
    } else if (strstr(type, "float") || strstr(type, "double")) {
        part = __float_heap;
        iter = sizeof(float);
        strcpy(fmt, "%p: %.4f\n");
    } else {
        part = __generic_heap;
        iter = 1;
        strcpy(fmt, "%p: %02x\n");
    }
    
    // printf("%lu\n", sizeof(part)/1024);
    for (int i = 0; i < max*iter; i += iter) {
        printf(fmt, &part[i], part[i]);
    }
}