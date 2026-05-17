#include <stdio.h>

struct router
{
    int cost[10];
    int from[10];
} rt[10];

int main()
{
    int r;

    printf("Enter number of routers:\n");
    scanf("%d", &r);

    int cost[r][r];

    printf("Enter the cost matrix:\n");

    for(int i = 0; i < r; i++)
    {
        for(int j = 0; j < r; j++)
        {
            scanf("%d", &cost[i][j]);

            rt[i].cost[j] = cost[i][j];
            rt[i].from[j] = j;
        }
    }

    // Distance vector algorithm
    for(int i = 0; i < r; i++)
    {
        for(int j = 0; j < r; j++)
        {
            for(int k = 0; k < r; k++)
            {
                if(rt[i].cost[j] > cost[i][k] + rt[k].cost[j])
                {
                    rt[i].cost[j] = cost[i][k] + rt[k].cost[j];
                    rt[i].from[j] = k;
                }
            }
        }
    }

    // Print routing table
    for(int i = 0; i < r; i++)
    {
        printf("\nRouting table for router %d\n", i + 1);

        for(int j = 0; j < r; j++)
        {
            printf("%d -> %d = %d\n",
                   j + 1,
                   rt[i].from[j] + 1,
                   rt[i].cost[j]);
        }
    }
}