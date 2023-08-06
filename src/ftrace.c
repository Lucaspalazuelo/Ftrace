/*
** EPITECH PROJECT, 2023
** B-PSU-400-LYN-4-1-ftrace-keziah.picq
** File description:
** ftrace
*/

#include "../inc/my.h"

void entering(data_s *data, long rip)
{
    for (int i = 0; data->adr_tab[i] != NULL; i++) {
        if (rip == atoi(data->adr_tab[i])) {
            printf("Entering function %s at %#x\n", data->name_tab[i],
            atoi(data->adr_tab[i]));
            data->current_name = strdup(data->name_tab[i]);
            break;
        }
    }
}

void leaving(data_s *data)
{
    if ((data->opcode & 0x3800) == 0x1000) {
        print_leaving(data);
    }
}

void print_leaving(data_s *data)
{
    if (data->current_name != NULL) {
        if ((data->opcode & 0xFF) == 0xC3 || (data->opcode & 0xFF) == 0xC2 ||
        (data->opcode & 0xFF) == 0xCB || (data->opcode & 0xFF) == 0xCA) {
            printf("Leaving function %s\n", data->current_name);
            free(data->current_name);
            data->current_name = NULL;
        }
    }
}
