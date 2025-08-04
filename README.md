# Lisp Interpreter

This is a interpreter for a programming language, a minimal lisp. It is being made by following the guide in [this book](https://buildyourownlisp.com/chapter1_introduction#about). This is a WIP - I plan to add more onto it in the future.

## Prerequisites

The editline library is required to compile the program. On Mac, this should be included with Command Line Tools. If you are on Linux, you will need to install it from a package manager.

### Ubuntu / Debian

```
sudo apt-get install libedit-dev
```

### Fedora

```
su -c "yum install libedit-dev*"
```

## Build

```
cc -std=c99 -Wall lisp-interpreter.c mpc.c -ledit -lm -o lisp-interpreter
```

## Test Commands

The program can be tested with some input.

```
kulisp> list 1 2 3 4
{1 2 3 4}
kulisp> {head (list 1 2 3 4)}
{head (list 1 2 3 4)}
kulisp> eval {head (list 1 2 3 4)}
{1}
kulisp> tail {tail tail tail}
{tail tail}
kulisp> eval (tail {tail tail {5 6 7}})
{6 7}
kulisp> eval (head {(+ 1 2) (+ 10 20)})
3
```

