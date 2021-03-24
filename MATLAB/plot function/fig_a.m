close all
clear, clc
t = 1:382;
load(strcat(cd,'\strategy_result\NO_str.mat'), 'I_result');
no_str = I_result;
clear I_result;
load(strcat(cd,'\strategy_result\str_1.mat'), 'I_result');
str1 = I_result;
clear I_result;
load(strcat(cd,'\strategy_result\str_2.mat'),'I_result');
str2 = I_result;
clear I_result;
load(strcat(cd,'\strategy_result\str_1_2.mat'),'I_result');
str3 = I_result;
clear I_result;

x1 = [1,17];
y1 = [0, 0 ];
y2 = [120000, 120000];
y3 = [15e7, 15e7];

fig = figure(1);
subplot(2,1,1)

plot(t,sum(no_str,2),'--', 'Color','r',  'LineWidth',1.5,'MarkerSize',1);
hold on
plot(t,sum(str1,2),':x', 'Color',[0,0,1],  'LineWidth',1.5,'MarkerSize',1);
ylabel('Infected cases','Interpreter', 'latex','fontsize',25);
set(gca,'ylim',[13000, 1.5e8],'FontSize',25);
set(gca,'xticklabel',[]);
set(gca,'box','on');
set(gca,'position',[0.15 0.5 0.7 0.4]);
a1 = legend('Standard sence', 'Air travel restrictions')
set(a1,'position',[0.3501 0.7033 0.3761 0.1860],'box','on','Interpreter', 'latex','fontsize',25)
fill([x1, fliplr(x1)],[y1, fliplr(y3)],[0.52941,0.80784,0.92157],'facealpha',0.3)
temp = ylim;
line([48 48],[0,temp(2)],'color','b','linestyle','--','linewidth',1.5)

subplot(2,1,2)

plot(t,sum(str2,2),'--*', 'Color', [0.49,0.18,0.56 ], 'LineWidth',1.5,'MarkerSize',1);
hold on
plot(t,sum(str3,2),'-+','Color', [0,1,0],  'LineWidth',1.5,'MarkerSize',1);

set(gca,'ylim',[0, 120000],'FontSize',25);
xlabel('$T$ (days after the opening ceremony)','Interpreter', 'latex','fontsize',17);
ylabel('Infected cases','Interpreter', 'latex','fontsize',25);

set(gca,'box','on');
set(gca,'position',[0.15 0.1 0.7 0.4]);
a2 = legend('Isolation', 'Isolation + Air travel restrictions')
 set(a2,'position',[0.3501 0.3033 0.1761 0.05],'box','on','Interpreter', 'latex','fontsize',25)
fill([x1, fliplr(x1)],[y1, fliplr(y2)],[0.52941,0.80784,0.92157],'facealpha',0.3)

annotation('arrow',[0.28 0.24],[0.25 0.25]);
text(78,38000,'Strategy begins','horiz','left','vert','bottom','FontSize',25,'Interpreter', 'latex')
temp = ylim;
line([48 48],[0,temp(2)],'color','b','linestyle','--','linewidth',1.5)

hfig2 = figure(1);
set(hfig2, 'position', get(0,'ScreenSize'));
set(gca,'LooseInset',get(gca,'TightInset'));%³ýÈ¥°×±ß
filename = 'strategy';
saveas(gcf,filename,'fig');

