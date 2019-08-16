%% 带箭头属性绘图
clc
clear
x  = linspace(0,10,1000);
y  = sin(2*pi*0.1*x);
Attribute_Set = {'LineWidth',1.5};        % 箭头属性及其取值，设置箭头宽度为1.5
[h h_a h_p h_arrow] = plot_with_arrow( [],x,y,'k',[],[],Attribute_Set );  % 绘图
htext_x = Arrow_Xlabel([],'时间/s',[]);       % x轴标签
htext_y = Arrow_Ylabel([],'幅值/V',[]);      % y轴标签
htext_title = Arrow_Title([],'图形Test');     % 图形标题


%% 用数值指示箭头坐标轴位置
clc
clear
x  = linspace(0,10,1000);
y  = sin(2*pi*0.1*x);
figure
ha1 = subplot(211);          % 获取坐标轴句柄
pos = [0.1 0.7 1 1 0.1 0.7];                                           % 坐标轴位置
[h h_a h_p h_arrow] = plot_with_arrow( ha1,x,y,'k',pos );  % 直接输入坐标轴位置，暂不支持箭头坐标轴位置输入数值情况
htext_x = Arrow_Xlabel([],'时间/s',pos);
htext_y = Arrow_Ylabel([],'幅值/V',pos);
htext_title = Arrow_Title([],'图形Test');

ha2 = subplot(212);          % 获取坐标轴句柄
pos = [0.8 0.2 0.1 0.6 0.8 0.2];                                        % 坐标轴位置
[h h_a h_p h_arrow] = plot_with_arrow( ha2,x,y,'k',pos );  % 直接输入坐标轴位置，暂不支持箭头坐标轴位置输入数值情况
htext_x = Arrow_Xlabel([],'时间/s',pos);
htext_y = Arrow_Ylabel([],'幅值/V',pos);
htext_title = Arrow_Title([],'图形Test');


%% 输入图形句柄
clc
clear
x  = linspace(0,10,1000);
y  = sin(2*pi*0.1*x);
h_f = figure;                                               %获取图形句柄
[h h_a h_p] = plot_with_arrow( h_f,x,y,'k' );   %绘图
htext_x = Arrow_Xlabel([],'时间/s',[]);
htext_y = Arrow_Ylabel([],'幅值/V',[]);
htext_title = Arrow_Title([],'图形Test');


%% 输入坐标轴句柄
clc
clear
x  = linspace(0,10,1000);
y  = sin(2*pi*0.1*x);
figure
h_a = subplot(211);           % 获取坐标轴句柄
[h h_a h_p] = plot_with_arrow( h_a,x,y,'k' );
htext_x = Arrow_Xlabel([],'时间/s',[]);
htext_y = Arrow_Ylabel([],'幅值/V',[]);
htext_title = Arrow_Title([],'图形Test1');

h_a2 = subplot(212);          % 获取坐标轴句柄
[h h_a h_p] = plot_with_arrow( h_a2,x,y,'k','nn' );
htext_x = Arrow_Xlabel([],'时间/s','nn');
htext_y = Arrow_Ylabel([],'幅值/V','nn');
htext_title = Arrow_Title([],'图形Test2');

%% 其它绘图函数
clc
clear
x = -2.9:0.2:2.9;
y = exp(-x.*x);

figure
h_a = subplot(211);
[h h_a h_p h_arrow] = plot_with_arrow( h_a,x,y,'r',[],@bar );         % 以bar函数绘直方图
htext_x = Arrow_Xlabel([],'时间/s',[]);
htext_y = Arrow_Ylabel([],'幅值/V',[]);
htext_title = Arrow_Title([],'图形Test1');
h_a2 = subplot(212);
[h h_a h_p h_arrow] = plot_with_arrow( h_a2,x,y,'b',[],@stem );     % 以stem函数画火柴杆图
htext_x = Arrow_Xlabel([],'时间/s',[]);
htext_y = Arrow_Ylabel([],'幅值/V',[]);
htext_title = Arrow_Title([],'图形Test2');

%% 绘制光坐标轴，hold on之后再绘制图形
pos = 'an';
[h ha hp h_arrow]  = plot_with_arrow([],[],[],[],pos);    % 绘制光坐标轴
hold on 
t = linspace(0,4*pi,200);
x = sin(t);
plot(t,x)                % 绘制图形
htext_x = Arrow_Xlabel([],'时间/s',pos);
htext_y = Arrow_Ylabel([],'幅值/V',pos);
htext_title = Arrow_Title([],'图形Test');

