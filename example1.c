/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
    int data;
    struct Node *next;
} NODE;
// pentru simplitate, folosim int uri pt a numi restaurantele/locatiile
// ex: 1 - restaurantul 1 si tot asa

typedef struct Graph
{
    int v;
    int *vis;
    struct Node **alst;
} GPH;

typedef struct Stack
{
    int t;
    int scap;
    int *arr;
} STACK;

NODE *create_node(int val)
{
    NODE *newnode = (NODE*)malloc(sizeof(NODE));
    newnode->data = val;
    newnode->next = NULL;
    return newnode;
}

void add_edge(GPH *g, int src, int dest)
{
    NODE *node = create_node(dest);
    node->next = g->alst[src];
    g->alst[src] = node;
    node = create_node(src);
    node->next = g->alst[dest];
    g->alst[dest] = node;
}

GPH *create_g(int nrv)
{
    GPH *g = malloc(sizeof(GPH));
    g->v = nrv;
    g->alst = malloc(nrv * sizeof(NODE*));
    g->vis = malloc(sizeof(int) * nrv);

    for (int i = 0; i < nrv; i++)
    {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }
    return g;
}

STACK *create_s(int scap)
{
    STACK *s = malloc(sizeof(STACK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;
    return s;
}

void push(int pshd, STACK *s)
{
    s->t = s->t + 1;
    s->arr[s->t] = pshd;
}

void DFS(GPH *g, STACK *s, int v_nr)
{
    NODE *adj_list = g->alst[v_nr];
    NODE *aux = adj_list;
    g->vis[v_nr] = 1;
    printf("%d ", v_nr);
    push(v_nr, s);
    while (aux != NULL)
    {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0)
            DFS(g, s, con_ver);
        aux = aux->next;
    }
}

void insert_edges(GPH *g, int edg_nr, int nrv)
{
    int src, dest, i;
    printf("adauga %d muchii (de la 1 la %d)\n", edg_nr, nrv);
    for (i = 0; i < edg_nr; i++)
    {
        scanf("%d%d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void wipe(GPH *g, int nrv)
{
    for (int i = 0; i < nrv; i++)
    {
        g->vis[i] = 0;
    }
}

void canbe(GPH *g, int nrv, STACK *s1, STACK *s2) // 0 sau 1 daca poate fi sau nu ajuns
{
    int *canbe = calloc(5, sizeof(int));
    for (int i = 0; i < nrv; i++) // aici i tine loc de numar adica de restaurant
    {
        for (int j = 0; j < 5; j++)
        {
            DFS(g, s1, i);
            wipe(g, nrv);
            DFS(g, s2, j);
            for (int j = 0; j < nrv; j++)
                for (int i = 0; i < nrv; i++)
                    if ((s1->arr[i] == j) && (s2->arr[j] == i))
                        *canbe = 1;
        }
    }
}

int main()
{

    int nrv;
    int edg_nr;

    printf("cate noduri are graful? ");
    scanf("%d", &nrv);

    printf("cate muchii are graful? ");
    scanf("%d", &edg_nr);

    GPH *g = create_g(nrv);

    STACK *s1 = create_s(2 * nrv);
    STACK *s2 = create_s(2 * nrv);

    insert_edges(g, edg_nr, nrv);

    canbe(g, nrv, s1, s2);
}