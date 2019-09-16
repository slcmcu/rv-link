#ifndef __RV_LINK_TAP_H__
#define __RV_LINK_TAP_H__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "rvl-tap-config.h"

typedef enum rvl_tap_state_e
{
  RVL_TAP_STATE_TEST_LOGIC_RESET = 0,
  RVL_TAP_STATE_RUN_TEST_IDLE,
  RVL_TAP_STATE_SELECT_DR_SCAN,
  RVL_TAP_STATE_SELECT_IR_SCAN,

  RVL_TAP_STATE_CAPTURE_DR,
  RVL_TAP_STATE_SHIFT_DR,
  RVL_TAP_STATE_EXIT1_DR,
  RVL_TAP_STATE_PAUSE_DR,
  RVL_TAP_STATE_EXIT2_DR,
  RVL_TAP_STATE_UPDATE_DR,

  RVL_TAP_STATE_CAPTURE_IR,
  RVL_TAP_STATE_SHIFT_IR,
  RVL_TAP_STATE_EXIT1_IR,
  RVL_TAP_STATE_PAUSE_IR,
  RVL_TAP_STATE_EXIT2_IR,
  RVL_TAP_STATE_UPDATE_IR,
}rvl_tap_state_t;

void rvl_tap_init(void);
void rvl_tap_fini(void);
int rvl_tap_tick(int tms, int tdi);
rvl_tap_state_t rvl_tap_trace_state(int tms);
void rvl_tap_shift(uint32_t* old, uint32_t *new, size_t len, uint8_t pre, uint8_t post);
void rvl_tap_shift_ir(uint32_t* old_ir, uint32_t* new_ir, size_t ir_len);
void rvl_tap_shift_dr(uint32_t* old_dr, uint32_t* new_dr, size_t dr_len);
void rvl_tap_go_idle(void);
void rvl_tap_run(uint32_t ticks);

#ifdef RVL_TAP_CONFIG_DYN
void rvl_tap_config(uint8_t ir_pre, uint8_t ir_post, uint8_t dr_pre, uint8_t dr_post);
#endif // RVL_TAP_CONFIG_DYN

#endif /* __RV_LINK_TAP_H__ */
