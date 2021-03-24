function [x,y]=runge_kutta1(ufunc,y0,h,a,b)
%������˳��������΢�ַ�����ĺ������ƣ���ʼֵ������������ʱ����㣬ʱ���յ㣨������ʽ�ο���ode45������
n=floor((b-a)/h);%����
x(1)=a;%ʱ�����
y(:,1)=y0;%����ֵ������������������Ҫע��ά��
for ii=1:n

x(ii+1)=x(ii)+h;

k1=ufunc(x(ii),y(:,ii));

k2=ufunc(x(ii)+h/2,y(:,ii)+h*k1/2);

k3=ufunc(x(ii)+h/2,y(:,ii)+h*k2/2);

k4=ufunc(x(ii)+h,y(:,ii)+h*k3);

y(:,ii+1)=y(:,ii)+h*(k1+2*k2+2*k3+k4)/6;
%���������������������ֵ���
end