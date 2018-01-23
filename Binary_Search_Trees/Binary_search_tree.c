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
BINARY_TREE_NODE* successor(BINARY_TREE_NODE *node,BINARY_TREE_NODE *obj);
BINARY_TREE_NODE* predecessor(BINARY_TREE_NODE *node,BINARY_TREE_NODE *obj);

/*Modification Operation of BST,these operations may change the root*/
int insert_node(BINARY_TREE_NODE **root,BINARY_TREE_NODE *new_node);
int delete_node(BINARY_TREE_NODE **root,BINARY_TREE_NODE *node);
int transplant(BINARY_TREE_NODE **root,BINARY_TREE_NODE *x,BINARY_TREE_NODE *y);	
/*Revome node x from its position in the tree, and attach y with y's subtree at this position*/
/*!!!!Change one connect requires to change two pointers!!!!!*/

int rotate_left(BINARY_TREE_NODE **root,BINARY_TREE_NODE *node);

int main(void)
{
	BINARY_TREE_NODE* root_pointer=0;
	BINARY_TREE_NODE* node=0;

	int keys[]={15,6,19,3,7,17,20,2,4,13,9,18};
	int array_size=sizeof(keys)/sizeof(keys[0]);
	int i=0;

	for(i=0;i<array_size;++i)
	{
		/*Create a new node, initialize it with a key*/
		node=(BINARY_TREE_NODE*)malloc(sizeof(BINARY_TREE_NODE));
		node->key=keys[i];
		node->left=0;
		node->right=0;
		node->parent=0;

		insert_node(&root_pointer,node);

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

	//delete_node(&root,);

	/*Traversing*/
	printf("\r\nTraversing the binary tree:\r\n");
	inorder_traverse(root_pointer);
	printf("\b \r\n\r\n");

	/*Minimum and successor*/
	node=minimum_key_node(root_pointer);
	printf("Node with minimum key=%d.\r\n",node->key);
	for(i=1;i<=array_size-1;++i)
	{	
		printf("The successor of %d is ",node->key);
		node=successor(root_pointer,node);
		printf("%d\r\n",node->key);
	}
	printf("\b \r\n");

	/*Maximum and predecessor*/	
	node=maximum_key_node(root_pointer);
	printf("Node with maximum key=%d.\r\n",node->key);
	for(i=1;i<=array_size-1;++i)
	{	
		if(node->key==15)
		{
			delete_node(&root_pointer,node);
			break;
		}
 
		printf("The predecessor of %d is ",node->key);
		node=predecessor(root_pointer,node);
		printf("%d\r\n",node->key);
	}
	printf("\b \r\n");

	inorder_traverse(root_pointer);

	return 0;
}

BINARY_TREE_NODE* search_key(BINARY_TREE_NODE *node,int k)
{
	BINARY_TREE_NODE* current=node;
	
	while((current!=0)&&((current->key)!=k))
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
	if(node!=0)		/*recursion termination condition: the tree is empty*/
	{
		/*Inorder traverse: Left-Root-Right */
		inorder_traverse(node->left);
		printf("%d,",node->key);
		inorder_traverse(node->right);		
	}

	return 0;
}

int insert_node(BINARY_TREE_NODE **node,BINARY_TREE_NODE *new_node)
{

	/*Insert new_node as root*/
	if((*node)==0)
	{	
		(*node)=new_node;
		return 0;
	}

	BINARY_TREE_NODE* current=*node;
	BINARY_TREE_NODE* trailing=0;	/*trailing pointer points to the parent of the current tree node after one loop*/

	/*Looking for the correct position for the new_node to insert*/
	while(current!=0)
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

	while((current!=0)&&(current->right!=0))
	{
		current=current->right;
	}

	return current;
}

BINARY_TREE_NODE* minimum_key_node(BINARY_TREE_NODE *node)
{
	BINARY_TREE_NODE* current=node;

	while((current!=0)&&(current->left!=0))
	{
		current=current->left;
	}

	return current;
}



BINARY_TREE_NODE *successor(BINARY_TREE_NODE *node,BINARY_TREE_NODE *obj)
{
	BINARY_TREE_NODE *x=obj,*y=0;
	/*If the node has a right subtree, then it's successor must be the minimum of the node of the right subtree*/
	if(obj->right)
	{
		return minimum_key_node(obj->right);
	}
	else /*If the node has a right subtree, then the successor is in its upstream nodes*/
	{	
		/*the node is the first right child of the upstream nodes.If reaches root, then there's no successor*/
		while((x->parent!=0)&&(x->parent->right==x))
		{
			x=x->parent;
		}

		return x->parent;
	}
}

/*Opposite to successor, comment omitted*/
BINARY_TREE_NODE *predecessor(BINARY_TREE_NODE *node,BINARY_TREE_NODE *obj)
{
	BINARY_TREE_NODE *x=obj,*y=0;

	if(obj->left)
	{
		return maximum_key_node(obj->left);
	}
	else
	{	
		while((x->parent!=0)&&(x->parent->left==x))
		{
			x=x->parent;
		}

		return x->parent;
	}
}

#if 1
int transplant(BINARY_TREE_NODE **root,BINARY_TREE_NODE *x,BINARY_TREE_NODE *y)
{
	if(x->parent)	/*Connect x's parent to y*/
	{
		if(x=x->parent->left)
		{
			x->parent->left=y;
		}
		else
		{
			x->parent->right=y;
		}
		
		if(y)		
		{
			y->parent=x->parent;
		}
	}
	else	/*x is root, then y becomes the new root*/
	{
		(*root)=y;
	}

	return 0;
}
#endif

int delete_node(BINARY_TREE_NODE **root,BINARY_TREE_NODE *node)
{
	BINARY_TREE_NODE *successor_node=0;

	if(!(node->left))		/*Left subtree is empty*/
	{
		transplant(root,node,node->right);
	}
	else if(!(node->right))		/*Right subtree is empty*/
	{
		transplant(root,node,node->left);

	}
	else		/*Neither left nor right subtree is empty*/
	{
		successor_node=minimum_key_node(node->right);		/*Get the node's successor who will replace the node*/
		if(successor_node!=node->right)
		{
			/*Replace successor right child to successor*/
			transplant(root,successor_node,successor_node->right);

			/*Relocate successor's right subtree to the node's right subtree*/
			successor_node->right=node->right;
			node->right->parent=successor_node;
		}

		/*Relocate successor's right subtree to the node's right subtree*/
		successor_node->left=node->left;
		node->left->parent=successor_node;

		/*Replace node with it's successor*/
		transplant(root,node,successor_node);
	}

	free(node);
	return 0;
}

int rotate_left(BINARY_TREE_NODE **root,BINARY_TREE_NODE *node)
{
	BINARY_TREE_NODE *new_node=node->right;
	transplant(0,node,new_node);

	new_node->left->parent=node;
	node->right=new_node->left;

	node->parent=new_node;
	new_node->left=node;
}

//15,6,3,2,4,7,13,9,19,17,18,20 
//2,3,4,6,7,9,13,  15  ,17,18,  19  ,20 



