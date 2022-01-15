#include <stdio.h>
#include <string.h>

struct StackNode {
	int id;
	char name[50];
	char category[50];
	int price;
	struct StackNode *next;
};

typedef struct StackNode StackNode;
typedef StackNode * StackNodePtr;

	
int Push(StackNode *TopPtr ,StackNode *NodePtr , int id, char *name, char *category, int price){
	int a;
	StackNodePtr NewNodePtr, TempPtr;
	NewNodePtr = TopPtr;
	while(1){
		if(NewNodePtr->name == NodePtr->name){
			a = 1;
			NodePtr->id = id;
			strcpy(NodePtr->name, name);
			strcpy(NodePtr->category, category);
			NodePtr->price = price;
			
			NodePtr->next = malloc(sizeof(StackNode));
			NodePtr->next->next = NULL;
			return a;
		}
		else if(NewNodePtr->name[0] > name[0] && NewNodePtr == TopPtr){
			a = 0;
			TempPtr = malloc(sizeof(StackNode));
			
			TempPtr->id = TopPtr->id;
			strcpy(TempPtr->name, TopPtr->name);
			strcpy(TempPtr->category, TopPtr->category);
			TempPtr->price = TopPtr->price;
			
			TopPtr->id = id;
			strcpy(TopPtr->name, name);
			strcpy(TopPtr->category, category);
			TopPtr->price = price;
			
			TempPtr->next = NewNodePtr->next;
			NewNodePtr->next = TempPtr;
			return a;
		}
		else if(NewNodePtr->next->name[0] > name[0]){
			a = 0;
			TempPtr = malloc(sizeof(StackNode));
			
			TempPtr->id = id;
			strcpy(TempPtr->name, name);
			strcpy(TempPtr->category, category);
			TempPtr->price = price;
			
			TempPtr->next = NewNodePtr->next;
			NewNodePtr->next = TempPtr;
			return a;
		}
		else if(NewNodePtr->name[0] < name[0]){
			NewNodePtr = NewNodePtr->next;
			continue;
		}
		else{
			NewNodePtr = NewNodePtr->next;
			continue;
		}
	}
}

int main()
{
	StackNodePtr NodePtr, top;
	NodePtr = malloc(sizeof(StackNode));
	top = NodePtr;
	
	char data[50];
	
	int id;
	int price;
    char name[50];
    char category[50];
    
    int count = 1;
    
    FILE* txt = fopen( "product_deneme.txt", "r" );
    while ( fscanf(txt, "%s", & data ) == 1 ) 
    {   
    	if(count == 1){
    		id = atoi(data);
    		//printf("%d\n", id);
    		count = count + 1;
    		continue;
		}
		else if(count == 2){
			//printf("%s\n", data);
			strcpy(name, data);
			count = count + 1;
    		continue;
		}
		else if(count == 3){
			//printf("%s\n", data);
			strcpy(category, data);
			count = count + 1;
    		continue;
		}
		else if(count == 4){
    		price = atoi(data);
    		//printf("%d\n", price);
    		if(Push(top, NodePtr, id, name, category, price) == 1){
    			NodePtr = NodePtr->next;
			}
			memset(name, 0, sizeof(name));
			memset(category, 0, sizeof(category));
			count = 1;
    		continue;
		}	
	}
	
	printf("\n");
	while(top->next != NULL){
			printf("%d, %s, %s, %d\n",top->id, top->name, top->category, top->price);
			top = top->next;
	}
	
    printf("\n");
	fclose(txt);	
	return 0;
}
