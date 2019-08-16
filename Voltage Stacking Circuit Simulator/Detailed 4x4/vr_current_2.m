R = 0.05;

data1=importdata('off_power_high');
x1 = data1(20000:1:50000,1);
y1 = data1(20000:1:50000,2);

data2=importdata('off_power_low');
x2 = data2(20000:1:50000,1);
y2 = data2(20000:1:50000,2);


y = y1 - y2;

y = y.*1e5;
y = y.*y.*R;
y1 = mean(y)

y1 = y1./R