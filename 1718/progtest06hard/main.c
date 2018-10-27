#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <ctype.h>



int compare(char *X, char *Y)
{
    while (*X && *Y)
    {
        if (*X == *Y || (*X == ' ' && *Y == '\n')) {
            X++;
            Y++;
        } else {
            return 0;
        }

    }

    return (*Y == '\0');
}

// Function to implement strstr() function
char* my_strstr(char* X, char* Y)
{
    while (*X != '\0')
    {
        if ( (*X == *Y) && compare(X, Y) )
            return X;
        X++;
    }

    return NULL;
}


char* clearDelimiters(char* input){
    char* output = (char*) malloc(strlen(input+1) * sizeof(char));
    int counter = 0, j=0, i=0;
    for (i = 0 ;  ; i++){
        if (input[i] == '\0'){
            output[counter] = '\0';
            break;
        }
       // printf("Odmazávám zbytečnosti.\n");
            if (isalpha(input[i]) || input[i] == '\n'){
                output[counter] = (char)tolower(input[i]);
              // printf("%c", output[counter]);
                counter++;
            } else {
                output[counter] = ' ';
               // printf("%c", output[counter]);
                counter++;
            }
    }

    for (i=0 ; i < strlen(output) ; i++){
       // printf("Dávám pryč mezery.\n");

        if (output[i] == ' ') {
            j = i + 1;
            while (output[j] == ' ') {
                output[j] = 1;
                j++;
            }
        }
       // printf("%c", output[i]);
    }


    return output;
}


int main() {
    long long int position=0, max = 100, questionPosition=0, counter = 0;
    char* input = NULL;
    char* ret = NULL;
    char* clearedInput = NULL;
  //  char* lookForThis = NULL;
    char* questionInput = NULL;
    int charInput, endInput = 0, lastQuestion = 0, firstSign = 0;
    printf("Text:\n");
    input = (char*) malloc(max * sizeof(char));


    while (1){
        charInput = getchar();

        if (charInput == EOF ) {
            free (input);
            printf("Nespravny vstup.\n");
            return 1;
        }

        if ((char) charInput == '\n') {
            endInput++;
        } else {
            endInput = 0;
        }

        if ( position >= max-1 ){
                max += ( max < 1000 ) ? 200 : max / 2;
                input = (char*) realloc(input, max * sizeof(char));
        }

        input[position] = (char)charInput;
        position++;


        if ( endInput == 2 && (charInput == '\n') )  break;
    }
    for (int i = 0 ; i <= position ; i++){
        input[i] = (char)tolower(input[i]);
    }

    clearedInput = clearDelimiters(input);
    free(input);
    printf("Výpis:\n%s\n",clearedInput);

    printf("Hledani:\n");



    while (1){
        max = 100;
        questionInput = (char*) malloc(max * sizeof(char));
        questionPosition = 0;
        firstSign = 1;

        for (int i = 0 ; ; i++) {
            if ( questionPosition >= max-1 ){
                max += ( max < 1000 ) ? 200 : max / 2;
                questionInput = (char*) realloc(questionInput, max * sizeof(char));
            }

            charInput = (char) getchar();
            if (charInput == '\n' || charInput == EOF ) {
                questionInput[i] = '\0';
                break;
            }
            questionInput[i] = (char) charInput;
            questionPosition++;
            firstSign = 0;
        }

        if (charInput == EOF) {
            lastQuestion = 1;
            break;
        }

        if (firstSign != 1) questionInput = clearDelimiters(questionInput);
        printf("Question input: %s\n", questionInput);
        if (strlen(questionInput) == 0){
            printf("Neplatny dotaz\n");
        } else {
        ret = NULL;
        ret = my_strstr(clearedInput, questionInput);
            if (ret == NULL){
                printf("Nenalezeno\n");
            } else {
                printf("%s\n", ret);
            }
        }
        counter = 1;
        for (int i = 0 ; clearedInput[i] != '\0' ; i++){
            if (clearedInput[i] == '\n') {counter++;
                //printf("Napočítal jsem %lld\n", counter);
            }
            if (&clearedInput[i] == ret) {
                printf("Napočítal jsem %lld\n", counter);
                break;
            }
        }

        if (lastQuestion){
            printf("Proběhl last question.\n");
            break;
        }
        free(questionInput);
    }



    free(clearedInput);
    free(questionInput);
    return 0;
}