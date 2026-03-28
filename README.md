# C-OTP

A minimal command-line Time-based One-Time Password (TOTP) generator written in C. Implements RFC 6238. 
It relies on OpenSSL for HMAC-SHA1 calculations and generates standard 6-digit codes.

## Dependencies

The OpenSSL development headers are required for compilation.

* Ubuntu/Debian: `sudo apt install libssl-dev`
* macOS: `brew install openssl`

## Build

Compile the source code using make:

```bash
make
```

## Usage
First, you need to put your codes and names for them in the my_keys.txt, separate with space on each line
(e.g. "ABCDEFGHIJKLMNOPQ google.com")
Names for codes will be displayed as well. Algorithm supports multiple codes in the file.

Run the program from your terminal.
```bash
./totp 
```
## Example of output
```
============TOTP Generator============
123456 example.com
789012 some app
```

## Credits

The Base32 decoding implementation used in this project is based on the work of Adrien Kunysz, originally part of the mjg59/tpmtotp repository.

## License

This project is licensed under the MIT License. See the LICENSE file for details.
