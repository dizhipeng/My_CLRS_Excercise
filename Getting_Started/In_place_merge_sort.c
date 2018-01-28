#include <stdio.h>

int merge_sort(unsigned int a[],int low,int high);
int merge_in_place(unsigned int a[],int low,int mid,int high);
int switch_subarray(int a[],int head,int mid,int tail);

int main(void)
{
	unsigned int a[]={18,10,3,5,7,11,4,9,13,2,14,15};	/*The sentinel element is positive infinity, equals -1 for unsigned int*/
	
	//unsigned int a[]={1,2,5,6,9,10,15,18, 3,4,7,8,11,12,13,14,19};

	int n=sizeof(a)/sizeof(a[0]);
	int i=0;

	if(n>50)
	{
		return -1;
	}
	
	//merge_in_place(a,0,7,16);
	merge_sort(a,0,n-1);
	//switch_subarray(a,0,n/2,n-1);

	printf("The reslut of in-place merge sort of an array:\r\n");
	for(i=0;i<n;++i){
		printf("%d,",a[i]);
	}
	printf("\b \r\n");

}

/*Merge sort an array a[low...high]*/
int merge_sort(unsigned int a[],int low,int high)
{
	int mid=(low+high)/2;	/*Array size: a[low,mid] is ceiling(n/2), and a[mid+1,high] is floor(n/2)*/
	
	if(low<high)	/*Execute the sort process only when there are at least two elements in the array*/
	{
		merge_sort(a,low,mid);		/*Merge sort a[low,mid]*/
		merge_sort(a,mid+1,high);		/*Merge sort a[mid+1,high]*/
		merge_in_place(a,low,mid,high);		/*Merge two sorted arrays a[low,mid] and a[mid+1,high]*/
	}

	return 0;
}

/*Merge two sorted parts a[low,mid] and a[mid+1,high] into one bigger sorted array[low,high]*/
int merge_in_place(unsigned int a[],int low,int mid,int high)
{
	int left=low,right=mid+1,move_head=right,n=high,i;

	while(left<right&&right<=high)	/*The indices are legal*/
	{

		while(left<right&&a[left]<=a[right])	/*Elements before left is alread at the correct position*/
		{
			++left;

		}
		if(left>=right)	/*Both sides at left index are sorted, therefore the whole array is sorted, done*/
		{
			break;
		}

		move_head=right;
		while(right<=high&&a[right]<=a[left])	/*Elements between move_head and right-1 is small than elements after left*/
		{		
			++right;	/*right is at least move_head+1*/
		}
		
		
		/*Doing the swith, making elements before left are the smallest and sorted*/
		switch_subarray(a,left,move_head-1,right-1);

		left+=right-move_head;/*After switching, update left index to point to the next element of the switched a[move_head..right-1]*/
	}
	
	return 0;
}

/*Switch the position of two parts of the array: from a[head..mid,mid+1..tail] to a[mid+1..tail,head..mid]*/
/*Without additional space requirements*/
int switch_subarray(int a[],int head,int mid,int tail)
{
	int i=0,j=0,temp;

	/*Inverse elements a[head..mid]*/
	i=head;
	j=mid;
	while(i<j)
	{
		temp=a[i];
		a[i++]=a[j];
		a[j--]=temp;
	}

	/*Inverse elements a[mid+1..tail]*/
	i=mid+1;
	j=tail;
	while(i<j)
	{
		temp=a[i];
		a[i++]=a[j];
		a[j--]=temp;
	}

	/*Inverse elements a[head..tail]*/
	i=head;
	j=tail;
	while(i<j)
	{
		temp=a[i];
		a[i++]=a[j];
		a[j--]=temp;
	}
}





