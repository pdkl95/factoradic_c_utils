# factoradic_c_utils

_Fast_ utilites to convert integers between decimal (base 10) and factoradic representation (factorial hase).

## Installing

### Dependencies

* A working C compiler (both gcc and clang have beentested.

* [GMP](https://gmplib.org/)

### Downloading the source

Download the project with git:

    git clone https://github.com/pdkl95/factoradic_c_utils.git

or download and unpack the [zip arhive](https://github.com/pdkl95/factoradic/archive/refs/heads/main.zip) provided by GitHub.

### Building the Util Programs

    ./configure
    make
    make check    # optional
    make install

See ./configure --help for a list a buils and install options..

If the autoconf script cannot find gmp, you can provide the location of the librarey and header file directly with the --with-gmp-include=DIR and --with-gmp-lib=OPTIONS

## Usage

### Converting decimal to factoradic

    $ dec2fact 719
    5:4:3:2:1:0

    $ dec2fact 720
    1:0:0:0:0:0:0

    $ dec2fact -d ',' 720
    1,0,0,0,0,0,0

### converting factoradic to decimal


    $ fact2dec 5:4:3:2:1:0
    719

    $ fact2dec 1:0:0:0:0:0:0
    720

    $ fact2dec -d ',' 1,0,0,0,0,0,0
    720

## License

Copyright 2022 Brent Sanders

factoradic_c_utils is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

factoradic_c_utils is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with factoradic_c_utils. If not, see <https://www.gnu.org/licenses/>.
