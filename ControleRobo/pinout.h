/*******************************************
 * DECLARAÇÃO DOS PINOS DE ENTRADA E SAÍDA
 *******************************************/

//Pins HIGH at Boot
//Some GPIOs change their state to HIGH or output PWM signals at boot or reset. This means that if you have outputs connected to these GPIOs you may get unexpected results when the ESP32 resets or boots.
//GPIO 1
//GPIO 3
//GPIO 5
//GPIO 6 to GPIO 11 (connected to the ESP32 integrated SPI flash memory – not recommended to use).
//GPIO 14
//GPIO 15

//Input only pins
//GPIO 34
//GPIO 35
//GPIO 36
//GPIO 39

//Good output pins
//2*, 4, 13, 16, 17, 18, 19, 21, 22, 23, 25, 26, 27, 32, 33

//Free output pins
//2*, 4, 13, 

//PINOS CONECTADOS NAS PONTES H ---> PORTAS COM PWM			//esuerda sentido positivo, direita negativo
#define M1_direita  22  // base
#define M1_esquerda 23  // base
#define M2_direita   4  // ombro				//trocar pino  
#define M2_esquerda  2  // ombro
#define M3_direita  19  // cotovelo verde
#define M3_esquerda 21  // cotovelo azul
#define M4_direita  13  // punho verde			//trocar pino
#define M4_esquerda 12  // punho azul
#define M5_direita  16  // garra roxo
#define M5_esquerda 17  // garra cinza


//PINOS DOS ENCODERS (CANAL A e CANAL B) --> PINOS ENTRADA COM INTERRUPCAO EXTERNA


#define ENC1_A 27		//verde
#define ENC1_B 14		//amarelo				//trocar pino
#define ENC2_A 39		//preto
#define ENC2_B 36		//branco
#define ENC3_A 35		//marrom
#define ENC3_B 34		//vermelho
#define ENC4_A 32		//verde
#define ENC4_B 33		//amarelo
#define ENC5_A 25		//verde
#define ENC5_B 26		//amarelo


#define LED_PLACA 15	//Led vermelho da placa