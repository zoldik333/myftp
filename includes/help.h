/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-theo.vermorel
** File description:
** help.h
*/

#pragma once
#include "commands.h"

static const char *help[NB_CMD] = {
    "USER <SP> <username> <CRLF>\t: Specify user for authentication\r\n",
    "PASS <SP> <password> <CRLF>\t: Specify password for authentication\r\n",
    "QUIT <CRLF>\t: Disconnection\r\n",
    "NOOP <CRLF>\t: Do nothing\r\n",
    "HELP [<SP> <string>] <CRLF>\t: List available commands\r\n",
    "CWD  <SP> <pathname> <CRLF>\t: Change working directory\r\n",
    "CDUP <CRLF>\t: Change working directory to parent directory\r\n",
    "DELE <SP> <pathname> <CRLF>\t: Delete file on the server\r\n",
    "PWD  <CRLF>\t: Print working directory\r\n",
    "PASV <CRLF>\t: Enable \"passive\" mode for data transfer\r\n",
    "PORT <SP> <host-port> <CRLF>\t: Enable \"active\" mode for data"
    "transfer\r\n",
    "RETR <SP> <pathname> <CRLF>\t: Download file from server to client\r\n",
    "STOR <SP> <pathname> <CRLF>\t: Upload file from client to server\r\n",
    "LIST [<SP> <pathname>] <CRLF>\t: List files in the current "
    "working directory\r\n",
};
