#include <cs50.h>
#include <stdio.h>
#include <string.h>


int main(void)
{
    FILE *file = fopen("phonebook.csv", "a"); // a for append , w for write, r for read
    if (file == NULL)
    {
        return 1;
    }

    char *name = get_string("Name: ");
    char *number = get_string("Number: ");

    fprintf(file, "%s,%s\n", name, number);
    fclose(file);
    return 0;
}
