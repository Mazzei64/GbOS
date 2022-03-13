#!/bin/bash
echo "Making bootloader"
echo "Making kernel"
cd Kernel
./build.sh
cd ..
echo "Making bootimage"
echo "Emulate"