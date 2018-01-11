#include <stdio.h>

int build_heap(int a[],int array_size);
int max_heapify(int a[],int i,int heap_size);

int main(void)
{
	/*Index starts from 1 to  make the calculation of a node's left & right child in accordance to the form of a heap*/
	/*i.e. left_i=i*2 and right_i=i*2+1 */
	int a[]={-1,4,1,3,2,16,9,10,14,8,7}; 
	
	int array_size = sizeof(a)/sizeof(a[0]) - 1 ;
	int max=0;
	int i=0;
	
	/*Build a max-heap from a[1] to a[array_size]*/
	build_heap(a,array_size);
	
	/*Pick the root of the max heap, and exchange it with the last element of the heap*/
	/*Then heapify with the new root, changing the array to a new max heap of size [1..heap_size-1]*/
	/*Repeat until a[1] has nothing to exchange*/
	for(i=array_size;i>=2;--i)
	{
		/*Exchange*/
		max=a[1];
		a[1]=a[i];
		a[i]=max;
		
		/*Heapify, now a[i] is not in the heap anymore*/
		max_heapify(a,1,i-1);
	}

	/*Print outputs, starting from a[1]*/
	printf("The reslut of heap sort of an array:\r\n");
	for(i=1;i<array_size;++i)
	{
		printf("%d,",a[i]);
	}
	printf("%d\r\n",a[i]);
}

/*Heapify an array to a max heap. Its root is a[i] and the index of its last node o is a[heap_size]*/
/*This condition must be satisfied: The left child and right child of the original tree are already max heaps*/
int max_heapify(int a[],int i,int heap_size)
{
	int left_i=0;
	int right_i=0;
	int max_index=0;
	int temp=0;
	
	while(i<=heap_size/2)		/*While a[i] is not a leaf (Indicating a[i] has at least a left child)*/
	{
		left_i=i*2;					/*Get index for i's left child*/
		right_i=i*2+1;			/*Get index for i's right child, but may not exist*/
		
		max_index=i;			/*Get the biggest element of a[i],a[left_i] and a[right_i]*/
		if(a[left_i]>a[i])
		{
			max_index=left_i;
		}
		
		if(right_i<=heap_size && a[right_i]>a[max_index])	/*Guarantee right_i exists*/
		{
			max_index=right_i;
		}
		
		if(max_index!=i)	/*Exchange a[i] and a[max_index]*/
		{
			temp=a[i];
			a[i]=a[max_index];
			a[max_index]=temp;
			
			/*Use this to check each exchange:*/ /*printf("[%d,%d],",a[max_index],a[i]);*/
			i=max_index;	/*Heapify the tree at new root a[max_index]*/
		}
		else	/*a[i] has already moved to the correct position*/
		{
			return 0;
		}

	}
	
	/*If a[i] is a leaf, then the adjustment is over, a[i] itself is a trival max heap*/
	return 0;

}

/*Build a max-heap based on array a[1..array_size]*/
/*The building order is from the first internal node a[array_size/2] to the root a[1]*/
int build_heap(int a[],int array_size)
{
	int i=0;
	for(i=(array_size/2);i>=1;--i)
	{
		max_heapify(a,i,array_size);
	}

}
