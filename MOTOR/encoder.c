#include "ti_msp_dl_config.h"
#include "encoder.h"

volatile int32_t left_encoder = 0;
volatile int32_t right_encoder = 0;

// typedef struct
// {
//      int32_t left;
//      int32_t right;
//      int32_t sum_left;
//      int32_t sum_right;
// }Count;

void encoder_refresh(Count *count)
{
    count->err_left = (0.7f)*count->err_left + (0.3f)*(float)left_encoder;
    count->err_right = (0.7f)*right_encoder + (0.3f)*(float)right_encoder;
    count->sum_left += left_encoder;
    count->sum_right += right_encoder;
    left_encoder = right_encoder = 0;
}

void encoder_delete_sum(Count *count)
{
    count->sum_right = count->sum_left = 0;
}

void encoder_delete_err(Count *count)
{
    count->err_left = count->err_right = 0;
}

void encoder_delete_all(Count *count)
{
    count->err_left = count->err_right = 0;
    count->sum_left = count->sum_right = 0;
    left_encoder = right_encoder = 0;
}