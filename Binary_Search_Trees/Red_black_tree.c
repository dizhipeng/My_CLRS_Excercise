#include <stdio.h>
#include <malloc.h>

#define RED	0
#define BLACK	1

/*Structure of BST's node*/
typedef struct binary_tree_node
{
	int key;
	struct binary_tree_node *parent;
	struct binary_tree_node *left;
	struct binary_tree_node *right;
	int color;
}BINARY_TREE_NODE;

/*The nil node for the parent of root and the leaves*/
BINARY_TREE_NODE *nil=0;

/*Initialize nil node, allocate space for it, and color it black*/
int init_nil()
{
	nil=(BINARY_TREE_NODE *)malloc(sizeof(BINARY_TREE_NODE));
	nil->color=BLACK;
}

#define NIL nil

/*Traverse the whole tree*/
int inorder_traverse(BINARY_TREE_NODE *node);	/*T(n)=O(n), proved by subtitution method*/
int preorder_traverse(BINARY_TREE_NODE *node);	/*T(n)=O(n), proved by subtitution method*/

/*Query Operations of BST*/
BINARY_TREE_NODE* search_key(BINARY_TREE_NODE *node,int k);
BINARY_TREE_NODE* minimum_key_node(BINARY_TREE_NODE *node);
#if 0
BINARY_TREE_NODE* maximum_key_node(BINARY_TREE_NODE *node);
BINARY_TREE_NODE *successor(BINARY_TREE_NODE *node,BINARY_TREE_NODE *obj)
BINARY_TREE_NODE* predecessor(BINARY_TREE_NODE *node,BINARY_TREE_NODE *obj);
#endif

/*Modification Operation of BST,these operations may change the root*/
int insert_node(BINARY_TREE_NODE **root,BINARY_TREE_NODE *new_node);
int delete_node(BINARY_TREE_NODE **root,BINARY_TREE_NODE *node);
int transplant(BINARY_TREE_NODE **root,BINARY_TREE_NODE *x,BINARY_TREE_NODE *y);	
/*Revome node x from its position in the tree, and attach y with y's subtree at this position*/
/*!!!!Change one connect requires to change two pointers!!!!!*/

/*Operations used for balance the red-black tree*/
int rotate_left(BINARY_TREE_NODE **root,BINARY_TREE_NODE *node);
int rotate_right(BINARY_TREE_NODE **root,BINARY_TREE_NODE *node);
int correct_insertion_voilation(BINARY_TREE_NODE **root,BINARY_TREE_NODE *node);
int correct_deletion_voilation(BINARY_TREE_NODE **root,BINARY_TREE_NODE *node);

int main(void)
{
	init_nil();

	BINARY_TREE_NODE* root_pointer=0;
	BINARY_TREE_NODE* node=0;

	int keys[]={21,24,26,28,30,32,34,36,38,40,42,18,16,14,12,10,8,6,4,2,37,20,1,3,5,7,33,35,31,43,45};
	int array_size=sizeof(keys)/sizeof(keys[0]);
	int i=0;

	for(i=0;i<array_size;++i)
	{
		/*Create a new node, initialize it with a key*/
		node=(BINARY_TREE_NODE*)malloc(sizeof(BINARY_TREE_NODE));
		node->key=keys[i];
		node->left=NIL;
		node->right=NIL;
		node->parent=NIL;
		node->color=RED;	/*Newly inserted node is always red*/

		insert_node(&root_pointer,node);

		/*Search the key to confirm the insertion is successful*/
		#if 0
		if(search_key(root_pointer,keys[i])!=NIL)
		{
			printf("Node with key=%d inserted.\r\n",keys[i]);
		}
		else
		{
			printf("Node with key=%d failed to insert.\r\n",keys[i]);
		}
		#endif
	}

	printf("Preorder and inorder traversing the binary tree after an insertion:\r\n");
	preorder_traverse(root_pointer);
	printf("\b \r\n");
	inorder_traverse(root_pointer);
	printf("\b \r\n\r\n");
	node=search_key(root_pointer,16);
	delete_node(&root_pointer,node);

	//node=search_key(root_pointer,14);
	//delete_node(&root_pointer,node);

	printf("Preorder and inorder traversing the binary tree after an insertion:\r\n");
	preorder_traverse(root_pointer);
	printf("\b \r\n");
	inorder_traverse(root_pointer);
	printf("\b \r\n\r\n");
	//node=search_key(root_pointer,keys[0]);

	//printf("key=%d\r\n",node->key);

	return 0;
}

