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
    static int step=1;

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

    
    for (int i = 0; i < g.n; i++) {
        printf("Path from %d to %d: ", 0, i);
        if (distance[i] == INF) {
            printf("No Path\n");
        }
        else {
            print_path(0, i);
            printf("\n");
        }
    }
    
    return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF INT_MAX

typedef struct Edge {
    int end;
    int weight;
    struct Edge* next;
} Edge;

typedef struct GraphType {
    int n; // 정점의 개수
    Edge* adj_list[MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES];
int found[MAX_VERTICES];
int path[MAX_VERTICES];

void insert_edge(GraphType* g, int start, int end, int weight) {
    Edge* new_edge = (Edge*)malloc(sizeof(Edge));
    new_edge->end = end;
    new_edge->weight = weight;
    new_edge->next = g->adj_list[start];
    g->adj_list[start] = new_edge;
}

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

void shortest_path(GraphType* g, int start) {
    for (int i = 0; i < g->n; i++) {
        distance[i] = INF;
        found[i] = 0;
        path[i] = -1;
    }

    distance[start] = 0;

    for (int i = 0; i < g->n - 1; i++) {
        int u = choose(distance, g->n, found);
        found[u] = 1;

        for (Edge* e = g->adj_list[u]; e != NULL; e = e->next) {
            int w = e->end;
            if (!found[w] && distance[u] + e->weight < distance[w]) {
                distance[w] = distance[u] + e->weight;
                path[w] = u;
            }
        }
    }
}

void print_path(int start, int end) {
    if (start == end) {
        printf("%d ", start);
        return;
    }
    print_path(start, path[end]);
    printf("-> %d ", end);
}

int main() {
    GraphType g;
    g.n = 5; // 노드의 개수

    // 간선 추가 예시
    insert_edge(&g, 0, 1, 10);
    insert_edge(&g, 0, 3, 30);
    insert_edge(&g, 0, 4, 100);
    insert_edge(&g, 1, 2, 50);
    insert_edge(&g, 2, 4, 10);
    insert_edge(&g, 3, 2, 20);
    insert_edge(&g, 3, 4, 60);

    shortest_path(&g, 0); // 시작 노드 (예: 0)
    print_path(0, 4);     // 경로 출력 예시 (0에서 4까지)

    return 0;
}
