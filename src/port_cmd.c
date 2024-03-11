/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-theo.vermorel
** File description:
** port_cmd.c
*/

#include "../includes/commands.h"

char *parse_ip(char **arr)
{
    size_t max_len = 0;
    char *ip;

    for (int i = 0; i < 4; i++)
        max_len += strlen(arr[i]);
    ip = malloc(sizeof(char) * (max_len + 3 + 1));
    memset(ip, 0, max_len + 1);
    for (int i = 0; i < 4; i++) {
        strcat(ip, arr[i]);
        if (i + 1 < 4)
            strcat(ip, ".");
    }
    return ip;
}

int parse_port(char *port1, char *port2)
{
    int port;

    port = (atoi(port1) * 256) + atoi(port2);
    return port;
}

void initialise_data_socket_port(client_t *client, char *ip,
    int port)
{
    printf("ip:[%s]\nport:[%d]\n", ip, port);
    client->data.accept_fd = socket(AF_INET, SOCK_STREAM, 0);
    client->data.addr.sin_family = AF_INET;
    client->data.addr.sin_port = htons(port);
    client->data.addr.sin_addr.s_addr = inet_addr(ip);
    client->data.mode = PORT;
}

void port_cmd(server_t *server, client_t *client, char *args)
{
    char **arr;
    char *ip;
    int port;

    while (*args == ' ')
        args++;
    arr = my_str_to_word_array(args, ",\r\n");
    if (length_2d_arr(arr) != 6) {
        fill_output_buffer(client->output, ERROR_501);
        return;
    }
    ip = parse_ip(arr);
    port = parse_port(arr[4], arr[5]);
    initialise_data_socket_port(client, ip, port);
    fill_output_buffer(client->output, CODE_200);
    free(ip);
    free_2d_arr(arr);
}
