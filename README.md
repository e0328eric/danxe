# danxe-lang

Experimental language development

# Features

- [ ] Implicit type conversion for arithmetic
- [ ] Heap allocation (manually managed)
- [ ] Implement Command IO
- [ ] Turing Complete (proved by implementing a basic brainfuck interpreter with fixed memory)
- [ ] Minimal Preprocessor Support

# For the beta version

- [ ] Dynamically sized stack
- [ ] Array in the stack
- [ ] glosso language can be compiled into C code properly

# For the stable version

- [ ] Internal garbage collection
- [ ] Implement a new language whose target is glasm

# Build

## using cmake

```console
$ cmake -S . -B ./build
$ make -C ./build
```

# Toolchains

## dxevm

A virtual machine that executes glosso binary (`.dxe` files)

## danxe

Assembler for glosso binary. Uses `.dxet` file for input in general

## example usage

```console
$ cmake -S . -B ./build
$ make -C ./build
$ ./build/bin/danxe ../examples/fib.glasm -o fib.dxet
$ ./build/bin/dxevm fib.dxe
```
