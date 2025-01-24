#include "pinout.h"

//2000000 é a velocidade no ArduinoSerialMonito
//921600 é a velocidade de gravação da esp
//115200
#define BAUDRATE 921600

//se PLOT_CSV defino print dos valores fica no formato CSV (separados por virgula). Usar comando 'log vars' para ver a ordem dos dados printados
//caso contrario printa os dados no formato 'nome1: valor1 nome2: valor2 ...'. Esse formato é bom para plotar os dados no QtSerialMonitor
#define PLOT_CSV	

//captura os maximos de algumas grandezas
#define LOG_MAX

//se definido printa os valores das constantes e o tempo para a trajetoria. Print sempre que cria nova trajetória
//#define PRINT_TRAJ

// #define VERBOSE_CMDS			//printa o cmd recebido (para verificar se está chegando o cmd correto)
// #define VERBOSE_SPLIT_CMDS	//printa info de separação dos cmds

// #define USE_R2_J2_J3	//Usa as juntas 2 e 3 como R2 e deixa as demais travadas
#define USE_R2_J3_J5	//Usa as juntas 3 e 5 como R2 e deixa as demais travadas
//#define USE_R5
 
// #if defined(USE_R2_J2_J3)
// #elif defined(USE_R2_J3_J5)
// #else
// #endif
 
#define MEASURE_TIME_CONTROLE		//inclui medições do tempo de execução do controle

#define PWM_FREQUENCY	30000
#define PWM_RESOLUTION	10
#define PWM_MAX			1023.0


#include <iostream> //std::cout
#include <ArduinoEigenDense.h>  //instalar Eigen no Library Manager

using std::numbers::pi;
using Eigen::Matrix;
using Eigen::Vector;
using Eigen::Array;
#define DIM 5

//Constantes já definidas
//#define RAD_TO_DEG 180/pi
//#define DEG_TO_RAD pi/180

//#define T_AMOSTRAGEM 0.01 	// 10 ms
#define T_AMOSTRAGEM 0.001 		// 1 ms

#define TORQUE_N  0.09*9.8	//0.8820			//0.0445		//torque nominal

////////////////////////////Valores de conversão dos encoder em graus e radianos
//Valores Originais
//Encoders[0] * (pi/180) * 0.065454 * 0.106;
//Encoders[1] * (pi/180) * 0.065454 * 0.14;
//Encoders[2] * (pi/180) * 0.065454 * 0.17;
//Encoders[3] * (pi/180) * 0.065454;
//Encoders[4] * (pi/180) * 0.065454 * 0.24;
//0.065454 = 360/(500*11), 360° em uma volta, 500x de redução e 11 pulsos por volta do motor
//numeros de dentes:
//p1:13		c1:100
//p2:13		c1:77
//p3:13		c1:61		original p3:10
//p4:1		c1:1
//p5:13		c5:45		original p5:10

//raios: 
//polias 10T: 7.525 mm
//polias 13T: 10.5 mm (dentes não encaixados +1.25 mm)
//j1: 79.00 mm
//j2: 60.00 mm
//j3: 47.50 mm
//j5: 35.00 mm

#define	RADS_PER_PULSE_J1 1.485116527151538621818704144823e-4		// (2*pi/(500*11))*13/100
#define RADS_PER_PULSE_J2 1.9287227625344657426216936945754e-4		// (2*pi/(500*11))*13/77
#define RADS_PER_PULSE_J3 2.8259302338511058795740524213232e-4		// (2*pi/(500*11))*(10.5+1.25)/47.5
#define RADS_PER_PULSE_J4 0.00114239732857810663216823395756		//  2*pi/(500*11)
#define RADS_PER_PULSE_J5 3.3002589492256413818193425440512e-4		// (2*pi/(500*11))*13/45

#define	DEGS_PER_PULSE_J1 0.00850909090909090909090909090909		// (360/(500*11))*13/100
#define DEGS_PER_PULSE_J2 0.01105076741440377804014167650531		// (360/(500*11))*13/77
#define DEGS_PER_PULSE_J3 0.01619138755980861244019138755981		// (360/(500*11))*(10.5+1.25)/47.5
#define DEGS_PER_PULSE_J4 0.06545454545454545454545454545455		//  360/(500*11)
#define DEGS_PER_PULSE_J5 0.01890909090909090909090909090909		// (360/(500*11))*13/45

