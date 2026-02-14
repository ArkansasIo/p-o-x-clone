@echo off
REM Batch script to assemble, pack, and run a PO-X game ROM

set ASM=tools\assemble_pox.py
set PACKER=build\tools\rom_packer\Debug\pox_rom_packer.exe
set EMU=build\apps\desktop_sdl\Debug\pox_desktop.exe
set EXAMPLE=sdk\examples\hello_world

REM Assemble pseudo-assembly to binary
python %ASM% %EXAMPLE%\main.pseudo.asm %EXAMPLE%\hello_world.bin

REM Pack binary to .poxr ROM
%PACKER% %EXAMPLE%\hello_world.bin %EXAMPLE%\hello_world.poxr

REM Run emulator with the new ROM
%EMU% %EXAMPLE%\hello_world.poxr
