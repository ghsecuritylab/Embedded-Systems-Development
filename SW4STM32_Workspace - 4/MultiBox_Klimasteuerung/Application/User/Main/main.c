/** \file
 *  \brief
 *
 *
 */

/** \addtogroup System
 *  @{
 */


#include "main.h"
uint8_t SD_Mounted = 0;
uint8_t SD_LOCK = 0;
uint8_t QSPI_status = 0;
uint8_t GUI_Initialized = 0;
uint8_t LoadingFinished = 0;

TIM_HandleTypeDef TimHandle;
IWDG_HandleTypeDef IwdgHandle;
IWDG_InitTypeDef IwdgInit;

uint32_t uwPrescalerValue = 0;

/* Private function prototypes -----------------------------------------------*/
static void SystemClock_Config(void);
void BSP_Background(void);

static void MPU_Config();
static void CPU_CACHE_Enable(void);

uint8_t ubKeyNumber = 0x0;

enum
{
    TRANSFER_WAIT,
    TRANSFER_COMPLETE,
    TRANSFER_ERROR
};

/* transfer state */
__IO uint32_t wTransferState = TRANSFER_WAIT;



//GUIControl
extern void MainTask(void);
struct clickBoard * Board_EXPAND4_Board_EXPAND4_Relaiskarte;


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */


int main(void)
{
    /* STM32F7xx HAL library initialization:
         - Configure the Flash ART accelerator on ITCM interface
         - Configure the Systick to generate an interrupt each 1 msec
         - Set NVIC Group Priority to 4
         - Global MSP (MCU Support Package) initialization
       */
    CPU_CACHE_Enable();

    HAL_Init();

    MPU_Config();

    SystemInit();

    /* Configure the system clock to 200 MHz */
    SystemClock_Config();

    /* Enable the CRC Module */
    __HAL_RCC_CRC_CLK_ENABLE();


    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
      DWT->LAR = 0xC5ACCE55;
      DWT->CYCCNT = 0;
      DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;


    /***********************************************************/

    /* Compute the prescaler value to have TIM3 counter clock equal to 10 KHz */
    uwPrescalerValue = (uint32_t) ((SystemCoreClock /2) / 100000) - 1;

    /* Set TIMx instance */
    TimHandle.Instance = TIM3;

    /* Initialize TIM3 peripheral as follows:
         + Period = 500 - 1
         + Prescaler = ((SystemCoreClock/2)/10000) - 1
         + ClockDivision = 0
         + Counter direction = Up
    */
    TimHandle.Init.Period = 100 - 1;
    TimHandle.Init.Prescaler = uwPrescalerValue;
    TimHandle.Init.ClockDivision = 0;
    TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
    if(HAL_TIM_Base_Init(&TimHandle) != HAL_OK)
    {
        while(1)
        {
        }
    }

    IwdgInit.Prescaler = IWDG_PRESCALER_256;
    IwdgInit.Reload = 4096;
    IwdgInit.Window = 0;

    IwdgHandle.Init = IwdgInit;
    IwdgHandle.Instance = IWDG;

    /* Initializes the SDRAM device */
    BSP_SDRAM_Init();

    /*Initializes the QSPI-Flash */
    QSPI_status = BSP_QSPI_Init();

    /* Unlock the Flash to enable the flash control register access *************/
    BSP_SD_Init();
    UB_Fatfs_Init();

    //Init ProcessLogic
    Firmware_ProcessLogic_Init();

    /* Init the STemWin GUI Library */
    GUI_Init();
    GUI_Clear();

    /* Activate the use of memory device feature */
    WM_SetCreateFlags(WM_CF_MEMDEV);

    Board_EXPAND4_Board_EXPAND4_Relaiskarte = Create_clickBoard(6, EXPAND_ADDR_DEF, "EXP - LED1", "");
	EXPAND4click_Select(Board_EXPAND4_Board_EXPAND4_Relaiskarte);
	Update_Clickboard(Board_EXPAND4_Board_EXPAND4_Relaiskarte);

    /*if (BSP_SD_IsDetected()) {
        SD_Test();
        SD_Mounted = 1;
    }*/

    //Ladebildschirm anzeigen, Initialisierung GUI
    WM_HWIN LoadingScreen;
    LoadingScreen = CreateLoadingScreen();

    GUI_Initialized = 1;

    /*##-2- Start the TIM Base generation in interrupt mode ####################*/
    /* Start Channel1 */
    //HAL_IWDG_Init(&IwdgHandle);

    if(HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK)
    {
        while(1)
        {
        }
    }

    Gui_Update_Counter = 0;
    MainTask();

    /* Infinite loop */
    for(;;);
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @param  htim: TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &TimHandle) {
        HAL_IWDG_Refresh(&IwdgHandle);
        BSP_Background();
    } /*else {
        TimerVorbei = 1;
        HAL_TIM_Base_Stop(&Tim_usHandle);
    }*/
}

