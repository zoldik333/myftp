/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-theo.vermorel
** File description:
** noop.c
*/

#include "../includes/help.h"

void noop_cmd(server_t *server, client_t *client, char *args)
{
    if (!only_spaces(args)) {
        fill_output_buffer(client->output, ERROR_500);
    } else {
        fill_output_buffer(client->output, CODE_200);
    }
}

int is_arg_existing_help(char *cmd)
{
    int len = 0;

    while (cmd[len] && cmd[len] != '\r')
        len++;
    for (int i = 0; i < NB_CMD; i++) {
        if (strncmp(cmd, cmds[i].cmd, len) == 0) {
            return i;
        }
    }
    return -1;
}

void help_cmd(server_t *server, client_t *client, char *args)
{
    int idx;
    char **tmp;
    char tmp_output[BUFFER_SIZE] = {0};

    if (only_spaces(args)) {
        fill_output_buffer(client->output, CODE_214);
        return;
    }
    tmp = my_str_to_word_array(args, " ");
    for (int i = 0; tmp[i]; i++) {
        idx = is_arg_existing_help(tmp[i]);
        if (idx == -1) {
            fill_output_buffer(client->output, ERROR_501);
            return;
        }
        fill_output_buffer(tmp_output, help[idx]);
    }
    fill_output_buffer(client->output, CODE_214);
    fill_output_buffer(client->output, tmp_output);
}
