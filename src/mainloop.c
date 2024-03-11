/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-theo.vermorel
** File description:
** mainloop.c
*/

#include "../includes/server.h"

static void loop_fds(server_t *server)
{
    if (FD_ISSET(server->fd, &server->read_fds)) {
        handle_new_client(server);
    }
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (FD_ISSET(server->clients[i].fd, &server->read_fds)) {
            handle_read_client(server, i);
        }
        if (FD_ISSET(server->clients[i].fd, &server->write_fds)) {
            handle_write_client(server, i);
        }
    }
}

int mainloop(char *argv[])
{
    server_t *server = setup_server(atol(argv[1]), argv[2]);

    FD_ZERO(&server->curr_read_fds);
    FD_ZERO(&server->write_fds);
    FD_SET(server->fd, &server->curr_read_fds);
    while (1) {
        server->read_fds = server->curr_read_fds;
        check(select(FD_SETSIZE + 1, &server->read_fds, &server->write_fds,
            NULL, NULL), server, "Select error");
        loop_fds(server);
    }
    return EXIT_SUCCESS;
}
