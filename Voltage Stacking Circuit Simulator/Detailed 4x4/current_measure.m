data1=importdata('R_test1_3');
x1 = data1(12000:1:32000,1);
y1 = data1(12000:1:32000,2);

data2=importdata('R_test1_3_gnd');
x2 = data2(12000:1:32000,1);
y2 = data2(12000:1:32000,2);

y = abs(y1-y2);

y = y.*1000;

%plot(x2,y);

current = mean(y)


xlim([0e-6 6e-6])
%ylim([0.2 1.2])

xlabel('Time')
ylabel('Voltage(V)')