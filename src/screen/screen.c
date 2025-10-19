volatile char *vga = (volatile char*)0xb8000;
#define empty_symbol 0x00

void clear()
{
    for (int i = 0; i < 80 * 25; i++)
    {
        vga[i * 2] = empty_symbol;
        vga[i * 2 + 1] = 0x07;
    }
}
void clear_str(int str)
{
    for (int i = 0; i < 80; i++)
    {
        int pos = (str * 80 + i) * 2;
        vga[pos] = empty_symbol;
        vga[pos + 1] = 0x07;
    }
    
}
char *get_str(int str) 
{
    static char buffer[81];
    
    for (int i = 0; i < 80; i++) 
    {
        buffer[i] = vga[(str * 80 + i) * 2];
    }
    buffer[80] = '\0';
    return buffer;
}
char *get_text()
{
    static char buffer[2001];

    for (int i = 0; i < 2000; i++)
    {
        buffer[i] = vga[i*2];
    }
    buffer[2001] = '\0';
    return buffer;
}
void replace(char text[], int str, int color)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        int pos = (str * 80 + i) * 2;
        vga[pos] = text[i];
        vga[pos + 1] = color;
    }
}
void backspace(int str)
{
    int pos = (str * 80) * 2;
    while (vga[pos] != empty_symbol)
    {
        pos += 2;
    }
    pos -= 2;
    vga[pos] = empty_symbol;
}
void print(char text[], int str, int color)
{
    int pos = (str * 80) * 2;
    
    while (vga[pos] != empty_symbol) pos += 2;
    
    for (int i = 0; text[i] != '\0'; i++) 
    {
        if (pos >= (str * 80 + 79) * 2) break;
        vga[pos] = text[i];
        vga[pos + 1] = color;
        pos += 2;
    }
}
void print_char(char c, int str, int color)
{
    int pos = (str * 80) * 2;
    while (vga[pos] != empty_symbol)
    {
        pos += 2;
    }
    vga[pos] = c;
    vga[pos + 1] = color;
}
void replace_char(char c, int str, int col, int color)
{
    int pos = (str * 80 + col) * 2;
    vga[pos] = c;
    vga[pos] = color;
}
int get_symbol_color(int str, int col)
{
    int pos = (str * 80 + col) * 2;
    return vga[pos + 1];
}
int is_color_same(int old_color, int str, int col)
{
    int pos = (str * 80 + col) * 2;
    if (vga[pos + 1] != old_color) return 0;
    else return 1;
}
//* Cursor
int pos = (24 * 80) * 2;

void hide_cursor()
{
    vga[pos] = empty_symbol;
    vga[pos + 1] = 0x0a;
}
void show_cursor()
{
    pos = (24 * 80) * 2;
    while (vga[pos] != empty_symbol)
    {
        pos += 2;
    }

    vga[pos] = empty_symbol;
    vga[pos + 1] = 0xff; 
}