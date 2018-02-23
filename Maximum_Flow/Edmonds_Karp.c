#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define V_NUM	6
#define WHITE 	0
#define GREY  	1
#define BLACK  	2
#define FLOW    0
#define CF      1

/*Operations and parameters for queue*/
#define QueueSize 10
int enqueue(int a[],int x);
int dequeue(int a[],int *x);
int head=0;	/*head points to the position of the first element in the queue*/
int tail=0;	/*tail points to one position after the last element in the queue*/

/*Structure of Adjancency list for edges*/
typedef struct adjacency_list
{
	/*Basic Fields*/
	int vertex;		/*Adjacent vertex*/
	int capacity;		/*Maximum capacity for edge (u,v), 0 if (u,v) not exits but (v,u) exists*/
	int flow;		/*Curret flow of edge (u,v), namely (u,v).f*/
	int cf;			/*Residual flow for every residual edge in Gf*/
	struct adjacency_list *next; 	/*pointer for linked list*/

} ADJACENCY_LIST;

/*Structure of Vertices*/
typedef struct vertices_array
{
	/*Fields used for BFS*/
	int color;		/*White is not visited; Grey is the queue; Black is out of the queue after visiting*/
	int distance;		/*Distance from the source s*/
	int pre;		/*predecessor of the current vertex*/

	/*Adjancency list*/
	struct adjacency_list *Adj;

} VERTICES_ARRAY;

/*Breadth-first search, source ranges from 'r' to 'y'*/
int BFS(VERTICES_ARRAY vertices[],char source);

int main(void)
{
	VERTICES_ARRAY vertices[V_NUM];		/*Space cost O(V+E), good for sparse graph*/
	memset(vertices,0,sizeof(vertices));

	ADJACENCY_LIST *new_vertex=0;	
	ADJACENCY_LIST *list_tail=0;

	int i=0;
	int vertex_index=0;

	/*The adjacent vertices for every vertex, seperated by |*/
	char connections[]="uw|vx|swv|uwxt|suvx|wvt";	/*stuvwx*/
	int weights[]={16,13,-1,0,0,-1,0,0,12,-1,0,9,0,20,-1,0,4,0,14,-1,0,7,4};
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
		new_vertex->vertex=connections[i]-'s';
		new_vertex->capacity=weights[i];
		new_vertex->flow=0;	
		new_vertex->cf=new_vertex->capacity;	/*cf(u,v)=c(u,v)-f(u,v)  if (u,v) exists; Initially,  f(u,v)=0, so cf(u,v)=c(u,v)*/
							/*cf(u,v)=f(v,u)  if (v,u) exists; Initially, f(v,u)=0, so cf(u,v)=0=c(u,v) when (u,v) doesn't exist but (v,u) exists*/
		new_vertex->next=0;

		/*If first node in the adj list, put it directly as the head*/
		if(vertices[vertex_index].Adj==0)
		{
			vertices[vertex_index].Adj=new_vertex;
			vertices[vertex_index].color=WHITE;		/*Color the node to white by the way*/
			vertices[vertex_index].distance=0;		/*For BFS the distanec to the sourec must be 0*/
			vertices[vertex_index].pre=-1;	/*For BFS the distanec to the sourec must be 0*/
		}
		else	/*If not, attach it to the next pointer*/
		{
			list_tail->next=new_vertex;
		}

		/*list_tail points to the tail of the Adj link list for next insert*/
		list_tail=new_vertex;
	}
	/*Check the adj list*/
	printf("Graph G=(V,E)\r\n");
	printf("Vertices V={s,t,u,v,w,x}\r\n");
	printf("Edges E={");
	for(i=0,vertex_index=0;i<V_NUM;++i)
	{
		new_vertex=vertices[i].Adj;
		while(new_vertex!=0)
		{
			printf("(%c,%c),",i+'s',new_vertex->vertex+'s');
			new_vertex=new_vertex->next;
		}
	}
	printf("\b}\r\n\r\n");

	/*Begin BFS from vertex s*/
	BFS(vertices,'s');

}

int BFS(VERTICES_ARRAY vertices[],char source)
{
	if(source<'s'||source>'x')
	{
		return -1;
	}

	int i=0;

	printf("Do the Breadth-first search to G, starts from vertex %c:\r\n",source);
	ADJACENCY_LIST *current_node=0;	/*Starting from source*/
	
	int queue[QueueSize]={0};
	int node_index=source-'s';
	enqueue(queue,node_index);

	/*Dequeue a node. If the queue is empty, BFS is over*/
	while(dequeue(queue,&node_index)!=-1)
	{

		/*Access the dequeued vertex, color it black. It's the current vertex*/
		printf("Accessing vertex %c, predecessor is %c, distance to source %c is %d\r\n",node_index+'s',vertices[node_index].pre+'s',source,vertices[node_index].distance);
		vertices[node_index].color=BLACK;

		/*Equeue every white vertices in the ajdacency list of the current vertex, color them to grey, compute their distances to the source, record its predecessor*/
		current_node=vertices[node_index].Adj;
		while(current_node!=0)
		{
			if( vertices[current_node->vertex].color==WHITE && current_node->cf!=0 /*When cf(u,v)==0, there is actually no edge from u to v in Gf*/ )
			{
				enqueue(queue,current_node->vertex);
				vertices[current_node->vertex].color=GREY;
				vertices[current_node->vertex].pre=node_index;
				vertices[current_node->vertex].distance=vertices[node_index].distance+1;
			}
			current_node=current_node->next;
		}

	}

}

int get_flow(VERTICES_ARRAY vertices[],int u,int v,int flow/*flow==FLOW to get f(u,v), flow==CF to get cf(u,v)*/)
{
	ADJACENCY_LIST *edge=vertices[u].Adj;

	while(edge!=0)
	{
		if(edge->vertex==v)	/*edge(u,v) is found*/
		{
			if( flow==FLOW && edge->capacity!=0 /*The edge must exit to make the flow valid*/)
			{
				return edge->flow;
			}
			else
			{
				return edge->cf;
			}

		}
	}

	if(flow==FLOW)
	{
		printf("Flow (%c,%c) is invalid\r\n",u+'s',v+'s');
	}
	else
	{
		printf("Residual flow (%c,%c) is invalid\r\n",u+'s',v+'s');
	}

	return -1;
}

#if 0
int get_cp(VERTICES_ARRAY vertices[])	/*cp is the cf of the critical edge in the found augument path for s to t*/
{
	ADJACENCY_LIST *edge=vertices[u].Adj;

	
	int vs=1;
	while(pr!=-1)
	{
		//printf("%c<-",pr+'s');
		pr=vertices[pr].pre;
	}

	while(edge!=0)
	{
		if(edge->vertex==v)
		{
			return edge->flow;
		}
	}

	return -1;
}
#endif

/*Queue realized in another excercise*/
int enqueue(int a[],int x)
{
	if(((tail+1)%QueueSize)==head)	/*The queue is full*/
	{
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
		return -1;
	}
	else
	{
		(*x)=a[head++];
		head%=QueueSize;	/*Wrap around when head reach the last position*/
		return 0;
	}
}
