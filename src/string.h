#ifndef _string_h
#define _string_h
#include <stdlib.h>
#include "macros.h"

typedef struct String {
  char *str;
  int length;
} String;

String string(char *str) {
  int len = 0;
  int i = 0;

  while (str[i++] != '\0') len++;
  char *s = (char *)malloc(len + 1);

  for (int i = 0; i < len; ++i) {
    s[i] = str[i];
  }

  s[len] = '\0';

  String string = { .str = s, .length = len };
  return string;
}

void print_string(String str) {
  for (int i = 0; i < str.length; ++i) {
    printf("%c", str.str[i]);
  }
  printf("\n");
}

String copy(String str) {
  char *copy = (char *)malloc(str.length);

  for (int i = 0; i < str.length; ++i) {
    copy[i] = str.str[i];
  }

  copy[str.length] = '\0';
  String copied = { .str = copy, .length = str.length };
  return copied;
}

int same_string(String s1, String s2) {
  if (s1.length not s2.length) return false;

  for (int i = 0; i < s1.length; ++i) {
    if (s1.str[i] not s2.str[i]) return false;
  }

  return true;
}

String *string_split(String str, char delimiter, int *length) {
  int count = 1;

  for (int i = 0; i < str.length; ++i) {
    if (str.str[i] == delimiter) count++;
  }

  (*length) = count;

  String *parts = (String *)malloc(count * sizeof(String));
  int index = 0;
  char part[str.length];

  for (int i = 0, j = 0; i < str.length; ++i) {
    if (str.str[i] == delimiter) {
      part[j] = '\0';
      String string_part = string(part);
      parts[index++] = copy(string_part);
      j = 0;
      continue;
    }

    part[j++] = str.str[i];

    if (i == str.length - 1) {
      part[j] = '\0';
      String string_part = string(part);
      parts[index++] = copy(string_part);
    }
  }

  return parts;
}

#endif
