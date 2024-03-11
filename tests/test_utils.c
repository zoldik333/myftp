/*
** EPITECH PROJECT, 2024
** B-NWP-400-LYN-4-1-myftp-theo.vermorel
** File description:
** test_utils.c
*/

#include <criterion/criterion.h>
#include "../includes/server.h"
#include "../includes/commands.h"

Test(commands_parsing, is_arg_existing) {
    char *arg = "     USER\r\n";

    while (*arg == ' ')
        arg++;

    cr_assert_eq(is_arg_existing_help(arg), 0);
}

Test(commands_parsing, is_arg_not_existing) {
    char *arg = "     USERS\r\n";

    while (*arg == ' ')
        arg++;

    cr_assert_eq(is_arg_existing_help(arg), -1);
}

char **get_list_args(char *args);

Test(list_cmd, test_return_value)
{
    char **tmp;
    char *args = " src";

    tmp = get_list_args(args);
    cr_assert_str_eq(tmp[0], "ls");
    cr_assert_str_eq(tmp[1], "src");
    cr_assert_null(tmp[2]);
    free_2d_arr(tmp);
}

Test(list_cmd, test_return_value2)
{
    char **tmp;
    char *args = ".";

    tmp = get_list_args(args);
    cr_assert_str_eq(tmp[0], "ls");
    cr_assert_str_eq(tmp[1], ".");
    cr_assert_null(tmp[2]);
    free_2d_arr(tmp);
}

char *get_ip(char *ip);

Test(get_ip, test_if_ip_string_correct)
{
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(0);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    char *ip = inet_ntoa(addr.sin_addr);
    char *new_ip = get_ip(ip);
    cr_assert_str_eq(new_ip, "0,0,0,0");

    free(new_ip);
}

int parse_port(char *port1, char *port2);

Test(parse_port, parse_port_utils)
{
    int port;

    port = parse_port("197", "145");
    cr_assert_eq(port, 50577);
}

char *parse_ip(char **arr);

Test(parse_ip, parse_ip_to_string)
{
    char *old_ip;
    char *ip;

    old_ip = strdup("127,0,0,1,256,23");
    char **arr = my_str_to_word_array(old_ip, ",");
    ip = parse_ip(arr);

    cr_assert_str_eq(ip, "127.0.0.1");
}

char **check_path_list_args(char **arr, char *home);

Test(check_path_list_args, check_path_list_args)
{
    char *args = NULL;
    char *home = NULL;
    char **arr = NULL;
    char **new = NULL;

    home = strdup(realpath(".", NULL));
    args = strdup(" src . no_directory");

    arr = get_list_args(args);
    new = check_path_list_args(arr, home);
    cr_assert_str_eq(new[3], "no_directory");

    free_2d_arr(new);
    free(home);
    free(args);
}

Test(check_path_list_args, check_path_list_args_not_working)
{
    char *args = NULL;
    char *home = NULL;
    char **arr = NULL;
    char **new = NULL;

    home = strdup(realpath(".", NULL));
    args = strdup(" src . ..");

    arr = get_list_args(args);
    new = check_path_list_args(arr, home);
    cr_assert_null(new);

    free(home);
    free(args);
}
