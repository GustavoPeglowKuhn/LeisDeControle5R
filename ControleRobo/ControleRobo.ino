#include "ControleRobo.h"

inline void CalcMVG(){
	#if defined(USE_R2_J2_J3)
		float q1 = q(2)+pi;
		float q2 = q(4)-(pi/2);
		float s1 = sinf(q1), s2 = sinf(q2);
		float c1 = cosf(q1), c2 = cosf(q2);
		// float s12 = sinf((q1+q2));
		float c12 = cosf((q1+q2));
		float dq1 = qp(2), dq2 = qp(4);
		
		M(0,0) = 1;	M(0,1) = 0;	M(0,2) = 0;	M(0,3) = 0;	M(0,4) = 0;
		M(1,0) = 0;							M(1,3) = 0;	M(1,4) = 0;
		M(2,0) = 0;							M(2,3) = 0; M(2,4) = 0;	
		M(3,0) = 0;	M(3,1) = 0;	M(3,2) = 0;	M(3,3) = 1;	M(3,4) = 0;
		M(4,0) = 0;	M(4,1) = 0;	M(4,2) = 0;	M(4,3) = 0; M(4,4) = 0;	
		
		M(1,1) = I1zz + I2zz + d1*d1*m2 + 2*d1*l2*m2*c2 + l1*l1*m1 + l2*l2*m2;
		M(1,2) = I2zz + d1*l2*m2*c2 + l2*l2*m2;
		M(2,1) = M(1,2);
		M(2,2) = I2zz +l2*l2*m2;
		
		G(0) = 0;	G(3) = 0;	G(4) = 0;
		G(1) = g*(d1*m2*c1 + l1*m1*c1 + l2*m2*c12);
		G(2) = g*(l2*m2*c12);
		
		V(0) = 0;	V(3) = 0;	V(4) = 0;
		V(1) = -d1*l2*m2*(2*dq1 + dq2)*s2*dq2;
		V(2) = d1*l2*m2*s2*dq1*dq1;
		
		Fd(1) = fd[1]*qp(1);
		Fd(2) = fd[2]*qp(2);
		
		Fs(1) = (qp(1)>0.01)?fs[1]:( (qp(1)<-0.01)?-fs[1]:0 );
		Fs(2) = (qp(2)>0.01)?fs[2]:( (qp(2)<-0.01)?-fs[2]:0 );
	#elif defined(USE_R2_J3_J5)
		float q1 = q(2)+pi;
		float q2 = q(4)-(pi/2);
		float s1 = sinf(q1), s2 = sinf(q2);
		float c1 = cosf(q1), c2 = cosf(q2);
		// float s12 = sinf((q1+q2));
		float c12 = cosf((q1+q2));
		float dq1 = qp(2), dq2 = qp(4);
		
		M(0,0) = 1;	M(0,1) = 0;	M(0,2) = 0;	M(0,3) = 0;	M(0,4) = 0;
		M(1,0) = 0;	M(1,1) = 1;	M(1,2) = 0;	M(1,3) = 0;	M(1,4) = 0;
		M(2,0) = 0;	M(2,1) = 0;				M(2,3) = 0;
		M(3,0) = 0;	M(3,1) = 0;	M(3,2) = 0;	M(3,3) = 1;	M(3,4) = 0;
		M(4,0) = 0;	M(4,1) = 0;				M(4,3) = 0;
		
		// M(2,2) = l2*l2*m2 + 2*l1*l2*m2*c2 +l1*l1*(m1+m2);
		// M(2,4) = l2*l2*m2 + l1*l2*m2*c2;
		// M(4,2) = M(2,4);
		// M(4,4) = l2*l2*m2;
		
		M(2,2) = I1zz + I2zz + d1*d1*m2 + 2*d1*l2*m2*c2 + l1*l1*m1 + l2*l2*m2;
		M(2,4) = I2zz + d1*l2*m2*c2 + l2*l2*m2;
		M(4,2) = M(2,4);
		M(4,4) = I2zz +l2*l2*m2;
		
		G(0) = 0;	G(1) = 0;	G(3) = 0;
		// G(2) = g*(l2*m2*c12 + l1*(m1+m2)*c1);
		// G(4) = g*(l2*m2*c12);
		G(2) = g*(d1*m2*c1 + l1*m1*c1 + l2*m2*c12);
		G(4) = g*(l2*m2*c12);
		
		V(0) = 0;	V(1) = 0;	V(3) = 0;	
		// V(2) = -(l1*l2*m2*s2)*(dq2*dq2 + 2*dq1*dq2);
		// V(4) = l1*l2*m2*s2*dq1*dq1;
		V(2) = -d1*l2*m2*(2*dq1 + dq2)*s2*dq2;
		V(4) = d1*l2*m2*s2*dq1*dq1;
		
		Fd(2) = fd[2]*qp(2);
		Fd(4) = fd[4]*qp(4);
		
		Fs(2) = (qp(2)>0.01)?fs[2]:( (qp(2)<-0.01)?-fs[2]:0 );
		Fs(4) = (qp(4)>0.01)?fs[4]:( (qp(4)<-0.01)?-fs[4]:0 );
	#else
		float s1 = sinf(q(0)), s2 = sinf(q(1)), s3 = sinf(q(2)), s4 = sinf(q(3)), s5 = sinf(q(4));
		float c1 = cosf(q(0)), c2 = cosf(q(1)), c3 = cosf(q(2)), c4 = cosf(q(3)), c5 = cosf(q(4));
		float s23 = sinf((q(1)+q(2)));
		float c23 = cosf((q(1)+q(2)));

		float	ss1 = s1*s1,
				cc1 = c1*c1,
				ss2 = s2*s2,
				cc2 = c2*c2,
				ss3 = s3*s3,
				cc3 = c3*c3,
				ss23 = s23*s23,
				cc23 = c23*c23,
				ss4 = s4*s4,
				cc4 = c4*c4,
				ss5 = s5*s5,
				cc5 = c5*c5,
				l5l5 = l5*l5;
				//c4c5 = c4*c5,
				//l5m5 = l5*m5;

		float 	dq1 = qp(0),
				dq2 = qp(1),
				dq3 = qp(2),
				dq4 = qp(3),
				dq5 = qp(4);

		/*float 	dth1dth1 = qp(0)*qp(0),
				dth1dth2 = qp(0)*qp(1),
				dth1dth3 = qp(0)*qp(2),
				dth1dth4 = qp(0)*qp(3),
				dth1dth5 = qp(0)*qp(4),
				dth2dth2 = qp(1)*qp(1),
				dth2dth3 = qp(1)*qp(2),
				dth2dth4 = qp(1)*qp(3),
				dth2dth5 = qp(1)*qp(4),
				dth3dth3 = qp(2)*qp(2),
				dth3dth4 = qp(2)*qp(3),
				dth3dth5 = qp(2)*qp(4),
				dth4dth4 = qp(3)*qp(3),
				dth4dth5 = qp(3)*qp(4),
				dth5dth5 = qp(4)*qp(4);*/

		M(0,0) = I1zz + I2xx*ss2 - I2yy*ss2 + I2yy + I3xx*ss2 + 2*I3xx*s2*s3*c23 + I3xx*ss3 - I3yy*ss2 - 2*I3yy*s2*s3*c23 - I3yy*ss3 + I3yy - I4xx*ss2*ss4 + I4xx*ss2 - 2*I4xx*s2*s3*ss4*c23 + 2*I4xx*s2*s3*c23 - I4xx*ss3*ss4 + I4xx*ss3 + I4yy*ss2*ss4 + 2*I4yy*s2*s3*ss4*c23 + I4yy*ss3*ss4 - I4zz*ss2 - 2*I4zz*s2*s3*c23 - I4zz*ss3 + I4zz - 4*I5xx*s23*s2*s3*s5*c4*c5 + I5xx*ss2*ss4*ss5 - I5xx*ss2*ss4 - 2*I5xx*ss2*ss5 + I5xx*ss2 + 2*I5xx*s2*s3*ss4*ss5*c23 - 2*I5xx*s2*s3*ss4*c23 - 4*I5xx*s2*s3*ss5*c23 + 2*I5xx*s2*s3*c23 + 2*I5xx*s2*s5*c2*c4*c5 + I5xx*ss3*ss4*ss5 - I5xx*ss3*ss4 - 2*I5xx*ss3*ss5 + I5xx*ss3 + 2*I5xx*s3*s5*c3*c4*c5 + I5xx*ss5 + 4*I5yy*s23*s2*s3*s5*c4*c5 - I5yy*ss2*ss4*ss5 + 2*I5yy*ss2*ss5 - I5yy*ss2 - 2*I5yy*s2*s3*ss4*ss5*c23 + 4*I5yy*s2*s3*ss5*c23 - 2*I5yy*s2*s3*c23 - 2*I5yy*s2*s5*c2*c4*c5 - I5yy*ss3*ss4*ss5 + 2*I5yy*ss3*ss5 - I5yy*ss3 - 2*I5yy*s3*s5*c3*c4*c5 - I5yy*ss5 + I5yy  + I5zz*ss2*ss4 + 2*I5zz*s2*s3*ss4*c23 + I5zz*ss3*ss4 + a2*a2*(m3 + m4 + m5)*cc2 + 2*a2*(-d4*(m4 + m5) - l3*m3 - l4*m4)*s23*c2 + 2*a2*l5*m5*(-s23*s5 + c23*c4*c5)*c2 + d4*d4*(m4 + m5)*ss23 + 2*d4*l4*m4*ss23 + 4*d4*l5*m5*s2*s3*s5*c2*c3 + l2*l2*m2*cc2 + (l3*l3*m3 + l4*l4*m4)*ss23 + l5l5*m5*( ((ss5 - cc4*cc5)*(2*c2*c3 - s2*s3))*s2*s3 + (1 - cc2*cc3)*ss4*cc5 - 2*ss5*cc2*cc3 + cc2*cc3 + ss5 - 2*s23*s5*c23*c4*c5 );
		M(0,1) = - I4xx*s23*s4*c4 + I4yy*s23*s4*c4 - I5xx*s23*s4*c4*cc5 - I5xx*s4*s5*c23*c5 + I5yy*s23*s4*c4*cc5 - I5yy*s23*s4*c4 + I5yy*s4*s5*c23*c5 + I5zz*s23*s4*c4 + a2*l5*m5*s2*s4*c5 + d4*l5*m5*s4*c23*c5 + l5l5*m5*(s23*c4*c5 + s5*c23)*s4*c5;
		M(0,2) = - I4xx*s23*s4*c4 + I4yy*s23*s4*c4 - I5xx*s23*s4*c4*cc5 - I5xx*s4*s5*c23*c5 + I5yy*s23*s4*c4*cc5 - I5yy*s23*s4*c4 + I5yy*s4*s5*c23*c5 + I5zz*s23*s4*c4 + d4*l5*m5*s4*c23*c5 + l5l5*m5*(s23*c4*c5 + s5*c23)*s4*c5;
		M(0,3) = I4zz*c23 + I5xx*s23*s5*c4*c5 - I5xx*c23*cc5 + I5xx*c23 - I5yy*s23*s5*c4*c5 + I5yy*c23*cc5 + a2*l5*m5*c2*c4*c5 - d4*l5*m5*s23*c4*c5 + l5l5*m5*(c23*c5 - s23*s5*c4)*c5;
		M(0,4) = I5zz*s23*s4 - a2*l5*m5*s4*s5*c2 + d4*l5*m5*s23*s4*s5 + l5l5*m5*s23*s4;

		M(1,0) = M(0,1);
		M(1,1) = I2zz + I3zz + I4xx*ss4 + I4yy*cc4 + I5xx*ss4*cc5 + I5yy*ss4*ss5 + I5zz*cc4 + a2*a2*(m3 + m4 + m5) - 2*a2*d4*m4*s3 - 2*a2*d4*m5*s3 - 2*a2*l3*m3*s3 - 2*a2*l4*m4*s3 - 2*a2*l5*m5*s3*s5 + 2*a2*l5*m5*c3*c4*c5 + d4*d4*m4 + d4*d4*m5 + 2*d4*l4*m4 + 2*d4*l5*m5*s5 + l2*l2*m2 + l3*l3*m3 + l4*l4*m4 + l5l5*m5*(ss4*ss5 - ss4 + 1);
		M(1,2) = I3zz + I4xx*ss4 + I4yy*cc4 + I5xx*ss4*cc5 + I5yy*ss4*ss5 + I5zz*cc4 - a2*d4*m4*s3 - a2*d4*m5*s3 - a2*l3*m3*s3 - a2*l4*m4*s3 - a2*l5*m5*s3*s5 + a2*l5*m5*c3*c4*c5 + d4*d4*m4 + d4*d4*m5 + 2*d4*l4*m4 + 2*d4*l5*m5*s5 + l3*l3*m3 + l4*l4*m4 + l5l5*m5*(ss4*ss5 - ss4 + 1);
		M(1,3) = - I5xx*s4*s5*c5 + I5yy*s4*s5*c5 - a2*l5*m5*s3*s4*c5 + d4*l5*m5*s4*c5 + l5l5*m5*s4*s5*c5;
		M(1,4) = I5zz*c4 + a2*l5*m5*(-s3*s5*c4 + c3*c5) + d4*l5*m5*s5*c4 + l5l5*m5*c4;

		M(2,0) = M(0,2);
		M(2,1) = M(1,2);
		M(2,2) = I3zz + I4xx*ss4 + I4yy*cc4 + I5xx*ss4*cc5 + I5yy*ss4*ss5 + I5zz*cc4 + d4*d4*m4 + d4*d4*m5 + 2*d4*l4*m4 + 2*d4*l5*m5*s5 + l3*l3*m3 + l4*l4*m4 + l5l5*m5*(ss4*ss5 - ss4 + 1);
		M(2,3) = - I5xx*s4*s5*c5 + I5yy*s4*s5*c5 + d4*l5*m5*ss23*s4*c5 + d4*l5*m5*ss1*s4*cc23*c5 + d4*l5*m5*s4*cc23*cc1*c5 + l5l5*m5*ss23*s4*s5*c5 + l5l5*m5*s23*ss1*s4*c23*c4*cc5 + l5l5*m5*s23*s4*c23*cc1*c4*cc5 - l5l5*m5*s23*s4*c23*c4*cc5 + l5l5*m5*ss1*s4*s5*cc23*c5 + l5l5*m5*s4*s5*cc23*cc1*c5;
		M(2,4) = I5zz*c4 + l5*m5*(d4*s5 + l5)*c4;

		M(3,0) = M(0,3);
		M(3,1) = M(1,3);
		M(3,2) = M(2,3);
		M(3,3) = I4zz + I5xx*ss5 + I5yy*cc5 + l5l5*m5*cc5;
		M(3,4) = 0;

		M(4,0) = M(0,4);
		M(4,1) = M(1,4);
		M(4,2) = M(2,4);
		M(4,3) = M(3,4);
		M(4,4) = I5zz + l5l5*m5;

		G(0) = 0;
		G(1) = g*( + a2*(m3 + m4 + m5)*c2 - d4*(m4 + m5)*s23 + l2*m2*c2 - l3*m3*s23 - l4*m4*s23 + l5*m5*(c23*c4*c5 - s23*s5));
		G(2) = g*( - d4*(m4 + m5)*s23 - l3*m3*s23 - l4*m4*s23 + l5*m5*(c23*c4*c5 - s23*s5));
		G(3) = g*( - l5*m5*s23*s4*c5);
		G(4) = g*( + l5*m5*(c23*c5 - s23*s5*c4));

		//V(0) = 0;	V(1) = 0;	V(2) = 0;	V(3) = 0;	V(4) = 0;
		V(0) = 
			 dq1*dq2*(2*I2xx*s2*c2 - 2*I2yy*s2*c2 - 4*I3xx*s23*s2*s3 + 2*I3xx*s2*c2 + 2*I3xx*s3*c3 + 4*I3yy*s23*s2*s3 - 2*I3yy*s2*c2 - 2*I3yy*s3*c3 - 4*I4xx*s23*s2*s3*cc4 + 2*I4xx*s2*c2*cc4 + 2*I4xx*s3*c3*cc4 + 4*I4yy*s23*s2*s3*cc4 - 4*I4yy*s23*s2*s3 - 2*I4yy*s2*c2*cc4 + 2*I4yy*s2*c2 - 2*I4yy*s3*c3*cc4 + 2*I4yy*s3*c3 + 4*I4zz*s23*s2*s3 - 2*I4zz*s2*c2 - 2*I4zz*s3*c3 - 4*I5xx*s23*s2*s3*cc4*cc5 - 4*I5xx*s23*s2*s3*cc5 + 4*I5xx*s23*s2*s3 - 8*I5xx*s2*s3*s5*c23*c4*c5 + 2*I5xx*s2*c2*cc4*cc5 + 2*I5xx*s2*c2*cc5 - 2*I5xx*s2*c2 + 2*I5xx*s3*c3*cc4*cc5 + 2*I5xx*s3*c3*cc5 - 2*I5xx*s3*c3 + 4*I5xx*s5*cc2*c4*c5 + 4*I5xx*s5*cc3*c4*c5 - 6*I5xx*s5*c4*c5 + 4*I5yy*s23*s2*s3*cc4*cc5 - 4*I5yy*s23*s2*s3*cc4 + 4*I5yy*s23*s2*s3*cc5 + 8*I5yy*s2*s3*s5*c23*c4*c5 - 2*I5yy*s2*c2*cc4*cc5 + 2*I5yy*s2*c2*cc4 - 2*I5yy*s2*c2*cc5 - 2*I5yy*s3*c3*cc4*cc5 + 2*I5yy*s3*c3*cc4 - 2*I5yy*s3*c3*cc5 - 4*I5yy*s5*cc2*c4*c5 - 4*I5yy*s5*cc3*c4*c5 + 6*I5yy*s5*c4*c5 + 4*I5zz*s23*s2*s3*cc4 - 4*I5zz*s23*s2*s3 - 2*I5zz*s2*c2*cc4 + 2*I5zz*s2*c2 - 2*I5zz*s3*c3*cc4 + 2*I5zz*s3*c3 - 2*a2*a2*m3*s2*c2 - 2*a2*a2*m4*s2*c2 - 2*a2*a2*m5*s2*c2 + 4*a2*d4*m4*s23*s2 - 2*a2*d4*m4*c3 + 4*a2*d4*m5*s23*s2 - 2*a2*d4*m5*c3 + 4*a2*l3*m3*s23*s2 - 2*a2*l3*m3*c3 + 4*a2*l4*m4*s23*s2 - 2*a2*l4*m4*c3 + 4*a2*l5*m5*s23*s2*s5 - 4*a2*l5*m5*s2*c23*c4*c5 - 2*a2*l5*m5*s3*c4*c5 - 2*a2*l5*m5*s5*c3 + d4*d4*(m4 + m5)*2*s23*c23 + 4*d4*l4*m4*s23*c23 + 4*d4*l5*m5*s23*s5*c23 + 8*d4*l5*m5*s2*s3*c23*c4*c5 - 4*d4*l5*m5*cc2*c4*c5 - 4*d4*l5*m5*cc3*c4*c5 + 6*d4*l5*m5*c4*c5 - 2*l2*l2*m2*s2*c2 + 2*l3*l3*m3*s23*c23 + 2*l4*l4*m4*s23*c23 - 2*l5*l5*m5*s23*c23*cc4*cc5 - 2*l5*l5*m5*s23*c23*cc5 + 2*l5*l5*m5*s23*c23 - 2*l5*l5*m5*s5*(cc23 - ss23)*c4*c5)
			+dq1*dq3*(-4*I3xx*s23*s2*s3 + 2*I3xx*s2*c2 + 2*I3xx*s3*c3 + 4*I3yy*s23*s2*s3 - 2*I3yy*s2*c2 - 2*I3yy*s3*c3 - 4*I4xx*s23*s2*s3*cc4 + 2*I4xx*s2*c2*cc4 + 2*I4xx*s3*c3*cc4 + 4*I4yy*s23*s2*s3*cc4 - 4*I4yy*s23*s2*s3 - 2*I4yy*s2*c2*cc4 + 2*I4yy*s2*c2 - 2*I4yy*s3*c3*cc4 + 2*I4yy*s3*c3 + 4*I4zz*s23*s2*s3 - 2*I4zz*s2*c2 - 2*I4zz*s3*c3 - 4*I5xx*s23*s2*s3*cc4*cc5 - 4*I5xx*s23*s2*s3*cc5 + 4*I5xx*s23*s2*s3 - 8*I5xx*s2*s3*s5*c23*c4*c5 + 2*I5xx*s2*c2*cc4*cc5 + 2*I5xx*s2*c2*cc5 - 2*I5xx*s2*c2 + 2*I5xx*s3*c3*cc4*cc5 + 2*I5xx*s3*c3*cc5 - 2*I5xx*s3*c3 + 4*I5xx*s5*cc2*c4*c5 + 4*I5xx*s5*cc3*c4*c5 - 6*I5xx*s5*c4*c5 + 4*I5yy*s23*s2*s3*cc4*cc5 - 4*I5yy*s23*s2*s3*cc4 + 4*I5yy*s23*s2*s3*cc5 + 8*I5yy*s2*s3*s5*c23*c4*c5 - 2*I5yy*s2*c2*cc4*cc5 + 2*I5yy*s2*c2*cc4 - 2*I5yy*s2*c2*cc5 - 2*I5yy*s3*c3*cc4*cc5 + 2*I5yy*s3*c3*cc4 - 2*I5yy*s3*c3*cc5 - 4*I5yy*s5*cc2*c4*c5 - 4*I5yy*s5*cc3*c4*c5 + 6*I5yy*s5*c4*c5 + 4*I5zz*s23*s2*s3*cc4 - 4*I5zz*s23*s2*s3 - 2*I5zz*s2*c2*cc4 + 2*I5zz*s2*c2 - 2*I5zz*s3*c3*cc4 + 2*I5zz*s3*c3 - 2*a2*d4*m4*c23*c2 - 2*a2*d4*m5*c23*c2 - 2*a2*l3*m3*c23*c2 - 2*a2*l4*m4*c23*c2 - 2*a2*l5*m5*(s23*c4*c5 + s5*c23)*c2 + d4*d4*(m4 + m5)*2*s23*c23 + 4*d4*l4*m4*s23*c23 + 4*d4*l5*m5*s23*s5*c23 + 8*d4*l5*m5*s2*s3*c23*c4*c5 - 4*d4*l5*m5*cc2*c4*c5 - 4*d4*l5*m5*cc3*c4*c5 + 6*d4*l5*m5*c4*c5 + 2*l3*l3*m3*s23*c23 + (l4*l4*m4 + l5*l5*m5)*2*s23*c23 + 2*l5*l5*m5*(ss4 - 2)*s23*c23*cc5  - 2*l5*l5*m5*s5*(cc23 - ss23)*c4*c5)
			+dq1*dq4*(-2*I4xx*ss2*s4*c4 - 4*I4xx*s2*s3*s4*c23*c4 - 2*I4xx*ss3*s4*c4 + 2*I4yy*ss2*s4*c4 + 4*I4yy*s2*s3*s4*c23*c4 + 2*I4yy*ss3*s4*c4  + 4*I5xx*s23*s2*s3*s4*s5*c5 + 2*I5xx*ss2*s4*ss5*c4 - 2*I5xx*ss2*s4*c4 + 4*I5xx*s2*s3*s4*ss5*c23*c4 - 4*I5xx*s2*s3*s4*c23*c4 - 2*I5xx*s2*s4*s5*c2*c5 + 2*I5xx*ss3*s4*ss5*c4 - 2*I5xx*ss3*s4*c4 - 2*I5xx*s3*s4*s5*c3*c5 - 4*I5yy*s23*s2*s3*s4*s5*c5 - 2*I5yy*ss2*s4*ss5*c4 - 4*I5yy*s2*s3*s4*ss5*c23*c4 + 2*I5yy*s2*s4*s5*c2*c5 - 2*I5yy*ss3*s4*ss5*c4 + 2*I5yy*s3*s4*s5*c3*c5 + 2*I5zz*ss2*s4*c4 + 4*I5zz*s2*s3*s4*c23*c4 + 2*I5zz*ss3*s4*c4 - 2*a2*l5*m5*s4*c23*c2*c5 + 2*d4*l5*m5*s23*s4*c23*c5 + 2*l5*l5*m5*s23*s4*s5*c23*c5 - 2*l5*l5*m5*ss2*s4*ss5*c4 + 2*l5*l5*m5*ss2*s4*c4 - 4*l5*l5*m5*s2*s3*s4*ss5*c23*c4 + 4*l5*l5*m5*s2*s3*s4*c23*c4 - 2*l5*l5*m5*ss3*s4*ss5*c4 + 2*l5*l5*m5*ss3*s4*c4)
			+dq1*dq5*(8*I5xx*s23*s2*s3*ss5*c4 - 4*I5xx*s23*s2*s3*c4 + 2*I5xx*ss2*ss4*s5*c5 - 4*I5xx*ss2*s5*c5 + 4*I5xx*s2*s3*ss4*s5*c23*c5 - 8*I5xx*s2*s3*s5*c23*c5 - 4*I5xx*s2*ss5*c2*c4 + 2*I5xx*s2*c2*c4 + 2*I5xx*ss3*ss4*s5*c5 - 4*I5xx*ss3*s5*c5 - 4*I5xx*s3*ss5*c3*c4 + 2*I5xx*s3*c3*c4 + 2*I5xx*s5*c5 - 8*I5yy*s23*s2*s3*ss5*c4 + 4*I5yy*s23*s2*s3*c4 - 2*I5yy*ss2*ss4*s5*c5 + 4*I5yy*ss2*s5*c5 - 4*I5yy*s2*s3*ss4*s5*c23*c5 + 8*I5yy*s2*s3*s5*c23*c5 + 4*I5yy*s2*ss5*c2*c4 - 2*I5yy*s2*c2*c4 - 2*I5yy*ss3*ss4*s5*c5 + 4*I5yy*ss3*s5*c5 + 4*I5yy*s3*ss5*c3*c4 - 2*I5yy*s3*c3*c4 - 2*I5yy*s5*c5 - 2*a2*l5*m5*(s23*c5 + s5*c23*c4)*c2 + 2*d4*l5*m5*s23*s5*c23*c4 + 2*d4*l5*m5*ss2*c5 + 4*d4*l5*m5*s2*s3*c23*c5 + 2*d4*l5*m5*ss3*c5 + 2*l5*l5*m5*s23*c23*c4*(2*ss5 - 1) + 2*l5*l5*m5*s5*c5*(ss23*cc4 - cc23))
			+dq2*dq2*(- I4xx*s4*c23*c4  + I4yy*s4*c23*c4 + I5xx*s23*s4*s5*c5 - I5xx*s4*c23*c4*cc5 - I5yy*s23*s4*s5*c5 + I5yy*s4*c23*c4*cc5 - I5yy*s4*c23*c4 + I5zz*s4*c23*c4 + a2*l5*m5*s4*c2*c5 - d4*l5*m5*s23*s4*c5 - l5*l5*m5*s23*s4*s5*c5 + l5*l5*m5*s4*c23*c4*cc5)
			+dq2*dq3*(- 2*I4xx*s4*c23*c4 + 2*I4yy*s4*c23*c4 + 2*I5xx*s23*s4*s5*c5 - 2*I5xx*s4*c23*c4*cc5 - 2*I5yy*s23*s4*s5*c5 + 2*I5yy*s4*c23*c4*cc5 - 2*I5yy*s4*c23*c4 + 2*I5zz*s4*c23*c4 - 2*d4*l5*m5*s23*s4*c5 - 2*l5*l5*m5*s23*s4*s5*c5 + 2*l5*l5*m5*s4*c23*c4*cc5)
			+dq2*dq4*((2*I4xx*ss4 - I4xx - 2*I4yy*ss4 + I4yy - I4zz - 2*I5xx*ss4*ss5 + 2*I5xx*ss4 - I5xx + 2*I5yy*ss4*ss5 - I5yy - 2*I5zz*ss4 + I5zz + 2*l5*l5*m5*ss4*ss5 - 2*l5*l5*m5*ss4)*s23)
			+dq2*dq5*(2*I5xx*s23*s4*s5*c4*c5 - 2*I5xx*s4*c23*cc5 + I5xx*s4*c23 - 2*I5yy*s23*s4*s5*c4*c5 + 2*I5yy*s4*c23*cc5 - I5yy*s4*c23 + I5zz*s4*c23 + 2*l5*l5*m5*(-s23*s5*c4 + c23*c5)*s4*c5)
			+dq3*dq3*(- I4xx*s4*c23*c4 + I4yy*s4*c23*c4 + I5xx*s23*s4*s5*c5 - I5xx*s4*c23*c4*cc5 - I5yy*s23*s4*s5*c5 + I5yy*s4*c23*c4*cc5 - I5yy*s4*c23*c4 + I5zz*s4*c23*c4 - d4*l5*m5*s23*s4*c5 + l5*l5*m5*(-s23*s5 + c23*c4*c5)*s4*c5)
			+dq3*dq4*((2*I4xx*ss4 - I4xx - 2*I4yy*ss4 + I4yy - I4zz - 2*I5xx*ss4*ss5 + 2*I5xx*ss4 - I5xx + 2*I5yy*ss4*ss5 - I5yy - 2*I5zz*ss4 + I5zz + 2*l5*l5*m5*ss4*ss5 - 2*l5*l5*m5*ss4)*s23)
			+dq3*dq5*(2*I5xx*s23*s4*s5*c4*c5 - 2*I5xx*s4*c23*cc5 + I5xx*s4*c23 - 2*I5yy*s23*s4*s5*c4*c5 + 2*I5yy*s4*c23*cc5 - I5yy*s4*c23 + I5zz*s4*c23 + 2*l5*l5*m5*(-s23*s5*c4 + c23*c5)*s4*c5)
			+dq4*dq4*(- I5xx*s23*s4*s5*c5 + I5yy*s23*s4*s5*c5 - a2*l5*m5*s4*c2*c5 + d4*l5*m5*s23*s4*c5 + l5*l5*m5*s23*s4*s5*c5)
			+dq4*dq5*(-2*I5xx*s23*ss5*c4 + I5xx*s23*c4 + 2*I5xx*s5*c23*c5  + 2*I5yy*s23*ss5*c4 - I5yy*s23*c4 - 2*I5yy*s5*c23*c5 + I5zz*s23*c4 - 2*a2*l5*m5*s5*c2*c4 + 2*d4*l5*m5*s23*s5*c4 + 2*l5*l5*m5*(s23*s5*c4 - c23*c5)*s5)
			+dq5*dq5*(- a2*l5*m5*s4*c2*c5 + d4*l5*m5*s23*s4*c5);

		V(1) = 
			 dq1*dq1*(-I2xx*s2*c2 + I2yy*s2*c2 + 2*I3xx*s23*s2*s3 - I3xx*s2*c2 - I3xx*s3*c3 - 2*I3yy*s23*s2*s3 + I3yy*s2*c2 + I3yy*s3*c3 + 2*I4xx*s23*s2*s3*cc4 - I4xx*s2*c2*cc4 - I4xx*s3*c3*cc4   - 2*I4yy*s23*s2*s3*cc4 + 2*I4yy*s23*s2*s3 + I4yy*s2*c2*cc4 - I4yy*s2*c2 + I4yy*s3*c3*cc4 - I4yy*s3*c3 - 2*I4zz*s23*s2*s3 + I4zz*s2*c2 + I4zz*s3*c3 + 2*I5xx*s23*s2*s3*cc4*cc5 + 2*I5xx*s23*s2*s3*cc5 - 2*I5xx*s23*s2*s3 + 4*I5xx*s2*s3*s5*c23*c4*c5 - I5xx*s2*c2*cc4*cc5 - I5xx*s2*c2*cc5 + I5xx*s2*c2 - I5xx*s3*c3*cc4*cc5 - I5xx*s3*c3*cc5 + I5xx*s3*c3 - 2*I5xx*s5*cc2*c4*c5 - 2*I5xx*s5*cc3*c4*c5 + 3*I5xx*s5*c4*c5 - 2*I5yy*s23*s2*s3*cc4*cc5 + 2*I5yy*s23*s2*s3*cc4 - 2*I5yy*s23*s2*s3*cc5 - 4*I5yy*s2*s3*s5*c23*c4*c5 + I5yy*s2*c2*cc4*cc5 - I5yy*s2*c2*cc4 + I5yy*s2*c2*cc5 + I5yy*s3*c3*cc4*cc5 - I5yy*s3*c3*cc4 + I5yy*s3*c3*cc5 + 2*I5yy*s5*cc2*c4*c5 + 2*I5yy*s5*cc3*c4*c5 - 3*I5yy*s5*c4*c5 - 2*I5zz*s23*s2*s3*cc4 + 2*I5zz*s23*s2*s3 + I5zz*s2*c2*cc4 - I5zz*s2*c2 + I5zz*s3*c3*cc4 - I5zz*s3*c3 + a2*a2*(m3 + m4 + m5)*s2*c2 + a2*(-2*d4*m4*s23*s2 + d4*m4*c3 - 2*d4*m5*s23*s2 + d4*m5*c3 - 2*l3*m3*s23*s2 + l3*m3*c3 - 2*l4*m4*s23*s2 + l4*m4*c3 - 2*l5*m5*s23*s2*s5 + 2*l5*m5*s2*c23*c4*c5 + l5*m5*s3*c4*c5 + l5*m5*s5*c3) - d4*d4*(m4+m5)*s23*c23 - 2*d4*l4*m4*s23*c23 - 2*d4*l5*m5*s23*s5*c23 + d4*l5*m5*(cc23 - ss23)*c4*c5 + l2*l2*m2*s2*c2 - l3*l3*m3*s23*c23 - l4*l4*m4*s23*c23 + l5*l5*m5*(cc4*cc5 + cc5 - 1)*s23*c23 + l5*l5*m5*s5*(cc23 - ss23)*c4*c5)
			+dq1*dq4*(-2*I4xx*s23*cc4 + I4xx*s23 + 2*I4yy*s23*cc4 - I4yy*s23 + I4zz*s23 - 2*I5xx*s23*cc4*cc5 + I5xx*s23 - 2*I5xx*s5*c23*c4*c5 + 2*I5yy*s23*cc4*cc5 - 2*I5yy*s23*cc4 + I5yy*s23 + 2*I5yy*s5*c23*c4*c5 + 2*I5zz*s23*cc4 - I5zz*s23 + 2*l5*m5*(a2*s2 + d4*c23)*c4*c5 + 2*l5*l5*m5*(s23*c4*c5 + s5*c23)*c4*c5)
			+dq1*dq5*((2*I5xx*s23*s5*c4*c5 + 2*I5xx*ss5*c23 - I5xx*c23 - 2*I5yy*s23*s5*c4*c5 - 2*I5yy*ss5*c23 + I5yy*c23 - I5zz*c23 - 2*l5*m5*(a2*s2 + d4*c23)*s5 - 2*l5*l5*m5*(s23*c4*c5 + s5*c23)*s5)*s4)
			+dq2*dq3*(- 2*a2*d4*(m4 + m5)*c3 - 2*a2*l3*m3*c3 - 2*a2*l4*m4*c3 - 2*a2*l5*m5*(s3*c4*c5 + s5*c3))
			+dq2*dq4*(2*I4xx*s4*c4 - 2*I4yy*s4*c4 + 2*I5xx*s4*c4*cc5 + 2*I5yy*s4*ss5*c4 - 2*I5zz*s4*c4 - 2*a2*l5*m5*s4*c3*c5 - 2*l5*l5*m5*s4*c4*cc5)
			+dq2*dq5*(-2*I5xx*ss4*s5*c5 + 2*I5yy*ss4*s5*c5 - 2*a2*l5*m5*(s3*c5 + s5*c3*c4) + 2*d4*l5*m5*c5 + 2*l5*l5*m5*ss4*s5*c5)
			+dq3*dq3*(- a2*(d4*m4*c3 + d4*m5*c3 + l3*m3*c3 + l4*m4*c3 + l5*m5*s3*c4*c5 + l5*m5*s5*c3))
			+dq3*dq4*(2*I4xx*s4*c4 - 2*I4yy*s4*c4 + 2*I5xx*s4*c4*cc5 + 2*I5yy*s4*ss5*c4 - 2*I5zz*s4*c4 - 2*a2*l5*m5*s4*c3*c5 - 2*l5*l5*m5*s4*c4*cc5)
			+dq3*dq5*(-2*I5xx*ss4*s5*c5 + 2*I5yy*ss4*s5*c5 - 2*a2*l5*m5*(s3*c5 + s5*c3*c4) + 2*d4*l5*m5*c5 + 2*l5*l5*m5*ss4*s5*c5)
			+dq4*dq4*(- I5xx*s5*c4*c5 + I5yy*s5*c4*c5 - a2*l5*m5*s3*c4*c5 + d4*l5*m5*c4*c5 + l5*l5*m5*s5*c4*c5)
			+dq4*dq5*(I5xx*s4*ss5 - I5xx*s4*cc5 - I5yy*s4*ss5 + I5yy*s4*cc5 - I5zz*s4 + 2*a2*l5*m5*s3*s4*s5 -2*d4*l5*m5*s4*s5 - 2*l5*l5*m5*s4*ss5)
			+dq5*dq5*(- a2*l5*m5*(s3*c4*c5 + s5*c3) + d4*l5*m5*c4*c5);

		V(2) = 
			 dq1*dq1*(2*I3xx*s23*s2*s3 - I3xx*s2*c2 - I3xx*s3*c3 - 2*I3yy*s23*s2*s3 + I3yy*s2*c2 + I3yy*s3*c3 - 2*I4xx*s23*s2*s3*ss4 + 2*I4xx*s23*s2*s3 + I4xx*s2*ss4*c2 - I4xx*s2*c2 + I4xx*s3*ss4*c3 - I4xx*s3*c3 + 2*I4yy*s23*s2*s3*ss4 - I4yy*s2*ss4*c2 - I4yy*s3*ss4*c3  - 2*I4zz*s23*s2*s3 + I4zz*s2*c2 + I4zz*s3*c3 + 2*I5xx*s23*s2*s3*ss4*ss5 - 2*I5xx*s23*s2*s3*ss4 - 4*I5xx*s23*s2*s3*ss5 + 2*I5xx*s23*s2*s3 + 2*I5xx*ss2*s5*c4*c5 + 4*I5xx*s2*s3*s5*c23*c4*c5 - I5xx*s2*ss4*ss5*c2 + I5xx*s2*ss4*c2 + 2*I5xx*s2*ss5*c2 - I5xx*s2*c2 + 2*I5xx*ss3*s5*c4*c5 - I5xx*s3*ss4*ss5*c3 + I5xx*s3*ss4*c3 + 2*I5xx*s3*ss5*c3 - I5xx*s3*c3 - I5xx*s5*c4*c5 - 2*I5yy*s23*s2*s3*ss4*ss5 + 4*I5yy*s23*s2*s3*ss5 - 2*I5yy*s23*s2*s3 - 2*I5yy*ss2*s5*c4*c5 - 4*I5yy*s2*s3*s5*c23*c4*c5 + I5yy*s2*ss4*ss5*c2 - 2*I5yy*s2*ss5*c2 + I5yy*s2*c2 - 2*I5yy*ss3*s5*c4*c5 + I5yy*s3*ss4*ss5*c3 - 2*I5yy*s3*ss5*c3 + I5yy*s3*c3 + I5yy*s5*c4*c5 + 2*I5zz*s23*s2*s3*ss4 - I5zz*s2*ss4*c2 - I5zz*s3*ss4*c3 + a2*(d4*m4*c23 + d4*m5*c23 + l3*m3*c23 + l4*m4*c23 + l5*m5*s23*c4*c5 + l5*m5*s5*c23)*c2 + d4*d4*(m4 + m5)*s23*c23 - 2*d4*l4*m4*s23*c23 + d4*l5*m5*( -ss23*c4*c5 - 2*s23*s5*c23 + cc23*c4*c5 ) - (l3*l3*m3 + l4*l4*m4)*s23*c23 + l5*l5*m5*(- ss23*s5*c4*c5 - s23*ss4*c23*cc5 - 2*s23*ss5*c23 + s23*c23 + s5*cc23*c4*c5))
			+dq1*dq4*(-2*I4xx*s23*cc4 + I4xx*s23 + 2*I4yy*s23*cc4 - I4yy*s23 + I4zz*s23 - 2*I5xx*s23*cc4*cc5 + I5xx*s23 - 2*I5xx*s5*c23*c4*c5 + 2*I5yy*s23*cc4*cc5 - 2*I5yy*s23*cc4 + I5yy*s23 + 2*I5yy*s5*c23*c4*c5 + 2*I5zz*s23*cc4 - I5zz*s23 + 2*d4*l5*m5*c23*c4*c5 + 2*l5*l5*m5*(s23*c4*c5 + s5*c23)*c4*c5)
			+dq1*dq5*((2*I5xx*s23*s5*c4*c5 + 2*I5xx*ss5*c23 - I5xx*c23 - 2*I5yy*s23*s5*c4*c5 - 2*I5yy*ss5*c23 + I5yy*c23 - I5zz*c23 - 2*d4*l5*m5*s5*c23 - 2*l5*l5*m5*s23*s5*c4*c5 - 2*l5*l5*m5*ss5*c23)*s4)
			+dq2*dq2*(a2*(d4*m4*c3 + d4*m5*c3 + l3*m3*c3 + l4*m4*c3 + l5*m5*s3*c4*c5 + l5*m5*s5*c3))
			+dq2*dq4*(2*I4xx*s4*c4 - 2*I4yy*s4*c4 + 2*I5xx*s4*c4*cc5 + 2*I5yy*s4*ss5*c4 - 2*I5zz*s4*c4 -2*l5*l5*m5*s4*c4*cc5)
			+dq2*dq5*(-2*I5xx*ss4*s5*c5 + 2*I5yy*ss4*s5*c5 + 2*d4*l5*m5*c5 + 2*l5*l5*m5*ss4*s5*c5)
			+dq3*dq4*(2*I4xx*s4*c4 - 2*I4yy*s4*c4 + 2*I5xx*s4*c4*cc5 + 2*I5yy*s4*ss5*c4 - 2*I5zz*s4*c4 - 2*l5*l5*m5*s4*c4*cc5)
			+dq3*dq5*(-2*I5xx*ss4*s5*c5 + 2*I5yy*ss4*s5*c5 + 2*d4*l5*m5*c5 + 2*l5*l5*m5*ss4*s5*c5)
			+dq4*dq4*(- I5xx*s5*c4*c5 + I5yy*s5*c4*c5 + d4*l5*m5*c4*c5 + l5*l5*m5*c4*s5*c5)
			+dq4*dq5*(I5xx*s4*ss5 - I5xx*s4*cc5 - I5yy*s4*ss5 + I5yy*s4*cc5 - I5zz*s4 - 2*d4*l5*m5*s4*s5 - 2*l5*l5*m5*s4*ss5)
			+dq5*dq5*(d4*l5*m5*c4*c5);

		V(3) = 
			 dq1*dq1*(I4xx*ss2*s4*c4 + 2*I4xx*s2*s3*s4*c23*c4 + I4xx*ss3*s4*c4 - I4yy*ss2*s4*c4 - 2*I4yy*s2*s3*s4*c23*c4 - I4yy*ss3*s4*c4 - 2*I5xx*s23*s2*s3*s4*s5*c5 - I5xx*ss2*s4*ss5*c4 + I5xx*ss2*s4*c4 - 2*I5xx*s2*s3*s4*ss5*c23*c4 + 2*I5xx*s2*s3*s4*c23*c4 + I5xx*s2*s4*s5*c2*c5 - I5xx*ss3*s4*ss5*c4 + I5xx*ss3*s4*c4 + I5xx*s3*s4*s5*c3*c5 + 2*I5yy*s23*s2*s3*s4*s5*c5 + I5yy*ss2*s4*ss5*c4 + 2*I5yy*s2*s3*s4*ss5*c23*c4 - I5yy*s2*s4*s5*c2*c5 + I5yy*ss3*s4*ss5*c4 - I5yy*s3*s4*s5*c3*c5 - I5zz*ss2*s4*c4 - 2*I5zz*s2*s3*s4*c23*c4 - I5zz*ss3*s4*c4 + a2*l5*m5*s4*c23*c2*c5 - d4*l5*m5*s23*s4*c23*c5 - l5*l5*m5*(s23*c4*c5 + s5*c23)*s23*s4*c5)
			+dq1*dq2*(2*I4xx*s23*cc4 - I4xx*s23 - 2*I4yy*s23*cc4 + I4yy*s23 - I4zz*s23 + 2*I5xx*s23*cc4*cc5 - I5xx*s23 + 2*I5xx*s5*c23*c4*c5 - 2*I5yy*s23*cc4*cc5 + 2*I5yy*s23*cc4 - I5yy*s23 - 2*I5yy*s5*c23*c4*c5 - 2*I5zz*s23*cc4 + I5zz*s23 -2*l5*m5*(a2*s2 + d4*c23 + l5*s23*c4*c5 + l5*s5*c23)*c4*c5)
			+dq1*dq3*(2*I4xx*s23*cc4 - I4xx*s23 - 2*I4yy*s23*cc4 + I4yy*s23 - I4zz*s23 + 2*I5xx*s23*cc4*cc5 - I5xx*s23 + 2*I5xx*s5*c23*c4*c5 - 2*I5yy*s23*cc4*cc5 + 2*I5yy*s23*cc4 - I5yy*s23 - 2*I5yy*s5*c23*c4*c5 - 2*I5zz*s23*cc4 + I5zz*s23 -2*l5*m5*(d4*c23 + l5*s23*c4*c5 + l5*s5*c23)*c4*c5)
			+dq1*dq5*(2*I5xx*s23*c4*cc5 - I5xx*s23*c4 + 2*I5xx*s5*c23*c5 - 2*I5yy*s23*c4*cc5 + I5yy*s23*c4 - 2*I5yy*s5*c23*c5 - I5zz*s23*c4 -2*l5*l5*m5*(s23*c4*c5 + s5*c23)*c5)
			+dq2*dq2*(-I4xx*s4*c4 + I4yy*s4*c4 - I5xx*s4*c4*cc5 - I5yy*s4*ss5*c4 + I5zz*s4*c4 + a2*l5*m5*s4*c3*c5 + l5*l5*m5*s4*c4*cc5)
			+dq2*dq3*(-2*I4xx*s4*c4 + 2*I4yy*s4*c4 - 2*I5xx*s4*c4*cc5 - 2*I5yy*s4*ss5*c4 + 2*I5zz*s4*c4 + 2*l5*l5*m5*s4*c4*cc5)
			+dq2*dq5*(I5xx*s4*ss5 - I5xx*s4*cc5 - I5yy*s4*ss5 + I5yy*s4*cc5 + I5zz*s4 + 2*l5*l5*m5*s4*cc5)
			+dq3*dq3*(-I4xx*s4*c4 + I4yy*s4*c4 - I5xx*s4*c4*cc5 - I5yy*s4*ss5*c4 + I5zz*s4*c4 + l5*l5*m5*s4*c4*cc5)
			+dq3*dq5*(I5xx*s4*ss5 - I5xx*s4*cc5 - I5yy*s4*ss5 + I5yy*s4*cc5 + I5zz*s4 + 2*l5*l5*m5*s4*cc5)
			+dq4*dq5*( 2*I5xx*s5*c5 - 2*I5yy*s5*c5 - 2*l5*l5*m5*c5*s5);

		V(4) = 
			 dq1*dq1*(-4*I5xx*s23*s2*s3*ss5*c4 + 2*I5xx*s23*s2*s3*c4 - I5xx*ss2*ss4*s5*c5 + 2*I5xx*ss2*s5*c5 - 2*I5xx*s2*s3*ss4*s5*c23*c5 + 4*I5xx*s2*s3*s5*c23*c5 + 2*I5xx*s2*ss5*c2*c4 - I5xx*s2*c2*c4 - I5xx*ss3*ss4*s5*c5 + 2*I5xx*ss3*s5*c5 + 2*I5xx*s3*ss5*c3*c4 - I5xx*s3*c3*c4 - I5xx*s5*c5 + 4*I5yy*s23*s2*s3*ss5*c4 - 2*I5yy*s23*s2*s3*c4 + I5yy*ss2*ss4*s5*c5 - 2*I5yy*ss2*s5*c5 + 2*I5yy*s2*s3*ss4*s5*c23*c5 - 4*I5yy*s2*s3*s5*c23*c5 - 2*I5yy*s2*ss5*c2*c4 + I5yy*s2*c2*c4 + I5yy*ss3*ss4*s5*c5 - 2*I5yy*ss3*s5*c5 - 2*I5yy*s3*ss5*c3*c4 + I5yy*s3*c3*c4 + I5yy*s5*c5 + a2*l5*m5*(s23*c5 + s5*c23*c4)*c2 - d4*l5*m5*(s23*c5 + s5*c23*c4)*s23 - 2*l5*l5*m5*s23*ss5*c23*c4 + l5*l5*m5*s23*c23*c4 - l5*l5*m5*ss2*ss3*ss4*s5*c5 + 2*l5*l5*m5*ss2*ss3*s5*c5 + 2*l5*l5*m5*s2*s3*ss4*s5*c2*c3*c5 - 4*l5*l5*m5*s2*s3*s5*c2*c3*c5 - l5*l5*m5*ss4*s5*cc2*cc3*c5 + l5*l5*m5*ss4*s5*c5 + 2*l5*l5*m5*s5*cc2*cc3*c5 - l5*l5*m5*s5*c5)
			+dq1*dq2*((-2*I5xx*s23*s5*c4*c5 - 2*I5xx*ss5*c23 + I5xx*c23 + 2*I5yy*s23*s5*c4*c5 + 2*I5yy*ss5*c23 - I5yy*c23 + I5zz*c23 + 2*l5*m5*(a2*s2 + d4*c23 + l5*s23*c4*c5 + l5*s5*c23)*s5)*s4)
			+dq1*dq3*((-2*I5xx*s23*s5*c4*c5 - 2*I5xx*ss5*c23 + I5xx*c23 + 2*I5yy*s23*s5*c4*c5 + 2*I5yy*ss5*c23 - I5yy*c23 + I5zz*c23 + 2*l5*m5*(d4*c23 + l5*s23*c4*c5 + l5*s5*c23)*s5)*s4)
			+dq1*dq4*(-2*I5xx*s23*c4*cc5 + I5xx*s23*c4 - 2*I5xx*s5*c23*c5 + 2*I5yy*s23*c4*cc5 - I5yy*s23*c4 + 2*I5yy*s5*c23*c5 + I5zz*s23*c4 + 2*l5*l5*m5*(s23*c4*c5 + s5*c23)*c5)
			+dq2*dq2*(I5xx*ss4*s5*c5 - I5yy*ss4*s5*c5 + a2*l5*m5*s3*c5 + a2*l5*m5*s5*c3*c4 - d4*l5*m5*c5 - l5*l5*m5*ss4*s5*c5)
			+dq2*dq3*(2*I5xx*ss4*s5*c5 - 2*I5yy*ss4*s5*c5 - 2*d4*l5*m5*c5 - 2*l5*l5*m5*ss4*s5*c5)
			+dq2*dq4*(-I5xx*s4*ss5 + I5xx*s4*cc5 + I5yy*s4*ss5 - I5yy*s4*cc5 - I5zz*s4 -2*l5*l5*m5*s4*cc5)
			+dq3*dq3*(I5xx*ss4*s5*c5 - I5yy*ss4*s5*c5 - d4*l5*m5*c5 - l5*l5*m5*ss4*s5*c5)
			+dq3*dq4*(-I5xx*s4*ss5 + I5xx*s4*cc5 + I5yy*s4*ss5 - I5yy*s4*cc5 - I5zz*s4 -2*l5*l5*m5*s4*cc5)
			+dq4*dq4*(-I5xx*s5*c5 + I5yy*s5*c5 + l5*l5*m5*s5*c5);
		
		Fd(0) = fd[0]*qp(0);
		Fd(1) = fd[1]*qp(1);
		Fd(2) = fd[2]*qp(2);
		Fd(3) = fd[3]*qp(3);
		Fd(4) = fd[4]*qp(4);
		
		Fs(0) = (qp(0)>0.01)?fs[0]:( (qp(0)<-0.01)?-fs[0]:0 );
		Fs(1) = (qp(1)>0.01)?fs[1]:( (qp(1)<-0.01)?-fs[1]:0 );
		Fs(2) = (qp(2)>0.01)?fs[2]:( (qp(2)<-0.01)?-fs[2]:0 );
		Fs(3) = (qp(3)>0.01)?fs[3]:( (qp(3)<-0.01)?-fs[3]:0 );
		Fs(4) = (qp(4)>0.01)?fs[4]:( (qp(4)<-0.01)?-fs[4]:0 );
	#endif
}

