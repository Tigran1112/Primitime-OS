#include "interprer/ports/ports.h"
#include "screen/screen.h"

void shutdown()
{
    outw(0xb004, 0x2000);
    outw(0x604, 0x2000);
    outw(0x4004, 0x3400);

    print("Shutdown failed. Please turn off PC manually (it`s safe. Don`t belive IT teacher)", 0, 0x0a);
    __asm__ volatile("cli; hlt");
}
void reboot()
{
    while (inb(0x64) & 0x02) {}
    outb(0x64, 0xfe);
    __asm__ volatile("int $0xff");
}