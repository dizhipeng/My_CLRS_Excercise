#include <stdio.h>
#include <string.h>

int main(void)
{

	int  i=0,j=0,q=0,k=0,l=0,last=0,a=0;
	char T[]="abababacababacabaac";		/*The text T*/
	char P[]="ababaca";			/*The pattern t*/
	
	int n=sizeof(T)/sizeof(T[0])-1; 	/*String size of T is n, \0 is excluded*/
	int m=sizeof(P)/sizeof(P[0])-1;		/*String size of P*/
	//int s=sizeof(Sigma)/sizeof(Sigma[0])-1;

	int pi[50]={0};		/*Prefix function for P, for any pi[q]=max_k(k<q,Pk is suffix of Pq)*/
	memset(pi,-1,sizeof(pi));

	k=-1;	/*-1 for empty prefix*/

	for(q=1;q<m;++q)
	{
		while((k>=0)&&(P[q]!=P[k+1]))	/*Find the longest prefix in Eq-1={k in pi*[q-1],P[q]==P[k+1]}*/
		{
			k=pi[k];	
		}

		if(P[q]==P[k+1])	/*Found a k in Eq-1, or start compare from first character of P*/
		{
			++k;		/*pi[q]=1 + max_k{Eq-1}*/
		}

		pi[q]=k;
	
	}

#if 1
	k=-1;
	for(i=0;i<n;++i)
	{
		while((k>=0)&&(P[k+1]!=T[i]))	/*Try to match T[i] for all prefix pi*[k] attach with the end P[k+1]*/
		{
			k=pi[k];
		}

		if(P[k+1]==T[i])		/*Matched one character, length k adds 1*/
		{
			++k;
		}

		if(k==m-1)			/*If matched length equals pattern length, the match is successful*/
		{
			printf("Matched at position %d of string \'%s\' for pattern \'%s\'\r\n",i-k,T,P);
			k=pi[k];		/*Restart matching from the longest suffix of the matched pattern*/
		}
	}
#endif
}


