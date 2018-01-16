#include <stdio.h>
#include <malloc.h>

/*Structure of BST's node*/
typedef struct binary_tree_node
{
	int key;
	struct binary_tree_node *parent;
	struct binary_tree_node *left;
	struct binary_tree_node *right;
}BINARY_TREE_NODE;

/*Traverse the whole tree*/
int inorder_traverse(BINARY_TREE_NODE *node);	/*T(n)=O(n), proved by subtitution method*/

/*Query Operations of BST*/
BINARY_TREE_NODE* search_key(BINARY_TREE_NODE *node,int k);
BINARY_TREE_NODE* maximum_key_node(BINARY_TREE_NODE *node);
BINARY_TREE_NODE* minimum_key_node(BINARY_TREE_NODE *node);
BINARY_TREE_NODE successor(BINARY_TREE_NODE *node,BINARY_TREE_NODE *new_node);
BINARY_TREE_NODE predeccessor(BINARY_TREE_NODE *node,BINARY_TREE_NODE *new_node);
int insert_node(BINARY_TREE_NODE *node,BINARY_TREE_NODE *new_node);
BINARY_TREE_NODE delete_node(BINARY_TREE_NODE *node,BINARY_TREE_NODE *new_node);

int main(void)
{
	BINARY_TREE_NODE* root_pointer=NULL;
	BINARY_TREE_NODE* node=NULL;

	int keys[]={15,6,18,3,7,17,20,2,4,13,9};
	int array_size=sizeof(keys)/sizeof(keys[0]);
	int i=0;

	for(i=0;i<array_size;++i)
	{
		/*Create a new node, initialize it with a key*/
		node=(BINARY_TREE_NODE*)malloc(sizeof(BINARY_TREE_NODE));
		node->key=keys[i];
		node->left=NULL;
		node->right=NULL;
		node->parent=NULL;

		if(root_pointer==NULL)
		{
			root_pointer=node;
			printf("BST starts with root key=%d.\r\n",root_pointer->key);
			continue;
		}

		insert_node(root_pointer,node);

		/*Search the key to confirm the insertion is successful*/
		if(search_key(root_pointer,keys[i]))
		{
			printf("Node with key=%d inserted.\r\n",keys[i]);
		}
		else
		{
			printf("Node with key=%d failed to insert.\r\n",keys[i]);
		}
	}

	printf("\r\nTraversing the binary tree:\r\n");
	inorder_traverse(root_pointer);
	printf("\b \r\n");

	node=minimum_key_node(root_pointer);
	printf("Node with minimum key=%d.\r\n",node->key);

	node=maximum_key_node(root_pointer);
	printf("Node with maximum key=%d.\r\n",node->key);

	return 0;
}

BINARY_TREE_NODE* search_key(BINARY_TREE_NODE *node,int k)
{
	BINARY_TREE_NODE* current=node;
	
	while((current!=NULL)&&((current->key)!=k))
	{
		if(k<(current->key))	/*Search the left subtree*/
		{
			current=current->left;
		}
		else
		{	/*Search the right subtree*/
			current=current->right;
		}
	}

	return current;	/*NULL when not found*/
}



int inorder_traverse(BINARY_TREE_NODE *node)
{
	if(node!=NULL)		/*recursion termination condition: the tree is empty*/
	{
		/*Inorder traverse: Left-Root-Right */
		inorder_traverse(node->left);
		printf("%d,",node->key);
		inorder_traverse(node->right);		
	}

	return 0;
}

int insert_node(BINARY_TREE_NODE *node,BINARY_TREE_NODE *new_node)
{
	BINARY_TREE_NODE* current=node;
	BINARY_TREE_NODE* trailing=NULL;	/*trailing pointer points to the parent of the current tree node after one loop*/

	/*Can't insert empty tree*/
	if(node==NULL)
	{	
		printf("The tree has no root");
		return -1;
	}

	/*Looking for the correct position for the new_node to insert*/
	while(current!=NULL)
	{
		trailing=current;
		if((new_node->key)<=(current->key))	/*go to the left subtree*/
		{
			current=current->left;
		}
		else
		{
			current=current->right;
		}
	}

	/*Insert new node*/
	if((new_node->key)<=(trailing->key))
	{
		trailing->left=new_node;	/*Insert to the left child*/
	}
	else
	{
		trailing->right=new_node;	/*Insert to the right child*/
	}

	new_node->parent=trailing;		/*new_node's parent*/

	return 0;
}


BINARY_TREE_NODE* maximum_key_node(BINARY_TREE_NODE *node)
{
	BINARY_TREE_NODE* current=node;

	while((current!=NULL)&&(current->right!=NULL))
	{
		current=current->right;
	}

	return current;
}

BINARY_TREE_NODE* minimum_key_node(BINARY_TREE_NODE *node)
{
	BINARY_TREE_NODE* current=node;

	while((current!=NULL)&&(current->left!=NULL))
	{
		current=current->left;
	}

	return current;
}

