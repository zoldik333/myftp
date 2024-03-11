/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-theo.vermorel
** File description:
** files.c
*/

#include "../includes/commands.h"

char **get_list_args(char *args)
{
    int count = 1;
    char **list_args;
    char **tmp;

    list_args = malloc(sizeof(char *) * (MAX_ARGS + 1));
    memset(list_args, 0, MAX_ARGS + 1);
    list_args[0] = strdup("ls");
    tmp = my_str_to_word_array(args, " \n\r");
    for (int i = 0; tmp[i]; i++) {
        list_args[count] = strdup(tmp[i]);
        count++;
    }
    list_args[count] = NULL;
    free_2d_arr(tmp);
    return list_args;
}

char **check_path_list_args(char **arr, char *home)
{
    char *tmp = NULL;

    for (int i = 1; arr[i]; i++) {
        tmp = realpath(arr[i], NULL);
        if (!tmp) {
            continue;
        }
        if (strncmp(tmp, home, strlen(home)) != 0) {
            free_2d_arr(arr);
            free(tmp);
            return NULL;
        }
        free(tmp);
    }
    return arr;
}

char **get_list_args_condition(char *args, char *home)
{
    char **list_args = NULL;

    if (only_spaces(args)) {
        list_args = get_list_args(".");
    } else {
        list_args = get_list_args(args);
    }
    return list_args;
}

void list_fork(client_t *client, char **list_args)
{
    pid_t pid;

    accept_connection(client);
    pid = fork();
    if (pid == 0) {
        dup2(client->data.accept_fd, 1);
        dup2(client->data.accept_fd, 2);
        execvp("ls", list_args);
    }
    close(client->data.accept_fd);
    fill_output_buffer(client->output, CODE_226);
}

void list_cmd(server_t *server, client_t *client, char *args)
{
    char **list_args;

    if (!check_connection(client))
        return;
    fill_output_buffer(client->output, CODE_150);
    list_args = get_list_args_condition(args, server->home);
    list_fork(client, list_args);
    client->data.mode = NO_CONNECTION;
    FD_CLR(client->data.data_fd, &server->curr_read_fds);
}
