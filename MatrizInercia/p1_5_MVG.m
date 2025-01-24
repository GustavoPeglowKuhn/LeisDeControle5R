%carrega o pacote de simolicos
pkg load symbolic
load("Torques")

printf ("\ntau1...");
[ctau1, ttau1] = coeffs(tau1, [ddq1, ddq2, ddq3, ddq4, ddq5, g]);
M11 = ctau1(1);
M12 = ctau1(2);
M13 = ctau1(3);
M14 = ctau1(4);
M15 = ctau1(5);
G1  = 0;
V1  = ctau1(6);

printf ("\ntau2...");
[ctau2, ttau2] = coeffs(tau2, [ddq1, ddq2, ddq3, ddq4, ddq5, g]);
M21 = ctau2(1);
M22 = ctau2(2);
M23 = ctau2(3);
M24 = ctau2(4);
M25 = ctau2(5);
G2  = ctau2(6);
V2  = ctau2(7);

printf ("\ntau3...");
[ctau3, ttau3] = coeffs(tau3, [ddq1, ddq2, ddq3, ddq4, ddq5, g]);
M31 = ctau3(1);
M32 = ctau3(2);
M33 = ctau3(3);
M34 = ctau3(4);
M35 = ctau3(5);
G3  = ctau3(6);
V3  = ctau3(7);

printf ("\ntau4...");
[ctau4, ttau4] = coeffs(tau4, [ddq1, ddq2, ddq3, ddq4, ddq5, g]);
M41 = ctau4(1);
M42 = ctau4(2);
M43 = ctau4(3);
M44 = ctau4(4);
M45 = ctau4(5);
G4  = ctau4(6);
V4  = ctau4(7);

printf ("\ntau5...");
[ctau5, ttau5] = coeffs(tau5, [ddq1, ddq2, ddq3, ddq4, ddq5, g]);
M51 = ctau5(1);
M52 = ctau5(2);
M53 = ctau5(3);
M54 = ctau5(4);
M55 = ctau5(5);
G5  = ctau5(6);
V5  = ctau5(7);


printf ("\nMijs...");
M11s = redux(char(M11));
M12s = redux(char(M12));
M13s = redux(char(M13));
M14s = redux(char(M14));
M15s = redux(char(M15));

M21s = redux(char(M21));
M22s = redux(char(M22));
M23s = redux(char(M23));
M24s = redux(char(M24));
M25s = redux(char(M25));

M31s = redux(char(M31));
M32s = redux(char(M32));
M33s = redux(char(M33));
M34s = redux(char(M34));
M35s = redux(char(M35));

M41s = redux(char(M41));
M42s = redux(char(M42));
M43s = redux(char(M43));
M44s = redux(char(M44));
M45s = redux(char(M45));

M51s = redux(char(M51));
M52s = redux(char(M52));
M53s = redux(char(M53));
M54s = redux(char(M54));
M55s = redux(char(M55));

printf ("\nVis...");
V1s  = redux(char(V1));
V2s  = redux(char(V2));
V3s  = redux(char(V3));
V4s  = redux(char(V4));
V5s  = redux(char(V5));

printf ("\nGis...");
G1s  = redux(char(G1));
G2s  = redux(char(G2));
G3s  = redux(char(G3));
G4s  = redux(char(G4));
G5s  = redux(char(G5));

%[cv1, tv1] = coeffs(V1, [dq1, dq2, dq3, dq4, dq5]);
%[cv2, tv2] = coeffs(V2, [dq1, dq2, dq3, dq4, dq5]);
%[cv3, tv3] = coeffs(V3, [dq1, dq2, dq3, dq4, dq5]);
%[cv4, tv4] = coeffs(V4, [dq1, dq2, dq3, dq4, dq5]);
%[cv5, tv5] = coeffs(V5, [dq1, dq2, dq3, dq4, dq5]);
%
%V1dq1 = redux(char(cv1(1)));
%V1dq2 = redux(char(cv1(2)));
%V1dq3 = redux(char(cv1(3)));
%V1dq4 = redux(char(cv1(4)));
%V1dq5 = redux(char(cv1(5)));
%
%V2dq1 = redux(char(cv2(1)));
%V2dq2 = redux(char(cv2(2)));
%V2dq3 = redux(char(cv2(3)));
%V2dq4 = redux(char(cv2(4)));
%V2dq5 = redux(char(cv2(5)));
%
%V3dq1 = redux(char(cv3(1)));
%V3dq2 = redux(char(cv3(2)));
%V3dq3 = redux(char(cv3(3)));
%V3dq4 = redux(char(cv3(4)));
%V3dq5 = redux(char(cv3(5)));
%
%V4dq1 = redux(char(cv4(1)));
%V4dq2 = redux(char(cv4(2)));
%V4dq3 = redux(char(cv4(3)));
%V4dq4 = redux(char(cv4(4)));
%V4dq5 = redux(char(cv4(5)));
%
%V5dq1 = redux(char(cv5(1)));
%V5dq2 = redux(char(cv5(2)));
%V5dq3 = redux(char(cv5(3)));
%V5dq4 = redux(char(cv5(4)));
%V5dq5 = redux(char(cv5(5)));

printf ("\nsave..."); save("MVG")
