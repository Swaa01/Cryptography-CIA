#include <stdio.h>
#include <string.h>

void generateNGrams(char *text, int n) {
    int len = strlen(text);

    printf("%d-grams:\n", n);
    for (int i = 0; i <= len - n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%c", text[i + j]);
        }
        printf("\n");
    }
}

int main() {
    char message[200];
    int n;

    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    printf("Enter value of n for N-grams (e.g., 2 or 3): ");
    scanf("%d", &n);

    generateNGrams(message, n);

    return 0;
}
