/** @file route_manager.c
 *  @brief A small program to analyze airline routes data.
 *  @author Anthea Blais
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


//function prototypes
void getCommandLineInput(int argc, char*argv[]);
void openFile(char[100], char[100]);
node_t* checkQuestion(char[100], char[100], RouteData newRoute,node_t *list);
node_t* deleteDuplicates(node_t *list,char[100]);
void deleteDuplicatesHelper(int, node_t *list,node_t *curr,node_t *ptr);
node_t* sort(node_t *list,char[100]);
void outputFile(char[100], char[100], node_t *list);
void swap(node_t *node1, node_t *node2);


// TODO: Make sure to adjust this based on the input files given
#define MAX_LINE_LEN 100

/**
 * @brief Serves as an incremental counter for navigating the list.
 *
 * @param p The pointer of the node to print.
 * @param arg The pointer of the index.
 *
 */
void inccounter(node_t *p, void *arg)
{
    int *ip = (int *)arg;
    (*ip)++;
}

/**
 * @brief Allows to print out the content of a node.
 *
 * @param p The pointer of the node to print.
 * @param arg The format of the string.
 *
 */
void print_node(node_t *p, void *arg)
{
    char *fmt = (char *)arg;
    printf(fmt, p->data.counter,p->data.to_airport_country/*p->word*/);
}

/**
 * @brief Allows to print each node in the list.
 *
 * @param l The first node in the list
 *
 */
void analysis(node_t *l)
{
    int len = 0;

    apply(l, inccounter, &len);
    printf("Number of nodes: %d\n", len);

    apply(l, print_node, "%i %s\n");
}

/*MY METHODS*/

/**
 * @brief Obtains the command line inputs and stores into variables
 * 
 * @param argc the number of command line inputs
 * @param argv the cmd line arguments
*/
void getCommandLineInput(int argc, char *argv[]){
    char question[100];
    char number[100];
    
    if(argc < 4){
        printf("ERROR: enter correct number of inputs\n");
    }
    else{
        sscanf(argv[2]+11, "%[^\t\n]",question);
        sscanf(argv[3]+4, "%[^\t\n]",number);
        
    }

    openFile(question,number);

}

/**
 * @brief Opens the yaml file and parses each line by the colon where each token is stored in  correct struct field
 * 
 * @param question  the question number from cmd line
 * @param number    the number of elements outputted into .csv file
*/
void openFile(char question[100], char number[100]){
    FILE *fp = fopen("routes-airlines-airports.yaml", "r");
    int i = 1;
    char *row;
    char temp[100];
    node_t *list = NULL;
    struct RouteData route;
    row = malloc(sizeof(char) * MAX_LINE_LEN);

    fgets(row,500,fp);  //overrides the very first line in the file "routes: " since not needed when parsing
    while (fgets(row,500,fp) != NULL ){
     
        char *token = strtok(row, ":"); //break up each row by colon 
        token = strtok(NULL,":");
        
        if(i <= 13){    //each of the 13 lines in file correspond to a specific struct (node) field, essentially creating new node every 13 lines
            switch(i) {
                case 1:
                    token ++;   //increase token pointer so we do not include space char when storing token
                    token = strtok(token, "\n");    //used to not include the new line char when storing token
                    strcpy(temp,token);
                    strcpy(route.airline_name,temp);
                    break;
                case 2:
                    token ++;
                    token = strtok(token, "\n");
                    strcpy(temp,token);
                    strcpy(route.airline_icao,temp);
                    break;
                case 3:
                    token ++;
                    token = strtok(token, "\n");
                    strcpy(temp,token);
                    strcpy(route.airline_country,temp);
                    break;
                case 4:
                    
                    token ++;
                    token = strtok(token, "\n");
                    strcpy(temp,token);
                    strcpy(route.from_airport_name,temp);
                    
                    break;
                case 5:
                    token ++;
                    token = strtok(token, "\n");
                    strcpy(temp,token);
                    strcpy(route.from_airport_city,temp);
                    
                    break;
                case 6:
                    
                    token ++;
                    token = strtok(token, "\n");
                    strcpy(temp,token);
                    strcpy(route.from_airport_country,temp);
                    
                    break;
                case 7:
                    token ++;
                    token = strtok(token, "\n");
                    strcpy(temp,token);
                    strcpy(route.from_airport_icao,temp);
                    
                    break;
                case 8:
                    token ++;
                    token = strtok(token, "\n");
                    strcpy(temp,token);
                    strcpy(route.from_airport_altitude,temp);
                    
                    break;
                case 9:
                    token ++;
                    token = strtok(token, "\n");
                    strcpy(temp,token);
                    strcpy(route.to_airport_name,temp);
                    
                    break;
                case 10:
                    token ++;
                    token = strtok(token, "\n");
                    strcpy(temp,token);
                    strcpy(route.to_airport_city,temp);
                    
                    break;
                case 11:        //this is the field that the edge case will land
                    if(token[2] == 32){ //so we check if the first char is ' which is ascii #32
                        token +=2;      //update token so it does not include single quote and space chars
                        token = strtok(token, "'");     //we remode the very last single quote off end of string
                    }
                    token ++;
                    token = strtok(token, "\n");
                    strcpy(temp,token);
                    strcpy(route.to_airport_country,temp);
                    
                    break;
                case 12:
                    token ++;
                    token = strtok(token, "\n");
                    strcpy(temp,token);
                    strcpy(route.to_airport_icao,temp);
                    
                    break;
                case 13:
                    token ++;
                    token = strtok(token, "\n");
                    strcpy(temp,token);
                    strcpy(route.to_airport_altitude,temp);
                    list = checkQuestion(question,number,route,list);
                    break;
                }
            if(i==13){
                i=1;
                
            }
            else{
                i++;
            }
        }
    }

    list = deleteDuplicates(list,question); //list that does not contain any duplicated nodes
    outputFile(question, number, list); //send to the output file function which creates final .csv file

    fclose(fp);

    //free everything in linked list
    node_t  *temp_n = NULL;
    for ( ; list != NULL; list = temp_n ) {
        temp_n = list->next;
        free(list);
    } 
    free(row);
}


