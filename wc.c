#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>

// function to count number of bytes
int bytesCounter(FILE *fileptr)
{
    int byte_count = 0;
    char ch;
    while ((ch = fgetc(fileptr)) != EOF)
    {
        byte_count++;
    }
    return byte_count;
}

// function to count number of lines
int lineCounter(FILE *fileptr)
{
    int line_count = 0;
    char ch;
    while ((ch = fgetc(fileptr)) != EOF)
    {
        if (ch == '\n')
        {
            line_count++;
        }
    }
    return line_count;
}

// function to count number of words
int wordCounter(FILE *fileptr)
{
    int word_count = 0;
    char ch;
    char str[1024];
    int inside_word = 0;
    while ((fgets(str, sizeof(str), fileptr)) != NULL)
    {
        for (int i = 0; i < sizeof(str); i++)
        {
            if (str[i] == '\0')
            {
                break;
            }
            else
            {
                if (isspace(str[i]))
                {
                    inside_word = 0;
                }
                else if (!inside_word)
                {
                    word_count++;
                    inside_word = 1;
                }
            }
        }
    }
    return word_count;
}

// function to count number of characters (multibyte and single byte)
int charCounter(FILE *fileptr)
{
    int count = 0;
    wint_t wc;
    mbstate_t state = {0};
    setlocale(LC_ALL, "");

    while ((wc = fgetwc(fileptr)) != WEOF)
    {
        count++;
    }
    return count;
}

int main(int argc, char *argv[])
{
    if (argc == 2) // when there's just filename or just options
    {
        if (argv[1][0] == '-') // if we have to read from standard input
        {
            char option = argv[1][1];
            if (option == 'm')
            {
                int nc = 0;
                wint_t wc;
                mbstate_t state = {0};
                setlocale(LC_ALL, "");

                while ((wc = getwchar()) != WEOF)
                {
                    nc++;
                }
                printf("%d\n", nc);
            }
            else
            {
                int nl, nw, nb, inside_word = 0;
                nl = nw = nb = 0;
                char ch;
                while ((ch = getchar()) != EOF)
                {
                    nb++;
                    if (ch == '\n')
                        nl++;
                    if (isspace(ch))
                    {
                        inside_word = 0;
                    }
                    else if (!inside_word)
                    {
                        nw++;
                        inside_word = 1;
                    }
                }

                if (option == 'c')
                {
                    printf("%d\n", nb);
                }
                else if (option == 'l')
                {
                    printf("%d\n", nl);
                }
                else if (option == 'w')
                {
                    printf("%d\n", nw);
                }
                else
                {
                    printf("Invalid option.\n");
                }
            }
        }
        else // if only filename is given
        {
            char *filename = argv[1];
            FILE *fileptr = fopen(filename, "r");

            if (fileptr == NULL)
            {
                printf("Could not open the file.\n");
                return 1;
            }

            int number_of_bytes = bytesCounter(fileptr);
            rewind(fileptr);
            int number_of_lines = lineCounter(fileptr);
            rewind(fileptr);
            int number_of_words = wordCounter(fileptr);

            printf("%d %d %d %s\n", number_of_lines, number_of_words, number_of_bytes, filename);
            fclose(fileptr);
        }
    }
    else if (argc == 3) // when we have filename and options
    {
        char *op = argv[1];
        char option = op[1];
        char *filename = argv[2];
        FILE *fileptr = fopen(filename, "r");

        if (fileptr == NULL)
        {
            printf("Could not open the file.\n");
            return 1;
        }

        switch (option)
        {
        case 'c':
            int number_of_bytes = bytesCounter(fileptr);
            printf("%d %s\n", number_of_bytes, filename);
            break;

        case 'l':
            int number_of_lines = lineCounter(fileptr);
            printf("%d %s\n", number_of_lines, filename);
            break;

        case 'w':
            int number_of_words = wordCounter(fileptr);
            printf("%d %s\n", number_of_words, filename);
            break;

        case 'm':
            int number_of_chars = charCounter(fileptr);
            printf("%d %s\n", number_of_chars, filename);
            break;

        default:
            printf("Invalid command line argument.\n");
            break;
        }

        fclose(fileptr);
        return 0;
    }
}