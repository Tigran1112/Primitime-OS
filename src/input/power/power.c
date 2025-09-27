void shutdown() 
{
    __asm__ volatile(
        "mov $0x2000, %ax \n"
        "mov $0x604, %dx \n"
        "out %ax, %dx \n"

        "mov $0x2000, %ax \n"
        "mov $0xb004, %dx \n"
        "out %ax, %dx \n"
    );
}
void reboot() 
{
    __asm__ volatile("int $0xff \n");
}