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
  // Pair struct type with pointer to array storage, which is an array of key value pairs
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
  // if pair is not NULL
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
  // From the BasicHashTable struct, create new ht pointer, allocate enough memory for Basic HashTable type
  // ht has capacity and storage
  BasicHashTable *ht = malloc(sizeof(BasicHashTable));
  // assign the int type capacity to the capacity of the ht struct
  ht->capacity = capacity;
  // use calloc which allocates mem and initializes allocated mem block to zero
  // arguments: num of blacks to be allocated, size of each block
  // in this case it is capacity and the bytes to fit in the Pair struct
  // calloc Pair type pointer
  ht->storage = calloc(capacity, sizeof(Pair *));
  // return new ht
  return ht;
}

/****
  Fill this in.

  If you are overwriting a value with a different key, print a warning.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_insert(BasicHashTable *ht, char *key, char *value)
{
  //our hash function expects to return unsigned int type, and two arguments, key and max, which is capacity
  unsigned int hashIndex = hash(key, ht->capacity);
  // if we are overwriting value with different key, print warning,
  // we can check if there is a value at the storage index
  if (ht->storage[hashIndex])
  {
    // print warning
    printf("There is already a value at that current hash index, overwriting.");
    // invoke destroy pair function, which frees malloc'ed memory
    destroy_pair(ht->storage[hashIndex]);
  }
  // create new pair and store it at the hash index
  ht->storage[hashIndex] = create_pair(key, value);
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void hash_table_remove(BasicHashTable *ht, char *key)
{
  // first we need to find the hash index, same as insert
  unsigned int hashIndex = hash(key, ht->capacity);
  // if ht at storage index hashIndex exists
  if (ht->storage[hashIndex])
  {
    // invoke destroy pair function, which frees malloc'ed memory
    destroy_pair(ht->storage[hashIndex]);
    // reassign storage at hashindex to null
    ht->storage[hashIndex] = NULL;
  }
}

/****
  Fill this in.

  Should return NULL if the key is not found.
 ****/
char *hash_table_retrieve(BasicHashTable *ht, char *key)
{
  // repeat to find hash index
  unsigned int hashIndex = hash(key, ht->capacity);
  // if ht at storage index hash index exists
  if (ht->storage[hashIndex])
  {
    // return the value at the storage at the hash index
    return ht->storage[hashIndex]->value;
  }
  // if no value at storage at hash index, return null
  return NULL;
}

/****
  Fill this in.

  Don't forget to free any malloc'ed memory!
 ****/
void destroy_hash_table(BasicHashTable *ht)
{
  // loop through capacity, if storage at i exists destroy pair,
  for (int i = 0; i < ht->capacity; i++)
  {
    // if storage at i exists destroy
    if (ht->storage[i])
    {
      // invoke destroy pair apss in the storage at index i
      destroy_pair(ht->storage[i]);
      // reassign ht storage at i to null
      ht->storage[i] = NULL;
    }
  }
  // free hashtable storage
  free(ht->storage);
  // free hash table
  free(ht);
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

// solution:
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// typedef struct Pair {
//   char *key;
//   char *value;
// } Pair;

// typedef struct BasicHashTable {
//   int capacity;
//   Pair **storage;
// } BasicHashTable;

// Pair *create_pair(char *key, char *value)
// {
//   Pair *pair = malloc(sizeof(Pair));
//   pair->key = strdup(key);
//   pair->value = strdup(value);

//   return pair;
// }

// void destroy_pair(Pair *pair)
// {
//   if (pair != NULL) {
//     free(pair->key);
//     free(pair->value);
//     free(pair);
//   }
// }

// unsigned int hash(char *str, int max)
// {
//   unsigned long hash = 5381;
//   int c;
//   unsigned char * u_str = (unsigned char *)str;

//   while ((c = *u_str++)) {
//     hash = ((hash << 5) + hash) + c;
//   }

//   return hash % max;
// }

// /****
//   Fill this in.

//   All values in storage should be initialized to NULL
//   (hint: look up `calloc`)
//  ****/
// BasicHashTable *create_hash_table(int capacity)
// {
//   BasicHashTable *ht = malloc(sizeof(BasicHashTable));
//   ht->storage = calloc(capacity, sizeof(Pair *));
//   ht->capacity = capacity;

//   return ht;
// }

// /****
//   Fill this in.

//   If you are overwriting a value with a different key, print a warning.

//   Don't forget to free any malloc'ed memory!
//  ****/
// void hash_table_insert(BasicHashTable *ht, char *key, char *value)
// {
//   unsigned int index = hash(key, ht->capacity);
//   Pair *pair = create_pair(key, value);

//   Pair *stored_pair = ht->storage[index];
//   if (stored_pair != NULL) {
//     if (strcmp(key, stored_pair->key) != 0) {
//       printf("WARNING: Overwriting key/value: %s/%s\n", stored_pair->key, stored_pair->value);
//     }
//     destroy_pair(stored_pair);
//   }
//   ht->storage[index] = pair;
// }

// /****
//   Fill this in.

//   Don't forget to free any malloc'ed memory!
//  ****/
// void hash_table_remove(BasicHashTable *ht, char *key)
// {
//   unsigned int index = hash(key, ht->capacity);

//   if (ht->storage[index] == NULL ||
//       strcmp(ht->storage[index]->key, key) != 0 ) {
//     fprintf(stderr, "Unable to remove entry with key: %s", key);
//   } else {
//     destroy_pair(ht->storage[index]);
//     ht->storage[index] = NULL;
//   }

// }

// /****
//   Fill this in.

//   Should return NULL if the key is not found.
//  ****/
// char *hash_table_retrieve(BasicHashTable *ht, char *key)
// {
//   unsigned int index = hash(key, ht->capacity);

//   if (ht->storage[index] == NULL ||
//       strcmp(ht->storage[index]->key, key) != 0 ) {
//     fprintf(stderr, "Unable to retrieve entry with key: %s\n", key);
//     return NULL;
//   }

//   return ht->storage[index]->value;
// }

// /****
//   Fill this in.

//   Don't forget to free any malloc'ed memory!
//  ****/
// void destroy_hash_table(BasicHashTable *ht)
// {
//   for (int i = 0 ; i < ht->capacity ; i++) {
//     if (ht->storage[i] != NULL) {
//       destroy_pair(ht->storage[i]);
//     }
//   }

//   free(ht->storage);
//   free(ht);
// }

// int main(void)
// {
//   struct BasicHashTable *ht = create_hash_table(16);

//   hash_table_insert(ht, "line", "Here today...\n");

//   printf("%s", hash_table_retrieve(ht, "line"));

//   hash_table_remove(ht, "line");

//   if (hash_table_retrieve(ht, "line") == NULL) {
//     printf("...gone tomorrow. (success)\n");
//   } else {
//     fprintf(stderr, "ERROR: STILL HERE\n");
//   }

//   destroy_hash_table(ht);

//   return 0;
// }