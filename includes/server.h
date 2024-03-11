/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-theo.vermorel
** File description:
** server.h
*/

#pragma once
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include "stdbool.h"

#define SOCKET_ERROR (-1)
#define EXIT_ERROR 84
#define MAX_CLIENTS 100
#define MAX_ARGS 10
#define SUB_IP 4
#define BUFFER_SIZE 4096
#define ANONYMOUS "Anonymous"

//typedef struct {
//	char *username;
//	char *password;
//} auth_t;

enum connect {
    NO_CONNECTION,
    PASV,
    PORT
};

typedef struct {
    int head;
    int tail;
    int size;
    char buffer[BUFFER_SIZE];
}circ_buf_t;

typedef struct {
    bool is_authenticated;
    bool has_pass;
    bool has_user;
} client_auth_t;

typedef struct data_s {
    int data_fd;
    int accept_fd;
    int mode;
    struct sockaddr_in addr;
} data_t;

typedef struct client_s {
    int fd;
    struct sockaddr_in addr;
    circ_buf_t circular;
    char *curr_wd;
    client_auth_t auth;
    data_t data;
    char output[BUFFER_SIZE];
} client_t;

typedef struct server_s {
    int fd;
    struct sockaddr_in addr;
    char *home;
    fd_set read_fds;
    fd_set write_fds;
    fd_set curr_read_fds;
    client_t *clients;
    int count;
} server_t;


// COMMAND_EXEC
void fill_output_buffer(char *buffer, const char *msg);
void exec_cmd(server_t *server, client_t *client, char *cmd);

// COMMAND_PARSING
bool read_cmd(client_t *client);
char *parse_cmd(client_t *client);

// CLIENT
void logout_client(server_t *server, int index);
void handle_new_client(server_t *server);
void handle_read_client(server_t *server, int index);
void handle_write_client(server_t *server, int index);

// SERVER
server_t *setup_server(uint16_t port, char *home);

// ERROR_HANDLING
int check(int ret_code, server_t *server, const char *msg);

// MAINLOOP
int mainloop(char *argv[]);