int delete_node(BINARY_TREE_NODE **root,BINARY_TREE_NODE *node)
{
	BINARY_TREE_NODE *y=0;		/*Point to z if z has only one child, otherwise point to z's successor that is going to be replace z*/
	BINARY_TREE_NODE *x=0;		/*Point to the node that is going to replace y. x is the only source that causes voilation*/
	int y_original_color=BLACK;	/*Save y's color before any change*/

	if(node->left==NIL)		/*Left subtree is empty*/	/*y=z,x replaces y*/
	{
		y=node;
		x=node->right;
		y_original_color=y->color;
		transplant(root,y,x);
	}
	else if(node->right==NIL)		/*Right subtree is empty*/	/*y=z,x replaces y*/
	{
		y=node;
		x=node->left;
		y_original_color=y->color;
		transplant(root,y,x);
	}
	else		/*Neither left nor right subtree is empty*/
	{
		y=minimum_key_node(node->right);		/*y is node's successor who will replace node*/
		x=y->right;
		y_original_color=y->color;
		if(y!=node->right)
		{
			/*Replace successor right child to successor*/
			transplant(root,y,x);

			/*Relocate successor's right subtree to the node's right subtree*/
			y->right=node->right;
			node->right->parent=y;

		}

		/*Relocate successor's right subtree to the node's right subtree*/
		y->left=node->left;
		node->left->parent=y;

		/*Color y the same with z, so no voilation at y*/
		y->color=node->color;	

		/*Replace node with it's successor*/
		transplant(root,node,y);
	}

	if(y_original_color==BLACK)			/*Only when y is red, x will be red-black or double-black*/
	{
//		correct_deletion_voilation(root,x);	/*Deal with voilation of x*/
	}

	free(node);
	return 0;
}

