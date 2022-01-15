#include <stdio.h>
#include <string.h>

struct Product {
	int id;
	char name[50];
	char category[50];
	int price;
	struct Product *next;
};

typedef struct Product Product;
typedef Product * ProductPtr;

struct Basket {
	int id;
	int amount;
	struct Product *next_product;
	struct Basket *next_basket;
};

typedef struct Basket Basket;
typedef Basket * BasketPtr;

struct Customer {
	int id;
	char name[50];
	char surname[50];
	struct Basket *next_basket;
	struct Customer *next_customer;
};

typedef struct Customer Customer;
typedef Customer * CustomerPtr;

	
void Push_Customer(Customer *NodePtr, int id, char *name, char *surname){
	NodePtr->id = id;
	strcpy(NodePtr->name, name);
	strcpy(NodePtr->surname, surname);
	NodePtr->next_customer = malloc(sizeof(Customer));
	NodePtr->next_customer->next_customer = NULL;
	NodePtr->next_basket = NULL;
}

void Push_Basket(Customer *TopPtr, int customer_id, int id, int product_id){
	
	CustomerPtr NewCustomerPtr;
	NewCustomerPtr = TopPtr;
	//printf("%d", NewBasketPtr->id);
	//printf("%d, %d, %d\n", customer_id, id, product_id);
	
	while(1){
		if((NewCustomerPtr->id == customer_id && NewCustomerPtr->next_basket == NULL)){
			BasketPtr TempPtr;
			TempPtr = malloc(sizeof(Basket));
			NewCustomerPtr->next_basket = TempPtr;
			TempPtr->id = id;
			TempPtr->next_basket = NULL;
			TempPtr->next_product = NULL;
			break;	
		}
		else if(NewCustomerPtr->id == customer_id && NewCustomerPtr->next_basket != NULL){
			if(NewCustomerPtr->next_basket->id != id){
				BasketPtr TempPtr;
				TempPtr = malloc(sizeof(Basket));
				TempPtr->id = id;
				TempPtr->next_basket = NULL;
				TempPtr->next_product = NULL;
				TempPtr->next_basket = NewCustomerPtr->next_basket;
				NewCustomerPtr->next_basket = TempPtr;
			}
			break;
		}
		else if(NewCustomerPtr->id != customer_id){
			NewCustomerPtr = NewCustomerPtr->next_customer;
			continue;
		}
	}
}

int main()
{
	CustomerPtr NodePtr_Customer, top_customer;
	NodePtr_Customer = malloc(sizeof(Customer));
	top_customer = NodePtr_Customer;
	
	char data_customer[50];
	
	int id_customer;
    char name_customer[50];
    char surname_customer[50];
    int count = 1;
    
    FILE* txt_customer = fopen( "customer.txt", "r" );
    while ( fscanf(txt_customer, "%s", & data_customer ) == 1 ) 
    {
    	if(count == 1){
    		id_customer = atoi(data_customer);
    		count = count + 1;
    		continue;
		}
		else if(count == 2){
			strcpy(name_customer, data_customer);
			count = count + 1;
    		continue;
		}
		else if(count == 3){
    		strcpy(surname_customer, data_customer);
    		Push_Customer(NodePtr_Customer, id_customer, name_customer, surname_customer);
			NodePtr_Customer = NodePtr_Customer->next_customer;
			count = 1;
    		continue;
		}	
	}
	
	BasketPtr NodePtr_Basket;
	//NodePtr_Basket = malloc(sizeof(Basket));
	
	char data_basket[50];
	
	int customer_id_basket, id_basket, product_id_basket;
	int tempint = 1;
	
	FILE* txt_basket = fopen( "basket.txt", "r" );
    while ( fscanf(txt_basket, "%s", & data_basket ) == 1 ) 
    {
    	if(count == 1){
    		customer_id_basket = atoi(data_basket);
    		customer_id_basket = customer_id_basket + tempint;
    		count = count + 1;
    		continue;
		}
		else if(count == 2){
			id_basket = atoi(data_basket);
			count = count + 1;
    		continue;
		}
		else if(count == 3){
    		product_id_basket = atoi(data_basket);
    		Push_Basket(top_customer, customer_id_basket, id_basket, product_id_basket);
			count = 1;
			if(tempint == 1){
				tempint = tempint - 1;
			}
    		continue;
		}	
	}
	
	printf("\n");
	while(top_customer->next_customer != NULL){
			printf("%d, %s, %s\n",top_customer->id, top_customer->name, top_customer->surname);
			while(top_customer->next_basket != NULL){
				printf("	%d\n",top_customer->next_basket->id);
				top_customer->next_basket = top_customer->next_basket->next_basket;
			}
			top_customer = top_customer->next_customer;
	}
	
    printf("\n");
	fclose(txt_customer);
	fclose(txt_basket);
	return 0;
}
