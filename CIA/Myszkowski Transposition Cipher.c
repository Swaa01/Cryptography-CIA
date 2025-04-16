#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 200

// Structure for key indexing
typedef struct {
    char ch;
    int index;
    int orig_pos;
} KeyChar;

int compareKeyChars(const void *a, const void *b) {
    KeyChar *k1 = (KeyChar *)a;
    KeyChar *k2 = (KeyChar *)b;

    if (k1->ch == k2->ch)
        return k1->orig_pos - k2->orig_pos;
    return k1->ch - k2->ch;
}

void toUpperStr(char *s) {
    for (int i = 0; s[i]; i++)
        s[i] = toupper(s[i]);
}

void encryptMyszkowski(char *text, char *key, char *cipher) {
    int len = strlen(text);
    int klen = strlen(key);

    // Pad text with X to fit the matrix
    while (len % klen != 0) {
        text[len++] = 'X';
        text[len] = '\0';
    }

    int rows = len / klen;
    char matrix[rows][klen];

    // Fill matrix row-wise
    int idx = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < klen; j++)
            matrix[i][j] = text[idx++];

    // Prepare key order
    KeyChar karr[klen];
    for (int i = 0; i < klen; i++) {
        karr[i].ch = key[i];
        karr[i].index = i;
        karr[i].orig_pos = i;
    }

    qsort(karr, klen, sizeof(KeyChar), compareKeyChars);

    // Extract encryption based on key order
    idx = 0;
    for (int i = 0; i < klen;) {
        char current = karr[i].ch;

        // Gather all positions with the same character
        for (int j = 0; j < klen; j++) {
            if (karr[j].ch == current) {
                for (int r = 0; r < rows; r++)
                    cipher[idx++] = matrix[r][karr[j].orig_pos];
            }
        }

        // Move to next unique character
        while (i < klen && karr[i].ch == current)
            i++;
    }

    cipher[idx] = '\0';
}

int main() {
    char text[MAX_LEN], key[MAX_LEN], cipher[MAX_LEN];

    printf("Enter the plaintext (no spaces): ");
    scanf("%s", text);
    printf("Enter the key (e.g., BALLOON): ");
    scanf("%s", key);

    toUpperStr(text);
    toUpperStr(key);

    encryptMyszkowski(text, key, cipher);

    printf("Encrypted (Myszkowski): %s\n", cipher);

    return 0;
}
