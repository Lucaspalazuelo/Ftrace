/*
** EPITECH PROJECT, 2023
** B-PSU-400-LYN-4-1-ftrace-keziah.picq
** File description:
** get
*/

#include "../inc/my.h"

void get_args(int ac, char **av, data_s *data)
{
    for (int i = 1; i < ac; i++) {
        if (strcmp(av[i], "--help") == 0) {
            printf("USAGE: ./ftrace <command>\n");
            exit(0);
        }
    }
    cpy_args(ac, av, data);
}

void cpy_args(int ac, char **av, data_s *data)
{
    int i = 1;
    int j = 0;

    data->args = malloc(sizeof(char *) * ac + 1);
    for (; i < ac; i++, j++)
        data->args[j] = strdup(av[i]);
    data->args[j] = NULL;
}
