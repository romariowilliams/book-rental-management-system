/* 
	Name of the Program		: HSBookRental
  	Intended to be used as	: School Library Book Rental Management System
  	Administrator password	: lib123
   
*/


#include <stdio.h> //Standard input/output library header for functions such as printf and scanf
#include <conio.h> //Console input/output library header for functions such as getch 
#include <string.h> //Strings header for string functions
#include <windows.h> //Windows-specific header file for system functions such as system("cls");
#include <stdlib.h> //Standard General Utilities library header for functions such as malloc, free and exit 

//Function Prototypes
void linesep(),welcome(),addBooks(),modifyBooks(),searchBooks(),updateStudBookCard(),searchStudBookCard(),addStudents();
int mainMenu(int menuOption), rentMenu(int menuOption);


// Data structure definition to create linked list as a stack.
struct listElement {
	char *s;
	struct listElement *next;  // recursive defintion of struct
};
struct listElement *tos=NULL; // top of the stack

// Declaration of structure bookInfo to store text books
struct bookInfo {char ISBN[20],bookName[50],bookAuthor[30],bookYear[10];
};
struct bookInfo book; //struct for storing textbook details
struct bookInfo modbook;//struct for modified textbook details 

// Declaration of structure studInfo to store students
struct studInfo {char studID[10],studName[40],studForm[5];
};
struct studInfo stud;//struct for storing student information 

// Declaration of structure cardInfo to store book rental cards
struct cardInfo {char studID[10],studName[40],studForm[5],bookID[10],bookISBN[20],bookName[50],rentDate[20],returnDate[20];
};
struct cardInfo card;//struct for storing rental card details
struct cardInfo modcard;//struct for modified rental card details

//File pointers
FILE *bookfile;
FILE *studentfile;
FILE *cardfile;
FILE *cardreportfile;

int bookCount; //Global varibale for counting books

int main(void){ //Main function begins
		
	welcome(); //display welcome message and header
	char passW[6]; 
	int menuOption;
	
	printf(" Welcome!\n Please enter the administrator password: ");
	scanf("%s",passW);
	while ( (strcmp("lib123",passW) != 0)) {
		printf("\n Incorrect! Please try again.\n Enter the administrator password: ");
		scanf("%s",passW);
	} //security measure to password protect the program
	
	
	
	do{
		menuOption= mainMenu(menuOption); //call function to display menu options
	
		switch(menuOption){
			case 1: { addBooks();// call function to add books
				break;
			}
		
			case 2: { modifyBooks();//call function to display books
				break; 
			}
			
			case 3: { searchBooks();//call function to search for books
				break;
			}
			
			case 4: { updateStudBookCard();//call function to update student card
				break;
			}
			
			case 5: { searchStudBookCard();//call function to search for student card
				break;
			}
			case 6: { addStudents();//call function to add student
				break;
			}
			
						
		}
		printf("\n\n Press any key to return to the Main Menu.");
		getch();
	
	} while (menuOption != 8 );//loop menu switch statement until value is 7
	
	getch();
	return 0;
}

void linesep(){ printf("___________________________________________________________________________\n\n");
}

void welcome(){	
	system("cls");
	printf("\n\t\t\tLIBRARY TEXTBOOK RENTAL SYSTEM\n");
    linesep();
}

int checkInput (int x){
	int status,temp;
		status = scanf("%d", &x);
	while(status!=1){
		while((temp=getchar()) != EOF && temp != '\n');
		printf("\n\n Invalid selection! Please enter a number.\n Try again: ");
		status = scanf("%d", &x);
		}
				
		return x;
}

/* --------------------------------------------------------------------------
 * function mainMenu: Displays main menu options 
 * --------------------------------------------------------------------------      
 */

int mainMenu(int menuOption){
	
	welcome();
	printf(" Welcome back!\n\n What would you like to do?\n");
	printf(" 1.Add Books\n 2.Modify Books\n 3.Search for a Book\n 4.Rent or Return Books\n");
	printf(" 5.Search for a Student Card\n 6.Add Student\n 7.Exit Program\n\n");
	printf(" Enter menu selection: ");
	
	menuOption=checkInput(menuOption);		
	while (menuOption <1 || menuOption >7){
			if (menuOption <1){ printf("\n\n You cannot enter a number below 1\n Try again: ");
				menuOption=checkInput(menuOption);
			}
			else if (menuOption >7){ printf("\n\n You cannot enter a number above 7\n Try again: ");
				menuOption=checkInput(menuOption);
			}
	}
	return menuOption;
}

