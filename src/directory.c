/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-theo.vermorel
** File description:
** directory.c
*/

#include "../includes/commands.h"

void cwd_cmd(server_t *server, client_t *client, char *args)
{
    char *path_from_arg;
    char *pathname;

    while (*args == ' ')
        args++;
    path_from_arg = length_till_crlf(args);
    if (!path_from_arg) {
        fill_output_buffer(client->output, ERROR_550);
        return;
    }
    pathname = realpath(path_from_arg, NULL);
    if (!pathname || strncmp(pathname, server->home, strlen(server->home)) != 0
        || chdir(pathname) == -1) {
        fill_output_buffer(client->output, ERROR_550);
    } else {
        client->curr_wd = strdup(pathname);
        fill_output_buffer(client->output, CODE_250);
    }
    free(path_from_arg);
}

void cdup_cmd(server_t *server, client_t *client, char *args)
{
    char *pathname;

    if (!only_spaces(args)) {
        fill_output_buffer(client->output, ERROR_550);
        return;
    }
    pathname = realpath("..", NULL);
    if (!pathname || strncmp(pathname, server->home, strlen(server->home)) != 0
        || chdir(pathname) == -1) {
        fill_output_buffer(client->output, ERROR_550);
    } else {
        client->curr_wd = strdup(pathname);
        fill_output_buffer(client->output, CODE_200);
    }
}

void pwd_cmd(server_t *server, client_t *client, char *args)
{
    if (!only_spaces(args)) {
        fill_output_buffer(client->output, ERROR_501);
    } else {
        fill_output_buffer(client->output, CODE_257);
        fill_output_buffer(client->output, client->curr_wd);
        fill_output_buffer(client->output, CODE_257_2);
    }
}
