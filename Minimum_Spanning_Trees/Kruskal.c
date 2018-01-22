#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define V_NUM	9
#define WHITE 	0
#define GREY  	1
#define BLACK  	2
#define E_NUM   ((V_NUM)*(V_NUM))	/*Edge numbers*/

typedef struct set_object
{
	int head;		/*Index of the head element*/
	int tail;		/*Index of the tail element*/
	int set_size;		/*The size of the disjoint set*/

}SET_OBJ;

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

	/*Field set for the disjoint set*/
	int next;		/*Index of the next element in the disjoint set*/
	SET_OBJ* set_obj;	/*Pointer to the object set*/
	/*The index of the vertex is */

} VERTICES_ARRAY;

/*Set of edges, from which to pick and add to Minimum spannig tree*/
typedef struct edge_set
{
	int vert1;
	int vert2;
	int weight;
}EDGE_SET;

int Union(VERTICES_ARRAY vertices[],int vert1,int vert2);
int Find(VERTICES_ARRAY vertices[],int index);
int Make_Set(VERTICES_ARRAY vertices[],int index);

int main(void)
{

	VERTICES_ARRAY vertices[V_NUM]={0};		/*Space cost O(V+E), good for sparse graph*/

	#if 0
	ADJACENCY_LIST *new_vertex=0;	
	ADJACENCY_LIST *list_tail=0;
	#endif
	int i=0,j=0;
	int vertex_index=0;
	int edge_index=0;

	/*The adjacent vertices for every vertex, seperated by |*/
	char connections[]="bh|ahc|bifd|cfe|df|gcde|hif|abig|hcg|";
	int weights[]={4,8,-1,4,11,8,-1,8,2,4,7,-1,7,14,9,-1,9,10,-1,2,4,14,10,-1,1,6,2,-1,8,11,7,1,-1,7,2,6,-1};
	int connect_num=sizeof(connections)/sizeof(connections[0]);
	EDGE_SET edges[E_NUM]={0};
	EDGE_SET edge_temp={0};		/*for holding the current egde*/

	/*Create the disjoint set for every vertex*/
	for(i=0;i<V_NUM;++i)
	{
		Make_Set(vertices,i);
	}

	/*For kruskal's algorithm, store the edges in non-decreasing order*/
	/*Not necessary to create the adjacency list*/
	/*Construct the graph, node 0~9 corresponds to node a~i*/
	edges[0].vert1=0;
	edges[0].vert2=connections[0]-'a';
	edges[0].weight=weights[0];
	vertex_index=0;
	edge_index=1;
	for(i=1;i<connect_num-1;++i)
	{
		/*Seperator, process the next vertex*/
		if(connections[i]=='|')
		{
			if(((++vertex_index)>=V_NUM)||(weights[i]!=-1))
			{
				break;
			}
			continue;
		}
		else if(connections[i]==' ')	/*No edges connect to the vertex*/
		{
			continue;
		}

		/*Insertion sort the edges according to weight*/
		edge_temp.vert1=vertex_index;
		edge_temp.vert2=connections[i]-'a';
		edge_temp.weight=weights[i];

		for(j=edge_index;j>0&&edge_temp.weight<edges[j-1].weight;--j)
		{
			edges[j]=edges[j-1];
		}
		edges[j]=edge_temp;
		++edge_index;

		#if 0
		/*New item in the adj list*/
		new_vertex=(ADJACENCY_LIST *)malloc(sizeof(ADJACENCY_LIST));
		new_vertex->vertex=connections[i]-'a';
		/*new_vertex->weight=weights[i];*/
		new_vertex->next=0;

		/*If first node in the adj list, put it directly as the head*/
		if(vertices[vertex_index].Adj==0)
		{
			vertices[vertex_index].Adj=new_vertex;
			vertices[vertex_index].color=WHITE;		/*Color the node to white by the way*/
			vertices[vertex_index].distance=0;		/*For BFS the distanec to the sourec must be 0*/
			vertices[vertex_index].pre=vertex_index;	/*For BFS the distanec to the sourec must be 0*/
		}
		else	/*If not, attach it to the next pointer*/
		{
			list_tail->next=new_vertex;
		}

		/*list_tail points to the tail of the Adj link list for next insert*/
		list_tail=new_vertex;


		/*Union vertices connected by an edge*/
		/*Must check whether the two elements are already in the same set!!!!!!*/
		if(Find(vertices,vertex_index)!=Find(vertices,new_vertex->vertex))
		{
			Union(vertices,vertex_index,new_vertex->vertex);
		}
		#endif
	}

	/*Check the adj list*/	
	printf("Graph G=(V,E)\r\n");
	printf("Vertices V={a,b,c,d,e,f,g,h,i}\r\n");
	printf("Edges with weights:\r\n");
	for(i=0;i<edge_index;++i)
	{
		printf("w(%c,%c)=%d,",edges[i].vert1+'a',edges[i].vert2+'a',edges[i].weight);
	}
	printf("\b \r\n\r\n");

	/*Using Kruskal algorithm to get the minimum spanning tree*/
	printf("All edges in the minimum spanning tree of graph G obtained by kruskal algorithm:\r\n");
	for(i=0;i<edge_index;++i)
	{
		if(Find(vertices,edges[i].vert1)!=Find(vertices,edges[i].vert2))
		{
			Union(vertices,edges[i].vert1,edges[i].vert2);
			printf("w(%c,%c)=%d\r\n",edges[i].vert1+'a',edges[i].vert2+'a',edges[i].weight);
		}
	}
	#if 0
	for(i=0,vertex_index=0;i<V_NUM;++i)
	{
		new_vertex=vertices[i].Adj;
		while(new_vertex!=0)
		{
			printf(/*"w(%c,%c)=%d,"*/"(%c,%c),",i+'a',new_vertex->vertex+'a'/*,new_vertex->weight*/);
			new_vertex=new_vertex->next;
		}
	}
	printf("\b \r\n\r\n");
	#endif

	#if 0
	/*Print the result of the disjoint set*/
	printf("Elements in the disjoint set:\r\n");
	printf("Vertex: ");
	for(i=0;i<V_NUM;++i)
	{
		printf("%c, ",i+'a');
	}
	printf("\b \r\nSet   : ");
	for(i=0;i<V_NUM;++i)
	{
		printf("%c, ",Find(vertices,i)+'a');
	}
	printf("\b \r\n");
	#endif

}

