on_chip = 0;
R = 0.02;

data1=importdata('R_test1_1');
x1 = data1(1:1:80000,1);
y1 = data1(1:1:80000,2);

data2=importdata('R_test1_1_gnd');
x2 = data2(1:1:80000,1);
y2 = data2(1:1:80000,2);


y = y1 - y2;

y = y.*1e5;
y = y.*y.*R;
y1 = mean(y)

on_chip = on_chip + mean(y);

data1=importdata('R_test1_2');
x1 = data1(1:1:80000,1);
y1 = data1(1:1:80000,2);

data2=importdata('R_test1_2_gnd');
x2 = data2(1:1:80000,1);
y2 = data2(1:1:80000,2);


y = y1 - y2;

y = y.*1e5;
y = y.*y.*R;
y2 = mean(y)
on_chip = on_chip + mean(y);

data1=importdata('R_test1_3');
x1 = data1(1:1:80000,1);
y1 = data1(1:1:80000,2);

data2=importdata('R_test1_3_gnd');
x2 = data2(1:1:80000,1);
y2 = data2(1:1:80000,2);


y = y1 - y2;

y = y.*1e5;
y = y.*y.*R;
y3 = mean(y)
on_chip = on_chip + mean(y);

data1=importdata('R_test1_4');
x1 = data1(1:1:80000,1);
y1 = data1(1:1:80000,2);

data2=importdata('R_test1_4_gnd');
x2 = data2(1:1:80000,1);
y2 = data2(1:1:80000,2);


y = y1 - y2;

y = y.*1e5;
y = y.*y.*R;
y4 = mean(y)
on_chip = on_chip + mean(y);

data1=importdata('R_test2_1');
x1 = data1(1:1:80000,1);
y1 = data1(1:1:80000,2);

data2=importdata('R_test2_1_gnd');
x2 = data2(1:1:80000,1);
y2 = data2(1:1:80000,2);


y = y1 - y2;

y = y.*1e5;
y = y.*y.*R;
y5 = mean(y)
on_chip = on_chip + mean(y);

data1=importdata('R_test2_2');
x1 = data1(1:1:80000,1);
y1 = data1(1:1:80000,2);

data2=importdata('R_test2_2_gnd');
x2 = data2(1:1:80000,1);
y2 = data2(1:1:80000,2);


y = y1 - y2;

y = y.*1e5;
y = y.*y.*R;
y6 = mean(y)
on_chip = on_chip + mean(y);

data1=importdata('R_test2_3');
x1 = data1(1:1:80000,1);
y1 = data1(1:1:80000,2);

data2=importdata('R_test2_3_gnd');
x2 = data2(1:1:80000,1);
y2 = data2(1:1:80000,2);


y = y1 - y2;

y = y.*1e5;
y = y.*y.*R;
y7 = mean(y)
on_chip = on_chip + mean(y);

data1=importdata('R_test2_4');
x1 = data1(1:1:80000,1);
y1 = data1(1:1:80000,2);

data2=importdata('R_test2_4_gnd');
x2 = data2(1:1:80000,1);
y2 = data2(1:1:80000,2);


y = y1 - y2;

y = y.*1e5;
y = y.*y.*R;
y8 = mean(y)
on_chip = on_chip + mean(y);


data1=importdata('R_test3_1');
x1 = data1(1:1:80000,1);
y1 = data1(1:1:80000,2);

data2=importdata('R_test3_1_gnd');
x2 = data2(1:1:80000,1);
y2 = data2(1:1:80000,2);


y = y1 - y2;

y = y.*1e5;
y = y.*y.*R;
y9 = mean(y)
on_chip = on_chip + mean(y);



data1=importdata('R_test3_2');
x1 = data1(1:1:80000,1);
y1 = data1(1:1:80000,2);

data2=importdata('R_test3_2_gnd');
x2 = data2(1:1:80000,1);
y2 = data2(1:1:80000,2);


y = y1 - y2;

y = y.*1e5;
y = y.*y.*R;
y10 = mean(y)
on_chip = on_chip + mean(y);



data1=importdata('R_test3_3');
x1 = data1(1:1:80000,1);
y1 = data1(1:1:80000,2);

data2=importdata('R_test3_3_gnd');
x2 = data2(1:1:80000,1);
y2 = data2(1:1:80000,2);


y = y1 - y2;

y = y.*1e5;
y = y.*y.*R;
y11 = mean(y)
on_chip = on_chip + mean(y);


data1=importdata('R_test3_4');
x1 = data1(1:1:80000,1);
y1 = data1(1:1:80000,2);

data2=importdata('R_test3_4_gnd');
x2 = data2(1:1:80000,1);
y2 = data2(1:1:80000,2);


y = y1 - y2;

y = y.*1e5;
y = y.*y.*R;
y12 = mean(y)
on_chip = on_chip + mean(y);

data1=importdata('R_test4_1');
x1 = data1(1:1:80000,1);
y1 = data1(1:1:80000,2);

data2=importdata('R_test4_1_gnd');
x2 = data2(1:1:80000,1);
y2 = data2(1:1:80000,2);


y = y1 - y2;

y = y.*1e5;
y = y.*y.*R;
y13 = mean(y)
on_chip = on_chip + mean(y);

data1=importdata('R_test4_2');
x1 = data1(1:1:80000,1);
y1 = data1(1:1:80000,2);

data2=importdata('R_test4_2_gnd');
x2 = data2(1:1:80000,1);
y2 = data2(1:1:80000,2);


y = y1 - y2;

y = y.*1e5;
y = y.*y.*R;
y14 = mean(y)
on_chip = on_chip + mean(y);

data1=importdata('R_test4_3');
x1 = data1(1:1:80000,1);
y1 = data1(1:1:80000,2);

data2=importdata('R_test4_3_gnd');
x2 = data2(1:1:80000,1);
y2 = data2(1:1:80000,2);


y = y1 - y2;

y = y.*1e5;
y = y.*y.*R;

y15 = mean(y)
on_chip = on_chip + mean(y);

data1=importdata('R_test4_4');
x1 = data1(1:1:80000,1);
y1 = data1(1:1:80000,2);

data2=importdata('R_test4_4_gnd');
x2 = data2(1:1:80000,1);
y2 = data2(1:1:80000,2);


y = y1 - y2;

y = y.*1e5;
y = y.*y.*R;
y16 = mean(y)
on_chip = on_chip + mean(y)
