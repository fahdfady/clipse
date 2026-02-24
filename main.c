#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

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

void print_elf_header(Elf64_Ehdr *ehdr) {
  printf("\n=== ELF Header ===\n");
  printf("type: %hu\n", ehdr->e_type);
  printf("machine: %hu\n", ehdr->e_machine);
  printf("sections number: %hu\n", ehdr->e_shnum);
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

  obj_file.ehdr = (Elf64_Ehdr *)obj_file.data;
  print_elf_header(obj_file.ehdr);
  printf("%s: %zu", obj_file.file_name, obj_file.size);

  // get section headers

  return obj_file;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "usage %s <file_1> <file_2>", argv[0]);
    return 1;
  };

  load_object(argv[1]);
  load_object(argv[2]);
  return 0;
}
