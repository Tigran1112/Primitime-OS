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
void replace_char(char c, int str, int col, int color);
int get_symbol_color(int str, int col);
int is_color_same(int old_color, int str, int col);
void replace_text(char text[], int str, int col, int color);
void hide_cursor();
void show_cursor();

#endif