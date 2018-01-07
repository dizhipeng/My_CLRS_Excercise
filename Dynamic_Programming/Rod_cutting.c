#include <stdio.h>

int main(void)
{
	
	int p[]={0,1,5,8,9,10,17,17,20,24,30};   /*Price for single piece*/

	int max_rod_length=sizeof(p)/sizeof(int)-1;	
	int i=0,n=0;
	int r[100]={0};
	int max=0;
	int current_cut_r=0;
	int cuts[100]={0};
	int position=0;
	int remain=0;

	/* maximum revenue: r(n)= max{p(i)+r(n-i)}, where  1<=i<=n  */
	printf("Maximum revenue list:\r\n");
	/*r(1)=p(1)*/
	r[1]=p[1];	
	printf("r_1=%d\r\n",r[1]);

	for(n=2;n<=max_rod_length;++n)
	{
		max=p[n];	/*Don't cut*/
		cuts[n]=0;	

		for(i=1;i<=n-1;++i)		/*Cut i,n-i*/
		{
			current_cut_r=p[i]+r[n-i];

			if(current_cut_r>max)
			{
				max=current_cut_r;
				cuts[n]=i;		/*The cut occurs at i*/
			}				
		}
		r[n]=max;		

		printf("r_%d=%d",n,r[n]);

		if(cuts[n]==0){
			printf(",no cuts.\r\n");
		}
		else
		{	
			printf(",cuts:");
			remain=n;
			position=cuts[remain];
			while(position!=0)
			{
				printf("%d,",position);
				remain=n-position;
				position=cuts[remain];
			}
			printf("%d\r\n",remain);
		}
	}

	return 0;

}