/**
  * @brief TIM MSP Initialization
  *        This function configures the hardware resources used in this application:
  *           - Peripheral's clock enable
  *           - Peripheral's GPIO Configuration
  * @param htim: TIM handle pointer
  * @retval None
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
    /*##-1- Enable peripherals and GPIO Clocks #################################*/
    /* TIMx Peripheral clock enable */
    __HAL_RCC_TIM3_CLK_ENABLE();
    //__HAL_RCC_TIM4_CLK_ENABLE();

    /*##-2- Configure the NVIC for TIMx ########################################*/
    /* Set the TIMx priority */
    HAL_NVIC_SetPriority(TIM3_IRQn, 1, 0);
    //HAL_NVIC_SetPriority(TIM4_IRQn, 0, 2);

    /* Enable the TIMx global Interrupt */
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
    //HAL_NVIC_EnableIRQ(TIM4_IRQn);

}

/**
* @brief  BSP_Background.
* @param  None
* @retval None
*/
void BSP_Background(void)
{
    if (!SD_LOCK) {
        Firmware_ProcessLogic_MainTask();
    }

    /*Gui_Update_Counter++;
    if((GUI_Initialized == 1) & (Gui_Update_Counter == 50))
    {
        BSP_Pointer_Update();

        ReDrawStopped = 0;
        Gui_Update_Counter = 0;
    }*/
}

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follow :
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 200000000
  *            HCLK(Hz)                       = 200000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 4
  *            APB2 Prescaler                 = 2
  *            HSE Frequency(Hz)              = 25000000
  *            PLL_M                          = 25
  *            PLL_N                          = 400
  *            PLL_P                          = 2
  *            PLL_Q                          = 8
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 6
  * @param  None
  * @retval None
  */
static void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;
    HAL_StatusTypeDef ret = HAL_OK;

    /* Enable HSE Oscillator and activate PLL with HSE as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25;
    RCC_OscInitStruct.PLL.PLLN = 400;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 8;

    ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);
    if(ret != HAL_OK)
    {
        while(1)
        {
            ;
        }
    }

    /* Activate the OverDrive to reach the 200 MHz Frequency */
    ret = HAL_PWREx_EnableOverDrive();
    if(ret != HAL_OK)
    {
        while(1)
        {
            ;
        }
    }

    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_6);
    if(ret != HAL_OK)
    {
        while(1)
        {
            ;
        }
    }

RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_SDMMC1
                              |RCC_PERIPHCLK_CLK48;
      PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
      PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLL;
      PeriphClkInitStruct.Sdmmc1ClockSelection = RCC_SDMMC1CLKSOURCE_CLK48;
      if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
      {
        while(1)
        {
            ;
        }
      }


    HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/**
  * @brief  Transmission  complete callback in non blocking mode
  * @param  CanHandle: pointer to a CAN_HandleTypeDef structure that contains
  *         the configuration information for the specified CAN.
  * @retval None
  */
/*void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef *CanHandle)
{
  if ((CanHandle->pRxMsg->StdId == 0x321) && (CanHandle->pRxMsg->IDE == CAN_ID_STD) && (CanHandle->pRxMsg->DLC == 2))
  {
    //LED_Display(CanHandle->pRxMsg->Data[0]);
    ubKeyNumber = CanHandle->pRxMsg->Data[0];
  }

   //Receive
  if (HAL_CAN_Receive_IT(CanHandle, CAN_FIFO0) != HAL_OK)
  {
    // Reception Error
    //Error_Handler();
  }
}*/

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {}
}
#endif

static void MPU_Config(void)
{
    MPU_Region_InitTypeDef MPU_InitStruct;

    /* Disable the MPU */
    HAL_MPU_Disable();

    /* Configure the MPU attributes as WT for SRAM */
    MPU_InitStruct.Enable = MPU_REGION_ENABLE;
    MPU_InitStruct.BaseAddress = 0x20010000;
    MPU_InitStruct.Size = MPU_REGION_SIZE_256KB;
    MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
    MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;
    MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
    MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
    MPU_InitStruct.Number = MPU_REGION_NUMBER0;
    MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
    MPU_InitStruct.SubRegionDisable = 0x00;
    MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;

    HAL_MPU_ConfigRegion(&MPU_InitStruct);

    /* Enable the MPU */
    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
}





/**
  * @brief  CPU L1-Cache enable.
  * @param  None
  * @retval None
  */
static void CPU_CACHE_Enable(void)
{
  /* Enable branch prediction */
  SCB->CCR |= (1 <<18);
  __DSB();

  /* Enable I-Cache */
  SCB_EnableICache();

  /* Enable D-Cache */
  SCB_EnableDCache();
}

void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c) {
    I2C_Tx = 1;
}


void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c) {
    I2C_Rx = 1;
    //__HAL_I2C_CLEAR_FLAG();
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
