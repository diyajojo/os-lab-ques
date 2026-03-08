#include <stdio.h>

void leaky_bucket(int capacity, int rate, int n, int packets[]) {
    int bucket = 0;

    printf("Time\tIncoming\tBucket\tLeaked\tRemaining\n");

    for (int i = 0; i < n; i++) {
        int incoming = packets[i];
        printf("%d\t%d\t\t", i + 1, incoming);

        bucket = bucket + incoming;

        if (bucket > capacity) {
            int dropped = bucket - capacity;
            bucket = capacity;
            printf("%d(Dropped %d)\t", bucket, dropped);
        } 
        else {
            printf("%d\t\t", bucket);
        }

        int leaked;
        if (bucket >= rate)
            leaked = rate;
        else
            leaked = bucket;

        bucket = bucket - leaked;

        printf("%d\t%d\n", leaked, bucket);
    }

    int time = n + 1;

    while (bucket > 0) {
        int leaked;

        if (bucket >= rate)
            leaked = rate;
        else
            leaked = bucket;

        printf("%d\t0\t\t%d\t%d\t%d\n", time, bucket, leaked, bucket - leaked);

        bucket = bucket - leaked;
        time++;
    }
}

int main() {
    int capacity, rate, n;

    printf("Enter bucket capacity: ");
    scanf("%d", &capacity);

    printf("Enter leak rate: ");
    scanf("%d", &rate);

    printf("Enter number of packets: ");
    scanf("%d", &n);

    int packets[n];

    printf("Enter packet sizes:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &packets[i]);
    }

    leaky_bucket(capacity, rate, n, packets);

    return 0;
}