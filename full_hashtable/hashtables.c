#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Hash table key/value pair with linked list pointer.

  Note that an instance of `LinkedPair` is also a node in a linked list.
  More specifically, the `next` field is a pointer pointing to the the 
  next `LinkedPair` in the list of `LinkedPair` nodes. 
 */
typedef struct LinkedPair
{
  // pointer to key string
  char *key;
  // pointer to value string
  char *value;
  // struct LinkedPair next value which points to next node of the LinkedPair linked list
  struct LinkedPair *next;
  // LinkedPair
} LinkedPair;

/*
  Hash table with linked pairs.
 */
typedef struct HashTable
{
  // hash table with int type capacity
  int capacity;
  // Linked pair struct type with pointer to array storage which is an array of key value pairs
  LinkedPair **storage;
  // full hash table, that can handle collisions, which is when two distinct piece of data have the same hash value,
  // it handles what to do, so things don't get overwritten unnecessarily
} HashTable;

/*
  Create a key/value linked pair to be stored in the hash table.
 */
LinkedPair *create_pair(char *key, char *value)
{
  // initialize linkedpair struct type pointer pair to have memory allocation of linkedpair size bytes
  LinkedPair *pair = malloc(sizeof(LinkedPair));
  // assign pair key with string duplicate func, pass in key's value
  pair->key = strdup(key);
  // assign pair value with string duplicate func, pass in value's value
  pair->value = strdup(value);
  // assign pair next with initialization of NULL
  pair->next = NULL;
  // return pair
  return pair;
}

/*
  Use this function to safely destroy a hashtable pair.
 */
void destroy_pair(LinkedPair *pair)
{
  // if pair is not NULL
  if (pair != NULL)
  {
    // free mem of pair key
    free(pair->key);
    // free mem of pair value
    free(pair->value);
    // free mem of pair
    free(pair);
  }
}

/*
  djb2 hash function

  Do not modify this!
 */
// same hash function
unsigned int hash(char *str, int max)
{
  // init long type hash to 5381
  unsigned long hash = 5381;
  // init int type c
  int c;
  // init char type pointer to unsigned char pointer str typecasted
  unsigned char *u_str = (unsigned char *)str;
  // while loop, continue while c can be assigned to u_str dref
  while ((c = *u_str++))
  {
    // assign hash to hash left shift operator 5 plus has then add c
    hash = ((hash << 5) + hash) + c;
  }
  // return hash mod max
  return hash % max;
}

/*
  Fill this in.

  All values in storage should be initialized to NULL
 */
HashTable *create_hash_table(int capacity)
{
  // from HashTable struct, create new ht pointer, allocate enough mem for hashtable type
  HashTable *ht = malloc(sizeof(HashTable));
  // assign int type capacity to capcity of ht struct
  ht->capacity = capacity;
  // use calloc an initialize allocated mem block to null
  // pass in capacity as num of blocks, and linkedpair type pointer
  ht->storage = calloc(capacity, sizeof(LinkedPair *));
  // return new ht
  return ht;
}

/*
  Fill this in.

  Inserting values to the same index with different keys should be
  added to the corresponding LinkedPair list.

  Inserting values to the same index with existing keys can overwrite
  the value in th existing LinkedPair list.
 */
void hash_table_insert(HashTable *ht, char *key, char *value)
{
  // assign hashIndex , two args, key, max (capacity)
  unsigned int hashIndex = hash(key, ht->capacity);
  // check if the bucket at that index is occupied, if something in bucket, linkedpair, if not null
  // assign the current_pair pointer to storage at hash index
  LinkedPair *current_pair = ht->storage[hashIndex];
  // create pointer to last pair
  LinkedPair *last_pair;
  // if it is occupied, walk through the linkedpairs to see if you find a pair with same key
  // due to the && wont do a string comparison if current pair is null,
  // if current pair is not null, exits while loop right away
  // check if current pair and key passed in is not same
  while (current_pair != NULL && strcmp(current_pair->key, key) != 0)
  {
    // set last pair to current pair
    last_pair = current_pair;
    // set current pair to last pair next
    current_pair = last_pair->next;
  }
  if (current_pair != NULL)
  {
    // if current pair is occupied
    current_pair->value = value;
  }
  else
  {
    // if its not occupied, add a new linkedpair to bucket
    LinkedPair *new_pair = create_pair(key, value);
    // assign the storage at hash index to the new pair next
    new_pair->next = ht->storage[hashIndex];
    // assign the new pair to storage at hash index
    ht->storage[hashIndex] = new_pair;
  }
}