#define	PULSES_PER_RAD_J1 6733.4783615801872825296976811448		// (500*11/(2*pi))*100/13
#define PULSES_PER_RAD_J2 5184.7783384167442075478672144815		// (500*11/(2*pi))* 77/13
#define PULSES_PER_RAD_J3 3538.6577772559707633719900579634		// (500*11/(2*pi))* 47.5/(10.5+1.25)
#define PULSES_PER_RAD_J4 875.35218700542434672886069854883		// (500*11/(2*pi))
#define PULSES_PER_RAD_J5 3030.0652627110842771383639565152		// (500*11/(2*pi))* 45/13

#define	PULSES_PER_DEG_J1 117.52136752136752136752136752137		// (500*11/(360))*100/13
#define PULSES_PER_DEG_J2 90.491452991452991452991452991453		// (500*11/(360))* 77/13
#define PULSES_PER_DEG_J3 61.761229314420803782505910165485		// (500*11/(360))* 47.5/(10.5+1.25)
#define PULSES_PER_DEG_J4 15.277777777777777777777777777778		// (500*11/(360))
#define PULSES_PER_DEG_J5 52.884615384615384615384615384615		// (500*11/(360))* 45/13
////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////Torques Maximos de cada junta
//#define INV_TORQUE_N 	1.0/TORQUE_N
//#define INV_2TORQUE_N 	0.5/TORQUE_N

//TORQUE_N = 0.09*9.8; %0.0445
//float TauMax[5] = {TORQUE_N/0.106, 2*TORQUE_N/0.14, TORQUE_N/(0.17*1.3), TORQUE_N, TORQUE_N/(0.24*1.3)};
//float InvTauMax[5] = {0.106/TORQUE_N, 0.14/(2*TORQUE_N), 0.17*1.3/TORQUE_N, 1/TORQUE_N, 0.24*1.3/TORQUE_N};

//float TauMax	 [5] = {8.3208,   12.6000,    5.1882,    0.8820,    3.6750};
//float InvTauMax[5] = {0.120181, 0.079365,   0.192744,  1.133787,  0.272109};
// float TauMax	[5] = {8.3208,   12.6000,    3.9910,    0.8820,  2.8269};
// float InvTauMax	[5] = {0.120181, 0.079365,   0.2506,  1.133787,  0.3537};

//0.882*100/13, 	2*0.882*77/13, 		0.882*47.5/(10.5+1.25), 	0.882*1, 	0.882*45/13
//13/(0.882*100), 	13/(2*0.882*77), 	(10.5+1.25)/(0.882.5), 		1/(0.882), 	13/(0.882*45)
float TauMax[5]    = {6.7846153846153846153846153846154 , 10.448307692307692307692307692308 , 3.5655319148936170212765957446809 , 0.882							  , 3.0530769230769230769230769230769};
float InvTauMax[5] = {0.14739229024943310657596371882086, 0.09570927938274877050387254468887, 0.28046306241794963599474877670366, 1.1337868480725623582766439909297, 0.3275384227765180146132527084908};

//Para braço reto para o lado (maximo torque gravitacional na junta2)
//tau2Grav calculado: 2.3137N.m
////////////////////////////////////////////////////////////////////////////////

/********************************************************************
 * DEFINIÇÃO DE VARIÁVEIS GLOBAIS
 ********************************************************************/
//variáveis para salvar os incrementos dos encoders dos motores
int32_t Encoders[5]{ 0, 0, 0, 0, 0 };

//controle de tragetoria (vel inicial e final iguais a 0)
typedef struct{
	float thf[5]{ 0, 0, 0, 0, 0 };
	//a1 = a2 = a3 = 0, a0 = th0
	float a0[5]{ 0, 0, 0, 0, 0 }; 
	//float a1[5]{ 0, 0, 0, 0, 0 };
	//float a2[5]{ 0, 0, 0, 0, 0 };
	//float a3[5]{ 0, 0, 0, 0, 0 };
	float a4[5]{ 0, 0, 0, 0, 0 };
	float a5[5]{ 0, 0, 0, 0, 0 };
	float a6[5]{ 0, 0, 0, 0, 0 };
	float a7[5]{ 0, 0, 0, 0, 0 };
	double t = 0;
	double tf = 0;
}ControleTragetoria;
ControleTragetoria Ct;

