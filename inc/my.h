/*
** EPITECH PROJECT, 2023
** B-PSU-400-LYN-4-1-ftrace-keziah.picq
** File description:
** my
*/

#ifndef MY_H_
    #define MY_H_
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/ptrace.h>
    #include <sys/wait.h>
    #include <unistd.h>
    #include <sys/user.h>
    #include <sys/syscall.h>
    #include <stdbool.h>
    #include <ctype.h>
    #include <errno.h>
    #include "syscall.h"
    #include <libelf.h>
    #include <gelf.h>
    #include <fcntl.h>

typedef struct data_t {
    char **args;
    char *binary;
    char **name_tab;
    char **adr_tab;
    char *current_name;
    short opcode;
}data_s;

void get_args(int ac, char **av, data_s *data);
void cpy_args(int ac, char **av, data_s *data);

int strace(data_s *data, Elf **e, Elf64_Shdr **shdr, Elf_Scn **scn);
void do_strace(data_s *data_s, pid_t child);
void get_params(data_s *data, struct user_regs_struct regs, int num);
void get_return(data_s *data, struct user_regs_struct regs, int num);
void get_params_types(long *params, int num);
void print_exit(int status);

void init_elf(data_s *data, char *file, Elf **e);
void parse_elf(data_s *data, Elf **e, Elf64_Shdr **shdr, Elf_Scn **scn);

void get_elf(data_s *data_s, Elf64_Shdr **sym_shdr, Elf_Scn **sym_scn, Elf **e);
void init_tab(data_s *data, int size);

void entering(data_s *data, long rip);
void leaving(data_s *data);
void print_leaving(data_s *data);

#endif /* !MY_H_ */
