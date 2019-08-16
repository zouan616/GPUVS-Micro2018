figure
data1=importdata('R_test2_4');
x1 = data1(1:1:100000,1);
y1 = data1(1:1:100000,2);

data2=importdata('R_test2_4_gnd');
x2 = data2(1:1:100000,1);
y2 = data2(1:1:100000,2);


y = y1 - y2;

plot(x1, y*100000)