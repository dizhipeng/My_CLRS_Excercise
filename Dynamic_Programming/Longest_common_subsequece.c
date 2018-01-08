#include <stdio.h>

int main(void)
{
	char x[]="ABCBDAB";
	char y[]="BDCABA";

	int x_len=sizeof(x)/sizeof(char)-1;
	int y_len=sizeof(y)/sizeof(char)-1;
	int c[50][50]={0};
	int i=0,j=0;
	int max=0;
	char lcs[50]={0};
	int head=0;		/*Record the leading zeros in lcs caused by reversely copying*/

	/*The length of LCS of x,y: c(i,j) is:*/
	/*0, if i=j=0*/
	/*c(i-1,j-1)+1, if x[i]==y[j]*/
	/*max{c(i-1,j),(i,j-1)}, if x[i]!=y[j]*/

	for(i=1;i<=x_len;++i)
	{
		for(j=1;j<=y_len;++j)
		{
			if(x[i-1]==y[j-1])	/*index start at 0*/
			{
				c[i][j]=c[i-1][j-1]+1;
			}
			else
			{
				max=(c[i][j-1]>c[i-1][j])?c[i][j-1]:c[i-1][j];	
				c[i][j]=max;
			}
		}
	}
	
	i=x_len;
	j=y_len;
	head=i+1;
	while(i>0&&j>0)
	{
		if(x[i-1]==y[j-1])		/*Current character is included in LCS, goes to the upper-left coner to process c(i-1,j-1).*/
		{
			lcs[i]=x[i-1];	/*Copy current character into LCS, both reversly*/
			--i;
			--j;
			--head;
		}
		else			/*Current character is not included in LCS, goes left or up to process,*/
					/*depends on which on is maximum.*/
		{
			if(c[i-1][j]>c[i][j-1])		/*Go up*/
			{
				--i;
			}
			else									/*Go left*/
			{
				--j;
			}
		}
	}
	
	printf("The LCS of x=\"%s\" and y=\"%s\" is: %s\r\n",x,y,lcs+head);
	
}
