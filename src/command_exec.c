/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-theo.vermorel
** File description:
** command_exec.c
*/

#include "../includes/commands.h"

void fill_output_buffer(char *buffer, const char *msg)
{
    strcat(buffer, msg);
}

int is_cmd_existing(char *cmd)
{
    for (int i = 0; i < NB_CMD; i++) {
        if (strncmp(cmd, cmds[i].cmd, cmds[i].len) == 0) {
            return i;
        }
    }
    return -1;
}

void exec_cmd(server_t *server, client_t *client, char *cmd)
{
    int cmd_index;

    cmd_index = is_cmd_existing(cmd);
    if (cmd_index == -1) {
        fill_output_buffer(client->output, ERROR_500);
        return;
    }
    if (!client->auth.is_authenticated && cmd_index > 4) {
        fill_output_buffer(client->output, ERROR_530);
        return;
    }
    cmds[cmd_index].func_ptr(server, client, &cmd[cmds[cmd_index].len]);
}
