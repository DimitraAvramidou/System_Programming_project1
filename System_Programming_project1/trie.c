#include <stdio.h>
#include "trie.h"
#include <stdlib.h>

List_t* CreatList(int id_text){
   List_t* temp_node;
   temp_node = (List_t *) malloc(sizeof (List_t));
   temp_node->id=id_text;
   temp_node->freq=1;
   temp_node->next=NULL;
   //printf("[%d,%d]xaaxaxaxa\n",temp_node->id ,temp_node->freq);
   return temp_node;
}

void Insert(List_t* node_list,int id_text){
    List_t* lista=node_list;
    int bika=0;
    while(lista!=NULL){
    //  printf("%d %d\n",lista->id,id_text);
        if(lista->id==id_text){
            lista->freq=(lista->freq)+1;
            //printf("[%d,%d]nnnnnn\n",lista->id ,lista->freq);
            break;
        }
        while(lista->next != NULL){
          //printf("kaiiiiiiiiii\n");
          if(lista->next->id==id_text){
              lista->next->freq=(lista->next->freq)+1;
             //printf("[%d,%d] aaaaa\n",lista->next->id ,lista->next->freq);
             bika++;
              break;
            }

          lista=lista->next;
          //lista=CreatList(id_text);
        }
        //printf("[%d,%d]\n",lista->id,lista->freq);
        //lista=lista->next;
        if(bika==0){
        lista->next=CreatList(id_text);
        List_t* temp=lista->next;
        while(temp!=NULL){
          //printf("[%d,%d]\n",temp->id,temp->freq);
					temp=temp->next;
        }
        break;
      }
      break;
    }

    //lista=lista->next;
    //lista=CreatList(id_text);


}

trieNode_t *TrieCreateNode(char key, int data);

void TrieCreate(trieNode_t **root)
{
 *root = TrieCreateNode('\0', 0xffffffff);
}

trieNode_t *TrieCreateNode(char key, int data)
{
 trieNode_t *node = NULL;
 node = (trieNode_t *)malloc(sizeof(trieNode_t));

 if(NULL == node)
 {
  printf("Malloc failed\n");
  return node;
 }

 node->key = key;
 node->next = NULL;
 node->children = NULL;
 node->value = data;
 node->parent= NULL;
 node->prev= NULL;
 node->end=false;
 node->PostingList=NULL;
 return node;
}

