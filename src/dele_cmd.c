/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-theo.vermorel
** File description:
** dele_cmd.c
*/

#include "../includes/commands.h"

void dele_cmd(server_t *server, client_t *client, char *args)
{
    char *path_from_arg;
    char *pathname;

    while (*args == ' ')
        args++;
    path_from_arg = length_till_crlf(args);
    if (!path_from_arg) {
        fill_output_buffer(client->output, ERROR_501);
        return;
    }
    pathname = realpath(path_from_arg, NULL);
    if (!pathname || strncmp(pathname, server->home, strlen(server->home)) != 0
        || remove(pathname) < 0) {
        fill_output_buffer(client->output, ERROR_550);
    } else {
        fill_output_buffer(client->output, CODE_250);
    }
    free(path_from_arg);
}
