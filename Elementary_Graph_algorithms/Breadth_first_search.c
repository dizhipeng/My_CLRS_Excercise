#include <stdio.h>
#include <malloc.h>

#define V_NUM	10
#define WHITE 	0
#define GREY  	1
#define BLACK  	2

/*Operations and parameters for queue*/
#define QueueSize 10
int enqueue(int a[],int x);
int dequeue(int a[],int *x);
int head=0;	/*head points to the position of the first element in the queue*/
int tail=0;	/*tail points to one position after the last element in the queue*/

/*Structure of BST's node*/
typedef struct adjacency_list
{
	/*Basic Fields*/
	int vertex;		/*Adjacent vertex*/
	int weight;		/*w(u,v), irrelevant for unweighted path*/
	struct adjacency_list *next; 	/*pointer for linked list*/

	/*Fields used for BFS*/
	int color;		/*White is not visited; Grey is the queue; Black is out of the queue after visiting*/
	int distance;		/*Distance from the source s*/
	int pre;		/*predecessor of the current vertex*/
} ADJACENCY_LIST;

/*Breadth-first search, source ranges from 'r' to 'y'*/
int BFS(ADJACENCY_LIST *Adj[],int Adj_size,char source);
int colorVertex(ADJACENCY_LIST *Adj[],int Adj_size,char source,int color);

int main(void)
{
	ADJACENCY_LIST *Adj[V_NUM]={0};	/*Space cost O(V+E), good for sparse graph*/
	ADJACENCY_LIST *new_vertex=0;	
	ADJACENCY_LIST *list_tail=0;

	int i=0;
	int vertex_index=0;

	/*The adjacent vertices for every vertex, seperated by |*/
	char connections[]="vs|rw|xwu|txy|r|stx|wtuy|xu";
	int connect_num=sizeof(connections)/sizeof(connections[0]);
	

	/*Construct the graph, node 0~7 corresponds to node r~y*/
	for(i=0,vertex_index=0;i<connect_num-1;++i)
	{
		/*Seperator, process the next vertex*/
		if(connections[i]=='|')
		{
			if((++vertex_index)>=V_NUM)
			{
				return -1;
			}
			continue;
		}

		/*New item in the adj list*/
		new_vertex=(ADJACENCY_LIST *)malloc(sizeof(ADJACENCY_LIST));
		new_vertex->vertex=connections[i]-'r';
		new_vertex->color=WHITE;
		new_vertex->distance=-1;
		new_vertex->pre=-1;
		new_vertex->next=0;

		/*If first node in the adj list, put it directly as the head*/
		if(Adj[vertex_index]==0)
		{
			Adj[vertex_index]=new_vertex;
		}
		else	/*If not, attach it to the next pointer*/
		{
			list_tail->next=new_vertex;
		}

		/*list_tail points to the tail of the Adj[i] link list for next insert*/
		list_tail=new_vertex;
	}
	/*Check the adj list*/
	printf("Graph G=(V,E)\r\n");
	printf("Vertices V={r,s,t,u,v,w,x,y}\r\n");
	printf("Edges E={");
	for(i=0,vertex_index=0;i<V_NUM;++i)
	{
		new_vertex=Adj[i];
		while(new_vertex!=0)
		{
			printf("(%c,%c),",i+'r',new_vertex->vertex+'r');
			new_vertex=new_vertex->next;
		}
	}
	printf("\b}\r\n");

	BFS(Adj,V_NUM,'s');
}


int BFS(ADJACENCY_LIST *Adj[],int Adj_size,char source)
{
	if(source<'r'||source>'y')
	{
		return -1;
	}

	int i=0;

	printf("Do the Breadth-first search to G, starts from vertex %c\r\n",source);
	ADJACENCY_LIST *current_node=0;	/*Starting from source*/
	
	int queue[QueueSize]={0};
	int node_name=source-'r';
	enqueue(queue,node_name);

	while(dequeue(queue,&node_name)!=-1)
	{

		printf("Accessing vertex %c, predecessor is %c, distance to source %c is %d\r\n",node_name+'r','-',source,0);
		colorVertex(Adj,V_NUM,'r'+node_name,BLACK);

		current_node=Adj[node_name];
		while(current_node!=0)
		{
			if(current_node->color==WHITE)
			{
				enqueue(queue,current_node->vertex);
			}
			current_node=current_node->next;
		}

		if(++i>60)break;
	}

}

/*Color all edges in the Adj[] with vertex=source to color*/
int colorVertex(ADJACENCY_LIST *Adj[],int Adj_size,char source,int color)
{
	ADJACENCY_LIST *new_vertex=0;
	int i;

	for(i=0;i<V_NUM;++i)
	{
		new_vertex=Adj[i];
		while(new_vertex!=0)
		{
			if((new_vertex->vertex)==(source-'r'))
			{
				new_vertex->color=color;
			}
			new_vertex=new_vertex->next;
		}
	}
}

/*Queue realized in another excercise*/
int enqueue(int a[],int x)
{
	if(((tail+1)%QueueSize)==head)	/*The queue is full*/
	{
		printf("Queue overflow\r\n");
		return -1;
	}
	else
	{
		printf("%d in queue\r\n",x);
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
		printf("%d out queue\r\n",(*x));
		head%=QueueSize;	/*Wrap around when head reach the last position*/
		return 0;
	}
}

