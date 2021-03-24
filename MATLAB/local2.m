function [Y,N] = local2(y,r,t_1)
% y = [S,E,I,R];
% r = [alpha_1,alpha_2,,delta,beta];
% t= [] %按小时进行计数；
% T_1 关于温度的一些参数


betaval = r(1);
delta = r(2);
gamma = r(3);

%options = odeset('InitialStep',1e-1);
%[t,Y] = ode45(@DifEq2, t_1, y,options);
[t,Y] = runge_kutta1(@DifEq2, y, 0.005,t_1(1),t_1(2));
t = t';
Y = Y';
function dy = DifEq2(t, y)
S = y(1);
E = y(2);
I = y(3);
R = y(4);
N = S+E+I+R;


dydt = zeros(4, 1);
% dydt(1) = - alpha_1* I * S/N * sigmoid(i/(1e-4)) - alpha_2*E*S/N*sigmoid(e/(1e-4));
% dydt(2) =  alpha_1 * I * S/N* sigmoid(i/(1e-4)) + alpha_2*E*S/N*sigmoid(e/(1e-4))-delta*E;
dydt(1) = - (betaval * I * S/N + 0.2*betaval*E*S/N);
dydt(2) = (betaval * I * S/N + 0.2*betaval*E*S/N)-delta*E;
dydt(3) =  delta*E-gamma*I;
dydt(4) =  gamma*I;
dy = dydt; 
end
Y = Y(end,:);
N = sum(Y);
end