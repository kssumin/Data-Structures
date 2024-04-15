
//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024
///////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _QueueNode {
	BSTNode *data;
	struct _QueueNode *nextPtr;
}QueueNode; // You should not change the definition of QueueNode


typedef struct _queue
{
	QueueNode *head;
	QueueNode *tail;
}Queue; // You should not change the definition of queue

///////////////////////////////////////////////////////////////////////////////////

// You should not change the prototypes of these functions
void levelOrderTraversal(BSTNode *node);

void insertBSTNode(BSTNode **node, int value);

BSTNode* dequeue(QueueNode **head, QueueNode **tail);
void enqueue(QueueNode **head, QueueNode **tail, BSTNode *node);
int isEmpty(QueueNode *head);
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
	printf("2: Print the level-order traversal of the binary search tree;\n");
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
			printf("The resulting level-order traversal of the binary search tree is: ");
			levelOrderTraversal(root); // You need to code this function
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

// 요구사항 : 레벨별로 노드를 출력해야 한다.
void levelOrderTraversal(BSTNode* root)
{
	if (root == NULL)
    {
        return ;
	}

	Queue *queue = malloc(sizeof(Queue));
	queue->head = NULL;
	queue->tail =NULL;

	// 루트 노드의 값을 큐에 삽입한다
	enqueue(&(queue->head), &(queue->tail), root);

	// 큐에 값이 없을 때 종료한다.
	// 큐에 값이 없다는 것은 모든 노드를 탐색했다는 뜻이다.
	while (queue->head!=NULL)
	{	
		// 가장 앞 노드를 뺀다
		BSTNode* popItem = dequeue(&(queue->head), &(queue->tail));

		printf("%d ", popItem->item);

		// 가장 앞 노드의 왼쪽 노드가 존재한다면 왼쪽 노드를 넣는다.
		if (popItem->left!=NULL)
		{
			enqueue(&(queue->head), &(queue->tail), popItem->left);
		}

		// 가장 앞 노드의 오른쪽 노드가 존재한다면 오른쪽 노드를 넣는다.
		if (popItem->right!=NULL)
		{
			enqueue(&(queue->head), &(queue->tail), popItem->right);
		}
	}
	
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

// 가장 뒷 노드의 뒤에 새로운 노드를 삽입한다
void enqueue(QueueNode **headPtr, QueueNode **tailPtr, BSTNode *node)
{
	// dynamically allocate memory
	QueueNode *newPtr = malloc(sizeof(QueueNode));

	// if newPtr does not equal NULL
	if (newPtr != NULL) {
		newPtr->data = node;
		newPtr->nextPtr = NULL;

		// 큐가 비었다면 head에 새로운 노드를 삽입한다
		if (isEmpty(*headPtr)) {
			*headPtr = newPtr;
		}
		// 마지막 노드의 다음 노드에 새로운 노드를 삽입한다
		else {
			(*tailPtr)->nextPtr = newPtr;
		}

		// 마지막 노드를 새로운 노드로 변경한다
		*tailPtr = newPtr;
	}
	else {
		printf("Node not inserted");
	}
}

BSTNode* dequeue(QueueNode **headPtr, QueueNode **tailPtr)
{	
	// 가장 앞에 위치한 노드
	BSTNode *node = (*headPtr)->data;

	// 가장 앞에 위치한 노드를 제거한다
	QueueNode *tempPtr = *headPtr;

	// 가장 앞에 위치한 노드를 변경한다
	*headPtr = (*headPtr)->nextPtr;

	if (*headPtr == NULL) {
		*tailPtr = NULL;
	}

	// 제거한 가장 앞 노드의 메모리 할당을 해제한다
	free(tempPtr);

	return node;
}

int isEmpty(QueueNode *head)
{
	return head == NULL;
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