inline void CalcPassoTrajetoria(){
	if(Ct.t < Ct.tf){
		Ct.t += T_AMOSTRAGEM;
		
		if(CtrlType == CtrlType_t::OnOff) Ct.t = Ct.tf;
		
		//   th = a0    +a4*t.^4    +a5*t.^5    +a6*t.^6     +a7*t.^7;
		//  dth =     +4*a4*t.^3  +5*a5*t.^4  +6*a6*t.^5   +7*a7*t.^6;
		// ddth =    +12*a4*t.^2 +20*a5*t.^3 +30*a6*t.^4  +42*a7*t.^5;

		double t2 = Ct.t*Ct.t;
		double t3 = t2*Ct.t;
		double t4 = t2*t2;
		double t5 = t4*Ct.t;
		double t6 = t3*t3;
		double t7 = t6*Ct.t;
		for(int i=0; i<5; ++i){
			qd(i)   = Ct.a0[i] +   t4*Ct.a4[i] +    t5*Ct.a5[i] +    t6*Ct.a6[i] +    t7*Ct.a7[i];
			qdp(i)  =            4*t3*Ct.a4[i] +  5*t4*Ct.a5[i] +  6*t5*Ct.a6[i] +  7*t6*Ct.a7[i];
			qdpp(i) =           12*t2*Ct.a4[i] + 20*t3*Ct.a5[i] + 30*t4*Ct.a6[i] + 42*t5*Ct.a7[i];
		}
		//106 mul, 50 sum, 6var
	}
	else if(EnMovment){
		if(CurrentMoveTimeOut < MoveTimeOut){
			CurrentMoveTimeOut += T_AMOSTRAGEM;
		}else{
			++PosIndex;
			if(PosIndex >= NPOS){
				PosIndex = 0;
				if(SingleMovment){
					if(SingleMovmentB) SingleMovmentB = false;
					else{
						SerialLog = false;
						SingleMovment = false;
						EnMovment = false;
						if(xSemaphoreTake(SemaphoreLogBuffer, 1)){
							TaskControllLogBuffer += "SingleMovment = 0;\n";
							xSemaphoreGive(SemaphoreLogBuffer);
						}
					}
				}
			}
			if(EnMovment){
				Ct.thf[0] = p[PosIndex](0); 
				Ct.thf[1] = p[PosIndex](1); 
				Ct.thf[2] = p[PosIndex](2); 
				Ct.thf[3] = p[PosIndex](3); 
				Ct.thf[4] = p[PosIndex](4);
				CalcTrajetoria();
				#ifdef PRINT_TRAJ
					if(xSemaphoreTake(SemaphoreLogBuffer, 1)){
						TaskControllLogBuffer += "thf a0 a4 a5 a6 a7;tf = ";
						TaskControllLogBuffer += Ct.tf;
						TaskControllLogBuffer += " s\n";
						for(int i=0; i<5; ++i)
							TaskControllLogBuffer +=
								String(Ct.thf[i]*180/pi)+' '+
								String(Ct.a0 [i]*180/pi)+' '+
								String(Ct.a4 [i], 10)+' '+
								String(Ct.a5 [i], 10)+' '+
								String(Ct.a6 [i], 10)+' '+
								String(Ct.a7 [i], 10)+'\n';
						xSemaphoreGive(SemaphoreLogBuffer);
					}
				#endif
			}
		}
	}
}

