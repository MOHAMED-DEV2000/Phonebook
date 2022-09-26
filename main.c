/********************************************************************************************/
/*                                                                                          /*
     * La date : 01/04/2022
     * Program de : Contact App en C on utilisent les listes chainees :)
     * Filière : LE-Informatique S4
     * Version : 1.0 
     * les fonction de cette application :
           1) Ajouter une nouveau contact.
           2) Rechercher un contact.
           3) Lister les contacts disponibles.
           4) Afficher les information d'un contact.
           5) Supprimer un contact.
           6) Modifier les informations d'un contact.
           7) Appeler et envoyer un message à un contact.
*/                                                                                          /*
/********************************************************************************************/

// Header Files Section
#include<stdio.h> // pour utiliser les fonctions d'E/S
#include<windows.h> // pour utiliser la fonction system avec 'clr' pour effacer l'écran
#include<stdlib.h> // pour utiliser la fonctionmalloc function
#include<ctype.h> // pour la conversation des characters de LowerCase à UpperCase et vice versa.
#include<string.h> // pour utiliser la fonction strcomp() et strncpy()



                /* La déclaration des structures de données que nous allons utiliser dans notre programme */

// La liste chainée des contacts.
typedef struct contact
{
    int number;
    char name[30];
    char Email[1000];
    // char faceBook[500];
    // char instgram[1000];
    struct contact *next;
}contact; 
typedef struct tracker
{
    int index;
    contact *cont;
    struct tracker *next;
}tracker;

// les prototypes des fonctions
void Add(contact **head);
void Search(contact *head, tracker **tete);
void searchByName(contact *head, char firstChar[], tracker **tete);
void searchByNumber(contact *head, int tel, tracker **tete);
void list(contact *head, tracker **tete);
void ContactInfo(contact **head, contact *cont);
void Edite(contact *cont);
void Delete(contact **head, contact *cont);
void Call(void);
void SendMsg(void);

/* le program principale */
int main(void)
{
    static contact *head = NULL; // créer une tête qui pointera vers une liste chaînée pourquoi ici parce qu'on veut qu'elle ne contienne rien au début.
    static tracker *teteLs = NULL;
    static tracker *teteSr = NULL;
    int choice;

    do
    {

     printf("\n");   
     printf("\t**************** < Menu > ****************\n");
     printf("\n");
     printf("\t< 1 > Add\t\t< 2 > Search\n"); 
     printf("\t< 3 > Contact List\t< 4 > Quit\n");
     printf("\n");
     printf("\t******************************************\n");
     printf("\n");
     printf("\t> ");
     scanf("%d",&choice);


             switch (choice)
              {
                  case 1:    
                            Add(&head);
                            system("cls");
                      
                      break;
     
                  case 2:
                            Search(head, &teteSr);
                            // system("cls");
                     break;

                  case 3:
                            list(head, &teteLs);
                            // system("cls");

                     break;

                  default:
                            printf("\n\n\n");
                            printf("\tExiting .........!\n");
                      break;
              }
              
    }while(choice == 1 || choice == 2 || choice == 3);
    

    return 0;
}


