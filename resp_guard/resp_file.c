#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/*
 User-space System Responsiveness Guard
 Measures scheduling delay to estimate responsiveness
*/

long diff_ns(struct timespec a, struct timespec b) {
    return (b.tv_sec - a.tv_sec) * 1000000000L +
           (b.tv_nsec - a.tv_nsec);
}

int main() {
    struct timespec start, end;
    const int interval_ms = 100;

    printf("System Responsiveness Guard (User-space)\n");
    printf("Monitoring scheduling delays...\n\n");

    while (1) {
        clock_gettime(CLOCK_MONOTONIC, &start);

        usleep(interval_ms * 1000);

        clock_gettime(CLOCK_MONOTONIC, &end);

        long expected = interval_ms * 1000000L;
        long actual = diff_ns(start, end);
        long delay = actual - expected;

        printf("Scheduling delay: %ld microseconds\n", delay / 1000);

        if (delay > 50000) {
            printf("⚠️  WARNING: System responsiveness degraded!\n");
        }

        printf("----------------------------------\n");
        sleep(1);
    }

    return 0;
}

