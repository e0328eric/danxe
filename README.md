# danxe-lang

Experimental language development. Previously, I already had made another virtual machine quite completely -- called `glosso` but this source code
is removed in github today -- but I want to make another one with the register based machine instead of the stack based one.

# Features

- [ ] Heap allocation (manually managed)
- [ ] Implement Command IO
- [ ] Turing Complete (proved by implementing a basic brainfuck interpreter with fixed memory)
- [ ] Minimal Preprocessor Support

# For the beta version

- [ ] Dynamically sized stack
- [ ] Array in the stack
- [ ] Dynamic linking with C libraries (for example, running SDL2 in my machine)

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
