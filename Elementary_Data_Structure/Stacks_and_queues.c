#include <stdio.h>

/*Operations and parameters for stack*/
#define StackSize 10
int push(int a[],int x);
int pop(int a[],int *x);
int top=-1;	/*top points to the position of the top element in the stack*/

/*Operations and parameters for queue*/
#define QueueSize 10
int enqueue(int a[],int x);
int dequeue(int a[],int *x);
int head=1;	/*head points to the position of the first element in the queue*/
int tail=1;	/*tail points to one position after the last element in the queue*/
/*To prevent the wrap around operation from interfering the full-checking process*/
/*head and tail starts from the second position of the queue*/

int main(void)
{	
	int a[]={15,6,9,8,4,17,3,5}; 
	int array_size = sizeof(a)/sizeof(a[0]);
	int stack[StackSize]={0};
	int queue[QueueSize]={0};
	int i=0;
	int temp=0;

	printf("Original sequence:\r\n");
	for(i=0;i<array_size;++i)
	{
		printf("%d,",a[i]);	
	}
	printf("\b \r\n");

	/*Stack operations*/
	printf("Afetr push and pop operations of a stack:\r\n");
	for(i=0;i<array_size;++i)
	{
		if(push(stack,a[i])!=0)
		{
			return -1;
		}	
	}
	for(i=0;i<array_size;++i)
	{
		if(pop(stack,&temp)!=0)
		{
			return -1;
		}	
		printf("%d,",temp);	
	}
	printf("\b \r\n");

	/*Queue operations*/
	printf("Afetr enqueue and dequeue operations of a queue:\r\n");
	for(i=0;i<array_size;++i)
	{
		if(enqueue(queue,a[i]))
		{
			return -1;
		}	
	}
	for(i=0;i<array_size;++i)
	{
		if(dequeue(queue,&temp))
		{
			return -1;
		}	
		printf("%d,",temp);	
	}
	printf("\b \r\n");

	return 0;	
}

int push(int a[],int x)
{
	if(top<StackSize-1){	
		a[++top]=x;
		return 0;
	}
	else	/*Handle overflow while pushing, when top points to the last element of the stack*/
	{
		printf("Stack overflow\r\n");
		return -1;
	}	
}

int pop(int a[],int *x)
{
	if(top>=0){
		(*x)=a[top--];
		return 0;
	}
	else	/*Handle underflow while poppnig, when top is -1*/
	{
		printf("Stack underflow\r\n");
		return -1;
	}	
}

int enqueue(int a[],int x)
{
	if((tail+1)==head)	/*The queue is full*/
	{
		printf("Queue overflow\r\n");
		return -1;
	}
	else
	{
		a[tail++]=x;
		tail%=QueueSize;	/*Wrap around when tail reach the last position*/
		return 0;
	}
}

int dequeue(int a[],int* x)
{
	if(tail==head)	/*The queue is empty*/
	{
		printf("Queue underflow\r\n");
		return -1;
	}
	else
	{
		(*x)=a[head++];
		head%=QueueSize;	/*Wrap around when head reach the last position*/
		return 0;
	}
}

