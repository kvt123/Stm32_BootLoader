
#include "gpio.h"



void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
  /* Reset GPIO init structure parameters values */
  GPIO_InitStruct->GPIO_Pin  = GPIO_Pin_13;
  GPIO_InitStruct->GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStruct->GPIO_Mode = GPIO_Mode_Out_PP;
}


void HAL_GPIO_Init(GPIO_TypeDef * GPIOx, GPIO_InitTypeDef * GPIO_InitStruct)
{
    uint32_t currentMode = 0x00, currentPin = 0x00, pinPos = 0x00, pos = 0x00;
    uint32_t tmpReg = 0x00, pinMask = 0x00;


/*---------------------------- GPIO Mode Configuration -----------------------*/  

    currentMode = ((GPIO_InitStruct->GPIO_Mode) & 0x0F);

    if(((GPIO_InitStruct->GPIO_Mode)& 0x10) != 0x00)
    {
        currentMode |=  GPIO_InitStruct->GPIO_Speed;
    }

/*---------------------------- GPIO CRL Configuration ------------------------*/

    if((GPIO_InitStruct->GPIO_Pin & ((uint32_t)0x00FF)) != 0x00)
    {

        tmpReg = GPIOx->CRL;
        for(pinPos=0; pinPos <0x08; pinPos++)
        {
            currentPin = 0x01 << pinPos;
            pos = (GPIO_InitStruct->GPIO_Pin)&((uint32_t)0x00FF);
            if(pos == currentPin)
            {
                /* clear 4 bit using */
                pinMask = ((0x0F)<< (pinPos*4));
                tmpReg &= ~pinMask;
                /* write user init config struct value to CRL */
                tmpReg |= currentMode << (pinPos*4);

                /* Reset the corresponding ODR bit */
                if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
                {
                  GPIOx->BRR = (((uint32_t)0x01) << pinPos);
                }
                else
                {
                  /* Set the corresponding ODR bit */
                  if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
                  {
                    GPIOx->BSRR = (((uint32_t)0x01) << pinPos);
                  }
                }
                

            }
        }

        GPIOx->CRL = tmpReg;
    }


/*---------------------------- GPIO CRH Configuration ------------------------*/

    if(((GPIO_InitStruct->GPIO_Pin) & 0xFF00) != 0x00)
    {

        tmpReg = GPIOx->CRH;
        for(pinPos=0; pinPos <0x08; pinPos++)
        {
            currentPin = 0x01 << pinPos;

            pos = ((GPIO_InitStruct->GPIO_Pin)>>8)&((uint32_t)0x00FF);
            if(pos == currentPin)
            {
                /* clear 4 bit using */
                pinMask = ((0x0F)<< (pinPos*4));
                tmpReg &= ~pinMask;
                /* write user init config struct value to CRL */
                tmpReg |= currentMode << (pinPos*4);
                 /* Reset the corresponding ODR bit */
                if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPD)
                {
                  GPIOx->BRR = (((uint32_t)0x01) << (pinPos + (uint32_t)0x08));
                }
                /* Set the corresponding ODR bit */
                if (GPIO_InitStruct->GPIO_Mode == GPIO_Mode_IPU)
                {
                  GPIOx->BSRR = (((uint32_t)0x01) << (pinPos + (uint32_t)0x08));
                }
            }
        }

        GPIOx->CRH = tmpReg;
    }


}

void HAL_GPIO_Write_Pin(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin,BitAction PinState)
{
    if(PinState == Bit_SET)
    {
        /* set bit*/
        GPIOx->BSRR |= GPIO_Pin;
    }
    else
    {
       GPIOx->BRR = GPIO_Pin;
    }

}


BitAction HAL_GPIO_Read_Pin(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
    uint8_t bitStatus = Bit_RESET;
    if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)Bit_RESET)
    {
      bitStatus = (uint8_t)Bit_SET;
    }
    else
    {
      bitStatus = (uint8_t)Bit_RESET;
    }
    return bitStatus;
}

void HAL_GPIO_Toggle_Pin(GPIO_TypeDef *GPIOx, uint32_t GPIO_Pin)
{
    if(HAL_GPIO_Read_Pin(GPIOx,GPIO_Pin) == Bit_SET)
    {
        HAL_GPIO_Write_Pin(GPIOx, GPIO_Pin, Bit_RESET);
    }
    else
    {
         HAL_GPIO_Write_Pin(GPIOx, GPIO_Pin, Bit_SET);
    }

}
