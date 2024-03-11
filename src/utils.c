/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-theo.vermorel
** File description:
** utils.c
*/

#include "../includes/commands.h"

int length_2d_arr(char **arr)
{
    int count = 0;

    for (int i = 0; arr[i]; i++)
        count++;
    return count;
}

void free_2d_arr(char **arr)
{
    if (!arr)
        return;
    for (int i = 0; arr[i]; i++) {
        if (arr[i])
            free(arr[i]);
    }
    free(arr);
}

char *length_till_crlf(char *str)
{
    int len = 0;
    char *dest = NULL;

    while (str[len] != '\r')
        len++;
    if (len > 0) {
        dest = malloc(sizeof(char) * (len + 1));
        memset(dest, 0, len + 1);
        strncpy(dest, str, len);
        dest[len + 1] = 0;
    }
    return dest;
}

char **my_str_to_word_array(char *str, char *delimiter)
{
    char **word_array = NULL;
    char *token = NULL;
    int count = 0;

    token = strtok(str, delimiter);
    while (token != NULL) {
        word_array = realloc(word_array, sizeof(char *) * (count + 2));
        word_array[count] = malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(word_array[count], token);
        count++;
        token = strtok(NULL, delimiter);
    }
    word_array[count] = NULL;
    return word_array;
}

bool only_spaces(char *args)
{
    bool only_spaces = true;
    int i = 0;

    while (args[i] != '\r') {
        if (args[i] != ' ') {
            only_spaces = false;
            break;
        }
        i++;
    }
    return only_spaces;
}
