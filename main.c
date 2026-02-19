#include <elf.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
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

  // return size;

  return fseek(fp, 0, SEEK_END);
}

ObjectFile load_object(const char *file_name) {
  ObjectFile obj_file;

  obj_file.file_name = file_name;
  obj_file.size = get_file_size(file_name);

  // get elf headers

  // get section headers

  return obj_file;
};

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "usage %s <file_1> <file_2>", argv[0]);
    return 1;
  };

  load_object(argv[1]);
  load_object(argv[2]);
  return 0;
}
