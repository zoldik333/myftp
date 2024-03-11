/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-theo.vermorel
** File description:
** check_connection.c
*/

#include "../includes/commands.h"

void accept_connection(client_t *client)
{
    socklen_t len;

    len = sizeof(client->data.addr);
    if (client->data.mode == PASV) {
        client->data.accept_fd = accept(client->data.data_fd,
            (struct sockaddr*)&client->data.addr, &len);
        return;
    }
    if (client->data.mode == PORT) {
        connect(client->data.accept_fd, (struct sockaddr *)&client->data.addr,
            len);
        return;
    }
}

bool check_connection(client_t *client)
{
    if (client->data.data_fd < 0) {
        fill_output_buffer(client->output, ERROR_425);
        return false;
    }
    if (client->data.mode == NO_CONNECTION) {
        fill_output_buffer(client->output, ERROR_425);
        if (client->data.data_fd > 0)
            close(client->data.data_fd);
        return false;
    }
    return true;
}
