#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define V_NUM	10
#define WHITE 	0
#define GREY  	1
#define BLACK  	2

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

int Union(VERTICES_ARRAY vertices[],int vert1,int vert2);
int Find(VERTICES_ARRAY vertices[],int index);
int Make_Set(VERTICES_ARRAY vertices[],int index);

int main(void)
{
	VERTICES_ARRAY vertices[V_NUM];		/*Space cost O(V+E), good for sparse graph*/
	memset(vertices,0,sizeof(vertices));

	ADJACENCY_LIST *new_vertex=0;	
	ADJACENCY_LIST *list_tail=0;

	int i=0;
	int vertex_index=0;

	/*The adjacent vertices for every vertex, seperated by |*/
	char connections[]="bc|acd|ab|b|fg|e|e|i|h| |";
	/*int weights[]={4,8,-1,4,11,8,-1,8,2,4,7,-1,7,14,9,-1,9,10,-1,2,4,14,10,-1,1,6,2,-1,8,11,7,1,-1,7,2,6,-1};*/
	int connect_num=sizeof(connections)/sizeof(connections[0]);
	

	/*Create the disjoint set for every vertex*/
	for(i=0;i<V_NUM;++i)
	{
		Make_Set(vertices,i);
	}

	/*Construct the graph, node 0~7 corresponds to node r~y*/
	for(i=0,vertex_index=0;i<connect_num-1;++i)
	{
		/*Seperator, process the next vertex*/
		if(connections[i]=='|')
		{
			if(((++vertex_index)>=V_NUM)/*||(weights[i]!=-1)*/)
			{
				break;
			}
			continue;
		}
		else if(connections[i]==' ')	/*No edges connect to the vertex*/
		{
			continue;
		}

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
	}

	#if 1
	/*Check the adj list*/
	printf("Graph G=(V,E)\r\n");
	printf("Vertices V={r,s,t,u,v,w,x,y}\r\n");
	printf("Edges:\r\n");
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




