#ifndef __ENCODER_H_
#define __ENCODER_H_

typedef struct
{
     float err_left;
     float err_right;
     float sum_left;
     float sum_right;
}Count;

void encoder_refresh(Count *count);

void encoder_delete_sum(Count *count);

void encoder_delete_err(Count *count);

void encoder_delete_all(Count *count);

#endif