/**
 * @brief   creates and returns a linked list depending on the given question from cmd line, 
 * 
 * @param question  the question number from cmd line
 * @param number    the number of elements outputted into .csv file 
 * @param newRoute  struct that holds data for the node
 * @param list      list of nodee]s 
*/
node_t* checkQuestion(char question[100],char number[100],RouteData newRoute,node_t *list){

    if(atoi(question) == 1 && (strcmp(newRoute.to_airport_country,"Canada") == 0)){ //creates and inserts the node with destination country as Canada
        list = add_end(list,new_node(newRoute));
    }
    else if(atoi(question) == 2){
        list = add_end(list,new_node(newRoute));
        
    }
    else if(atoi(question) == 3){
        list = add_end(list,new_node(newRoute));
    
    }
    return list;
    
}

/**
 * @brief finds any duplicate nodes, increases counter and deletes duplicates
 * 
 * @param list      the linked list
 * @param question  the question number from cmd line
*/
node_t* deleteDuplicates(node_t *list,char question[100]){
    node_t *curr = list;
    node_t *ptr = curr;
    
    int temp = 0;   //counter that counts the duplicates

    while(curr != NULL){
        ptr = curr;
        while(ptr->next != NULL){
            //checks the question number so we remove correct nodes
            switch(atoi(question)){
                case 1:
                    if(strcmp(curr->data.airline_name,ptr->next->data.airline_name) == 0){
                        deleteDuplicatesHelper(temp, list, curr, ptr);
                     } else{
                        ptr = ptr->next;
                    }
                    break;
                case 2:
                    if(strcmp(curr->data.to_airport_country,ptr->next->data.to_airport_country) == 0){
                        deleteDuplicatesHelper(temp, list, curr, ptr);
                    } else {
                        ptr = ptr->next;
                    }
                    break;
                case 3:
                    if(strcmp(curr->data.to_airport_name,ptr->next->data.to_airport_name) == 0){
                        deleteDuplicatesHelper(temp, list, curr, ptr);
                    } else{
                        ptr = ptr->next;
                    }
                    break;
            }

        }
        curr = curr->next;
    }

    list = sort(list,question); //sends the modified list to be sorted
    return list;
}

