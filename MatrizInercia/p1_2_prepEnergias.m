%%referencias:
%%Craig: 6.9 p174


%k_i = (1/2)*m_i*transpose(vc_i)*vc_i + (1/2)*transpose(^iwi)*^ciIi*^iwi
%u_i = -m_i*transpose(0g)*0Pc_i + uref_i

%  k(q, dq) = (1/2)*transpose(dq)*M*dq

%k = sum(k_i)
%u = sum(u_i)

%L = k(q, dq) - u(q)

%tau = diff(diff(L, dq), t) - diff(L, q)

%tau = diff(diff(k, dq), t) - diff(k, q) + diff(u, q)


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%carrega o pacote de simolicos
pkg load symbolic

load("Tn_0");

%sympref display ascii
%sympref display unicode
sympref display flat

%cria os simbolos a serem utilizados
syms t m1 m2 m3 m4 m5 l1 l2 l3 l4 l5 g;	%t: tempo, mi: massa elo i, l1: distancia centro de massa elo i, g: gravidade

syms I1xx I1yy I1zz I1xy I1yz I1xz
syms I2xx I2yy I2zz I2xy I2yz I2xz
syms I3xx I3yy I3zz I3xy I3yz I3xz
syms I4xx I4yy I4zz I4xy I4yz I4xz
syms I5xx I5yy I5zz I5xy I5yz I5xz

%tensores de inercia
I1 = [I1xx, I1xy I1xz; I1xy, I1yy, I1yz; I1xz, I1yz, I1zz];
I2 = [I2xx, I2xy I2xz; I2xy, I2yy, I2yz; I2xz, I2yz, I2zz];
I3 = [I3xx, I3xy I3xz; I3xy, I3yy, I3yz; I3xz, I3yz, I3zz];
I4 = [I4xx, I4xy I4xz; I4xy, I4yy, I4yz; I4xz, I4yz, I4zz];
I5 = [I5xx, I5xy I5xz; I5xy, I5yy, I5yz; I5xz, I5yz, I5zz];

g0 = [0; 0; -g];	%[gx; gy; gz];

% https://octave.sourceforge.io/symbolic/function/assume.html
% https://octave.sourceforge.io/symbolic/function/@sym/assumeAlso.html
assume a2 a5 d1 d4 m1 m2 m3 m4 m5 l1 l2 l3 l4 l5 g real
assumeAlso([a2 a5 d1 d4 m1 m2 m3 m4 m5 g], 'positive')
%assumptions

half = sym(2)^-1;	%melhor não inserir floats em equação simbolicas

printf ("\ndq e ddq...");
%derivadas das posições
dq1 = diff(q1, t);
dq2 = diff(q2, t);
dq3 = diff(q3, t);
dq4 = diff(q4, t);
dq5 = diff(q5, t);
ddq1 = diff(dq1, t);
ddq2 = diff(dq2, t);
ddq3 = diff(dq3, t);
ddq4 = diff(dq4, t);
ddq5 = diff(dq5, t);


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%definição do tensores de inercia de cada elo
%simplificando cada elo colo um cilindro. Obs.: USAR UMA APROXIMAÇÃO MELHOR

%Solid cylinder of radius r, height h and mass m
%I = [1/12 *m *(3*r^2 +h^2), 0, 0;
%     0, 1/12 *m *(3*r^2 +h^2), 0;
%     0,      0,       1/2 *m *r^2]

%I1_cm = [1/12 *m1 *(3*r1^2 +d1^2), 0, 0; 0, 1/12 *m1 *(3*r1^2 +d1^2), 0; 0, 0, 1/2 *m1 *r1^2];
%I1_1 = I1_cm + m1*[Pc1_y^2+Pc1_z^2, -Pc1_x*Pc1_y, -Pc1_x*Pc1_z; -Pc1_x*Pc1_y, Pc1_x^2+Pc1_z^2, -Pc1_y*Pc1_z; -Pc1_x*Pc1_z, -Pc1_y*Pc1_z, Pc1_x^2+Pc1_y^2]


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


printf ("\nPci...");
%centro de massa de cada elo em relação a sua junta
Pc1 = [0, 0, l1]';
Pc2 = [l2, 0, 0]';
Pc3 = [0, l3, 0]';
Pc4 = [0, 0, l4]';
Pc5 = [l5, 0, 0]';
#Pc6 = [l6, 0, 0]';


%centro de massa de cada elo em relação a origem
Pc1_0 = (R1_0 * Pc1) + P1_0;
Pc2_0 = (R2_0 * Pc2) + P2_0;
Pc3_0 = (R3_0 * Pc3) + P3_0;
Pc4_0 = (R4_0 * Pc4) + P4_0;
Pc5_0 = (R5_0 * Pc5) + P5_0;
#Pc6_0 = (R6_0 * Pc6) + P6_0;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


printf ("\nvci...");
vc1 = [diff(Pc1_0(1), t); diff(Pc1_0(2), t); diff(Pc1_0(3), t)];
vc2 = [diff(Pc2_0(1), t); diff(Pc2_0(2), t); diff(Pc2_0(3), t)];
vc3 = [diff(Pc3_0(1), t); diff(Pc3_0(2), t); diff(Pc3_0(3), t)];
vc4 = [diff(Pc4_0(1), t); diff(Pc4_0(2), t); diff(Pc4_0(3), t)];
vc5 = [diff(Pc5_0(1), t); diff(Pc5_0(2), t); diff(Pc5_0(3), t)];


printf ("\nwi_i...");
%%Craig eq (6.31)
%w{i+1}_{i+1} = Ri_{i+1}*wi_i + dth{i+1}*Zhat{i+1}_{i+1}

%Zhat{i+1}_{i+1} = [0; 0; 1];

w0_0 = [0;0;0];
w1_1 = R0_1*w0_0 + [0; 0; dq1];
w2_2 = R1_2*w1_1 + [0; 0; dq2];
w3_3 = R2_3*w2_2 + [0; 0; dq3];
w4_4 = R3_4*w3_3 + [0; 0; dq4];
w5_5 = R4_5*w4_4 + [0; 0; dq5];


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%












