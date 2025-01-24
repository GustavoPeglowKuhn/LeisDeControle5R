%carrega o pacote de simolicos
pkg load symbolic
printf ("\nload..."); load("MVG");

printf ("\nsimplify(M11)..."); M11simp = simplify(M11);
printf ("\nsimplify(M12)..."); M12simp = simplify(M12);
printf ("\nsimplify(M13)..."); M13simp = simplify(M13);
printf ("\nsimplify(M14)..."); M14simp = simplify(M14);
printf ("\nsimplify(M15)..."); M15simp = simplify(M15);

printf ("\nsimplify(M22)..."); M22simp = simplify(M22);
printf ("\nsimplify(M23)..."); M23simp = simplify(M23);
printf ("\nsimplify(M24)..."); M24simp = simplify(M24);
printf ("\nsimplify(M25)..."); M25simp = simplify(M25);

printf ("\nsimplify(M33)..."); M33simp = simplify(M33);
printf ("\nsimplify(M34)..."); M34simp = simplify(M34);
printf ("\nsimplify(M35)..."); M35simp = simplify(M35);

printf ("\nsimplify(M44)..."); M44simp = simplify(M44);
printf ("\nsimplify(M45)..."); M45simp = simplify(M45);

printf ("\nsimplify(M55)..."); M55simp = simplify(M55);

printf ("\nsimplify(G1)..."); G1simp = 0;%simplify(G1);
printf ("\nsimplify(G2)..."); G2simp = simplify(G2);
printf ("\nsimplify(G3)..."); G3simp = simplify(G3);
printf ("\nsimplify(G4)..."); G4simp = simplify(G4);
printf ("\nsimplify(G5)..."); G5simp = simplify(G5);

M11simps = redux(char(M11simp));
M12simps = redux(char(M12simp));
M13simps = redux(char(M13simp));
M14simps = redux(char(M14simp));
M15simps = redux(char(M15simp));

M22simps = redux(char(M22simp));
M23simps = redux(char(M23simp));
M24simps = redux(char(M24simp));
M25simps = redux(char(M25simp));

M33simps = redux(char(M33simp));
M34simps = redux(char(M34simp));
M35simps = redux(char(M35simp));

M44simps = redux(char(M44simp));
M45simps = redux(char(M45simp));

M55simps = redux(char(M55simp));

G1simps  = "0";%redux(char(G1simp));
G2simps  = redux(char(G2simp));
G3simps  = redux(char(G3simp));
G4simps  = redux(char(G4simp));
G5simps  = redux(char(G5simp));

printf ("\nsave..."); save("MVGsimlified")
