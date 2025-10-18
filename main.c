#include <arpa/inet.h>
#include <assert.h>
#include <endian.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CRSF_MAX_CHANNELS   24U      // Maximum number of channels from crsf datastream
#define CRSF_FRAMELEN_MAX   64U      // maximum possible framelength
#define CRSF_HEADER_LEN     2U       // header length
#define CRSF_FRAME_PAYLOAD_MAX (CRSF_FRAMELEN_MAX - CRSF_HEADER_LEN)     // maximum size of t>
#define CRSF_FRAME_LENGTH_MIN 2 // min value for _frame.length
#define CRSF_BAUDRATE      416666U
#define ELRS_BAUDRATE      420000U
#define CRSF_TX_TIMEOUT    500000U   // the period after which the transmitter is considered >
#define CRSF_RX_TIMEOUT    150000U   // the period after which the receiver is considered dis>

#define PACKED __attribute__((packed, aligned(1)))

struct Channels12Bit_4Chan {
#if __BYTE_ORDER == __LITTLE_ENDIAN
  uint32_t ch0 : 12;
  uint32_t ch1 : 12;
  uint32_t ch2 : 12;
  uint32_t ch3 : 12;
#elif __BYTE_ORDER == __BIG_ENDIAN
  uint32_t ch0 : 12;
  uint32_t ch1 : 12;
  uint32_t ch2 : 12;
  uint32_t ch3 : 12;
#else
#error "unsupported-endian architecture"
#endif
} PACKED;


    struct SubsetChannelsFrame {
#if __BYTE_ORDER == __LITTLE_ENDIAN
        uint8_t starting_channel:5;     // which channel number is the first one in the frame
        uint8_t res_configuration:2;    // configuration for the RC data resolution (10 - 13 >
        uint8_t digital_switch_flag:1;  // configuration bit for digital channel
#elif __BYTE_ORDER == __BIG_ENDIAN
        uint8_t digital_switch_flag:1;  // configuration bit for digital channel
        uint8_t res_configuration:2;    // configuration for the RC data resolution (10 - 13 >
        uint8_t starting_channel:5;     // which channel number is the first one in the frame
#else
#error "unsupported-endian architecture"
#endif
        uint8_t channels[CRSF_FRAME_PAYLOAD_MAX - 2]; // payload less byte above
        // uint16_t channel[]:res;      // variable amount of channels (with variable resolut>
                                        // on the res_configuration) based on the frame size
        // uint16_t digital_switch_channel[]:10; // digital switch channel
    } PACKED;

    struct PACKED VTXFrame {
        uint8_t flags;
        uint16_t frequency;         // frequency in Mhz
        uint16_t power;              // power in mw, 0 == off
#if __BYTE_ORDER == __LITTLE_ENDIAN
        uint8_t band : 4;               // A, B, E, AirWave, Race
        uint8_t channel : 4;            // 1x-8x
#elif __BYTE_ORDER == __BIG_ENDIAN
        uint8_t channel : 4;            // 1x-8x
        uint8_t band : 4;               // A, B, E, AirWave, Race
#else
#error "Unsupported-endian architecture"
#endif
        uint8_t spare[3];
    };

int main()
{
  printf("Testing SubsetChannelsFrame:\n");
  for(int i = -1; i < 17; ++i){
    struct SubsetChannelsFrame f;
    memset(&f, 0x00, sizeof(f));
    uint8_t * p = (uint8_t*)&f;
    if(i >= 0 && i < 8 * (int)sizeof(f)) {
      p[i / 8] |= 1 << (i % 8);
    }
    printf("Bit=%2i word=0x%02x%02x starting_channel=%4u res_configuration=%4u digital_switch_flag=%u\n",
        i,
        p[0],p[1],
        f.starting_channel,
        f.res_configuration,
        f.digital_switch_flag);
  }
  printf("\n");

  printf("Testing Channels12Bit_4Chan:\n");
  for(int i = -1; i <= 48; ++i){
    struct Channels12Bit_4Chan f;
    memset(&f, 0x00, sizeof(f));
    uint8_t * p = (uint8_t*)&f;
    if(i >= 0 && i < 8 * (int)sizeof(f)) {
      p[i / 8] |= 1 << (i % 8);
    }
    printf("Bit=%2i word=0x%02x%02x%02x%02x%02x%02x ch0=0x%04x ch1=0x%04x ch2=0x%04x ch3=0x%04x\n",
        i,
        p[0],p[1],p[2],p[3],p[4],p[5],
        f.ch0, f.ch1, f.ch2, f.ch3);
  }
  printf("\n");

  printf("Testing VTXFrame:\n");
  for(int i = -1; i <= 72; ++i){
    struct VTXFrame f;
    memset(&f, 0x00, sizeof(f));
    uint8_t * p = (uint8_t*)&f;
    if(i >= 0 && i < 8 * (int)sizeof(f)) {
      p[i / 8] |= 1 << (i % 8);
    }
    printf("Bit=%2i word=0x%02x%02x%02x%02x%02x%02x%02x%02x%02x flags=0x%04x freq=0x%04x power=0x%04x band=0x%04x channel=0x%04x s0=0x%02x s1=0x%02x s2=0x%02x\n",
        i,
        p[0],p[1],p[2],p[3],p[4],p[5],p[6],p[7],p[8],
        f.flags, ntohs(f.frequency), ntohs(f.power), f.band, f.channel, f.spare[0], f.spare[1], f.spare[2]);
  }
  printf("\n");

  return 0;
}

