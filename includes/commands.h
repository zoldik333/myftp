/*
** EPITECH PROJECT, 2025
** B-NWP-500-LYN-5-1-myftp-theo.vermorel
** File description:
** commands.h
*/

#pragma once
#include <fcntl.h>
#include "server.h"
#define NB_CMD 14

#define CODE_220 "220\r\n"
#define ERROR_500 "500 Syntax error.\r\n"
#define ERROR_501 "501 Syntax error in parameters or arguments.\r\n"
#define ERROR_530 "530 Not logged in.\r\n"
#define CODE_230 "230 User logged in, proceed.\r\n"
#define CODE_331 "331 User name okay, need password.\r\n"
#define CODE_332 "332 Need account for login.\r\n"
#define CODE_221 "221 Service closing control connection.\r\n"
#define CODE_200 "200 Command okay.\r\n"
#define CODE_214 "214 Help message.\r\n"
#define ERROR_450 "450 Requested file action not taken.\r\n"
#define CODE_250 "250 Requested file action okay, completed.\r\n"
#define CODE_150 "150 File status okay, about to open data connection.\r\n"
#define CODE_226 "226 Closing data connection.\r\n"
#define CODE_257 "257 \""
#define CODE_257_2 "\" created.\r\n"
#define CODE_227 "227 Entering Passive Mode"
#define ERROR_400 "400\r\n"
#define ERROR_550 "550 Requested action not taken.\r\n"
#define ERROR_425 "425 Can't open data connection.\r\n"

typedef struct {
    char *cmd;
    int len;
    void (*func_ptr)(server_t *server, client_t *client, char *args);
} cmd_t;

// UTILS
int length_2d_arr(char **arr);
void free_2d_arr(char **arr);
char *length_till_crlf(char *str);
char **my_str_to_word_array(char *str, char *separator);
bool only_spaces(char *args);

// CHECK_CONNECTION
bool check_connection(client_t *client);
void accept_connection(client_t *client);

// HELP
int is_arg_existing_help(char *cmd);
int is_cmd_existing(char *cmd);

void user_cmd(server_t *server, client_t *client, char *args);
void pass_cmd(server_t *server, client_t *client, char *args);
void quit_cmd(server_t *server, client_t *client, char *args);
void noop_cmd(server_t *server, client_t *client, char *args);
void help_cmd(server_t *server, client_t *client, char *args);
void cwd_cmd(server_t *server, client_t *client, char *args);
void pwd_cmd(server_t *server, client_t *client, char *args);
void cdup_cmd(server_t *server, client_t *client, char *args);
void dele_cmd(server_t *server, client_t *client, char *args);
void pasv_cmd(server_t *server, client_t *client, char *args);
void list_cmd(server_t *server, client_t *client, char *args);
void retr_cmd(server_t *server, client_t *client, char *args);
void port_cmd(server_t *server, client_t *client, char *args);
void stor_cmd(server_t *server, client_t *client, char *args);

static const cmd_t cmds[NB_CMD] = {
    {"USER", 4, user_cmd},
    {"PASS", 4, pass_cmd},
    {"QUIT", 4, quit_cmd},
    {"NOOP", 4, noop_cmd},
    {"HELP", 4, help_cmd},
    {"CWD", 3, cwd_cmd},
    {"CDUP", 4, cdup_cmd},
    {"DELE", 4, dele_cmd},
    {"PWD", 3, pwd_cmd},
    {"PORT", 4, port_cmd},
    {"PASV", 4, pasv_cmd},
    {"RETR", 4, retr_cmd},
    {"STOR", 4, stor_cmd},
    {"LIST", 4, list_cmd}
};
