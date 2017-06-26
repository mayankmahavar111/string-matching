#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int count=0;
int findPair(char , char , char *, int);
int findPairChar(char , char , char *, int);
int occurence_table[20];
int compare(char *,char *);
void create_occurence_table(char * );
int getChar(char *, char, int);
int jump(char *, char *, int );
int main()
{
	int i;
	char Str[1000000],pattern[100];
	printf("Enter a String\n");
    gets(Str);
    printf("Enter a pattern\n");
    gets(pattern);
    create_occurence_table(pattern);
    for(i=0;i<strlen(pattern);i++)
        printf("%d ",occurence_table[i]);
    printf("\n");
    compare(Str,pattern);
    printf("The no.of pattern occurs in the givem string is %d",count);

}
void create_occurence_table(char *a)
{
    int i,j;
    for(i=0;i<strlen(a);i++)
    {
        occurence_table[i]=-1;
        for(j=i-1;j>=0;j--)
        {
            if(a[j]==a[i])
            {
                occurence_table[i]=j;
                break;
            }
        }
    }
}
int compare(char *Str, char *pattern)
{
    int i;
    for(i=0;i<strlen(Str);)
    {
    	printf("this is inside compare : %d\n",i);
        i+=jump(Str,pattern,i);
    }
}
int jump(char *Str, char *pattern, int k)
{
	int i,PairIndex,x;
	char pair_x;
	char pair_y;
	for(i=strlen(pattern)-1;i>=0;i--)
	{
			if(Str[k+i]!=pattern[i])
			{
				PairIndex=getChar(pattern,Str[k+i],i);
				
				if (PairIndex == -1)
				{
					//printf("Returning %d\n",i+1);
					return i+1;
				}
				pair_y=Str[k+i];
				x=findPair(pair_y,Str[k+i-1],pattern,PairIndex);
				if (x==-1)
				{
					return strlen(pattern)-1-PairIndex;
				}
				if(x>-1)
				{
					printf("  Giving %d and pair %d and %d\n",i,PairIndex,x);
					return strlen(pattern)-x-1;
				}

			}
	}
	count++;
	return 1;
}
int getChar(char *pattern, char y,int k)
{

	int i;
	for(i=k-1;i>=0;i--)
	{
		if (pattern[i]==y)
		{
			return i;
		}
	}
	return -1;
}
int findPair(char y, char x,char *pattern, int k)
{
	while(k>0)
	{
		if (pattern[k-1]==x)
		{
			return k;
		}
		if (occurence_table[k]==-1)
		{
			return -1;
		}
		else
		{
			k=occurence_table[k];
		}
	}
	return -1;
}
int findPairChar(char y,char x,char *pattern,int k)
{
		if(k<=0)
			return -1;

		if (pattern[k-1]==x)
		{
			return k-1;
		}
		else
		{
			if (occurence_table[k]!=-1)
			{
				return findPairChar(y,x,pattern,occurence_table[k]);
			}
			else
			{
				return -1;	
			}
		}
}