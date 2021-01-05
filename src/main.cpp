#include <iostream>
#include <cstdio>
using namespace std;

typedef struct node
{
    int row, col;
    union
    {
        ElemType val;
        struct node *ptr;
    };
    struct node *right, *down;
}CNode, *CrossLink;

typedef struct
{
    int m, n, t, nil;
    CrossLink *link;
}HNode, *HLink;

#define MaxN 100

HLink MREAD()
{
    HLink HEAD;
    CrossLink p, last, hdnode[MaxN];
    int m, n, t, k, i, current_row;
    int rrow, ccol, val;
    scanf("%d%d", &m, &n);

    if(t <= 0)
    {
        return nullptr;
    }
    k = (m>n)?m:n;
    for(i = 0; i < k; i++)
    {
        p = (CrossLink)malloc(sizeof(CNode));
        hdnode[i] = p;
        p->row = 0;
        p->col = 0;
        p->ptr = 0;
        p->right = p;
        p->down = p;
    }

    current_row = 1;
    last = hdnode[0];
    for(i = 1; i <= t; i++)
    {
        scanf("%d%d%d", &rrow, &ccol, &val);
        if(rrow > current_row)
        {
            last->right = hdnode[current_row-1];
            current_row = rrow;
            last = hdnode[rrow - 1];
        }
        p = (CrossLink)malloc(sizeof(CNode));
        p->row = rrow;
        p->col = ccol;
        p->val = val;
        last->right = p;
        last = p;
        hdnode[ccol-1]->ptr->down = p;
        hdnode[ccol-1]->ptr = p;
    }

    if(t != 0)
    {
        last->right = hdnode[current_row-1];
    }
    for(i = 0; i < k; i++)
    {
        hdnode[i]->ptr->down = hdnode[i];
    }
    HEAD = (HLink)malloc(sizeof(HNode));
    HEAD->m = m;
    HEAD->n = n;
    HEAD->t = t;
    for(i = 0; i < k; i++)
    {
        hdnode[i]->ptr = hdnode[i+1];
    }
    if(k == 0)
    {
        HEAD->ptr = HEAD;
    }
    else
    {
        hdnode[k-1]->ptr = HEAD;
        HEAD->ptr = hdnode[0];
    }
    return HEAD;
}

#define MaxN 100
void TRANSFORM(int A[][MaxN], int m, int n, int TA[][3])
{
    int i, j, t=0;
    TA[0][0] = m;
    TA[0][1] = n;
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        {
            if(A[i][j] != 0)
            {
                TA[++t][0] = i;
                TA[t][1] = j;
                TA[t][2] = A[i][j];
            }
        }
    }
    TA[0][2] = t;
}

#define MaxN 1000
void STOREAB(int A[][MaxN], int n, int B[])
{
    int i, j, k = 0;
    for(j = 0; j < n; j++)
    {
        for(i = j+1; i < n; i++)
        {
            B[k++] = A[i][j];
        }
    }
}

#define MaxN 100
int MATRIXA(int TA[][3], int A[][MaxN])
{
    int i, j;
    for(i = 1; i < TA[0][2]; i++)
    {
        A[TA[i][0]-1][TA[i][1]-1] = TA[i][2];
        A[TA[i][1]-1][TA[i][0]-1] = TA[i][2];
    }
    return TA[0][0];
}

























