void TrieAdd(trieNode_t **root, char *key, int data)
{
 trieNode_t *pTrav = NULL;
 trieNode_t *pTrav1 = NULL;
 int i=0;
 if(NULL == *root)
 {
  printf("NULL tree\n");
  return;
 }
//#ifdef DEBUG
 //printf("\nInserting key %s: \n",key);
//#endif
 pTrav = (*root)->children;
 pTrav1 = (*root)->children;


 if(pTrav == NULL)
 {
  /*First Node*/
  for(pTrav = *root; *key; pTrav = pTrav->children)
  {
   pTrav->children = TrieCreateNode(*key, 0xffffffff);
   pTrav->children->parent = pTrav;
//#ifdef DEBUG
  //printf("Inserting: [%c]\n",pTrav->children->key);
//#endif
   key++;
  }

  pTrav->children = TrieCreateNode('\0', data);
  pTrav->children->parent = pTrav;
  //printf("apo edw\n" );
  pTrav->children->PostingList=CreatList(data);
//#ifdef DEBUG
  //printf("Inserting: [%c]\n",pTrav->children->key);
//#endif
  return;
 }

 if(TrieSearch(pTrav, key))
 {
  //printf("Duplicate!\n");
  i++;
  pTrav1=pTrav->children;
  //return;
 }
 //printf("irthaaa\n");
 while(*key != '\0')
 {
  if(*key == pTrav->key)
  {
   key++;
//#ifdef DEBUG
   //printf("Traversing child: [%c]\n",pTrav->key);
//#endif
   pTrav = pTrav->children;
    //key++;

  }
  else
   break;
 }
 if(i>0 && pTrav->key=='\0'){
  Insert(pTrav->PostingList,data);
 }
//printf("irthaaa\n");
 while(pTrav->next)
 {
  if(*key == pTrav->next->key)
  {
   key++;
   TrieAdd(&(pTrav->next), key, data);
   return;
  }
  pTrav = pTrav->next;
 }

 if(*key)
 {
  pTrav->next = TrieCreateNode(*key, 0xffffffff);
 }
 else
 {
  pTrav->next = TrieCreateNode(*key, data);
 }

 pTrav->next->parent = pTrav->parent;
 pTrav->next->prev = pTrav;

//#ifdef DEBUG
 //printf("Inserting [%c] as neighbour of [%c] \n",pTrav->next->key, pTrav->key);
//#endif


 if(!(*key))
  return;

 key++;

 for(pTrav = pTrav->next; *key; pTrav = pTrav->children)
 {
  pTrav->children = TrieCreateNode(*key, 0xffffffff);
  pTrav->children->parent = pTrav;
//#ifdef DEBUG
  //printf("Inserting: [%c]\n",pTrav->children->key);
//#endif
  key++;
 }

//printf("irthaaa\n");
 pTrav->children = TrieCreateNode('\0', data);
  pTrav->children->parent = pTrav;
 pTrav=pTrav->children;
  if(pTrav->next==NULL  ){
    //printf("geiaaaaaaaaaaaaaaaaaa souuuuu\n");
    pTrav->PostingList=CreatList(data);

  }
  else{
    //printf("geiaaaaaaaaaaaaaaaaaa maria\n");
    Insert(pTrav->PostingList,data);

  }


//#ifdef DEBUG
 //printf("Inserting: [%c]\n",pTrav->children->key);

//#endif

 return;
}

List_t* TrieSearch(trieNode_t *root,const char *key)
{
  trieNode_t *level = root;
  trieNode_t *pPtr = NULL;

  int lvl=0;
  while(1)
  {
   trieNode_t *found = NULL;
   trieNode_t *curr;

   for (curr = level; curr != NULL; curr = curr->next)
   {
    if (curr->key == *key)
    {
     found = curr;
     lvl++;
     break;
    }
   }

   if (found == NULL)
    return NULL;

   if (*key == '\0')
   {
    pPtr = curr;

    return (pPtr->PostingList);
   }


   level = found->children;
   key++;
  }
 }




void TrieDestroy( trieNode_t* root )
{
 trieNode_t *tPtr = root;
 trieNode_t *tmp = root;

    while(tPtr)
 {
  while(tPtr->children)
   tPtr = tPtr->children;

  if( tPtr->prev && tPtr->next)
  {
   tmp = tPtr;
   tPtr->next->prev = tPtr->prev;
   tPtr->prev->next = tPtr->next;
//#ifdef DEBUG
   //printf("Deleted [%c] \n", tmp->key);
//#endif
   free(tmp);
  }
  else if(tPtr->prev && !(tPtr->next))
  {
   tmp = tPtr;
   tPtr->prev->next = NULL;
//#ifdef DEBUG
   //printf("Deleted [%c] \n", tmp->key);
//#endif
   free(tmp);
  }
  else if(!(tPtr->prev) && tPtr->next)
  {
   tmp = tPtr;
   tPtr->parent->children = tPtr->next;
   tPtr->next->prev = NULL;
   tPtr = tPtr->next;
//#ifdef DEBUG
   //printf("Deleted [%c] \n", tmp->key);
//#endif
   free(tmp);
  }
  else
  {
   tmp = tPtr;
   if(tPtr->parent == NULL)
   {
    /*Root*/
    free(tmp);
    return;
   }
   tPtr = tPtr->parent;
   tPtr->children = NULL;
//#ifdef DEBUG
   //printf("Deleted [%c] \n", tmp->key);
//#endif
   free(tmp);
  }
 }

}
