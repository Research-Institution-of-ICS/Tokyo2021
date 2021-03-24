close all
clear, clc
% 画出一些主要国家的疫情发展情况图
%航空客流量的影响
% load('data.mat');
t = 1:382;

x1 = [0,17];
y1 = [0, 0 ];
y2 = [120000, 120000];
y3 = [1.6e7, 1.6e7];

figure(1)
for j =1:10
    % load(strcat(cd,'\lambda\result',num2str(11-j),'.mat'))
    load(strcat(cd,'\results\sensitivity\lambda\result',num2str(11-j),'.mat'))
    I_result = sum(I_result,2);
    switch(11-j)
        case 1
            plot(t,I_result, '-o', 'Color',[0 0 0],  'LineWidth',2,'MarkerSize',1)
        case 2
            plot(t,I_result, '--*', 'Color',[0.96 0.64 0.38],  'LineWidth',2,'MarkerSize',1)
        case 3
            plot(t,I_result, ':^', 'Color',[0.87 0.63 0.87],  'LineWidth',2,'MarkerSize',1)
        case 4
            plot(t,I_result, '-x', 'Color',[0.63 0.13 0.94 ],  'LineWidth',2,'MarkerSize',1) %紫色
        case 5
            plot(t,I_result, '--p', 'Color',[0 1 1 ],  'LineWidth',2,'MarkerSize',1) %青
        case 6
            plot(t,I_result, '-*', 'Color', [0 0 1 ], 'LineWidth',2,'MarkerSize',1) %蓝
        case 7
            plot(t,I_result, '--v', 'Color',[0 1 0 ],  'LineWidth',2,'MarkerSize',1) %绿
        case 8
            plot(t,I_result, '-^', 'Color',[1 1 0],  'LineWidth',2,'MarkerSize',1) % 黄
        case 9
            plot(t,I_result, '-h', 'Color',[1 0.38 0 ],  'LineWidth',2,'MarkerSize',1) %橙
        case 10
            plot(t,I_result, '--d', 'Color',[1 0 0 ],  'LineWidth',2,'MarkerSize',1)% 红
    end
    hold on;
end


set(gca,'FontSize',20,'Fontname', 'calibri');
xlabel('T (days after the opening ceremony)','FontSize',25,'Fontname', 'calibri')
ylabel('Infected Cases','FontSize',25,'Fontname', 'calibri')
%legend('\lambda = 0.1 ','\lambda = 0.2 ','\lambda = 0.3 ','\lambda = 0.4 ','\lambda = 0.5 ','\lambda = 0.6 ','\lambda = 0.7 ','\lambda = 0.8 ','\lambda = 0.9 ','\lambda = 1 ','FontSize',16,'Interpreter','latex','position',[65 230 .05 .05])
%a1 = legend('\beta_{plane} = 2.4', '\beta_{plane} = 2.2', '\beta_{plane} = 2.0','\beta_{plane} = 1.8', '\beta_{plane} = 1.6', '\beta_{plane} = 1.4', '\beta_{plane} = 1.2',...
%'\beta_{plane} = 1.0', '\beta_{plane} = 0.8', '\beta_{plane} = 0.6', '\beta_{plane} = 0.4')
a1 = legend('\lambda = 1.0 ','\lambda = 0.9 ','\lambda = 0.8 ','\lambda = 0.7 ','\lambda = 0.6 ','\lambda = 0.5 ','\lambda = 0.4 ','\lambda = 0.3 ','\lambda = 0.2 ','\lambda = 0.1 ')
set(a1,'position',[0.3501 0.7033 0.3761 0.1860],'box','on','Fontname', 'calibri','fontsize',25)

set(gca,'ylim',[0, 1.6e7],'FontSize',25);
fill([x1, fliplr(x1)],[y1, fliplr(y3)],[0.52941,0.80784,0.92157],'facealpha',0.3,'edgealpha',0,'HandleVisibility','off')


hfig2 = figure(1);
set(hfig2, 'position', get(0,'ScreenSize'));
set(gca,'LooseInset',get(gca,'TightInset'));%除去白边

% saveas(gcf,'lambda.fig');
% saveas(gcf,'lambda.eps','psc2');

%saveas(gcf,'beta_plane.fig');