void FuncTaskControle( void * pvParameters ) {
	for (;;) {
		if(tmrData.countAmost>=tmrData.maxAmost){//verifica tempo 1 ms
			tmrData.countAmost = 0;              //zera a contagem de tempo
			
			//pega o semáforo das variáveis de controle
			xSemaphoreTake(SemaphoreControllVars, portMAX_DELAY);
			
			#ifdef MEASURE_TIME_CONTROLE
				t0 = esp_timer_get_time();
			#endif

			//filtro de q para permitir derivada
			// float qBruto[5];
			ConvertEncodersToRad(qBruto);
			for(int i=0; i<5; ++i)
				q(i) += T_AMOSTRAGEM*pf*( qBruto(i) - q(i) );// q(i) += T_AMOSTRAGEM*pf*( qBruto[i] - q(i) );

			qp = (q-qAnt)/T_AMOSTRAGEM;
			qAnt = q;
			// qpp = (qp-qpAnt)/T_AMOSTRAGEM;
			// qpAnt = qdp;
			e  = qd  - q ;
			ep = qdp - qp;
			//epslon = epslon +(e*T_AMOSTRAGEM);
			for(int i=0; i<5; ++i){	//limite e epslon
				epslon(i) = epslon(i) +(e(i)*T_AMOSTRAGEM);
				 //limita epslon
				if(CtrlType == CtrlType_t::ControleDeJuntaClassico){
					if(epslon(i)>epslonMax[i]) epslon(i) = epslonMax[i]; 
					else if(epslon(i)<(-epslonMax[i])) epslon(i) = -epslonMax[i];
				}else if(CtrlType == CtrlType_t::TorqueCalculado){
					if(epslon(i)>epslonMaxTorque[i]) epslon(i) = epslonMaxTorque[i]; 
					else if(epslon(i)<(-epslonMaxTorque[i])) epslon(i) = -epslonMaxTorque[i];	
				}
				//float lim = 0.2*TauMax/CtrlData[CtrlType].Ki[i];	//limita o torque gerado pelo inegrador em 20% do max
				//epslon(i) = constrain(epslon(i), -lim, lim);
			}
			
			for(int i=0; i<5; ++i)		//	u(i) = -Kd[i]*ep(i) -Kp[i]*e(i) -Ki[i]*epslon(i);
				u(i) =	-CtrlData[CtrlType].K*(
							+CtrlData[CtrlType].Kd[i]*ep(i)
							+CtrlData[CtrlType].Kp[i]*e(i)
							+CtrlData[CtrlType].Ki[i]*epslon(i));

			CalcMVG();	//Calcula os valores de M, V e G

			//executa a lei de controle selecionada na variável CtrlType
			//Torque computado
			if(CtrlType == CtrlType_t::TorqueCalculado){	//tau = M*(qdpp -u) + V + G;
				//CalcMVG();
				#if defined(USE_R2_J2_J3) //R2 Juntas 2 e 3
					tau(1) = M(1,1)*(qdpp(1) -u(1)) + M(1,2)*(qdpp(2) -u(2));
					tau(2) = M(1,2)*(qdpp(1) -u(1)) + M(2,2)*(qdpp(2) -u(2));
				#elif defined(USE_R2_J3_J5) //R2 Juntas 3 e 5
					tau(2) = M(2,2)*(qdpp(2) -u(2)) + M(2,4)*(qdpp(4) -u(4));
					tau(4) = M(2,4)*(qdpp(2) -u(2)) + M(4,4)*(qdpp(4) -u(4));
				#else //R5
					tau = M*(qdpp -u);
				#endif
				if(UseV) tau += V;
				if(UseG) tau += G;
				if(UseFd) tau += Fd;
				if(UseFs) tau += Fs;
			}
			else if(CtrlType == CtrlType_t::PIDplusG){
				//CalcMVG();
				tau = -u + G;
			}else if(CtrlType == CtrlType_t::ControleDeJuntaClassico){	//tau = -u;
				tau = -u;	//M=I, N = -qdpp => tau = M*(qdpp -u) + V + G = I*(qdpp -u) +N = qdpp -u -qdpp => tau = -u;
			}
			else if(CtrlType == CtrlType_t::PID){
				for(int i=0; i<5; ++i){
					if	(CtrlCompG == CtrlCompG_t::CompFadap2)
						Fadap(i) = beta*Fadap(i) + (float)T_AMOSTRAGEM*gama*e(i);	//dt*gama*e
					else
						Fadap(i) = beta*Fadap(i) + (float)T_AMOSTRAGEM*gama*e(i)*(u(i)>0?u(i):-u(i));	//dt*gama*e*abs(u(i))
					if		(Fadap(i) >  TauMax[i]) Fadap(i) =  TauMax[i];
					else if	(Fadap(i) < -TauMax[i]) Fadap(i) = -TauMax[i];
				}
				
				if		(CtrlCompG == CtrlCompG_t::SemG)		tau = -u;
				else if	(CtrlCompG == CtrlCompG_t::CompG)		tau = -u +G;
				else if (CtrlCompG == CtrlCompG_t::CompGCond)	{}
				else if (CtrlCompG == CtrlCompG_t::CompFd)		tau = -u +Fd;
				else if	(CtrlCompG == CtrlCompG_t::CompFadap)	tau = -u +Fadap;
				else if	(CtrlCompG == CtrlCompG_t::CompFadap2)	tau = -u +Fadap;
				else if (CtrlCompG == CtrlCompG_t::CompFdFadap)	tau = -u +Fd+Fadap;
			}
			
			if(CtrlType == CtrlType_t::OnOff){
				for(int i=0; i<5; ++i){
					if		(e(i) >  CtrlOnOffTol) {pwm[i] = PWM_MAX; sentido[i] = true; } 
					else if	(e(i) < -CtrlOnOffTol) {pwm[i] = PWM_MAX; sentido[i] = false;}
					else 				 			pwm[i] = 0;
				}
			}
			else if(CtrlType != CtrlType_t::Nenhum){
				//Frank Lewis(pg 152) - Actuator Dynamics
				float torque;//considera o torque nominal (TORQUE_N) pra pwm=100%
				for(int i=0; i<5; ++i){
					if(tau(i)<0){ torque = -tau(i);sentido[i] = false; }
					else		{ torque =  tau(i);sentido[i] = true; } 
					torque*=InvTauMax[i];	//multiplicação é mais rapida que uma divisão, por isso já deixo salva a inversa do torque max
					if(torque > 1) torque = 1;	//limita entre 0 e 1
					if(EnDeadZone){
						pwm[i] = torque*(PWM_MAX-DeadZone[i]);
						if(pwm[i] != 0) pwm[i] += DeadZone[i];
					}else pwm[i] = torque*PWM_MAX;
				}
			}
			
			//para usar ledc ver https://randomnerdtutorials.com/esp32-pwm-arduino-ide/
			//https://randomnerdtutorials.com/esp32-dc-motor-l298n-motor-driver-control-speed-direction/
			#if defined(USE_R2_J2_J3)
			ledcWrite(M2_esquerda, (mEnable[1] &  sentido[1])?pwm[1]:0);
			ledcWrite(M2_direita,  (mEnable[1] & !sentido[1])?pwm[1]:0);
			ledcWrite(M3_esquerda, (mEnable[2] &  sentido[2])?pwm[2]:0);
			ledcWrite(M3_direita,  (mEnable[2] & !sentido[2])?pwm[2]:0);
			#elif defined(USE_R2_J3_J5)
			ledcWrite(M3_esquerda, (mEnable[2] &  sentido[2])?pwm[2]:0);
			ledcWrite(M3_direita,  (mEnable[2] & !sentido[2])?pwm[2]:0);
			ledcWrite(M5_esquerda, (mEnable[4] &  sentido[4])?pwm[4]:0);
			ledcWrite(M5_direita,  (mEnable[4] & !sentido[4])?pwm[4]:0);
			#else
			ledcWrite(M1_esquerda, (mEnable[0] &  sentido[0])?pwm[0]:0);
			ledcWrite(M1_direita,  (mEnable[0] & !sentido[0])?pwm[0]:0);
			ledcWrite(M2_esquerda, (mEnable[1] &  sentido[1])?pwm[1]:0);
			ledcWrite(M2_direita,  (mEnable[1] & !sentido[1])?pwm[1]:0);
			ledcWrite(M3_esquerda, (mEnable[2] &  sentido[2])?pwm[2]:0);
			ledcWrite(M3_direita,  (mEnable[2] & !sentido[2])?pwm[2]:0);
			ledcWrite(M4_esquerda, (mEnable[3] &  sentido[3])?pwm[3]:0);
			ledcWrite(M4_direita,  (mEnable[3] & !sentido[3])?pwm[3]:0);
			ledcWrite(M5_esquerda, (mEnable[4] &  sentido[4])?pwm[4]:0);
			ledcWrite(M5_direita,  (mEnable[4] & !sentido[4])?pwm[4]:0);
			#endif
			
			CalcPassoTrajetoria();
		
			#ifdef MEASURE_TIME_CONTROLE
				t1 = esp_timer_get_time();
				sum_dt += t1-t0;
				++countControle;
			#endif

			#ifdef LOG_MAX
				for(int i=0; i<5; ++i){
					if		(e(i)   >   eLogMax(i))   eLogMax(i) =   e(i);
					else if	(e(i)   <   eLogMin(i))   eLogMin(i) =   e(i);
					if		(qp(i)  >  qpLogMax(i))  qpLogMax(i) =  qp(i);
					else if	(qp(i)  <  qpLogMin(i))  qpLogMin(i) =  qp(i);
					if		(Fadap(i)> FaLogMax(i))  FaLogMax(i) = Fadap(i);
					else if	(Fadap(i)< FaLogMin(i))  FaLogMin(i) = Fadap(i);
					if(sentido[i]){
						if(pwm[i] > pwmLogMax(i))pwmLogMax(i) = pwm[i];
					}else{
						if(pwm[i] > pwmLogMin(i))pwmLogMin(i) = pwm[i];
					}
				}
			#endif
			
			xSemaphoreGive(SemaphoreControllVars);  // Release the semaphore
			if (tmrData.countPrint>=tmrData.maxPrint){
				tmrData.countPrint = 0;
				xSemaphoreGive(SemaphorePrint);  // Release the semaphore
			}
		}
		vTaskDelay(1);
	}
}

