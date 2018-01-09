#include <stdio.h>

int main(void)
{

	/*Get the maximum subarray of the array*/
	int array[]={13,-3,-25,20,-3,-16,-23,18,20,-7,12,-5,-22,15,-4,7}; 
	
	int array_size = sizeof(array)/sizeof(array[0]);
	if(array_size>50)
	{
		return -1;
	}
	int i=0;
	
	int maxsub=array[0];		/*The sum of the maximum subarray of array[i]*/
	int maxtail=array[0];		/*The sum of the maximum subarray of array[i] which includes the element i*/
	
	int current_start=0;		/*The start of the current subarray being checked*/
	int current_end=0;		/*The end of the current subarray being checked*/
	int max_start=0;		/*The start index of the maximum subarray*/
	int max_end=0;			/*The end index of the maximum subarray*/
	
	/*Using dynamic programming to solve this problem in time O(n), space O(1)*/
	/*The optimal substructure is as following:*/
	for(i=1;i<array_size;++i)
	{
		maxtail=maxtail+array[i];
		if(array[i]>maxtail)		/*maxtail[i]=max{maxtail[i-1]+array[i],array[i]}*/
		{
			maxtail=array[i];
			current_start=i;	/*The subarray restarts from array[i],find a new start, and the end equels to the start*/
			current_end=i;
		}
		else
		{
			current_end=i;		/*The subarray includes array[i] as its end*/
		}
		
		/*maxsub=max{maxtail[i],maxsub[i-1]}*/
		if(maxtail>maxsub)
		{
			maxsub=maxtail;
			max_start=current_start;
			max_end=current_end;
		}
	}
	
	printf("%d,%d,%d\r\n",maxsub,max_start,max_end);
	
}
