#include "ti_msp_dl_config.h"
volatile int ec11_now_data = 0;
volatile int ec11_last_data = 0;
volatile int ec11_err = 0;

int get_ec11_err(void)
{
    ec11_err = ec11_now_data - ec11_last_data;
    ec11_last_data = ec11_now_data;
    return ec11_err;
}

int get_ec11_now(void)
{
    return ec11_now_data;
}