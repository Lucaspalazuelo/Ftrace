/*
** EPITECH PROJECT, 2023
** B-PSU-400-LYN-4-1-ftrace-keziah.picq
** File description:
** strace_params
*/

#include "../inc/my.h"

void get_params(data_s *data, struct user_regs_struct regs, int num)
{
    long *params = malloc(sizeof(long) * 6);

    params[0] = regs.rdi;
    params[1] = regs.rsi;
    params[2] = regs.rdx;
    params[3] = regs.r10;
    params[4] = regs.r8;
    params[5] = regs.r9;
    get_params_types(params, num);
    free(params);
}

void get_params_types(long *params, int num)
{
    for (int i = 0; i < syscalls_info[num].num_params; i++) {
        if (i == syscalls_info[num].num_params - 1)
            printf("%#lx", params[i]);
        else
            printf("%#lx, ", params[i]);
    }
}

void get_return(data_s *data, struct user_regs_struct regs, int num)
{
    (regs.rax == -ENOSYS) ? printf(") = ?\n") : printf(") = %#llx\n",
    regs.rax);
}
