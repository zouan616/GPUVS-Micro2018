%% ����ͷ���Ի�ͼ
clc
clear
x  = linspace(0,10,1000);
y  = sin(2*pi*0.1*x);
Attribute_Set = {'LineWidth',1.5};        % ��ͷ���Լ���ȡֵ�����ü�ͷ���Ϊ1.5
[h h_a h_p h_arrow] = plot_with_arrow( [],x,y,'k',[],[],Attribute_Set );  % ��ͼ
htext_x = Arrow_Xlabel([],'ʱ��/s',[]);       % x���ǩ
htext_y = Arrow_Ylabel([],'��ֵ/V',[]);      % y���ǩ
htext_title = Arrow_Title([],'ͼ��Test');     % ͼ�α���


%% ����ֵָʾ��ͷ������λ��
clc
clear
x  = linspace(0,10,1000);
y  = sin(2*pi*0.1*x);
figure
ha1 = subplot(211);          % ��ȡ��������
pos = [0.1 0.7 1 1 0.1 0.7];                                           % ������λ��
[h h_a h_p h_arrow] = plot_with_arrow( ha1,x,y,'k',pos );  % ֱ������������λ�ã��ݲ�֧�ּ�ͷ������λ��������ֵ���
htext_x = Arrow_Xlabel([],'ʱ��/s',pos);
htext_y = Arrow_Ylabel([],'��ֵ/V',pos);
htext_title = Arrow_Title([],'ͼ��Test');

ha2 = subplot(212);          % ��ȡ��������
pos = [0.8 0.2 0.1 0.6 0.8 0.2];                                        % ������λ��
[h h_a h_p h_arrow] = plot_with_arrow( ha2,x,y,'k',pos );  % ֱ������������λ�ã��ݲ�֧�ּ�ͷ������λ��������ֵ���
htext_x = Arrow_Xlabel([],'ʱ��/s',pos);
htext_y = Arrow_Ylabel([],'��ֵ/V',pos);
htext_title = Arrow_Title([],'ͼ��Test');


%% ����ͼ�ξ��
clc
clear
x  = linspace(0,10,1000);
y  = sin(2*pi*0.1*x);
h_f = figure;                                               %��ȡͼ�ξ��
[h h_a h_p] = plot_with_arrow( h_f,x,y,'k' );   %��ͼ
htext_x = Arrow_Xlabel([],'ʱ��/s',[]);
htext_y = Arrow_Ylabel([],'��ֵ/V',[]);
htext_title = Arrow_Title([],'ͼ��Test');


%% ������������
clc
clear
x  = linspace(0,10,1000);
y  = sin(2*pi*0.1*x);
figure
h_a = subplot(211);           % ��ȡ��������
[h h_a h_p] = plot_with_arrow( h_a,x,y,'k' );
htext_x = Arrow_Xlabel([],'ʱ��/s',[]);
htext_y = Arrow_Ylabel([],'��ֵ/V',[]);
htext_title = Arrow_Title([],'ͼ��Test1');

h_a2 = subplot(212);          % ��ȡ��������
[h h_a h_p] = plot_with_arrow( h_a2,x,y,'k','nn' );
htext_x = Arrow_Xlabel([],'ʱ��/s','nn');
htext_y = Arrow_Ylabel([],'��ֵ/V','nn');
htext_title = Arrow_Title([],'ͼ��Test2');

%% ������ͼ����
clc
clear
x = -2.9:0.2:2.9;
y = exp(-x.*x);

figure
h_a = subplot(211);
[h h_a h_p h_arrow] = plot_with_arrow( h_a,x,y,'r',[],@bar );         % ��bar������ֱ��ͼ
htext_x = Arrow_Xlabel([],'ʱ��/s',[]);
htext_y = Arrow_Ylabel([],'��ֵ/V',[]);
htext_title = Arrow_Title([],'ͼ��Test1');
h_a2 = subplot(212);
[h h_a h_p h_arrow] = plot_with_arrow( h_a2,x,y,'b',[],@stem );     % ��stem����������ͼ
htext_x = Arrow_Xlabel([],'ʱ��/s',[]);
htext_y = Arrow_Ylabel([],'��ֵ/V',[]);
htext_title = Arrow_Title([],'ͼ��Test2');

%% ���ƹ������ᣬhold on֮���ٻ���ͼ��
pos = 'an';
[h ha hp h_arrow]  = plot_with_arrow([],[],[],[],pos);    % ���ƹ�������
hold on 
t = linspace(0,4*pi,200);
x = sin(t);
plot(t,x)                % ����ͼ��
htext_x = Arrow_Xlabel([],'ʱ��/s',pos);
htext_y = Arrow_Ylabel([],'��ֵ/V',pos);
htext_title = Arrow_Title([],'ͼ��Test');

