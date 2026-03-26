# C-OTP

A minimal command-line Time-based One-Time Password (TOTP) generator written in C. It relies on OpenSSL for HMAC-SHA1 calculations and generates standard 6-digit codes.

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
Run the program from your terminal. It will securely prompt you to enter your Base32 secret key:

```bash
./totp 
```

Example of interaction:

```bash 
TOTP Generator
Please enter your Base32 secret key (e.g., JBSWY3DPEHPK3PXP):
> JBSWY3DPEHPK3PXP
Current Code: 123456
```

## Credits

The Base32 decoding implementation used in this project is based on the work of Adrien Kunysz, originally part of the mjg59/tpmtotp repository.

## License

This project is licensed under the MIT License. See the LICENSE file for details.
