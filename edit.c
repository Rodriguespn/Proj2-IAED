#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structures.h"

void Add_Contact();
void Destroy_Schedule(Contact_Node **schedule);
void Make_Contact(Contact * new_contact1, Contact * new_contact2);
void Read_Input(char string[]);
Contact * Free_Contact(Contact * contact);
void Delete_Contact();
void Change_Email(); /*FALTA MUDAR NA LINKED LIST*/
void Insert_Contact_Hash(Contact *contact);
void Search_Contact();
Contact_Node *Search(char * key);
void Print_Contact(Contact * contact);
void Delete_Contact_Hash(char * name);
unsigned int Hash_Code(char * name);

Contact_Node * schedule[SIZE];
Contact_Node * list_of_contact;
#include "safe_code.c"

int main()
{
	char c, name[MAX_NAME];
	while((c = getchar()) != 'x')
	{
		switch(c)
	    {
	        case 'a':
	    	    Add_Contact();
	            break;
	        case 'p':
	        	Search_Contact();
	        	break;
	        case 'r':
	        	Delete_Contact();
	        	break;

	        case 'e':
	        	Change_Email();
	        	break;

	        case 'c':
	        	Read_Input(name);
	        	break;
	        	
	        default: /*Teste sem o l*/
	        	break;
		}
	}
	Destroy_Schedule(schedule);
	return 0;
}

/*Le o nome dado no input e apaga o contacto com esse nome, do sistema, se este existir*/
void Delete_Contact()
{
	char name[MAX_NAME];
	Contact_Node * node;

   	getchar();
   	Read_Input(name);
   	if ((node = Search(name)) != NULL)
   	{
		Delete_Contact_Hash(name);
	}
	else
		printf("Nome inexistente.\n");
}

/*Apaga o contacto com o nome "name" do sistema*/
void Delete_Contact_Hash(char * name)
{
	unsigned int hashIndex = Hash_Code(name);
	Contact_Node * node = Search(name), *aux; /*Admitimos que o contacto existe (testado antes)*/

	/*Se o contacto e o unico nesse index da hashtable*/
	if(node -> next == NULL && node -> previous == NULL) 
	{
		Free_Contact(node -> contact);
		free(node);
		schedule[hashIndex] = NULL;		
	}
	else
	{
		if (node == schedule[hashIndex]) /*ja sei que schedule[hashIndex] -> next != NULL*/
		{
			aux = node -> next;
			Free_Contact(node -> contact);
			free(node);
			schedule[hashIndex] = aux;
			schedule[hashIndex] -> previous = NULL;
			node = NULL;
		}
		else
		{
			if (node -> next == NULL) /*Se o contacto e o ultimo da lista*/
			{
				node -> previous -> next = NULL;
				Free_Contact(node -> contact);
				free(node);
				node = NULL;
			}
			else /*Se o contacto estiver no "meio" da linked list na hash table*/
			{
				node -> previous -> next = node -> next; 
				node -> next -> previous = node -> previous;
				Free_Contact(node -> contact);
				free(node);
				node = NULL;
			}
		}
	}
}

void Insert_Contact_Hash(Contact * contact)
{
	Contact_Node * new_node, * aux;
	unsigned int hashIndex = Hash_Code(contact -> name);

	if (schedule[hashIndex] == NULL) /*Adicionamos o primeiro elemento*/
   	{
    	schedule[hashIndex] = (Contact_Node *) malloc(sizeof(Contact_Node));
    	schedule[hashIndex] -> contact = contact;
      	schedule[hashIndex] -> next = NULL;
      	schedule[hashIndex] -> previous = NULL;
   	}
   	else  /*Se ja houver primeiro elemento, fazemos o novo Node apontar para o antigo, e acrescentamo-lo
   	a primeira posicao desse indice na hashtable*/
   	{
   		new_node = (Contact_Node *) malloc(sizeof(Contact_Node));

    	aux = schedule[hashIndex];
    	new_node -> contact = contact;
      	new_node -> next = aux;
      	new_node -> previous = NULL;
      	schedule[hashIndex] = new_node;
      	aux  -> previous = new_node;
   	}
}

unsigned int Hash_Code(char * name)
{
   unsigned int hash = 5381; /*Numero primo*/
   int c;

   while ((c = *name++))
      hash = 33*hash + c; /*33*hash = 32*hash +hash = hash * 2**5 + hash = hash >> 5 + hash*/
   return hash % SIZE;
}

void Add_Contact()
{
	Contact * hash_contact = (Contact *) malloc(sizeof(Contact)), 	/*Contacto para a hash table*/
	* list_contact = (Contact *) malloc(sizeof(Contact));			/*Contacto para a lista duplamente ligada*/
	Contact_Node * c;
	Make_Contact(hash_contact, list_contact);

	if ((c = Search(hash_contact -> name)) == NULL) /*Se o nome ja existir no sistema*/
	{
		Insert_Contact_Hash(hash_contact);
		/*Insert_Contact_List(list_contact);*/
	}
	else
		printf("Nome existente.\n");
	list_contact = Free_Contact(list_contact);
}
