#include <stdio.h>
#include <ctype.h>
#include <string.h>

void augustCipher(char *text) {
    int key = 8;
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base + key) % 26 + base;
        }
    }
}

void decryptAugust(char *text) {
    int key = 8;
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base - key + 26) % 26 + base;
        }
    }
}

int main() {
    char text[100];

    printf("Enter message: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    augustCipher(text);
    printf("Encrypted: %s\n", text);

    decryptAugust(text);
    printf("Decrypted: %s\n", text);

    return 0;
}
