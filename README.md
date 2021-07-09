# ft_ssl

Partial recreation of openSSL utility

## Supported Ciphers

* MD5
* SHA224
* SHA256
* SHA384
* SHA512
* SHA512_224
* SHA512_256

## Installation
1. Download/Clone this repo
```
git clone https://github.com/TheWeaklessOne/ft_ssl.git
```
2. `cd` into directrory and run `make`
```
make
./ft_openssl
```
## Main project instructions
#### General Instructions
- Project must be written in C in accordance with [the Norm](https://github.com/R4meau/minishell/blob/master/norme.en.pdf).
- Program cannot have memory leaks.
- No Segmentation fault, bus error, double free, etc.
- Recode the openSSL utility.
- Allowed to use the following functions:
  - *write*
  - *open*
  - *close*
  - *malloc*
  - *free*
  - *exit*
#### Bonus Part
  - Flag '-s' to set string to translate. Example: ./ft_ssl sha384 -s "example"
  - Flag '-p' echo stdin to stdout and append the checksum to stdout
  - Flag '-q' to enter the silent mode