void Add(contact **head)
{
      // this function adds new contact at the front of the list each time this way has time complexity of O(1) that's why i chose it
      contact *new;
      new = (contact*)malloc(sizeof(contact));
      new->next = *head;
      *head = new;
   
      puts("\t\t**** < Creating New Contact > ****");
      puts("\t< Name : ");
      getchar();  // to avoid buffer overflow
      fgets(new->name, sizeof(new->name), stdin); //  It limits the input length based on the buffer size also to avoid buffer overflow and leak of info

      puts("\t< Tel : 06 ");
      scanf("%d", &new->number);
      
      puts("");
      puts("\t< E-mail : ");
      getchar();
      fgets(new->Email, sizeof(new->Email), stdin);

    //   puts("\t< Facebook : ");
    //   fgets(new->faceBook, sizeof(new->faceBook), stdin);

    //   puts("\t< Instgram : ");
    //   fgets(new->instgram, sizeof(new->instgram), stdin);
      
}
void searchByName(contact *head, char firstChar[], tracker **tete)
{
      if(head == NULL)
      {
          puts("\tNo available contact!");
          return;
      }else{
          tracker *tker = (tracker*)malloc(sizeof(tracker));
          contact *temp = head;
          int i = 1, tracker = 0;

          while(temp != NULL)
            {
                 if(strcmp(temp->name, firstChar) == 0)
                 {
                     tracker++;

                     tker->next = *tete;
                     *tete = tker;
                     tker->cont = temp;
                     tker->index = tracker;
  
                     printf("\t[%d] %s\n", tracker, temp->name);
                 }
                 temp = temp->next;
                 i++;
            }
            if(tracker == 0){
                 puts("\tNo contact matches that!");
                 return;
            }
            else{
                int choice;
                puts("\t<0 Save>");
                scanf("%d", &choice);

                if(choice == 0)
                   return;

                while(tker != NULL && choice != tker->index)
                {
                    tker = tker->next;
                }

                if(choice != tker->index)
                    return;
                ContactInfo(&head, tker->cont);
                
            }
            
      }
}
void searchByNumber(contact *head, int tel, tracker **tete)
{
      if(head == NULL)
      {
          puts("\tNo available contact!");
          return;
      }else{
          tracker *tker = (tracker*)malloc(sizeof(tracker));
          contact *temp = head;
          int i = 1, tracker = 0;

          while(head != NULL)
            {
                 if(head->number == tel)
                 {
                     tracker++;

                     tker->next = *tete;
                     *tete = tker;
                     tker->cont = temp;
                     tker->index = tracker;

                     printf("\t[%d] %s", i,head->name);
                 }
                 head = head->next;
                 i++;
            }
            if(tracker == 0){
                 puts("\tNo contact matches that!");
                 return;
            }
            else{
                int choice;
                puts("\t<0 Save>");
                scanf("%d", &choice);

                if(choice == 0)
                   return;

                while(tker != NULL && choice != tker->index)
                {
                    tker = tker->next;
                }

                if(choice != tker->index)
                    return;

                ContactInfo(&head, tker->cont);
                
            }  
      }
}
void Search(contact *head, tracker **tete)
{
      int choice, tel;
      char firstChar[30];

          puts("\n\n\tSearch by :");
          puts("\t[0] Quit\n\t[1] name\n\t[2] Phone number");
          scanf("%d",&choice);

          
          if(choice == 0)
                 return;
          else if(choice == 1)
          {
             puts("\tContact name : ");
             getchar();
             fgets(firstChar, sizeof(firstChar), stdin);
             searchByName(head, firstChar, tete);
          }else if(choice == 2){
             printf("\tPhone Number \n\t06 ");
             scanf("%d",&tel);
             searchByNumber(head, tel, tete);
          }else{
             puts("\tPlease Check your answer!");
          }
      
}
void list(contact *head, tracker **tete){

      if(head == NULL){
           printf("\t******************************************\n"); 
           printf("\t<No Contact has been found!\n");
           printf("\t******************************************\n\n");
      }
      else
      {
           // Parte 1 : How many contacts are there ?
           
           int comp = 0;
           tracker *tker = (tracker*)malloc(sizeof(tracker));
           contact *temp = head; // pour ne perder pas les infos originales 
           
           while (temp != NULL)
           {
              comp++;
              temp = temp->next;
           }

           printf("\t******************************************\n"); 
           printf("\t<%d Contact(s) has been found!\n", comp); // Show how many contacts are there
           printf("\t******************************************\n\n");
           
          // Parte 2 : Show contacts
          temp = head;
          int n = 0;

          while(temp != NULL)
          {
              n++;
              tker->next = *tete;
              *tete = tker;
              tker->cont = temp;
              tker->index = n;

              printf("\n\t[%d] - %s\n", n, temp->name); // Show the available contacts
              temp = temp->next; 
          }
          if(n == 0)
               return;

          int choice;
          puts("\t[0 Return]");
          scanf("%d", &choice);

          if(choice == 0)
                return;

          while(tker != NULL && choice != tker->index)
          {
               tker = tker->next;
          }

          if(choice != tker->index)
                 return;

          ContactInfo(&head, tker->cont);
                
        } 
}
void ContactInfo(contact **head, contact *cont)
{
      int button;
      
      puts("\t**************** Contact Info *****************");
      puts("");
      printf("\tName: %s\n", cont->name);
      printf("\tPhone number : %d\n", cont->number);
      printf("\tE-mail : %s\n", cont->Email);
    //   printf("\tFaceBook : %s\n", cont->faceBook);
    //   printf("\tInstgram : %s\n", cont->instgram);

      puts("\t[1 Edite] \t[2 Delete]");
      puts("\t[3 Call] \t[4 Send a message]");
      puts("\t[5 Exit]");
      scanf("%d",&button);

      switch (button)
      {
           case 1:
                   Edite(cont);
               break;
           case 2:
                   Delete(head, cont);
               break;
           case 3:
                   Call();
               break;
           case 4:
                   SendMsg();
               break;
           default:
                puts("\n\tExiting .....");
                break;
      }
}
void Edite(contact *cont)
{     

       contact temp;

       puts("Edite contact name (Y/N)?");
       getchar();
       char ans = getchar();
       ans = toupper(ans); 

       if(ans == 'Y')
       {
            strncpy(cont->name, temp.name, 30); // Saving the old data temperarlly :)

            puts("New contact name :");
            getchar();
            fgets(cont->name, sizeof(cont->name), stdin);
            printf("Contact name was edited successfully :) %s\n",cont->name);
       }

       puts("Edite Phone number  (Y/N)?");
       getchar();
       ans = getchar();
       ans = toupper(ans);

       if(ans == 'Y')
       {
            temp.number = cont->number;

            puts("New contact Phone number :");
            getchar();
            scanf("%d", &cont->number);
            printf("Contact name was edited successfully :) %s\n",cont->number);
       }

       puts("Edite E-mail (Y/N)?");
       getchar();
       ans = getchar();
       ans = toupper(ans);

       if(ans == 'y')
       {
            strncpy(cont->Email, temp.Email, 1000);

            puts("New contact E-mail :");
            getchar();
            fgets(cont->Email, sizeof(cont->Email), stdin);
            printf("Contact name was edited successfully :) %s\n",cont->Email);
       }

    //    puts("Edite instgram contact (Y/N)?");
    //    getchar();
    //    ans = getchar();
    //    ans = toupper(ans);

    //    if(ans == 'y')
    //    {
    //         strncpy(cont->instgram, temp.instgram, 1000);
            
    //         puts("New contact instgram :");
    //         getchar();
    //         fgets(cont->instgram, sizeof(cont->instgram), stdin);
    //         printf("Contact name was edited successfully :) %s\n",cont->instgram);
    //    }

    //    puts("Edite facebook contact (Y/N)?");
    //    getchar();
    //    ans = getchar();
    //    ans = toupper(ans);

    //    if(ans == 'y')
    //    {
    //         strncpy(cont->faceBook, temp.faceBook, 500);

    //         puts("New contact facebook :");
    //         getchar();
    //         fgets(cont->faceBook, sizeof(cont->faceBook), stdin);
    //         printf("Contact name was edited successfully :) %s\n", cont->faceBook);
    //    }

       int choice;

       puts("\t<1 Save> \t<2 Cancel>");
       scanf("%d",&choice);

       if (choice != 1){
           // this will retrieve the old data and in order to not change anything

           strncpy(cont->name, temp.name, 30);
           strncpy(cont->Email, temp.Email, 1000);
        //    strncpy(cont->faceBook, temp.faceBook, 500);
        //    strncpy(cont->instgram, temp.instgram, 1000);
           cont->number = temp.number; 
           return;
       }else{
           // The old values has been changed successfully

           puts("\tContact saved successfully :)");
           return;
       }
       
 }
