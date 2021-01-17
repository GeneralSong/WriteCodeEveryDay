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

void MOVE(int A[], int n, int k)
{
    int count, i;
    int tmp;
    for(count = 1; count <= k; count++)
    {
        tmp = A[n-1];
        for(i = n-1; i >= 0; i--)
        {
            A[i+1] = A[i];
        }
        A[0] = tmp;
    }
}

void MOVE1(int A[], int n, int k)
{
    int count = 1, i = 0, j = 0;
    int temp;
    while(count < n)
    {
        j = (j+k)%n;
        if(j != i)
        {
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
        else
        {
            i++;
            j++;
        }
        count++;
    }
}


void REVERSE(int A[], int from, int to)
{
	int temp;
	int i;
	for(i = 0; i < (to-from+1)/2; i++)
	{
		temp = A[from+i];
		A[from+i] = A[to-i];
		A[to-i] = temp;
	}
}

void MOVE2(int A[], int n, int k)
{
	REVERSE(A, n-k, n-1);
	REVERSE(A, 0, n-k-1);
	REVERSE(A, 0, n-1);
}

#define MaxN 100
#define M 3*n-2
void EXSTORE(int A[][MaxN], int n, int B[M])
{
	int i, j, k;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(A[i][j] != 0)
			{
				k = 2 * i + j - 3;
				B[k] = A[i][j];
			}
		}
	}
}

#define MaxN 100
int MULT(int A[][MaxN], int n)
{
	int i, j, s=1;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n;  j++)
		{
			scanf("%d",&A[i][j]);
		}
	}	
	for(i = 0; i < n; i++)
	{
		s = s * A[i][i] * A[i][n-i-1];
	}
	if(A[n/2][n/2] != 0)
	{
		s/=A[n/2][n/2];
	}
}

#define MaxN 100
int ACCUMULATE(int A[][MaxN], int m, int n)
{
	int sum = 0;
	int k;
	for(k = 0; k < n; k++)
	{
		sum += A[0][k];
		sum += A[m-1][k];
	}
	for(k = 1; k < m-1; k++)
	{
		sum += A[k][0];
		sum += A[k][n-1];
	}
	return sum;
}

#define MaxN 100
void REVOLVE(int A[][MaxN], int n)
{
	int i, j;
	int temp;
	for(i = 0; i < n/2; i++)
	{
		for(j = i; j < n-i-1; j++)
		{
			temp = A[i][j];
			A[i][j] = A[n-j-1][i];
			A[n-j-1][i] = A[n-i-1][n-j-1];
			A[n-i-1][n-j-1] = A[j][n-i-1];
			A[j][n-i-1] = temp;
		}
	}

}

#define MaxN 100
int SADDLE(int A[][MaxN], int m, int n)
{
	int min, max;
	int i, j, ii, jj;
	for(i = 0; i < m; i++)
	{	
		min = A[i][0];
		jj = 0;
		for(j = 1; j < n; j++)
		{
			if(A[i][j] < min)
			{
				min = A[i][j];
				jj = j;
			}
		}
		max = A[i][j];
		ii = 0;
		while(ii < m && max >= A[ii][jj])
		{
			ii++;
			if(ii > m-1)
			{
				return A[i][jj];
			}
		}
	}
	return 0;
}








