//Variaveis a serem copiadas e printadas na serial
struct PrintEn_t{
	bool Encoders	= true;
	bool qBruto		= true;
	bool q			= true;
	bool qp			= true;
	bool qd			= true;
	bool qdp		= false;
	bool qdpp		= false;
	bool e			= true;
	bool ep			= false;
	bool ei			= false;
	bool u			= true;
	bool tau		= false;
	bool V			= false;
	bool G			= false;
	bool Fadap		= true;
	bool pwm		= true;
	// bool t;
}PrintEn;
struct PrintVars{
	int32_t Encoders[5];
	float qBruto[5];
	float q[5];
	float qp[5];
	float qd[5];
	float qdp[5];
	float qdpp[5];
	float e[5];
	float ep[5];
	float epslon[5];
	float u[5];
	float tau[5];
	float V[5];
	float G[5];
	float Fadap[5];
	int pwm[5];
	bool sentido[5];
	
	double t;
};
void FuncTaskPrint( void * pvParameters ) {
	//copy vars
	struct PrintVars printVars;
	for (;;) {
		if(xSemaphoreTake(SemaphoreLogBuffer, 1)){
			String buffer = TaskControllLogBuffer;
			TaskControllLogBuffer = "";
			xSemaphoreGive(SemaphoreLogBuffer);
			if(!buffer.isEmpty()) Serial.println(buffer);
		}
		
		if(SerialLog){
			if( xSemaphoreTake(SemaphorePrint, (1*portTICK_PERIOD_MS)) ) {
				if ( xSemaphoreTake(SemaphoreControllVars, (200*portTICK_PERIOD_MS)) ) {  // try to acquire the semaphore
										
					#if defined(USE_R2_J2_J3)
					for(uint8_t i=1; i<3; ++i)
					#elif defined(USE_R2_J3_J5)
					for(uint8_t i=2; i<5; i+=2)
					#else
					for(uint8_t i=0; i<5; ++i)
					#endif
					{
						printVars.Encoders[i] = Encoders[i];
						printVars.qBruto[i] = qBruto(i);
						
						printVars.q		[i] = q		(i);
						printVars.qp	[i] = qp	(i);
						printVars.qd	[i] = qd	(i);
						printVars.qdp	[i] = qdp	(i);
						printVars.qdpp	[i] = qdpp	(i);
						printVars.e		[i] = e		(i);
						printVars.ep	[i] = ep	(i);
						printVars.epslon[i] = epslon(i);
						printVars.u		[i] = u		(i);
						printVars.tau	[i] = tau	(i);
						printVars.V		[i] = V		(i);
						printVars.G		[i] = G		(i);
						printVars.Fadap	[i] = Fadap	(i);
						printVars.pwm	[i] = pwm	[i];
						printVars.sentido[i] = sentido[i];
					}
					printVars.t = Ct.t;
					
					#ifdef MEASURE_TIME_CONTROLE
						uint64_t p_sum_dt = sum_dt;
						uint32_t p_countControle = countControle;
						sum_dt = 0;
						countControle = 0;
					#endif
					
					xSemaphoreGive(SemaphoreControllVars);  // Release the semaphore
					//Serial.println(count);if(SerialLog){

					#if defined(USE_R2_J2_J3)
					for(uint8_t i=1; i<3; ++i)
					#elif defined(USE_R2_J3_J5)
					for(uint8_t i=2; i<5; i+=2)
					#else
					for(uint8_t i=0; i<5; ++i)
					#endif
					{
						if(JlogEn[i]){	//usar double para impedir o uso da FPU e deixa-la livra para a task de controle
							#ifdef PLOT_CSV
								if(PrintEn.Encoders	){Serial.print(printVars.Encoders[i]);		Serial.print(",");}
								if(PrintEn.qBruto	){Serial.print(printVars.qBruto	[i]*180/pi);Serial.print(",");}
								if(PrintEn.q		){Serial.print(printVars.q   	[i]*180/pi);Serial.print(",");}
								if(PrintEn.qp		){Serial.print(printVars.qp  	[i]*180/pi);Serial.print(",");}
								if(PrintEn.qd		){Serial.print(printVars.qd  	[i]*180/pi);Serial.print(",");}
								if(PrintEn.qdp		){Serial.print(printVars.qdp 	[i]*180/pi);Serial.print(",");}
								if(PrintEn.qdpp		){Serial.print(printVars.qdpp	[i]*180/pi);Serial.print(",");}
								if(PrintEn.e		){Serial.print(printVars.e  	[i]*180/pi);Serial.print(",");}
								if(PrintEn.ep		){Serial.print(printVars.ep 	[i]*180/pi);Serial.print(",");}
								if(PrintEn.ei		){Serial.print(printVars.epslon	[i]*180/pi);Serial.print(",");}
								if(PrintEn.u		){Serial.print(printVars.u  	[i], 5);	Serial.print(",");}
								if(PrintEn.tau		){Serial.print(printVars.tau	[i], 5);	Serial.print(",");}
								if(PrintEn.V		){Serial.print(printVars.V  	[i], 5);	Serial.print(",");}
								if(PrintEn.G		){Serial.print(printVars.G  	[i], 5);	Serial.print(",");}
								if(PrintEn.Fadap	){Serial.print(printVars.Fadap	[i], 5);	Serial.print(",");}
								if(PrintEn.pwm		){if(!printVars.sentido[i])Serial.print('-'); Serial.print(printVars.pwm[i]);Serial.print(",");}
								Serial.print("  ");
							#else
								if(PrintEn.Encoders	){Serial.print(" Encoders");Serial.print(i+1);Serial.print(": ");Serial.print(printVars.Encoders[i]);}
								if(PrintEn.qBruto	){Serial.print(" qBruto"  );Serial.print(i+1);Serial.print(": ");Serial.print(printVars.qBruto   [i]*180/pi);}
								if(PrintEn.q		){Serial.print(" q"       );Serial.print(i+1);Serial.print(": ");Serial.print(printVars.q   [i]*180/pi);}
								if(PrintEn.qp		){Serial.print(" qp"      );Serial.print(i+1);Serial.print(": ");Serial.print(printVars.qp  [i]*180/pi);}
								if(PrintEn.qd		){Serial.print(" qd"      );Serial.print(i+1);Serial.print(": ");Serial.print(printVars.qd  [i]*180/pi);}
								if(PrintEn.qdp		){Serial.print(" qdp"     );Serial.print(i+1);Serial.print(": ");Serial.print(printVars.qdp [i]*180/pi);}
								if(PrintEn.qdpp		){Serial.print(" qdpp"    );Serial.print(i+1);Serial.print(": ");Serial.print(printVars.qdpp[i]*180/pi);}
								if(PrintEn.e		){Serial.print(" e"       );Serial.print(i+1);Serial.print(": ");Serial.print(printVars.e  [i]*180/pi);}
								if(PrintEn.ep		){Serial.print(" ep"      );Serial.print(i+1);Serial.print(": ");Serial.print(printVars.ep [i]*180/pi);}
								if(PrintEn.ei		){Serial.print(" ei"      );Serial.print(i+1);Serial.print(": ");Serial.print(printVars.epslon[i]*180/pi);}
								if(PrintEn.u		){Serial.print(" u"       );Serial.print(i+1);Serial.print(": ");Serial.print(printVars.u  [i], 5);}
								if(PrintEn.tau		){Serial.print(" tau"     );Serial.print(i+1);Serial.print(": ");Serial.print(printVars.tau[i], 5);}
								if(PrintEn.V		){Serial.print(" V"       );Serial.print(i+1);Serial.print(": ");Serial.print(printVars.V  [i], 5);}
								if(PrintEn.G		){Serial.print(" G"       );Serial.print(i+1);Serial.print(": ");Serial.print(printVars.G  [i], 5);}
								if(PrintEn.Fadap	){Serial.print(" Fadap"   );Serial.print(i+1);Serial.print(": ");Serial.print(printVars.Fadap[i], 5);}
								if(PrintEn.pwm		){Serial.print(" pwm"     );Serial.print(i+1);Serial.print(": ");
									if(!printVars.sentido[i])Serial.print('-'); Serial.print(printVars.pwm[i]);}
								Serial.print("  ");
							#endif
						}
					}
					#ifdef PLOT_CSV
						Serial.print(1e3*printVars.t);
						#ifdef MEASURE_TIME_CONTROLE
							Serial.print(",");Serial.print(p_countControle);
							Serial.print(",");Serial.print((float)p_sum_dt/p_countControle);
						#endif
					#else 
						Serial.print(" t: ");Serial.print(1e3*printVars.t);
						#ifdef MEASURE_TIME_CONTROLE
							Serial.print(" cnt: ");Serial.print(p_countControle);
							Serial.print(" dt: ");Serial.print((float)p_sum_dt/p_countControle);
						#endif
					#endif
					
					Serial.println("");
				}
			}
		}
		vTaskDelay(1);	//vTaskDelay(1*portTICK_PERIOD_MS);
		//taskYIELD();	//https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/system/freertos_idf.html?highlight=taskyield#c.taskYIELD
	}
}

