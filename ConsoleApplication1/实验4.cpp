#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Bsnode
{
	char data[20];
	struct Bsnode *Lchild, *Rchild;
}BSN,*BSP;
/**********************堆栈操作***********************/
typedef struct node
{
	BSP bsp;
	struct node *next;
}snode,*slink;
int Emptystack(slink S)
{
	if (S == NULL)
		return(1);
	else
		return(0);
}
BSP Pop(slink *top)
{
	BSP bsp2;
	slink p;
	if (Emptystack(*top))
		return(NULL);
	else
	{
		bsp2 = (*top)->bsp;
		p = *top;
		*top = (*top)->next;
		free(p);
		return(bsp2);
	}
}
void Push(slink *top, BSP bsp)
{
	slink p = NULL;
	p = (slink)malloc(sizeof(snode));
	p->bsp = bsp;
	p->next = *top;
	*top = p;
}
void Clearstack(slink *top)
{
	slink p;
	while (*top!=NULL)
	{
		p = (*top)->next;
		Pop(top);
		*top = p;
	}
	*top = NULL;
}
BSP Getstop(slink S)
{
	if (S!=NULL)
	{
		return(S->bsp);
	}
	return(NULL);
}
/**********************堆栈操作结束***********************/
BSP BSTinsert(BSP T, BSP S)
{
	BSP p, q;
	if (T == NULL)
	{
		return(S);
	}
	p = T;
	q = NULL;
	while (p)
	{
		q = p;
		if (strcmp(S->data, p->data) == 0)
		{
			free(S);
			return(T);
		}
		if (strcmp(S->data, p->data)>0)
		{
			p = p->Rchild;
		}
		else
		{
			p = p->Lchild;
		}
	}
	if (strcmp(S->data, q->data)>0)
	{
		q->Rchild = S;
	}
	else
	{
		q->Lchild = S;
	}
	return(T);
}

int isEnd(char x[], char y)
{
	int i = 0;
	while (x[i]!=NULL)
	{
		if (x[i] == y)
		{
			return(0);
		}
		i++;
	}
	return(1);
}

BSP createBst()
{
	BSP T, S;
	char key[20];
	T = NULL;
	printf("请输入英文句子，以'.'结束:");
	scanf("%s", key);
	while (isEnd(key,'.'))
	{
		S = (BSP)malloc(sizeof(BSN));
		int i = 0;
		while (key[i]!='\0')
		{		
			S->data[i] = key[i];
			i++;
		}
		S->Lchild = S->Rchild = NULL;
		T = BSTinsert(T, S);
		scanf("%s", key);
	}
	S = (BSP)malloc(sizeof(BSN));
	int i = 0;
	while (key[i] != '\0')
	{
		S->data[i] = key[i];

		i++;
	}
	S->Lchild = S->Rchild = NULL;
	T = BSTinsert(T, S);

	return(T);
}

/***********递归遍历*********
void visit(BSP T)
{
	int i;
	if (isEnd(T->data,'.') == 0)
	{
		for (i = 0;i <= T->data.w - 1;i++)
		{
			printf("%c", T->data.key[i]);
		}
	}
	else
	{
		for (i = 0; i <= T->data.w; i++)
		{
			printf("%c", T->data.key[i]);
		}
	}
	printf(" ");
}*/

/*void inOrderLDR(BSP T)
{
	if (T)
	{
		inOrderLDR(T->Lchild);
		visit(T);
		inOrderLDR(T->Rchild);
	}
}
***********递归遍历*********/
/***********非递归遍历*********/
void inOrderLDR(BSP T)
{
	int i = 0;
	BSP p = T;
	slink S = NULL;
	Push(&S, T);
	while (!Emptystack(S))
	{
		while ((p = Getstop(S)) && p)
			Push(&S, p->Lchild);
		p = Pop(&S);
		if (!Emptystack(S))
		{
			p = Pop(&S);
			while (p->data[i] != -51&&p->data[i]!='.')
			{
				printf("%c", p->data[i]);
				i++;
			}
			printf(" ");
			i = 0;
			Push(&S, p->Rchild);
		}
	}
}
/******************************/
void main()
{
	BSP T;
	int i = 0;
	do
	{
		T = createBst();
		printf("LDR序输出为：");
		inOrderLDR(T);
		printf("\n");
		printf("是否继续？是：1；否：0\n");
		scanf("%d", &i);
	} while (i);
}