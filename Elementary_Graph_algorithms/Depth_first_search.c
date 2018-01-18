#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define V_NUM	6
#define WHITE 	0
#define GREY  	1
#define BLACK  	2

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
	int weight;		/*w(u,v), irrelevant for unweighted path*/
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

/*Depth-first search*/
int DFS(VERTICES_ARRAY vertices[],int size);
int DFS_vertex(VERTICES_ARRAY vertices[],int index);

int main(void)
{
	VERTICES_ARRAY vertices[V_NUM];		/*Space cost O(V+E), good for sparse graph*/
	memset(vertices,0,sizeof(vertices));

	ADJACENCY_LIST *new_vertex=0;	
	ADJACENCY_LIST *list_tail=0;

	int i=0;
	int vertex_index=0;

	/*The adjacent vertices for every vertex, seperated by |*/
	char connections[]="vx|y|yz|v|x|z";
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
		new_vertex->vertex=connections[i]-'u';
		new_vertex->next=0;

		/*If first node in the adj list, put it directly as the head*/
		if(vertices[vertex_index].Adj==0)
		{
			vertices[vertex_index].Adj=new_vertex;
			vertices[vertex_index].color=WHITE;	/*Color the node to white by the way*/
			vertices[vertex_index].distance=0;	/*For BFS the distanec to the sourec must be 0*/
			vertices[vertex_index].pre=vertex_index;	/*For BFS the distanec to the sourec must be 0*/
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
	printf("Vertices V={r,s,t,u,v,w,x,y}\r\n");
	printf("Edges E={");
	for(i=0,vertex_index=0;i<V_NUM;++i)
	{
		new_vertex=vertices[i].Adj;
		while(new_vertex!=0)
		{
			printf("(%c,%c),",i+'u',new_vertex->vertex+'u');
			new_vertex=new_vertex->next;
		}
	}
	printf("\b}\r\n\r\n");

	/*Begin BFS from vertex s*/
	printf("Do the Depth-first search to G, for every vertex in V:\r\n");
	DFS(vertices,V_NUM);
}

int DFS(VERTICES_ARRAY vertices[],int size)
{

	int i=0;
	for(i=0;i<size;i++)
	{
		if(vertices[i].color==WHITE)
		{
			DFS_vertex(vertices,i);
		}
		
	}
	return 0;
}


int DFS_vertex(VERTICES_ARRAY vertices[],int index)
{
	printf("Accessing vertex %c\r\n",index+'u');
	vertices[index].color=BLACK;
	
	ADJACENCY_LIST *adj_vertex=vertices[index].Adj;
	/*DFS all WHITE vertices in the adjancency list of current vertex*/
	while(adj_vertex!=0)
	{
		if(vertices[adj_vertex->vertex].color==WHITE)
		{
			DFS_vertex(vertices,adj_vertex->vertex);
		}
		adj_vertex=adj_vertex->next;
	}
}

#if 0
	if(source<'r'||source>'y')
	{
		return -1;
	}

	int i=0;

	printf("Do the Breadth-first search to G, starts from vertex %c:\r\n",source);
	ADJACENCY_LIST *current_node=0;	/*Starting from source*/
	
	int queue[QueueSize]={0};
	int node_index=source-'r';
	enqueue(queue,node_index);

	while(dequeue(queue,&node_index)!=-1)
	{

		printf("Accessing vertex %c, predecessor is %c, distance to source %c is %d\r\n",node_index+'r',vertices[node_index].pre+'r',source,vertices[node_index].distance);

		vertices[node_index].color=BLACK;
		current_node=vertices[node_index].Adj;
		while(current_node!=0)
		{
			if(vertices[current_node->vertex].color==WHITE)
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
#endif
