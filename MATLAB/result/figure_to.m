close all
clear, clc
load('data.mat')
% 画出一些主要国家的疫情发展情况图
%航空客流量的影响
index = [1,34,44,53,71,73,99,103,107,188,218];
[~,name]= xlsread('F:\项目\新冠肺炎\参考论文\2016_flight\newdata\Periodic\ToHou\country_info.xlsx', 'A2:A235');
len = length(index);
t = 1:382;
for i = 1:10
    figure(i)
    for j =1:10
        load(strcat(cd,'\lambda\result',num2str(11-j),'.mat'))
        switch(11-j)
            case 1
                plot(t,I_result(:,index(i)), '-o', 'Color',[0 0 0],  'LineWidth',2,'MarkerSize',1) 
            case 2
                plot(t,I_result(:,index(i)), '--*', 'Color',[0.96 0.64 0.38],  'LineWidth',2,'MarkerSize',1)
            case 3
                plot(t,I_result(:,index(i)), ':^', 'Color',[0.87 0.63 0.87],  'LineWidth',2,'MarkerSize',1)
            case 4
                plot(t,I_result(:,index(i)), '-x', 'Color',[0.63 0.13 0.94 ],  'LineWidth',2,'MarkerSize',1) %紫色
            case 5
                plot(t,I_result(:,index(i)), '--p', 'Color',[0 1 1 ],  'LineWidth',2,'MarkerSize',1) %青
            case 6
                plot(t,I_result(:,index(i)), '-*', 'Color', [0 0 1 ], 'LineWidth',2,'MarkerSize',1) %蓝
            case 7
                plot(t,I_result(:,index(i)), '--v', 'Color',[0 1 0 ],  'LineWidth',2,'MarkerSize',1) %绿
            case 8
                plot(t,I_result(:,index(i)), '-^', 'Color',[1 1 0],  'LineWidth',2,'MarkerSize',1) % 黄
            case 9
                plot(t,I_result(:,index(i)), '-h', 'Color',[1 0.38 0 ],  'LineWidth',2,'MarkerSize',1) %橙
            case 10
                plot(t,I_result(:,index(i)), '--d', 'Color',[1 0 0 ],  'LineWidth',2,'MarkerSize',1)% 红
        end
        hold on;
    end
    %plot([17 17], [0 1e5],'--k','linewidth',1.5)
    set(gca,'FontSize',20,'Fontname', 'Times New Roman');
    title(name(index(i)),'FontSize',36,'Interpreter','latex')
    xlabel('$T$/days','FontSize',25,'Interpreter','latex')
    ylabel('Cases of  infectious','FontSize',25,'Interpreter','latex')
    legend('\lambda = 1.0 ','\lambda = 0.9 ','\lambda = 0.8 ','\lambda = 0.7 ','\lambda = 0.6 ','\lambda = 0.5 ','\lambda = 0.4 ','\lambda = 0.3 ','\lambda = 0.2 ','\lambda = 0.1 ','FontSize',20,'Interpreter','latex','position',[60 230 .05 .05])
   % legend('\beta_{plane} = 2.4', '\beta_{plane} = 2.2', '\beta_{plane} = 2.0','\beta_{plane} = 1.8', '\beta_{plane} = 1.6', '\beta_{plane} = 1.4', '\beta_{plane} = 1.2',...
    %    '\beta_{plane} = 1.0', '\beta_{plane} = 0.8', '\beta_{plane} = 0.6', '\beta_{plane} = 0.4','FontSize',20,'Interpreter','latex','position',[63 203 .05 .05])
    temp = ylim;
    line([17 17],[0,temp(2)],'color','b','linestyle','--','linewidth',1.5)
    text(17,0,'Closing ceremony','horiz','left','vert','bottom','FontSize',25,'Interpreter','latex')
    
    hfig2 = figure(i);
    set(hfig2, 'position', get(0,'ScreenSize')); % 放大框框
    set(gca,'LooseInset',get(gca,'TightInset'));%除去白边
    filename = name(index(i));
    filename = filename{1};
    saveas(gcf,filename,'jpg');
    saveas(gcf,filename,'eps');
end
