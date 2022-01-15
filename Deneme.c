#include <stdio.h>
#include <string.h>

//Turgay Tumay 150119750
//Suleyman Burak Ozcan 150119742
//Ramazan Ozbolat 150119650

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

void Push_Basket(Customer *TopPtr, int customer_id, int id, int product_id, Product *NodePtr_Product){
	
	CustomerPtr NewCustomerPtr;
	NewCustomerPtr = TopPtr;
	
	while(1){
		if((NewCustomerPtr->id == customer_id && NewCustomerPtr->next_basket == NULL)){
			BasketPtr TempPtr;
			TempPtr = malloc(sizeof(Basket));
			NewCustomerPtr->next_basket = TempPtr;
			TempPtr->id = id;
			TempPtr->next_basket = NULL;
			NodePtr_Product->next = NULL;
			TempPtr->next_product = NodePtr_Product;
			break;	
		}
		else if(NewCustomerPtr->id == customer_id && NewCustomerPtr->next_basket != NULL){
			if(NewCustomerPtr->next_basket->id != id){
				BasketPtr TempPtr;
				TempPtr = malloc(sizeof(Basket));
				TempPtr->id = id;
				NodePtr_Product->next = NULL;
				TempPtr->next_product = NodePtr_Product;
				TempPtr->next_basket = NewCustomerPtr->next_basket;
				NewCustomerPtr->next_basket = TempPtr;
				break;
			}
			else if(NewCustomerPtr->next_basket->id == id){
				NodePtr_Product->next = NewCustomerPtr->next_basket->next_product;
				NewCustomerPtr->next_basket->next_product = NodePtr_Product;
				break;
			}
		}
		else if(NewCustomerPtr->id != customer_id){
			NewCustomerPtr = NewCustomerPtr->next_customer;
			continue;
		}
	}
}

void PrintAll(Customer *TopPtr){
	CustomerPtr ShowCustomerPtr;
	BasketPtr ShowBasketPtr;
	ProductPtr ShowProductPtr;
	ShowCustomerPtr = TopPtr;
	
	while(ShowCustomerPtr->next_customer != NULL){
		ShowBasketPtr = ShowCustomerPtr->next_basket;
			printf("%d, %s, %s\n",ShowCustomerPtr->id, ShowCustomerPtr->name, ShowCustomerPtr->surname);
			while(ShowBasketPtr != NULL){
				ShowProductPtr = ShowBasketPtr->next_product;
				printf("	%d\n",ShowBasketPtr->id);
				while(ShowProductPtr != NULL){
					printf("		%s\n",ShowProductPtr->name);
					ShowProductPtr = ShowProductPtr->next;
				}
				ShowBasketPtr = ShowBasketPtr->next_basket;
			}
			ShowCustomerPtr = ShowCustomerPtr->next_customer;
	}
}

void PrintCustomers(Customer *TopPtr){
	CustomerPtr ShowCustomerPtr;
	ShowCustomerPtr = TopPtr;
	
	while(ShowCustomerPtr->next_customer != NULL){
			printf("%d, %s, %s\n",ShowCustomerPtr->id, ShowCustomerPtr->name, ShowCustomerPtr->surname);
			ShowCustomerPtr = ShowCustomerPtr->next_customer;
	}
}

int CheckCustomers(Customer *TopPtr, char *new_name){
	CustomerPtr ShowCustomerPtr;
	ShowCustomerPtr = TopPtr;
	
	while(ShowCustomerPtr->next_customer != NULL){
		if(strcmp(ShowCustomerPtr->name, new_name) == 0){
			printf("There is a Customer which has same name\n");
			return 0;
		}
		ShowCustomerPtr = ShowCustomerPtr->next_customer;
	}
	return 1;
}

