#include <stdio.h>

int main()
{
    int capacity=0, leak=0, rate=0;
    int bucket=0, time=0, n=0, p[100];

    printf("Enter size of bucket\n");
    scanf("%d",&capacity);

    printf("Enter number of packets\n");
    scanf("%d",&n);

    printf("Enter size of each packets\n");

    for(int i=0;i<n;i++)
        scanf("%d",&p[i]);

    printf("Enter leak rate\n");
    scanf("%d",&rate);

    printf("Time\tIncoming\tBucket\tLeaked\tRemaining\n");

    for(int i=0;i<n;i++)
    {
        bucket += p[i];

        if(bucket > capacity)
            bucket = capacity;

        leak = (bucket < rate) ? bucket : rate;

        printf("%d\t%d\t\t%d\t%d\t%d\n",
               i+1, p[i], bucket, leak, bucket-leak);

        bucket -= leak;
    }

    time = n + 1;

    while(bucket > 0)
    {
        leak = (bucket < rate) ? bucket : rate;

        printf("%d\t0\t\t%d\t%d\t%d\n",
               time, bucket, leak, bucket-leak);

        bucket -= leak;
        time++;
    }
}