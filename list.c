/** @file list.c
 *  @brief Implementation of a linked list.
 *
 * Based on the implementation approach described in "The Practice
 * of Programming" by Kernighan and Pike (Addison-Wesley, 1999).
 *
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "emalloc.h"
#include "list.h"

/**
 * Function:  new_node
 * -------------------
 * @brief  Allows to dynamically allocate memory for a new node to be added to the linked list.
 *
 * This function should confirm that the argument being passed is not NULL (i.e., using the assert library). Then,
 * It dynamically allocates memory for the new node using emalloc(), and assign values to attributes associated with the node (i.e., val and next).
 *
 * @param route The struct which holds each of the 13 route attributes in a specified field
 *
 * @return node_t* A pointer to the node created.
 *
 */
node_t *new_node(RouteData route)        
{
    assert(&route != NULL);
    node_t *temp = (node_t *)emalloc(sizeof(node_t));
    strcpy(temp->data.airline_name,route.airline_name);
    strcpy(temp->data.airline_icao,route.airline_icao);
    strcpy(temp->data.airline_country,route.airline_country);
    strcpy(temp->data.from_airport_name,route.from_airport_name);
    strcpy(temp->data.from_airport_city,route.from_airport_city);
    strcpy(temp->data.from_airport_country,route.from_airport_country);
    strcpy(temp->data.from_airport_icao,route.from_airport_icao);
    strcpy(temp->data.from_airport_altitude,route.from_airport_altitude);
    strcpy(temp->data.to_airport_name,route.to_airport_name);
    strcpy(temp->data.to_airport_city,route.to_airport_city);
    strcpy(temp->data.to_airport_country,route.to_airport_country);
    strcpy(temp->data.to_airport_icao,route.to_airport_icao);
    strcpy(temp->data.to_airport_altitude,route.to_airport_altitude);
    temp->data.counter = 1;

   
    temp->next = NULL;

    return temp;
}

/**
 * Function:  add_front
 * --------------------
 * @brief  Allows to add a node at the front of the list.
 *
 * @param list The list where the node will be added (i.e., a pointer to the first element in the list).
 * @param new The node to be added to the list.
 *
 * @return node_t* A pointer to the new head of the list.
 *
 */
node_t *add_front(node_t *list, node_t *new)
{
   
    new->next = list;
    return new;
}

/**
 * Function:  add_end
 * ------------------
 * @brief  Allows to add a node at the end of the list.
 *
 * @param list The list where the node will be added (i.e., a pointer to the first element in the list).
 * @param new The node to be added to the list.
 *
 * @return node_t* A pointer to the head of the list.
 *
 */
node_t *add_end(node_t *list, node_t *new)
{
    node_t *curr;

    if (list == NULL)
    {
        new->next = NULL;
        return new;
    }

    for (curr = list; curr->next != NULL; curr = curr->next)
        ;
    curr->next = new;
    new->next = NULL;
    return list;
}

/**
 * Function:  add_inorder
 * ----------------------
 * @brief  Allows to add a new node to the list respecting an order.
 *
 * @param list The list where the node will be added (i.e., a pointer to the first element in the list).
 * @param new The node to be added to the list.
 *
 * @return node_t* A pointer to the node created.
 *
 */
node_t *add_inorder(node_t *list, node_t *new)
{
    node_t *prev = NULL;
    node_t *curr = NULL;

    if (list == NULL)
    {
        return new;
    }

    for (curr = list; curr != NULL; curr = curr->next)
    {
        prev = curr;
        
        /*
        if (strcmp(new->word, curr->word) > 0)
        {
            prev = curr;
        }
        else
        {
            break;
        }
        */
        
    }

    new->next = curr;

    if (prev == NULL)
    {
        return (new);
    }
    else
    {
        prev->next = new;
        return list;
    }
}

/**
 * Function:  peek_front
 * ---------------------
 * @brief  Allows to get the head node of the list.
 *
 * @param list The list to get the node from.
 *
 * @return node_t* A pointer to the head of the list.
 *
 */
node_t *peek_front(node_t *list)
{
    return list;
}

/**
 * Function:  remove_front
 * -----------------------
 * @brief  Allows removing the head node of the list.
 *
 * @param list The list to remove the node from.
 *
 * @return node_t* A pointer to the head of the list.
 *
 */
node_t *remove_front(node_t *list)
{
    if (list == NULL)
    {
        return NULL;
    }

    return list->next;
}

/**
 * Function: apply
 * --------------
 * @brief  Allows to apply a function to the list.
 *
 * @param list The list (i.e., pointer to head node) where the function will be applied.
 * @param fn The pointer of the function to be applied.
 * @param arg The arguments to be applied.
 *
 */
void apply(node_t *list,
           void (*fn)(node_t *list, void *),
           void *arg)
{
    for (; list != NULL; list = list->next)
    {
        (*fn)(list, arg);
    }
}
