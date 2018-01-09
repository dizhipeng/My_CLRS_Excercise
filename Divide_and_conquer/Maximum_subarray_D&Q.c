#include <stdio.h>

int find_maximum_subarray(int array[],int low,int high,int* max_left,int* max_right,int* max_value);
int find_maximum_subarray_cross_mid(int array[],int low,int high,int* max_left,int* max_right,int* max_value);

/*This problem is introduced from the maximum profit of stock exchange promble*/
int main(void)
{

	/*Get the maximum subarray of the array*/
	int array[]={13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7}; 
	
	int array_size = sizeof(array)/sizeof(array[0]) ;
	int i=0;
	int max_left=0;
	int max_right=0;
	int max_value=0;
	
	find_maximum_subarray(array,0,array_size-1,&max_left,&max_right,&max_value);
	
	printf("The maximum subarray is [%d,..,%d], and its value is %d.\r\n",max_left,max_right,max_value);
	
	return 0;
	
}

/*Recursive function to solve the problem.*/
/*Three situations(pay attention to the equal sign, guarantee they are complement):*/
/*The left and right part can be defined first:*/
/*low<=i<=j<=mid, close right section:(low,mid)*/
/*mid<i<=j<=high, left open section: (mid+1,high)*/
/*Then comes the middle part:*/
/*low<=i<=mid<j<=high, internally implemented in the sub-function,i from mid and j from mid+1*/

int find_maximum_subarray(int array[],int low,int high,int* max_left,int* max_right,int* max_value)
{
	/*Three situations:*/
	int left_part_left_max =0;
	int left_part_right_max =0;
	int left_part_max_value=0;
	
	int right_part_left_max =0;
	int right_part_right_max =0;
	int right_part_max_value=0;
	
	int mid_part_left_max =0;
	int mid_part_right_max =0;
	int mid_part_max_value=0;
	
	int mid=0;
	
	/*When theren is only one element left in the array, return the result directly*/
	if(low==high)
	{
		(*max_left)=low;
		(*max_right)=high;
		(*max_value)=array[low];
		
		return 0;
	}
	
	mid=(low+high)/2;
	
	/*Or, find the maximum subarray in each one of the tree situations*/

	/*Find in the middle part of the array*/
	find_maximum_subarray_cross_mid(array,low,high,&mid_part_left_max,&mid_part_right_max,&mid_part_max_value);
	/*Find in the left part of the array, recursive call*/
	find_maximum_subarray(array,low,mid,&left_part_left_max,&left_part_right_max,&left_part_max_value);
	/*Find in the right part of the array, recursive call*/
	find_maximum_subarray(array,mid+1,high,&right_part_left_max,&right_part_right_max,&right_part_max_value);
	
	/*Choose the maximum case from the three*/
	if((mid_part_max_value>=left_part_max_value)&&(mid_part_max_value>=right_part_max_value))
	{
		(*max_left)=mid_part_left_max;
		(*max_right)=mid_part_right_max;
		(*max_value)=mid_part_max_value;
	}
	else if((left_part_max_value>=mid_part_max_value)&&(left_part_max_value>=right_part_max_value))
	{
		(*max_left)=left_part_left_max;
		(*max_right)=left_part_right_max;
		(*max_value)=left_part_max_value;
	}
	else
	{
		(*max_left)=right_part_left_max;
		(*max_right)=right_part_right_max;
		(*max_value)=right_part_max_value;

	}
}

/*Find the maximum subarray cross the middle of the array*/
/*Two parts:  { maximum subarray in array[low, mid] } , find in time theta(n/2)*/
/*concatenate with */
/* { maximum subarray in array[mid+1, high] }, find in time theta(n/2)*/
int find_maximum_subarray_cross_mid(int array[],int low,int high,int* max_left,int* max_right,int* max_value)
{
	int mid=(low+high)/2;
	/*Boundary condition: low==high, there is only one element left*/
	/*This must be ruled out outside this function*/
	if(low==high)
	{
		/*Return directly, preventing index access overflow array[mid+1]*/
		return -1;	
	}
	
	int max_left_index=mid;
	int max_right_index=mid+1;
	int max_left_value=0;
	int max_right_value=0;
	int sum=0;
	int i=0;
	
	/*Find maximum subarray in array[low, mid]*/
	/*Init value is array[mid]*/
	max_left_value=array[mid];
	sum=array[mid];
	max_left_index=mid;
	/*sum is the current subarray's value*/
	/*when found the maximum sum of subarray, record its value and index*/
	for(i=mid-1;i>=low;--i)
	{
		sum+=array[i];
		if(sum>max_left_value)
		{
			max_left_value=sum;
			max_left_index=i;
		}
	}
	
	/*The same way to find maximum subarray in array[mid+1, high]*/
	max_right_value=array[mid+1];
	sum=array[mid+1];
	max_right_index=mid+1;
	for(i=mid+2;i<=high;++i)
	{
		sum+=array[i];
		if(sum>max_right_value)
		{
			max_right_value=sum;
			max_right_index=i;
		}
	}
	
	/*Return the results by pointer parameter*/
	(*max_left)=max_left_index;
	(*max_right)=max_right_index;
	(*max_value)=max_left_value+max_right_value;
	
}
