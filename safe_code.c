void Search_Contact()
{
   char name[1024];
      Contact_Node * node;

   getchar();
   Read_Input(name);
   if ((node = Search(name)) != NULL)
      Print_Contact(node-> contact);
   else
      printf("Nome inexistente.\n");

}

void Print_Contact(Contact * contact)
{
   printf("%s %s@%s %s\n", contact -> name, contact -> email -> local, 
      contact -> email -> domain, contact -> phone);
}

Contact_Node *Search(char * key)
{
   unsigned int hashIndex = Hash_Code(key);
   Contact_Node *current = schedule[hashIndex];

   while(current != NULL)
   {
      if (!strcmp(current -> contact -> name, key))
         return current;
      current = current-> next;
   }
   return NULL;
}

void Destroy_Schedule(Contact_Node **schedule)
{
   int i;
   Contact_Node * next_contact;
   for (i=0; i < SIZE; i++)
   {
      if(schedule[i] != NULL)
      {
         while(schedule[i] != NULL)
         {
            schedule[i] -> contact = Free_Contact(schedule[i] -> contact);
            next_contact = schedule[i] -> next;
            free(schedule[i]);
            schedule[i] = next_contact;
         }
      }
   }
}

void Make_Contact(Contact * new_contact1, Contact * new_contact2)
{
	char name[MAX_NAME], email[MAX_EMAIL], phone[MAX_PHONE];
   	char *token;

   	getchar();	/*Devido ao espaco entre a letra da instrucao e a info da instrucao*/
	/*Name*/
	Read_Input(name);
	 /*Devido ao '\0' no final*/
	new_contact1 -> name = (char *) malloc(sizeof(char) * (strlen(name)+1));
	strcpy(new_contact1 -> name, name);
	new_contact2 -> name = (char *) malloc(sizeof(char) * (strlen(name)+1));
	strcpy(new_contact2 -> name, name);
	
	/*Email*/
	/*Local*/
	new_contact1 -> email = (Email *) malloc(sizeof(Email));
	new_contact2 -> email = (Email *) malloc(sizeof(Email));
	Read_Input(email);
	token = strtok(email, "@");
	new_contact1 -> email -> local = (char *) malloc(sizeof(char) * (strlen(token)+1));
	strcpy(new_contact1 -> email -> local, token);
	new_contact2 -> email -> local = (char *) malloc(sizeof(char) * (strlen(token)+1));
	strcpy(new_contact2 -> email -> local, token);

	/*Domain*/
   	token = strtok(NULL, "@");
   	new_contact1 -> email -> domain = (char *) malloc(sizeof(char) * (strlen(token)+1));
   	strcpy(new_contact1 -> email -> domain, token);
   	new_contact2 -> email -> domain = (char *) malloc(sizeof(char) * (strlen(token)+1));
   	strcpy(new_contact2 -> email -> domain, token);
	
	/*Phone*/
	Read_Input(phone);
   	new_contact1 -> phone = (char *) malloc(sizeof(char) * (strlen(phone)+1));
   	strcpy(new_contact1 -> phone, phone);
   	new_contact2 -> phone = (char *) malloc(sizeof(char) * (strlen(phone)+1));
   	strcpy(new_contact2 -> phone, phone);
}

void Read_Input(char string[])
{
	int i;
	char c;

	for(i = 0;(c = getchar()) != ' ' && c != '\n'; i++)
		string[i] = c;
	string[i] = '\0';
}

Contact * Free_Contact(Contact * contact)
{
   free(contact -> name);
   free(contact -> email-> local);
   free(contact -> email-> domain);
   free(contact -> email);
   free(contact -> phone);
   free(contact);

   return NULL;
}

/*Muda o email de um contacto*/
void Change_Email() /*FALTA MUDAR NA LINKED LIST*/
{
   Contact_Node * node;
   char name[MAX_NAME], new_email[MAX_EMAIL], *parts_email;
   int size;

   scanf("%s %s\n", name, new_email);
   if ((node = Search(name)) != NULL)
   {
      parts_email = strtok(new_email, "@");
      size = strlen(parts_email) + 1;
      node -> contact -> email -> local = realloc(node -> contact -> email -> local, size);
      strcpy(node -> contact -> email -> local, parts_email);

      parts_email = strtok(NULL, "@");
      size = strlen(parts_email) + 1;
      node -> contact -> email -> domain = realloc(node -> contact -> email -> domain, size);
      strcpy(node -> contact -> email -> domain, parts_email);
   }
   else
      printf("Nome inexistente.\n");
}