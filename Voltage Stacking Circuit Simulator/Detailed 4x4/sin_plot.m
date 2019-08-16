x  = linspace(0,10,1000);
y  = 2 + sin(2*pi*0.1*x);
Attribute_Set = {'LineWidth',2};        % 箭头属性及其取值，设置箭头宽度为1.5
[h h_a h_p h_arrow] = plot_with_arrow( [],x,y,'k',[],[],Attribute_Set );  % 绘图


hold on
x  = linspace(0,10,1000);
y  = 2 - sin(2*pi*0.1*x);
Attribute_Set = {'LineWidth',2};        % 箭头属性及其取值，设置箭头宽度为1.5
[h h_a h_p h_arrow] = plot_with_arrow( [h],x,y,'k',[],[],Attribute_Set );  % 绘图

hold on
x1  = linspace(0,10,1000);
y1  = 5 + sin(2*pi*0.1*x);
hold on

[h h_a h_p h_arrow] = plot_with_arrow( [h],x1,y1,'k',[],[],Attribute_Set );
hold on
x1  = linspace(0,10,1000);
y1  = 1 + sin(2*pi*0.1*x);
[h h_a h_p h_arrow] = plot_with_arrow( [h],x1,y1,'k',[],[],Attribute_Set );
hold on
