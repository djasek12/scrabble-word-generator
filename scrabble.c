// given an input of letters, computes the best possible play in Scrabble

#include <stdio.h>
#include <string.h>

//void getWords(char words[178693][50]);
int getValue(char word[], int values[]);
int hasLetters(char letters[], char word[]);
void findLetterFreq(char string[], int freq[]);
void findWordFreq(char string[], int freq[]);
void printWord(char word[]);
void printArray(int array[]);
int enoughLetters(int letterFreq[], int wordFreq[]);
void set_to_0(int array[]);
void getLetters(char letters[], char *let);
int hasLet(char let, char word[]);

int main()
{
   // initializes variables
   char letters[9];
   char word[50];
   char let; // letter that word intersects with (must be used)
   int values[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

   FILE *ifp;
   ifp = fopen("scrabble.txt", "r");

   int i=0, j;
   int max=0;
   char bestWord[50];
   int value=0;

   int letterFreq[26] = {0};
   int wordFreq[26] = {0};

   system("clear");
   printf("---------------------\n");
   printf("-SCRABBLE CALCULATOR-\n");
   printf("---------------------\n\n");

   getLetters(letters, &let);
   findLetterFreq(letters, letterFreq);

   printf("\nPossible Words:\n");
   
   // checks through all words
   while(!feof(ifp))
   {
      fgets(word, 49, ifp);

      if(hasLet(let, word))
      {
         if(hasLetters(letters, word))
         {
            set_to_0(wordFreq);
            findWordFreq(word, wordFreq);

            if(enoughLetters(letterFreq, wordFreq))
            {
               printWord(word);

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

   printf("\nBest word is: ");
   printWord(bestWord);
   printf("It will get you %d points\n\n\n", max);
}

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

int hasLetters(char letters[], char word[])
{
   int i, j;
   int found;
   for(i=0; i<strlen(word)-1; i++) // for each letter in the word
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
      if(!found)
         return 0;
   }
   return 1;
}

void findLetterFreq(char string[], int freq[])
{
   int i;
   for(i=0; i<strlen(string); i++)
   {
      freq[string[i] - 'a']++;
   }
}

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
      printf("%c", word[j]);
   }
}

void printArray(int array[])
{
   int i;
   for(i=0; i<26; i++)
   {
      printf("%d, ", array[i]);
   }
}

int enoughLetters(int letterFreq[], int wordFreq[])
{
   int i;
   for(i=0; i<26; i++)
   {
      if(wordFreq[i] > letterFreq[i])
      {
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

void getLetters(char letters[], char *let)
{
   char garbage; // traps \n
   printf("Enter your 7 letters: ");
   scanf("%s", letters);
   scanf("%c", &garbage);
   printf("Enter the letter your word will intersect with: ");
   scanf("%c", let); 

   letters[7] = *let;
   letters[8] = '\0';
}

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