/* --------------------------------------------------------------------------
 * function addBooks: Allows the user to add books to the library
 * --------------------------------------------------------------------------      
 */

void addBooks(){
	int op;
	do {if ((bookfile = fopen ("LibraryBooks.txt","ab+")) == NULL) {
			printf (" File could not be opened.\n");
		}
		else{char isbnvar[20];
			welcome();
			printf("\t\t\tAdd Books\n");
			linesep();
			printf(" Enter the Book ISBN: ");
			scanf("%s",isbnvar);
			fseek(bookfile, 0, SEEK_SET); 
			do{
			   if(strcmp(isbnvar,book.ISBN)==0){
            		do {
						printf("\n That ISBN already exists! Enter another ISBN: ");
                    	scanf("%s",isbnvar);
                    	fseek(bookfile, 0, SEEK_SET); 
                    } while (strcmp(isbnvar,book.ISBN)==0);
				}
			}while(fread(&book,sizeof(book),1,bookfile));
			strcpy(book.ISBN,isbnvar);
			fclose(bookfile);
			bookfile = fopen ("LibraryBooks.txt","ab");
			printf(" \n Enter the Book Name: ");
			scanf(" %[^\n]s",book.bookName); 
			printf(" \n Who is the author of the book? ");
			scanf(" %[^\n]s",book.bookAuthor); 
			printf(" \n What year was the book published? ");
			scanf("%s",book.bookYear);
			fwrite(&book,sizeof(book),1,bookfile);
			fclose(bookfile);
			linesep();
			system("cls");
			welcome();
			printf("\t\t\tAdd Books\n");
			linesep();
			printf(" You just added the following book.\n\n");
			printf(" ISBN: %s\n Name: %s\n Author: %s\n Year: %s\n\n",book.ISBN,book.bookName,book.bookAuthor,book.bookYear);
			printf(" You can edit this information by selecting Modify Books from the Main Menu\n");
			printf(" \n Book IDs for each book will be assigned upon book rental\n");
			linesep();
			printf (" What would you like to do now?\n 1.Add another book\n 2.Stop adding books\n\n Enter selection: ");
			op=checkInput(op);
		}
	} while (op == 1);
}
/* --------------------------------------------------------------------------
 * function modifyBooks: Allows the user to modify book details
 * --------------------------------------------------------------------------      
 */

void modifyBooks(){
	welcome();
	printf("\t\t\tModify Books\n");
	linesep();
	char isbnvar[20];
	int numbook=0;
	if ((bookfile = fopen ("LibraryBooks.txt","rb+")) == NULL) {
			printf (" You must add books before using this module.\n");
		}
	else {
		bookfile = fopen("LibraryBooks.txt","rb+");
	    printf(" Please enter the Book ISBN#: ");
	    scanf("%s",isbnvar);
	    linesep();
	    fseek(bookfile, 0, SEEK_SET); 
	    
	    
	    
	    
	    do {
	    fread(&book,sizeof(book),1,bookfile);
		} while((strcmp(isbnvar,book.ISBN)!=0)&&(!feof(bookfile)));
	    if(strcmp(isbnvar,book.ISBN)==0){
	    	printf(" Book Found!\n Name of Book: %s\n",book.bookName);
			printf(" \n Enter the New Book Name: ");
			scanf(" %[^\n]s",modbook.bookName); //[^\n] allows for space in string , also the space between " and % should not be removed
			printf(" \n Who is the author of the book? ");
			scanf(" %[^\n]s",modbook.bookAuthor); 
			printf(" \n What year was the book published? ");
			scanf("%s",modbook.bookYear);
			strcpy(modbook.ISBN,book.ISBN);
			fseek(bookfile,-sizeof(book),SEEK_CUR);
			fwrite(&modbook,sizeof(book),1,bookfile);
			printf(" \n Book modification was successful! ");
		} 
		else {
			printf(" Book not Found. Sorry!");
		}			
		   
	
	    
		fclose(bookfile);              	
	}
}

/* --------------------------------------------------------------------------
 * function searchBooks: Allows the user search for a book
 * --------------------------------------------------------------------------      
 */

