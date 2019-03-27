#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/****
  Basic hash table key/value pair
 ****/
typedef struct Pair
{
  // pointer to key string
  char *key;
  // pointer to value string
  char *value;
  // Pair
} Pair;

/****
  Basic hash table
 ****/
typedef struct BasicHashTable
{
  // hash table has capacity
  int capacity;
  // Pair struct type with pointer to array
  Pair **storage;
  // Basic Hash Table
} BasicHashTable;

/****
  Create a key/value pair to be stored in the hash table.
 ****/
Pair *create_pair(char *key, char *value)
{
  // Initialize the Pair struct type pointer to have memory allocation of Pair size bytes
  Pair *pair = malloc(sizeof(Pair));
  // assign pair key string with string duplicate function and pass in key's value
  pair->key = strdup(key);
  // assign pair value string with string duplicate function and pass in value's value
  pair->value = strdup(value);
  // return pair
  return pair;
}

/****
  Use this function to safely destroy a hashtable pair.
 ****/
void destroy_pair(Pair *pair)
{
  // if value of pair is not empty
  if (pair != NULL)
  {
    // free memory of pair key
    free(pair->key);
    // free memory of pair value
    free(pair->value);
    // free memory of pair
    free(pair);
  }
}

/****
  djb2 hash function

  Do not modify this!
 ****/
unsigned int hash(char *str, int max)
{
  // initialize long type hash to 5381
  unsigned long hash = 5381;
  // initialize int type c
  int c;
  // initialize char type pointer u_str and assign value of char pointer str typecasted
  unsigned char *u_str = (unsigned char *)str;
  // while loop continue while c can be assigned to u_str deref
  while ((c = *u_str++))
  {
    // assign hash to hash left shift operator 5 plus hash then add c
    hash = ((hash << 5) + hash) + c;
  }
  // return hash mod max
  return hash % max;
}

/****
  Fill this in.

  All values in storage should be initialized to NULL
  (hint: look up `calloc`)
 ****/
BasicHashTable *create_hash_table(int capacity)
{
  BasicHashTable *ht;

  return ht;
}

/****
  Fill this in.

  If you are overwriting a value with a different key, print a warning.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_insert(BasicHashTable *ht, char *key, char *value)
{
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_remove(BasicHashTable *ht, char *key)
{
}

/****
  Fill this in.

  Should return NULL if the key is not found.
 ****/
char *hash_table_retrieve(BasicHashTable *ht, char *key)
{
  return NULL;
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void destroy_hash_table(BasicHashTable *ht)
{
}

#ifndef TESTING
int main(void)
{
  struct BasicHashTable *ht = create_hash_table(16);

  hash_table_insert(ht, "line", "Here today...\n");

  printf("%s", hash_table_retrieve(ht, "line"));

  hash_table_remove(ht, "line");

  if (hash_table_retrieve(ht, "line") == NULL)
  {
    printf("...gone tomorrow. (success)\n");
  }
  else
  {
    fprintf(stderr, "ERROR: STILL HERE\n");
  }

  destroy_hash_table(ht);

  return 0;
}
#endif
