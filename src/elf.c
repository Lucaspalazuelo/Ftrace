/*
** EPITECH PROJECT, 2023
** B-PSU-400-LYN-4-1-ftrace-keziah.picq
** File description:
** init_elf
*/

#include "../inc/my.h"

void init_elf(data_s *data, char *file, Elf **e)
{
    int fd = open(file, O_RDONLY, 0);

    if (fd < 0) {
        printf("Error: open_failed.\n");
        exit(84);
    }
    if (elf_version(EV_CURRENT) == EV_NONE) {
        printf("Error: elf_version failed.\n");
        exit(84);
    }
    *e = elf_begin(fd, ELF_C_READ, NULL);
    if (*e == NULL) {
        printf("Error: elf_begin failed.\n");
        exit(84);
    }
    if (elf_kind(*e) != ELF_K_ELF) {
        printf("Error: %s isn't an elf file.\n", file);
        exit(84);
    }
}

void parse_elf(data_s *data, Elf **e, Elf64_Shdr **shdr, Elf_Scn **scn)
{
    while ((*scn = elf_nextscn(*e, *scn)) != NULL) {
        *shdr = elf64_getshdr(*scn);
        if (*shdr == NULL) {
            printf("Error: couldn't retreive section header.\n");
            exit(84);
        }
        if ((*shdr)->sh_type == SHT_SYMTAB)
            strace(data, e, shdr, scn);
    }
}

void get_elf(data_s *data_s, Elf64_Shdr **sym_shdr, Elf_Scn **sym_scn, Elf **e)
{
    Elf_Data *data = elf_getdata(*sym_scn, NULL);
    int nb_sym = (*sym_shdr)->sh_size / (*sym_shdr)->sh_entsize;
    Elf64_Sym *symtab = (Elf64_Sym *)data->d_buf;
    int st_type = 0;
    int size = 0;
    char *name = NULL;

    init_tab(data_s, nb_sym);
    for (int i = 0 ; i < nb_sym ; i++) {
        name = elf_strptr(*e, (*sym_shdr)->sh_link, symtab[i].st_name);
        if (ELF64_ST_TYPE(symtab[i].st_info) == STT_FUNC && symtab[i].st_shndx
        != 0 && ELF64_ST_BIND(symtab[i].st_info) == 1 && name[0] != '_') {
            data_s->name_tab[size] = strdup(name);
            data_s->adr_tab[size] = malloc(sizeof(char) * 100);
            sprintf(data_s->adr_tab[size], "%ld", symtab[i].st_value);
            size++;
        }
    }
    data_s->name_tab[size] = NULL;
    data_s->adr_tab[size] = NULL;
}

void init_tab(data_s *data, int size)
{
    data->name_tab = malloc(sizeof(char *) * size);
    data->adr_tab = malloc(sizeof(char *) * size);
}
