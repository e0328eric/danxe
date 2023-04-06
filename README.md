# danxe language

Experimental language development inspired by [Tsoding's bm](https://github.com/tsoding/bm)

# Features

- [x] Implicit type conversion for arithmetic
- [x] Heap allocation (manually managed)
- [ ] Implement Command IO
- [ ] Turing Complete (proved by implementing a basic brainfuck interpreter with fixed memory)
- [ ] C like macro except include files
- [ ] Module system for assembler

# For the beta version

- [ ] Dynamically sized stack
- [ ] Array in the stack
- [ ] danxe language can be compiled into C code properly

# For the stable version

- [ ] Internal garbage collection
- [ ] Implement a new language whose target is danxeasm

# Build

## using cmake

```console
$ cmake -S . -B ./build
$ make -C ./build
```

# Toolchains

## danxevm

A virtual machine that executes danxe binary (`.dxb` files)

## danxeasm

Assembler for danxe binary. Uses `.dxa` file for input in general

## example usage

```console
$ cmake -S . -B ./build
$ make -C ./build
$ ./build/bin/danxeasm ../examples/fib.dxb -o fib.dxa
$ ./build/bin/danxevm fib.dxb
```
