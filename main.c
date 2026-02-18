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

ObjectFile load_object(const char *file_name) {
  printf("%s", file_name);

  // get file size

  // get elf headers

  // get section headers

  ObjectFile obj_file;

  return obj_file;
};

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "usage %s <file_1> <file_2>", argv[0]);
    return 1;
  };

  load_object("objectfile");
  return 0;
}
