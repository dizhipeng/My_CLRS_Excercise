#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define V_NUM	9
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

int Prim(VERTICES_ARRAY v[]);

int main(void)
{
	VERTICES_ARRAY vertices[V_NUM];		/*Space cost O(V+E), good for sparse graph*/
	memset(vertices,0,sizeof(vertices));

	ADJACENCY_LIST *new_vertex=0;	
	ADJACENCY_LIST *list_tail=0;

	int i=0;
	int vertex_index=0;

	/*The adjacent vertices for every vertex, seperated by |*/
	char connections[]="bh|ahc|bifd|cfe|df|gcde|hif|abig|hcg";
	int weights[]={4,8,-1,4,11,8,-1,8,2,4,7,-1,7,14,9,-1,9,10,-1,2,4,14,10,-1,1,6,2,-1,8,11,7,1,-1,7,2,6,-1};
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
	#if 1
	/*Check the adj list*/
	printf("Graph G=(V,E)\r\n");
	printf("Vertices V={r,s,t,u,v,w,x,y}\r\n");
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

	/*Begin BFS from vertex s*/
	Prim(vertices);
}

int Prim(VERTICES_ARRAY v[])
{
	int i=0,j=0;
	unsigned int weights[V_NUM]={0};
	int in_Q[V_NUM]={0};	/*0 means in Q, otherwise not in Q*/
	int pre[V_NUM]={0};
	unsigned int min_value=-1,min=0;
	ADJACENCY_LIST *adj=0;

	/*Initial the weights for all vertices to positive infinity*/
	for(i=0;i<V_NUM;++i)
	{
		weights[i]=-1;
	}
	printf("All edges in the minimum spanning tree of graph G obtained by prim algorithm:\r\n");

	/*Get n-1 edges for the minimum spanning tree*/
	for(j=1,min=0;j<=V_NUM-1;++j)
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
			if(in_Q[adj->vertex]==0&&adj->weight<weights[adj->vertex])
			{
				weights[adj->vertex]=adj->weight;
				pre[adj->vertex]=min;	/*If updated, record the current parent*/
			}
			adj=adj->next;
		}

		/*Fetch the minimum value min from Q*/
		/*Q is supposed to be a mim-heap, but for simplicity, an array is used instead*/
		min_value=-1;
		min=-1;
		for(i=1;i<V_NUM;++i)
		{
			if(in_Q[i]==0&&weights[i]<min_value)
			{
				min_value=weights[i];
				min=i;
			}
		}

		/*Print the result: the vertex picked, its parent and the weight of the edge between them*/
		printf("w(%c,%c)=%u\r\n",pre[min]+'a',min+'a',min_value);
	}

}
