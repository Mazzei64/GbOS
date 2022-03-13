#!/bin/bash
echo "Entering kernel build stage..."
../../../Downloads/smlrc kernel.c kernel.inc
nasm start.asm -o ../kernel16.exe