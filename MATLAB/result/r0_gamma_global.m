close all
clear, clc
% 画出一些主要国家的疫情发展情况图
%航空客流量的影响
t = 1:382;

x1 = [0,17];
y1 = [0, 0 ];
y2 = [120000, 120000];
y3 = [5e8, 5e8];

figure(1)
for j =1:5
    load(strcat(cd,'\results\sensitivity\R0_gamma\gamma\result',num2str(6-j),'.mat'))
    % load(strcat(cd,'\R0_gamma\y=0.1429\result',num2str(6-j),'.mat'))
    I_result = sum(I_result,2)
    switch(6- j)
        case 1
            plot(t,I_result, '-*', 'Color', [0 0 1 ], 'LineWidth',2,'MarkerSize',1) %蓝
        case 2
            plot(t,I_result, '--v', 'Color',[0 1 0 ],  'LineWidth',2,'MarkerSize',1) %绿
        case 3
            plot(t,I_result, '-^', 'Color',[1 1 0],  'LineWidth',2,'MarkerSize',1) % 黄
        case 4
            plot(t,I_result, '-h', 'Color',[1 0.38 0 ],  'LineWidth',2,'MarkerSize',1) %橙
        case 5
            plot(t,I_result, '--d', 'Color',[1 0 0 ],  'LineWidth',2,'MarkerSize',1)% 红
    end
    hold on;
end
%plot([17 17], [0 1e5],'--k','linewidth',1.5)
set(gca,'FontSize',20,'Fontname', 'calibri');
xlabel('T (days after the opening ceremony)','Fontname', 'calibri','fontsize',25);
ylabel('Infected cases','Fontname', 'calibri','fontsize',25);
a1 = legend('R_0=2.4,\gamma=0.1429' ,'R_0=2.0,\gamma=0.1429','R_0=1.6,\gamma=0.1429',...
    'R_0=1.2,\gamma=0.1429','R_0=0.8,\gamma=0.1429')

%a1 = legend('R_0=2.4,\gamma= 0.0953' ,'R_0=2.0,\gamma=0.1143','R_0=1.6,\gamma=0.1429',...
   %'R_0=1.2,\gamma=0.1905','R_0=0.8,\gamma=0.2858')
set(a1,'position',[0.3501 0.7033 0.3761 0.1860],'box','on','Fontname', 'calibri','fontsize',25)

fill([x1, fliplr(x1)],[y1, fliplr(y3)],[0.52941,0.80784,0.92157],'facealpha',0.3,'edgealpha',0,'HandleVisibility','off')


hfig2 = figure(1);
set(hfig2, 'position', get(0,'ScreenSize')); % 放大框框
set(gca,'LooseInset',get(gca,'TightInset'));%除去白边

%saveas(gcf,'gamma.fig');
%saveas(gcf,'R0_gamma.fig');


