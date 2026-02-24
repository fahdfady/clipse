#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>

typedef struct {
  void *data;
  char *file_name;
  size_t size;
  // elf headers
  Elf64_Ehdr *ehdr;
  // section headers
  Elf64_Shdr *shdrs;
} ObjectFile;

long int get_file_size(const char *file_name) {
  FILE *fp = fopen(file_name, "r");

  if (fp == NULL) {
    printf("couldn't open file %s\n", file_name);
    // return something ??
    return -1;
  }
  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  fclose(fp);

  return size;
}

void print_elf_debug_info(Elf64_Ehdr *ehdr, Elf64_Shdr *shdrs) {
  printf("\n=== ELF Header ===\n");
  printf("type: %hu\n", ehdr->e_type);
  printf("machine: %hu\n", ehdr->e_machine);
  printf("sections number: %hu\n", ehdr->e_shnum);

  printf("\n=== Section Header ===\n");
  printf("e_shoff = %lu (section headers at byte %lu)\n", ehdr->e_shoff,
         ehdr->e_shoff);
  printf("e_shnum = %u (there are %u sections)\n", ehdr->e_shnum,
         ehdr->e_shnum);
  printf("e_shstrndx = %u (section %u has names)\n", ehdr->e_shstrndx,
         ehdr->e_shstrndx);

  // change this into the acutal name
  int first_section_name = shdrs[1].sh_name;
  printf("Section 1 name offset: %d\n", first_section_name);
}

ObjectFile load_object(const char *file_name) {
  ObjectFile obj_file;

  int fd = open(file_name, O_RDONLY);

  if (fd < 0) {
    perror("open");
    exit(1);
  }

  obj_file.file_name = (char *)file_name;

  obj_file.size = get_file_size(file_name);

  obj_file.data = mmap(NULL, obj_file.size, PROT_READ, MAP_PRIVATE, fd, 0);

  close(fd);

  obj_file.ehdr = (Elf64_Ehdr *)obj_file.data;

  // map the data with the ehdr pointing us to the section header offset
  obj_file.shdrs = (Elf64_Shdr *)(obj_file.data + obj_file.ehdr->e_shoff);

  return obj_file;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "usage %s <file_1> <file_2>", argv[0]);
    return 1;
  };

  printf("Loading %s...\n", argv[1]);
  ObjectFile obj1 = load_object(argv[1]);
  print_elf_debug_info(obj1.ehdr, obj1.shdrs);

  printf("Loading %s...\n", argv[2]);
  ObjectFile obj2 = load_object(argv[2]);
  print_elf_debug_info(obj2.ehdr, obj2.shdrs);

  return 0;
}
