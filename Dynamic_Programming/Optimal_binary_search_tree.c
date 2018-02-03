#include <stdio.h>
#include <malloc.h>

#define POS_INFINI 0xfffffff
#define LEFT  0
#define RIGHT 1
/*Structure of BST's node*/
typedef struct binary_tree_node
{
	int key;
	struct binary_tree_node *parent;
	struct binary_tree_node *left;
	struct binary_tree_node *right;
}BINARY_TREE_NODE;

int rebuild_tree(BINARY_TREE_NODE **root,int c[][50],int start,int end);
int build_subtree(BINARY_TREE_NODE *root,int c[][50],int start,int end,int l_or_r);
int preorder_traverse(BINARY_TREE_NODE *node);
	
int main()
{

	int p[]={0,15,10,5,10,20};
	int q[]={5,10,5,5,5,10};

	int nodes=sizeof(p)/sizeof(p[0])-1;

	int i=0,j=0,r=0,l=0;
	int c[50][50]={0};		/*The optimal search cost matrix*/
	int w[50][50]={0};		/*The summary of pi and qi*/
	int root[50][50]={0};	/*The root at every level of the binary tree, used to rebuild the tree from c*/
	int temp=0,min=0;

	BINARY_TREE_NODE *root_pointer=0;

	/*The start point of dynamic programming, which only contains every dummy node di for 0<=i<=n*/
	for(j=0;j<=nodes;++j)
	{
		c[j+1][j]=q[j];
		w[j+1][j]=q[j];
	}

	/*Final result: c[1][nodes]*/
	for(l=0;l<=nodes-1;++l)		/*l is the gap between i and j during one iteration*/
	{
		i=1;
		j=i+l;
		//printf("c[%d,%d]=min{",i,j);
		while(j<=nodes)
		{
			min=POS_INFINI;	
			w[i][j]=w[i][j-1]+p[j]+q[j];	/*w[i][j] is sum(pn+qn) for all i<=n<=j, plus q[i-1]*/
			for(r=i;r<=j;++r)		/*w is the increased cost after all the subtrees of node[i..j] has deepered by 1*/
			{
				//printf("c[%d,%d]+c[%d,%d]+w[%d,%d],",i,r-1,r+1,j,i,j);
				temp=c[i][r-1]+c[r+1][j]+w[i][j];
				if(temp<min)	/*Choose the minimun from all c[i][r-1]+c[r+1][j]+w for i<=c<=j*/
				{				/*which is the current optimal substructure*/
					min=temp;
					root[i][j]=r;
				}
			}
			c[i][j]=min;
			++i;			/*Update i,j*/
			j=i+l;
		}
		//printf("\b}\r\n");
	}

	rebuild_tree(&root_pointer,root,1,nodes);

	printf("Optimal binary tree is built for the given probablities of pi(1<=i<=n) and qi(1<=i<=n):\r\n");
	printf("(The leaves d0..di..dn are shown by -i)\r\n");
	preorder_traverse(root_pointer);
	printf("\b \r\n");

	return 0;

}

int rebuild_tree(BINARY_TREE_NODE **root,int c[][50],int start,int end)
{
	/*Allocate root node*/
	BINARY_TREE_NODE *node=(BINARY_TREE_NODE *)malloc(sizeof(BINARY_TREE_NODE));

	/*Find the root key*/
	int key=c[start][end];


	node->key=key;
	/*Build left subtree*/
	build_subtree(node,c,start,key-1,LEFT);

	/*Build right subtree*/
	build_subtree(node,c,key+1,end,RIGHT);

	(*root)=node;

	return 0;
}

int build_subtree(BINARY_TREE_NODE *root,int c[][50],int start,int end,int l_or_r)
{
	/*Find the key for the root of the subtree*/
	int key=c[start][end];

	/*Allocate child root node*/
	BINARY_TREE_NODE *node=(BINARY_TREE_NODE *)malloc(sizeof(BINARY_TREE_NODE));
	node->key=key;
	node->parent=root;

	if(l_or_r==LEFT)
	{
		root->left=node;
	}
	else
	{
		root->right=node;
	}

	if(key!=0)	/*If not 0, bulid left and right subtree of the current subtree recursively*/
	{
		build_subtree(node,c,start,key-1,LEFT);
		build_subtree(node,c,key+1,end,RIGHT);
	}
	else
	{
		node->key=-end;
		node->left=0;
		node->right=0;
	}

	return 0;

}

int preorder_traverse(BINARY_TREE_NODE *node)
{
	if(node!=0)		/*recursion termination condition: the tree is empty*/
	{
		/*Inorder traverse: Left-Root-Right */
		printf("%d,",node->key);
		preorder_traverse(node->left);
		preorder_traverse(node->right);		
	}

	return 0;
}



