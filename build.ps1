mkdir -Force build

# 1. Ассемблер
nasm -f elf32 src\load.asm -o build\load.o

# 2. Компилируем C файлы
Get-ChildItem *.c | ForEach-Object {
    gcc -m32 -ffreestanding -nostdlib -c $_.Name -o build\"$($_.BaseName).o"
}

# 3. Линкуем ЧЕРЕЗ СКРИПТ
ld -m i386pe -T src\linker.ld -o build\kernel.bin build\*.o