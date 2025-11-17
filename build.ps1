mkdir -Force build

nasm -f elf32 src\load.asm -o build\load.o

Get-ChildItem src\*.c -Recurse | ForEach-Object {
    $source = $_.FullName
    $output = "build\$($_.BaseName).o"
    Write-Output "Compiling $source..."
    i686-elf-gcc -m32 -ffreestanding -nostdlib -I src -c $source -o $output -Wno-implicit-function-declaration
}

$object = @()
Get-ChildItem build\*.o -Recurse | ForEach-Object {
    $object += $_.FullName
}

i686-elf-ld -T src\linker.ld -o build\kernel.elf $object

i686-elf-objcopy -O binary build\kernel.elf build\kernel.bin

qemu-system-i386 -kernel build\kernel.elf

cls
