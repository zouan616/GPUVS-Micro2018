figure

data1=importdata('SM1_13_2');
x1 = data1(20000:1:40000,1);
y1 = data1(20000:1:40000,2);

data2=importdata('SM1_gnd_13_2');
x2 = data2(20000:1:40000,1);
y2 = data2(20000:1:40000,2);

%x1 = x1./(1000*1.5e-9);

y = y1 - y2;

plot(x1,y, 'linewidth', 2);


xlabel('Time')
ylabel('Supply Voltage Noise(V)')
grid on