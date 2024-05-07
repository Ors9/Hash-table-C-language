#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_TABLE_SIZE 29

/* Structure representing each element in the hash table */
typedef struct Node{ /* Represents each element in the hash table */
    int quantity;/* quantity the element occurs  */
    char *filename;/* Filename associated with the element */
    struct Node *next;/* Pointer to the next node in case of collision */
}Node;

/* Array of pointers to Node structures representing the hash table */
typedef Node *HashTable[HASH_TABLE_SIZE]; 

/*Function to create new node and initialize*/
Node * New_Node(){
    Node *new_node = calloc(1,sizeof(Node));
    if(new_node == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    } 
    /*Initialize new Node*/
    new_node->quantity = 0;
    new_node->filename = NULL;
    new_node->next = NULL;
    return new_node;
}/*End of New_node function*/

/* Function to create a new list where each node is initialized */
Node * NodeList(int argc){
    int i;
    Node *head = New_Node();
    Node *current = head;
    /* Connect every initialized node in the list */
    for(i = 0 ; i < argc ; i++){
        current->next = New_Node();
        current = current->next;
    }
    return head;
}/*End of NodeList function*/

/*Function to create the hash table*/
HashTable * create_hash_table(int argc){
    int i;
    HashTable *ptr = calloc(1 , sizeof(HashTable));
    if(ptr == NULL){
        printf("Memory allocation failed\n");
        exit(1);    
    }
    /*Initialize each element of the hash table*/
    for(i = 0 ; i < HASH_TABLE_SIZE ; i++){
        (*ptr)[i] = NodeList(argc);
    }
    return ptr;
} /*End of create_hash_table function*/

/* Function to print the hash table */
void print_hash_table(HashTable * ptr){
    int  i,flag = 0; /* The flag indicates if we already printed that number appears in a file */
    Node * temp = NULL;
    for(i = 0 ;i < HASH_TABLE_SIZE ; i++){
        temp = (*ptr)[i];
        while(temp != NULL){
            if(temp->filename != NULL){
                if(flag == 0){
                    printf("%d appear in file " , i);
                }/*case time*/
                if(temp->quantity <= 1){
                    printf("%s - %d time",temp->filename,temp->quantity);  
                    flag++;
                }/*case times*/
                else if(temp->quantity > 1){
                    printf("%s - %d times",temp->filename,temp->quantity);  
                    flag++;
                }/*Case more left to print add comma*/
                if(temp->next != NULL && temp->next->filename != NULL){
                    printf(", ");
                }
            }  
            temp = temp->next;
        }/*End of while*/
        if(flag != 0){
            printf("\n");
        }
        flag = 0;
    }/*End of for*/

    return;
}/*End of print_hash_table function*/

void insert_to_hash_table(HashTable *ptr ,int number , char *filename){
    Node * curr = (*ptr)[number];
    while(curr != NULL){
        /*Check if there already place where the file name used*/
        if(curr->filename != NULL && strcmp(curr->filename, filename) == 0){
            curr->quantity++;
            break;
        }
        /*If the name is not in use yet*/
        else if(curr->quantity == 0){
            curr->quantity++;
            curr->filename = filename;
            break;
        }
        curr = curr->next;
    }
    return;
}/*End of insert_to_hash_table function*/

/*Function to free all memory allocated for the hash table*/
void free_hash_table(HashTable *ptr){
    int i;
    Node *temp = NULL;
    Node *next = NULL;
    for(i = 0 ; i < HASH_TABLE_SIZE ; i++){
        temp = (*ptr)[i];
        while(temp != NULL){
            next = temp->next; /*Point to the next point avoid losing the pointer for the list*/
            free(temp); /*Free current node*/
            temp = next;
        }    
    }
    return;
}

/* Main function */
int main(int argc , char ** argv){
    FILE * file;
    int i;
    int number;
    HashTable *ptr = create_hash_table(argc); /*create the hash table and the link list and initialize each node*/
    if(argc < 2){
        fprintf(stderr, "No input files provided\n");
        exit(1);
    } 
    argv++;
    argc--;
   
    /*Loop through each file*/
    for(i = 0 ; i < argc ; i++){
        file = fopen(argv[i] , "r");
        if(file){
            while( fscanf(file,"%d" , &number) == 1 ){
                insert_to_hash_table(ptr, number, argv[i]); /*Call helper function to add values to hash table*/
            }
            fclose(file);
        }
        else{
            fprintf(stderr,"Error opening file %s\n", argv[i]);
            exit(1);
        }
    }/*End of for*/

    print_hash_table(ptr); /*Print the hash table*/
    free_hash_table(ptr); /*Free all the dymanic memory in the program*/
    

    return 0;
}/*End of main*/


