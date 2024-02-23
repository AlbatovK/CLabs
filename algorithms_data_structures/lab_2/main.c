#include <stdio.h>

#include <stdlib.h>

#include "queue.h"


int main() {
    queue_t q = create_new_queue();
    do_queue(q);
    return 0;
}