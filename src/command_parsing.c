/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-theo.vermorel
** File description:
** commands.c
*/

#include "../includes/server.h"

static char *fill_cmd(circ_buf_t *circular, int count)
{
    char cmd[count + 1];
    char *new_cmd = NULL;
    int pos = circular->tail;
    int i = 0;

    for (; i < count; i++) {
        if (pos >= BUFFER_SIZE)
            pos = 0;
        cmd[i] = circular->buffer[pos];
        pos++;
    }
    cmd[i] = '\0';
    new_cmd = strdup(cmd);
    return new_cmd;
}

char *get_cmd(circ_buf_t *circular, int i, int pos, int tmp_tail)
{
    char *tmp = NULL;

    tmp = fill_cmd(circular, i + 1);
    circular->size -= (i + 1);
    circular->tail = tmp_tail + pos + 1;
    return tmp;
}

char *parse_cmd(client_t *client)
{
    int tmp_tail = client->circular.tail;
    int pos = 0;
    bool is_found = false;

    for (int i = 0; i <= client->circular.size; i++) {
        if (tmp_tail + i >= BUFFER_SIZE) {
            tmp_tail = 0;
            pos = 0;
        }
        if (is_found && client->circular.buffer[tmp_tail + pos] == '\n') {
            return get_cmd(&client->circular, i, pos, tmp_tail);
        } else
            is_found = false;
        if (client->circular.buffer[tmp_tail + pos] == '\r')
            is_found = true;
        pos++;
    }
    return NULL;
}

bool read_cmd(client_t *client)
{
    size_t read_bytes;
    char tmp[4096];

    read_bytes = read(client->fd, tmp, BUFFER_SIZE);
    if (read_bytes <= 0)
        return false;
    client->circular.size += read_bytes;
    for (int i = 0; i < read_bytes; i++) {
        if (client->circular.head >= BUFFER_SIZE)
            client->circular.head = 0;
        client->circular.buffer[client->circular.head] = tmp[i];
        client->circular.head += 1;
    }
    return true;
}
