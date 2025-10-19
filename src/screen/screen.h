#ifndef SCREEN_H
#define SCREEN_H

void clear();
void clear_str(int str);
char *get_str(int str);
char *get_text();
void backspace(int str);
void print(char text[], int str, int color);
void print_char(char c, int str, int color);
void replace_char(char c, int str, int col, int color);
void replace(char text[], int str, int col, int color);
int is_color_same(int old_color, int str, int col);
void hide_cursor();
void show_cursor();

#endif