bool bitDebug = false;
void FuncTaskCom( void * pvParameters ) {
	for (;;) {
		if(Serial.available()){
			int inChar = Serial.read();
			if(inChar == '\t') inChar = ' ';
			
			if(inChar == '\n' || inChar == '\r'){
				if(SerialBuffer.length() > 0){	//só processa se tiver dados
					#ifdef VERBOSE_CMDS
						Serial.print("  s: '");Serial.print(SerialBuffer);Serial.println("'");
					#else
						Serial.println("");
					#endif
					SplitCmds();//ProcessSerialString();
					SerialBuffer = "";
				}
			}else
				SerialBuffer += (char)inChar;
		}
		else vTaskDelay(100 / portTICK_PERIOD_MS);
	}
}

void setup() {
	Serial.begin(BAUDRATE);	// velocidade da serial
	while(!Serial);
	
	initPosList();
	initCtrlData();

	// pinos de entrada digital dos encoders 
	pinMode(ENC1_A, INPUT);
	pinMode(ENC1_B, INPUT);
	pinMode(ENC2_A, INPUT);
	pinMode(ENC2_B, INPUT);
	pinMode(ENC3_A, INPUT);
	pinMode(ENC3_B, INPUT);
	pinMode(ENC4_A, INPUT);
	pinMode(ENC4_B, INPUT);
	pinMode(ENC5_A, INPUT);
	pinMode(ENC5_B, INPUT);
	 
	// pinos de saida PWM para os motores
	pinMode(M1_esquerda, OUTPUT);
	pinMode(M1_direita , OUTPUT);
	pinMode(M2_esquerda, OUTPUT);
	pinMode(M2_direita , OUTPUT);
	pinMode(M3_esquerda, OUTPUT);
	pinMode(M3_direita , OUTPUT);
	pinMode(M4_esquerda, OUTPUT);
	pinMode(M4_direita , OUTPUT);
	pinMode(M5_esquerda, OUTPUT);
	pinMode(M5_direita , OUTPUT);

	// configure LEDC PWM
	ledcAttachChannel(M1_direita , PWM_FREQUENCY, PWM_RESOLUTION, 0);
	ledcAttachChannel(M1_esquerda, PWM_FREQUENCY, PWM_RESOLUTION, 1);
	ledcAttachChannel(M2_direita , PWM_FREQUENCY, PWM_RESOLUTION, 2);
	ledcAttachChannel(M2_esquerda, PWM_FREQUENCY, PWM_RESOLUTION, 3);
	ledcAttachChannel(M3_direita , PWM_FREQUENCY, PWM_RESOLUTION, 4);
	ledcAttachChannel(M3_esquerda, PWM_FREQUENCY, PWM_RESOLUTION, 5);
	ledcAttachChannel(M4_direita , PWM_FREQUENCY, PWM_RESOLUTION, 6);
	ledcAttachChannel(M4_esquerda, PWM_FREQUENCY, PWM_RESOLUTION, 7);
	ledcAttachChannel(M5_direita , PWM_FREQUENCY, PWM_RESOLUTION, 8);
	ledcAttachChannel(M5_esquerda, PWM_FREQUENCY, PWM_RESOLUTION, 9);
	
	#if defined(USE_R2_J2_J3)
	ledcWrite(M1_esquerda, 0);
	ledcWrite(M1_direita , 0);
	ledcWrite(M4_esquerda, 0);
	ledcWrite(M4_direita , 0);
	ledcWrite(M5_esquerda, 0);
	ledcWrite(M5_direita , 0);
	#elif defined(USE_R2_J3_J5)
	ledcWrite(M1_esquerda, 0);
	ledcWrite(M1_direita , 0);
	ledcWrite(M2_esquerda, 0);
	ledcWrite(M2_direita , 0);
	ledcWrite(M4_esquerda, 0);
	ledcWrite(M4_direita , 0);
	#endif
	
	//CONFIGURA AS INTERRUPCOES EXTERNAS PARA BORDA DE SUBIDA DO CANAL DO ENCODER
	attachInterrupt (ENC1_A, read_encoder1, RISING);
	attachInterrupt (ENC2_A, read_encoder2, RISING);
	attachInterrupt (ENC3_A, read_encoder3, RISING);
	attachInterrupt (ENC4_A, read_encoder4, RISING);
	attachInterrupt (ENC5_A, read_encoder5, RISING);
	// attachInterrupt (ENC6_A, read_encoder6, RISING);   


	#ifdef	LED_PLACA
		pinMode(LED_PLACA, OUTPUT);
		digitalWrite(LED_PLACA, CtrlType != CtrlType_t::Nenhum? HIGH : LOW);
	#endif

	SerialBuffer = "";
	//inicia na posição reto para cima
	ConvertRadtoEncoders(0, 90*pi/180.0, -90*pi/180.0, 0, 90*pi/180.0);
	q  << 0, 90*pi/180.0, -90*pi/180.0, 0, 90*pi/180.0;
	qd << 0, 90*pi/180.0, -90*pi/180.0, 0, 90*pi/180.0;
	epslon << 0, 0, 0, 0, 0;
	
	SemaphoreControllVars 	= xSemaphoreCreateBinary();  // Set the semaphore as binary
	SemaphoreControll		= xSemaphoreCreateBinary();
	SemaphorePrint 			= xSemaphoreCreateBinary();
	SemaphoreLogBuffer		= xSemaphoreCreateBinary();
	
	if( SemaphoreControllVars == NULL ){
		Serial.println("Semafore SemaphoreControllVars creation error!");
		return;
	}else if( SemaphoreControll == NULL ){
		Serial.println("Semafore SemaphoreControll creation error!");
		return;
	}else if( SemaphorePrint == NULL ){
		Serial.println("Semafore SemaphorePrint creation error!");
		return;
	}else if( SemaphoreLogBuffer == NULL ){
		Serial.println("Semafore SemaphoreLogBuffer creation error!");
		return;
	}else{
		Serial.println("Semafore creation OK!");
	}
	
	//vTaskStartScheduler();
	xSemaphoreGive(SemaphoreLogBuffer);
	xSemaphoreGive(SemaphoreControllVars);  // Release the semaphore
	Serial.println("semafore relased");
	
	////configurando o timer para interrupção
	//timer = timerBegin(0, 80, true); // timerBegin(n do timer usado (0 a 3), prescaler, sentido da contagem)
	//// a ESP tem clock 80 Mhz, utilizando 80 no prescaler, o clock do contador será de 1MHz (incrementa a cada 1 us)
	//timerAttachInterrupt(timer, &cb_timer, true); // chama a função da interrupção sempre que a interrupção disparar
	//timerAlarmWrite(timer, 500, true);  // define o tempo de amostragem. 
	//timerAlarmEnable(timer);  // habilita o timer
	//Atualização da API do timer	
	//	https://github.com/espressif/arduino-esp32/releases
	//	https://docs.espressif.com/projects/arduino-esp32/en/latest/migration_guides/2.x_to_3.0.html
	//	https://docs.espressif.com/projects/arduino-esp32/en/latest/api/timer.html
	//timer = timerBegin(1000000);  //seta frequencia de 1 MHz
	timer = timerBegin(10000000);  //seta frequencia de 10 MHz
	timerAttachInterrupt(timer, &cb_timer);
	timerAlarm(timer, 500, true, 0);  // define o tempo de amostragem. 
	
	
	//Using:
	//	Events run on: "Core 1"
	//	Arduino runs on: "Core 1"

	//TaskControle
	xTaskCreatePinnedToCore(	//create a task that will be executed in the FuncTaskControle() function, with priority 10 and executed on core 1
		FuncTaskControle,	/* Task function. */
		"TaskControle",		/* name of task. */
		10240,				/* Stack size of task */
		NULL,				/* parameter of the task */
		10,					/* priority of the task */
		&TaskControle,		/* Task handle to keep track of created task */
		1);					/* pin task to core 0 */
	if(pdTRUE == pdTRUE) Serial.println("TaskControle OK");
	else Serial.println("TaskControle Error");
	
	//TaskCom
	xTaskCreatePinnedToCore(	//create a task that will be executed in the FuncTaskCom() function, with priority 0 and executed on core 0
		FuncTaskCom,		/* Task function. */
		"TaskCom",			/* name of task. */
		2048,				/* Stack size of task */
		NULL,				/* parameter of the task */
		1,					/* priority of the task */
		&TaskCom,			/* Task handle to keep track of created task */
		0);					/* pin task to core 1 */
	if(pdTRUE == pdTRUE) Serial.println("TaskCom OK");
	else Serial.println("TaskCom Error");

	//TaskPrint
	xTaskCreatePinnedToCore(	//create a task that will be executed in the FuncTaskPrint() function, with priority 0 and executed on core 0
		FuncTaskPrint,		/* Task function. */
		"TaskPrint",		/* name of task. */
		2048,				/* Stack size of task */
		NULL,				/* parameter of the task */
		1,					/* priority of the task */
		&TaskPrint,			/* Task handle to keep track of created task */
		0);					/* pin task to core 1 */
	if(pdTRUE == pdTRUE) Serial.println("TaskPrint OK");
	else Serial.println("TaskPrint Error");

	//max used Stack of task
	//https://freertos.org/uxTaskGetStackHighWaterMark.html
}
void loop(){vTaskSuspend(NULL);}

