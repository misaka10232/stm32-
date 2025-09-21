#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "AD.h"
#include "Delay.h"
uint16_t ADValue,ADValue1;
uint16_t currstate1,prevstate1;
uint16_t currstate2,prevstate2;

int x = 0;

//编码格式：UTF-8

int main(void)
{
	OLED_Init();
	AD_Init();

	
	while (1)
	{
		prevstate1 = currstate1;
		prevstate2 = currstate2;
		ADValue = AD_GetValue(ADC_Channel_0);
		currstate1 = ADValue; 
		ADValue1 = AD_GetValue(ADC_Channel_1);
		currstate2 = ADValue1;
		OLED_DrawPoint(x,128 - ((float)ADValue / 4095) * 128);
		OLED_DrawLine(x,128 - ((float)ADValue / 4095) * 128,x-1,128 - ((float)prevstate1 / 4095) * 128);
		OLED_DrawPoint(x,128 - ((float)ADValue1 / 4095) * 128);
		OLED_DrawLine(x,128 - ((float)ADValue1 / 4095) * 128,x-1,128 - ((float)prevstate2 / 4095) * 128);
		OLED_DrawPoint(x,128 - ((float)ADValue / 4095) * 128 + 1);
		OLED_DrawPoint(x,128 - ((float)ADValue / 4095) * 128 - 1);

		OLED_Update();
		x ++;
		if (x == 127)
		{
			x = 0;
			OLED_Clear();
			OLED_Update();
		}
	}
}
