//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 5
		 Implementing 'remove node' operation for BST*/
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS2(BSTNode *root);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);
BSTNode* removeNodeFromTree(BSTNode *root, int value);
BSTNode * findNode(BSTNode * root, int value);
BSTNode * findMinNode(BSTNode * root);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode * root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS2(root); // You need to code this function
			printf("\n");
			break;
		case 3:
			printf("before delete node ");
			postOrderIterativeS2(root); 
			printf("want remove node: ");
			scanf("%d", &i);

			removeNodeFromTree(root, i);
			printf("after delete node");
			postOrderIterativeS2(root); 
			printf("\n");
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

/**
 * 후위 순회
 *  1. 루트 노드를 젤 먼저 방문하게 되지만 젤 마지막으로 출력해야 한다.
 *  2. 왼쪽 노드 -> 오른쪽 노드로 방문해야 한다.
 * 
 * 스택의 특성 상 먼저 들어간 노드가 젤 마지막에 나오게 된다.
 * 따라서 루트 노드를 젤 먼저 넣고, 이후 오른쪽 왼쪽을 넣게 되면
 * 스택에서 나오는 순서가 왼쪽 -> 오른쪽 -> 루트 노드이다.
 * 
*/
void postOrderIterativeS2(BSTNode *root)
{
	BSTNode * temp;
	 if (root==NULL)
	 {
		return ;
	 }

	// 방문한 노드는 해당 스택에 저장한다
	Stack * stack1 = malloc(sizeof(Stack));
	stack1->top= NULL;

	// 해당 스택을 pop하면 후위순회의 결과와 일치한다.
	Stack * stack2 = malloc(sizeof(Stack));
	stack2->top= NULL;

	if (stack1 == NULL && stack2 == NULL)
	{
		return ;
	}

	push(stack1, root);

	while(!isEmpty(stack1))
	{
		temp = pop(stack1);
		push(stack2, temp);

		if (temp -> left!=NULL)
		{	
			push(stack1, temp->left);
		}

		// 오른쪽을 stack1에 먼저 넣어야
		// stack1에서 왼쪽보다 더 먼저 나온다.
		// 따라서 stack2에는 더 먼저 들어가기 때문에
		// 오른쪽이 왼쪽보다 더 늦게 출력된다.
		if (temp ->right!=NULL)
		{	
			push(stack1, temp->right);
		}
	}
	

	while (!isEmpty(stack2))
	{
		printf("%d ", pop(stack2)->item);
	}
}

/* Given a binary search tree and a key, this function
   deletes the key and returns the new root. Make recursive function. */
BSTNode* removeNodeFromTree(BSTNode *root, int value)
{	
	BSTNode * temp;

	if (root == NULL)
	{
		return NULL;
	}

	if (root->item < value)
	{
		root ->right = removeNodeFromTree(root -> right, value);
	}
	if (root -> item >value)
	{
		root -> left = removeNodeFromTree(root -> left, value);
	}
	if (root -> item == value)
	{
		// 삭제하고자 하는 노드가 리프노드라면
		if (root->left ==NULL && root->right == NULL)
		{
			free(root);
			printf("%s\n", "왜 종료안해?");
			return NULL;
		}

		// 오른쪽 서브노드만 존재한다면
		if (root ->left ==NULL && root -> right !=NULL)
		{
			free(root);
			return root->right;
		}

		// 왼쪽 서브노드만 존재한다면
		if (root ->left !=NULL && root -> right ==NULL)
		{
			free(root);
			return root->left;
		}

		// 삭제하고자 하는 해당 루트노드가
		// 왼쪽 오른쪽 모두 서브트리가 존재한다면
		// 작은 값 중에서 가장 큰 값을 찾는다
		temp = findMinNode(root->left);

		root->item = temp->item;

		root->left = removeNodeFromTree(root->left, temp->item);
	}
	
	return root;
}

BSTNode * findNode(BSTNode * root, int value)
{	
	if (root == NULL)
	{
		return NULL;
	}

	if (root->item == value)
	{
		return root;
	}
	
	// 찾고자 하는 값이 루트 노드의 값보다 더 크다면 
	// 오른쪽 서브 트리를 탐색한다
	if (root->item < value)
	{
		return findNode(root->right, value);
	}

	// 찾고자 하는 값이 루트 노드의 값보다 더 작다면
	// 왼쪽 서브 트리를 탐색한다
	return findNode(root ->left, value);
}

BSTNode * findMinNode(BSTNode * root)
{	
	if (root->right == NULL)
	{
		return root;
	}

	return findMinNode(root->right);
}

///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
