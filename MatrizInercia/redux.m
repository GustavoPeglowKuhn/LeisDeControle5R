%%Rexuz um string usando apelidos para termos mais longos
%%uso "var_str = redux(char(symvar));"
function red = redux(str)
	red = strrep( strrep( strrep( strrep( strrep( strrep( strrep( strrep( strrep( strrep( strrep( strrep( strrep( strrep( strrep( strrep( strrep( strrep( strrep( strrep( strrep( strrep( strrep( strrep( strrep( strrep(
		str,
		"Derivative(q1(t), t)","dq1"),
		"Derivative(q2(t), t)","dq2"),
		"Derivative(q3(t), t)","dq3"),
		"Derivative(q4(t), t)","dq4"),
		"Derivative(q5(t), t)","dq5"),
		"Derivative(q1(t), (t, 2))","ddq1"),
		"Derivative(q2(t), (t, 2))","ddq2"),
		"Derivative(q3(t), (t, 2))","ddq3"),
		"Derivative(q4(t), (t, 2))","ddq4"),
		"Derivative(q5(t), (t, 2))","ddq5"),
		"sin(q1(t))","s1"),
		"cos(q1(t))","c1"),
		"sin(q2(t))","s2"),
		"cos(q2(t))","c2"),
		"sin(q3(t))","s3"),
		"cos(q3(t))","c3"),
		"sin(q2(t) + q3(t))","s23"),
		"cos(q2(t) + q3(t))","c23"),
		"sin(q4(t))","s4"),
		"cos(q4(t))","c4"),
		"sin(q5(t))","s5"),
		"cos(q5(t))","c5"),
		"sin(2*q2(t))","2*s2*c2"),
		"sin(2*q2(t) + 2*q3(t))","2*s23*c23"),
		"cos(2*q2(t) + 2*q3(t))", "(c23^2 - s23^2)"),
		"**", "^");
endfunction

function res = r(v)
	res = redux(char(simplify(v)));
endfunction

