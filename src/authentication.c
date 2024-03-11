/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-theo.vermorel
** File description:
** authentication.c
*/

#include "../includes/commands.h"

static void check_status_auth(client_auth_t *auth)
{
    if (auth->has_pass && auth->has_user) {
        auth->is_authenticated = true;
    }
}

void user_cmd(server_t *server, client_t *client, char *args)
{
    if (only_spaces(args)) {
        fill_output_buffer(client->output, ERROR_500);
        return;
    }
    while (*args == ' ')
        args++;
    if (strncmp(args, ANONYMOUS, strlen(ANONYMOUS)) == 0) {
        fill_output_buffer(client->output, (client->auth.has_pass == true ?
            CODE_230 : CODE_331));
        client->auth.has_user = true;
        check_status_auth(&client->auth);
    } else {
        client->auth.has_user = false;
        fill_output_buffer(client->output, CODE_331);
    }
}

void pass_cmd(server_t *server, client_t *client, char *args)
{
    if (only_spaces(args)) {
        fill_output_buffer(client->output, (client->auth.has_user == true ?
            CODE_230 : CODE_332));
        client->auth.has_pass = true;
        check_status_auth(&client->auth);
    } else {
        fill_output_buffer(client->output, ERROR_530);
    }
}

void quit_cmd(server_t *server, client_t *client, char *args)
{
    int i = 0;

    for (; i < MAX_CLIENTS; i++) {
        if (server->clients[i].fd == client->fd)
            break;
    }
    write(client->fd, CODE_221, strlen(CODE_221));
    logout_client(server, i);
}
