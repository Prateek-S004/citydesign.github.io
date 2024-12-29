#include <stdio.h>
#include <stdlib.h>

void bfs(float m[10][10], int v, int source)
{
    int queue[20];
    int front = 0;
    int rear = 0;
    int u, i;
    int visited[10];

    for (i = 0; i < v; i++)
        visited[i] = 0;

    queue[rear] = source;
    visited[source] = 1;

    printf("The BFS Traversal is... \n");

    while (front <= rear)
    {
        u = queue[front];
        printf("%d\t", u);
        front++;

        for (i = 0; i < v; i++)
        {
            if (m[u][i] != 0 && visited[i] == 0)
            {
                visited[i] = 1;
                rear++;
                queue[rear] = i;
            }
        }
    }
}

int main()
{
    int v = 5;
    float m[10][10] = {
        {0, 7, 9.4, 9.4, 7},
        {7, 0, 5.2, 8.8, 8.2},
        {9.4, 5.2, 0, 8.8, 7},
        {9.4, 8.8, 8.8, 0, 5.2},
        {7, 8.2, 7, 5.2, 0}
    };

    int source = 0;  // Starting from Golf Course (1)
    bfs(m, v, source);

    return 0;
}
