#include <stdio.h>
#include <stdlib.h>
#define LH +1
#define EH 0
#define RH -1
typedef int Elem;
typedef struct BSTNode{
	Elem data;
	int bf;
	struct BSTNode *lchild,*rchild;
}*BSTree,BSTNode;

void R_Rotate(BSTree *T)
{
	BSTree lc = (*T)->lchild;
	(*T)->lchild = lc->rchild;
	lc->rchild = (*T);
	*T = lc;
}

void L_Rotate(BSTree *T)
{
	BSTree rc = (*T)->rchild;
	(*T)->rchild = rc->lchild;
	rc->lchild = *T;
	*T = rc;
}

void LeftBalance(BSTree *T)
{
	BSTree lc,rd;
	lc = (*T)->lchild;
	switch(lc->bf)
	{
		case LH:
			(*T)->bf = lc->bf = EH;
			R_Rotate(T);
			break;
		case RH:
			rd = lc->rchild;
			switch(rd->bf)
			{
				case LH:
					(*T)->bf = RH;
					lc->bf = EH;
					break;
				case EH:
					(*T)->bf=lc->bf = EH;
					break;
				case RH:
					(*T)->bf = EH;
					lc->bf = LH;
					break;
			}
		rd->bf = EH;
		L_Rotate(&lc);//risk
		R_Rotate(T);
		break;
	}
}
void RightBalance(BSTree *T)
{
	BSTree lc,rd;
	lc = (*T)->rchild;
	switch(lc->bf)
	{
		case RH:
			(*T)->bf = lc->bf = EH;
			L_Rotate(T);
			break;
		case LH:
			rd = lc->lchild;
			switch(rd->bf)
			{
				case LH:
					(*T)->bf = EH;
					lc->bf = RH;
					break;
				case EH:
					(*T)->bf = lc->bf = EH;
					break;
				case RH:
					(*T)->bf = EH;
					lc->bf = LH;
					break;
			}
		rd->bf = EH;
		R_Rotate(&lc);
		L_Rotate(T);
		break;
	}
}
int InsertAVL(BSTree *T,Elem e,bool *taller)
{
	if((*T)==NULL)
	{
		(*T)=(BSTree)malloc(sizeof(BSTNode));
		(*T)->bf = EH;
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		*taller = true;
	}	
	else if(e==(*T)->data)
	{
		*taller = false;
		return 0;
	}
	else if(e<(*T)->data)
	{
		if(!InsertAVL(&(*T)->lchild,e,taller));
			return 0;
		if(*taller)
		{
			switch((*T)->bf)
			{
				case LH:
					LeftBalance(T);
					*taller = false;
					break;
				case EH:
					(*T)->bf = LH;
					*taller = true;
					break;
				case RH:
					(*T)->bf = EH;
					*taller = false;
					break;
			}
		}
	}
	else
	{
		if(!InsertAVL(&(*T)->rchild,e,taller))
			return 0;
		if(*taller)
		{
			switch((*T)->bf)
			{
				case LH:
					(*T)->bf = EH;
					*taller = false;
					break;
				case EH:
					(*T)->bf = RH;
					*taller = true;
					break;
				case RH:
					RightBalance(T);
					*taller = false;
					break;
			}
		}		
	}
	return 1;
}
void inorder(BSTree T)
{
	if(T==NULL) return;
	inorder(T->lchild);
	printf("%d,",T->data);
	inorder(T->rchild);
}
void preorder(BSTree T)
{
	if(T==NULL) return;
	printf("%d,",T->data);
	preorder(T->lchild);
	preorder(T->rchild);
}
int main()
{
	BSTree T = NULL;
	bool taller;
//	int a[]={1,23,45,34,98,9,4,35,23};
	for(int i=1;i<=9;i++)
	{
		InsertAVL(&T,i,&taller);
	}
	printf("preorder:");
	preorder(T);
	printf("\ninorder:");
	inorder(T);
	return 0;
}
