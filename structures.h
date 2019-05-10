/*Structures*/

typedef struct
{
	char 	*local;			/*Parte local do email*/
	char 	*domain;		/*Parte do dominio do email*/
} Email;

typedef struct
{
    char 	*name;			/*Nome do contacto*/
    Email	*email;			/*Email do contacto*/
    char	*phone;			/*Telemovel do contacto*/
} Contact;

typedef struct node
{  
   	struct node * next;
   	struct node * previous;
   	Contact     * contact;
} Contact_Node;