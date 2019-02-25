/*
* The statistics of words and frequency of a text.
* For example:
* "I am a Chinese, and you are a Chinese too."    
* => “I, 1”-> “am, 1” -> “a, 2” ->“Chinese, 2” ->”You, 1”->”are, 1”->“too ,1”
*
* Date: Feb 26, 2019
* Author: Lijun SUN
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct wordcouts
{
    char *word;
    unsigned count;
    struct wordcouts *next;    
}WORDCOUNTS;


void readSentence(char *sentence)
{
    printf("Input a sentence: ");
    scanf("%[^\n]", sentence);
}

void printSentence(char *sentence, WORDCOUNTS *head)
{
    WORDCOUNTS *temp = head;
    printf("The sentence is: %s\n", sentence);
    printf("The statistics of words are: \n");
    while(temp){
        printf("%s, %u\n", temp->word, temp->count);
        temp = temp->next;
    }
    
}

WORDCOUNTS * createNewWord(unsigned wordlength)
{
    WORDCOUNTS * newWord = (WORDCOUNTS *)malloc(sizeof(WORDCOUNTS));
    if(newWord){
        newWord->word = (char *)malloc(wordlength * sizeof(char));
        newWord->count = 1;
        newWord->next = NULL;
    }  
    return newWord;
}

void copyWord(char *from, char *to, unsigned wordlength)
{
    for (unsigned idx = 0; idx < wordlength; idx++){
        *(to + idx) = *(from + idx);
    }
}

void addWord(WORDCOUNTS **head, WORDCOUNTS **tail, WORDCOUNTS *newWord)
{
    if(newWord){
        // If the linked list is empty, add at the head.
        if ((*head == NULL) && (*tail == NULL)){
            *head = newWord;
            *tail = newWord;
        } 
        else{
            // Check whether the word occurs previously.
            WORDCOUNTS *temp = *head;
            while(temp && (strcmp(temp->word, newWord->word) != 0)){
                temp = temp->next;
            }
            // If not reach the tail of the linked list, the word once occurred.
            if(temp){
                (temp->count)++;
            }
            else{
                // Otherwise, the tail is reached and add at the tail.
                (*tail)->next = newWord;
                *tail = newWord;
            }
        }
    }
}

bool isLetter(char a)
{
    if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z')){
        return true;
    } 
    return false;
}

void splitSentence(char *sentence, WORDCOUNTS **head, WORDCOUNTS **tail)
{
    WORDCOUNTS *newWord;
    char *pstart = sentence;
    unsigned wordlength = 0;
    // traverse the sentence until reach its termination symbol '\0'
    while(*sentence != '\0'){
        if (isLetter(*sentence)){
            if (wordlength++ == 0){
                pstart = sentence;
            }
        }
        else if (pstart){
            // copy the single word from the sentence
            newWord = createNewWord(wordlength);
            if(newWord){
                copyWord(pstart, newWord->word, wordlength);
                // add newWord to the linked list
                addWord(head, tail, newWord);          
                // update
                wordlength = 0;
                pstart = NULL;
            }
            else{
                printf("Fail to create a new word!");
                return;
            }         
        }
        // update
        sentence++;
    }
    if(pstart){
        // copy the last single word from the sentence
        newWord = createNewWord(wordlength);
        if(newWord){
            copyWord(pstart, newWord->word, wordlength);
            // add newWord to the linked list
            addWord(head, tail, newWord);
        }
    }
}



int main(int argc, char* arg[])
{
    char sentence[100];
    WORDCOUNTS *head = NULL, *tail = NULL;

    readSentence(sentence);
    splitSentence(sentence, &head, &tail);
    printSentence(sentence, head);

    return 0;
}
