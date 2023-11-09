// 1번 방법

/*
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 // 무한대 (연결이 없는 경우)

typedef struct GraphType {
    int n; // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES]; // 가중치
} GraphType;

int distance[MAX_VERTICES]; // 시작정점으로부터의 최단경로 거리
int found[MAX_VERTICES];    // 방문한 정점 표시
int path[MAX_VERTICES];     // 최단경로 상의 이전 정점을 추적

int choose(int distance[], int n, int found[]) {
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (i = 0; i < n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

void print_path(int start, int end) {
    if (start == end) {
        printf("%d ", start);
        return;
    }
    print_path(start, path[end]);
    printf("-> %d ", end);
}

void print_status(GraphType* g) // 상태 출력
{
    static int step = 1;

    printf("STEP %d: ", step++);
    printf("distance: ");

    for (int i = 0; i < g->n; i++) {

        if (distance[i] == INF)
            printf(" * ");
        else
            printf("%2d ", distance[i]);
    }

    printf("\n");
    printf("        found:    ");

    for (int i = 0; i < g->n; i++)
        printf("%2d ", found[i]);
    printf("\n\n");
}

void shortest_path(GraphType* g, int start) {
    int i, u, w;

    for (i = 0; i < g->n; i++) { // 초기화
        distance[i] = g->weight[start][i];
        if (distance[i] != INF && i != start) {
            path[i] = start;
        }
        else {
            path[i] = -1;
        }
        found[i] = FALSE;
    }

    found[start] = TRUE;    // 시작 정점 방문 표시
    distance[start] = 0;

    for (i = 0; i < g->n - 1; i++) {
        print_status(g);
        u = choose(distance, g->n, found);
        found[u] = TRUE;

        for (w = 0; w < g->n; w++) {
            if (!found[w]) {
                if (distance[u] + g->weight[u][w] < distance[w]) {
                    distance[w] = distance[u] + g->weight[u][w];
                    path[w] = u;
                }
            }
        }
    }
}

int main(void) {
    GraphType g = { 10, // 노드의 개수
      {
        { 0, 3, INF, INF, INF, 11, 12, INF, INF, INF }, // 1
        { 3, 0, 5, 4, 1, 7, 8, INF, INF, INF }, // 2
        { INF, 5, 0, 2, INF, INF, 6, 5, INF, INF }, // 3
        { INF, 4, 2, 0, 13, INF, INF, 14, INF, 16 }, // 4
        { INF, 1, INF, 13, 0, 9, INF, INF, 18, 17 }, // 5
        { 11, 7, INF, INF, 9, 0, INF, INF, INF, INF }, // 6
        { 12, 8, 6, INF, INF, INF, 0, 13, INF, INF }, // 7
        { INF, INF, 5, 14, INF, INF, 13, 0, INF, 15 }, // 8
        { INF, INF, INF, INF, INF, INF, INF, INF, 0, 10 }, // 9
        { INF, INF, INF, INF, 17, INF, INF, 15, 10, 0 } // 10
      }
    };

    shortest_path(&g, 0); // 시작 정점을 0으로 설정



    return 0;
}
*/

// 2번 방법
/*
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>


#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphNode {
    int vertex;
    int weight;
    struct GraphNode* next;
} GraphNode;

typedef struct GraphType {
    int n;   // 정점의 개수
    GraphNode* adjList[MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES]; // 시작 정점으로부터의 최단 경로 거리
int found[MAX_VERTICES]; // 방문한 정점 표시

// 그래프 초기화
void init_graph(GraphType* g, int n) {
    g->n = n;
    for (int i = 0; i < n; i++) {
        g->adjList[i] = NULL;
    }
}

// 간선 넣기
void insert_edge(GraphType* g, int u, int v, int weight) {
    GraphNode* node = (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex = v;
    node->weight = weight;
    node->next = g->adjList[u];
    g->adjList[u] = node;
}

// 작은 수 결정
int choose(int distance[], int n, int found[]) {
    int min = INF;
    int minpos = -1;
    for (int i = 0; i < n; i++) {
        if (distance[i] < min && !found[i]) {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

// 최단 경로 찾기
void shortest_path(GraphType* g, int start) {
    for (int i = 0; i < g->n; i++) {
        distance[i] = INF;
        found[i] = FALSE;
    }

    distance[start] = 0;

    for (int i = 0; i < g->n - 1; i++) {
        printf("Distance: \n");
        for (int j = 0; j < g->n; j++)
            if (distance[j] == INF)
                printf(" * ");
            else
                printf("%d ", distance[j]);
        printf("\n");

        printf("Found: ");
        for (int j = 0; j < g->n; j++)
            printf("%d ", found[j]);
        printf("\n");

        int u = choose(distance, g->n, found);
        found[u] = TRUE;

        for (GraphNode* node = g->adjList[u]; node != NULL; node = node->next) {
            int v = node->vertex;
            if (!found[v] && distance[u] + node->weight < distance[v]) {
                distance[v] = distance[u] + node->weight;
            }
        }
    }
}

void free_graph(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        GraphNode* node = g->adjList[i];
        while (node != NULL) {
            GraphNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
}

int main(void) {
    GraphType g;
    init_graph(&g, 10); // 10개의 정점을 가진 그래프를 초기화

    // 그래프 선언(배열로 선언한 후 변경)
    int adj_matrix[10][10] = {
    {0, 3, INF, INF, INF, 11, 12, INF, INF, INF},
    {3, 0, 5, 4, 1, 7, 8, INF, INF, INF},
    {INF, 5, 0, 2, INF, INF, 6, 5, INF, INF},
    {INF, 4, 2, 0, 13, INF, INF, 14, INF, 16},
    {INF, 1, INF, 13, 0, 9, INF, INF, 18, 17},
    {11, 7, INF, INF, 9, 0, INF, INF, INF, INF},
    {12, 8, 6, INF, INF, INF, 0, 13, INF, INF},
    {INF, INF, 5, 14, INF, INF, 13, 0, INF, 15},
    {INF, INF, INF, INF, INF, INF, INF, INF, 0, 10},
    {INF, INF, INF, INF, 17, INF, INF, 15, 10, 0}
    };

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (adj_matrix[i][j] != INF) {
                insert_edge(&g, i, j, adj_matrix[i][j]);
            }
        }
    }

    // 최단 경로를 찾기
    shortest_path(&g, 0);


    // 메모리 해제
    free_graph(&g);

    return 0;
}
*/