// FUNCAO DE CONTROLE TEMPO
void cb_timer() {
	++tmrData.countAmost;
	++tmrData.countPrint;
}
//FUNCOES DE LEITURA DOS ENCODERS
void read_encoder1 () {
	if(digitalRead(ENC1_B) != 0)++Encoders[0];
	else						--Encoders[0];
}
void read_encoder2 () {
	if(digitalRead(ENC2_B) != 0)++Encoders[1];
	else						--Encoders[1];
}
void read_encoder3 () {
	if(digitalRead(ENC3_B) != 0)++Encoders[2];
	else						--Encoders[2];
}
void read_encoder4 () {
	if(digitalRead(ENC4_B) != 0)++Encoders[3];
	else						--Encoders[3];
}
void read_encoder5 () {
	if(digitalRead(ENC5_B) != 0)++Encoders[4];
	else						--Encoders[4];
}

//https://arduino.stackexchange.com/questions/1013/how-do-i-split-an-incoming-string
//https://www.delftstack.com/howto/arduino/arduino-split-string/
//https://www.forward.com.au/pfod/ArduinoProgramming/SafeString/index.html
//https://www.forward.com.au/pfod/ArduinoProgramming/ArduinoStrings/index.html
//Separa SerialBuffer em string separadas por ';' e processa cada uma
void SplitCmds(){
	#ifdef VERBOSE_SPLIT_CMDS
		uint64_t t0, t1;
		t0 = esp_timer_get_time();//Time();
	#endif
	String buffer = SerialBuffer, cmd="                                                  ";
	SerialBuffer = "";
	
	int lastSplitIndex = 0;
	int size = buffer.length();
	int splitIndex;
	do{
		splitIndex = buffer.indexOf('&', lastSplitIndex);
		if(splitIndex != -1){
			#ifdef VERBOSE_SPLIT_CMDS
				Serial.print(lastSplitIndex); Serial.print(" > "); Serial.print(splitIndex); Serial.print(" => ");
			#endif
			cmd = buffer.substring(lastSplitIndex,splitIndex);	//sem o ';'
			ProcessSerialString(cmd);//ProcessCmd(cmd);
			lastSplitIndex = splitIndex+1;
		}else{
			#ifdef VERBOSE_SPLIT_CMDS
				Serial.print(lastSplitIndex); Serial.print(" > "); Serial.print(splitIndex); Serial.print(" => ");
			#endif
			cmd = buffer.substring(lastSplitIndex);
			ProcessSerialString(cmd);//ProcessCmd(cmd);
		}
	}while(splitIndex != -1);
	#ifdef VERBOSE_SPLIT_CMDS
		t1 = esp_timer_get_time();//Time();
		Serial.print("t_prcs_str: ");Serial.print(t1-t0);Serial.println(" us");
	#endif
}

void ProcessCmd(String &buffer){
	Serial.println(buffer);
	buffer.trim();
	int spaceIndex = buffer.indexOf(' ');
	String cmd, arg1 = "";
	cmd	= (spaceIndex == -1)? buffer : buffer.substring(0,spaceIndex);
	
	//args = buffer.substring(spaceIndex+1).trim();
	Serial.print("cmd='");Serial.print(cmd);Serial.println("'");//Serial.print("' arg1='");Serial.print(arg1);
	Serial.println("");
}

void read5floats(String str, float val[]){
	int index;
	for(int i=0; i<4; ++i){ 
		index = str.indexOf(';');
		val[i] = str.substring(0,index).toFloat();
		str = str.substring(index+1);
	}
	val[4] = str.toFloat();
}

