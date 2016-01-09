// problems: words that are too long are being output, especially with a lot of blanks input

// given an input of letters, computes the best possible play in Scrabble

#include <stdio.h>
#include <string.h>

int getValue(char word[], int values[]);
int hasLetters(char letters[], char word[], int numBlanks);
void findLetterFreq(char string[], int freq[]);
void findWordFreq(char string[], int freq[]);
void printWord(char word[]);
void printArray(int array[]);
int enoughLetters(int letterFreq[], int wordFreq[], int numBlanks);
void set_to_0(int array[]);
void getLetters(char letters[], char *let, int *numBlanks);
int hasLet(char let, char word[]);

int main()
{
   // initializes variables
   char letters[9];
   char word[50];
   char let; // letter that word intersects with (must be used)
   int values[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10}; // Scrabble letter values

   // sets up file pointer
   FILE *ifp;
   ifp = fopen("scrabble.txt", "r");

   int i=0, j;
   int max=0;
   char bestWord[50];
   int value=0;
   int numBlanks = 0;
   int row = 0; // keeps track of the row in the output

   int letterFreq[26] = {0};
   int wordFreq[26] = {0};

   system("clear");
   printf("---------------------\n");
   printf("-SCRABBLE CALCULATOR-\n");
   printf("---------------------\n\n");

   getLetters(letters, &let, &numBlanks); // get letters from user
   findLetterFreq(letters, letterFreq); // find frequency of each letter given

   printf("\nPossible Words:\n");
   
   // checks through all words
   while(!feof(ifp))
   {
      fgets(word, 49, ifp);

      if(hasLet(let, word)) // checks if the word has the letter to be intersected
      {
         if(hasLetters(letters, word, numBlanks)) // checks we have all the letters for the word
         {
            set_to_0(wordFreq);
            findWordFreq(word, wordFreq);

            if(enoughLetters(letterFreq, wordFreq, numBlanks)) // checks if we have enough of each letter
            {
               row++;
               printWord(word);
               if(row%8 == 0)
                  printf("\n");

               value = getValue(word, values);
               if(value > max)
               {
                  max = value;
                  strcpy(bestWord, word);
               }
            }
         }
     }

      i++; 
   }

   printf("\n\nBest word is: ");
   printWord(bestWord);
   printf("\nIt will get you %d points\n\n", max);
}

// returns scrabble value of a word
int getValue(char word[], int values[])
{
   int i=0;
   int value=0;

   while(isalpha(word[i]))
   {
      value += values[word[i]-'a'];
      i++;
   }
   return value;
}

// checks if we have the letters to make the word
int hasLetters(char letters[], char word[], int numBlanks)
{
   int i, j;
   int found;
   int blanksUsed = 0;

   for(i=0; i<strlen(word); i++) // for each letter in the word
   {
      found=0;
      for(j=0; j<strlen(letters); j++) // for each letter you have
      {
         if(word[i] == letters[j])
         {
            found = 1;
            break;
         }
      }

      if(!found && isalpha(word[i])) // fixes problem of \n's at the ends of words
      {
         blanksUsed+=1;
         if(blanksUsed > numBlanks)
         {
            return 0;
         }
      }
   }
   return 1;
}

// finds frequency of each letter we have in a word in a 26 entry array
void findLetterFreq(char string[], int freq[])
{
   int i;
   for(i=0; i<strlen(string); i++)
   {
      freq[string[i] - 'a']++;
   }
}

// finds letter frequency of the word
void findWordFreq(char string[], int freq[])
{
   int i;
   for(i=0; i<strlen(string)-1; i++)
   {
      freq[string[i] - 'a']++;
   }
}

void printWord(char word[])
{
   int j;
   for(j=0; j<strlen(word); j++)
   {
      if(isalpha(word[j]))
         printf("%c", word[j]);
   }
   printf("\t");
}

void printArray(int array[])
{
   int i;
   for(i=0; i<26; i++)
   {
      printf("%d, ", array[i]);
   }
}

// checks to make sure we have enough of each letter to make the word
int enoughLetters(int letterFreq[], int wordFreq[], int numBlanks)
{
   int blanksUsed = 0;
   int i;
   for(i=0; i<26; i++)
   {
      if(wordFreq[i] > letterFreq[i])
      {
         blanksUsed += 1;
         if(blanksUsed > numBlanks)
            return 0;
      }
   }
   return 1;
}

void set_to_0(int array[])
{
   int i;
   for(i=0; i<26; i++)
   {
      array[i] = 0;
   }
}

// lets user enter things to begin the program
void getLetters(char letters[], char *let, int *numBlanks)
{
   char garbage; // traps \n
   char enteredLetters[9]; // it might have to be this long

   printf("Enter your letters (enter '_' for blanks): ");
   scanf("%s", enteredLetters);
   scanf("%c", &garbage);

   int i, j=0;

   // sets entire letters array to null character (this fixed a bug?)
   for(i=0; i<9; i++)
   {
      letters[i] = '\0';
   }

   for(i=0; i<strlen(enteredLetters); i++)
   {
      if(enteredLetters[i] == '_')
      {
         *numBlanks += 1;
      }
      else if(isalpha(enteredLetters[i])) 
      {
         letters[j] = enteredLetters[i];
         j++;
      }
   }

   printf("\nnumBlanks: %d\n", *numBlanks);

   printf("Enter the letter your word will intersect with: ");

   // necessary to do this? without it there is a bug
   char c; 
   scanf("%c", &c);
   *let = c;

   letters[strlen(letters)] = *let;
   letters[strlen(letters)] = '\0'; // strlen(letters) is incremented previously
   printf("\nstrlen letters: %d\n", strlen(letters));
}

// checks to see if our certain letter is contained in a word
int hasLet(char let, char word[])
{
   int i;
   for(i=0; i<strlen(word)-1; i++) // for each letter in the word
   {
      if(word[i] == let)
      {
         return 1;
      }
   }
   return 0;
}

