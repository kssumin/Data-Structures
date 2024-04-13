//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 5 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototype of this function
void frontBackSplitLinkedList(LinkedList* ll, LinkedList *resultFrontList, LinkedList *resultBackList);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *l);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	LinkedList ll;
	LinkedList resultFrontList, resultBackList;

	//Initialize the linked list as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	//Initialize the front linked list as an empty linked list
	resultFrontList.head = NULL;
	resultFrontList.size = 0;

	// Initialize the back linked list as an empty linked list
	resultBackList.head = NULL;
	resultBackList.size = 0;

	printf("1: Insert an integer to the linked list:\n");
	printf("2: Split the linked list into two linked lists, frontList and backList:\n");
	printf("0: Quit:\n");

	while (c != 0)
	{
	    printf("Please input your choice(1/2/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			insertNode(&ll, ll.size, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The resulting linked lists after splitting the given linked list are:\n");
			frontBackSplitLinkedList(&ll, &resultFrontList, &resultBackList); // You need to code this function
			printf("Front linked list: ");
			printList(&resultFrontList);
			printf("Back linked list: ");
			printList(&resultBackList);
			printf("\n");
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		case 0:
			removeAllItems(&ll);
			removeAllItems(&resultFrontList);
			removeAllItems(&resultBackList);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void frontBackSplitLinkedList(LinkedList *ll, LinkedList *resultFrontList, LinkedList *resultBackList)
{
	int size = ll->size;
	int midSize=0;

	// 절반으로 나누어 떨어진다면
	if (size%2==0)
	{
		midSize = size/2;
	}
	// 절반으로 나누어 떨어지지 않는다면
	else
	{
		midSize = size/2 +1;
	}
	

	ListNode *cur, *temp;

	if(ll ==NULL)
	{
		return;
	}

	if (resultFrontList == NULL || resultBackList ==NULL)
	{
		return;
	}

	cur = ll -> head;
	
	if(cur ==NULL)
	{
		return;
	}

	int frontSize = 0;

	while(frontSize < midSize)
	{
		// front 리스트에 노드를 추가한다
		insertNode(resultFrontList, frontSize, cur->item);

		// 다음 노드로 이동한다
		cur = cur -> next;

		// 해당 리스트의 사이즈를 늘린다
		frontSize +=1;
	}

	int backSize = 0;

	while(cur!=NULL)
	{	
		// front 리스트에 노드를 추가한다
		insertNode(resultBackList, backSize, cur->item);

		// 다음 노드로 이동한다
		cur = cur -> next;

		// 해당 리스트의 사이즈를 늘린다
		backSize +=1;
	}
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;
	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		// 다음 노드를 가리키도록 한다
		tmp = cur->next;

		// 해당 노드를 메모리 할당 해제한다
		free(cur);

		// 현 노드를 다음 노드이다
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	// 헤드를 가리키는 임시 노드
	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	// index는 찾고자 하는 노드의 인덱스
	while (index > 0){
		// 다음 노드를 가리키도록 한다
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// 삽입하고자 하는 노드가 첫 번째 노드이다
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		// 헤드를 가리킬 메모리를 할당한다
		ll->head = malloc(sizeof(ListNode));

		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}

	// Find the nodes before and at the target position
	// Create a new node and reconnect the links

	// 삽입하고자 하는 인덱스의 이전 노드를 찾는다
	if ((pre = findNode(ll, index - 1)) != NULL){
		// 삽입하고자 하는 인덱스에 있는 노드를 가리키는 포인터
		cur = pre->next;

		// 삽입하고자 하는 위치의 이전 노드가 가리키는 포인터에 메모리를 할당한다
		pre->next = malloc(sizeof(ListNode));

		// 값을 넣는다
		pre->next->item = value;
		// 기존에 있던 노드를 가리키도록 한다
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer

	// 첫 번째 노드인 경우
	if (index == 0){
		// 첫 번째 노드의 다음 노드
		cur = ll->head->next;

		// 첫 번째 노드를 메모리 해제시킨다
		free(ll->head);

		// 첫 번째를 첫 번째 노드의 다음 노드로 변경한다
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links

	// 제거하고자 하는 노드의 이전 노드를 찾는다
	if ((pre = findNode(ll, index - 1)) != NULL){

		// 찾고자 하는 노드가 없을 때 에러가 발생한다
		if (pre->next == NULL)
			return -1;

		// 제거하고자 하는 노드
		cur = pre->next;
		
		printf("%d\n", cur->item);

		// 이전 노드가 제거하고자 하는 노드의 다음 노드를 가리키도록 한다
		pre->next = cur->next;

		// 제거하고자 하는 노드의 메모리 할당을 해제한다
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
