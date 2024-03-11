/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-theo.vermorel
** File description:
** connection.c
*/

#include "../includes/commands.h"

void initialise_data_socket_pasv(server_t *server, client_t *client)
{
    socklen_t len;

    client->data.data_fd = socket(AF_INET, SOCK_STREAM, 0);
    client->data.addr.sin_family = AF_INET;
    client->data.addr.sin_port = htons(0);
    client->data.addr.sin_addr.s_addr = INADDR_ANY;
    check(bind(client->data.data_fd, (struct sockaddr *) &client->data.addr,
        sizeof(client->data.addr)), NULL, "Bind data socket");
    check(listen(client->data.data_fd, 1), server, "Listen server socket");
    FD_SET(client->data.data_fd, &server->curr_read_fds);
    len = sizeof(client->addr);
    getsockname(client->fd, (struct sockaddr *) &client->addr,
        &len);
    len = sizeof(client->data.addr);
    getsockname(client->data.data_fd, (struct sockaddr *)&client->data.addr,
        &len);
}

char *get_ip(char *ip)
{
    char **tmp;
    char *new_ip;

    new_ip = malloc(sizeof(char) * (strlen(ip) + 1));
    memset(new_ip, 0, strlen(ip) + 1);
    tmp = my_str_to_word_array(ip, ".");
    for (int i = 0; tmp[i]; i++) {
        strcat(new_ip, tmp[i]);
        if (tmp[i + 1])
            strcat(new_ip, ",");
    }
    free_2d_arr(tmp);
    return new_ip;
}

void pasv_cmd(server_t *server, client_t *client, char *args)
{
    char *ip;
    char *new_ip;
    uint16_t port;
    char tmp[BUFFER_SIZE] = {0};

    if (!only_spaces(args)) {
        fill_output_buffer(client->output, ERROR_501);
        return;
    }
    initialise_data_socket_pasv(server, client);
    ip = inet_ntoa(client->addr.sin_addr);
    port = ntohs(client->data.addr.sin_port);
    new_ip = get_ip(ip);
    sprintf(tmp, "%s. %s,%d,%d\r\n", CODE_227, new_ip,
        (port >> 8) & 0xFF, port & 0xFF);
    fill_output_buffer(client->output, tmp);
    client->data.mode = PASV;
    memset(&tmp, 0, BUFFER_SIZE);
    free(new_ip);
}
