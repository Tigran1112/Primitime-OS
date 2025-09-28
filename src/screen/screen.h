#ifndef SCREEN_H
#define SCREEN_H

void clear();
void clear_str(int str);
char *get_str(int str);
char *get_text();
void replace(char text[], int str, int color);
void backspace(int str);
void print(char text[], int str, int color);
void print_char(char c, int str, int color);
void hide_cursor();
void show_cursor();

#endif