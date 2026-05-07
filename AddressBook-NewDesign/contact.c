#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

int  Validate_Email_Id(char* email,AddressBook* addressBook)
{
    int i;
    int atcount=0,atindex;
    int dotcount=0,dotindex;
    for(i=0;email[i]!='\0';i++)
    {
       if(email[i]>='A'&&email[i]<='Z')
        {
            printf("Email Contains Lower case Characters only\n");
           return 0;
        }
       if(email[i]=='@')
       {
       atcount++;
       atindex = i;
       }
       if(email[i]=='.')
       {
        dotcount++;
        dotindex = i;
       }
   }

    if(dotcount!=1 && atcount!=1)
    return 0;

   if(atindex > dotindex)
   {
   printf("Enter (.) before (@)");
   return 0;
   }

   if(atindex==0 || dotindex==atindex+1)
   return 0;

   for(int i=0;i<addressBook->contactCount;i++)
    {
       if(strcmp(email,addressBook->contacts[i].email)==0)
       {
       printf("Email Already Exists\n");
       return 0;
       }
    }


   return 1;
}


int Validate_Phone_Number(char* phone , AddressBook* addressBook)
{
    int len = strlen(phone);
    if(len!=10)
    {
        printf("Phone Number should contain 10 Digits\n");
        return 0;
    }

    for(int i=0;i<len;i++)
    {
        if(phone[i]<'0' || phone[i] > '9')
        {
             return 0;
        }
    }
    for(int i=0;i<addressBook->contactCount;i++)
    {
       if(strcmp(phone,addressBook->contacts[i].phone)==0)
       {
       printf("Phone number already Exists\n");
       return 0;
       }
    }

    return 1;
}




void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    for(int i=0;i<addressBook->contactCount-1;i++)
    {
        for(int j=0;j<addressBook->contactCount-i-1;j++)
        {
            if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)
            {
                Contact temp;
                temp=addressBook->contacts[j];
                addressBook->contacts[j]=addressBook->contacts[j+1];
                addressBook->contacts[j+1]=temp;

            }
        }
    }
    for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("%s %s %s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }

}


void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
  // populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
   saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    char phone[20];
    char email[50];
    getchar();

    printf("Enter your name:");
    scanf("%[^\n]", addressBook->contacts[addressBook->contactCount].name);
    

     int phone_flag=1;

    do{
         
        printf("Enter your phone number:");
        scanf(" %[^\n]",phone);
   
         if(Validate_Phone_Number(phone,addressBook))
         {
         phone_flag=0;
         }
        
    }while(phone_flag);

    int email_flag=1;
     do{
         
        printf("Enter your Email:");
        scanf(" %[^\n]",email);
   
         if(Validate_Email_Id(email,addressBook))
         {
         email_flag=0;
         }
         else{
            printf("Please enter a valid email\n");
         }
    }while(email_flag);
    

      strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
      strcpy(addressBook->contacts[addressBook->contactCount].email,email);

	/* Define the logic to create a Contacts */
    addressBook->contactCount++;
    printf("\n------------------\033[1;32mCreated Contact Successfully!\033[0m---------------\n");
}

int searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
   char name[20];
   char phone[20];
   char email[50];
   int option;
   
   printf("By what you want to search:\n1.Name\n2.Phone number\n3.Email Id\n");
   printf("Enter the option:");
   scanf("%d",&option);
   int flag=0;
   int index=0;
   switch(option)
   {
    case 1: 
            getchar();
            printf("Enter the name:");
            scanf("%[^\n]",name);
            
            for( int i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(name,addressBook->contacts[i].name)==0)
                {
                    flag=1;
                    index=i;
                    printf("%s\t\t%s\t\t%s\n",addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
                     printf("%d\n",index);
                  
                }
            }
                if(flag==1)
                {
                    printf("Contact Found\n");
                   
                    return 1;
                }
                    
                else
                {
                    printf("Contact Not Found\n");
                    return 0;
                
                }
            

    break;
    case 2:
    getchar();
     printf("Enter the Phone number:");
            scanf("%[^\n]",phone);
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(phone,addressBook->contacts[i].phone)==0)
                {
                    flag=1;
                  index=i;
                }
            }
                if(flag==1)
                {
                    printf("\nContact Found\n");
                     printf("%s\t\t%s\t\t%s\n",addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
                     printf("%d\n",index);
                    return 1;
                }
                else
                {
                    printf("\nContact Not Found\n");
                    return 0;
                }
            
    break;
    case 3:
    getchar();
     printf("Enter the Email Id:");
            scanf("%[^\n]",email);
            for( int i=0;i<addressBook->contactCount;i++)
            {
                if(strcmp(email,addressBook->contacts[i].email)==0)
                {
                    flag=1;
                   index=i;
                }
            }
                if(flag==1)
                {
                    printf("\nContact Found\n");
                     printf("%s\t\t%s\t\t%s\n",addressBook->contacts[index].name,addressBook->contacts[index].phone,addressBook->contacts[index].email);
                     printf("%d\n",index);
                    return 1;
                }
                else
                {
                    printf("\nContact Not Found\n");
                    return 0;
                }
            
    break;
    default: printf("Inavlid Option Entered");
            

   }
   
}

void editContact(AddressBook *addressBook)
{
    int index=0;
    int option;
    char email[20];
    char phone[20];
    int email_flag=1,phone_flag=1;
	/* Define the logic for Editcontact */
    int ret=searchContact(addressBook);
    if(ret==0)
    {
        printf("Edit contact failure");
        return;
    }
    else
    {
    printf("Enter the displayed index:");
    scanf("%d",&index);
    printf("What do you want to Edit in the Contact\n1.Name\n2.Phone\n3.Email\n");

    printf("Enter the option:");
    scanf("%d",&option);

    switch(option)
    {
        case 1:
        getchar();
        printf("Enter your name:");
         scanf("%[^\n]", addressBook->contacts[index].name);
        break;
        case 2: 
         getchar();

        do{
         
        printf("Enter your phone number:");
        scanf(" %[^\n]",phone);
   
         if(Validate_Phone_Number(phone,addressBook))
         {
         phone_flag=0;
         }
         else{
            printf("Please enter a valid number\n");
         }
        }while(phone_flag);
        strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
        break;
        
       case 3:  
         do{
         
        printf("Enter your Email:");
        scanf(" %[^\n]",email);
   
         if(Validate_Email_Id(email,addressBook))
         {
         email_flag=0;
         }
         else
         {
            printf("Please enter a valid email\n");
         }
         }while(email_flag);
         
         strcpy(addressBook->contacts[addressBook->contactCount].email,email);
        break;

        default: printf("Invalid Option entered:");

    }
      
      printf("---------------\033[1;32mContact Edited Successfully!\033[0m--------------------\n");
    }

    
}

void deleteContact(AddressBook *addressBook)
{
    int index=0;
	/* Define the logic for deletecontact */
    int ret = searchContact(addressBook);
   if(ret==0)
   {
    printf("Delete info Failure");
    return ;
   }
   else
   {
    printf("Enter the value displayed to proceed :");
    scanf("%d",&index);

    for( int i=index;i<addressBook->contactCount;i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];
            
        
    }
    }
    
      addressBook->contactCount--;
        printf("-------------------\033[1;32mContact Deleted Successfully!\033[0m-----------------\n");
   
   
}
