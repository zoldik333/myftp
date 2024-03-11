/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-theo.vermorel
** File description:
** retr_stor.c
*/

#include "../includes/commands.h"

char *pathname_has_error(client_t *client, char *args, char *home)
{
    char *path_from_arg;
    char *pathname;

    while (*args == ' ')
        args++;
    path_from_arg = length_till_crlf(args);
    if (!path_from_arg) {
        fill_output_buffer(client->output, ERROR_501);
        return NULL;
    }
    pathname = realpath(path_from_arg, NULL);
    free(path_from_arg);
    if (!pathname || strncmp(pathname, home, strlen(home)) != 0) {
        fill_output_buffer(client->output, ERROR_550);
        return NULL;
    }
    return pathname;
}

void retr_fork(int fd, client_t *client)
{
    pid_t pid;
    char buffer[BUFFER_SIZE] = {0};

    accept_connection(client);
    pid = fork();
    if (pid == 0) {
        while (read(fd, buffer, BUFFER_SIZE)) {
            write(client->data.accept_fd, buffer, strlen(buffer));
        }
        close(fd);
        close(client->data.accept_fd);
        exit(0);
    }
    close(client->data.accept_fd);
    fill_output_buffer(client->output, CODE_226);
}

void retr_cmd(server_t *server, client_t *client, char *args)
{
    int fd;
    char *pathname;

    if (!check_connection(client))
        return;
    pathname = pathname_has_error(client, args, server->home);
    if (!pathname) {
        fill_output_buffer(client->output, ERROR_550);
        return;
    }
    fd = open(pathname, O_RDONLY, "r");
    if (fd == -1) {
        fill_output_buffer(client->output, ERROR_550);
        return;
    }
    fill_output_buffer(client->output, CODE_150);
    retr_fork(fd, client);
    client->data.mode = NO_CONNECTION;
    FD_CLR(client->data.data_fd, &server->curr_read_fds);
    free(pathname);
}
