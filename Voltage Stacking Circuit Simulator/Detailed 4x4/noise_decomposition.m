%figure

data1=importdata('SM1_full');
x1 = data1(1:1:250000,1);
y1 = data1(1:1:250000,2);

data2=importdata('SM1_gnd_full');
x2 = data2(1:1:250000,1);
y2 = data2(1:1:250000,2);

%x1 = x1./(1000*1.5e-9);

y = y1 - y2;

plot(x1.*1e6,y, 'r', 'linewidth', 1.5);

hold on



data1=importdata('SM1_global');
x1 = data1(1:1:250000,1);
y1 = data1(1:1:250000,2);

data2=importdata('SM1_gnd_global');
x2 = data2(1:1:250000,1);
y2 = data2(1:1:250000,2);

%x1 = x1./(1000*1.5e-9);

y = y1 - y2;

plot(x1.*1e6,y, 'b', 'linewidth', 1.5);

hold on

data1=importdata('SM1_stack');
x1 = data1(1:1:250000,1);
y1 = data1(1:1:250000,2);

data2=importdata('SM1_gnd_stack');
x2 = data2(1:1:250000,1);
y2 = data2(1:1:250000,2);

%x1 = x1./(1000*1.5e-9);

y = y1 - y2;

plot(x1.*1e6,y, 'g' ,'linewidth', 1.5);

hold on

data1=importdata('SM1_residual');
x1 = data1(1:1:250000,1);
y1 = data1(1:1:250000,2);

data2=importdata('SM1_gnd_residual');
x2 = data2(1:1:250000,1);
y2 = data2(1:1:250000,2);

%x1 = x1./(1000*1.5e-9);

y = y1 - y2;

plot(x1.*1e6,y, 'k','linewidth', 1.5);

hold on

xlabel('Time(us)')
ylabel('Supply Voltage Noise(V)')
grid on

legend('\Delta V','\Delta V^{G}','\Delta V^{ST}','\Delta V^{R}')

xlim([0 3])
ylim([-0.2 0.2])
