figure

clear

data1=importdata('r_test');
x1 = data1(12000:1:52000,1);
y1 = data1(12000:1:52000,2);

data2=importdata('r_test_gnd');
x2 = data2(12000:1:52000,1);
y2 = data2(12000:1:52000,2);





plot(x2,(y1 - y2));



xlim([0e-6 6e-6])
ylim([0.2 1.2])

xlabel('Time')
ylabel('Voltage(V)')

legend('without power management','with power management')
mean(abs(y1-y2)*10000)