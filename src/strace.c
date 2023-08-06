/*
** EPITECH PROJECT, 2023
** B-PSU-400-LYN-4-1-ftrace-keziah.picq
** File description:
** strace
*/

#include "../inc/my.h"

int strace(data_s *data, Elf **e, Elf64_Shdr **shdr, Elf_Scn **scn)
{
    pid_t child;

    child = fork();
    if (child == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        execvp(data->args[0], &data->args[0]);
        exit(1);
    }
    get_elf(data, shdr, scn, e);
    do_strace(data, child);
    return 0;
}

void do_strace(data_s *data_s, pid_t child)
{
    int status;
    struct user_regs_struct regs;

    while (1) {
        ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
        wait(&status);
        ptrace(PTRACE_GETREGS, child, NULL, &regs);
        data_s->opcode = ptrace(PTRACE_PEEKTEXT, child, regs.rip, NULL);
        entering(data_s, (long)regs.rip);
        if (regs.orig_rax != -1 && regs.orig_rax < 329) {
            printf("Syscall %s(", syscalls_info[regs.orig_rax].name);
            get_params(data_s, regs, regs.orig_rax);
            get_return(data_s, regs, regs.orig_rax);
        }
        leaving(data_s);
        if (WIFEXITED(status)) {
            print_exit(status);
            break;
        }
    }
}

void print_exit(int status)
{
    printf("Syscall exit_group(%#x) = ?\n", WEXITSTATUS(status));
    printf("Leaving function main\n");
    printf("+++ exited with %d +++\n", WEXITSTATUS(status));
}
