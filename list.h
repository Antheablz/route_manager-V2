/** @file list.h
 *  @brief Function prototypes for the linked list.
 */
#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#define MAX_WORD_LEN 50

/**
 * @brief An struct that represents a node in the linked list.
 */
typedef struct RouteData{
    char airline_name[100];
    char airline_icao[100];
    char airline_country[100];
    char from_airport_name[100];
    char from_airport_city[100];
    char from_airport_country[100];
    char from_airport_icao[100];
    char from_airport_altitude[100];
    char to_airport_name[100];
    char to_airport_city[100];
    char to_airport_country[100];
    char to_airport_icao[100];
    char to_airport_altitude[100];
    int counter;
}RouteData;

typedef struct node_t
{
    struct RouteData data;
    struct node_t *next;
} node_t;

/**
 * Function protypes associated with a linked list.
 */
node_t *new_node(RouteData route);
node_t *add_front(node_t *, node_t *);
node_t *add_end(node_t *, node_t *);
node_t *add_inorder(node_t *, node_t *);
node_t *peek_front(node_t *);
node_t *remove_front(node_t *);
void apply(node_t *, void (*fn)(node_t *, void *), void *arg);


#endif