void ProcessSerialString(String SerialBuffer){
	if(SerialBuffer.startsWith("clear")){  //limpa o buffer de comandos 
	}
	else if(SerialBuffer.startsWith("log ")){
		String param = SerialBuffer.substring(4);
		if		(param.startsWith("start")){ SerialLog = true; } //começa a enviar valores das juntas 
		else if	(param.startsWith("stop" )){ SerialLog = false; } //para de enviar valores das juntas
		else if	(param.startsWith("all"  )){ JlogEn[0] = 1; JlogEn[1] = 1; JlogEn[2] = 1; JlogEn[3] = 1; JlogEn[4] = 1; }
		else if	(param.startsWith("none" )){ JlogEn[0] = 0; JlogEn[1] = 0; JlogEn[2] = 0; JlogEn[3] = 0; JlogEn[4] = 0; }
		else if (param.startsWith("ang"  )){
			xSemaphoreTake(SemaphoreControllVars, portMAX_DELAY);
			Vector<float, DIM> qPrint = q;
			xSemaphoreGive(SemaphoreControllVars);  // Release the semaphore
			#if defined(USE_R2_J2_J3) 
				float q1 = qPrint(1);
				float q2 = qPrint(2);
				Serial.print(" q1: "+String(qPrint(2)*180/pi)); Serial.print(" q2: "+String(qPrint(4)*180/pi));
				Serial.print("\n q1: "+String(q1*180/pi)); Serial.print(" q2: "+String(q2*180/pi));
			#elif defined(USE_R2_J3_J5)
				float q1 = qPrint(2)+pi;
				float q2 = qPrint(4)-(pi/2);
				Serial.print(" q1: "+String(qPrint(2)*180/pi)); Serial.print(" q2: "+String(qPrint(4)*180/pi));
				Serial.print("\n q1: "+String(q1*180/pi)); Serial.print(" q2: "+String(q2*180/pi));
			#else
				for(int i=0; i<5; ++i)Serial.print(" q"+String(i+1)+": "+String(qPrint(i)*180/pi)); //{Serial.print(" q");Serial.print(i+1);Serial.print(": ");Serial.print(qPrint(i)*180/pi);}
			#endif
			Serial.println();
		}
		else if (param.startsWith("G")){
			xSemaphoreTake(SemaphoreControllVars, portMAX_DELAY);
			Vector<float, DIM> qPrint = q;
			xSemaphoreGive(SemaphoreControllVars);  // Release the semaphore
			Vector<float, DIM>  Gprint		= Vector<float, DIM>::Zero();
			#if defined(USE_R2_J2_J3)
				float q1 = qPrint(2)+pi;
				float q2 = qPrint(4)-(pi/2);
				float c1 = cosf(q1), c12 = cosf((q1+q2));
				Gprint(2) = g*(l2*m2*c12 + l1*(m1+m2)*c1);
				Gprint(4) = g*(l2*m2*c12);
				Serial.print( "G1: "+String(Gprint(2)));
				Serial.print(" G2: "+String(Gprint(4)));
			#elif defined(USE_R2_J3_J5)
				float q1 = qPrint(2)+pi;
				float q2 = qPrint(4)-(pi/2);
				float c1 = cosf(q1), c12 = cosf((q1+q2));
				Gprint(2) = g*(l2*m2*c12 + l1*(m1+m2)*c1);
				Gprint(4) = g*(l2*m2*c12);
				Serial.print( "G1: "+String(Gprint(2)));
				Serial.print(" G2: "+String(Gprint(4)));
			#else
				float s2 = sinf(qPrint(1)), s4 = sinf(qPrint(3)), s5 = sinf(qPrint(4));
				float c2 = cosf(qPrint(1)), c4 = cosf(qPrint(3)), c5 = cosf(qPrint(4));
				float s23 = sinf((qPrint(1)+qPrint(2)));
				float c23 = cosf((qPrint(1)+qPrint(2)));
				Gprint(1) = g*( + a2*(m3 + m4 + m5)*c2 - d4*(m4 + m5)*s23 + l2*m2*c2 - l3*m3*s23 - l4*m4*s23 + l5*m5*(c23*c4*c5 - s23*s5));
				Gprint(2) = g*( - d4*(m4 + m5)*s23 - l3*m3*s23 - l4*m4*s23 + l5*m5*(c23*c4*c5 - s23*s5));
				Gprint(3) = g*( - l5*m5*s23*s4*c5);
				Gprint(4) = g*( + l5*m5*(c23*c5 - s23*s5*c4));
				for(int i=0; i<5; ++i)Serial.print(" G"+String(i+1)+": "+String(Gprint(i))); //{Serial.print(" q");Serial.print(i+1);Serial.print(": ");Serial.print(qPrint(i)*180/pi);}
			#endif
			Serial.println();
		}
		else if (param.startsWith("dim"  )){
			#if defined(USE_R2_J2_J3) || defined(USE_R2_J3_J5)
			Serial.println("m1="+String(1e3*m1)+" \tm2="+String(1e3*m2)+" g");
			Serial.println("l1="+String(1e3*l1)+" \tl2="+String(1e3*l2)+" mm");
			Serial.println("d1="+String(1e3*d1)+" \td2="+String(1e3*d2)+" mm");
			Serial.println("I1zz="+String(1e3*I1zz,5)+" \tI2zz="+String(1e3*I2zz,5)+" g*m^2");
			#else
				Serial.println("TODO");
			#endif
		}	
		
		else if (param.endsWith("pEn")){
			Serial.println  ("Encoders: "+String(PrintEn.Encoders));
			Serial.println  ("  qBruto: "+String(PrintEn.qBruto	));
			Serial.println  ("       q: "+String(PrintEn.q		));
			Serial.println  ("      qp: "+String(PrintEn.qp		));
			Serial.println  ("      qd: "+String(PrintEn.qd		));
			Serial.println  ("     qdp: "+String(PrintEn.qdp	));
			Serial.println  ("    qdpp: "+String(PrintEn.qdpp	));
			Serial.println  ("       e: "+String(PrintEn.e		));
			Serial.println  ("      ep: "+String(PrintEn.ep		));
			Serial.println  ("      ei: "+String(PrintEn.ei		));
			Serial.println  ("       u: "+String(PrintEn.u		));
			Serial.println  ("     tau: "+String(PrintEn.tau	));
			Serial.println  ("       V: "+String(PrintEn.V		));
			Serial.println  ("       G: "+String(PrintEn.G		));
			Serial.println  ("   Fadap: "+String(PrintEn.Fadap	));
			Serial.println  ("     pwm: "+String(PrintEn.pwm	));
		}
		else if (param.startsWith("pEn"  )){
			bool val = param.endsWith(":1");
			int index = param.indexOf(':');
			param = param.substring(0, index); //testar
			Serial.println("param : '"+param+"' val: "+String(val));
			if		(param.endsWith(" Encoders"	)) PrintEn.Encoders = val;
			else if	(param.endsWith(" qBruto"	)) PrintEn.qBruto	= val;
			else if	(param.endsWith(" q"		)) PrintEn.q		= val;
			else if	(param.endsWith(" qp"		)) PrintEn.qp		= val;
			else if	(param.endsWith(" qd"		)) PrintEn.qd		= val;
			else if	(param.endsWith(" qdp"		)) PrintEn.qdp		= val;
			else if	(param.endsWith(" qdpp"		)) PrintEn.qdpp		= val;
			else if	(param.endsWith(" e"		)) PrintEn.e		= val;
			else if	(param.endsWith(" ep"		)) PrintEn.ep		= val;
			else if	(param.endsWith(" ei"		)) PrintEn.ei		= val;
			else if	(param.endsWith(" u"		)) PrintEn.u		= val;
			else if	(param.endsWith(" tau"		)) PrintEn.tau		= val;
			else if	(param.endsWith(" V"		)) PrintEn.V		= val;
			else if	(param.endsWith(" G"		)) PrintEn.G		= val;
			else if	(param.endsWith(" Fadap"	)) PrintEn.Fadap	= val;
			else if	(param.endsWith(" pwm"		)) PrintEn.pwm		= val;
			// bool t;
			else Serial.println("print param unknown: '"+param+"'");
		}
		
		else if (param.endsWith("vars")){
			#if defined(USE_R2_J2_J3)
			for(uint8_t i=1; i<3; ++i)
			#elif defined(USE_R2_J3_J5)
			for(uint8_t i=2; i<5; i+=2)
			#else
			for(uint8_t i=0; i<5; ++i)
			#endif
			{
				if(JlogEn[i]){
					if(PrintEn.Encoders	){Serial.print(" Encoders");Serial.print(i+1);Serial.print("; ");}
					if(PrintEn.qBruto	){Serial.print(" qBruto"  );Serial.print(i+1);Serial.print("; ");}
					if(PrintEn.q		){Serial.print(" q"       );Serial.print(i+1);Serial.print("; ");}
					if(PrintEn.qp		){Serial.print(" qp"      );Serial.print(i+1);Serial.print("; ");}
					if(PrintEn.qd		){Serial.print(" qd"      );Serial.print(i+1);Serial.print("; ");}
					if(PrintEn.qdp		){Serial.print(" qdp"     );Serial.print(i+1);Serial.print("; ");}
					if(PrintEn.qdpp		){Serial.print(" qdpp"    );Serial.print(i+1);Serial.print("; ");}
					if(PrintEn.e		){Serial.print(" e"       );Serial.print(i+1);Serial.print("; ");}
					if(PrintEn.ep		){Serial.print(" ep"      );Serial.print(i+1);Serial.print("; ");}
					if(PrintEn.ei		){Serial.print(" ei"      );Serial.print(i+1);Serial.print("; ");}
					if(PrintEn.u		){Serial.print(" u"       );Serial.print(i+1);Serial.print("; ");}
					if(PrintEn.tau		){Serial.print(" tau"     );Serial.print(i+1);Serial.print("; ");}
					if(PrintEn.V		){Serial.print(" V"       );Serial.print(i+1);Serial.print("; ");}
					if(PrintEn.G		){Serial.print(" G"       );Serial.print(i+1);Serial.print("; ");}
					if(PrintEn.Fadap	){Serial.print(" Fadap"   );Serial.print(i+1);Serial.print("; ");}
					if(PrintEn.pwm		){Serial.print(" pwm"     );Serial.print(i+1);Serial.print("; ");}
					Serial.print("  ");
				}
			}
			Serial.print(" t");
			#ifdef MEASURE_TIME_CONTROLE
				Serial.print("; cnt");
				Serial.print("; dt");
			#endif			
			Serial.println("");
		}
		
		else if(param.endsWith("max")){
			#ifdef LOG_MAX
				for(int i=0; i<5; ++i){
					//Serial.print("\t  e["+String(i+1)+"] " +String(  eLogMin(i)*180/pi)+" to "+String(  eLogMax(i)*180/pi)+" º");
					//Serial.print("\t qp["+String(i+1)+"] " +String( qpLogMin(i)*180/pi)+" to "+String( qpLogMax(i)*180/pi)+" º/s");
					//Serial.print("\t Fa["+String(i+1)+"] " +String( FaLogMin(i)       )+" to "+String( FaLogMax(i)       )+" N.m");
					//Serial.print("\tpwm["+String(i+1)+"] -"+String(pwmLogMin(i)       )+" to "+String(pwmLogMax(i)       )+"\n");
					
					Serial.print(String(  eLogMin(i)*180/pi)+" <   e["+String(i+1)+"] < "+String(  eLogMax(i)*180/pi)+" º\t");
					Serial.print(String( qpLogMin(i)*180/pi)+" <  qp["+String(i+1)+"] < "+String( qpLogMax(i)*180/pi)+" º/s\t");
					Serial.print(String( FaLogMin(i)       )+" <  Fa["+String(i+1)+"] < "+String( FaLogMax(i)       )+" N.m\t");
					Serial.print(String(pwmLogMin(i)       )+" < pwm["+String(i+1)+"] < "+String(pwmLogMax(i)       )+"\n");
				}
			#else
				Serial.println("defina 'LOG_MAX' para habilitar a função");
			#endif
		}
		
		else{
			Serial.println("log '"+param+"' desconhecido");
			return;
		}
	}
	
	else if(SerialBuffer.startsWith("zEps")){ epslon << 0, 0, 0, 0, 0; }
	
	else if(SerialBuffer.startsWith("ctrl ")){
		String param = SerialBuffer.substring(5);
		if		(param.startsWith("stop"   )){ //para de enviar valores das juntas
			CtrlType = CtrlType_t::Nenhum;
			pwm[0] = 0;pwm[1] = 0;pwm[2] = 0;pwm[3] = 0;pwm[4] = 0;
			mEnable[0] = false;mEnable[1] = false;mEnable[2] = false;mEnable[3] = false;mEnable[4] = false;
		}
		else if	(param.startsWith("none"   )){
			CtrlType = CtrlType_t::Nenhum; 
			pwm[0] = 0;pwm[1] = 0;pwm[2] = 0;pwm[3] = 0;pwm[4] = 0;
		}
		else if	(param.startsWith("ControleDeJuntaClassico")){ CtrlType = CtrlType_t::ControleDeJuntaClassico; }
		else if	(param.startsWith("Torque" )){ CtrlType = CtrlType_t::TorqueCalculado; }
		else if	(param.startsWith("Grav"   )){ CtrlType = CtrlType_t::PIDplusG; }
		else if	(param.startsWith("OnOff"  )){ 
			CtrlType = CtrlType_t::OnOff;
			if	(param.startsWith("OnOff val:"  ))
				CtrlOnOffTol = param.substring(param.indexOf(':')+1).toFloat()*pi/180;
		}
		else if	(param.startsWith("PID"    )){
			CtrlType = CtrlType_t::PID;
			if		(param.endsWith(" G"))		CtrlCompG = CtrlCompG_t::CompG;
			else if	(param.endsWith(" Fd"))		CtrlCompG = CtrlCompG_t::CompFd;
			else if	(param.endsWith(" Gc"))		CtrlCompG = CtrlCompG_t::CompGCond;
			else if	(param.endsWith(" Fa"))		CtrlCompG = CtrlCompG_t::CompFadap;
			else if	(param.endsWith(" Fa2"))	CtrlCompG = CtrlCompG_t::CompFadap2;
			else if	(param.endsWith(" FdFa"))	CtrlCompG = CtrlCompG_t::CompFdFadap;
			else CtrlCompG = CtrlCompG_t::SemG;	//sempre vai para "tau = -u" se não selecionar nenhum valido
			Fadap << 0, 0, 0, 0, 0;
		}
		else if	(param.startsWith("mEn:0"  )){ mEnable[0] = false;mEnable[1] = false;mEnable[2] = false;mEnable[3] = false;mEnable[4] = false; }
		else if	(param.startsWith("mEn:1"  )){ mEnable[0] = true; mEnable[1] = true; mEnable[2] = true; mEnable[3] = true; mEnable[4] = true;  }
		else{
			Serial.println("ctrl '"+param+"' desconhecido");
			return;
		}
		epslon << 0, 0, 0, 0, 0;
	}
	
	else if(SerialBuffer.startsWith("gama:")){
		float aux = SerialBuffer.substring(SerialBuffer.indexOf(':')+1).toFloat();
		xSemaphoreTake(SemaphoreControllVars, portMAX_DELAY);
		gama = aux;
		Fadap = Vector<float, DIM>::Zero();
		xSemaphoreGive(SemaphoreControllVars);  // Release the semaphore
		Serial.println("gama = "+String(aux));
	}
	else if(SerialBuffer.startsWith("beta:")){
		float aux = SerialBuffer.substring(SerialBuffer.indexOf(':')+1).toFloat();
		xSemaphoreTake(SemaphoreControllVars, portMAX_DELAY);
		beta = aux;
		Fadap = Vector<float, DIM>::Zero();
		xSemaphoreGive(SemaphoreControllVars);  // Release the semaphore
		Serial.println("beta = "+String(aux));
	}
	
	else if(SerialBuffer.startsWith("K:")){
		CtrlData[CtrlType].K = SerialBuffer.substring(SerialBuffer.indexOf(':')+1).toFloat();
		Serial.print("(K="+String(CtrlData[CtrlType].K)+") ");
		if(CtrlType == CtrlType_t::TorqueCalculado){
			Serial.println("TorqueCalculado");
			Serial.println("UseV="+String(UseV)+" UseG="+String(UseG)+" UseFd="+String(UseFd)+" UseFs="+String(UseFs));
		}
		else if(CtrlType == CtrlType_t::PIDplusG) Serial.println("PD-Plus-Gravity");
		else if(CtrlType == CtrlType_t::ControleDeJuntaClassico) Serial.println("ControleDeJuntaClassico");
		else if(CtrlType == CtrlType_t::PID){
			Serial.print("PID multi uso ");
			if		(CtrlCompG == CtrlCompG_t::SemG) Serial.println("Sem G");
			else if	(CtrlCompG == CtrlCompG_t::CompG)Serial.println("Com G");
			else //if	(CtrlCompG == CtrlCompG_t::CompGCond){
				Serial.println("Com G condicional");
		}
		else if(CtrlType == CtrlType_t::OnOff)Serial.println("Controle_OnOff");
		else Serial.println("SemControle");
	}
	else if(SerialBuffer[0] > '0' && SerialBuffer[0] < '6'){
		uint8_t index = SerialBuffer[0] - '1';
		
		int paramIndex = SerialBuffer.indexOf(':');
		String cmd = SerialBuffer.substring(1, paramIndex);

		//Serial.print("cmd:");Serial.println(cmd);
		//Serial.print("index:");Serial.println(index);

		if 		(cmd == "log") JlogEn[index]  = SerialBuffer[paramIndex+1] == '1';
		else if	(cmd == "mEn") mEnable[index] = SerialBuffer[paramIndex+1] == '1';
		else{
			float val = SerialBuffer.substring(paramIndex+1).toFloat();
			if 		(cmd == "pwm")  {if(val < 0){pwm[index] = -val; sentido[index] = false;} else {pwm[index] =  val; sentido[index] = true; }}
			//else if (cmd == "j") 	{qd(index) = constrain(val*pi/180.0, qMax[index][0], qMax[index][1]); SerialLog=true;}
			//else if (cmd == "jr")	{qd(index) = constrain(val, qMax[index][0], qMax[index][1]); SerialLog=true;}
			else if (cmd == "kp")	CtrlData[CtrlType].Kp[index] = val;
			else if (cmd == "kd")	CtrlData[CtrlType].Kd[index] = val;
			else if (cmd == "ki")	CtrlData[CtrlType].Ki[index] = val;
			
			else if (cmd == "fd")	fd[index] = val;
			else if (cmd == "fs")	fs[index] = val;

			else if (cmd == "vM")   qpMax[index] = val*pi/180.0;
			else if (cmd == "zEps") epslon(index) = 0.0;
			
			else if (cmd == "dz")	DeadZone[index] = val;
			
			else if (cmd == "q" )   {
				xSemaphoreTake(SemaphoreControllVars, portMAX_DELAY);
				float aux[5];
				for(int i=0; i<5; ++i) aux[i] = q(i);
				aux[index] = val*pi/180.0;
				qd(index) = aux[index];
				ConvertRadtoEncoders(aux[0], aux[1], aux[2], aux[3], aux[4]);
				xSemaphoreGive(SemaphoreControllVars);  // Release the semaphore
			}
			
			#if defined(USE_R2_J2_J3) || defined(USE_R2_J3_J5)
			else if (cmd == "m" )   {
				if(index == 0)m1 = val;else m2 = val;
				Serial.println("m"+String(index+1)+" = "+String(val));
			}
			else if (cmd == "l" )   {
				if(index == 0)l1 = val;else l2 = val;
				Serial.println("l"+String(index+1)+" = "+String(val));
			}
			else if (cmd == "d" )   {
				if(index == 0)d1 = val;else d2 = val;
				Serial.println("d"+String(index+1)+" = "+String(val));
			}
			else if (cmd == "Izz" )   {
				if(index == 0)I1zz = val;else I2zz = val;
				Serial.println("Izz"+String(index+1)+" = "+String(val));
			}
			#endif
		
			else Serial.print("cmd desconhecido:");Serial.println(cmd);
		}
	}
	
	else if(SerialBuffer.startsWith("set ")){
		String param = SerialBuffer.substring(4);
		float aux[] = {0, 0, 0, 0, 0};
		
		if(param.startsWith("qz") || param.startsWith("home")){ //para zerar os contadores de posição. Marca todos angulos e setpoints como 0
			//aux já está com  os valores desejados
		}
		else if(param.startsWith("qr") || param.startsWith("reto")){	//0; 90;-90;0;90
			aux[1] =  pi/2;
			aux[2] = -pi/2;
			aux[4] =  pi/2;
		}
		else if(param.startsWith("qs") || param.startsWith("esticado")){	//0; 0;-90;0;90
			aux[2] = -pi/2;
			aux[4] =  pi/2;
		}
		else if(param.startsWith("ang ")){	//"set ang %f;%f;%f;%f;%f"
			float vals[5];
			read5floats(param.substring(4), vals);
			for(int i=0; i<5; ++i) aux[i] = vals[i]*pi/180;	//passa para radianos
		}
		else{
			Serial.println("posição '"+param+"' desconhecida");
			return;
		}
		
		xSemaphoreTake(SemaphoreControllVars, portMAX_DELAY);
		ConvertRadtoEncoders(aux[0], aux[1], aux[2], aux[3], aux[4]);
		q 		<< aux[0], aux[1], aux[2], aux[3], aux[4]; qAnt = q;
		qp		<< 0, 0, 0, 0, 0; qpAnt = qp;
		qd 		<< aux[0], aux[1], aux[2], aux[3], aux[4];
		epslon 	<< 0, 0, 0, 0, 0;
		xSemaphoreGive(SemaphoreControllVars);  // Release the semaphore
	}
	else if(SerialBuffer.startsWith("goto ")){
		String param = SerialBuffer.substring(5);
		float aux[] = {0, 0, 0, 0, 0};
		
		if(param.startsWith("qz") || param.startsWith("home")){ //para zerar os contadores de posição. Marca todos angulos e setpoints como 0
			//aux já está com  os valores desejados
		}
		else if(param.startsWith("qr") || param.startsWith("reto")){	//0; 90;-90;0;90
			aux[1] =  pi/2;
			aux[2] = -pi/2;
			aux[4] =  pi/2;
		}
		else if(param.startsWith("qs") || param.startsWith("esticado")){	//0; 0;-90;0;90
			aux[2] = -pi/2;
			aux[4] =  pi/2;
		}
		else{
			Serial.println("posição '"+param+"' desconhecida");
			return;
		}
		
		if(param.endsWith("log:1")) SerialLog = true;
		
		Ct.thf[0] = aux[0]; Ct.thf[1] = aux[1]; Ct.thf[2] = aux[2]; Ct.thf[3] = aux[3]; Ct.thf[4] = aux[4];
		CalcTrajetoria();
	}

	else if(SerialBuffer.startsWith("home")){ //para zerar os contadores de posição. Marca todos angulos e setpoints como 0
		xSemaphoreTake(SemaphoreControllVars, portMAX_DELAY);
		ConvertRadtoEncoders(0, 0, 0, 0, 0);
		q 		<< 0, 0, 0, 0, 0; qAnt = q;
		qp		<< 0, 0, 0, 0, 0; qpAnt = qp;
		qd 		<< 0, 0, 0, 0, 0;
		epslon 	<< 0, 0, 0, 0, 0;
		xSemaphoreGive(SemaphoreControllVars);  // Release the semaphore
	}
	else if(SerialBuffer.startsWith("reto")){ //para zerar os contadores de posição. Marca todos angulos e setpoints como 0
		xSemaphoreTake(SemaphoreControllVars, portMAX_DELAY);
		ConvertRadtoEncoders(0, pi/2, -pi/2, 0, pi/2);
		q  << 0, pi/2, -pi/2, 0, pi/2; qAnt = q;
		qp << 0, 0, 0, 0, 0; qpAnt = qp;
		qd << 0, pi/2, -pi/2, 0, pi/2;
		epslon << 0, 0, 0, 0, 0;
		xSemaphoreGive(SemaphoreControllVars);  // Release the semaphore
	}
	
	else if(SerialBuffer.startsWith("tes")){
		SerialBuffer = SerialBuffer.substring(3);	//remove o cmd "abs" ou "rel" da frente
		float vals[5];
		read5floats(SerialBuffer, vals);
		for(int i=0; i<5; ++i)
			Serial.println("v["+String(i)+"] = "+String(vals[i]));
	}
	
	else if(SerialBuffer.startsWith("abs") || SerialBuffer.startsWith("rel")){
		float d[5];
		if(SerialBuffer.startsWith("abs")){
			d[0] = 0; d[1] = 0; d[2] = 0; d[3] = 0; d[4] = 0;
		}else if(SerialBuffer.startsWith("rel")){
			d[0] = q(0); d[1] = q(1); d[2] = q(2); d[3] = q(3); d[4] = q(4);
		}
			
		//"abs [setpoint1];[setpoint2];[setpoint3];[setpoint4];[setpoint5]\n"	//deslocamento para posição absoluta recebida
		//"rel [setpoint1];[setpoint2];[setpoint3];[setpoint4];[setpoint5]\n"	//deslocamento relativo com valor recebido
		
		SerialBuffer = SerialBuffer.substring(3);	//remove o cmd "abs" ou "rel" da frente

		float vals[5];
		read5floats(SerialBuffer, vals);
		for(int i=0; i<5; ++i)
			Ct.thf[i] = constrain(d[i] + vals[i]*pi/180.0, qMax[i][0], qMax[i][1]);
		
		CalcTrajetoria();
		
		Serial.print("thf a0 a4 a5 a6 a7;tf = ");Serial.print(Ct.tf, 10);Serial.println();
		for(int i=0; i<5; ++i){
			Serial.print(Ct.thf[i]*180/pi);Serial.print(" ");
			Serial.print(Ct.a0 [i]*180/pi);Serial.print(" ");
			Serial.print(Ct.a4 [i], 10);Serial.print(" ");
			Serial.print(Ct.a5 [i], 10);Serial.print(" ");
			Serial.print(Ct.a6 [i], 10);Serial.print(" ");
			Serial.print(Ct.a7 [i], 10);Serial.println();
		}
		
		SerialLog = true;
	}
	
	else if(SerialBuffer.startsWith("sp ")){	//seta posição N da lista de posiçoes 
		//Uso:	"sp N th1;th2;th3;th4;th5"
		//N é a n-ezima posição 
		//th_ são os angulos da posição N
		//Ex: "sp 1 30;30;-30;90;-90" e "sp 2 0;30;-90;-90;0"
		//	com esses comandos o robo 
		
		SerialBuffer = SerialBuffer.substring(3);	//remove o cmd "sp " da frente
		int pindex = SerialBuffer.toInt();
		if(pindex > NPOS || pindex == 0){
			Serial.println("sp index out of range "+String(pindex));
			return;
		}
		pindex-=1;
		
		SerialBuffer = SerialBuffer.substring(SerialBuffer.indexOf(' ')+1);
		
		float vals[5];
		read5floats(SerialBuffer, vals);
		//for(int i=0; i<5; ++i){Serial.println("val["+String(i+1)+"] = "+String(vals[i]));}
		for(int i=0; i<5; ++i){
			vals[i]*=pi/180;
			p[pindex](i) = constrain(vals[i], qMax[i][0], qMax[i][1]);
			if(vals[i] != p[pindex](i)) Serial.println("p["+String(pindex+1)+"]("+String(i+1)+") constrained to "+String(p[pindex](i)*180/pi));
		}
	}
	else if(SerialBuffer.startsWith("get sp")){	//printa a lista de posiçoes
		for(int pindex=0; pindex<NPOS; ++pindex)
			Serial.println(String(p[pindex](0)*180.0/pi)+"; "
						+  String(p[pindex](1)*180.0/pi)+"; "
						+  String(p[pindex](2)*180.0/pi)+"; "
						+  String(p[pindex](3)*180.0/pi)+"; "
						+  String(p[pindex](4)*180.0/pi));
	}
	else if(SerialBuffer.startsWith("move ")){
		
		
		if(SerialBuffer.startsWith("move single")){
			#ifdef LOG_MAX
				eLogMax 	<< 0, 0, 0, 0, 0;	eLogMin		<< 0, 0, 0, 0, 0;
				qpLogMax 	<< 0, 0, 0, 0, 0;	qpLogMin 	<< 0, 0, 0, 0, 0;
				pwmLogMax 	<< 0, 0, 0, 0, 0;	pwmLogMin 	<< 0, 0, 0, 0, 0;
				FaLogMax 	<< 0, 0, 0, 0, 0;	FaLogMin 	<< 0, 0, 0, 0, 0;
			#endif
			xSemaphoreTake(SemaphoreControllVars, portMAX_DELAY);
			EnMovment = true;
			SingleMovment = true;
			SingleMovmentB = true;
			PosIndex = NPOS;	//PosIndex = 0;
			xSemaphoreGive(SemaphoreControllVars);  // Release the semaphore
		}
		else if(SerialBuffer.startsWith("move start")){
			#ifdef LOG_MAX
				eLogMax 	<< 0, 0, 0, 0, 0;	eLogMin		<< 0, 0, 0, 0, 0;
				qpLogMax 	<< 0, 0, 0, 0, 0;	qpLogMin 	<< 0, 0, 0, 0, 0;
				pwmLogMax 	<< 0, 0, 0, 0, 0;	pwmLogMin 	<< 0, 0, 0, 0, 0;
				FaLogMax 	<< 0, 0, 0, 0, 0;	FaLogMin 	<< 0, 0, 0, 0, 0;
			#endif
			xSemaphoreTake(SemaphoreControllVars, portMAX_DELAY);
			EnMovment = true;
			SingleMovment = false;
			xSemaphoreGive(SemaphoreControllVars);  // Release the semaphore
		}
		else EnMovment = false;
		
		if(SerialBuffer.endsWith("log:1")) SerialLog = true;
	}
	else if(SerialBuffer.startsWith("MoveTimeOut:")){
		float aux = SerialBuffer.substring(SerialBuffer.indexOf(':')+1).toFloat();
		xSemaphoreTake(SemaphoreControllVars, portMAX_DELAY);
		MoveTimeOut = aux;
		xSemaphoreGive(SemaphoreControllVars);  // Release the semaphore
		Serial.println("MoveTimeOut = "+String(aux)+ " s");
	}
	
	else if(SerialBuffer.startsWith("EnDeadZone")){
		int paramIndex = SerialBuffer.indexOf(':');
		EnDeadZone = SerialBuffer.substring(paramIndex+1).startsWith("true")?true:false;
		Serial.print("EnDeadZone = "); Serial.println(EnDeadZone);
	}
	
	else if(SerialBuffer.startsWith("Use") && SerialBuffer[4] == ':'){	//"Use_:", '_' == 'V' || 'G'
		if		(SerialBuffer[3] == 'V') UseV = SerialBuffer[5] == '1'?true:false;
		else if	(SerialBuffer[3] == 'G') UseG = SerialBuffer[5] == '1'?true:false;
	}
	else if(SerialBuffer.startsWith("UseF") && SerialBuffer[5] == ':'){	//"Use_:", '_' == 'V' || 'G'
		if		(SerialBuffer[4] == 'd') UseFd = SerialBuffer[6] == '1'?true:false;
		else if	(SerialBuffer[4] == 's') UseFs = SerialBuffer[6] == '1'?true:false;
	}
	
	else if(SerialBuffer.startsWith("date")){
		Serial.println("Compilado em '"+String(__DATE__)+" "+String(__TIME__)+"'");	//Serial.print(__DATE__);Serial.print(" ");Serial.println(__TIME__);
	}
	else if(SerialBuffer.startsWith("info")){
		SerialLog = false;
		Serial.println();
		
		Serial.println("Compilado em '"+String(__DATE__)+" "+String(__TIME__)+"'");
		
		Serial.print("(K="+String(CtrlData[CtrlType].K)+") ");
		if(CtrlType == CtrlType_t::TorqueCalculado){
			Serial.println("TorqueCalculado");
			Serial.println("UseV="+String(UseV)+" UseG="+String(UseG)+" UseFs="+String(UseFs)+" UseFd="+String(UseFd));
		}
		else if(CtrlType == CtrlType_t::PIDplusG) 					Serial.println("PD-Plus-Gravity");
		else if(CtrlType == CtrlType_t::ControleDeJuntaClassico) 	Serial.println("ControleDeJuntaClassico");
		else if(CtrlType == CtrlType_t::PID){
			Serial.print("PID multi uso ");
			if		(CtrlCompG == CtrlCompG_t::SemG) Serial.println("Sem G");
			else if	(CtrlCompG == CtrlCompG_t::CompG)Serial.println("Com G");
			else if	(CtrlCompG == CtrlCompG_t::CompGCond)Serial.println("Com G condicional");
			else if	(CtrlCompG == CtrlCompG_t::CompFd){
				Serial.println("Comp Fd");
				for(uint8_t i=0; i<5; ++i)Serial.println("fd["+String(i+1)+"]: "+String(fd[i]));
			}
			else if	(CtrlCompG == CtrlCompG_t::CompFadap){
				Serial.println("Com F adaptativo");
				Serial.println("gama = "+String(gama));
				Serial.print("beta = ");Serial.println(beta, 6);
			}
			else if	(CtrlCompG == CtrlCompG_t::CompFadap2){
				Serial.println("Com F adaptativo (F = Fant +dt*gama*e)");
				Serial.println("gama = "+String(gama));
				Serial.print("beta = ");Serial.println(beta, 6);
			}
			else if	(CtrlCompG == CtrlCompG_t::CompFdFadap){
				Serial.println("Com Fd e F adaptativo");
				Serial.println("gama = "+String(gama));
				Serial.print("beta = ");Serial.println(beta, 6);
				for(uint8_t i=0; i<5; ++i)Serial.println("fd["+String(i+1)+"]: "+String(fd[i]));
			}
		}
		else if(CtrlType == CtrlType_t::OnOff){
			Serial.println("Controle_OnOff");
		}
		else{	//CtrlType_t::Nenhum
			Serial.println("SemControle");
		}
		#if defined(USE_R2_J2_J3)
		Serial.println("  USE_R2_J2_J3  ");
		Serial.println("J1 En="+String(mEnable[1])+" Kp="+String(CtrlData[CtrlType].Kp[1], 5)+" Ki="+String(CtrlData[CtrlType].Ki[1], 5)+" Kd="+String(CtrlData[CtrlType].Kd[1], 5)+" TauMax="+String(TauMax[1], 5)+" InvTauMax="+String(InvTauMax[1], 5)+" vMax="+String(qpMax[1]*180/pi)+" DeadZone="+String(DeadZone[1]));
		Serial.println("J2 En="+String(mEnable[2])+" Kp="+String(CtrlData[CtrlType].Kp[2], 5)+" Ki="+String(CtrlData[CtrlType].Ki[2], 5)+" Kd="+String(CtrlData[CtrlType].Kd[2], 5)+" TauMax="+String(TauMax[2], 5)+" InvTauMax="+String(InvTauMax[2], 5)+" vMax="+String(qpMax[2]*180/pi)+" DeadZone="+String(DeadZone[2]));
		#elif defined(USE_R2_J3_J5)
		Serial.println("  USE_R2_J3_J5  ");
		Serial.println("J1 En="+String(mEnable[2])+" Kp="+String(CtrlData[CtrlType].Kp[2], 5)+" Ki="+String(CtrlData[CtrlType].Ki[2], 5)+" Kd="+String(CtrlData[CtrlType].Kd[2], 5)+" TauMax="+String(TauMax[2], 5)+" InvTauMax="+String(InvTauMax[2], 5)+" vMax="+String(qpMax[2]*180/pi)+" DeadZone="+String(DeadZone[2]));
		Serial.println("J2 En="+String(mEnable[4])+" Kp="+String(CtrlData[CtrlType].Kp[4], 5)+" Ki="+String(CtrlData[CtrlType].Ki[4], 5)+" Kd="+String(CtrlData[CtrlType].Kd[4], 5)+" TauMax="+String(TauMax[4], 5)+" InvTauMax="+String(InvTauMax[4], 5)+" vMax="+String(qpMax[4]*180/pi)+" DeadZone="+String(DeadZone[4]));
		#else
		for(uint8_t i=0; i<5; ++i){
			Serial.print("J"+String(i+1));
			Serial.print(" En=");Serial.print(mEnable[i]);
			Serial.print(" Kp=");Serial.print(CtrlData[CtrlType].Kp[i], 5);
			Serial.print(" Ki=");Serial.print(CtrlData[CtrlType].Ki[i], 5);
			Serial.print(" Kd=");Serial.print(CtrlData[CtrlType].Kd[i], 5);
			Serial.print(" TauMax=");Serial.print(TauMax[i], 5);
			Serial.print(" InvTauMax=");Serial.print(InvTauMax[i], 5);
			Serial.print(" vMax=");Serial.print(qpMax[i]*180/pi);
			Serial.print(" DeadZone=");Serial.print(DeadZone[i]);
			Serial.println();
		}
		#endif
		Serial.println("EnMovment = "+String(EnMovment)+" "+String(PosIndex)+"/"+String(NPOS)+" "+String(CurrentMoveTimeOut)+"/"+String(MoveTimeOut)+" s");
	}
	
	else if(SerialBuffer.startsWith("pf:")){
		float aux = SerialBuffer.substring(SerialBuffer.indexOf(':')+1).toFloat();
		xSemaphoreTake(SemaphoreControllVars, portMAX_DELAY);
		pf = aux;
		xSemaphoreGive(SemaphoreControllVars);  // Release the semaphore
		Serial.println("pf = "+String(aux));
	}
	
	
	
	else if(SerialBuffer.startsWith("reset")){
		xSemaphoreTake(SemaphoreControllVars, portMAX_DELAY);
		Encoders[0]=0; Encoders[1]=0; Encoders[2]=0; Encoders[3]=0; Encoders[4]=0;
		q		<< 0, 0, 0, 0, 0; qAnt = q;
		qp		<< 0, 0, 0, 0, 0; qpAnt = qp;
		qpp		<< 0, 0, 0, 0, 0;
		qd		<< 0, 0, 0, 0, 0;
		qdp		<< 0, 0, 0, 0, 0;
		qdpp	<< 0, 0, 0, 0, 0;
		u		<< 0, 0, 0, 0, 0;
		tau		<< 0, 0, 0, 0, 0;
		e		<< 0, 0, 0, 0, 0;
		ep		<< 0, 0, 0, 0, 0;
		epslon	<< 0, 0, 0, 0, 0;
		V		<< 0, 0, 0, 0, 0;
		G		<< 0, 0, 0, 0, 0;
		Fadap	<< 0, 0, 0, 0, 0;
		xSemaphoreGive(SemaphoreControllVars);  // Release the semaphore
	}
	
	else{
		Serial.println("Unknown comand: "+SerialBuffer);
	}
}