void Delete(contact **head, contact *cont)
{
     
     puts("Are you sure you want delete this contact? (Y/N)");

     getchar();
     char confirm = getchar();
     confirm = toupper(confirm);

     if(confirm == 'N')
        return;
     else if(confirm != 'Y' && confirm != 'N')
          puts("Error check your answer please!");
     else
     {
           // Store head node
           contact *temp = *head, *prev;
 
           if(temp == NULL)
                return;

           // If head node itself holds the key to be deleted
           if(temp != NULL && temp == cont){
                *head = temp->next; // Changed head
                free(temp); // free old head
                puts("\tThe contact was deleted successfully!");
                return;
            }
 
            // Search for the contact to be deleted, keep track of the
            // previous node as we need to change 'prev->next'

            while(temp != NULL && temp != cont){
                 prev = temp;
                 temp = temp->next;
            }
            
            if(temp == NULL)
                   return;
            
            prev->next = temp->next;
            free(temp);
            puts("\tThe contact was deleted successfully!");
      } 
}
void Call(void)
{
    puts("\n\tCalling .........");
}
void SendMsg(void)
{
    char message[1000];
    int choice;
    
    puts("\tNew message: ");
    getchar();
    fgets(message, sizeof(message), stdin);


    puts("\t<1 Send>\t<2 cancel>");
    scanf("%d", &choice);
    
    if(choice != 1)
          return;
    puts("\tYour message was sent successfully!");
}