void searchBooks(){
	welcome();
	printf("\t\t\tSearch for a Book\n"); 
	linesep();
	char isbnvar[20];
	int numbook=0;
	int stat;
	 if ((bookfile = fopen ("LibraryBooks.txt","rb+")) == NULL) {
			printf (" You must add books before using this module.\n");
		}
	 else {
	 	bookfile = fopen("LibraryBooks.txt","rb+");
	 	printf(" Please enter the Book ISBN#: ");
        scanf("%s",isbnvar);
        linesep();
        while (fread(&book,sizeof(book),1,bookfile)){
			if(strcmp(isbnvar,book.ISBN)==0){
			printf(" Name of Book: %s\n",book.bookName);
			printf(" Author of Book: %s\n",book.bookAuthor);
			printf(" Year Published: %s\n",book.bookYear);
			stat = 1;
						
							if ((cardfile = fopen ("StudentCards.txt","rb+")) == NULL) {
							printf ("\n This book has not been rented as yet.\n");
						}
						else { cardfile = fopen ("StudentCards.txt","rb+");
							fseek(cardfile, 0, SEEK_SET); 
                   			 while(fread(&card,sizeof(card),1,cardfile))
                   		 {
                      		  if(strcmp(isbnvar,card.bookISBN)==0)
                       		 {
                        		numbook = numbook +1;
                       		 }
                   		 }
                  		printf(" Number of this book in library: %d\n",numbook);
                    	linesep();
                   		printf(" Data List for this Book\n\n");
                   		char headNB[]={" Name of Book"};
						char headBID[]= {" Book ID"};
						char headRented[]= {" Rented to"};
						printf("%-30s%-15s%-15s\n",headNB,headBID,headRented);
                    	fseek(cardfile, 0, SEEK_SET); 
                    	while(fread(&card,sizeof(card),1,cardfile))
                    	{
                       	 if((strcmp(isbnvar,card.bookISBN)==0)&&(strcmp(card.returnDate,"not returned")==0))
                       	 {
                        	printf("%-32s%-13s%-30s\n",card.bookName,card.bookID,card.studName);
                        	stat = 1;
                       	 }
                    	}
                    	fclose(cardfile);
						}
             	   }
             	   
             	}
             	   if (stat!=1){
             	   		printf(" Book not Found. Sorry!");
					}
                     
                    fclose(bookfile);
	}
}

/* --------------------------------------------------------------------------
 * function rentMenu: Displays menu option for renting or returning book
 * --------------------------------------------------------------------------      
 */

int rentMenu(int menuOption){
	
	
	printf("\n What is the student doing?\n 1.Renting a book\n 2.Returning a book\n\n");
    printf(" Select a number from the menu to continue: ");
	
	menuOption=checkInput(menuOption);		
	while (menuOption <1 || menuOption >2){
			if (menuOption <1){ printf("\n\n You cannot enter a number below 1\n Try again: ");
				menuOption=checkInput(menuOption);
			}
			else if (menuOption >2){ printf("\n\n You cannot enter a number above 2\n Try again: ");
				menuOption=checkInput(menuOption);
			}
	}
	return menuOption;
}

/* --------------------------------------------------------------------------
 * function searchStudBookCard: Allows the user to update student book card 
 *	Allows students to rent or return books
 * --------------------------------------------------------------------------      
 */

