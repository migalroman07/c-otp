#ifndef BASE32_H
#define BASE32_H

#include <stddef.h>
/*
 *Just declare base_32 encoding function.
 */
size_t base32_decode(const unsigned char *coded, size_t coded_len, unsigned char *plain);

#endif
