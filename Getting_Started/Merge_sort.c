#include <stdio.h>

int merge_sort(unsigned int a[],int low,int high);
int merge(unsigned int a[],int low,int mid,int high);

int main(void)
{
	unsigned int a[]={5,2,4,7,1,3,2,6};	/*The sentinel element is positive infinity, equals -1 for unsigned int*/
	
	int n=sizeof(a)/sizeof(a[0]);
	int i=0;

	if(n>50)
	{
		return -1;
	}
	
	merge_sort(a,0,n-1);

	printf("The reslut of merge sort of an array:\r\n");
	for(i=0;i<n-1;++i){
		printf("%d,",a[i]);
	}
	printf("%d\r\n",a[i]);

}

/*Merge sort an array a[low...high]*/
int merge_sort(unsigned int a[],int low,int high)
{
	int mid=(low+high)/2;	/*Array size: a[low,mid] is ceiling(n/2), and a[mid+1,high] is floor(n/2)*/
	
	if(low<high)	/*Execute the sort process only when there are at least two elements in the array*/
	{
		merge_sort(a,low,mid);		/*Merge sort a[low,mid]*/
		merge_sort(a,mid+1,high);		/*Merge sort a[mid+1,high]*/
		merge(a,low,mid,high);		/*Merge two sorted arrays a[low,mid] and a[mid+1,high]*/
	}

	return 0;
}

/*Merge two sorted parts a[low,mid] and a[mid+1,high] into one bigger sorted array[low,high]*/
int merge(unsigned int a[],int low,int mid,int high)
{
	unsigned int left[50]={0};	/*left[50]={1} will not set all element of left[] to 1!!!!!!*/
	unsigned int right[50]={0};

	int i=0;
	int left_index=0;
	int right_index=0;

	/*Copy a[low,mid] into left array*/
	for(i=low,left_index=0;i<=mid;++i)
	{
		left[left_index++]=a[i];
	}

	/*Copy a[mid+1,high] into right array*/
	for(i=mid+1,right_index=0;i<=high;++i)
	{
		right[right_index++]=a[i];
	}

	/*Set the sentinel element for left and right array*/
	left[left_index]=-1;
	right[right_index]=-1;

	/*Merge left array and right array back into the oringal array*/
	for(i=low,left_index=0,right_index=0;i<=high;++i)
	{
		/*Choose the smallest element of left and right array to copy*/
		if(left[left_index]<right[right_index])
		{
			a[i]=left[left_index++];
		}
		else
		{
			a[i]=right[right_index++];
		}
	}
	
	return 0;
}