void updateStudBookCard(){
	welcome();
	printf("\t\t\tUpdate a Student's Book Card\n");
	linesep();
		char isbnvar[20];
		char bookidvar[10];
		char studidvar[20];
		char c[5];
		int menuOption;
		int stat;
		int numbook;
	 if ((bookfile = fopen ("LibraryBooks.txt","rb+")) == NULL) {
			printf (" You must add books before using this module.\n");
		}
		else if ((studentfile = fopen ("StudentList.txt","rb+")) == NULL) {
			printf (" You must add students before using this module.\n");
		}
	 
	 else {  		bookfile = fopen("LibraryBooks.txt","rb+");
	 				cardfile=fopen("StudentCards.txt","ab+");
	 			     studentfile=fopen("StudentList.txt","rb+");
	 
                	
                    printf(" Please enter the student ID#: ");
                    scanf("%s",studidvar);
                    linesep();
                                     
                
                       	fseek(studentfile, 0, SEEK_SET); 
                    	do 
						
						{fread(&stud,sizeof(stud),1,studentfile);
						} while((strcmp(studidvar,stud.studID)!=0)&&(!feof(studentfile)));
                    	
                       	                       	 
                       	 if(strcmp(studidvar,stud.studID)==0){	
                        	printf(" Just to verify, is the student %s? (Y/N) \n Enter Y for yes or N for no:  ",stud.studName);
                        	scanf("%s",c);
                        	if(strcmp(c,"y")==0 || strcmp(c,"Y")==0){
                        		menuOption= rentMenu(menuOption);
	
								switch(menuOption){
									case 1: { 
											  fseek(studentfile, 0, SEEK_SET); 
											  do {
											    fread(&stud,sizeof(stud),1,studentfile);
												} while((strcmp(studidvar,stud.studID)!=0)&&(!feof(studentfile)));
											  	 if(strcmp(studidvar,stud.studID)==0){ 
											  strcpy(card.studID,stud.studID);
											  strcpy(card.studName,stud.studName);
											  strcpy(card.studForm,stud.studForm);
												}
											  printf("\n Enter the rental date (DD/MM/YYYY): ");
											  scanf("%s",card.rentDate);
											  strcpy(card.returnDate,"not returned");
											  printf("\n How many books are you adding to the student card? ");
											  bookCount = checkInput(bookCount);
											  int i;
											  for (i=1; i <= bookCount;i++){ 
												
												printf("\n Please enter book %d's Book ISBN: ",i);
												scanf ("%s",isbnvar);
												fseek(bookfile, 0, SEEK_SET); 
											    do {
											    fread(&book,sizeof(book),1,bookfile);
												} while((strcmp(isbnvar,book.ISBN)!=0)&&(!feof(bookfile)));
											    if(strcmp(isbnvar,book.ISBN)==0){
                   									 	strcpy(card.bookISBN,book.ISBN);
                   									 	strcpy(card.bookName,book.bookName);
                   									 	printf("\n The book was found: %s ",book.bookName);
                   									 	printf("\n Now enter the specific Book ID of the book being rented: ");
                   									 	scanf("%s",card.bookID);
                   									 	fwrite(&card,sizeof(card),1,cardfile);
                   									   }
                   									   else {
                   									 	printf(" Book not found. Book %d not added",i);
                   									 	
														}
														
							                        
                   									 }
                   									 												              									 	
											
											  
										break;
									}
								
									case 2: { printf("\n Enter the return date (DD/MM/YYYY): ");
											  scanf("%s",modcard.returnDate);
									
											  printf("\n How many books are being returned? ");
											  bookCount = checkInput(bookCount);
											  int i;
											  for ( i=1; i <= bookCount;i++){ 
												printf("\n Please enter book %d's Book ID: ",i);
												scanf ("%s",bookidvar);
												
												fseek(cardfile, 0, SEEK_SET); 
    
    
    
    
											    do {
											    fread(&card,sizeof(card),1,cardfile);
												} while((strcmp(bookidvar,card.bookID)!=0)&&(!feof(cardfile)));
											    if((strcmp(bookidvar,card.bookID)==0)&&(strcmp(studidvar,card.studID)==0)){
									    			strcpy(modcard.studID,card.studID);
													strcpy(modcard.studName,card.studName);
													strcpy(modcard.studForm,card.studForm);
													strcpy(modcard.bookID,card.bookID);
													strcpy(modcard.bookISBN,card.bookISBN);
													strcpy(modcard.bookName,card.bookName);
													strcpy(modcard.rentDate,card.rentDate);
													fseek(cardfile,-sizeof(card),SEEK_CUR);
													fwrite(&modcard,sizeof(card),1,cardfile);
												}
														else {
                   									 	printf(" Book not found on Student Card! ");
                   									 	}
														
													}
												
											 }
									
										break; 
									
									}
								
									
								}
								
							}
							else {
								printf(" Student does not exist in school database.");
							}
						
                       	
                       	
                       
                       	
                     
                    fclose(studentfile);
                    fclose(cardfile);
                    fclose(bookfile);
	 
	 }
}

/* --------------------------------------------------------------------------
 * function searchStudBookCard: Allows the user to search for a student book card
 * --------------------------------------------------------------------------      
 */

