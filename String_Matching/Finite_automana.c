#include <stdio.h>
#include <string.h>

int main(void)
{

	int  i=0,j=0,q=0,k=0,l=0,last=0,a=0;
	char T[]="abababacababacabaac";		/*The text T, for Sigma={a,b,..,y,z}, |Sigma|=26, */
	char P[]="ababaca";			/*The pattern t*/
	char Sigma[]="abc";
	
	int n=sizeof(T)/sizeof(T[0])-1; 	/*String size of T is n, \0 is excluded*/
	int m=sizeof(P)/sizeof(P[0])-1;		/*String size of P*/
	int s=sizeof(Sigma)/sizeof(Sigma[0])-1;

	int delta[50][50]={0};		/*Transition function delte(q,a) is the number of matched characters when meet character a*/

	int match=1;

	int state=0;
	
	for(q=0;q<=m;++q)			/*Preprocessing: calculate delta(q,a) for all 0<=q<=m, a=Sigma[..]*/
	{
		for(j=0;j<s;++j )
		{
			a=Sigma[j];	/*a for Pqa*/
			if(q==m)
			{
				last=m-1;		/*Last position of P to find the max*/
			}
			else
			{
				last=q;
			}

			for(k=last;k>=0;--k)
			{

				if(a!=P[k])		/*character a is not equal to the last character of Pk*/
				{
					continue;	/*Not match, try a smaller k*/
				}

				match=1;
				for(l=0;l<k;++l)	/*Test whether Pk is a suffix of Pqa, if it is, then the  maximum k is found*/
				{
					if(P[l]!=P[l+(last-k)+((q==m)?1:0)])	/*P[l] for Pk: P[0~k-1]*/
					{
						match=0;
						break;
					}
				}

				if(match)		/*Pass the test, save k*/
				{
					delta[q][j]=k+1;
					break;
				}
			}
		}
	}

	state=0;
	for(i=0;i<n;i++)	/*Matching string using the finite automaton*/
	{
		state=delta[state][T[i]-'a'];	/*Successfully matched whenever the state is the size of P*/
		if(state==m)
		{
			printf("Matched at position %d of string \'%s\' for pattern \'%s\'\r\n",i-m+1,T,P);
		}

	}
}


