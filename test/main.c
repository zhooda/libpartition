#include "../partition.h"
#include <stdint.h>

typedef struct test_struct {
    int value;
    char *name;
    char *function;
} test_t;

int main(int argc, char **argv) {

    int *p = palloc(sizeof(int32_t), int32_t);

    for (int i = 0; i < 10; i++) {
        p[i] = i;
    }

    printf("allocating for ints\n");
    int *i8  = palloc(sizeof(int8_t), int);
    int *i16 = palloc(sizeof(int16_t), int);
    int *i32 = palloc(sizeof(int32_t), int);
    int *i64 = palloc(sizeof(int64_t), int64_t);

    test_t *StructTest = palloc(sizeof(test_t), test_t);

    palloc(sizeof(uint32_t), char);
    palloc(sizeof(uint32_t), float);

    for (int i = 0; i < 10; i++) {
        printf("%d %s", p[i], (i==9) ? "" : "-> ");
    }
}