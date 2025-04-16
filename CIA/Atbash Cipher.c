#include <stdio.h>
#include <ctype.h>
#include <string.h>

void atbash(char *text) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            if (isupper(text[i]))
                text[i] = 'Z' - (text[i] - 'A');
            else
                text[i] = 'z' - (text[i] - 'a');
        }
    }
}

int main() {
    char text[100];

    printf("Enter message: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    atbash(text);
    printf("Encrypted: %s\n", text);

    atbash(text);  // reversible
    printf("Decrypted: %s\n", text);

    return 0;
}
