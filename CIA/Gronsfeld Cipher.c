#include <stdio.h>
#include <string.h>
#include <ctype.h>

void gronsfeldEncrypt(char *text, char *key) {
    int keyLen = strlen(key);
    for (int i = 0, j = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            int shift = key[j % keyLen] - '0';
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base + shift) % 26 + base;
            j++;
        }
    }
}

void gronsfeldDecrypt(char *text, char *key) {
    int keyLen = strlen(key);
    for (int i = 0, j = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            int shift = key[j % keyLen] - '0';
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base - shift + 26) % 26 + base;
            j++;
        }
    }
}

int main() {
    char message[100];
    char key[100];

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    printf("Enter numeric key (e.g., 31415): ");
    scanf("%s", key);

    gronsfeldEncrypt(message, key);
    printf("Encrypted: %s\n", message);

    gronsfeldDecrypt(message, key);
    printf("Decrypted: %s\n", message);

    return 0;
}
