#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define V_NUM	5
#define POS_INFINI (0xffff)
#define NEG_INFINI (-0xffff)
#define NIL	   (-1)

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
	//int color;		/*White is not visited; Grey is the queue; Black is out of the queue after visiting*/
	int distance;		/*estimated shortest distance from the source s*/
	int pre;		/*predecessor of the current vertex in the shortest path*/

	/*Adjancency list*/
	struct adjacency_list *Adj;

} VERTICES_ARRAY;

int relaxation(VERTICES_ARRAY vertex[],int u,int v,int w);

int main(void)
{
	VERTICES_ARRAY vertices[V_NUM];		/*Space cost O(V+E), good for sparse graph*/
	memset(vertices,0,sizeof(vertices));

	ADJACENCY_LIST *new_edge=0;	
	ADJACENCY_LIST *list_tail=0;
	

	int i=0,j=0;
	int vertex_index=0;
	int source=0;
	int predecessor=NIL;

	/*The adjacent vertices for every vertex, seperated by |*/
	char connections[]="bd|cde|b|ce|ac|";
	int weights[]={6,7,POS_INFINI,5,8,-4,POS_INFINI,-2,POS_INFINI,-3,9,POS_INFINI,2,7,POS_INFINI};
	int connect_num=sizeof(connections)/sizeof(connections[0]);
	

	/*Construct the graph, node 0~5 corresponds to node a~e*/
	for(i=0,vertex_index=0;i<connect_num-1;++i)
	{
		/*Seperator, process the next vertex*/
		if(connections[i]=='|')
		{
			if(((++vertex_index)>=V_NUM)||(weights[i]!=POS_INFINI))
			{
				//printf("Parameter error!\r\n");
				//return -1;
				break;
			}
			continue;
		}

		/*New item in the adj list*/
		new_edge=(ADJACENCY_LIST *)malloc(sizeof(ADJACENCY_LIST));
		new_edge->vertex=connections[i]-'a';
		new_edge->weight=weights[i];
		new_edge->next=0;

		/*If first node in the adj list, put it directly as the head*/
		if(vertices[vertex_index].Adj==0)
		{
			vertices[vertex_index].Adj=new_edge;
			vertices[vertex_index].distance=POS_INFINI;/*The distance is initialize to positive infinity for the algorithm*/
			vertices[vertex_index].pre=NIL;		   /*The predecessor is not known*/
		}
		else	/*If not, attach it to the next pointer*/
		{
			list_tail->next=new_edge;
		}

		/*list_tail points to the tail of the Adj link list for next insert*/
		list_tail=new_edge;
	}
	#if 1
	/*Check the adj list*/
	printf("Graph G=(V,E)\r\n");
	printf("Vertices V={r,s,t,u,v,w,x,y}\r\n");
	printf("Edges weights:\r\n");
	for(i=0,vertex_index=0;i<V_NUM;++i)
	{
		new_edge=vertices[i].Adj;
		while(new_edge!=0)
		{
			printf("w(%c,%c)=%d,",i+'a',new_edge->vertex+'a',new_edge->weight);
			new_edge=new_edge->next;
		}
	}
	printf("\b \r\n\r\n");
	#endif

	/*The estimated distance of source vertex must be initialized to 0*/
	source=0;
	vertices[source].distance=0;

	/*Bellman-Ford algorithm*/
	printf("Calling Bellman-Ford algorithm to find the shortest path for source %c:\r\n",source+'a');
	for(i=1;i<V_NUM-1;++i)
	{
		/*Do the relaxation for every edge of the graph*/
		for(j=0;j<V_NUM;++j)
		{
			new_edge=vertices[j].Adj;
			while(new_edge)
			{
				relaxation(vertices,j,new_edge->vertex,new_edge->weight);
				new_edge=new_edge->next;
			}
		}
	}

	/*If after |V-1| times iteration, there are distances which can still be shorten*/
	/*Then there must be some negative cycle along the path start from the source*/
	/*So the algorithm fails*/
	for(j=0;j<V_NUM;++j)
	{
		new_edge=vertices[j].Adj;
		while(new_edge)
		{
			if(vertices[new_edge->vertex].distance>vertices[j].distance+new_edge->weight)
			{
				printf("Negative cycles exist, can't find shortest path from %c\r\n",source+'a');
				return -1;
			}
			new_edge=new_edge->next;
		}
	}

	for(i=0;i<V_NUM;++i)
	{
		if(i!=source)
		{
			printf("Shortest path from %c to %c: %c",source+'a',i+'a',i+'a');
			predecessor=vertices[i].pre;
			while(predecessor!=NIL)
			{	
				printf("<-%c",predecessor+'a');
				predecessor=vertices[predecessor].pre;
			}
			printf(", weight=%d\r\n",vertices[i].distance);
		}
	}
	/*Using Prim algorithm to get the minimum spanning tree*/
}


int relaxation(VERTICES_ARRAY vertex[],int u,int v,int w)
{
	if(vertex[v].distance > vertex[u].distance + w)
	{							/*The relaxation process is the only one*/ 
		vertex[v].distance=vertex[u].distance+w;	/*that would change the estimated shorted distance of v*/
		vertex[v].pre=u;				/*And the predecessor of v*/
	}

	return 0;
}

int Bellman_Ford(VERTICES_ARRAY vertex[],int size)
{

}

/*Init the vertice's estimated distance and predecessor for the shortes path algorithm*/
#if 0
int init_vertices(VERTICES_ARRAY vertex[],int size,int source)
{
	int i=0;

	for(i=0;i<size;++i)
	{
		vertex[i].distance=POS_INFINI;
		vertex[i].pre=NIL;
	}

	vertex[source].distance=0;
}
#endif

