function [y,N] = takeoff(y,N,W)
% y = [S,E,I,R];
% N 为起飞国家的人口数
% W 为该国当天出境的人数；

s = y(1)/N;
e = y(2)/N;
i = y(3)/N;
r = y(4)/N;
y(1) = y(1) - s*W;
y(2) = y(2) - e*W;
y(3) = y(3) - i *W;
y(4) = y(4) - r*W;

N = sum(y);
end
