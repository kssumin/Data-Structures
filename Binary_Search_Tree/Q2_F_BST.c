//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 2 */

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
void inOrderTraversal(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode *root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the in-order traversal of the binary search tree;\n");
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
			printf("The resulting in-order traversal of the binary search tree is: ");
			inOrderTraversal(root); // You need to code this function
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

void inOrderTraversal(BSTNode *root)
{	
	if(root == NULL)
	{
		return;
	}

	inOrderTraversal(root -> left);
	printf("%d ", root->item);
	inOrderTraversal(root ->right);
}

///////////////////////////////////////////////////////////////////////////////

// BST의 삽입은 leaf 노드에서 일어난다.
// 1. 탐색 시 루트노드보다 더 작은 값을 삽입하려고 하면 왼쪽 서브 트리로 이동한다.
// 2. 탐색 시 루트노드보다 더 큰 값을 삽입하려고 하면 오른쪽 서브 트리로 이동한다.
// 3. 동일한 값이 있을 시에 삽입하지 못 한다.
// 4. NULL인 곳에 값을 삽입한다.
void insertBSTNode(BSTNode **node, int value){

	// node는 현 서브 트리에서 루트 노드이다.
	// NULL이므로 값을 삽입한다.
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
		// 삽입하고자 하는 값이 더 작다면 왼쪽 서브 트리로 이동
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		// 삽입하고자 하는 값이 더 크다면 오른쪽 서브 트리로 이동
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}

		// 삽입하고자 하는 값이 존재한다면 삽입하지 못 한다.
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

	// stack에 삽입하고자 하는 노드
	temp->data = node;

	// 스택이 비어있다면
	if (stack->top == NULL)
	{	
		// 스택의 탑에 삽입하고자 하는 노드를 넣는다
		stack->top = temp;
		temp->next = NULL;
	}

	// 스택이 비어있지 않는다면
	else
	{	
		// 삽입하고자 하는 노드의 다음으로 스택의 탑을 넣는다.
		temp->next = stack->top;
		// 스택의 탑을 새로 삽입하는 노드로 변경한다
		stack->top = temp;
	}
}

BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	// 기존 스택의 탑
	t = s->top;

	// 스택의 탑이 존재한다면
	if (t != NULL)
	{	
		// 기존 스택의 탑 다음 노드
		temp = t->next;
		// 기존 스택의 값
		ptr = t->data;

		// 스택의 탑을 기존 스택의 탑 다음 노드로 변경한다
		s->top = temp;

		// 기존 스택의 탑의 메모리 할당을 해제한다
		free(t);
		t = NULL;
	}

	// 기존 스택의 값을 반환한다
	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;

	// 스택의 탑
	temp = s->top;
	if (temp != NULL)
		// 스택의 탑 데이터를 반환한다
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
		// 왼쪽 서브 트리로 이동한다
		removeAll(&((*node)->left));

		// 오른쪽 서브 트리로 이동한다
		removeAll(&((*node)->right));

		// 서브 트리의 루트 노드를 메모리 할당 해제한다
		free(*node);
		*node = NULL;
	}
}