/*Creat a disjoint set that includes the only set member vertices[index]*/
int Make_Set(VERTICES_ARRAY vertices[],int index)
{
	SET_OBJ* sn=0;
	sn=(SET_OBJ*)malloc(sizeof(SET_OBJ));

	/*Head and tail points the only set member*/
	sn->head=index;
	sn->tail=index;
	sn->set_size=1;

	/*Assign the set member to the vertex, which has no next vertex in the linked-list*/
	vertices[index].set_obj=sn;
	vertices[index].next=-1;

	return 0;	
}

int Find(VERTICES_ARRAY vertices[],int index)
{
	/*The representive of the set is its head element*/
	return (vertices[index].set_obj)->head;
}

int Union(VERTICES_ARRAY vertices[],int vert1,int vert2)
{
	int small=0,big=0,i;

	/*To achieve better performance, always attach small set to big one.*/
	if((vertices[vert1].set_obj)->set_size > (vertices[vert2].set_obj)->set_size)
	{
		small=vert2;
		big=vert1;
	}
	else
	{
		small=vert1;
		big=vert2;
	}

	SET_OBJ *big_set=vertices[big].set_obj;
	SET_OBJ *small_set=vertices[small].set_obj;

	vertices[big_set->tail].next=small_set->head;
	big_set->tail=small_set->tail;

	i=small_set->head;
	while(i>=0)
	{
		vertices[i].set_obj=big_set;
		i=vertices[i].next;
	}

	(big_set->set_size) += (small_set->set_size);

	free(small_set);

	return 0;
}




