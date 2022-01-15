#include <stdio.h>
#include <string.h>

struct StackNode {
	int data;
	struct StackNode *next;
};

typedef struct StackNode StackNode;
typedef StackNode * StackNodePtr;

	
void Push(StackNode *NodePtr, int data){
	NodePtr->data = data;
	NodePtr->next = malloc(sizeof(StackNode));
	NodePtr->next->next = NULL;
	NodePtr->next->data = NULL;
}

char Pop(StackNode *TopPtr, StackNode *NodePtr) {
	char temp;
	StackNodePtr NewNodePtr;
	NewNodePtr = TopPtr;
	while(NewNodePtr->next->next != NodePtr || NewNodePtr->next == NodePtr){
		NewNodePtr = NewNodePtr->next;
	}
	//free(NewNodePtr->next);
	if(NewNodePtr->next->data != NULL){
		temp = NewNodePtr->next->data;
		NewNodePtr->next = NodePtr;
	}
	else if(NewNodePtr->next->data == NULL){
		temp = NewNodePtr->data;
		NewNodePtr = NodePtr;
	}
	return temp;
}

void Print(StackNode *head) {
    StackNode *current_node = head;
   	while(current_node->next != NULL){
			printf("%d\n",current_node->data);
			current_node = current_node->next;
	}
}

int main()
{
	StackNodePtr NodePtr, top;
	NodePtr = malloc(sizeof(StackNode));
	top = NodePtr;
	
    int number;
    int t = 0;
    
    FILE* txt = fopen( "input.txt", "r" );
    while ( fscanf(txt, "%d", & number ) == 1 ) 
    {   
    	Push(NodePtr, number);
		NodePtr = NodePtr->next;
	}
	
	Pop(top, NodePtr);
	Pop(top, NodePtr);
	Pop(top, NodePtr);
	Pop(top, NodePtr);
	Pop(top, NodePtr);
	
	
	printf("\n");
	
	Print(top);
	
	
    printf("\n");
	fclose(txt);	
	return 0;
}
