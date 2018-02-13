/*Dijkstra's algorithms*/

/*
Symbols:
V is the set of all vertices.
s is the single source vertex.
S is the set of shortest paths from s to all other vertices.(i.e. the solution to the single source shortest path).
Q is a priority queue which stores the weights from vertices V-S to vertices in S.
d[v] is the estimated shortest path weigth of vertex v (in Q or S), d{w,v} is the weight from w to v.
MinKey(Q) the vertex who has the minimun estimated shortest path weight in Q.
Adj[u] is the set of vertices in u's adjacency list.These vertice can be in S or Q.

Initialization:
d[s]=0;
for any other element q in V, set d{q}=INFINITY.
S={};
Q=V;

Algorithm:
while Q!={}
	u = MinKey(Q) 
	S = S union {u}
	Q = Q - {u}

	for every v in Adj[u]:
		if d[v]>d[u]+w[u,v]		<----Relaxation step
			d[u]=d[v]+w[u,v]	<----
done
*/

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define V_NUM	5
#define WHITE 	0
#define GREY  	1
#define BLACK  	2
#define POS_INFI (0xffffff)
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
	int color;		/*White is not visited; Grey is the queue; Black is out of the queue after visiting*/
	int distance;		/*Stands for the estimated distance v.d*/
	int pre;		/*predecessor of the current vertex*/

	/*Adjancency list*/
	struct adjacency_list *Adj;

} VERTICES_ARRAY;

int Dijkstra(VERTICES_ARRAY v[]);
int relaxation(VERTICES_ARRAY vertex[],int u,int v,int w);

int main(void)
{
	VERTICES_ARRAY vertices[V_NUM];		/*Space cost O(V+E), good for sparse graph*/
	memset(vertices,0,sizeof(vertices));

	ADJACENCY_LIST *new_vertex=0;	
	ADJACENCY_LIST *list_tail=0;

	int i=0;
	int vertex_index=0;

	/*The adjacent vertices for every vertex, seperated by |*/
	char connections[]="bd|cd|e|bec|ca";
	int weights[]={10,5,-1,1,2,-1,4,-1,3,2,9,-1,6,7};
	int connect_num=sizeof(connections)/sizeof(connections[0]);
	

	/*Construct the graph, node 0~7 corresponds to node r~y*/
	for(i=0,vertex_index=0;i<connect_num-1;++i)
	{
		/*Seperator, process the next vertex*/
		if(connections[i]=='|')
		{
			if(((++vertex_index)>=V_NUM)||(weights[i]!=-1))
			{
				printf("Parameter error!\r\n");
				return -1;
			}
			continue;
		}

		/*New item in the adj list*/
		new_vertex=(ADJACENCY_LIST *)malloc(sizeof(ADJACENCY_LIST));
		new_vertex->vertex=connections[i]-'a';
		new_vertex->weight=weights[i];
		new_vertex->next=0;

		/*If first node in the adj list, put it directly as the head*/
		if(vertices[vertex_index].Adj==0)
		{
			vertices[vertex_index].Adj=new_vertex;
			vertices[vertex_index].color=WHITE;	/*Color the node to white by the way*/
			vertices[vertex_index].distance=POS_INFI;	/*For BFS the distanec to the sourec must be 0*/
			vertices[vertex_index].pre=vertex_index;	/*For BFS the distanec to the sourec must be 0*/
		}
		else	/*If not, attach it to the next pointer*/
		{
			list_tail->next=new_vertex;
		}

		/*list_tail points to the tail of the Adj link list for next insert*/
		list_tail=new_vertex;
	}
	#if 1
	/*Check the adj list*/
	printf("Graph G=(V,E)\r\n");
	printf("Vertices V={a,b,c,d,e}\r\n");
	printf("Edges weights:\r\n");
	for(i=0,vertex_index=0;i<V_NUM;++i)
	{
		new_vertex=vertices[i].Adj;
		while(new_vertex!=0)
		{
			printf("w(%c,%c)=%d,",i+'a',new_vertex->vertex+'a',new_vertex->weight);
			new_vertex=new_vertex->next;
		}
	}
	printf("\b \r\n\r\n");
	#endif

	/*Using Prim algorithm to get the minimum spanning tree*/
	Dijkstra(vertices);
}

int Dijkstra(VERTICES_ARRAY v[])
{
	int i=0,j=0;
	int in_Q[V_NUM]={0};	/*0 means in Q, otherwise not in Q*/
	int pre[V_NUM]={0};
	unsigned int min_value=-1,min=0,source=0;
	ADJACENCY_LIST *adj=0;
	int predecessor=0;

	source=0;
	//v[source].distance=POS_INFI;
	/*Get n-1 edges for the minimum spanning tree*/
	for(j=1,min=source;j<=V_NUM-1;++j)
	{

#if 0		/*Use to observe the vertex in Q with it's shorted distance to V-Q*/
		int k; 

		printf("\r\n");
		for(k=0;k<V_NUM;++k)
		{
			printf("  %c",k+'a');
		}
		printf("\r\n");
		for(k=0;k<V_NUM;++k)
		{
			printf("%3d",in_Q[k]);
		}
		printf("\r\n");
		for(k=0;k<V_NUM;++k)
		{
			printf("%3d",weights[k]);
		}
		printf("\r\n");
#endif
		/*Choose the last minimum weight vertex picked as the current vertex, equals to 'a' for the first time*/
		in_Q[min]=1;		/*Exclude it out of Q*/
		adj=v[min].Adj;
		/*Upadte the shorted distance from Q to V-Q based on the adjancency list of the newest picked vertex from Q*/
		while(adj!=0)
		{
			relaxation(v,min,adj->vertex,adj->weight);	/*Relax every edge of the newly added vertex*/
			adj=adj->next;
		}

		/*Fetch the minimum value min from Q*/
		/*Q is supposed to be a mim-heap, but for simplicity, an array is used instead*/
#if 1
		min_value=POS_INFI;
		min=-1;
		for(i=0;i<V_NUM;++i)
		{
			if(in_Q[i]==0&&(v[i].distance<min_value))
			{
				min_value=v[i].distance;
				min=i;
			}
		}
#endif
	}

	printf("Printing the shortest path using Dijkstra algorithm:\r\n");
	for(i=0;i<V_NUM;++i)
	{
		if(i!=source)
		{
			printf("Shortest path from %c to %c: %c",source+'a',i+'a',i+'a');
			predecessor=v[i].pre;
			while(predecessor!=NIL)
			{	
				printf("<-%c",predecessor+'a');
				predecessor=v[predecessor].pre;
			}
			printf(", weight=%d\r\n",v[i].distance);
		}
	}
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
