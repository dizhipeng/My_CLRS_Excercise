#include <stdio.h>

int partition(int a[],int p,int *q,int r);
//int quicksort(int a[],int p,int r);
int find_pivot(int a[],int p,int *q,int r);

int main(void)
{
	/*Index starts from 1 to  make the calculation of a node's left & right child in accordance to the form of a heap*/
	/*i.e. left_i=i*2 and right_i=i*2+1 */
	int a[]={2,7,16,20,4,9,19,8,5,34,10,6,15,17,18,21}; 
	
	int array_size=sizeof(a)/sizeof(a[0]);
	int i=0;
	int pos=0;

	find_pivot(a,4,&pos,array_size-6);
#if 0
	for(i=0;i<array_size;++i)
	{
		printf("%2d  ",a[i]);
		if((i+1)%5==0)
		{
			printf("\r\n");
		}
	}
#endif

	return 0;

}

/*This function change the unsorted array a[p..r] into a new array, such that a[p..q-1]<=a[q]<a[q+1..r]*/
/*Argument q is the pivot that is randomly picked*/
int partition(int a[],int p,int *q,int r)
{
	/*No need to worry about the boundary condition*/
	/*p=r or p+1=r can work perfectly*/
	
	/*Loop invariant:*/
	/*a[r] is the pivot*/
	/*a[k]<=a[r],for p<=k<=i*/
	/*a[k]>a[r],for i+1<=k<=j*/
	/*Untouched element:a[k],for j+i<=k<=r-1*/
	int i=p-1;
	int j=p;
	int temp=0;

	/*printf("1.p=%d,q=%d,r=%d\r\n",p,(*q),r);*/

	for(;j<=r-1;++j)
	{
		if(a[j]<=a[r])
		{
			++i;		/*At the moment a[i+1]>a[k]*/
			temp=a[i];
			a[i]=a[j];	/*Keep the loop invariant: a[i]<=a[k]*/
			a[j]=temp;	/*Keep the loop invariant: a[j]>a[k]*/

		}
	}

	/*Put the pivot at a[i+1]*/
	temp=a[i+1];
	a[i+1]=a[r];
	a[r]=temp;

	(*q)=i+1;
	/*printf("2.p=%d,q=%d,r=%d\r\n",p,(*q),r);*/
	return 0;
}

/*Select the rank k element*/
int select(int a[],int p,int r)
{
	int q=0;

	/*Must indicate the recursion stop condition!!*/
	if(p<r)	/*When p<r, the sort is needed*/
	{
		partition(a,p,&q,r);
		//quicksort(a,p,q-1);
		//quicksort(a,q+1,r);
	}
	
	return 0;
}

/*Finding median-of-medians of elements a[p..r], and return its position in q*/
/*This is not the partition process, thus rank of q is undetermined*/
/*BFPRT algorithm is used*/
int find_pivot(int a[],int p,int *q,int r)
{
	int i=0,j=0,k=0,temp=0,position;

	for(i=p;i<=r;i+=5)	/*Insertion sort for every 5-element group a[i..i+4]. To be legal, i,j can't exceed r*/
	{
		for(j=i+1;j<(i+5) && j<=r;++j)	/*j<=r avoids error when the group is smaller than 5*/
		{
			temp=a[j];
			for(k=j-1;k>=i && temp<a[k];--k)
			{
				a[k+1]=a[k];
			}
			a[k+1]=temp;
		}
	}
#if 1
	/*Insertion sort the median of every group*/
	for(i=p+5;i<=r;i+=5)
	{
		if((i+4)<=r)	/*group a[i..i+4] is legal*/
		{
			/*The median of group a[i..i+4]*/
			temp=a[i+2];

			position=i-3;	/*Check from the previous element*/
		}
		else		/*The tail group's size is not 5*/
		{
			/*The median is (i+r)/2*/
			temp=a[(i+r)/2];

			if(temp<a[i-3])		/*Move the previous median to the current position.*/
			{
				//printf("Copy %d to %d\r\n",a[i-3],a[(i+r)/2]);
				a[(i+r)/2]=a[i-3];	/* The first current position is not at a[i+2], so it must be handle seperately*/
			}

			position=i-3-5;		/*Check from the previous previous element*/
		}


		for(j=position;j>=p+2/*First median*/ && temp<a[j]; j-=5)
		{
			//printf("Copy %d to %d\r\n",a[j],a[j+5]);
			a[j+5]=a[j];
		}

		printf("Copy %d to %d\r\n",temp,a[j+5]);
		a[j+5]=temp;	
	}
#endif
	printf("\r\n%d\r\n",a[p+(r-p+1)/5/2*5+2]);

	for(i=0;i<r-p+1;++i)
	{

		printf("%2d  ",a[i+p]);
		if((i+1)%5==0)
		{
			printf("\r\n");
		}

	}


	return 0;


}

