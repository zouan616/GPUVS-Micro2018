R = 0.01;

data1=importdata('on_power_high1');
x1 = data1(20000:1:40000,1);
y1 = data1(20000:1:40000,2);

data2=importdata('on_power_low1');
x2 = data2(20000:1:40000,1);
y2 = data2(20000:1:40000,2);


y = y1 - y2;

y = y.*1e4;

y = y.*y.*R;
s1 = mean(y)

R = 0.01;

data1=importdata('on_power_high2');
x1 = data1(20000:1:40000,1);
y1 = data1(20000:1:40000,2);

data2=importdata('on_power_low2');
x2 = data2(20000:1:40000,1);
y2 = data2(20000:1:40000,2);


y = y1 - y2;
y = y.*1e4;


y = y.*y.*R;
s2 = mean(y)

R = 0.01;

data1=importdata('on_power_high3');
x1 = data1(20000:1:40000,1);
y1 = data1(20000:1:40000,2);

data2=importdata('on_power_low3');
x2 = data2(20000:1:40000,1);
y2 = data2(20000:1:40000,2);


y = y1 - y2;

y = y.*1e4;



y = y.*y.*R;
s3 = mean(y)

R = 0.01;

data1=importdata('on_power_high4');
x1 = data1(20000:1:40000,1);
y1 = data1(20000:1:40000,2);

data2=importdata('on_power_low4');
x2 = data2(20000:1:40000,1);
y2 = data2(20000:1:40000,2);


y = y1 - y2;

y = y.*1e4;



y = y.*y.*R;
s4 = mean(y)

s1
s2
s3
s4
s = s1 + s2 + s3 + s4

s = s./R
