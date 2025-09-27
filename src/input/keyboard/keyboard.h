#ifndef KEYBOARD_H
#define KEYBOARD_H

char scan2char(unsigned char scancode);
unsigned char inb(unsigned short port);
unsigned char read_keyboard();

#endif