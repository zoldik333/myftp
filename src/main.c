/*
** EPITECH PROJECT, 2024
** bootstrap_my_ftp
** File description:
** main.c
*/

#include "server.h"

static int usage(void)
{
    printf("USAGE: ./myftp port path\n"
        "\tport is the port number on which the server socket listens\n"
        "\tpath is the path to the home directory for the Anonymous user");
    return 0;
}

bool unknown_path(const char *arg)
{
    char *tmp_path = NULL;

    tmp_path = realpath(arg, NULL);
    if (!tmp_path) {
        return false;
    }
    free(tmp_path);
    return true;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 84;
    if (argc == 2 && !strncmp(argv[1], "-help", 5))
        return usage();
    if (argc != 3 || !unknown_path(argv[2]))
        return 84;
    return mainloop(argv);
}
