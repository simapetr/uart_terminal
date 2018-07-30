uart_terminal
-------------

This is windows terminl for UART communication with JavaScript support.

Supported function:

- Set UART communication parameter
- Direct read and write data in text and HEX format
- Control DTR, RTS and Tx(break) line
- Read CTS, DSR, RING and RLSD
- Load JavaScript

The project is based on:

- wxWidget 3.0 GUI (https://github.com/wxWidgets/wxWidgets)
- Jerry script ECMAScript 5.1 (https://github.com/jerryscript-project/jerryscript)
- Windows file access

Platforms
---------

Supported platforms:

- Windows XP, Vista, 7, 8 and 10 (32/64 bits).

Building
--------

Builded in Code::Blocks by MinGW 4.6.2.

For compilation is necesery wxWidget 3.0.4

Build commands

SET PATH=C:\MinGW\bin;C:\MinGW\mingw32\bin

mingw32-make -f makefile.gcc SHARED=0 MONOLITHIC=1 UNICODE=1 BUILD=release

mingw32-make -f makefile.gcc SHARED=0 MONOLITHIC=1 UNICODE=1 BUILD=debug