/*
  Fill this in.

  Should search the entire list of LinkedPairs for existing
  keys and remove matching LinkedPairs safely.

  Don't forget to free any malloc'ed memory!
 */
void hash_table_remove(HashTable *ht, char *key)
{
  // assign hashIndex , two args, key, max (capacity)
  unsigned int hashIndex = hash(key, ht->capacity);
  // check if bucket at index is occupied, if it is it is a linkedpair, if not it is null
  // assign current_pair pointer to storage at hash index
  LinkedPair *current_pair = ht->storage[hashIndex];
  // create pointer to last pair
  LinkedPair *last_pair;
  // if occupied, walk through until you find pair with same key,
  while (current_pair != NULL && strcmp(current_pair->key, key) != 0)
  {
    // assign the storage at current hash index to the current pair next
    ht->storage[hashIndex] = current_pair->next;
    // set last pair to current pair
    last_pair = current_pair;
    // set current pair to last pair next
    current_pair = last_pair->next;
  }
  // assign the last pair next to current pair next
  last_pair->next = current_pair->next;
}

/*
  Fill this in.

  Should search the entire list of LinkedPairs for existing
  keys.

  Return NULL if the key is not found.
 */
char *hash_table_retrieve(HashTable *ht, char *key)
{
  // assign hashIndex , two args, key, max (capacity)
  unsigned int hashIndex = hash(key, ht->capacity);

  // if no value at storage at hash index, return null
  return NULL;
}

/*
  Fill this in.

  Don't forget to free any malloc'ed memory!
 */
void destroy_hash_table(HashTable *ht)
{
  // // loop through capacity
  // for (int i = 0; i < ht->capacity; i++)
  // {
  //   // if storage at index i does not equal null
  //   if (ht->storage[i] != NULL)
  //   {
  //     // invoke destroy pair, pass in storage at index i
  //     destroy_pair(ht->storage[i]);
  //   }
  // }
  // // free ht storage
  // free(ht->storage);
  // // free ht
  // free(ht);
}

/*
  Fill this in.

  Should create a new hash table with double the capacity
  of the original and copy all elements into the new hash table.

  Don't forget to free any malloc'ed memory!
 */
HashTable *hash_table_resize(HashTable *ht)
{
  // create new hash table
  HashTable *new_ht;
  // allocate enough mem for new hash table
  new_ht = malloc(sizeof(HashTable));
  // capacity is double the size of ht capacity
  new_ht->capacity = 2 * ht->capacity;
  // pass in double ht capacity as num of blocks and linked pair type pointer
  new_ht->storage = calloc(2 * ht->capacity, sizeof(LinkedPair *));
  // loop through original capacity to store in new ht
  for (int i = 0; i < ht->capacity; i++)
  {
    // assign the storage values of old ht to new ht
    new_ht->storage[i] = ht->storage[i];
  }
  // free old ht storage
  free(ht->storage);
  // free old ht
  free(ht);
  // return new ht
  return new_ht;
}

#ifndef TESTING
int main(void)
{
  struct HashTable *ht = create_hash_table(2);

  hash_table_insert(ht, "line_1", "Tiny hash table\n");
  hash_table_insert(ht, "line_2", "Filled beyond capacity\n");
  hash_table_insert(ht, "line_3", "Linked list saves the day!\n");

  printf("%s", hash_table_retrieve(ht, "line_1"));
  printf("%s", hash_table_retrieve(ht, "line_2"));
  printf("%s", hash_table_retrieve(ht, "line_3"));

  int old_capacity = ht->capacity;
  ht = hash_table_resize(ht);
  int new_capacity = ht->capacity;

  printf("\nResizing hash table from %d to %d.\n", old_capacity, new_capacity);

  destroy_hash_table(ht);

  return 0;
}
#endif
