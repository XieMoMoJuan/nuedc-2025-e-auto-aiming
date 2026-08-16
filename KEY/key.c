#include "ti_msp_dl_config.h"
#include "key.h"
uint8_t KeyFlag = 0;
uint8_t NextFlag = 0;
uint8_t Key0Time = 0;
uint8_t Key1Time = 0;

// 20ms调用一次
uint8_t scanKeys(void)
{
    if (KeyFlag == 0)
    {
        if (DL_GPIO_readPins(KEYS_PORT, KEYS_KEY0_PIN) == KEYS_KEY0_PIN)
        {
            KeyFlag = 1;
            NextFlag = 0;
        }
        else if (DL_GPIO_readPins(KEYS_PORT, KEYS_KEY1_PIN) == KEYS_KEY1_PIN)
        {
            KeyFlag = 1;
            NextFlag = 1;
        }
    }
    if (KeyFlag == 1)
    {
        switch (NextFlag)
        {
        case 0:
            if (DL_GPIO_readPins(KEYS_PORT, KEYS_KEY0_PIN) == 0)
            {
                KeyFlag = 0;
                if (Key0Time >= 10)
                {
                    Key0Time = 0;
                    return KEY0_LONG;
                }
                Key0Time = 0;
                return KEY0;
            }
            else
            {
                Key0Time++;
                if (Key0Time > 250) Key0Time = 250;
            }
            break;
        case 1:
            if (DL_GPIO_readPins(KEYS_PORT, KEYS_KEY1_PIN) == 0)
            {
                KeyFlag = 0;
                if (Key1Time >= 10)
                {
                    Key1Time = 0;
                    return KEY1_LONG;
                }
                Key1Time = 0;
                return KEY1;
            }
            else
            {
                Key1Time++;
                if (Key1Time > 250) Key1Time = 250;
            }
            break;
        }
    }
    return KEY_NULL;
}