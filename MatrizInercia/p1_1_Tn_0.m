clear
clc

pkg load symbolic;

#Denavit-Hartenberg
####################################
# i | α(i−1) | a(i−1)  | di   | θi #
#---+--------+---------+------+----#
# 1 | 0◦     | 0       | 230  | θ1 #
# 2 | 90◦    | 0       | 0    | θ2 #
# 3 | 0◦     | 220     | 0    | θ3 #
# 4 |-90◦    | 0       | 230  | θ4 #
# 5 | 90◦    | 0       | 0    | θ5 #
# 6 | 0◦     | 120     | 0    | 0◦ #
####################################


alpha0 = 0;
alpha1 = 90;
alpha2 = 0;
alpha3 = -90;
alpha4 = 90;
alpha5 = 0;
a0 = 0;
a1 = 0;
syms a2; #220
a3 = 0;
a4 = 0;
syms a5; #120
syms d1; #230
d2 = 0;
d3 = 0;
syms d4; #230
d5 = 0;
d6 = 0;
syms q1(t);
syms q2(t);
syms q3(t);
syms q4(t);
syms q5(t);
q6 = 0;

salpha0 = sind(alpha0);
calpha0 = cosd(alpha0);
salpha1 = sind(alpha1);
calpha1 = cosd(alpha1);
salpha2 = sind(alpha2);
calpha2 = cosd(alpha2);
salpha3 = sind(alpha3);
calpha3 = cosd(alpha3);
salpha4 = sind(alpha4);
calpha4 = cosd(alpha4);
salpha5 = sind(alpha5);
calpha5 = cosd(alpha5);

s1 = sin(q1);
c1 = cos(q1);
s2 = sin(q2);
c2 = cos(q2);
s3 = sin(q3);
c3 = cos(q3);
s23 = sin(q2+q3);
c23 = cos(q2+q3);
s4 = sin(q4);
c4 = cos(q4);
s5 = sin(q5);
c5 = cos(q5);

s6 = sin(q6);
c6 = cos(q6);

printf ("\nTi_{i-1}...");
#Ti_i-1=[[ci,         -si,          0,        a(i−1)    ],
#		 [si*cα(i−1),  ci*cα(i−1), -sα(i−1), -sα(i−1)*di],
#		 [si*sα(i−1),  ci*sα(i−1),  cα(i−1),  cα(i−1)*di],
#		 [0,           0,           0,        1         ]]

T1_0 = [[c1,         -s1,          0,        a0    	   ],
		[s1*calpha0,  c1*calpha0, -salpha0, -salpha0*d1],
		[s1*salpha0,  c1*salpha0,  calpha0,  calpha0*d1],
		[0,           0,           0,        1         ]]

T2_1 = [[c2,         -s2,          0,        a1    	   ],
		[s2*calpha1,  c2*calpha1, -salpha1, -salpha1*d2],
		[s2*salpha1,  c2*salpha1,  calpha1,  calpha1*d2],
		[0,           0,           0,        1         ]]

T3_2 = [[c3,         -s3,          0,        a2    	   ],
		[s3*calpha2,  c3*calpha2, -salpha2, -salpha2*d3],
		[s3*salpha2,  c3*salpha2,  calpha2,  calpha2*d3],
		[0,           0,           0,        1         ]]

T4_3 = [[c4,         -s4,          0,        a3    	   ],
		[s4*calpha3,  c4*calpha3, -salpha3, -salpha3*d4],
		[s4*salpha3,  c4*salpha3,  calpha3,  calpha3*d4],
		[0,           0,           0,        1         ]]

T5_4 = [[c5,         -s5,          0,        a4    	   ],
		[s5*calpha4,  c5*calpha4, -salpha4, -salpha4*d5],
		[s5*salpha4,  c5*salpha4,  calpha4,  calpha4*d5],
		[0,           0,           0,        1         ]]

T6_5 = [[c6,         -s6,          0,        a5    	   ],
		[s6*calpha5,  c6*calpha5, -salpha5, -salpha5*d6],
		[s6*salpha5,  c6*salpha5,  calpha5,  calpha5*d6],
		[0,           0,           0,        1         ]]


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


printf ("\nTi_0...");
#T1_0 = T1_0
T2_0 = T1_0 * T2_1;
#T3_0 = T2_0 * T3_2
T3_0 = T1_0*simplify(T2_1*T3_2);	%Matrix([[c23*c1, -s23*c1, s1, a2*c1*c2], [s1*c23, -s23*s1, -c1, a2*s1*c2], [s23, c23, 0, a2*s2 + d1], [0, 0, 0, 1]])
T4_0 = T3_0 * T4_3;
T5_0 = T4_0 * T5_4;
T6_0 = T5_0 * T6_5;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


printf ("\nRi_0...");
%rotação de cada junta
R1_0 = T1_0(1:3,1:3);
R2_0 = T2_0(1:3,1:3);
R3_0 = T3_0(1:3,1:3);
R4_0 = T4_0(1:3,1:3);
R5_0 = T5_0(1:3,1:3);
R6_0 = T6_0(1:3,1:3);

printf ("\nPi_0...");
%posição de cada junta
P1_0 = T1_0(1:3, 4);
P2_0 = T2_0(1:3, 4);
P3_0 = T3_0(1:3, 4);
P4_0 = T4_0(1:3, 4);
P5_0 = T5_0(1:3, 4);
P6_0 = T6_0(1:3, 4);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%R1_0 = T1_0(1:3,1:3);
R2_1 = T2_1(1:3,1:3);
R3_2 = T3_2(1:3,1:3);
R4_3 = T4_3(1:3,1:3);
R5_4 = T5_4(1:3,1:3);
R6_5 = T6_5(1:3,1:3);

printf ("\nRi_{i+1}...");
%inversas
R0_1 = transpose(R1_0);
R1_2 = transpose(R2_1);
R2_3 = transpose(R3_2);
R3_4 = transpose(R4_3);
R4_5 = transpose(R5_4);
R5_6 = transpose(R6_5);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

printf ("\nsave...");save("Tn_0");