void CalcTrajetoria(){	//chamada pelos 2 nucleos (no controle e ao receber comandos da serial)
	Ct.tf = 0;
	//dddth Max em t = [0.8873, 0.5, 0.1127]
	// ddth Max em t = [0.7236, 0.2764]
	//  dth Max em t = [0.5]
	for(int i=0; i<5; ++i){
		//tf = dX*2.1875/dthMax
		double aux = ( (double)Ct.thf[i] -qd(i) )*2.1875/qpMax[i];		//limitando somente a velocidade
		if(aux < 0) aux = -aux;
		if(aux > Ct.tf) Ct.tf = aux;
	}
		
	for(int i=0; i<5; ++i){
		Ct.a0[i] = qd(i);
		double aux = ((double)(Ct.thf[i]-Ct.a0[i]));	//dX
		if(aux > -pi/288.0 && aux < pi/288.0){ //0.625°
			Ct.a4[i] = 0;
			Ct.a5[i] = 0;
			Ct.a6[i] = 0;
			Ct.a7[i] = 0;
		}else{
			double inv_tf = 1/Ct.tf;	//t^-1
			aux *=(inv_tf*inv_tf*inv_tf*inv_tf);
			Ct.a4[i] =  35*aux;	// 35*dX*tf^-4
			aux*=inv_tf;
			Ct.a5[i] = -84*aux;	//-84*dX*tf^-5
			aux*=inv_tf;
			Ct.a6[i] =  70*aux; // 70*dX*tf^-6
			aux*=inv_tf;
			Ct.a7[i] = -20*aux;	//-20*dX*tf^-7
		}
	}
	Ct.t = 0;
	CurrentMoveTimeOut = 0;
}