//Tipo de controle selecionado
enum CtrlType_t{
	Nenhum,
	TorqueCalculado,				//p185
	ControleDeJuntaClassico,		//p208
	PIDplusG,						//p205
	PID,							//PID multi uso
	//Adaptativo,
	Robusto,						//p263, p294
	OnOff
};
enum CtrlType_t CtrlType = CtrlType_t::Nenhum;	//CtrlType_t::ControleDeJuntaClassico;

float CtrlOnOffTol = 5*pi/180;	//tolerancia para controle OnOff
enum CtrlCompG_t{
	SemG,
	CompG,
	CompGCond,
	CompFadap,
	CompFadap2,
	CompFd,
	CompFdFadap
}CtrlCompG = CtrlCompG_t::SemG;		//compensação para controle PID

struct CtrlData_t{
	float K = 1;
	float Kp[5]{100, 100, 25, 10, 25};		// Ganho proporcional
	float Ki[5]{0, 0, 0, 0, 0};//{22.91831	, 25.21014	, 25.78310	, 25.78310	, 25	};		// Ganho integral
	float Kd[5]{2, 2, 1, 1, 1};		// Ganho derivativo
};
struct CtrlData_t CtrlData[7];		//Constantes Kp, Kd e Ki para os controladores (K é um multiplicador para as 3 constantes)
//cada tipo de controle tem seu conjunto de constantes (K,) Kp, Kd e Ki

inline void initCtrlData(){	//inicializa valores de Kp, Kd e Ki
	CtrlData[CtrlType_t::TorqueCalculado].Kp[0] =  30000;
	CtrlData[CtrlType_t::TorqueCalculado].Kp[1] =   8000;
	CtrlData[CtrlType_t::TorqueCalculado].Kp[2] =  20000;
	CtrlData[CtrlType_t::TorqueCalculado].Kp[3] =  55000;
	CtrlData[CtrlType_t::TorqueCalculado].Kp[4] = 625000;
	
	#ifdef USE_R2_J3_J5
		CtrlData[CtrlType_t::TorqueCalculado].Kp[2] =   50000;
		CtrlData[CtrlType_t::TorqueCalculado].Kp[4] = 1000000;
		
		CtrlData[CtrlType_t::TorqueCalculado].Ki[2] =     100;
		CtrlData[CtrlType_t::TorqueCalculado].Ki[4] =     100;
		
		CtrlData[CtrlType_t::TorqueCalculado].Kd[2] =     200;
		CtrlData[CtrlType_t::TorqueCalculado].Kd[4] =     200;
	#endif
}

float epslonMax[5] = {	0.5*6.7846153846153846153846153846154/22.91831,
						0.5*10.448307692307692307692307692308/25.21014,
						0.5*3.5655319148936170212765957446809/25.78310,
						0.5*0.882							 /25.78310,
						0.5*3.0530769230769230769230769230769/25};	//TauMax/4
float epslonMaxTorque[5] = {
						0.5*6.7846153846153846153846153846154/22.91831,
						0.5*10.448307692307692307692307692308/25.21014,
						0.5*3.5655319148936170212765957446809/25.78310,
						0.5*0.882							 /25.78310,
						0.5*3.0530769230769230769230769230769/25.00000};	//TauMax/4
/*
//GANHOS PARA O CONTROLADOR
//Original
//float Kp[5]{5.8		, 7.5	, 7.5	, 7.5	, 7.5	};		// Ganho proporcional
//float Ki[5]{0.4		, 0.44	, 0.45	, 0.45	, 0.45	};		// Ganho integral
//float Kd[5]{0.035	, 0.035	, 0.035	, 0.035	, 0.035	}; 		// Ganho derivativo

//float Kp[5]{332.31552	, 429.71835	, 200.0		, 10.0		, 429.71835	};		// Ganho proporcional
//float Ki[5]{22.91831	, 25.21014	, 25.78310	, 25.78310	, 25.78310	};		// Ganho integral
//float Kd[5]{2.00535 	, 2.00535	, 1.0		, 0.1		, 2.00535	};		// Ganho derivativo

//ctrl PID - junta5 Kp=12.50000 Ki=1.00000 Kd=0.50000
//ctrl Torque - junta4 Kp=100 Ki=25.78310 Kd=0.1
//ctrl Torque - junta5 Kp=429.71835 Ki=25.78310 Kd=2.00535
*/