/*Solve voilation caused by x*/
int correct_deletion_voilation(BINARY_TREE_NODE **root,BINARY_TREE_NODE *node)
{
	BINARY_TREE_NODE *x=node;
	BINARY_TREE_NODE *sibling=0;
						
	while(x!=(*root) && x->color==BLACK )	/*Process only if x is non-root and double-black, or color x black directly will suffice*/
	{
		if(x->parent->left==x)
		{
			sibling=x->parent->right;	/*Solving the voilation based on x's sibling*/

			if(sibling->color==RED)		/*Left rotation to change x's sibling black*/
			{
				x->parent->color=RED;
				sibling->color=BLACK;
				rotate_left(root,x->parent);
				sibling=x->parent->right;
			}

			/*Sibling is BLACK*/
			if(sibling->right->color==BLACK)	
			{
				if(sibling->left->color==BLACK)	/*Sibling's both children are black, then change sibling to red is safe*/
				{
					sibling->color=RED;	/*x changes from double-black to black, sibling changes to red*/
					x=x->parent;		/*The redundant blackness is passed to x's parent*/
					continue;
				}
				else	/*Move red node from sibling's left child to right*/
				{
					sibling->left->color=BLACK;
					sibling->color=RED;
					rotate_right(root,sibling);
				}
			}

			/*Sibling's right child is red, the last situation to deal with*/
			sibling->color=x->parent->color;
			x->parent->color=BLACK;
			sibling->right->color=BLACK;
			rotate_left(root,x->parent);

		}
		else
		{
			sibling=x->parent->left;

			if(sibling->color==RED)		/*Left rotation to change x's sibling black*/
			{
				x->parent->color=RED;
				sibling->color=BLACK;
				rotate_right(root,x->parent);
				sibling=x->parent->left;
			}

			/*Sibling is BLACK*/
			if(sibling->left->color==BLACK)	
			{
				if(sibling->right->color==BLACK)	/*Sibling's both children are black, then change sibling to red is safe*/
				{
					sibling->color=RED;	/*x changes from double-black to black, sibling changes to red*/
					x=x->parent;		/*The redundant blackness is passed to x's parent*/
					continue;
				}
				else	/*Move red node from sibling's left child to right*/
				{
					sibling->right->color=BLACK;
					sibling->color=RED;
					rotate_left(root,sibling);
				}
			}

			/*Sibling's right child is red, the last situation to deal with*/
			sibling->color=x->parent->color;
			x->parent->color=BLACK;
			sibling->left->color=BLACK;
			rotate_right(root,x->parent);

		}
	}
	x->color=BLACK;	/*Color x black directly to turn x from red-black to black*/
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

BINARY_TREE_NODE* search_key(BINARY_TREE_NODE *node,int k)
{
	BINARY_TREE_NODE* current=node;
	
	while((current!=NIL)&&((current->key)!=k))
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
	if(node!=NIL)		/*recursion termination condition: the tree is empty*/
	{
		/*Inorder traverse: Left-Root-Right */
		inorder_traverse(node->left);
		if(node->color)
		{
			printf("%d,B|",node->key);
		}
		else
		{
			printf("%d,R|",node->key);
		}
		inorder_traverse(node->right);		
	}

	return 0;
}

int preorder_traverse(BINARY_TREE_NODE *node)
{
	if(node!=NIL)		/*recursion termination condition: the tree is empty*/
	{
		/*Inorder traverse: Left-Root-Right */
		if(node->color)
		{
			printf("%d,B|",node->key);
		}
		else
		{
			printf("%d,R|",node->key);
		}
		preorder_traverse(node->left);
		preorder_traverse(node->right);		
	}

	return 0;
}

BINARY_TREE_NODE* minimum_key_node(BINARY_TREE_NODE *node)
{
	BINARY_TREE_NODE* current=node;

	while((current!=NIL)&&(current->left!=NIL))
	{
		current=current->left;
	}

	return current;
}

int insert_node(BINARY_TREE_NODE **root,BINARY_TREE_NODE *new_node)
{

	/*Insert new_node as root, and color the root black*/
	if((*root)==0)
	{
		new_node->color=BLACK;
		new_node->parent=NIL;
		(*root)=new_node;
		return 0;
	}

	BINARY_TREE_NODE* current=*root;
	BINARY_TREE_NODE* trailing=0;	/*trailing pointer points to the parent of the current tree node after one loop*/

	/*Looking for the correct position for the new_node to insert*/
	while(current!=NIL)
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

	correct_insertion_voilation(root,new_node);

	return 0;
}

int transplant(BINARY_TREE_NODE **root,BINARY_TREE_NODE *x,BINARY_TREE_NODE *y)
{
	if(x->parent!=NIL)	/*Connect x's parent to y*/
	{
		if(x==x->parent->left)
		{
			x->parent->left=y;
		}
		else
		{
			x->parent->right=y;
		}
		
		y->parent=x->parent;
	}
	else	/*x is root, then y becomes the new root*/
	{
		(*root)=y;
		y->parent=NIL;
	}

	return 0;
}

int rotate_left(BINARY_TREE_NODE **root,BINARY_TREE_NODE *node)
{
	BINARY_TREE_NODE *new_node=node->right;
	transplant(root,node,new_node);

	/*Traversing*/
	//printf("\r\nPreorder traversing the binary tree:\r\n");
	//preorder_traverse(*root);
	//printf("\b \r\nInorder traversing the binary tree:\r\n");
	//inorder_traverse(*root);
	//printf("\b \r\n\r\n");

	if(new_node->left!=NIL)
	{	
		new_node->left->parent=node;
	}	
	node->right=new_node->left;

	node->parent=new_node;
	new_node->left=node;
}

int rotate_right(BINARY_TREE_NODE **root,BINARY_TREE_NODE *node)
{
	BINARY_TREE_NODE *new_node=node->left;
	transplant(root,node,new_node);

	if(new_node->right!=NIL)
	{	
		new_node->right->parent=node;
	}	
	node->left=new_node->right;

	node->parent=new_node;
	new_node->right=node;
}

/*The newly added node could voilate the properties of red-black tree*/
/*This function correct all voilations caused by the insertion operation*/
int correct_insertion_voilation(BINARY_TREE_NODE **root,BINARY_TREE_NODE *node)
{
	BINARY_TREE_NODE *z=node;
	BINARY_TREE_NODE *grand=0;
	BINARY_TREE_NODE *uncle=0;

	while(z->parent->color==RED)	/*Voilations exist when current node z's parent is red, because in the loop z is alway red*/
	{
		grand=z->parent->parent;

		if(z->parent==grand->left)	/*If z's parent is a left child, z has a right uncle*/
		{
			uncle=grand->right;
			
			//printf("Right uncle color=%d",uncle->color);
			if(uncle->color==RED)	/*z's parent and uncle are both red, just coloring, no rotations*/
			{
				grand->color=RED;	/*Recolor z's parent, grand and uncle*/
				uncle->color=BLACK;
				z->parent->color=BLACK;

				z=grand;	/*z's grand becomes red, then correct the voilation of grand*/
			}
			else	/*Rotation is necessary*/
			{
				if(z==z->parent->right)	/*First, adjust z/parent/grand to be in a straight line*/
				{
					//printf("Making a left straight line\r\n");
					rotate_left(root,z->parent);
					z=z->left;
				}

				z->parent->color=BLACK;
				grand->color=RED;
				rotate_right(root,grand);
			}
		}
		else	/*Z has a left uncle*/
		{

			uncle=grand->left;

			//printf("Left uncle color=%d,key=%d\r\n",uncle->color,uncle->key);
			if(uncle->color==RED)	/*z's parent and uncle are both red, just coloring, no rotations*/
			{
				grand->color=RED;	/*Recolor z's parent, grand and uncle*/
				uncle->color=BLACK;
				z->parent->color=BLACK;

				z=grand;	/*z's grand becomes red, then correct the voilation of grand*/
			}
			else	/*Rotation is necessary*/
			{
				if(z==z->parent->left)	/*First, adjust z/parent/grand to be in a straight line*/
				{
						//printf("Making a right straight line\r\n");
						rotate_right(root,z->parent);
						z=z->right;
				}

				z->parent->color=BLACK;
				grand->color=RED;
				rotate_left(root,grand);
			}
		}
	}

	(*root)->color=BLACK;

}

