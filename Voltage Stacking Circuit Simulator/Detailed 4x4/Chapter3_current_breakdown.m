data1=importdata('BFS1_power.txt');

x1 = data1(1:1:5000-1,1);
x2 = data1(1:1:5000-1,2);
x3 = data1(1:1:5000-1,3);
x4 = data1(1:1:5000-1,4);
x5 = data1(1:1:5000-1,5);
x6 = data1(1:1:5000-1,6);
x7 = data1(1:1:5000-1,7);
x8 = data1(1:1:5000-1,8);
x9 = data1(1:1:5000-1,9);
x10 = data1(1:1:5000-1,10);
x11 = data1(1:1:5000-1,11);
x12 = data1(1:1:5000-1,12);
x13 = data1(1:1:5000-1,13);
x14 = data1(1:1:5000-1,14);
x15 = data1(1:1:5000-1,15);
x16 = data1(1:1:5000-1,16);


I_g = (x1 + x2 + x3 + x4 + x5 + x6 + x7 + x8 + x9 + x10 + x11 + x12 + x13 + x14 + x15 + x16)./16;

I_st_1 = (x1 + x5 + x9 + x13)./4  - I_g;
I_st_2 = (x2 + x6 + x10 + x14)./4  - I_g;
I_st_3 = (x3 + x7 + x11 + x15)./4  - I_g;
I_st_4 = (x4 + x8 + x12 + x16)./4  - I_g;



I_r_1 = x1 - I_st_1 - I_g;
I_r_2 = x2 - I_st_2 - I_g;
I_r_3 = x3 - I_st_3 - I_g;
I_r_4 = x4 - I_st_4 - I_g;
I_r_5 = x5 - I_st_1 - I_g;
I_r_6 = x6 - I_st_2 - I_g;
I_r_7 = x7 - I_st_3 - I_g;
I_r_8 = x8 - I_st_4 - I_g;
I_r_9 = x9 - I_st_1 - I_g;
I_r_10 = x10 - I_st_2 - I_g;
I_r_11 = x11 - I_st_3 - I_g;
I_r_12 = x12 - I_st_4 - I_g;
I_r_13 = x13 - I_st_1 - I_g;
I_r_14 = x14 - I_st_2 - I_g;
I_r_15 = x15 - I_st_3 - I_g;
I_r_16 = x16 - I_st_4 - I_g;

x = -6:0.5:6;





SM1 = 0.*[I_g I_g I_g I_g I_g I_g]./6 + 0.*[I_st_1 I_st_1 I_st_1 I_st_1 I_st_1 I_st_1]./6 + 0.01.*[I_r_1 I_r_1 I_r_1 I_r_1 I_r_1 I_r_1]./6;
SM2 = 0.*[I_g I_g I_g I_g I_g I_g]./6 + 0.*[I_st_2 I_st_2 I_st_2 I_st_2 I_st_2 I_st_2]./6 + 0.01.*[I_r_2 I_r_2 I_r_2 I_r_2 I_r_2 I_r_2]./6;
SM3 = 0.*[I_g I_g I_g I_g I_g I_g]./6 + 0.*[I_st_3 I_st_3 I_st_3 I_st_3 I_st_3 I_st_3]./6 + 0.01.*[I_r_3 I_r_3 I_r_3 I_r_3 I_r_3 I_r_3]./6;
SM4 = 0.*[I_g I_g I_g I_g I_g I_g]./6 + 0.*[I_st_4 I_st_4 I_st_4 I_st_4 I_st_4 I_st_4]./6 + 0.01.*[I_r_4 I_r_4 I_r_4 I_r_4 I_r_4 I_r_4]./6;
SM5 = 0.*[I_g I_g I_g I_g I_g I_g]./6 + 0.*[I_st_1 I_st_1 I_st_1 I_st_1 I_st_1 I_st_1]./6 + 0.01.*[I_r_5 I_r_5 I_r_5 I_r_5 I_r_5 I_r_5]./6;
SM6 = 0.*[I_g I_g I_g I_g I_g I_g]./6 + 0.*[I_st_2 I_st_2 I_st_2 I_st_2 I_st_2 I_st_2]./6 + 0.01.*[I_r_6 I_r_6 I_r_6 I_r_6 I_r_6 I_r_6]./6;
SM7 = 0.*[I_g I_g I_g I_g I_g I_g]./6 + 0.*[I_st_3 I_st_3 I_st_3 I_st_3 I_st_3 I_st_3]./6 + 0.01.*[I_r_7 I_r_7 I_r_7 I_r_7 I_r_7 I_r_7]./6;
SM8 = 0.*[I_g I_g I_g I_g I_g I_g]./6 + 0.*[I_st_4 I_st_4 I_st_4 I_st_4 I_st_4 I_st_4]./6 + 0.01.*[I_r_8 I_r_8 I_r_8 I_r_8 I_r_8 I_r_8]./6;
SM9 = 0.*[I_g I_g I_g I_g I_g I_g]./6 + 0.*[I_st_1 I_st_1 I_st_1 I_st_1 I_st_1 I_st_1]./6 + 0.01.*[I_r_9 I_r_9 I_r_9 I_r_9 I_r_9 I_r_9]./6;
SM10 = 0.*[I_g I_g I_g I_g I_g I_g]./6 + 0.*[I_st_2 I_st_2 I_st_2 I_st_2 I_st_2 I_st_2]./6 + 0.01.*[I_r_10 I_r_10 I_r_10 I_r_10 I_r_10 I_r_10]./6;
SM11 = 0.*[I_g I_g I_g I_g I_g I_g]./6 + 0.*[I_st_3 I_st_3 I_st_3 I_st_3 I_st_3 I_st_3]./6 + 0.01.*[I_r_11 I_r_11 I_r_11 I_r_11 I_r_11 I_r_11]./6;
SM12 = 0.*[I_g I_g I_g I_g I_g I_g]./6 + 0.*[I_st_4 I_st_4 I_st_4 I_st_4 I_st_4 I_st_4]./6 + 0.01.*[I_r_12 I_r_12 I_r_12 I_r_12 I_r_12 I_r_12]./6;
SM13 = 0.*[I_g I_g I_g I_g I_g I_g]./6 + 0.*[I_st_1 I_st_1 I_st_1 I_st_1 I_st_1 I_st_1]./6 + 0.01.*[I_r_13 I_r_13 I_r_13 I_r_13 I_r_13 I_r_13]./6;
SM14 = 0.*[I_g I_g I_g I_g I_g I_g]./6 + 0.*[I_st_2 I_st_2 I_st_2 I_st_2 I_st_2 I_st_2]./6 + 0.01.*[I_r_14 I_r_14 I_r_14 I_r_14 I_r_14 I_r_14]./6;
SM15 = 0.*[I_g I_g I_g I_g I_g I_g]./6 + 0.*[I_st_3 I_st_3 I_st_3 I_st_3 I_st_3 I_st_3]./6 + 0.01.*[I_r_15 I_r_15 I_r_15 I_r_15 I_r_15 I_r_15]./6;
SM16 = 0.*[I_g I_g I_g I_g I_g I_g]./6 + 0.*[I_st_4 I_st_4 I_st_4 I_st_4 I_st_4 I_st_4]./6 + 0.01.*[I_r_16 I_r_16 I_r_16 I_r_16 I_r_16 I_r_16]./6;




P = [SM1 SM2 SM3 SM4 SM5 SM6 SM7 SM8 SM9 SM10 SM11 SM12 SM13 SM14 SM15 SM16];




csvwrite('global_100K.txt',P)