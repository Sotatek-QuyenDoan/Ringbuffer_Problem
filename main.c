#include <stdio.h>
#include "ringbuffer.h"
int main(void) {
    ringbuffer_init(5);

    ringbuffer_add(10);
    ringbuffer_add(20);

    int value;
    ringbuffer_remove(&value); // value should now be 10

    return 0;
}
