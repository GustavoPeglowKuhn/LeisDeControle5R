printf ("\nki...");
%Craig eq (6.69)
%k_i = (1/2)*m_i*transpose(vc_i)*vc_i + (1/2)*transpose(^iwi)*^ciIi*^iwi
k1 = half*m1*transpose(vc1)*vc1 + half*transpose(w1_1)*I1*w1_1;
k2 = half*m2*transpose(vc2)*vc2 + half*transpose(w2_2)*I2*w2_2;
k3 = half*m3*transpose(vc3)*vc3 + half*transpose(w3_3)*I3*w3_3;
k4 = half*m4*transpose(vc4)*vc4 + half*transpose(w4_4)*I4*w4_4;
k5 = half*m5*transpose(vc5)*vc5 + half*transpose(w5_5)*I5*w5_5;


printf ("\nui...");
%Craig eq (6.73)
%u_i = -m_i*transpose(0g)*0Pc_i + uref_i


uref_1 = 0;	%qualquer valor que faça ui ser sempre >= 0
uref_2 = 0;
uref_3 = 0;
uref_4 = 0;
uref_5 = 0;
u1 = -m1*transpose(g0)*Pc1_0 + uref_1;
u2 = -m2*transpose(g0)*Pc2_0 + uref_2;
u3 = -m3*transpose(g0)*Pc3_0 + uref_3;
u4 = -m4*transpose(g0)*Pc4_0 + uref_4;
u5 = -m5*transpose(g0)*Pc5_0 + uref_5;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
printf ("\nL...");

K = k1+k2+k3+k4+k5;
U = u1+u2+u3+u4+u5;


%L = K-U;


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


printf ("\nsave..."); save("Energias")

