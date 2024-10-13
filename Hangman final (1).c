#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char tolowercase (char c) {               //converts character input to lowercase
	if (c >= 65 && c <= 90) {
			c = c + 32;
	}
	return(c);
}

void startingScreen(int highscore_max)                      //Game starting screen
{
	int key;
	printf("\n");
	printf("\t <>      <>       <><>       <>      <>    <>>>>>     <>      <>       <><>       <>      <>  \n");
	printf("\t <>      <>     <>    <>     <>>>    <>   <>    <>    <>>>  <<<>     <>    <>     <>>>    <>  \n");
	printf("\t <><<<>>><>   <>  <<>>  <>   <>  <>  <>   <>          <> <<>> <>   <>  <<>>  <>   <>  <>  <>  \n");
	printf("\t <>      <>   <>        <>   <>    <<<>   <>   <<<    <>  <>  <>   <>        <>   <>    <<<>  \n");
	printf("\t <>      <>   <>        <>   <>      <>    <>>>>>     <>      <>   <>        <>   <>      <>  \n");
	
	while (key !=1) {                                                 //displays a menu to the user
		printf("\n\n\n");                                             // 1 to start game, 2 for how to play, 3 for highscore
		printf("Press '1' to start game!!!\n");
		printf("Press '2' to view game rules!!!\n");
		printf("Press '3' to view previous high score!!!\n");
		scanf("%d", &key);
		while (key != 1 && key != 2 && key != 3)
		{
			printf("Incorrect Key Pressed, Please try again!\n");
			getchar();
			scanf("%d", &key);
		}
		if (key == 1)
		{
			return;
		}
		else if (key == 2)
		{
			printf("-> You have a total of 6 lives/chances to guess a word\n");
			printf("-> Enter a single letter each time\n");
			printf("-> Upon entering a letter, if correct it will replace the '_' or it will appear in the incorrect letter list.\n");
			printf("-> Make sure that you keep a look at incorrect words before entering a letter\n");
			printf("\n \n \t HEY BUDDY, YOU ARE GOOD TO GO!!!\n\n");
		}
		else if (key == 3) {
			printf("The highscore is: %d", highscore_max);
		}
		}
}

void printHangman(int no_of_tries, int no_of_lives, int highscore){                     //main display during game
	printf("\n");
	printf("Current score: %d   |   Lives Remaining: %d\n", highscore,no_of_lives);
    switch (no_of_tries)
    {
    case 0:
        printf("%c%c%c%c%c\n",201,205,205,205,187);
        printf("%c\n",186);
        printf("%c\n",186);
        printf("%c\n",186);
        printf("%c\n",186);
        printf("%c\n",202);
        break;

    case 1:
        printf("%c%c%c%c%c\n",201,205,205,205,187);
        printf("%c   O\n",186);
        printf("%c\n",186);
        printf("%c\n",186);
        printf("%c\n",186);
        printf("%c\n",202);
        break;

    case 2:
        printf("%c%c%c%c%c\n",201,205,205,205,187);
        printf("%c   O\n",186);
        printf("%c   %c\n",186,179);
        printf("%c   %c\n",186,179);
        printf("%c\n",186);
        printf("%c\n",202);
        break;

    case 3:
        printf("%c%c%c%c%c\n",201,205,205,205,187);
        printf("%c   O\n",186);
        printf("%c %c%c%c\n",186,196,196,180);
        printf("%c   %c\n",186,179);
        printf("%c\n",186);
        printf("%c\n",202);
        break;

    case 4:
        printf("%c%c%c%c%c\n",201,205,205,205,187);
        printf("%c   O\n",186);
        printf("%c %c%c%c%c%c\n",186,196,196,197,196,196);
        printf("%c   %c\n",186,179);
        printf("%c\n",186);
        printf("%c\n",202);
        break;

    case 5:
        printf("%c%c%c%c%c\n",201,205,205,205,187);
        printf("%c   O\n",186);
        printf("%c %c%c%c%c%c\n",186,196,196,197,196,196);
        printf("%c   %c\n",186,179);
        printf("%c  %c\n",186,47);
        printf("%c\n",202);
        break;

    

    case 6:
        printf("%c%c%c%c%c\n",201,205,205,205,187);
        printf("%c   O\n",186);
        printf("%c %c%c%c%c%c\n",186,196,196,197,196,196);
        printf("%c   %c\n",186,179);
        printf("%c  %c %c\n",186,47,92);
        printf("%c\n",202);
        break;
    
    default: break;
    }
}

