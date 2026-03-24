#include "base32.h"
#include "totp.h"
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <stdio.h>
#include <string.h>

int main(void) {
  const char *secret = "vl34qjrsmycbmr2esltwt5h2fjdqe7pp";
  int len = strlen(secret);

  unsigned char decoded_key[20] = {0};
  size_t decoded_bytes = base32_decode(secret, len, decoded_key);

  if (decoded_bytes != 20) {
    printf("Error\n");
    return 1;
  }

  unsigned char time_data[8] = {0};
  get_current_time_bytes(time_data);

  unsigned char hmac_result[EVP_MAX_MD_SIZE];
  unsigned int hmac_len;
  HMAC(EVP_sha1(), decoded_key, decoded_bytes, time_data, sizeof(time_data), hmac_result, &hmac_len);

  uint32_t totp_code = truncate_hash_to_code(hmac_result);

  printf("%06u\n", totp_code);

  return 0;
}
