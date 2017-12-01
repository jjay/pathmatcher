// A simple program that matach a path to file with a pattern
#include <stdio.h>

bool is_delimiter(char c){
  return c == '/' || c == '\\';
}
bool match_char(char a, char b){
  return a == b || (is_delimiter(a) && is_delimiter(b));
}
bool match(char *path, char *pattern){
  switch (*pattern) {
    case 0: return !*path;
    case '?': return *path != 0 && match(path+1, pattern+1);
    case '*':
      switch (*(pattern+1)) {
        case '*': return *(pattern+2) == 0 || match(path, pattern+2) || match(path+1, pattern);
        default: return match(path, pattern+1) || (!is_delimiter(*path) && match(path+1, pattern));
      }
    default: return match_char(*path, *pattern) && match(path+1, pattern+1);
  }
}

int main (int argc, char *argv[])
{
  if (argc != 3) {
      fprintf(stdout, "Usage: %s /path/to/check pattern", argv[0]);
      return 2;
  }
  bool matched = match(argv[1], argv[2]);
  fprintf(stdout, "Match: %s\n", matched ? "yes" : "no");
  return matched ? 0 : 1;
}