void searchStudBookCard(){
	welcome();
	printf("\t\t\tSearch for a Student's Book Card\n");
	linesep();
	char studidvar[20];
	 if ((cardfile = fopen ("StudentCards.txt","rb+")) == NULL) {
			printf (" You must add student cards before using this module.\n");
		}
	else{
		
	cardfile=fopen("StudentCards.txt","rb+");
	
	
	printf(" Please enter the student ID#: ");
    scanf("%s",studidvar);
    linesep();
    fseek(cardfile, 0, SEEK_SET); 
            do {
				fread(&card,sizeof(card),1,cardfile);
			} while((strcmp(studidvar,card.studID)!=0)&&(!feof(cardfile)));				
            
			if(strcmp(studidvar,card.studID)==0){
				
				cardreportfile = fopen ("StudentRentalCard.txt","w+");	
				printf(" Student: %s\tID#: %s\tForm: %s\n",card.studName,card.studID,card.studForm);
				fprintf(cardreportfile,"\t\tGlenmuir High School - TextBook Rental Cards \n");
				fprintf(cardreportfile,"---------------------------------------------------------------- \n");
				fprintf(cardreportfile,"Student: %s\tID#: %s\tForm: %s\n",card.studName,card.studID,card.studForm);
				fprintf(cardreportfile,"---------------------------------------------------------------- \n");
				linesep();
				char headNB[]={" Name of Book"};
				char headBID[]= {" Book ID"};
				char headRenD[]= {" Date Rented"};
				char headRetD[]= {" Date Returned"};
				printf("%-30s%-15s%-15s%-15s\n",headNB,headBID,headRenD,headRetD);
				
					fprintf(cardreportfile,"%-30s%-15s%-15s%-15s\n",headNB,headBID,headRenD,headRetD);
					
					fseek(cardfile, 0, SEEK_SET); 
					while (fread(&card,sizeof(card),1,cardfile)){
					
                    if(strcmp(studidvar,card.studID)==0){
								
							
						if (strcmp("not returned",card.returnDate)==0){
						  		printf(" %-32s%-13s%-15s\n",card.bookName,card.bookID,card.rentDate);
						  		fprintf(cardreportfile,"%-32s%-13s%-15s\n",card.bookName,card.bookID,card.rentDate);
						}
						else if (strcmp("not returned",card.returnDate)!=0){
						  		printf(" %-32s%-13s%-15s%-15s\n",card.bookName,card.bookID,card.rentDate,card.returnDate);
						  		fprintf(cardreportfile,"%-32s%-13s%-15s%-15s\n",card.bookName,card.bookID,card.rentDate,card.returnDate);
						}
						
			    	}
			    	}
				 fclose(cardreportfile);
				 system("StudentRentalCard.txt");
			}
			else{
				printf(" The student does not have a rental card to display.");
			}
     		fclose(cardfile);
    
	
	
	}
}




/* --------------------------------------------------------------------------
 * function addStudents: Allows the user to add students to the library
 * --------------------------------------------------------------------------      
 */

void addStudents(){
	int op;
	do {if ((studentfile = fopen ("StudentList.txt","ab+")) == NULL) {
			printf (" File could not be opened.\n");
		}
		else{char studidvar[20];
			welcome();
			printf("\t\t\tAdd Students\n");
			linesep();
			printf(" Enter the Student ID: ");
			scanf("%s",studidvar);
			fseek(studentfile, 0, SEEK_SET); 
			do{
			   if(strcmp(studidvar,stud.studID)==0){
            		do {
						printf("\n That ID already exists! Enter another ID: ");
                    	scanf("%s",studidvar);
                    	fseek(studentfile, 0, SEEK_SET); 
                    } while (strcmp(studidvar,stud.studID)==0);
				}
			}while(fread(&stud,sizeof(stud),1,studentfile));
			strcpy(stud.studID,studidvar);
			fclose(studentfile);
			studentfile = fopen ("StudentList.txt","ab");
			printf(" \n Enter the Student Name: ");
			scanf(" %[^\n]s",stud.studName); 
			printf(" \n What grade is the student in? ");
			scanf(" %[^\n]s",stud.studForm); 			
			fwrite(&stud,sizeof(stud),1,studentfile);
			fclose(studentfile);
			linesep();
			system("cls");
			welcome();
			printf("\t\t\tAdd Students\n");
			linesep();
			printf(" You just added the following student.\n\n");
			printf(" ID: %s\n Name: %s\n Grade: %s\n\n",stud.studID,stud.studName,stud.studForm);
			printf(" You can edit this information by selecting Modify Students from the Main Menu\n");
			linesep();
			printf (" What would you like to do now?\n 1.Add another student\n 2.Stop adding students\n\n Enter selection: ");
			op=checkInput(op);
		}
	} while (op == 1);
}