bool UseV = true;
bool UseG = true;
bool UseFd = false;
bool UseFs = false;

float g = 9.8;

#if defined(USE_R2_J2_J3)
	float m1 = 0.60150, m2 = 0.30759+0.19595+0.091150;
	float d1 = 213.12379e-3, 	d2 = 222.50e-3 + .120;
	float 	l1 = 73.18051e-3, 
			l2 = 81.44900e-3;	//(l3*m3 + l4*m4 + l5*m5)/(m3+m4+m5), onde l4 = 222.50-40.346		
	float 	I1zz = 9.1071e-3,		//mL^2/3
			I2zz = 2.3254e-2;		//mL^2/3
#elif defined(USE_R2_J3_J5)
	float m1 = .31159 +.27095, m2 = 0.091150;
	float d1 = 222.50e-3, 	d2 = 0.120;
	//float l1 =  75.00e-3;		//centro de massa pelo Fussion
	float l1 = 106.86000e-3;		//(l3*m3 + l4*m4)/(m3+m4), onde l4 = 222.50-40.346
	float l2 =  24.45907e-3;
	// float l1 = d1, 	l2 = d2;	//Centro de massa na ponta de cada elo

	//(1/12)*m*(3*r^2 +h^2);
	// float I1zz = 1.1356e-03;		//(1/12)*m1*(3*r1^2 +h1^2);	//r1 = 39e-3, h1 = 2*l1 = 2*75.00e-3
	// float I1zz = 2.4389e-03;		//(1/12)*m1*(3*r1^2 +h1^2);	//r1 = 39e-3, h1 = 2*l1 = 2*106.86000e-3
	// float I2zz = 2.4010e-05;		//(1/12)*m2*(3*r2^2 +h2^2);	//r2 = 16e-3, h2 = 2*l2 = 2* 24.45907e-3
	
	float I1zz = 0.009613123625; //mL^2/3, ((.31159+.27095)*(222.50e-3^2))/3
	float I2zz = 0.00043752;     //mL^2/3, ((0.091150)*(0.12^2))/3
	
	// float I1zz = 0, I2zz = 0;
#else
	// float m1 = 1.4376, m2 = 0.60150, m3 = 0.30759, m4 = 0.19595, m5 = 0.091150;
	// float d1 = 231.57*1e-3, a2 = 213.12379*1e-3, d4 = 222.50*1e-3, a5 = 0.120;
	// float l1 = -80.65468*1e-3, l2 = 73.18051*1e-3, l3 = 34.18249*1e-3, l4 = -46.25619*1e-3, l5 = 24.45907*1e-3;

	// float I1xx = 5.4174e-03, I1yy = 5.4174e-03;
	// float I1zz = 4.6003e-03;
	// // float I1xy = 0, I1yz = 0, I1xz = 0;
	// float I2zz = 1.4497e-03, I2yy = 1.4497e-03;
	// float I2xx = 7.5187e-04;
	// // float I2xy = 0, I2yz = 0, I2xz = 0;
	// float I3zz = 2.3676e-04, I3xx = 2.3676e-04;
	// float I3yy = 2.3392e-04;
	// // float I3xy = 0, I3yz = 0, I3xz = 0;
	// float I4xx = 2.1426e-04, I4yy = 2.1426e-04;
	// float I4zz = 1.4902e-04;
	// // float I4xy = 0, I4yz = 0, I4xz = 0;
	// float I5zz = 2.4010e-05, I5yy = 2.4010e-05;
	// float I5xx = 1.1667e-05;
	// // float I5xy = 0, I5yz = 0, I5xz = 0;

	// float m1 = 1.4376, m2 = 0.60150, m3 = 0.30759, m4 = 0.19595, m5 = 0.091150;
	// float d1 = 231.57*1e-3, a2 = 213.12379*1e-3, d4 = 222.50*1e-3, a5 = 0.120;
	// float l1 = -80.65468*1e-3, l2 = 73.18051*1e-3, l3 = 34.18249*1e-3, l4 = -46.25619*1e-3, l5 = 24.45907*1e-3;
	
	float m1 = 1.5511, m2 = .78406, m3 = .31159, m4 = .27095, m5 = 0.091150;
	float d1 = 231.57e-3, a2 = 213.12379e-3, d4 = 222.50e-3, a5 = 120e-3;
	float l1 = -80.65468e-3, l2 = 97.705e-3, l3 = 41.389e-3, l4 = -40.346e-3, l5 = 24.45907e-3;

	float I1xx = 0, I1yy = 0;
	float I1zz = 0;
	// float I1xy = 0, I1yz = 0, I1xz = 0;
	float I2zz = 0, I2yy = 0;
	float I2xx = 0;
	// float I2xy = 0, I2yz = 0, I2xz = 0;
	float I3zz = 0, I3xx = 0;
	float I3yy = 0;
	// float I3xy = 0, I3yz = 0, I3xz = 0;
	float I4xx = 0, I4yy = 0;
	float I4zz = 0;
	// float I4xy = 0, I4yz = 0, I4xz = 0;
	float I5zz = 0, I5yy = 0;
	float I5xx = 0;
	// float I5xy = 0, I5yz = 0, I5xz = 0;
