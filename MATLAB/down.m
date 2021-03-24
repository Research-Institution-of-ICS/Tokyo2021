function [y,N] = down(y,N,W)
% y = [S,E,I,R];
% N 为到达国家的人口数
% gamma 为全球的人口转移率
% W= [S, E ,I ,R]为该国当天入境的人数；

%这个程序中以人口为标准




y(1) = y(1)+W(1);
y(2) = y(2)+W(2);
y(3) = y(3)+W(3);
y(4) = y(4)+W(4);
N = N+sum(W);
end


