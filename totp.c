#include "totp.h" // get_current_time_bytes(), truncate_hash_to_code()
#include <time.h> // time(), NULL

#define MASK_BYTE 0xFF   // Mask to extract 8 bits.
#define MASK_OFFSET 0x0F // Mask to get the 4-bit offset.
#define MASK_SIGN 0x7F   // Mask to ignore the sign bit.

/*
 * Creates a time array with number of 30-second intervals since Unix epoch.
 */
void get_current_time_bytes(unsigned char *time_array) {
  uint64_t current_steps = time(NULL) / 30;
  for (int i = 7; i >= 0; i--) {
    time_array[i] = current_steps & MASK_BYTE;
    current_steps >>= 8;
  }
}

/*
 * Truncate the resulting hash to get the final code.
 */
uint32_t truncate_hash_to_code(const unsigned char *hmac_result) {
  int offset = hmac_result[19] & MASK_OFFSET;
  uint32_t binary = ((hmac_result[offset] & MASK_SIGN) << 24) | ((hmac_result[offset + 1] & MASK_BYTE) << 16) |
                    ((hmac_result[offset + 2] & MASK_BYTE) << 8) | (hmac_result[offset + 3] & MASK_BYTE);

  return binary % 1000000;
}
