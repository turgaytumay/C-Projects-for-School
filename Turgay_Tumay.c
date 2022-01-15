#include <stdio.h>
#include <string.h>

struct node
{
    //char word; //node will store an char
   	char  *word;
    struct node *right_child; // right child
    struct node *left_child; // left child
};

//function to create a node
struct node* new_node(char *word)
{
    struct node *p;
    p=(struct node *)malloc(sizeof(struct node));
    //p = malloc(50);
    p->word = word;
    p->left_child = NULL;
    p->right_child = NULL;

    return p;
}

struct node* insert(struct node *root, char *word)
{
	//printf("%s %s\n", word, root->word);
    //searching for the place to insert
    if(root==NULL){
        return new_node(word);
	}
    else if(getindex(word)>getindex(root->word)) 
        root->right_child = insert(root->right_child, word);
    else if(getindex(word)<getindex(root->word)) 
       	root->left_child = insert(root->left_child, word);
    return root;
}

void inorder(struct node *root)
{
    if(root!=NULL) // checking if the root is not null
    {
        inorder(root->left_child); 
        printf(" %s ", root->word); 
        inorder(root->right_child);
    }
}

int getindex(char *letter);

int main()
{
	FILE *txt;
    char data[50];
    char *token;
    
    char word[50];
    
    int number;
    
    txt = fopen( "input.txt", "r" );
    struct node *root;
    root=(struct node *)malloc(sizeof(struct node));
    while( fgets ( data, 50, txt ) != NULL )
    {
    	char *token  = strtok(data, ",");
    	token = strtok(NULL, ",");
    	strcpy(word, token);
    	
    	if (number == 0){
    		root = new_node(word);
    		number = 1;
    		continue;
		}
		else{
			insert(root, word);
			continue;
		}
	}
	inorder(root);
    printf("\n");
	fclose(txt);	
	return 0;
}

int getindex(char *letter){
	int i = 0;
	if(letter != NULL){
		i += letter[0];
		return i;
	}
	else
		i = 0;
	return i;
}

/*

#include <stdio.h>
#include <string.h>
struct node
{
    //int frequency; //node will store an integer
   	int  frequency;
    struct node *right_child; // right child
    struct node *left_child; // left child
};

//function to create a node
struct node* new_node(int freq)
{
    struct node *p;
    p = malloc(50);
    p->frequency = freq;
    p->left_child = NULL;
    p->right_child = NULL;

    return p;
}

struct node* insert(struct node *root, int freq)
{
    //searching for the place to insert
    if(root==NULL)
        return new_node(freq);
    else if(freq>root->frequency) // x is greater. Should be inserted to right
        root->right_child = insert(root->right_child, freq);
    else // x is smaller should be inserted to left
        root->left_child = insert(root->left_child, freq);
    return root;
}

void inorder(struct node *root)
{
    if(root!=NULL) // checking if the root is not null
    {
        inorder(root->left_child); // visiting left child
        printf(" %d ", root->frequency); // printing data at root
        inorder(root->right_child);// visiting right child
    }
}

int main()
{
	FILE *txt;
    char data[50];
    char *token;
    
    int order;
    char word[50];
    int frequency;
    
    int number = 0;
    // geting data from txt
    txt = fopen( "input.txt", "r" );
    struct node *root;
    while( fgets ( data, 50, txt ) != NULL )
    {
    	char * token  = strtok(data, ",");
    	token = strtok(NULL, ",");
    	token = strtok(NULL, ",");
    	sscanf(token, "%d", &frequency);// geting frequency info from txt data which just separated
    	
    	if (number == 0){
    		root = new_node(frequency);
    		number += 1;
		}
		else{
			insert(root, frequency);
		}
	}
	inorder(root);
    printf("\n");
    fclose( txt );	
	return 0;
}

*/



