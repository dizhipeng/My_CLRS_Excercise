#include <stdio.h>

void print_optimal_multiplication(int s[][20],int head,int tail);

int main(void)
{
	int p[]={30,35,15,5,10,20,25};  /*the number of rows is p[i-1] and the number of column is p[i], in terms of  Matrix M[i]*/


	int number_of_matrix=sizeof(p)/sizeof(int)-1;
	if(number_of_matrix>20)
		number_of_matrix=20;

	int m[20][20]={0}; 	/*Minimum Multiplication cost for 1..n is m[1][n]*/
	int i=0,l=0,j=0,k=0;
	int min=0,current_cost;
	int s[20][20]={0};	/*Optimal slice position for current multiplication 1..n matrix*/
	/* the caculation of multiplication cost: m[i,j]=min{m[i,k]+m[k+1,j]+p[i-1]p[k]p[j]},for every i<=k<j */
	/* the order of calculation: (1,1);...;(n,n); */
	/* then (1,2)->(1,1),(2,2); (2,3)->(2,2),(3,3);...;(n-1,n)->(n-1,n-1),(n,n) */
	/* then (1,3)->(1,1),(2,3),(1,2)(3,3); (2,4)->(2,2),(3,4),(2,3),(4,4); (n-2,n)->(n-2,n-2),(n-1,n),(n-2,n-1),(n,n)*/
	/*...*/
	/* then (1,n)->....*/
	/* for every line, the gap l=1,2,3...,n-1*/
	
	for(l=1;l<=number_of_matrix-1;++l)
	{
		for(i=1;i<=number_of_matrix-l;++i)
		{
			j=i+l;
			k=i;
			min=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
			s[i][j]=k;

			for(k=i+1;k<j;++k)
			{
				current_cost=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j];
				if(current_cost<min)
				{
					min=current_cost;
					s[i][j]=k;
				}
			}
			m[i][j]=min;	
		}	
	}
	
	printf("The multiplication of M1*M2*..*Mn which has the minimum cost is:\r\n");
	print_optimal_multiplication(s,1,number_of_matrix);
	printf("\r\n");

	return 0;
}

void print_optimal_multiplication(int s[][20],int head,int tail)
{
	int slice=s[head][tail];
	if(slice==0)
	{
		printf("A%d",tail);
		return;
	}
	
	printf("(");	
	print_optimal_multiplication(s,head,slice);
	print_optimal_multiplication(s,slice+1,tail);
	printf(")");
}
