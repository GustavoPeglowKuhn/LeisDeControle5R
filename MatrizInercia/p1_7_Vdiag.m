%carrega o pacote de simolicos
pkg load symbolic
sympref display flat
load("MVG")

%V1ds = redux(char(eval(V1)));
%V2ds = redux(char(eval(V2)));
%V3ds = redux(char(eval(V3)));
%V4ds = redux(char(eval(V4)));
%V5ds = redux(char(eval(V5)));

%[cv1, tv1] = coeffs(V1, [dq1, dq2, dq3, dq4, dq5]);
%[cv2, tv2] = coeffs(V2, [dq1, dq2, dq3, dq4, dq5]);
%[cv3, tv3] = coeffs(V3, [dq1, dq2, dq3, dq4, dq5]);
%[cv4, tv4] = coeffs(V4, [dq1, dq2, dq3, dq4, dq5]);
%[cv5, tv5] = coeffs(V5, [dq1, dq2, dq3, dq4, dq5]);

%V1dq1  = redux(char(simplify(expand(cv1( 1)))));
%V1dq2  = redux(char(simplify(expand(cv1( 2)))));
%V1dq3  = redux(char(simplify(expand(cv1( 3)))));
%V1dq4  = redux(char(simplify(expand(cv1( 4)))));
%V1dq5  = redux(char(simplify(expand(cv1( 5)))));
%V1dq6  = redux(char(simplify(expand(cv1( 6)))));
%V1dq7  = redux(char(simplify(expand(cv1( 7)))));
%V1dq8  = redux(char(simplify(expand(cv1( 8)))));
%V1dq9  = redux(char(simplify(expand(cv1( 9)))));
%V1dq10 = redux(char(simplify(expand(cv1(10)))));
%V1dq11 = redux(char(simplify(expand(cv1(11)))));
%V1dq12 = redux(char(simplify(expand(cv1(12)))));
%V1dq13 = redux(char(simplify(expand(cv1(13)))));
%V1dq14 = redux(char(simplify(expand(cv1(14)))));

%V2dq1  = redux(char(simplify(expand(cv2( 1)))));
%V2dq2  = redux(char(simplify(expand(cv2( 2)))));
%V2dq3  = redux(char(simplify(expand(cv2( 3)))));
%V2dq4  = redux(char(simplify(expand(cv2( 4)))));
%V2dq5  = redux(char(simplify(expand(cv2( 5)))));
%V2dq6  = redux(char(simplify(expand(cv2( 6)))));
%V2dq7  = redux(char(simplify(expand(cv2( 7)))));
%V2dq8  = redux(char(simplify(expand(cv2( 8)))));
%V2dq9  = redux(char(simplify(expand(cv2( 9)))));
%V2dq10 = redux(char(simplify(expand(cv2(10)))));
%V2dq11 = redux(char(simplify(expand(cv2(11)))));
%V2dq12 = redux(char(simplify(expand(cv2(12)))));
%V2dq13 = redux(char(simplify(expand(cv2(13)))));

%V3dq1  = redux(char(simplify(expand(cv3( 1)))));
%V3dq2  = redux(char(simplify(expand(cv3( 2)))));
%V3dq3  = redux(char(simplify(expand(cv3( 3)))));
%V3dq4  = redux(char(simplify(expand(cv3( 4)))));
%V3dq5  = redux(char(simplify(expand(cv3( 5)))));
%V3dq6  = redux(char(simplify(expand(cv3( 6)))));
%V3dq7  = redux(char(simplify(expand(cv3( 7)))));
%V3dq8  = redux(char(simplify(expand(cv3( 8)))));
%V3dq9  = redux(char(simplify(expand(cv3( 9)))));
%V3dq10 = redux(char(simplify(expand(cv3(10)))));
%V3dq11 = redux(char(simplify(expand(cv3(11)))));
%V3dq12 = redux(char(simplify(expand(cv3(12)))));
%V3dq13 = redux(char(simplify(expand(cv3(13)))));

%V4dq1  = redux(char(simplify(expand(cv4( 1)))));
%V4dq2  = redux(char(simplify(expand(cv4( 2)))));
%V4dq3  = redux(char(simplify(expand(cv4( 3)))));
%V4dq4  = redux(char(simplify(expand(cv4( 4)))));
%V4dq5  = redux(char(simplify(expand(cv4( 5)))));
%V4dq6  = redux(char(simplify(expand(cv4( 6)))));
%V4dq7  = redux(char(simplify(expand(cv4( 7)))));
%V4dq8  = redux(char(simplify(expand(cv4( 8)))));
%V4dq9  = redux(char(simplify(expand(cv4( 9)))));
%V4dq10 = redux(char(simplify(expand(cv4(10)))));
%V4dq11 = redux(char(simplify(expand(cv4(11)))));
%V4dq12 = redux(char(simplify(expand(cv4(12)))));
%V4dq13 = redux(char(simplify(expand(cv4(13)))));
%V4dq14 = redux(char(simplify(expand(cv4(14)))));

%V5dq1  = redux(char(simplify(expand(cv5( 1)))));
%V5dq2  = redux(char(simplify(expand(cv5( 2)))));
%V5dq3  = redux(char(simplify(expand(cv5( 3)))));
%V5dq4  = redux(char(simplify(expand(cv5( 4)))));
%V5dq5  = redux(char(simplify(expand(cv5( 5)))));
%V5dq6  = redux(char(simplify(expand(cv5( 6)))));
%V5dq7  = redux(char(simplify(expand(cv5( 7)))));
%V5dq8  = redux(char(simplify(expand(cv5( 8)))));
%V5dq9  = redux(char(simplify(expand(cv5( 9)))));
%V5dq10 = redux(char(simplify(expand(cv5(10)))));
%V5dq11 = redux(char(simplify(expand(cv5(11)))));
%V5dq12 = redux(char(simplify(expand(cv5(12)))));
%V5dq13 = redux(char(simplify(expand(cv5(13)))));
%V5dq14 = redux(char(simplify(expand(cv5(14)))));