/**
 * @brief helper function which specifically increases the nodes counter and deletes duplicate node
 * 
 * @param temp  temporary variabel to hold the current count of node
 * @param list  the linked list
 * @param curr  current node we are at inside the linked list
 * @param ptr   used to find element that is after curr element in linked list
*/
void deleteDuplicatesHelper(int temp, node_t *list,node_t *curr,node_t *ptr){
    node_t *duplicate = NULL;
    temp = curr->data.counter;
    temp++;
    curr->data.counter = temp;

    duplicate = ptr->next;
    ptr->next = ptr->next->next;
    free(duplicate);

}

/**
 * @brief sorts the linked list in alphabetically and based on count ascending or decensing order
 * 
 * @param list  the linked list
 * @param question  the question number we use to find how to sort linked list
*/
node_t* sort(node_t *list,char question[100]){
    node_t *curr = list;
    node_t *ptr = curr;

    while(curr != NULL){
        ptr = curr;
        while(ptr->next != NULL){
            //switch statement to figure out to sort depending on the question number
            switch(atoi(question)){
                case 1:
                    if(curr->data.counter < ptr->next->data.counter){   //sorts based on count first
                        swap(curr,ptr);
                    //sorts based on alphabetical order
                    } else if(curr->data.counter == ptr->next->data.counter && strcmp(curr->data.airline_name,ptr->next->data.airline_name) > 0){ 
                        swap(curr,ptr);
                    }
                    break;
                case 2:
                    if(curr->data.counter > ptr->next->data.counter){ 
                        swap(curr,ptr);
                    } else if(curr->data.counter == ptr->next->data.counter && strcmp(curr->data.to_airport_country,ptr->next->data.to_airport_country) > 0){
                        swap(curr,ptr);
                     }
                    break;
                case 3:
                    if(curr->data.counter < ptr->next->data.counter){ 
                        swap(curr,ptr);
                    } else if(curr->data.counter == ptr->next->data.counter && strcmp(curr->data.to_airport_name,ptr->next->data.to_airport_name) > 0){
                        swap(curr,ptr);
                    }
                    break;
            }
            ptr = ptr->next;
        }
        curr = curr->next;
    }

    return list;
}

/**
 * @brief function which outputs correct information into the .csv file
 * 
 * @param question  the question obtained from cmd line used to find what we should be outputting
 * @param number    the number of elements from linked list we want to write into the file
 * @param list      the linked list
*/
void outputFile(char question[100], char number[100],node_t *list){
    FILE *file = fopen("output.csv", "w");
    int counter = atoi(number); //the number of elements we want in the file

    fprintf(file,"subject,statistic\n");    //labels at top of the file

    //switch to find the question so we can output correct items into the file
    switch(atoi(question)){
        case 1:
            for(node_t *curr = list; curr != NULL; curr = curr->next){  //for loop to go through linked list
                if(counter > 0){
                    fprintf(file, "%s (%s),%i\n",curr->data.airline_name,curr->data.airline_icao,curr->data.counter);
                }
                counter--;  //decrease counter so we have the correct number of elements outputted into the .csv file
            }
            break;
        case 2:
            for(node_t *curr = list; curr != NULL; curr = curr->next){
                if(counter > 0){
                    fprintf(file,"%s,%i\n",curr->data.to_airport_country,curr->data.counter);
                }
                counter--;
            }
            break;
        case 3:
            for(node_t *curr = list; curr != NULL; curr = curr->next){
                if(counter > 0){
                    fprintf(file,"\"%s (%s), %s, %s\",%i\n",curr->data.to_airport_name,curr->data.to_airport_icao,curr->data.to_airport_city,curr->data.to_airport_country,curr->data.counter);
                }
                counter--;
            }
            break;
    }

    fclose(file);
}

/**
 * @brief swap function which swaps nodes, used inside of the sorting function
 * 
 * @param node1 first node we want to swap
 * @param node2 second node we want to swap
*/
void swap(node_t *node1, node_t *node2){
    RouteData temp;

    temp = node1->data;
    node1->data = node2->next->data;
    node2->next->data = temp;

}
/**
 * @brief The main function and entry point of the program.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The list of arguments passed to the program.
 * @return int 0: No errors; 1: Errors produced.
 *
 */
int main(int argc, char *argv[])
{
    getCommandLineInput(argc,argv); //get command lines

    exit(0);
}



