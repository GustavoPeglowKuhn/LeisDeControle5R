%carrega o pacote de simolicos
pkg load symbolic
load("Energias")

%Craig eq (6.76)
#%derivadas no tempo das derivadas em dth menos as derivadas em th
%tau1 = diff(diff(L,diff(th1(t)))) - diff(L,th1(t));
%tau2 = diff(diff(L,diff(th2(t)))) - diff(L,th2(t));
%tau3 = diff(diff(L,diff(th3(t)))) - diff(L,th3(t));
%tau4 = diff(diff(L,diff(th4(t)))) - diff(L,th4(t));
%tau5 = diff(diff(L,diff(th5(t)))) - diff(L,th5(t));


%Craig eq (6.77)
%tau1 = diff(diff(K,diff(q1(t)))) - diff(K,q1(t)) + diff(U,q1(t));
%tau2 = diff(diff(K,diff(q2(t)))) - diff(K,q2(t)) + diff(U,q2(t));
%tau3 = diff(diff(K,diff(q3(t)))) - diff(K,q3(t)) + diff(U,q3(t));
%tau4 = diff(diff(K,diff(q4(t)))) - diff(K,q4(t)) + diff(U,q4(t));
%tau5 = diff(diff(K,diff(q5(t)))) - diff(K,q5(t)) + diff(U,q5(t));

printf ("\ntau1..."); tau1 = diff(diff(K,dq1(t))) - diff(K,q1(t)) + diff(U,q1(t));
printf ("\ntau2..."); tau2 = diff(diff(K,dq2(t))) - diff(K,q2(t)) + diff(U,q2(t));
printf ("\ntau3..."); tau3 = diff(diff(K,dq3(t))) - diff(K,q3(t)) + diff(U,q3(t));
printf ("\ntau4..."); tau4 = diff(diff(K,dq4(t))) - diff(K,q4(t)) + diff(U,q4(t));
printf ("\ntau5..."); tau5 = diff(diff(K,dq5(t))) - diff(K,q5(t)) + diff(U,q5(t));

printf ("\ntau1s..."); tau1s = redux(char(tau1));
printf ("\ntau2s..."); tau2s = redux(char(tau2));
printf ("\ntau3s..."); tau3s = redux(char(tau3));
printf ("\ntau4s..."); tau4s = redux(char(tau4));
printf ("\ntau5s..."); tau5s = redux(char(tau5));


printf ("\nsave..."); save("Torques");

