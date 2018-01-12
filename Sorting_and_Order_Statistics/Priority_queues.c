#include <stdio.h>

int max_heapify(int a[],int i,int heap_size);
int insert_key(int a[],int key,int heap_size);
int increasing_key(int a[],int i,int key);
int extract_maximum(int a[],int* max,int heap_size);

int main(void)
{
	/*Index starts from 1 to  make the calculation of a node's left & right child in accordance to the form of a heap*/
	/*i.e. left_i=i*2 and right_i=i*2+1 */
	int a[]={-1,4,1,3,2,16,9,10,14,8,7}; 
	int b[50]={0};
	int i=0;
	int max=0;
	
	int array_size = sizeof(a)/sizeof(a[0]) - 1 ;
	if(array_size>=50)
	{
		return -1;
	}

	printf("Inserting keys into the queue:\r\n");
	for(i=1;i<=array_size;++i)
	{
		printf("%d,",a[i]);
		/*Build the heap by inserting keys from a to b*/
		insert_key(b,a[i],i-1);
	}
	printf("\b \r\n");

	printf("Extracting keys from the queue:\r\n");
	for(i=array_size;i>=1;--i)
	{
		extract_maximum(b,&max,i);
		printf("%d,",max);
	}
	printf("\b \r\n");


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
		
		if(right_i<=heap_size && a[right_i]>a[max_index])			/*Guarantee right_i exists*/
		{
			max_index=right_i;
		}
		
		if(max_index!=i)	/*Exchange a[i] and a[max_index]*/
		{
			temp=a[i];
			a[i]=a[max_index];
			a[max_index]=temp;
			
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

/*heap_size is the current size of the heap*/
int insert_key(int a[],int key,int heap_size)
{
	a[++heap_size]=-1;					/*New element starts with negative infinity*/
	increasing_key(a,heap_size,key);	/*Increase the value of new element to key*/
}

int increasing_key(int a[],int i,int key)
{
	int parent=0;
	int temp=0;
	
	if(key<a[i])
	{
		printf("Fail to increase.");
		return -1;
	}
	
	a[i]=key;
	while(i>1)	/*Exchange every upstream smaller parent,until i reaches the root*/
	{
		parent=i/2;
		
		if(a[parent]<a[i])
		{
			/*Exchange i to i's parent*/
			temp=a[i];
			a[i]=a[parent];
			a[parent]=temp;

			/*One level up to i*/
			i=parent;
		}
		else
		{
			/*i's parent is not smaller than i, no need to exchage any more*/
			return 0;
		}
	}

	return 0; /*i reaches the top*/
}

int extract_maximum(int a[],int* max,int heap_size)
{

	if(heap_size<1)
	{
		printf("The queue is empty!\r\n");
		return -1;
	}
	
	(*max)=a[1];
	a[1]=a[heap_size];
	
	max_heapify(a,1,--heap_size);
	return 0;
}
