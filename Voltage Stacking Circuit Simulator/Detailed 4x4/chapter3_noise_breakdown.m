figure
data1=importdata('SM1.data');
x1 = data1(1:1:220000,1);
y1 = data1(1:1:220000,2);
data2=importdata('SM6.data');
x2 = data2(1:1:220000,1);
y2 = data2(1:1:220000,2);




plot(x1,y1-y2 - 1.08);
