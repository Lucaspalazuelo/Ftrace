/*
** EPITECH PROJECT, 2023
** ftrace
** File description:
** main
*/

#include "../inc/my.h"

int print_usage(void)
{
    printf("USAGE: ftrace <command>\n");
    return 0;
}

int main(int argc, char **argv)
{
    struct data_t data;
    Elf *e = NULL;
    Elf64_Shdr *shdr = NULL;
    Elf_Scn *scn = NULL;
    data.current_name = NULL;

    if (argc != 2)
        return 84;
    if (strcmp(argv[1], "--help") == 0)
        return print_usage();
    get_args(argc, argv, &data);
    init_elf(&data, argv[1], &e);
    parse_elf(&data, &e, &shdr, &scn);
    return 0;
}