#endif

float fd[5] = {.5, 40.855, 9.3621, .5, 7.1152};
float fs[5] = {.05, .05, .05, .05, .05};

Vector<float, DIM> qpAnt 	= Vector<float, DIM>::Zero();
Vector<float, DIM> qAnt 	= Vector<float, DIM>::Zero();
Vector<float, DIM> q		= Vector<float, DIM>::Zero();
Vector<float, DIM> qBruto	= Vector<float, DIM>::Zero();
Vector<float, DIM> qp		= Vector<float, DIM>::Zero();
Vector<float, DIM> qpp		= Vector<float, DIM>::Zero();
Vector<float, DIM> qd		= Vector<float, DIM>::Zero();
Vector<float, DIM> qdp		= Vector<float, DIM>::Zero();
Vector<float, DIM> qdpp		= Vector<float, DIM>::Zero();
Vector<float, DIM> u		= Vector<float, DIM>::Zero();
Vector<float, DIM> tau		= Vector<float, DIM>::Zero();
Vector<float, DIM> e		= Vector<float, DIM>::Zero();
Vector<float, DIM> ep		= Vector<float, DIM>::Zero();
Vector<float, DIM> epslon	= Vector<float, DIM>::Zero();
Matrix<float, DIM, DIM> M 	= Matrix<float, DIM, DIM>::Identity();
Vector<float, DIM>  V 		= Vector<float, DIM>::Zero();
Vector<float, DIM>  G 		= Vector<float, DIM>::Zero();
Vector<float, DIM>  Fd 		= Vector<float, DIM>::Zero();
Vector<float, DIM>  Fs 		= Vector<float, DIM>::Zero();
Vector<float, DIM>  Fadap	= Vector<float, DIM>::Zero();
Matrix<float, 3,3> rot		= Matrix<float, 3,3>();
Vector<float, 3> 	pos		= Vector<float, 3>();

float gama = 1000;
float beta = 0.99;	//fator de esquecimento

#ifdef LOG_MAX
Vector<float, DIM>
	eLogMax 	= Vector<float, DIM>::Zero(),	eLogMin 	= Vector<float, DIM>::Zero(),
	qpLogMax 	= Vector<float, DIM>::Zero(),	qpLogMin 	= Vector<float, DIM>::Zero(),
	pwmLogMax 	= Vector<float, DIM>::Zero(),	pwmLogMin 	= Vector<float, DIM>::Zero(),
	FaLogMax 	= Vector<float, DIM>::Zero(),	FaLogMin 	= Vector<float, DIM>::Zero();
#endif

#define NPOS	2	//4
Vector<float, DIM> p[NPOS];	//= {Vector<float, DIM>::Zero(), Vector<float, DIM>::Zero(), Vector<float, DIM>::Zero()};	//lista de posições (angulos de juntas)
inline void initPosList(){
	for(uint8_t i=0; i<NPOS; ++i)
		p[i] << 0, 90*pi/180.0, -90*pi/180.0, 0, 90*pi/180.0;
	
	// p[0](1) =  75*pi/180.0;
	// p[2](1) = 105*pi/180.0;
	p[0](2) = -135*pi/180.0;
	p[0](4) =   45*pi/180.0;
	// p[2](2) =  -45*pi/180.0;
	// p[2](4) =  135*pi/180.0;
	// p[0](4) =   45*pi/180.0;
	// p[2](4) =  135*pi/180.0;
}

