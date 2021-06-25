#include <stdio.h>
#include <string.h>
#define MAX 100
void getnext(char substr[],int next[],int sublen);
int kmp(char main[],char substr[],int next[],int mainlen,int sublen);
int main()
{
	char substr[MAX];
	char main[MAX];
	scanf("%s",main);
	scanf("%s",substr);
	int mainlen = strlen(main);
	int sublen = strlen(substr);
	int next[sublen];
//	char *sub = substr;
//	sub--;
	getnext(substr,next,sublen);
//	for(int i = 0;i<sublen;i++)
//	{
//		printf("%d,",next[i]);
//	}
	int i = kmp(main,substr,next,mainlen,sublen);
	printf("\n");
	printf("#%d#",i+1);
	return 0;
}
void getnext(char substr[],int next[],int sublen)
{
	int i = 0,j = -1;
	next[0] = -1;
	while(i<sublen)
	{
		if(j==-1||substr[i]==substr[j])
		{
			i++;
			j++;
			next[i] = j;
//			if(substr[i]!=substr[j]) //不相同的话 回退的慢一点  aaaaaaaaab 
			{
				next[i] = j;
			}
			else  //相同的话回退到next【j】 
			{
				next[i] = next[j];
			}
		}
		else
		{
			//不匹配的时候将查自己的next
			//j在变化 
//			printf("j = %d,next[j] = %d\n",j,next[j]);
			j=next[j]; //让j回溯； 让j发生减少；
		}
	}
	
}
int kmp(char main[],char substr[],int next[],int mainlen,int sublen)
{
	int i = 0,j = 0;
	while(i<mainlen&&j<sublen)
	{
		if(main[i]==substr[j]||j == -1)
		{
			i++;
			j++;
		}
		else
		{	
			j = next[j];
		}
	}
	if(j>=sublen)
		return i-sublen;
	else
		return -1;
}
