#include <stdio.h>
#include <stdlib.h>

struct AdjList //the adjecency list
{
    struct AdjListNode *head;
};
struct AdjListNode //the node
{
    int dest;
    struct AdjListNode *next;
};
struct Graph // graph struct
{
    int vertex;
    struct AdjList *arr;
    int *visited;
};
struct AdjListNode *newAdjListNode(int dest)
{
    struct AdjListNode *node = (struct AdjListNode *)malloc(sizeof(struct AdjListNode)); //allocating memory for the node.
    node->dest = dest;
    node->next = NULL;
}
struct Graph *newGraph(int vertex)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->vertex = vertex; //graph present. next up the list

    graph->arr = (struct AdjList *)malloc(vertex * sizeof(struct AdjList));
    graph->visited = malloc(vertex * sizeof(int));
    //initialize the list
    for (int i = 0; i < vertex; i++)
    {
        graph->arr[i].head = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}
void addEdge(struct Graph *graph, int source, int dest)
{
    struct AdjListNode *check = NULL;
    struct AdjListNode *node = newAdjListNode(dest);
    if (graph->arr[source].head == NULL)
    {
        node->next = graph->arr[source].head;
        graph->arr[source].head = node;
    }
    else
    {
        check = graph->arr[source].head;
        while (check->next != NULL)
        {
            check = check->next;
        }
        check->next = node;
    }
    node = newAdjListNode(source);
    if (graph->arr[dest].head == NULL)
    {
        node->next = graph->arr[dest].head;
        graph->arr[dest].head = node;
    }
    else
    {
        check = graph->arr[dest].head;
        while (check->next != NULL)
        {
            check = check->next;
        }
        check->next = node;
    }
}
void print(struct Graph *graph)
{
    for (int vertex = 0; vertex < graph->vertex; vertex++)
    {
        struct AdjListNode *after = graph->arr[vertex].head;
        printf("\n Adjacent verticies of %d\n head", vertex);
        while (after)
        {
            printf("-> %d", after->dest);
            after = after->next;
        }
        printf("\n");
    }
}
void DFS(struct Graph *graph, int vertex)
{
    struct AdjListNode *node = graph->arr[vertex].head;
    struct AdjListNode *temp = node;
    graph->visited[vertex] = 1; //has been visited
    printf("%d visited!\n", vertex);
    while (temp != NULL)
    {
        int conV = temp->dest;
        if (graph->visited[conV] == 0)
        {
            DFS(graph, conV);
        }
        temp = temp->next;
    }
}
int main()
{
    int V = 4;
    struct Graph *graph = newGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 3);
    print(graph);
    DFS(graph, 2);
    return 0;
}
