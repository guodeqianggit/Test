/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "inc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
//extern DMA_HandleTypeDef hdma_usart1_tx;
//extern unsigned char USART1_P_Rx;
//extern unsigned char USART1_RX_BUF[0x1000];     //接收缓冲,最大USART_REC_LEN个字节.

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/




/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}




/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN MemoryManagement_IRQn 1 */

  /* USER CODE END MemoryManagement_IRQn 1 */
}

/**
* @brief This function handles Pre-fetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN BusFault_IRQn 1 */

  /* USER CODE END BusFault_IRQn 1 */
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN UsageFault_IRQn 1 */

  /* USER CODE END UsageFault_IRQn 1 */
}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}






/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles DMA2 stream7 global interrupt.
*/
void DMA2_Stream7_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Stream7_IRQn 0 */

  /* USER CODE END DMA2_Stream7_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart1_tx);
  /* USER CODE BEGIN DMA2_Stream7_IRQn 1 */

  /* USER CODE END DMA2_Stream7_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



/** @defgroup TIM_Exported_Functions_Group7 TIM IRQ handler management 
 *  @brief    IRQ handler management 
 *
@verbatim   
  ==============================================================================
                        ##### IRQ handler management #####
  ==============================================================================  
  [..]  
    This section provides Timer IRQ handler function.
               
@endverbatim
  * @{
  */
/**
  * @brief  This function handles TIM interrupts requests.
  * @param  htim: pointer to a TIM_HandleTypeDef structure that contains
  *                the configuration information for TIM module.
  * @retval None
  */
//void HAL_TIM_IRQHandler(TIM_HandleTypeDef *htim)
//{
//  /* Capture compare 1 event */
//  if(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC1) != RESET)
//  {
//    if(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC1) !=RESET)
//    {
//      {
//        __HAL_TIM_CLEAR_IT(htim, TIM_IT_CC1);
//        htim->Channel = HAL_TIM_ACTIVE_CHANNEL_1;
//        
//        /* Input capture event */
//        if((htim->Instance->CCMR1 & TIM_CCMR1_CC1S) != 0x00U)
//        {
//          HAL_TIM_IC_CaptureCallback(htim);
//        }
//        /* Output compare event */
//        else
//        {
//          HAL_TIM_OC_DelayElapsedCallback(htim);
//          HAL_TIM_PWM_PulseFinishedCallback(htim);
//        }
//        htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
//      }
//    }
//  }
//  /* Capture compare 2 event */
//  if(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC2) != RESET)
//  {
//    if(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC2) !=RESET)
//    {
//      __HAL_TIM_CLEAR_IT(htim, TIM_IT_CC2);
//      htim->Channel = HAL_TIM_ACTIVE_CHANNEL_2;
//      /* Input capture event */
//      if((htim->Instance->CCMR1 & TIM_CCMR1_CC2S) != 0x00U)
//      {          
//        HAL_TIM_IC_CaptureCallback(htim);
//      }
//      /* Output compare event */
//      else
//      {
//        HAL_TIM_OC_DelayElapsedCallback(htim);
//        HAL_TIM_PWM_PulseFinishedCallback(htim);
//      }
//      htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
//    }
//  }
//  /* Capture compare 3 event */
//  if(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC3) != RESET)
//  {
//    if(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC3) !=RESET)
//    {
//      __HAL_TIM_CLEAR_IT(htim, TIM_IT_CC3);
//      htim->Channel = HAL_TIM_ACTIVE_CHANNEL_3;
//      /* Input capture event */
//      if((htim->Instance->CCMR2 & TIM_CCMR2_CC3S) != 0x00U)
//      {          
//        HAL_TIM_IC_CaptureCallback(htim);
//      }
//      /* Output compare event */
//      else
//      {
//        HAL_TIM_OC_DelayElapsedCallback(htim);
//        HAL_TIM_PWM_PulseFinishedCallback(htim); 
//      }
//      htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
//    }
//  }
//  /* Capture compare 4 event */
//  if(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_CC4) != RESET)
//  {
//    if(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_CC4) !=RESET)
//    {
//      __HAL_TIM_CLEAR_IT(htim, TIM_IT_CC4);
//      htim->Channel = HAL_TIM_ACTIVE_CHANNEL_4;
//      /* Input capture event */
//      if((htim->Instance->CCMR2 & TIM_CCMR2_CC4S) != 0x00U)
//      {          
//        HAL_TIM_IC_CaptureCallback(htim);
//      }
//      /* Output compare event */
//      else
//      {
//        HAL_TIM_OC_DelayElapsedCallback(htim);
//        HAL_TIM_PWM_PulseFinishedCallback(htim);
//      }
//      htim->Channel = HAL_TIM_ACTIVE_CHANNEL_CLEARED;
//    }
//  }
//  /* TIM Update event */
//  if(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_UPDATE) != RESET)
//  {
//    if(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_UPDATE) !=RESET)
//    {
//      __HAL_TIM_CLEAR_IT(htim, TIM_IT_UPDATE);
//      HAL_TIM_PeriodElapsedCallback(htim);
//    }
//  }
//  /* TIM Break input event */
//  if(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_BREAK) != RESET)
//  {
//    if(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_BREAK) !=RESET)
//    {
//      __HAL_TIM_CLEAR_IT(htim, TIM_IT_BREAK);
//      HAL_TIMEx_BreakCallback(htim);
//    }
//  }
//  /* TIM Trigger detection event */
//  if(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_TRIGGER) != RESET)
//  {
//    if(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_TRIGGER) !=RESET)
//    {
//      __HAL_TIM_CLEAR_IT(htim, TIM_IT_TRIGGER);
//      HAL_TIM_TriggerCallback(htim);
//    }
//  }
//  /* TIM commutation event */
//  if(__HAL_TIM_GET_FLAG(htim, TIM_FLAG_COM) != RESET)
//  {
//    if(__HAL_TIM_GET_IT_SOURCE(htim, TIM_IT_COM) !=RESET)
//    {
//      __HAL_TIM_CLEAR_IT(htim, TIM_FLAG_COM);
//      HAL_TIMEx_CommutationCallback(htim);
//    }
//  }
//}
//////////////////////////////////////////////////////////////////////////////