%% �ۺϻ���
clc
clear
x  = linspace(0,10,1000);
y  = sin(2*pi*0.1*x);
figure
h_a1 = subplot(221);
[h1 h_a1 h_p1 h_arrow1] = plot_with_arrow( h_a1,x,y,'r' );       % ������pos����
htext_x1 = Arrow_Xlabel([],'ʱ��/s',[]);
htext_y1 = Arrow_Ylabel([],'��ֵ/V',[]);
h_a2 = subplot(222);
pos2 = 'an';
[h2 h_a2 h_p2 h_arrow2] = plot_with_arrow( h_a2,x,y,'r',pos2 );    % ����ĸ��ɷ�ʽ����pos����an
htext_x2 = Arrow_Xlabel([],'ʱ��/s',pos2);
htext_y2 = Arrow_Ylabel([],'��ֵ/V',pos2);
h_a3 = subplot(223);
pos3 = 'nn';
[h3 h_a3 h_p3 h_arrow3] = plot_with_arrow( h_a3,x,y,'r',pos3 );      % ����ĸ��ɷ�ʽ����pos����nn
htext_x3 = Arrow_Xlabel([],'ʱ��/s',pos3);
htext_y3 = Arrow_Ylabel([],'��ֵ/V',pos3);
h_a4 = subplot(224);
pos4 = 'np';
[h4 h_a4 h_p4 h_arrow4] = plot_with_arrow( h_a4,x,y,'r',pos4 );       % ����ĸ��ɷ�ʽ����pos����np
htext_x4 = Arrow_Xlabel([],'ʱ��/s',pos4);
htext_y4 = Arrow_Ylabel([],'��ֵ/V',pos4);

%% �������
% ���������е��Ӷ���(�����ߵ�)��Label����סʱ����ͨ��axis��xlim��ylim����������λ������������Ӱ��
% Ҳ��ͨ��h_text_x/y�������ͨ������ֶ�����Label�����λ��
clc
clear
x  = linspace(0,10,1000);
y  = sin(2*pi*0.1*x);
figure
h_a1 = subplot(221);
[h1 h_a1 h_p1 h_arrow1] = plot_with_arrow( h_a1,x,y,'r','pa' );
htext_x1 = Arrow_Xlabel([],'ʱ��/s','pa');
htext_y1 = Arrow_Ylabel([],'��ֵ/V','pa');
htext_title1 = Arrow_Title(h_a1,'����ǰ');
h_a2 = subplot(222);
[h2 h_a2 h_p2 h_arrow2] = plot_with_arrow( h_a2,x,y,'b','pa' );
htext_x2 = Arrow_Xlabel([],'ʱ��/s','pa');
htext_y2 = Arrow_Ylabel([],'��ֵ/V','pa');
htext_title2 = Arrow_Title(h_a2,'������');
axes(h_a2)                % ʹh_a2Ϊ��ǰ������    
axis([0 12 -1.5 1.5])    % ���������ᣬʹLabel������ͼ��
h_a3 = subplot(223);
pos3 = 'nn';
[h3 h_a3 h_p3 h_arrow3] = plot_with_arrow( h_a3,x,y,'r',pos3 );
htext_x3 = Arrow_Xlabel([],'ʱ��/s',pos3);
htext_y3 = Arrow_Ylabel([],'��ֵ/V',pos3);
htext_title3 = Arrow_Title(h_a3,'����ǰ');
h_a4 = subplot(224);
[h4 h_a4 h_p4 h_arrow4] = plot_with_arrow( h_a4,x,y,'b',pos3 );
htext_x4 = Arrow_Xlabel([],'ʱ��/s',pos3);
htext_y4 = Arrow_Ylabel([],'��ֵ/V',pos3);
htext_title4 = Arrow_Title(h_a4,'������');
axes(h_a4)                  % ʹh_a4Ϊ��ǰ������   
axis([-2 10 -1.5 1])        % ���������ᣬʹLabel������ͼ��

%% �޸ļ�ͷ����
x  = linspace(0,10,1000);
y  = sin(2*pi*0.1*x);
h_f = figure;
[h h_a h_p h_arrow] = plot_with_arrow( h_f,x,y,'k' );  % ����ͼ��
htext_x = Arrow_Xlabel([],'ʱ��/s',[]);
htext_y = Arrow_Ylabel([],'��ֵ/V',[]);
% �ı���ɫ
set( h_arrow,'color','r' )
% �޸ļ�ͷ����
set( h_arrow,'HeadStyle','vback3' )


