# Woody-Woodpacker

## what is packing?
make executable encrypted to avoid reverse engineering (such as virus software) and process is as follows.

## my method.
* add decrypt STUB at the end of the file (with alignment in compliance to ABI).
* after the STUB, add PAYLOAD to decrypt and I added new elf program header table.
* the new program header table is expanded by one to indicate the above as PT_LOAD
* elf header's entry point to be changed at the head of STUB
* new phdr should reflect all the changes.

## decoder_stub creation
1. `nasm -f bin <file.s>`
1. `xxd -i <decoder.bin> > decoder_stub.h`

## limitations
1. only compatible to X86-64
1. only little endien

## refrence
アナライジング・マルウェア
