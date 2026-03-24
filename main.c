#include "base32.h"
#include "totp.h"
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

/*
 * Function to get the TOT code from the secret and current time.
 */
uint32_t get_totp_code(const unsigned char *key, size_t key_len) {
  unsigned char time_data[8] = {0};
  get_current_time_bytes(time_data); // Get current time.

  unsigned char hmac_result[EVP_MAX_MD_SIZE];
  unsigned int hmac_len;

  // Calculate HMA(SHA-1) using OpenSSL.
  HMAC(EVP_sha1(), key, key_len, time_data, sizeof(time_data), hmac_result, &hmac_len);

  return truncate_hash_to_code(hmac_result);
}

// Funtion to draw the interface.
void display_status(uint32_t code, int seconds_left) {
  printf("\rCurrent Code: %06u  [", code);

  // Draw progress-bar.
  for (int i = 0; i < 15; i++) {
    if (i < (seconds_left / 2)) printf("#");
    else printf("_");
  }

  printf("] %02ds", seconds_left);
  fflush(stdout);
}

/*
 * Main body:
 * 1) decode the key
 * 2) LOOP: update the code every 30s.
 */
int main(int argc, char *argv[]) {
  const char *secret = argv[1];
  unsigned char decoded_key[20];

  size_t key_len = base32_decode((const unsigned char *)secret, strlen(secret), decoded_key);
  if (key_len != 20) {
    fprintf(stderr, "Invalid secret key!\n");
    return 1;
  }

  while (1) {
    time_t now = time(NULL);
    int seconds_remaining = 30 - (now % 30);

    // Get the data.
    uint32_t current_code = get_totp_code(decoded_key, key_len);

    // 2. Display the data.
    display_status(current_code, seconds_remaining);

    // 3. Wait for the next step.
    sleep(1);
  }

  return 0;
}
