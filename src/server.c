/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-theo.vermorel
** File description:
** server.c
*/

#include "../includes/server.h"


server_t *setup_server(uint16_t port, char *home)
{
    char *tmp_path;
    server_t *server = malloc(sizeof(server_t));

    check((server->fd = socket(AF_INET, SOCK_STREAM, 0)), server, "Socket");
    tmp_path = realpath(home, NULL);
    check((tmp_path != NULL ? 0 : -1), server,
        "Wrong path");
    server->home = strdup(tmp_path);
    server->clients = malloc(sizeof(client_t) * MAX_CLIENTS);
    memset(server->clients, 0, sizeof(client_t) * MAX_CLIENTS);
    server->count = 0;
    memset(&server->addr, 0, sizeof(server->addr));
    server->addr.sin_family = AF_INET;
    server->addr.sin_port = htons(port);
    server->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    check(bind(server->fd, (struct sockaddr *) &server->addr,
        sizeof(server->addr)), server, "Bind server socket");
    check(listen(server->fd, MAX_CLIENTS), server, "Listen server socket");
    return server;
}
