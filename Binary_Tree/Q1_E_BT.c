//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////
typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode{
    BTNode *btnode;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
    StackNode *top;
}Stack;

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int identical(BTNode *tree1, BTNode *tree2);

BTNode* createBTNode(int item);

BTNode* createTree();
void push( Stack *stk, BTNode *node);
BTNode* pop(Stack *stk);

void printTree(BTNode *node);
void removeAll(BTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    int c, s;
    char e;
    BTNode *root1, *root2;

    root1 = NULL;
    root2 = NULL;
    c = 1;

    printf("1: Create a binary tree1.\n");
    printf("2: Create a binary tree2.\n");
    printf("3: Check whether two trees are structurally identical.\n");
    printf("0: Quit;\n");

    while(c != 0){
        printf("Please input your choice(1/2/3/0): ");
        if(scanf("%d", &c) > 0)

        {

            switch(c)
            {
            case 1:
                removeAll(&root1);
                printf("Creating tree1:\n");
                root1 = createTree();
                printf("The resulting tree1 is: ");
                printTree(root1);
                printf("\n");
                break;
            case 2:
                removeAll(&root2);
                printf("Creating tree2:\n");
                root2 = createTree();
                printf("The resulting tree2 is: ");
                printTree(root2);
                printf("\n");
                break;
            case 3:
                s = identical(root1, root2);
                if(s){
                printf("Both trees are structurally identical.\n");
                }
                else{
                printf("Both trees are different.\n");
                }
                removeAll(&root1);
                removeAll(&root2);
                break;
            case 0:
                removeAll(&root1);
                removeAll(&root2);
                break;
            default:
                printf("Choice unknown;\n");
                break;
            }
		}
        else
        {
            scanf("%c",&e);
        }

    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int identical(BTNode *tree1, BTNode *tree2)
{   
    // 트리가 둘 두 비어있는 경우 -> 구조적으로 동일하다
    if (tree1 == NULL && tree2 == NULL)
        return 1;
    
    // 트리의 한 쪽만 비어있는 경우 -> 구조적으로 동일하지 않다
    if (tree1 == NULL || tree2 == NULL)
        return 0;
    
    // 값이 같지 않다면 -> 구조적으로 동일하지 않다
    if (tree1->item != tree2->item)
        return 0;
    
    // 왼쪽 노드의 값을 탐색한다
    identical(tree1 -> left, tree2 -> left);
    identical(tree1 -> right, tree2 -> right);
}

/////////////////////////////////////////////////////////////////////////////////

// 이진 트리 노드를 생성한다
// 값을 넣고 왼쪽 트리와 오른쪽 트리에는 아무런 노드가 없다
BTNode *createBTNode(int item){
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//////////////////////////////////////////////////////////////////////////////////


// 이진 트리를 생성한다
BTNode *createTree()
{
    Stack stk;
    BTNode *root, *temp;
    char s;
    int item;

    // 이진 트리의 루트 노드 값 초기화
    stk.top = NULL;
    root = NULL;

    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    printf("Enter an integer value for the root: ");

    // 이진 트리의 루트 노드에 삽입하고자 하는 숫자
    if(scanf("%d",&item) > 0)
    {   
        // 루트 노드를 생성한다
        root = createBTNode(item);

        // 이진 트리의 루트 노드로 삽입한다
        push(&stk,root);
    }
    else
    {
        scanf("%c",&s);
    }

    // 스택에 값이 있을 동안
    while((temp =pop(&stk)) != NULL)
    {

        printf("Enter an integer value for the Left child of %d: ", temp->item);

        if(scanf("%d",&item)> 0)
        {
            temp->left = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        printf("Enter an integer value for the Right child of %d: ", temp->item);
        if(scanf("%d",&item)>0)
        {
            temp->right = createBTNode(item);
        }
        else
        {
            scanf("%c",&s);
        }

        if(temp->right != NULL)
            push(&stk,temp->right);
        if(temp->left != NULL)
            push(&stk,temp->left);
    }
    return root;
}

void push( Stack *stk, BTNode *node){
    StackNode *temp;

    temp = malloc(sizeof(StackNode));
    if(temp == NULL)
        return;
    temp->btnode = node;

    // 다른 최상위 노드가 존재하지 않는다면
    if(stk->top == NULL){
        // 최상위 노드로 설정한다
        stk->top = temp;
        temp->next = NULL;
    }

    // 다른 최상위 노드가 존재한다면
    else{
        // 삽입하고자 하는 노드의 다음 노드로 최상위 노드로 설정한다
        temp->next = stk->top;

        // 최상위 노드를 현 삽입하고자 하는 노드로 설정한다
        stk->top = temp;
    }
}

// 최상위 노드를 삭제한다
BTNode* pop(Stack *stk){
   StackNode *temp, *top;
   BTNode *ptr;
   ptr = NULL;

   top = stk->top;

    // 최상위 노드가 존재한다면
   if(top != NULL){

        // 최상위 노드의 다음 노드
        temp = top->next;
        // 최상위 노드
        ptr = top->btnode;

        // 최상위 노드를 최상위 노드의 다음 노드로 설정한다
        stk->top = temp;

        // 기존의 최상위 노드 메모리 할당 해제
        free(top);
        top = NULL;
   }

   // 기존의 최상위 노드를 반환
   return ptr;
}

void printTree(BTNode *node){
    if(node == NULL) return;

    // 가장 왼쪽 노드로 이동한다
    printTree(node->left);

    // 값을 출력한다
    printf("%d ",node->item);

    // 해당 노드의 오른쪽을 탐색한다
    printTree(node->right);
}


void removeAll(BTNode **node){
    if(*node != NULL){
        removeAll(&((*node)->left));
        removeAll(&((*node)->right));
        free(*node);
        *node = NULL;
    }
}
