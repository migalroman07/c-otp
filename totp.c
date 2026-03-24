#include "totp.h"
#include <time.h>

/*
 * Creates a time array with number of 30-second intervals since Unix epoch.
 */
void get_current_time_bytes(unsigned char *time_array) {
  uint64_t current_steps = time(NULL) / 30;
  for (int i = 7; i >= 0; i--) {
    time_array[i] = current_steps & 0xFF;
    current_steps >>= 8;
  }
}

/*
 * Truncate the resulting hash to get the final code.
 */
uint32_t truncate_hash_to_code(const unsigned char *hmac_result) {
  int offset = hmac_result[19] & 0x0F;
  uint32_t binary = ((hmac_result[offset] & 0x7F) << 24) | ((hmac_result[offset + 1] & 0xFF) << 16) |
                    ((hmac_result[offset + 2] & 0xFF) << 8) | (hmac_result[offset + 3] & 0xFF);
  return binary % 1000000;
}