%% 综合绘制
clc
clear
x  = linspace(0,10,1000);
y  = sin(2*pi*0.1*x);
figure
h_a1 = subplot(221);
[h1 h_a1 h_p1 h_arrow1] = plot_with_arrow( h_a1,x,y,'r' );       % 不给出pos参数
htext_x1 = Arrow_Xlabel([],'时间/s',[]);
htext_y1 = Arrow_Ylabel([],'幅值/V',[]);
h_a2 = subplot(222);
pos2 = 'an';
[h2 h_a2 h_p2 h_arrow2] = plot_with_arrow( h_a2,x,y,'r',pos2 );    % 以字母组成方式给出pos参数an
htext_x2 = Arrow_Xlabel([],'时间/s',pos2);
htext_y2 = Arrow_Ylabel([],'幅值/V',pos2);
h_a3 = subplot(223);
pos3 = 'nn';
[h3 h_a3 h_p3 h_arrow3] = plot_with_arrow( h_a3,x,y,'r',pos3 );      % 以字母组成方式给出pos参数nn
htext_x3 = Arrow_Xlabel([],'时间/s',pos3);
htext_y3 = Arrow_Ylabel([],'幅值/V',pos3);
h_a4 = subplot(224);
pos4 = 'np';
[h4 h_a4 h_p4 h_arrow4] = plot_with_arrow( h_a4,x,y,'r',pos4 );       % 以字母组成方式给出pos参数np
htext_x4 = Arrow_Xlabel([],'时间/s',pos4);
htext_y4 = Arrow_Ylabel([],'幅值/V',pos4);

%% 坐标调整
% 当坐标轴中的子对象(如曲线等)被Label对象挡住时，可通过axis或xlim、ylim调整坐标轴位置来消除这种影响
% 也可通过h_text_x/y句柄或是通过鼠标手动调整Label对象的位置
clc
clear
x  = linspace(0,10,1000);
y  = sin(2*pi*0.1*x);
figure
h_a1 = subplot(221);
[h1 h_a1 h_p1 h_arrow1] = plot_with_arrow( h_a1,x,y,'r','pa' );
htext_x1 = Arrow_Xlabel([],'时间/s','pa');
htext_y1 = Arrow_Ylabel([],'幅值/V','pa');
htext_title1 = Arrow_Title(h_a1,'调整前');
h_a2 = subplot(222);
[h2 h_a2 h_p2 h_arrow2] = plot_with_arrow( h_a2,x,y,'b','pa' );
htext_x2 = Arrow_Xlabel([],'时间/s','pa');
htext_y2 = Arrow_Ylabel([],'幅值/V','pa');
htext_title2 = Arrow_Title(h_a2,'调整后');
axes(h_a2)                % 使h_a2为当前坐标轴    
axis([0 12 -1.5 1.5])    % 调整坐标轴，使Label不干扰图形
h_a3 = subplot(223);
pos3 = 'nn';
[h3 h_a3 h_p3 h_arrow3] = plot_with_arrow( h_a3,x,y,'r',pos3 );
htext_x3 = Arrow_Xlabel([],'时间/s',pos3);
htext_y3 = Arrow_Ylabel([],'幅值/V',pos3);
htext_title3 = Arrow_Title(h_a3,'调整前');
h_a4 = subplot(224);
[h4 h_a4 h_p4 h_arrow4] = plot_with_arrow( h_a4,x,y,'b',pos3 );
htext_x4 = Arrow_Xlabel([],'时间/s',pos3);
htext_y4 = Arrow_Ylabel([],'幅值/V',pos3);
htext_title4 = Arrow_Title(h_a4,'调整后');
axes(h_a4)                  % 使h_a4为当前坐标轴   
axis([-2 10 -1.5 1])        % 调整坐标轴，使Label不干扰图形

%% 修改箭头属性
x  = linspace(0,10,1000);
y  = sin(2*pi*0.1*x);
h_f = figure;
[h h_a h_p h_arrow] = plot_with_arrow( h_f,x,y,'k' );  % 绘制图形
htext_x = Arrow_Xlabel([],'时间/s',[]);
htext_y = Arrow_Ylabel([],'幅值/V',[]);
% 改变颜色
set( h_arrow,'color','r' )
% 修改箭头类型
set( h_arrow,'HeadStyle','vback3' )


