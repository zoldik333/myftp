/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-theo.vermorel
** File description:
** client.c
*/

#include "../includes/commands.h"

void place_client(server_t *server, client_t *client)
{
    for (int i = 0; i < server->count; i++) {
        if (server->clients[i].fd == 0) {
            server->clients[i] = *client;
            FD_SET(server->clients[i].fd, &server->curr_read_fds);
            FD_SET(server->clients[i].fd, &server->write_fds);
            break;
        }
    }
}

void handle_new_client(server_t *server)
{
    client_t client;
    socklen_t addr_len = sizeof(client.addr);

    memset(&client, 0, sizeof(client_t));
    check((client.fd = accept(server->fd, (struct sockaddr*)&client.addr,
        &addr_len)), server, "Accept error");
    server->count += 1;
    fill_output_buffer(client.output, CODE_220);
    client.curr_wd = strdup(server->home);
    place_client(server, &client);
}

void logout_client(server_t *server, int index)
{
    client_t *client = &server->clients[index];

    FD_CLR(client->fd, &server->curr_read_fds);
    close(client->fd);
    memset(client, 0, sizeof(client_t));
    memset(&client->data, 0, sizeof(data_t));
    memset(&client->addr, 0, sizeof(struct sockaddr_in));
    server->count -= 1;
}

void handle_read_client(server_t *server, int index)
{
    char *cmd = NULL;

    if (!read_cmd(&server->clients[index])) {
        logout_client(server, index);
        return;
    }
    cmd = parse_cmd(&server->clients[index]);
    if (cmd) {
        chdir(server->clients[index].curr_wd);
        exec_cmd(server, &server->clients[index], cmd);
        FD_SET(server->clients[index].fd, &server->write_fds);
        free(cmd);
    }
}

void handle_write_client(server_t *server, int index)
{
    check(write(server->clients[index].fd, server->clients[index].output,
                strlen(server->clients[index].output)), server, "Write error");
    memset(server->clients[index].output, 0, BUFFER_SIZE);
    FD_CLR(server->clients[index].fd, &server->write_fds);
}
