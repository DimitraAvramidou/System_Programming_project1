#include <stdbool.h>
typedef int trieVal_t;
typedef struct List{
   int id;
   int freq;
   struct List *next;
} List_t;

typedef struct trieNode {
    char key;
    trieVal_t value;
    struct trieNode *next;
    struct trieNode *prev;
    struct trieNode *children;
    struct trieNode *parent;
    bool end;
    List_t *PostingList;
} trieNode_t;


void TrieCreate(trieNode_t **root);
List_t* TrieSearch(trieNode_t *root, const char *key);
void TrieAdd(trieNode_t **root, char *key, int data);
void TrieDestroy( trieNode_t* root );
List_t* insert(trieNode_t *root,int id);
