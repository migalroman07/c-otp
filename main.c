#include "base32.h"       // base32_decode()
#include "totp.h"         // get_current_time_bytes(), truncate_hash_to_code()
#include <openssl/evp.h>  // EVP_MAX_MD_SIZE, EVP_sha1()
#include <openssl/hmac.h> // HMAC()
#include <stdint.h>       // uint32_t
#include <stdio.h>        // printf(), fprintf(), fgets(), stdin, stderr
#include <string.h>       // strlen(), strcspn()
#include <time.h>         // time()

// Function declaration.
uint32_t get_totp_code(const unsigned char *key, size_t key_len);

/*
 * Main body:
 * 1) Prompt for the key.
 * 2) Decode the key.
 * 3) Output the current TOTP code once.
 */
int main(void) {
  char secret[256];
  unsigned char decoded_key[64];

  printf("==========TOTP Generator==========\n");
  printf("Please enter your Base32 secret key\n(e.g., JBSWY3DPEHPK3PXP, lower register is suppoted as well.):\n> ");

  // Handle empty or failed input.
  if (fgets(secret, sizeof(secret), stdin) == NULL) {
    fprintf(stderr, "Error reading input.\n");
    return 1;
  }

  // Remove trailing newline.
  secret[strcspn(secret, "\n")] = 0;

  // Handle empty string after removing newline.
  if (strlen(secret) == 0) {
    fprintf(stderr, "Error: Secret key cannot be empty.\n");
    return 1;
  }

  size_t key_len = base32_decode((const unsigned char *)secret, strlen(secret), decoded_key);
  if (key_len < 16) {
    fprintf(stderr, "Error: Invalid secret key!\n");
    return 1;
  }

  // Get the TOTP code.
  uint32_t current_code = get_totp_code(decoded_key, key_len);

  // Display the code.
  printf("Current Code: %06u\n", current_code);

  return 0;
}

/*
 * Function to get the TOTP code from the secret and current time.
 */
uint32_t get_totp_code(const unsigned char *key, size_t key_len) {
  unsigned char time_data[8] = {0};
  get_current_time_bytes(time_data); // Get current time.

  unsigned char hmac_result[EVP_MAX_MD_SIZE];
  unsigned int hmac_len;

  // Calculate HMAC(SHA-1) using OpenSSL.
  HMAC(EVP_sha1(), key, key_len, time_data, sizeof(time_data), hmac_result, &hmac_len);

  return truncate_hash_to_code(hmac_result);
}
