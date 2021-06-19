# One-Sided Malicious Private Set Intersection

## Installation
The implementation has been tested on Linux. To download the code and compile, run the following commands. It will also download and compile the libraries of [`libOTe`](https://github.com/osu-crypto/libOTe), [`Boost`](https://sourceforge.net/projects/boost/), and [`Miracl`](https://github.com/miracl/MIRACL).
```
$ git clone --recursive https://github.com/XXcryptoman/OMPSI.git
$ cd OMPSI
$ bash compile
```

## Running the Code
### Parameters:
```
-r 0/1   to run a sender/receiver.
-ss      log of the set size on sender side.
-rs      log of the set size on receiver side.
-ip      ip address (and port).
-exp   repetition times on calling functions
```
### Examples:
```
$ ./bin/PSI_test -r 0 -ss 16 -rs 16  -ip 127.0.0.1
  & ./bin/PSI_test -r 1 -ss 16 -rs 16  -ip 127.0.0.1

$ ./bin/PSI_test -r 0 -ss 18 -rs 18  -ip 127.0.0.1
  & ./bin/PSI_test -r 1 -ss 18 -rs 18 -ip 127.0.0.1

$ ./bin/PSI_test -exp  100000
```

