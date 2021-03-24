close all
clear, clc
% 画出一些主要国家的疫情发展情况图
%航空客流量的影响
load('data.mat')
index = [1,34,44,53,71,73,99,103,107,188,218];
[~,name]= xlsread('F:\项目\新冠肺炎\参考论文\2016_flight\newdata\Periodic\ToHou\country_info.xlsx', 'A2:A235');
len = length(index);
t = 1:382;
for i = 1:len
    figure(i)
    for j =1:4
        load(strcat(cd,'\策略\result',num2str(j),'.mat'))
        for m = 1:length(N)
            I_result(:,m) = I_result(:,m) *10000/N(m);
        end
        switch(j)
            case 1
                %plot(t,I_result(:,index(i)), '-o', 'Color',[1 0 0 ],  'LineWidth',2,'MarkerSize',1)
            case 2
                plot(t,I_result(:,index(i)), '--*', 'Color',[0 0 1 ],  'LineWidth',2,'MarkerSize',1)
            case 3
                plot(t,I_result(:,index(i)), ':^', 'Color',[0 1 0 ],  'LineWidth',2,'MarkerSize',1)
            case 4
                %plot(t,I_result(:,index(i)), '-x', 'Color',[0.63 0.13 0.94 ],  'LineWidth',2,'MarkerSize',1)
        end
        hold on;
    end
    %plot([17 17], [0 1e5],'--k','linewidth',1.5)
    set(gca,'FontSize',20,'Fontname', 'Times New Roman');
    title(name(index(i)),'FontSize',36,'Interpreter','latex')
    xlabel('T/days','FontSize',20,'Interpreter','latex')
    ylabel('Infectious','FontSize',20,'Interpreter','latex')
    legend('Restriction 2','Restriction 3','FontSize',16,'Interpreter','latex','position',[70 270 .05 .05])
   % legend('Restriction 1','Restriction 2','Restriction 3','No restriction','FontSize',16,'Interpreter','latex','position',[65 255 .05 .05])
    
    temp = ylim;
    line([17 17],[0,temp(2)],'color','b','linestyle','--','linewidth',1.5)
    text(17,0,'Olympics end','horiz','center','vert','bottom','FontSize',20,'Interpreter','latex')   
    hfig2 = figure(i);
    set(hfig2, 'position', get(0,'ScreenSize')); % 放大框框
    set(gca,'LooseInset',get(gca,'TightInset'));%除去白边
    filename = name(index(i));
    filename = filename{1};
    saveas(gcf,filename,'jpg');
    saveas(gcf,filename,'eps');
end
