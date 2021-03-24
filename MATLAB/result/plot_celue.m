%% 策略图

% 防控策略下的疫情发展情况
clear; clc
close all;
load('data.mat')
t = 1:382;
for j =1:4
    load(strcat(cd,'\策略\result',num2str(j),'.mat'))
    I_result = sum(I_result,2);
    switch(j)
        case 1
            plot(t,I_result, '-o', 'Color',[1 0 0 ],  'LineWidth',2,'MarkerSize',1)
        case 2
            plot(t,I_result, '--*', 'Color',[0 0 1 ],  'LineWidth',2,'MarkerSize',1)
        case 3
            plot(t,I_result, ':^', 'Color',[0 1 0 ],  'LineWidth',2,'MarkerSize',1)
        case 4
            plot(t,I_result, '-x', 'Color',[0.63 0.13 0.94 ],  'LineWidth',2,'MarkerSize',1)
    end
    hold on;
end
set(gca,'FontSize',20,'Fontname', 'Times New Roman');
title('Global','FontSize',36,'Interpreter','latex')
xlabel('T/days','FontSize',20,'Interpreter','latex')
ylabel('Infectious','FontSize',26,'Interpreter','latex')
%legend('Restriction 1','Restriction 2','Restriction 3','No restriction','FontSize',16,'Interpreter','latex','position',[70 255 .05 .05])
legend('Restriction 2','Restriction 3','FontSize',16,'Interpreter','latex','position',[70 270 .05 .05])
temp = ylim;
line([17 17],[0,temp(2)],'color','b','linestyle','--','linewidth',1.5)
text(17,0,'Olympics end','horiz','center','vert','bottom','FontSize',20,'Interpreter','latex')

hfig2 = figure(1);
set(hfig2, 'position', get(0,'ScreenSize')); % 放大框框
set(gca,'LooseInset',get(gca,'TightInset'));%除去白边
%saveas(gcf,'global','jpg');
%saveas(gcf,'global','eps');