#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define V_NUM	6
#define WHITE 	0
#define GREY  	1
#define BLACK  	2

/*Structure of Adjancency list for edges*/
typedef struct adjacency_list
{
	/*Basic Fields*/
	int vertex;		/*Adjacent vertex*/
	int weight;		/*w(u,v), irrelevant for unweighted path*/
	struct adjacency_list *next; 	/*pointer for linked list*/

} ADJACENCY_LIST,TOPOSORT;

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
int topo_sort(VERTICES_ARRAY vertices[],int size,TOPOSORT sorted[]);
int DFS_vertex(VERTICES_ARRAY vertices[],int index,TOPOSORT sorted[],int *position);

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

	printf("Do the topological sort for G:\r\n");
	TOPOSORT sorted[V_NUM];		/*Result for topoligcal sort for direceted acyclic graph G*/
	topo_sort(vertices,V_NUM,sorted);

	for(i=0;i<V_NUM;i++)
	{
		printf("%d,",sorted[i].vertex);
	}
}

int topo_sort(VERTICES_ARRAY vertices[],int size,TOPOSORT sorted[])
{

	int i=0,position=size-1;
	
	for(i=0;i<size;i++)
	{
		if(vertices[i].color==WHITE)
		{
			DFS_vertex(vertices,i,sorted,&position);
		}
		
	}
	return 0;
}


int DFS_vertex(VERTICES_ARRAY vertices[],int index,TOPOSORT sorted[],int *position)
{
	printf("Accessing vertex %c\r\n",index+'u');
	vertices[index].color=BLACK;
	
	ADJACENCY_LIST *adj_vertex=vertices[index].Adj;
	/*DFS all WHITE vertices in the adjancency list of current vertex*/
	while(adj_vertex!=0)
	{
		if(vertices[adj_vertex->vertex].color==WHITE)
		{
			//DFS_vertex(vertices,adj_vertex->vertex);
		}
		adj_vertex=adj_vertex->next;
	}

	sorted[*position].vertex=index;
	--(*position);
	printf("%d\r\n",index);
	
	return 0;
}

