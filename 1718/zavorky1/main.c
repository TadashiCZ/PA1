
#include <stdio.h>
#include <assert.h>
#include <memory.h>

#define ERROR -1;


int max(const char *str) {
    int max = 0, score = 0;
//Check for errors
    for (int i = 0; i < (int) strlen(str); i++) {
        if (str[i] != ')' && str[i] != '(') return ERROR;
    }

// Find max size
    for (int i = 0; i < (int) strlen(str) - 1; i++) {
        if (str[i] == '(') {
            for (int j = i; j < (int) strlen(str); j++) {

                if (str[j] == ')') {
                    score--;
                } else if (str[j] == '(') {
                    score++;
                }

                if (score == 0) {
                    max = (j - i + 1) > max ? (j - i + 1) : max;
                } else if (score < 0) {
                    break;
                }
            }
        }
    }
    // printf("Return is %d\n", max);
    return max;
}


int main() {
    assert (max("()()") == 4);   // nejdelsi od indexu 0 po index 3
    assert (max("))())") == 2);  // nejdelsi od indexu 2 po index 3
    assert (max("()()()()") == 8);  // nejdelsi od indexu 0 po index 7
    assert (max("(()())()") == 8);  // nejdelsi od indexu 0 po index 7
    assert (max(")((((") == 0);   // nevyskytuje se usek se spravnym uzavorkovanim
    assert (max(")o(((") == -1);  // jiny znak




    return 0;
}
