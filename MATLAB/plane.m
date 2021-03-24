%%%飞机上的传染病模型
function Y = plane(y,r,t)
% y = [S,E,I,R];
% 无治愈；
% r = [alpha_3,alpha_4,,delta];
% t= [] %按天进行计数；
beta_plane = r(1);
delta = r(2);

[t,Y] = runge_kutta1(@DifEq2, y, 0.005,t(1),t(2));
t = t';
Y = Y';
    function dy = DifEq2(t, y)
        S = y(1);
        E = y(2);
        I = y(3);
        R = y(4);
        N = S+E+I+R;
        
        dy = zeros(4, 1);
        if N>10
            dy(1) = - beta_plane* I * S/N  - 0.2*beta_plane*E*S/N;
            dy(2) =  beta_plane *I * S/N + 0.2*beta_plane*E*S/N-delta*E;
            dy(3) =  delta*E;
        end
    end
Y = Y(end,:);
end