close all
clear, clc
% ����һЩ��Ҫ���ҵ����鷢չ���ͼ
%���տ�������Ӱ��
load('data.mat')
index = [1,34,44,53,71,73,99,103,107,188,218];
[~,name]= xlsread('F:\��Ŀ\�¹ڷ���\�ο�����\2016_flight\newdata\Periodic\ToHou\country_info.xlsx', 'A2:A235');
len = length(index);
t = 1:382;
for i = 1:len
    figure(i)
    for j =1:5
        load(strcat(cd,'\R0_gamma\y=0.1429\result',num2str(6-j),'.mat'))
        switch(6-j)
            case 1
                plot(t,I_result(:,index(i)), '-*', 'Color', [0 0 1 ], 'LineWidth',2,'MarkerSize',1) %��
            case 2
                plot(t,I_result(:,index(i)), '--v', 'Color',[0 1 0 ],  'LineWidth',2,'MarkerSize',1) %��
            case 3
                plot(t,I_result(:,index(i)), '-^', 'Color',[1 1 0],  'LineWidth',2,'MarkerSize',1) % ��
            case 4
                plot(t,I_result(:,index(i)), '-h', 'Color',[1 0.38 0 ],  'LineWidth',2,'MarkerSize',1) %��
            case 5
                plot(t,I_result(:,index(i)), '--d', 'Color',[1 0 0 ],  'LineWidth',2,'MarkerSize',1)% ��
        end
        hold on;
    end
    %plot([17 17], [0 1e5],'--k','linewidth',1.5)
    set(gca,'FontSize',20,'Fontname', 'Times New Roman');
    title(name(index(i)),'FontSize',36,'Interpreter','latex')
    xlabel('$T$/days','FontSize',25,'Interpreter','latex')
    ylabel('Cases of  infectious','FontSize',25,'Interpreter','latex')
   
    %legend('R_0=2.8,\gamma=0.0816' ,'R_0=2.4,\gamma=0.0952','R_0=2.0,\gamma=0.1143',...
      %  'R_0=1.6,\gamma=0.1429','R_0=1.2,\gamma=0.1905','FontSize',20,'Interpreter','latex','position',[70 243 .05 .05])
   
    %legend('R_0=1.2,\gamma=0.1429' ,'R_0=1.6,\gamma=0.1429','R_0=2.0,\gamma=0.1429',...
    %'R_0=2.4,\gamma=0.1429','R_0=2.8,\gamma=0.1429','FontSize',20,'Interpreter','latex','position',[75 245 .05 .05])
    legend('R_0=2.8,\gamma=0.1429' ,'R_0=2.4,\gamma=0.1429','R_0=2.0,\gamma=0.1429',...
    'R_0=1.6,\gamma=0.1429','R_0=1.2,\gamma=0.1429','FontSize',20,'Interpreter','latex','position',[71,243, .05 .05])
    temp = ylim;
    line([17 17],[0,temp(2)],'color','b','linestyle','--','linewidth',1.5)
    text(17,0,'Closing ceremony','horiz','left','vert','bottom','FontSize',25,'Interpreter','latex')
    
    hfig2 = figure(i);
    set(hfig2, 'position', get(0,'ScreenSize')); % �Ŵ���
    set(gca,'LooseInset',get(gca,'TightInset'));%��ȥ�ױ�
    filename = name(index(i));
    filename = filename{1};
    saveas(gcf,filename,'jpg');
    saveas(gcf,filename,'eps');
end