bool EnMovment = false;
bool SingleMovment = false;
bool SingleMovmentB = false;
int PosIndex = 0;
float MoveTimeOut = 1, CurrentMoveTimeOut = 0;



//+ou- 90° em relação a posição reta para cima
float qMax[5][2] = {
	{-0.25*pi,0.25*pi},  // angulos limite para o motor 1
	{     0.0,     pi},  // angulos limite para o motor 2
//	{     0.0, 0.5*pi},  // angulos limite para o motor 2	//giro somente para o lado da placa de controle
	{     -pi,    0.0},  // angulos limite para o motor 3
	{	  -pi,     pi},  // angulos limite para o motor 4
	{     0.0,     pi}   // angulos limite para o motor 5
};
//dqMax (sem carga) - 12 rpm = 72 º/s
// 9.36  , 12.1558, 17.8105, 72     , 20.8
//dqMax (com torque nominal) - 9 rpm = 54 º/s
// 7.02  ,  9.1169, 13.3579, 54     , 15.6
//float qpMax[5] {	//vel max do motor (após redução, com torque nominal): 9 rpm = 54 º/s = 0.15 pi rad/s
//	 7.5*pi/180.0, 		
//	10.0*pi/180.0, 
//	10.0*pi/180.0, 
//	20.0*pi/180.0, 		//até 25°/s erro muito baixo. Mov45°: {v45°/s e3°}, {v70°/s e5°}, {v90°/s e7.5°}
//	10.0*pi/180.0
//};	//°/s
float qpMax[5] {	//vel max do motor (após redução, com torque nominal): 9 rpm = 54 º/s = 0.15 pi rad/s
	 7.02*pi/180.0, 		
	 9.12*pi/180.0, 
	13.36*pi/180.0, 
	54.00*pi/180.0, 		//até 25°/s erro muito baixo. Mov45°: {v45°/s e3°}, {v70°/s e5°}, {v90°/s e7.5°}
	15.60*pi/180.0
};	//rad/s
//float qppMax[5]{};	//°/s^2

bool mEnable[5]{true,true,true,true,true};//{false,false,false,false,false};

uint16_t pwm[5]{ 0, 0, 0, 0, 0 };
bool sentido[5]{true,true,true,true,true};

bool EnDeadZone = true;
//int16_t DeadZone[5]{20, 18, 14, 16, 15};
//int16_t DeadZone[5]{15, 13, 10, 11, 10};
//int16_t   DeadZone[5]{10,  8,  4,  6,  5};
//int16_t DeadZone[5]{20, 18, 13, 19, 15};
//reto (1s):
// dz_pos = 17 15 19 22 19 
// dz_pos = 18 13 16 15 14 
// dz_neg = 14 23 17 17 30 
// dz_pos = 22 15 11 18 10 
// dz_neg = 23  0 25 13 28 
// dz_pos = 22 15 10 18 9 
// dz_neg = 22 21 23 13 27 
//reto (2s):
// dz_pos = 17 13 12 21 11 
// int16_t DeadZone[5]{14, 13, 15, 15, 14};
//int16_t DeadZone[5]{14, 13, 13, 15, 6};
int16_t DeadZone[5]{56, 52, 52, 60, 24};	//valores de 8bit de resolução multiplicados por 4 para 10 bits de resolução
											//testar e modificar se necessário

//m1=582.54 	m2=91.15 g
//l1=106.86 	l2=24.46 mm
//d1=222.50 	d2=120.00 mm
//I1zz=2.43890 	I2zz=0.02401 g*m^2
//q3:  -90 >> pwm: [20, 21, -20, -22] G1: 0.00 G2: 0.00
//q3: -105 >> pwm: [23, -25]	G1: 0.19 G2: 0.01
//q3: -120 >> pwm: [27, -17]	G1: 0.36 G2: 0.01
//q3: -135 >> pwm: [30, -17]	G1: 0.52 G2: 0.02
//q3: -150 >> pwm: [31, -18]	G1: 0.63 G2: 0.02
//q3: -165 >> pwm: [33, -19]	G1: 0.70 G2: 0.02
//q3: -180 >> pwm: [38, -20]	G1: 0.73 G2: 0.02