int main() {
	srand(time(NULL));
	char character, keepPlaying = 'y', restart;
	int word_length = 0, count = 1, random, no_of_correct = 0, no_of_tries = 0, quit = 0, correct_flag = 0, no_of_lives = 3, highscore = 0, incorrect_count = 0;
	int already_present = 0, highscore_max = 0;
	char *word, *incorrect_letters;
	int *correct;
	FILE *words, *fhighscore;
	
	words = fopen("words.txt","r");   		// Finding words.txt file
		if (words == NULL) {
	       printf("Error! opening file");
	       exit(1);
	   }
	    
	fhighscore = fopen("highscore.txt", "r+");    //reading highscore from preexisting file or creating a new file if not present
	fscanf(fhighscore, "%d", &highscore_max);
	fclose(fhighscore);
   
	startingScreen(highscore_max);                            //game starting screen
   
   while (no_of_lives > 0 && quit == 0 && keepPlaying == 'y') {     //Game loop
   	
   		words = fopen("words.txt","r");                //opens file in read mode
	   
	   do {
			character = fgetc(words);
			if (character == '\n' ) {
				count++;
			}
		} while (character != EOF);                               //counts the number of words in the file
	
		fclose(words);                                           //closes file
		
		random = rand() % count;                                //gets a random number between 0 and the number of words in the file
		count = 0;
	
		words = fopen("words.txt","r");           //opens the file again in read mode
		
		do {                                                  //counts the words upto the random number generated
			character = fgetc(words);
			if (character == '\n' ){
				count++;
			}
		} while (count != random);
			
		
		word_length = 0;                                     //initializes word length to zero before picking new word
		word = (char *) calloc(0, sizeof(char));             //Dynamically allocating memory to store the picked word
		
		do {
			character = fgetc(words);                        //gets character
			if (character == '\n') {                         //if newline character so breaks out of loop
				break;
			}
			word_length++;                                  //if it is any character apart from \n, it increases the wordlength
			word = (char *) realloc(word, word_length * sizeof(char));      //reallocates memory to hold the next character
			*(word + (word_length-1)) = character;                          //stores the character to the correct address
		}while(character != '\n');
		
   		fclose(words);
   		
   		correct = (int *)calloc(word_length, sizeof(int));               //dynamically assigns memory to correct array which will tell us which positions have been guessed
   		incorrect_letters = (char *) calloc(0,sizeof(char));             //dynamically assigns memory to incorrect_letters array which will display all incorrect letters entered by user

   		while (no_of_correct < word_length && no_of_tries < 6 && quit == 0) {   //guess word loop
   			system("cls");                                                      //clears screen
   			printHangman(no_of_tries, no_of_lives, highscore);                  //calls function of display
   	
	   		for (int i = 0; i < word_length; i++) {                             //prints _ where letters have not been guessed
	   			if (*(correct + i) == 0) {
	   				printf("_ ");
			   	}
			   	else {
			   		printf("%c ", *(word + i));                                //prints the character which have been guessed
			   	}
		   	}
		
			printf("\nIncorrect letters: ");                                  //Displays incorrect letters that have been inputted
			for (int i = 0; i < incorrect_count; i++) {                       //incorrect_count keeps count of wrong letters input
				printf("%c ,", *(incorrect_letters+i));                       //The wrong letters that have been input are displayed if any
			}
	   		printf("\nEnter a character (type - to exit): ");                //input character
	   		scanf(" %c", &character);
	   		character = tolowercase(character);                              //converts input to lower case
	   	
	   		if (character == '-') {                                          //quits if - input
	   			quit = 1;
		   	}
	   	
	   		for (int i = 0; i < word_length; i++) {                         //loop runs for each character in the word
	   			if (character == *(word + i) && *(correct + i) == 0) {      //if character appears in word and correct array shows that it had not been input earlier
	   				*(correct + i) = 1;                                     //set correct array to 1 at that place and increment no_of_correct
	   				no_of_correct++;
	   				correct_flag = 1;                                       //correct_flag set to 1 if input character was correct
			   	}															//input character is incorrect if it is not a letter, or a letter that has been enterred previously
		   	}
		   
			if (correct_flag == 0 && quit != 1) {                          //if input character was not correct, no of tries are incremented
				no_of_tries++;
				for (int i = 0; i < incorrect_count; i++) {                //run loop up till no of times user entered unique incorrect input
					if (character == *(incorrect_letters + i)) {           //if input character already present in incorrect_letters array, set already_present flag to 1
						already_present = 1;
					}
				}
				if (already_present == 0) {                               //if already present is not flagged 
					incorrect_count++;                                    //increment incorrect count and use it to reallocate size of incorrect_letters array to hold next unique incorrect character
					incorrect_letters = (char *) realloc(incorrect_letters, incorrect_count * sizeof(char));
					*(incorrect_letters + (incorrect_count - 1)) = character;   //store character in incorrect_letters array at next position	
				}
				already_present = 0;                                     //set both already present and correct flag back to zero for next loop in guessing character
			}
	   	
	   		correct_flag = 0;
	   }
	   
	   if (quit == 1) {                                                 //if user had input - so game loop will terminate
	   	break;
	   }
	   if (no_of_tries == 6) {                                         //if 6 tries have been reached, decrement lives by 1
	   		printf("Sorry you weren't able to guess the word! The correct word was: ");
	   		for (int i = 0; i < word_length; i++) {
	   			printf("%c", *(word+i));
			}
	   		printf("\n");
	   		no_of_lives--;
	   }
	   else if (no_of_correct == word_length) {                      //if number of characters correctly inputted equals to the word length, then show congrats msg
	   	printf("Yay! You guessed the correct word! The word was: ");
	   	for (int i = 0; i < word_length; i++) {
	   		printf("%c", *(word+i));
		}
	   	printf("\n");
	   	highscore++;                                                //Also increments user's score
	   }
		if (highscore > highscore_max) {
	   		printf("Woohoo! You managed to get a new highscore!\n");   //checks to see if user's current score is greater than all time highscore
	   		fhighscore = fopen("highscore.txt", "w+");    //If it is, displays congrats msg and writes highscore to file
			fprintf(fhighscore, "%d", highscore);
			fclose(fhighscore);
			highscore_max = highscore;
		   }
	   if (no_of_lives > 0) {                                                       //Asks the user if they want to keep playing
	   		printf("Do you want to keep playing? Type Y for yes and N for no: ");
	   		scanf(" %c", &keepPlaying);
	   		keepPlaying = tolowercase(keepPlaying);
	   		while (keepPlaying != 'y' && keepPlaying != 'n') {
	   			printf("Incorrect Input! Please try again: ");
				scanf(" %c", &keepPlaying);
				keepPlaying = tolowercase(keepPlaying);
			} 
	   }
	   if (no_of_lives <= 0) {                                                     //If the user is out of lives, tells them their score and asks them if they want to restart game
	   	printf("Sorry you are out of lives T_T\n");
	   	printf("Your score was %d\n", highscore);
		printf("Would you like to restart with 3 lives? Type Y for yes and N for no: ");
		scanf(" %c", &restart);
		restart = tolowercase(restart);
		while (restart != 'y' && restart != 'n') {
			printf("Incorrect Input! Please try again: ");
			scanf(" %c", &restart);
			restart = tolowercase(restart);
		}
		if (restart == 'y') {
			no_of_lives = 3;
			highscore = 0;
		}
	   }

	   no_of_correct = 0;
	   no_of_tries = 0;
	   incorrect_count = 0;
	   count = 0;
	   free(word);
	   free(correct);
	   free(incorrect_letters);
	   fflush(stdin);
   }
   
}
   
   