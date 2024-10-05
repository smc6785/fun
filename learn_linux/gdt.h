#ifndef __GDT_H 
#define __GDT_H

typedef struct
{
  uint16_t limit_low;
  uint16_t base_low;
  uint8_t base_high;
  uint8_t type;
  uint8_t flags_limit_high;
  uint8_t base_vhigh;
} segment_descriptor;

uint32_t base(void);
uint32_t limit(void);

segment_descriptor null_segment_selector;
segment_descriptor unused_segment_selector;
segment_descriptor code_segment_selector;
segment_descriptor data_segment_selector;
#endif
