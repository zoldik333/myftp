/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-theo.vermorel
** File description:
** error_handling.c
*/

#include "../includes/server.h"

static void free_inner_members(server_t *server)
{
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (server->clients[i].curr_wd != NULL)
            free(server->clients[i].curr_wd);
    }
}

int check(int ret_code, server_t *server, const char *msg)
{
    if (ret_code != SOCKET_ERROR) {
        return ret_code;
    }
    perror(msg);
    if (server) {
        free_inner_members(server);
        free(server->clients);
        if (server->home)
            free(server->home);
        free(server);
    }
    exit(EXIT_ERROR);
}
