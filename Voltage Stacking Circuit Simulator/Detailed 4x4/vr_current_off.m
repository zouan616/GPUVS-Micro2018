off_chip = 0;
R = 0.01;


data1=importdata('R_test_off_2_1');
x1 = data1(1:1:100000,1);
y1 = data1(1:1:100000,2);

data2=importdata('R_test_off_2_1_gnd');
x2 = data2(1:1:100000,1);
y2 = data2(1:1:100000,2);


y = y1 - y2;

y = y.*1e5;
y = y.*y.*R;
off_chip = off_chip + mean(y);

data1=importdata('R_test_off_2_2');
x1 = data1(1:1:100000,1);
y1 = data1(1:1:100000,2);

data2=importdata('R_test_off_2_2_gnd');
x2 = data2(1:1:100000,1);
y2 = data2(1:1:100000,2);


y = y1 - y2;

y = y.*1e5;

y = y.*y.*R;
off_chip = off_chip + mean(y);

data1=importdata('R_test_off_2_3');
x1 = data1(1:1:100000,1);
y1 = data1(1:1:100000,2);

data2=importdata('R_test_off_2_3_gnd');
x2 = data2(1:1:100000,1);
y2 = data2(1:1:100000,2);


y = y1 - y2;

y = y.*1e5;
y = y.*y.*R;
off_chip = off_chip + mean(y);

data1=importdata('R_test_off_2_4');
x1 = data1(1:1:100000,1);
y1 = data1(1:1:100000,2);

data2=importdata('R_test_off_2_4_gnd');
x2 = data2(1:1:100000,1);
y2 = data2(1:1:100000,2);


y = y1 - y2;

y = y.*1e5;
y = y.*y.*R;
off_chip = off_chip + mean(y)
