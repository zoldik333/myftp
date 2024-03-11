/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-theo.vermorel
** File description:
** stor_cmd.c
*/

#include "../includes/commands.h"

void stor_fork(char *path, client_t *client)
{
    FILE *fd;
    pid_t pid;
    char buffer[BUFFER_SIZE] = {0};

    accept_connection(client);
    pid = fork();
    if (pid == 0) {
        fd = fopen(path, "w");
        while (read(client->data.accept_fd, buffer, BUFFER_SIZE)) {
            fwrite(&buffer, strlen(buffer), 1, fd);
        }
        fclose(fd);
        close(client->data.accept_fd);
        exit(0);
    }
    close(client->data.accept_fd);
}

void stor_cmd(server_t *server, client_t *client, char *args)
{
    char *path_from_arg;

    if (!check_connection(client))
        return;
    while (*args == ' ')
        args++;
    path_from_arg = length_till_crlf(args);
    if (!path_from_arg) {
        fill_output_buffer(client->output, ERROR_501);
        return;
    }
    fill_output_buffer(client->output, CODE_150);
    stor_fork(path_from_arg, client);
    fill_output_buffer(client->output, CODE_226);
    FD_CLR(client->data.data_fd, &server->curr_read_fds);
    free(path_from_arg);
}
