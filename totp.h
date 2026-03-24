#ifndef TOTP_H
#define TOTP_H

#include <stdint.h>

void get_current_time_bytes(unsigned char *time_array);
uint32_t truncate_hash_to_code(const unsigned char *hmac_result);

#endif
