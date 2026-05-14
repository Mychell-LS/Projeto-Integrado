/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdlib.h>
#include "ST7789\st7789.h"
#include <time.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define s1 HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)
#define s2 HAL_GPIO_ReadPin(B2_GPIO_Port, B2_Pin)
#define s3 HAL_GPIO_ReadPin(B3_GPIO_Port, B3_Pin)
#define s4 HAL_GPIO_ReadPin(B4_GPIO_Port, B4_Pin)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

/* USER CODE BEGIN PV */
char senha[3];
int pos = 0;
char s[3];
char alunos[2];
int Qa = 0;
int senhaexibi;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */
void gerador(void);
void exibirsenhad(void);
void exibirqalunos(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */

  ST7789_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  int liberado = 1;
	  int s1_at = s1;
	  int s2_at = s2;
	  int s3_at = s3;
	  int s1_ant = s1_at;
	  int s2_ant = s2_at;
	  int s3_ant = s3_at;
	  int a = 0; // senha digitada
	  int Q = 1;
	  int C = 0;
	  int A = 0;
	  int N = 0;
	  int total = 0;
	  int IP = 0; // inseridos pelo professor no código anterior que eu já tenho.
	  int K = 0;
	  int AF = 0; // alunos que estão fora que irão entrar.
	  int S = 0;
	  int tent = 3;

	  for (int i = 0; i<3; i++){
		  s[i] = '0';
	  }

	  s[3] = '\0';

	  for (int i = 0; i<2; i++){
		  alunos[i] = '0';
	  }

	  alunos[2] = '\0';

	  ST7789_Fill_Color(WHITE);
	  ST7789_WriteString(30, 20,"Iniciar Aula", Font_16x26, BLACK, WHITE);
	  ST7789_WriteString(30, 63,"Confirmar = PA9", Font_11x18, BLACK, WHITE);
	  exibirqalunos();
	  while (1)
	  {
	      if (s1 == 0 && liberado == 0)
	      {
	    	  ST7789_Fill_Color(WHITE);
	    	  ST7789_WriteString(30, 20,"Aula iniciada", Font_16x26, BLACK, WHITE);
	          liberado = 1;
	          pos = 0;
	          a = 0;
	          gerador();
	          ST7789_Fill_Color(WHITE);
	          ST7789_WriteString(20, 20,senha, Font_16x26, BLACK, WHITE);
	          HAL_Delay(3000);
	          exibirsenhad();
	      }

	      if (liberado == 1 && Q == 0)
	      {

	          if (s2 == 0)
	          {
	              a++;
	              if (a > 9) {
	            	  a = 0;
	            	  s[pos] = '0';
	              } else s[pos] ++;
	              exibirsenhad();
	          }

	          if (s3 == 0)
	          {
	              a--;
	              if (a < 0) {
	            	  a = 9;
	            	  s[pos] = '9';
	              } else s[pos] --;
	              exibirsenhad();
	          }

	          if (s4 == 0)
	          {
	              pos++;
	              a = 0;
	              if (pos == 3)
	              {
	                  s[3] = '\0';
	                  pos = 0;
	                  int ok = 1;
	                  for (int i = 0; i < 3; i++)
	                  {
	                      if (s[i] != senha[i]) ok = 0;
	                  }

	                  if (ok)
	                  {
	                	  Q = 1;
	                	  ST7789_Fill_Color(WHITE);
	                	  ST7789_WriteString(30, 63,"Acesso permitido!", Font_11x18, GREEN, WHITE);
	                	  HAL_Delay(1000);
	                	  exibirqalunos();
	                  }
	                  else
	                  {
	                	  ST7789_Fill_Color(WHITE);
	                	  ST7789_WriteString(30, 63,"Senha inválida!", Font_11x18, RED, WHITE);
	                	  HAL_Delay(1000);
	                	  tent--;
	                	  if (tent <= 0) {
	                		  while (1==1){
	                			  ST7789_Fill_Color(GRAY);
	                	  	      ST7789_WriteString(20, 63,"ACESSO BLOQUEADO", Font_16x26, RED, WHITE);
	                	  	      HAL_Delay(4000);
	                		  }
	                		  HAL_Delay(1000);
	                	  }
	                  }
	              } else exibirsenhad();
	          }
	      }

	      if(Q == 1 && C == 0){
	    	  if (s2 == 0){
	        	A++;
	        	alunos[Qa]++;
	        	if (A > 9) {
	        		A = 0;
	        		alunos[Qa] = '0';
	        	}
	        	exibirqalunos();
	    	  }
	    	  if (s3 == 0){
	    		  A--;
	    		  alunos[Qa]++;
	    		  if (A < 0) {
	    			  A = 0;
	    			  alunos[Qa] = '9';
	    		  }
	    		  exibirqalunos();
	    	  }
	    	  if(s4 == 0){
	    		  A = 0;
	    		  Qa++;
	    		  if(Qa == 2){
	    			  Qa = 0;
	    		  }
	    		  exibirqalunos();
	    	  }
	    	  if (s1 == 0){
	    		  C = 1;
	    		  char casdv[20];
	    		  total = atoi(alunos);
	    		  sprintf(casdv, "Aula (Aluno s%d/%d2", total, atoi(alunos));
	    		  ST7789_Fill_Color(WHITE);
	    		  ST7789_WriteString(30, 20,casdv, Font_11x18, BLACK, WHITE);
	    		  //ST7789_WriteString(70, 50,s, Font_11x18, BLACK, WHITE);
	    	  }
	      }

	      if (C == 1) {
	    	  s1_at = s1;
	    	  s2_at = s2;
	    	  s3_at = s3;


	    	  if(s1_ant == 1 && s1_at == 0){
	    		  N = 1;
	    	  }

	    	  if(s2_ant == 1 && s2_at == 0){
	    		  K = 1;
	    	  }

	    	  if(s3_ant == 1 && s3_at == 0){
	    		  S = 1;
	    	  }

	    	  s1_ant = s1_at;
	    	  s2_ant = s2_at;
	    	  s3_ant = s3_at;

	    	  if(N==1)//entrada
	    	  {
	    		  if(total>alunos[2]){
	    			  //???
	    		  } else if(total<alunos[2]){
	    			  total++;
	    		  }
	    		  N = 0;
	    	  }

	    	  if(K==1)  //saída da sala
	    	  {
	    		  if(AF>=3){
	    			  //???
	    		  }

	    		  else if(AF<3 && total>0){
	    			  AF++;
	    			  total--;
	    		  }

	    		  K = 0;
	    	  }

	    	  if(S==1)// retorno para sala
	    	  {
	    		  if(AF>0){
	    			  AF--;
	    			  total++;
	    		  } else{
	    			  //???
	    		  }

	    		  S = 0;
	    	  }


	    	  if(s1==0 && s2==0){

	    		  liberado = 0;
	    		  break;
	    	  }
	      }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(ST7789_CS_GPIO_Port, ST7789_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, ST7789_DC_Pin|ST7789_RST_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : ST7789_CS_Pin */
  GPIO_InitStruct.Pin = ST7789_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(ST7789_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : ST7789_DC_Pin ST7789_RST_Pin */
  GPIO_InitStruct.Pin = ST7789_DC_Pin|ST7789_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : B1_Pin B2_Pin B3_Pin B4_Pin */
  GPIO_InitStruct.Pin = B1_Pin|B2_Pin|B3_Pin|B4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
 void gerador(void){
	 srand(time(NULL));
	 for (int i = 0; i<3 ; i++){
		 int digito = (rand()%9) + 1;
		 senha[i] = '0' + digito;
	 }
	 senha[3] = '0';
	 senhaexibi = senha;

 }

 void exibirsenhad(void){
	 char casdv[20];
	 sprintf(casdv, "Casa %d", pos + 1);
	 ST7789_Fill_Color(WHITE);
	 ST7789_WriteString(30, 20,"Digite a Senha", Font_16x26, BLACK, WHITE);
	 ST7789_WriteString(70, 50,s, Font_11x18, BLACK, WHITE);
	 ST7789_WriteString(30, 70, casdv, Font_11x18, BLACK, WHITE);
 }

 void exibirqalunos(void) {
	 char casdv[20];
	 sprintf(casdv, "Casa %d", Qa + 1);
	 ST7789_Fill_Color(WHITE);
	 ST7789_WriteString(30, 20,"Max alunos:", Font_16x26, BLACK, WHITE);
	 ST7789_WriteString(70, 50,alunos, Font_11x18, BLACK, WHITE);
	 ST7789_WriteString(30, 70, casdv, Font_11x18, BLACK, WHITE);
	 ST7789_WriteString(30, 90, "Salvar = PA9", Font_11x18, BLACK, WHITE);
 }
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
