#include <stdio.h>
#include <math.h>

int main(void)
{

	int i=0;
	char T[]="abcabaabcabaacbbaba";		/*The text T, for Sigma={a,b,..,y,z}, |Sigma|=26, */
	char P[]="abaa";			/*The pattern t*/
	
	int n=sizeof(T)/sizeof(T[0])-1; 	/*String size of T is n, \0 is excluded*/
	int m=sizeof(P)/sizeof(P[0])-1;		/*String size of P*/

	int s=0;
	int p=0;
	int ts=0;

	int q=29;					/*A prime number bigger than d, for the modulo operation*/
	int d=26;					/*Usually same as |Sigma|*/
	int h=((int)pow((double)d,(double)(m-1)))%q;	/*The weight of the MSB in m-digit number, in modulo q space*/

	for(i=0;i<m;++i)	/*Preprocessing, turn pattern P into an integer p, represented by its digits and modulo q*/
	{
		p=(p*d+P[i]-'a')%q;
		ts=(ts*d+T[i]-'a')%q;	/*Calucate t0*/
	}

	for(s=0;s<=n-m;++s)		/*Matching P[1..m] with T[s+1..s+m] for s=0,..,n-m*/
	{
		if(ts==p)
		{
			for(i=0;i<m;++i)
			{
				if(T[s+i]!=P[i])	/*Rule out the spurious matching who happens to have the save modulo with p*/
				{
					break;
				}
			}

			if(i==m)
			{
				printf("Matching patter at position %d of string \'%s\' for pattern \'%s\'\r\n",s,T,P);
			}		
		}

		if(s<n-m)	/*Compute the next ts if it's not the last one*/
		{
			ts=(d*(ts-h*(T[s]-'a')) + (T[s+m]-'a'))%q;
		}

		if(ts<0)	/*Guarantee ts is positive*/
		{
			ts+=q;
		}
	}

}