int TakeCustomerId(Customer *TopPtr){
	CustomerPtr ShowCustomerPtr;
	ShowCustomerPtr = TopPtr;
	int new_id;
	while(ShowCustomerPtr->next_customer->next_customer != NULL){
			ShowCustomerPtr = ShowCustomerPtr->next_customer;
	}
	new_id = ShowCustomerPtr->id;
	return new_id;
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
			ProductPtr NodePtr_Product;
			NodePtr_Product = malloc(sizeof(Product));
    		product_id_basket = atoi(data_basket);
    		
    		while(1){
    			char data_product[50];
	
				int id_product;
			    char name_product[50];
			    char category_product[50];
			    int price;
			    int count = 1;
			    
				FILE* txt_product = fopen( "product.txt", "r" );
				    while ( fscanf(txt_product, "%s", & data_product ) == 1 ) 
				    {	
						if(count == 1){
				    		id_product = atoi(data_product);
				    		count = count + 1;
				    		continue;
						}
						else if(count == 2){
							strcpy(name_product, data_product);
							count = count + 1;
				    		continue;
						}
						else if(count == 3){
							strcpy(category_product, data_product);
							count = count + 1;
				    		continue;
						}
						else if(count == 4){
				    		price = atoi(data_product);
				    		if(id_product != product_id_basket){
				    			count = 1;
				    			continue;	
							}
							else if(id_product == product_id_basket){
								count = 5;
				    			break;
							}
						}
						else if(count == 5){
							break;	
						} 	
					}
				NodePtr_Product->id = id_product;
				strcpy(NodePtr_Product->name, name_product);
				strcpy(NodePtr_Product->category, category_product);
				NodePtr_Product->price = price;
				fclose(txt_product);
				break;
			}
    		Push_Basket(top_customer, customer_id_basket, id_basket, product_id_basket, NodePtr_Product);
			count = 1;
			if(tempint == 1){
				tempint = tempint - 1;
			}
    		continue;
		}	
	}
	
	//PrintAll(top_customer);
	
	while(1){
		
		int choice;
		printf("\n");
        printf("Main Menu options:\n  1- Add a customer\n  2- Add basket\n  3- Remove customer\n  4- List the customers who bought a specific product\n  5- List the total shopping amounts of each customer\n  6-Exit\n"); 
        puts("Choose an option: ");
        scanf("%d", &choice);
        if (choice == 1){
        	printf("\n");
        	PrintCustomers(top_customer);
        	char new_name[50];
            puts("Enter the name of new customer: ");
            scanf("%s", &new_name);
            char new_surname[50];
            puts("Enter the surname of new customer: ");
        	scanf("%s", &new_surname);
        	printf("\n");
        	if(CheckCustomers(top_customer, new_name) == 0){
        		printf("There is a Customer who has the same name\n");
			}
			else{
				int new_id;
				Push_Customer(NodePtr_Customer, (TakeCustomerId(top_customer) + 1), new_name, new_surname);
				PrintCustomers(top_customer);
			}
        	continue;
        }
        else if (choice == 2){
            PrintCustomers(top_customer);
            printf("\n");
            int customer_idselection;
            puts("Enter a valid id from the list to choose customer: ");
            scanf("%d", &customer_idselection);
            
            while(1){
    			char data_product[50];
	
				int id_product;
			    char name_product[50];
			    char category_product[50];
			    int price;
			    int count = 1;
			    
			    printf("\n");
				FILE* txt_product = fopen( "product.txt", "r" );
				while ( fscanf(txt_product, "%s", & data_product ) == 1 ) 
				{	
					if(count == 1){
				    	id_product = atoi(data_product);
				    	count = count + 1;
				    	continue;
					}
					else if(count == 2){
						strcpy(name_product, data_product);
						count = count + 1;
				    	continue;
					}
					else if(count == 3){
						strcpy(category_product, data_product);
						count = count + 1;
				    	continue;
					}
					else if(count == 4){
				    	price = atoi(data_product);
				    	printf("%d	%s	%s	%d\n", id_product, name_product, category_product, price);
				    	count = 1;
				    	continue;
					}	
				}
				fclose(txt_product);
				break;
			}
            
            int product_idselection = 0;
            while (1){
                puts("Enter a valid id from the list to choose product or enter '-1' to complete shopping: ");
                scanf("%d", &product_idselection);
                if (product_idselection != -1){
                	ProductPtr NodePtr_Product;
					NodePtr_Product = malloc(sizeof(Product));
		    		product_id_basket = atoi(data_basket);
    		
	                while(1){
	    			char data_product[50];
		
					int id_product;
				    char name_product[50];
				    char category_product[50];
				    int price;
				    int count = 1;
				    
					FILE* txt_product = fopen( "product.txt", "r" );
					    while ( fscanf(txt_product, "%s", & data_product ) == 1 ) 
					    {	
							if(count == 1){
					    		id_product = atoi(data_product);
					    		count = count + 1;
					    		continue;
							}
							else if(count == 2){
								strcpy(name_product, data_product);
								count = count + 1;
					    		continue;
							}
							else if(count == 3){
								strcpy(category_product, data_product);
								count = count + 1;
					    		continue;
							}
							else if(count == 4){
					    		price = atoi(data_product);
					    		if(id_product != product_idselection){
					    			count = 1;
					    			continue;	
								}
								else if(id_product == product_idselection){
									count = 5;
					    			break;
								}
							}
							else if(count == 5){
								break;	
							} 	
						}
					NodePtr_Product->id = id_product;
					strcpy(NodePtr_Product->name, name_product);
					strcpy(NodePtr_Product->category, category_product);
					NodePtr_Product->price = price;
					fclose(txt_product);
					
					Push_Basket(top_customer, customer_idselection, 4, product_idselection, NodePtr_Product);
					break;
					}
                    }
                else if (product_idselection  ==  -1){
                	PrintAll(top_customer);
                    break;
                    }
            	}
            continue;
                               
        }
        else if (choice == 3){
            PrintCustomers(top_customer);
            printf("\n");
            char new_name[20];
            puts("Enter the name of new customer: ");
            scanf("%s", &new_name);
            char new_surname[20];
            puts("Enter the surname of new customer: ");
        	scanf("%s", &new_surname);
        	
        	CustomerPtr temp_customer, temp_customer_2;
        	temp_customer = top_customer;
        	
        	while(temp_customer->next_customer != NULL){
        		if(strcmp(temp_customer->next_customer->name, new_name) == 0 && strcmp(temp_customer->next_customer->surname, new_surname) == 0){
        			CustomerPtr temp_top_customer;
        			temp_top_customer = temp_customer->next_customer->next_customer;
					temp_customer->next_customer = temp_customer->next_customer->next_customer;
        			break;
				}
				else if(strcmp(temp_customer->name, new_name) == 0 && strcmp(temp_customer->surname, new_surname) == 0){
        			temp_customer = temp_customer->next_customer;
        			break;
				}
				temp_customer = temp_customer->next_customer;
			}
			temp_customer_2 = top_customer;
			int id_count = 1;
			while(temp_customer_2->next_customer != NULL){
				temp_customer_2->id = id_count;
				id_count = id_count + 1;
				temp_customer_2 = temp_customer_2->next_customer;
			}
			
			printf("\n");
			PrintCustomers(top_customer);
            printf("\n");
				
            continue;
        }
        else if (choice == 4){
        	
        	while(1){
    			char data_product[50];
	
				int id_product;
			    char name_product[50];
			    char category_product[50];
			    int price;
			    int count = 1;
			    
			    printf("\n");
				FILE* txt_product = fopen( "product.txt", "r" );
				while ( fscanf(txt_product, "%s", & data_product ) == 1 ) 
				{	
					if(count == 1){
				    	id_product = atoi(data_product);
				    	count = count + 1;
				    	continue;
					}
					else if(count == 2){
						strcpy(name_product, data_product);
						count = count + 1;
				    	continue;
					}
					else if(count == 3){
						strcpy(category_product, data_product);
						count = count + 1;
				    	continue;
					}
					else if(count == 4){
				    	price = atoi(data_product);
				    	printf("%d	%s	%s	%d\n", id_product, name_product, category_product, price);
				    	count = 1;
				    	continue;
					}	
				}
				fclose(txt_product);
				break;
			}
            int product_idselection = 0;
            puts("Enter a valid id from the list to choose product: ");
            scanf("%d", &product_idselection);
            printf("\n");
            
            CustomerPtr ShowCustomerPtr;
			BasketPtr ShowBasketPtr;
			ProductPtr ShowProductPtr;
			ShowCustomerPtr = top_customer;
			
			while(ShowCustomerPtr->next_customer != NULL){
				ShowBasketPtr = ShowCustomerPtr->next_basket;
					while(ShowBasketPtr != NULL){
						ShowProductPtr = ShowBasketPtr->next_product;
						while(ShowProductPtr != NULL){
							if(ShowProductPtr->id == product_idselection){
								printf("%d, %s, %s\n",ShowCustomerPtr->id, ShowCustomerPtr->name, ShowCustomerPtr->surname);
							}
							ShowProductPtr = ShowProductPtr->next;
						}
						ShowBasketPtr = ShowBasketPtr->next_basket;
					}
					ShowCustomerPtr = ShowCustomerPtr->next_customer;
			}
            continue;
        }
        else if (choice == 5){
        	int amount = 0;
        	CustomerPtr ShowCustomerPtr;
			BasketPtr ShowBasketPtr;
			ProductPtr ShowProductPtr;
			ShowCustomerPtr = top_customer;
        	
        	while(ShowCustomerPtr->next_customer != NULL){
				ShowBasketPtr = ShowCustomerPtr->next_basket;
				printf("%d, %s, %s\n",ShowCustomerPtr->id, ShowCustomerPtr->name, ShowCustomerPtr->surname);
				while(ShowBasketPtr != NULL){
					ShowProductPtr = ShowBasketPtr->next_product;
					while(ShowProductPtr != NULL){
						amount = amount + ShowProductPtr->price;
						ShowProductPtr = ShowProductPtr->next;
					}
					ShowBasketPtr = ShowBasketPtr->next_basket;
				}
				printf("		%d\n",amount);
				amount = 0;
				ShowCustomerPtr = ShowCustomerPtr->next_customer;
			}
            continue;
        }
		else if(choice == 6){
			break;
		}
	}
	
	
	
    printf("\n");
	fclose(txt_customer);
	fclose(txt_basket);
	return 0;
}
