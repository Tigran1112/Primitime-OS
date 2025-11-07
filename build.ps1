mkdir -Force build

nasm -f elf32 src\load.asm -o build\load.o

Get-ChildItem *.c | ForEach-Object {
    gcc -m32 -ffreestanding -nostdlib -c $_.Name -o build\"$($_.BaseName).o"
}


ld -m i386pe -T src\linker.ld -o build\kernel.bin build\*.o