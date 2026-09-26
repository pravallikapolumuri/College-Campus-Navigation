#include <stdio.h>
#include <limits.h>

#define MAX 10

// Campus locations
char *locations[MAX] = {
    "Main Gate",
    "Administration Block",
    "CSE Block",
    "Library",
    "Laboratory",
    "Canteen",
    "Auditorium",
    "Hostel",
    "Sports Ground",
    "Parking Area"
};

// Display campus locations
void displayLocations()
{
    int i;

    printf("\n========== CAMPUS LOCATIONS ==========\n");

    for (i = 0; i < MAX; i++)
    {
        printf("%d. %s\n", i + 1, locations[i]);
    }
}

// Display graph
void displayGraph(int graph[MAX][MAX])
{
    int i, j;

    printf("\n========== CAMPUS GRAPH ==========\n");

    for (i = 0; i < MAX; i++)
    {
        printf("%s -> ", locations[i]);

        for (j = 0; j < MAX; j++)
        {
            if (graph[i][j] != 0)
            {
                printf("%s(%d m)  ", locations[j], graph[i][j]);
            }
        }

        printf("\n");
    }
}

// BFS Traversal
void BFS(int graph[MAX][MAX], int start)
{
    int queue[MAX];
    int visited[MAX] = {0};
    int front = 0, rear = 0;
    int current, i;

    queue[rear++] = start;
    visited[start] = 1;

    printf("\nBFS Traversal:\n");

    while (front < rear)
    {
        current = queue[front++];

        printf(" -> %s", locations[current]);

        for (i = 0; i < MAX; i++)
        {
            if (graph[current][i] != 0 && !visited[i])
            {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    printf("\n");
}

// DFS Utility Function
void DFSUtil(int graph[MAX][MAX], int current, int visited[MAX])
{
    int i;

    visited[current] = 1;

    printf(" -> %s", locations[current]);

    for (i = 0; i < MAX; i++)
    {
        if (graph[current][i] != 0 && !visited[i])
        {
            DFSUtil(graph, i, visited);
        }
    }
}

// DFS Traversal
void DFS(int graph[MAX][MAX], int start)
{
    int visited[MAX] = {0};

    printf("\nDFS Traversal:\n");

    DFSUtil(graph, start, visited);

    printf("\n");
}

// Find vertex with minimum distance
int minDistance(int distance[MAX], int visited[MAX])
{
    int min = INT_MAX;
    int minIndex = -1;
    int i;

    for (i = 0; i < MAX; i++)
    {
        if (!visited[i] && distance[i] < min)
        {
            min = distance[i];
            minIndex = i;
        }
    }

    return minIndex;
}

// Dijkstra's Algorithm
void Dijkstra(int graph[MAX][MAX], int source, int destination)
{
    int distance[MAX];
    int visited[MAX] = {0};
    int parent[MAX];
    int i, count, current;
    int path[MAX];
    int pathLength = 0;

    // Initialize
    for (i = 0; i < MAX; i++)
    {
        distance[i] = INT_MAX;
        parent[i] = -1;
    }

    distance[source] = 0;

    // Dijkstra
    for (count = 0; count < MAX - 1; count++)
    {
        current = minDistance(distance, visited);

        if (current == -1)
            break;

        visited[current] = 1;

        for (i = 0; i < MAX; i++)
        {
            if (!visited[i] &&
                graph[current][i] != 0 &&
                distance[current] != INT_MAX &&
                distance[current] + graph[current][i] < distance[i])
            {
                distance[i] = distance[current] + graph[current][i];
                parent[i] = current;
            }
        }
    }

    if (distance[destination] == INT_MAX)
    {
        printf("\nNo path exists between the selected locations.\n");
        return;
    }

    // Construct path
    current = destination;

    while (current != -1)
    {
        path[pathLength++] = current;
        current = parent[current];
    }

    printf("\n========== SHORTEST PATH ==========\n");

    printf("From      : %s\n", locations[source]);
    printf("To        : %s\n", locations[destination]);

    printf("Path      : ");

    for (i = pathLength - 1; i >= 0; i--)
    {
        printf("%s", locations[path[i]]);

        if (i != 0)
            printf(" -> ");
    }

    printf("\nDistance  : %d meters\n", distance[destination]);
}

// Main Function
int main()
{
    /*
       Graph representation using adjacency matrix.

       0 means there is no direct path.
       Other values represent distance in meters.
    */

    int graph[MAX][MAX] =
    {
        // MG   AB   CSE  LIB  LAB  CAN  AUD  HOS  SPG  PAR
        { 0,  100, 300,   0,   0,   0,   0,   0,   0, 150 }, // Main Gate
        {100,    0, 200, 150,   0,   0,   0,   0,   0,   0 }, // Administration
        {300,  200,   0, 100, 120,   0,   0,   0,   0,   0 }, // CSE
        {  0,  150, 100,   0,  80, 100, 200,   0,   0,   0 }, // Library
        {  0,    0, 120,  80,   0,  70,   0, 150,   0,   0 }, // Laboratory
        {  0,    0,   0, 100,  70,   0, 150,   0, 200,   0 }, // Canteen
        {  0,    0,   0, 200,   0, 150,   0, 180, 100,   0 }, // Auditorium
        {  0,    0,   0,   0, 150,   0, 180,   0, 250, 100 }, // Hostel
        {  0,    0,   0,   0,   0, 200, 100, 250,   0, 150 }, // Sports Ground
        {150,    0,   0,   0,   0,   0,   0, 100, 150,   0 }  // Parking
    };

    int choice;
    int start, destination;

    printf("\n============================================\n");
    printf("   COLLEGE CAMPUS NAVIGATION SYSTEM\n");
    printf("============================================\n");

    while (1)
    {
        printf("\n========== MENU ==========\n");
        printf("1. Display Campus Locations\n");
        printf("2. Display Campus Graph\n");
        printf("3. BFS Traversal\n");
        printf("4. DFS Traversal\n");
        printf("5. Dijkstra Shortest Path\n");
        printf("6. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                displayLocations();
                break;

            case 2:
                displayGraph(graph);
                break;

            case 3:
                displayLocations();

                printf("\nEnter starting location number: ");
                scanf("%d", &start);

                if (start < 1 || start > MAX)
                {
                    printf("Invalid location!\n");
                }
                else
                {
                    BFS(graph, start - 1);
                }
                break;

            case 4:
                displayLocations();

                printf("\nEnter starting location number: ");
                scanf("%d", &start);

                if (start < 1 || start > MAX)
                {
                    printf("Invalid location!\n");
                }
                else
                {
                    DFS(graph, start - 1);
                }
                break;

            case 5:
                displayLocations();

                printf("\nEnter starting location number: ");
                scanf("%d", &start);

                printf("Enter destination location number: ");
                scanf("%d", &destination);

                if (start < 1 || start > MAX ||
                    destination < 1 || destination > MAX)
                {
                    printf("Invalid location!\n");
                }
                else
                {
                    Dijkstra(graph, start - 1, destination - 1);
                }
                break;

            case 6:
                printf("\nThank you for using Campus Navigation System!\n");
                return 0;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}