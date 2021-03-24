close all
clear, clc
% 画出Fang的其中6中策略的后续全球发展图 

t = 1:382;

load(strcat(cd,'\Fang_result\main.mat'), 'I_result');
str_1 = sum(I_result,2);
load(strcat(cd,'\Fang_result\MV.mat'), 'I_result');
str_2 = sum(I_result,2);
load(strcat(cd,'\Fang_result\NC.mat'), 'I_result');
str_3 = sum(I_result,2);
load(strcat(cd,'\Fang_result\NX.mat'), 'I_result');
str_4 = sum(I_result,2);
load(strcat(cd,'\Fang_result\RL1.mat'), 'I_result');
str_5 = sum(I_result,2);
load(strcat(cd,'\Fang_result\RL2.mat'), 'I_result');
str_6 = sum(I_result,2);
load(strcat(cd,'\Fang_result\RL3.mat'), 'I_result');
str_7 = sum(I_result,2);


x1 = [0,17];
y1 = [0, 0 ];
y3 = [15e7, 15e7];
figure(1)
plot(t,str_1, '--d', 'Color',[1 0 0 ],  'LineWidth',1.5,'MarkerSize',1)
hold on;
plot(t,str_4, '--v', 'Color',[1 0.6471 0],  'LineWidth',1.5,'MarkerSize',1)
hold on;
plot(t,str_3, '-^', 'Color',[1 1 0],  'LineWidth',1.5,'MarkerSize',1)
hold on;
plot(t,str_6, '--p', 'Color',[0 1 0],  'LineWidth',1.5,'MarkerSize',1) 
hold on;
plot(t,str_7, '-x', 'Color',[0  0.498 1],  'LineWidth',1.5,'MarkerSize',1)
hold on;
plot(t,str_2, '-h', 'Color',[0 0 1],  'LineWidth',1.5,'MarkerSize',1)
hold on;
plot(t,str_5, '-*', 'Color', [0.5451 0 1], 'LineWidth',1.5,'MarkerSize',1) 
hold on;
a1 = legend('Standard','Travel Restriction', 'No Ceremonies','Suspension Loss Dominant','Equilibrium','More Olympics Villages','Infection Loss Dominant')
set(a1,'FontSize',25,'Interpreter', 'latex','box','off','position',[0.25 0.7 .05 .05])
fill([x1, fliplr(x1)],[y1, fliplr(y3)],[0.52941,0.80784,0.92157],'facealpha',0.3)
xlabel('T (days after the opening ceremony)','Interpreter', 'latex','fontsize',25);
ylabel('Infected cases','Interpreter', 'latex','fontsize',25);
%plot([17 17], [0 1e5],'--k','linewidth',1.5)
set(gca,'FontSize',25);
hfig2 = figure(1);
set(hfig2, 'position', get(0,'ScreenSize'));
set(gca,'LooseInset',get(gca,'TightInset'));%除去白边
filename = 'inf_time';
saveas(gcf,filename,'fig');


figure(3)
t1 = 1:17
plot(t1,str_1(1:17), '--d', 'Color',[1 0 0 ],  'LineWidth',1.5,'MarkerSize',1)
hold on;
plot(t1,str_4(1:17), '--v', 'Color',[1 0.6471 0],  'LineWidth',1.5,'MarkerSize',1)
hold on;
plot(t1,str_3(1:17), '-^', 'Color',[1 1 0],  'LineWidth',1.5,'MarkerSize',1)
hold on;
plot(t1,str_6(1:17), '--p', 'Color',[0 1 0],  'LineWidth',1.5,'MarkerSize',1) 
hold on;
plot(t1,str_7(1:17), '-x', 'Color',[0  0.498 1],  'LineWidth',1.5,'MarkerSize',1)
hold on;
plot(t1,str_2(1:17), '-h', 'Color',[0 0 1],  'LineWidth',1.5,'MarkerSize',1)
hold on;
plot(t1,str_5(1:17), '-*', 'Color', [0.5451 0 1], 'LineWidth',1.5,'MarkerSize',1) 
hold on;
set(gca,'FontSize',25,'Fontname', 'calibri');
set(gca,'xlim',[1, 18],'FontSize',25,'Fontname', 'calibri');
hfig2 = figure(3);
set(hfig2, 'position', get(0,'ScreenSize'));
set(gca,'LooseInset',get(gca,'TightInset'));%除去白边
filename = '17';
saveas(gcf,filename,'fig');



clear all

load(strcat(cd,'\Fang_result\main.mat'));
str_1 = sum(I_result,2)+sum(E_result,2)+sum(R_result,2);
load(strcat(cd,'\Fang_result\MV.mat'), 'I_result');
str_2 =sum(I_result,2)+sum(E_result,2)+sum(R_result,2);
load(strcat(cd,'\Fang_result\NC.mat'), 'I_result');
str_3 = sum(I_result,2)+sum(E_result,2)+sum(R_result,2);
load(strcat(cd,'\Fang_result\NX.mat'), 'I_result');
str_4 = sum(I_result,2)+sum(E_result,2)+sum(R_result,2);
load(strcat(cd,'\Fang_result\RL1.mat'), 'I_result');
str_5 = sum(I_result,2)+sum(E_result,2)+sum(R_result,2);
load(strcat(cd,'\Fang_result\RL2.mat'), 'I_result');
str_6 = sum(I_result,2)+sum(E_result,2)+sum(R_result,2);
load(strcat(cd,'\Fang_result\RL3.mat'), 'I_result');
str_7 = sum(I_result,2)+sum(E_result,2)+sum(R_result,2);

x1 = [0,17];
y1 = [0, 0 ];
y3 = [20e8, 20e8];
t = 1:382;
figure(2)
plot(t,str_1, '--d', 'Color',[1 0 0 ],  'LineWidth',1.5,'MarkerSize',1)
hold on;
plot(t,str_4, '--v', 'Color',[1 0.6471 0],  'LineWidth',1.5,'MarkerSize',1)
hold on;
plot(t,str_3, '-^', 'Color',[1 1 0],  'LineWidth',1.5,'MarkerSize',1)
hold on;
plot(t,str_6, '--p', 'Color',[0 1 0],  'LineWidth',1.5,'MarkerSize',1) 
hold on;
plot(t,str_7, '-x', 'Color',[0  0.498 1],  'LineWidth',1.5,'MarkerSize',1)
hold on;
plot(t,str_2, '-h', 'Color',[0 0 1],  'LineWidth',1.5,'MarkerSize',1)
hold on;
plot(t,str_5, '-*', 'Color', [0.5451 0 1], 'LineWidth',1.5,'MarkerSize',1) 
hold on;

a3 = legend('Standard','Travel Restriction', 'No Ceremonies','Suspension Loss Dominant','Equilibrium','More Olympics Villages','Infection Loss Dominant')
set(a3,'FontSize',25,'Fontname', 'calibri','box','off','position',[0.25 0.7 .05 .05])

fill([x1, fliplr(x1)],[y1, fliplr(y3)],[0.52941,0.80784,0.92157],'facealpha',0.3)
xlabel('T (days after the opening ceremony)','Fontname', 'calibri','fontsize',25);
ylabel('Cumulative infected cases','Fontname', 'calibri','fontsize',25);
%plot([17 17], [0 1e5],'--k','linewidth',1.5)
set(gca,'FontSize',25,'Fontname', 'calibri');
hfig2 = figure(2);
set(hfig2, 'position', get(0,'ScreenSize'));
set(gca,'LooseInset',get(gca,'TightInset'));%除去白边
filename = 'sum';
saveas(gcf,filename,'fig');

