#include <stdio.h>
#include <string.h>

struct StackNode {
	char data;
	struct StackNode *next;
};

typedef struct StackNode StackNode;
typedef StackNode * StackNodePtr;

void Push(StackNode *NodePtr, char letter){
	NodePtr->data = letter;
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

int main()
{
	StackNodePtr NodePtr, top, topPrint, topPrintFix, PostFix;
	NodePtr = malloc(sizeof(StackNode));
	top = NodePtr;
	topPrint = NodePtr;
	
	PostFix = malloc(sizeof(StackNode));
	topPrintFix = PostFix;
	
    int number;
    char data[50];
    
    FILE* txt = fopen( "infix_input.txt", "r" );
    fscanf(txt, "%s", & data );
    
    int t=0;
    int par=0;
    int pri;
    int last=0;
    while(1){
    	if(data[t] != 0){
    		printf("%c",data[t]);
    		if(data[t] == ')'){
    			par = t - par;
    			par= par - 2 ;
    			last++;
    			while(par != 0){
    				Push(PostFix, Pop(top, NodePtr));
					PostFix = PostFix->next;
					par--;
					last++;
				}
				//Pop(top, NodePtr);
				par=0;
	    		t++;
	    		continue;
			}
    		
    		else if(data[t] == '('){
    			pri = 5;
    			Push(NodePtr, data[t]);
				NodePtr = NodePtr->next;
	    		t++;
	    		last++;
    			par=t;
    			continue;
			}
			
			else if(data[t] =='*'){
    			pri = 4;
    			Push(NodePtr, data[t]);
				NodePtr = NodePtr->next;
	    		t++;
	    		continue;
			}
			
			else if(data[t] == '/'){
    			pri = 3;
    			Push(NodePtr, data[t]);
				NodePtr = NodePtr->next;
	    		t++;
	    		continue;
			}
			
			else if(data[t] == '+'){
    			pri = 2;
    			Push(NodePtr, data[t]);
				NodePtr = NodePtr->next;
	    		t++;
	    		continue;
			}
			
			else if(data[t] == '-'){
    			pri = 1;
    			Push(NodePtr, data[t]);
				NodePtr = NodePtr->next;
	    		t++;
	    		continue;
			}
			
			else{
				Push(PostFix, data[t]);
				PostFix = PostFix->next;
				last++;
	    		t++;
			}
    	}
    	else{
    		int a = (t-last);
    		if (a==1){
    			Push(PostFix, top->data);
				PostFix = PostFix->next;
			}
			else if(a>1){
				while(a!=0){
    			printf("%d\n", a);
    			Push(PostFix, Pop(top, NodePtr));
				PostFix = PostFix->next;
				a--;
				}
			}
    		break;
		}
	}
	printf("\n");
	printf("\n");
	
	//Pop(top, NodePtr);
	
	while(topPrint->next != NULL){
			printf("%c\n",topPrint->data);
			topPrint = topPrint->next;
	}
    printf("\n");
    while(topPrintFix->next != NULL){
			printf("%c",topPrintFix->data);
			topPrintFix = topPrintFix->next;
	}
	fclose(txt);	
	return 0;
}
