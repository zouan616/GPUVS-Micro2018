figure

data1=importdata('SM1_total');
x1 = data1(1:1:207152,1);
y1 = data1(1:1:207152,2);
data2=importdata('SM1_gnd_total');
x2 = data2(1:1:207152,1);
y2 = data2(1:1:207152,2);


plot(x2,8*(y1 - y2 - 1));

hold on


data1=importdata('SM1_global');
x1 = data1(1:1:207152,1);
y1 = data1(1:1:207152,2);
data2=importdata('SM1_gnd_global');
x2 = data2(1:1:207152,1);
y2 = data2(1:1:207152,2);


plot(x2,8*(y1 - y2 - 1));

hold on

data1=importdata('SM1_stack');
x1 = data1(1:1:207152,1);
y1 = data1(1:1:207152,2);
data2=importdata('SM1_gnd_stack');
x2 = data2(1:1:207152,1);
y2 = data2(1:1:207152,2);


plot(x2,8*(y1 - y2 - 1));


hold on

data1=importdata('SM1_residual');
x1 = data1(1:1:207152,1);
y1 = data1(1:1:207152,2);
data2=importdata('SM1_gnd_residual');
x2 = data2(1:1:207152,1);
y2 = data2(1:1:207152,2);


plot(x2,8*(y1 - y2 - 1));

hold on

legend('\Delta V','\Delta V^{G}','\Delta V^{ST}','\Delta V^{R}')
