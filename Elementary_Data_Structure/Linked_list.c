#include <stdio.h>

#define FreeSize 10

/*A doubly linked list with sentinel, multiple array representation*/
/*Operations for the linked list*/
int insert(int x);
int delete(int x);	/*Free the memory inside*/
int search(int k);

/*Operations for memory allocation*/
int allocateMem();
int freeMem(int x);

/*Initialization for the linked list*/
int initLinkedList();

int free_pointer=1;		/*free_pointer points to the first free element in the free list*/

int next[FreeSize]={0};		/*The linked list, L[0] is the sentinel*/
int prev[FreeSize]={0};	
int key[FreeSize]={0};

/*This is a */
int main(void)
{	
	int a[]={15,6,9,8,4,17,3,5,7,23,18,11,14}; 
	int array_size = sizeof(a)/sizeof(a[0]);
	int x_pointer=0;	/*x_poiter=0 means null pointer*/
	int i=0;

	initLinkedList();

	/*Insert*/
	printf("Insert elements to linked list:\r\n");
	for(i=0;i<array_size;++i)
	{
		if(x_pointer=allocateMem())	/*Allocate space to the pointer, returns null pointer if failed*/
		{
			key[x_pointer]=a[i];	/*x->key=a[i]*/

			printf("%d,",key[x_pointer]);
			insert(x_pointer);	/*Insert x to the linked list*/	
		}
		else
		{
			printf("\b \r\nAllocation of memory fails. ");
			break;
		}
	}
	printf("\b \r\n");

	/*Search&Delete*/
	printf("Search and delete elements:\r\n");
	for(i=array_size;i>=0;i-=2)
	{
		/*Return null pointer if key is not found in the linked list*/
		if(x_pointer=search(a[i]))
		{
			printf("Found key %d, now deleting...",a[i]);
			delete(x_pointer);
			/*Search again to check whether deleting is successful*/
			if(x_pointer=search(a[i]))
			{
				printf("Failed.\r\n");
			}
			else
			{
				printf("Succeeded.Memory freed.\r\n");
			}
		}
		else
		{
			printf("Key %d is not in the linked list\r\n",a[i]);
		}
	}

	return 0;	
}

int initLinkedList()
{
	int i=0;

	/*Empty linked list, set sentinel's next and prev points to itself*/
	next[0]=0;
	prev[0]=0;

	/*Build the free list for memory allocation*/
	free_pointer=1;
	for(i=1;i<FreeSize-1;++i)
	{
		next[i]=i+1;
	}
	next[FreeSize-1]=0;	/*Last space has no next*/
}

int insert(int x)
{
	/*L[0] is Link.nil*/
	/*Insert element x in the head of the linked list*/
	next[x]=next[0];
	prev[x]=0;

	prev[next[0]]=x;
	next[0]=x;

	return 0;
	
}

int delete(int x)
{
	prev[next[x]]=prev[x];
	next[prev[x]]=next[x];

	freeMem(x);

	return 0;
}

int search(int k)
{
	int x=next[0];

	while(x!=0&&key[x]!=k)
	{
		x=next[x];	/*Search next element*/
	}
	return x;	/*Find x.key=key or x=0*/

}

int allocateMem()
{
	int pointer=0;
	if(free_pointer==0)	/*No more free space*/
	{
		return 0;
	}
	else
	{
		/*free pointer points to the next free space, return the current free space*/
		pointer=free_pointer;
		free_pointer=next[free_pointer];
		return pointer;
	}
	
}

int freeMem(int x)
{
	/*free pointer points to space x, while x's next becomes the origin free space*/
	next[x]=free_pointer;
	free_pointer=x;
}