//G = [.19, .36, .52, .63, .70, .73]
//3.5655319148936170212765957446809 * ([23, 27, 30, 31, 33, 38]-20)/235

/**************************************************************
	*LÓGICA PARA CONVERTER OS PASSOS INCREMENTAIS DOS ENCODERS EM
	*VALORES CORRESPONDENTES AOS ANGULOS DAS JUNTAS
*****************************************************************/
inline void ConvertEncodersToRad(Vector<float, DIM> &q){
	q(0) = Encoders[0] * RADS_PER_PULSE_J1;
	q(1) = Encoders[1] * RADS_PER_PULSE_J2;
	q(2) = Encoders[2] * RADS_PER_PULSE_J3;
	q(3) = Encoders[3] * RADS_PER_PULSE_J4;
	q(4) = Encoders[4] * RADS_PER_PULSE_J5;
}
inline void ConvertEncodersToRad(float q[]){
	q[0] = Encoders[0] * RADS_PER_PULSE_J1;
	q[1] = Encoders[1] * RADS_PER_PULSE_J2;
	q[2] = Encoders[2] * RADS_PER_PULSE_J3;
	q[3] = Encoders[3] * RADS_PER_PULSE_J4;
	q[4] = Encoders[4] * RADS_PER_PULSE_J5;
}
inline void ConvertRadtoEncoders(float q1, float q2, float q3, float q4, float q5){
	Encoders[0] = q1 * PULSES_PER_RAD_J1;
	Encoders[1] = q2 * PULSES_PER_RAD_J2;
	Encoders[2] = q3 * PULSES_PER_RAD_J3;
	Encoders[3] = q4 * PULSES_PER_RAD_J4;
	Encoders[4] = q5 * PULSES_PER_RAD_J5;
}
inline void ConvertDegtoEncoders(float q1, float q2, float q3, float q4, float q5){
	Encoders[0] = q1 * PULSES_PER_DEG_J1;
	Encoders[1] = q2 * PULSES_PER_DEG_J2;
	Encoders[2] = q3 * PULSES_PER_DEG_J3;
	Encoders[3] = q4 * PULSES_PER_DEG_J4;
	Encoders[4] = q5 * PULSES_PER_DEG_J5;
}

inline void CalcTrajetoria();

hw_timer_t *timer = NULL;  // cria um ponteiro para o timer do tipo hw_timer_t
typedef struct{
	long countAmost = 0;long maxAmost = 20;		//  1 ms
	long countPrint = 0;long maxPrint = 500;	// 25 ms
}TmrData;
TmrData tmrData;
void IRAM_ATTR cb_timer();

void IRAM_ATTR read_encoder1();
void IRAM_ATTR read_encoder2();
void IRAM_ATTR read_encoder3();
void IRAM_ATTR read_encoder4();
void IRAM_ATTR read_encoder5();
//Sobre IRAM_ATTR
//	https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/memory-types.html
//	https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/spi_flash/spi_flash_concurrency.html#iram-safe-interrupt-handlers
//	https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-guides/memory-types.html#how-to-place-code-in-iram

//inicializado com 256 chars
String SerialBuffer = "                                                                                                                                                                                                                                                                ";
bool SerialLog = false;
bool JlogEn[5]{true,true,true,true,true};//{false,false,false,false,false};

String TaskControllLogBuffer = "";

float pf = 10;

uint32_t tLastPrint = 0;

inline void CalcMVG();
inline void CalcPassoTrajetoria();

TaskHandle_t TaskControle;
TaskHandle_t TaskPrint;
TaskHandle_t TaskCom;

SemaphoreHandle_t SemaphoreControllVars = NULL;  // Create a semaphore object
SemaphoreHandle_t SemaphoreControll = NULL;
SemaphoreHandle_t SemaphorePrint = NULL;
SemaphoreHandle_t SemaphoreLogBuffer = NULL;

#ifdef MEASURE_TIME_CONTROLE
uint64_t t0, t1;
uint64_t sum_dt;
uint32_t countControle = 0;
#endif
