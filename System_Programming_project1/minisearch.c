#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "trie.h"
#define _GNU_SOURCE




int main(int argc,char*argv[]){
	int lines_allocated = 1280000;
    int max_line_len = 100000;

    /* Allocate lines of text */
    char **words = (char **)malloc(sizeof(char*)*lines_allocated);
		char **rest = (char **)malloc(sizeof(char*)*lines_allocated);
		char **copy = (char **)malloc(sizeof(char*)*lines_allocated);
		char **copy1 = (char **)malloc(sizeof(char*)*lines_allocated);
		char **text = (char **)malloc(sizeof(char*)*lines_allocated);
		char **ids = (char **)malloc(sizeof(char*)*lines_allocated);
    if (words==NULL)
        {
        fprintf(stderr,"Out of memory (1).\n");
        exit(1);
        }

    FILE *fp = fopen(argv[2], "r");
    if (fp == NULL)
        {
        fprintf(stderr,"Error opening file.\n");
        exit(2);
        }

    int i;
    for (i=0;1;i++)
        {
        int j;

        /* Have we gone over our line allocation? */
        if (i >= lines_allocated)
        {
            int new_size;

						/* Double our allocation and re-allocate */
            new_size = lines_allocated*2;
            words = (char **)realloc(words,sizeof(char*)*new_size);
						rest=(char**)realloc(rest,sizeof(char*)*new_size);
						copy=(char**)realloc(copy,sizeof(char*)*new_size);
						copy1=(char**)realloc(copy1,sizeof(char*)*new_size);
						text=(char**)realloc(text,sizeof(char*)*new_size);
            if (words==NULL)
                {
                fprintf(stderr,"Out of memory.\n");
                exit(3);
                }
            lines_allocated = new_size;
        }
        /* Allocate space for the next line */
        words[i] = malloc(max_line_len);
				rest[i]=malloc(max_line_len);
				copy[i]=malloc(max_line_len);
				copy1[i]=malloc(max_line_len);
				text[i]=malloc(max_line_len);
				  char *pbuff;
					int r=0;
        if (words[i]==NULL)
            {
            fprintf(stderr,"Out of memory (3).\n");
            exit(4);
            }

        if (fgets(words[i],max_line_len-1,fp)==NULL) //diavazw to arxeio
            break;
		}

					        /* Get rid of CR or LF at end of line */
        //for (int j=strlen(words[i])-1;j>=0 && (words[i][j]=='\n' || words[i][j]=='\r');j--){
          	//words[i][j+1]='\0';

					//}



				/* Close file */
    fclose(fp);

    int j,line=0;
		char *token1;
		for(j = 0; j < i; j++)
		{
			strcpy( copy[j], words[j]);
 			/* get the first token */
	    token1 = strtok(copy[j]," \t");
			ids[j]=token1;										//apothikeuw ta id se enan pinaka

			while (token1 != NULL)
    	{
				text[j]=token1;									//apothikeuw to upoloipo keimeno se kathe grammh tou pinaka
        token1 = strtok (NULL,"");			//kathe keimeno se mia grammh tou pinaka
			}

		}

		for(j = 0; j < i; j++)
		{
				//printf ("%s %s\n",ids[j],text[j]);
				//printf ("%s\n",ids[j]);
		}

/*Create a trie */

	trieNode_t *root;
	TrieCreate(&root);
	char *token3;
	int id;
	int t;

	for(t = 0; t < i; t++)
	{
		id=atoi(ids[t]);
		if(t>0){
			if(atoi(ids[t])-atoi(ids[t-1]) != 1){
				printf("wrong id\n");
				return 0;
			}
		}
		strcpy(copy1[t],text[t]);
		token3 = strtok(copy1[t]," ");
		while (token3 != NULL)
		{
				TrieAdd(&root, token3,id);
				token3 = strtok (NULL," ");
		}
	}


		//--------------------------------------------> end of trie creation





		char* token4;
		char *buffer=NULL;
		int read;
		char** yes=(char **)malloc(sizeof(char*)*400);
		int y=0;
		size_t len;
     //----diavazei apo to plhktrologio thn entolh pou thelw----//
			printf("Enter a command \n");
			read=getline(&buffer,&len,stdin);
			if(-1 != read){
				puts(buffer);							//vazw olh thn grammh apo to terminal ston buffer
				token4=strtok(buffer," "); //spaw olo to string analoga me to keno kai pairnw thn kathe leksi

				while(token4!=NULL){

						yes[y]=token4;							//vazw thn kathe leski se ena pinaka
						token4=strtok(NULL," \n\t");
						y++;
					}
			}
			else{
				printf("no line to read.. \n");
			}
			//-----an dothei to /search -----//
		if (strcmp(yes[0],"/search")==0){

			//printf("i am searching the word : <<%s>>\n",yes[1]);

			if(y>11){ 			//elegxos gia to an oi lekseis pou dothoun einai pano apo 10 ,an einai pare mono tis 10
				y=11;
			}
				//search the word//
				for(int x=1;x<=y-1 ;x++){
						List_t* ret = TrieSearch(root->children,yes[x]);
						List_t* temp=ret;
						if(NULL != temp){

								printf("found %s\n",yes[x]);
								while(temp!=NULL){
									printf("[%d,%d]\n",temp->id,temp->freq);
									printf("%d		%s\n",temp->id,text[(temp->id)-1]);
									temp=temp->next;
								}
								printf("\n\n\n\n\n");
						}
						else{
								printf("not found %s\n\n\n\n\n",yes[x]);
							}
					}


		}
		else if(strcmp(yes[0],"/exit")==0){		//an dothei to /exit
			return 0;
		}
		else if(strcmp(yes[0],"/df")==0){			//an dothei to /df
			for(int x=1;x<y ;x++){
			List_t* ret = TrieSearch(root->children,yes[x]);
			List_t* temp=ret;
			int suxnothta=0;
			if(NULL != temp){


					while(temp!=NULL){
						suxnothta=suxnothta+(temp->freq);
						temp=temp->next;
					}
					printf("%s   %d\n",yes[x],suxnothta); //ektuponei thn leksh kai poses fores uparxei sunolika sto txt
			}
			else{
					printf("not found %s\n",yes[x]);
				}
			}
		}
//---------apodesmeush pinakwn--------------///////

		free(words);
		free(rest);
		free(copy);
		free(copy1);
		free(text);
		free(ids);
		free(yes);
		TrieDestroy(root->children);
return 0;
}
