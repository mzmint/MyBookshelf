#include <stdio.h>
#include <string.h>
#include <stdlib.h>

_Bool Validate(char day[], char month[], char year[]) {
    char* endptr;

    if (strcmp(month, "4") == 0 || strcmp(month, "6") == 0 || strcmp(month, "9") == 0 || strcmp(month, "11") == 0) {
        if (strtol(day, &endptr, 10) <= 30 && strtol(day, &endptr, 10) >= 1) return 1;
        return 0;
    }

    if (strcmp(month, "2") == 0) {
        int d = strtol(day, &endptr, 10);
        int y = strtol(year, &endptr, 10);

        _Bool isLeap = (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0));

        if (d >= 1 && d <= (isLeap ? 29 : 28)) return 1;
        return 0;
    }

    else {
        if (strtol(day, &endptr, 10) <= 31 && strtol(day, &endptr, 10) >= 1) return 1;
        return 0;
    }
}

int main(void) {
    _Bool isQuit = 0;
    _Bool isValid = 0;
    _Bool isDateValid = 0;

    char name[256];
    char author[256];
    char day[4];
    char month[4];
    char year[7];
    char command[8];
    char isbn[20];

    char* endptr;

    char bookshelf[256];

    printf("Enter bookshelf name: \n");
    fgets(bookshelf, sizeof(bookshelf), stdin);
    bookshelf[strcspn(bookshelf, "\n")] = '\0';

    FILE *file = fopen(strcat(bookshelf, ".csv"), "a+");

    if (file == NULL) {
        printf("Error creating file!\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);

    if (ftell(file) == 0) {
        fprintf(file, "Name,Author,DD,MM,YYYY,ISBN\n");
    }

    while (!isQuit) {

        printf("Enter book name: \n");
        if (fgets(name, sizeof(name), stdin) == NULL) break;
        name[strcspn(name, "\n")] = '\0';

        printf("Enter book author: \n");
        if (fgets(author, sizeof(author), stdin) == NULL) break;
        author[strcspn(author, "\n")] = '\0';
        while (!isDateValid) {

            isValid = 0;
            while (!isValid) {
                printf("Enter day made: \n");
                if (fgets(day, sizeof(day), stdin) == NULL) return 1;
                day[strcspn(day, "\n")] = '\0';

                if (strtol(day, &endptr, 10) > 31 ||
                    strtol(day, &endptr, 10) < 1)
                    isValid = 0;
                else isValid = 1;

                if (!isValid) printf("Invalid Day\n");
            }

            isValid = 0;
            while (!isValid) {
                printf("Enter month made: \n");
                if (fgets(month, sizeof(month), stdin) == NULL) return 1;
                month[strcspn(month, "\n")] = '\0';

                if (strtol(month, &endptr, 10) > 12 ||
                    strtol(month, &endptr, 10) < 1)
                    isValid = 0;
                else isValid = 1;

                if (!isValid) printf("Invalid Month\n");
            }

            isValid = 0;
            while (!isValid) {
                printf("Enter year made: \n");
                if (fgets(year, sizeof(year), stdin) == NULL) return 1;
                year[strcspn(year, "\n")] = '\0';

                if (strtol(year, &endptr, 10) > 2099 ||
                    strtol(year, &endptr, 10) < -9999)
                    isValid = 0;
                else isValid = 1;

                if (!isValid) printf("Invalid Year\n");
            }

            if (Validate(day, month, year)) {
                isDateValid = 1;
            }
            else {
                printf("Invalid date! Please try again.\n");
                isValid = 0;
            }
        }
        printf("Enter ISBN: \n");
        if (fgets(isbn, sizeof(isbn), stdin) == NULL) break;
        isbn[strcspn(isbn, "\n")] = '\0';

        fprintf(file, "%s,%s,%s,%s,%s,%s\n",
            name, author, day, month, year, isbn);

        printf("Book added!\n");

        printf("Quit? [Y/n]: ");
        if (fgets(command, sizeof(command), stdin) == NULL) break;
        if (command[0] == 'Y' || command[0] == 'y') isQuit = 1;
    }

    fclose(file);

    printf("Bookshelf saved successfully!\n");

    return 0;
}