#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define PACKED __attribute__((packed, aligned(1)))
struct Channels12Bit_4Chan {
#if __BYTE_ORDER == __LITTLE_ENDIAN
  uint32_t ch0 : 12;
  uint32_t ch1 : 12;
  uint32_t ch2 : 12;
  uint32_t ch3 : 12;
#elif __BYTE_ORDER == __BIG_ENDIAN
  uint32_t ch3 : 12;
  uint32_t ch2 : 12;
  uint32_t ch1 : 12;
  uint32_t ch0 : 12;
#else
#error "unsupported-endian architecture"
#endif
} PACKED;

int main()
{

  struct Channels12Bit_4Chan f;
  for(int i = -1; i < 49; ++i){
    memset(&f, 0x00, sizeof(f));
    uint8_t * p = (uint8_t*)&f;
    if(i >= 0 && i < 8 * (int)sizeof(f)) {
      p[i / 8] |= 1 << (i % 8);
    }
    printf("Bit=%2i ch0=%4u ch1=%4u ch2=%4u ch3=%4u\n", i, f.ch0, f.ch1, f.ch2, f.ch3);
  }

  return 0;
}

