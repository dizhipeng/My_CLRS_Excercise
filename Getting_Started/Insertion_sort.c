#include <stdio.h>

int main(void)
{

	int a[]={5,2,4,6,1,3}; 
	int array_size = sizeof(a)/sizeof(a[0]) ;

	int i=0;
	int j=0;
	int a_i=0;
	
	for(i=1;i<array_size;++i)
	{
		a_i=a[i];	/*Current element*/
		for(j=i-1;j>=0 && a_i<a[j];--j)		/*Loop invariant [1,..,i-1], in sorted order*/
		{
			a[j+1]=a[j];		/*Move bigger element backward to make room for current element*/
		}
		a[j+1]=a_i;			/*Insert current element to the right position*/
	}

	printf("The reslut of insertion sort of an array:\r\n");
	for(i=0;i<array_size-1;++i)
	{
		printf("%d,",a[i]);
	}
	printf("%d\r\n",a[i]);
	return 0;
}
