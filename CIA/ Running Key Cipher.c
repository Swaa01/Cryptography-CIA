#include <stdio.h>
#include <string.h>
#include <ctype.h>

void autokeyEncrypt(char *text, char *key) {
    int textLen = strlen(text);
    int keyLen = strlen(key);
    char fullKey[200];

    // Create full key: original key + plaintext (up to length of text)
    int j = 0;
    for (int i = 0; i < keyLen; i++)
        fullKey[j++] = toupper(key[i]);
    for (int i = 0; j < textLen; i++) {
        if (isalpha(text[i]))
            fullKey[j++] = toupper(text[i]);
    }

    for (int i = 0, k = 0; i < textLen; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            int shift = fullKey[k++] - 'A';
            text[i] = (text[i] - base + shift) % 26 + base;
        }
    }
}

void autokeyDecrypt(char *text, char *key) {
    int textLen = strlen(text);
    int keyLen = strlen(key);
    char recoveredKey[200];

    // Copy original key
    for (int i = 0; i < keyLen; i++)
        recoveredKey[i] = toupper(key[i]);

    for (int i = 0, k = 0; i < textLen; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            int keyChar = recoveredKey[k] - 'A';
            int ptChar = (text[i] - base - keyChar + 26) % 26;
            char plainChar = ptChar + base;
            text[i] = plainChar;
            recoveredKey[keyLen + k] = toupper(plainChar);  // build up key
            k++;
        }
    }
}

int main() {
    char message[100];
    char key[100];

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    printf("Enter keyword: ");
    scanf("%s", key);

    autokeyEncrypt(message, key);
    printf("Encrypted: %s\n", message);

    autokeyDecrypt(message, key);
    printf("Decrypted: %s\n", message);

    return 0;
}
