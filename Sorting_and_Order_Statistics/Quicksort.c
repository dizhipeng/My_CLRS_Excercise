#include <stdio.h>

int partition(int a[],int p,int *q,int r);
int quicksort(int a[],int p,int r);


int main(void)
{
	/*Index starts from 1 to  make the calculation of a node's left & right child in accordance to the form of a heap*/
	/*i.e. left_i=i*2 and right_i=i*2+1 */
	int a[]={2,8,7,1,3,5,6,4}; 
	
	int array_size=sizeof(a)/sizeof(a[0]);
	int i=0;

	quicksort(a,0,array_size-1);
	printf("The reslut of quicksort of an array:\r\n");
	for(i=0;i<array_size;++i)
	{
		printf("%d,",a[i]);
	}
	printf("\b \r\n");

	return 0;

}

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

int quicksort(int a[],int p,int r)
{
	int q=0;

	/*Must indicate the recursion stop condition!!*/
	if(p<r)	/*When q<r, the sort is needed*/
	{
		partition(a,p,&q,r);
		quicksort(a,p,q-1);
		quicksort(a,q+1,r);
	}
	
	return 0;
}

