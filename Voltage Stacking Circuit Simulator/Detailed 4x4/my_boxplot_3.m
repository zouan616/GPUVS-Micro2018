clear
length1 = 80000;
start1 = 20000;

length2 = 70000;
start2 = 20000;

length3 = 60000;
start3 = 20000;

P11 = [];
P12 = [];
P13 = [];
P21 = [];
P22 = [];
P23 = [];
P31 = [];
P32 = [];
P33 = [];
P41 = [];
P42 = [];
P43 = [];
P51 = [];
P52 = [];
P53 = [];
P61 = [];
P62 = [];
P63 = [];
P71 = [];
P72 = [];
P73 = [];
P81 = [];
P82 = [];
P83 = [];
P91 = [];
P92 = [];
P93 = [];
P101 = [];
P102 = [];
P103 = [];

P131 = [];
P132 = [];
P133 = [];

%data11=importdata('SM9_1_1');
%data110=importdata('SM9_gnd_1_1');
%P11 = data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2);
%data12=importdata('SM9_1_2');
%data120=importdata('SM9_gnd_1_2');
%P12 = data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2);

%-----------------------------------------------------------------------------------
data11=importdata('SM1_1_1');
data110=importdata('SM1_gnd_1_1');
P11 = [P11; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM1_1_2');
data120=importdata('SM1_gnd_1_2');
P12 = [P12; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM1_1_3');
data130=importdata('SM1_gnd_1_3');
P13 = [P13; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];


data11=importdata('SM2_1_1');
data110=importdata('SM2_gnd_1_1');
P11 = [P11; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM2_1_2');
data120=importdata('SM2_gnd_1_2');
P12 = [P12; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM2_1_3');
data130=importdata('SM2_gnd_1_3');
P13 = [P13; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];

data11=importdata('SM3_1_1');
data110=importdata('SM3_gnd_1_1');
P11 = [P11; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM3_1_2');
data120=importdata('SM3_gnd_1_2');
P12 = [P12; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM3_1_3');
data130=importdata('SM3_gnd_1_3');
P13 = [P13; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];

data11=importdata('SM4_1_1');
data110=importdata('SM4_gnd_1_1');
P11 = [P11; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM4_1_2');
data120=importdata('SM4_gnd_1_2');
P12 = [P12; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM4_1_3');
data130=importdata('SM4_gnd_1_3');
P13 = [P13; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];


data11=importdata('SM5_1_1');
data110=importdata('SM5_gnd_1_1');
P11 = [P11; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM5_1_2');
data120=importdata('SM5_gnd_1_2');
P12 = [P12; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM5_1_3');
data130=importdata('SM5_gnd_1_3');
P13 = [P13; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];

data11=importdata('SM6_1_1');
data110=importdata('SM6_gnd_1_1');
P11 = [P11; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM6_1_2');
data120=importdata('SM6_gnd_1_2');
P12 = [P12; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM6_1_3');
data130=importdata('SM6_gnd_1_3');
P13 = [P13; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];

data11=importdata('SM7_1_1');
data110=importdata('SM7_gnd_1_1');
P11 = [P11; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM7_1_2');
data120=importdata('SM7_gnd_1_2');
P12 = [P12; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM7_1_3');
data130=importdata('SM7_gnd_1_3');
P13 = [P13; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];

data11=importdata('SM8_1_1');
data110=importdata('SM8_gnd_1_1');
P11 = [P11; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM8_1_2');
data120=importdata('SM8_gnd_1_2');
P12 = [P12; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM8_1_3');
data130=importdata('SM8_gnd_1_3');
P13 = [P13; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];

data11=importdata('SM9_1_1');
data110=importdata('SM9_gnd_1_1');
P11 = [P11; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM9_1_2');
data120=importdata('SM9_gnd_1_2');
P12 = [P12; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM9_1_3');
data130=importdata('SM9_gnd_1_3');
P13 = [P13; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];


data11=importdata('SM10_1_1');
data110=importdata('SM10_gnd_1_1');
P11 = [P11; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM10_1_2');
data120=importdata('SM10_gnd_1_2');
P12 = [P12; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM10_1_3');
data130=importdata('SM10_gnd_1_3');
P13 = [P13; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];


data11=importdata('SM11_1_1');
data110=importdata('SM11_gnd_1_1');
P11 = [P11; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM11_1_2');
data120=importdata('SM11_gnd_1_2');
P12 = [P12; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM11_1_3');
data130=importdata('SM11_gnd_1_3');
P13 = [P13; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];

data11=importdata('SM12_1_1');
data110=importdata('SM12_gnd_1_1');
P11 = [P11; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM12_1_2');
data120=importdata('SM12_gnd_1_2');
P12 = [P12; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM12_1_3');
data130=importdata('SM12_gnd_1_3');
P13 = [P13; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];

data11=importdata('SM13_1_1');
data110=importdata('SM13_gnd_1_1');
P11 = [P11; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM13_1_2');
data120=importdata('SM13_gnd_1_2');
P12 = [P12; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM13_1_3');
data130=importdata('SM13_gnd_1_3');
P13 = [P13; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];

data11=importdata('SM14_1_1');
data110=importdata('SM14_gnd_1_1');
P11 = [P11; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM14_1_2');
data120=importdata('SM14_gnd_1_2');
P12 = [P12; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM14_1_3');
data130=importdata('SM14_gnd_1_3');
P13 = [P13; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];

data11=importdata('SM15_1_1');
data110=importdata('SM15_gnd_1_1');
P11 = [P11; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM15_1_2');
data120=importdata('SM15_gnd_1_2');
P12 = [P12; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM15_1_3');
data130=importdata('SM15_gnd_1_3');
P13 = [P13; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];

data11=importdata('SM16_1_1');
data110=importdata('SM16_gnd_1_1');
P11 = [P11; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM16_1_2');
data120=importdata('SM16_gnd_1_2');
P12 = [P12; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM16_1_3');
data130=importdata('SM16_gnd_1_3');
P13 = [P13; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];
%------------------------------------------------------------------------------------------------------------

data11=importdata('SM1_2_1');
data110=importdata('SM1_gnd_2_1');
P21 = [P21; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM1_2_2');
data120=importdata('SM1_gnd_2_2');
P22 = [P22; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM1_2_3');
data130=importdata('SM1_gnd_2_3');
P23 = [P23; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];


data11=importdata('SM2_2_1');
data110=importdata('SM2_gnd_2_1');
P21 = [P21; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM2_2_2');
data120=importdata('SM2_gnd_2_2');
P22 = [P22; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM2_2_3');
data130=importdata('SM2_gnd_2_3');
P23 = [P23; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];

data11=importdata('SM3_2_1');
data110=importdata('SM3_gnd_2_1');
P21 = [P21; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM3_2_2');
data120=importdata('SM3_gnd_2_2');
P22 = [P22; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM3_2_3');
data130=importdata('SM3_gnd_2_3');
P23 = [P23; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];

data11=importdata('SM4_2_1');
data110=importdata('SM4_gnd_2_1');
P21 = [P21; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM4_2_2');
data120=importdata('SM4_gnd_2_2');
P22 = [P22; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM4_2_3');
data130=importdata('SM4_gnd_2_3');
P23 = [P23; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];

data11=importdata('SM5_2_1');
data110=importdata('SM5_gnd_2_1');
P21 = [P21; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM5_2_2');
data120=importdata('SM5_gnd_2_2');
P22 = [P22; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM5_2_3');
data130=importdata('SM5_gnd_2_3');
P23 = [P23; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];


data11=importdata('SM6_2_1');
data110=importdata('SM6_gnd_2_1');
P21 = [P21; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM6_2_2');
data120=importdata('SM6_gnd_2_2');
P22 = [P22; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM6_2_3');
data130=importdata('SM6_gnd_2_3');
P23 = [P23; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];


data11=importdata('SM7_2_1');
data110=importdata('SM7_gnd_2_1');
P21 = [P21; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM7_2_2');
data120=importdata('SM7_gnd_2_2');
P22 = [P22; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM7_2_3');
data130=importdata('SM7_gnd_2_3');
P23 = [P23; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];


data11=importdata('SM8_2_1');
data110=importdata('SM8_gnd_2_1');
P21 = [P21; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM8_2_2');
data120=importdata('SM8_gnd_2_2');
P22 = [P22; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM8_2_3');
data130=importdata('SM8_gnd_2_3');
P23 = [P23; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];

data11=importdata('SM9_2_1');
data110=importdata('SM9_gnd_2_1');
P21 = [P21; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM9_2_2');
data120=importdata('SM9_gnd_2_2');
P22 = [P22; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM9_2_3');
data130=importdata('SM9_gnd_2_3');
P23 = [P23; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];

data11=importdata('SM10_2_1');
data110=importdata('SM10_gnd_2_1');
P21 = [P21; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM10_2_2');
data120=importdata('SM10_gnd_2_2');
P22 = [P22; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM10_2_3');
data130=importdata('SM10_gnd_2_3');
P23 = [P23; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];

data11=importdata('SM11_2_1');
data110=importdata('SM11_gnd_2_1');
P21 = [P21; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM11_2_2');
data120=importdata('SM11_gnd_2_2');
P22 = [P22; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM11_2_3');
data130=importdata('SM11_gnd_2_3');
P23 = [P23; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];


data11=importdata('SM12_2_1');
data110=importdata('SM12_gnd_2_1');
P21 = [P21; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM12_2_2');
data120=importdata('SM12_gnd_2_2');
P22 = [P22; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM12_2_3');
data130=importdata('SM12_gnd_2_3');
P23 = [P23; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];

data11=importdata('SM13_2_1');
data110=importdata('SM13_gnd_2_1');
P21 = [P21; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM13_2_2');
data120=importdata('SM13_gnd_2_2');
P22 = [P22; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM13_2_3');
data130=importdata('SM13_gnd_2_3');
P23 = [P23; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];

data11=importdata('SM14_2_1');
data110=importdata('SM14_gnd_2_1');
P21 = [P21; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM14_2_2');
data120=importdata('SM14_gnd_2_2');
P22 = [P22; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM14_2_3');
data130=importdata('SM14_gnd_2_3');
P23 = [P23; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];

data11=importdata('SM15_2_1');
data110=importdata('SM15_gnd_2_1');
P21 = [P21; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM15_2_2');
data120=importdata('SM15_gnd_2_2');
P22 = [P22; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM15_2_3');
data130=importdata('SM15_gnd_2_3');
P23 = [P23; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];

data11=importdata('SM16_2_1');
data110=importdata('SM16_gnd_2_1');
P21 = [P21; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM16_2_2');
data120=importdata('SM16_gnd_2_2');
P22 = [P22; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data13=importdata('SM16_2_3');
data130=importdata('SM16_gnd_2_3');
P23 = [P23; data13(start3:1:(start3+length3),2) - data130(start3:1:(start3+length3),2)];

%------------------------------------------------------------------------------------------------------------
data11=importdata('SM1_3_1');
data110=importdata('SM1_gnd_3_1');
P31 = [P31; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM1_3_2');
data120=importdata('SM1_gnd_3_2');
P32 = [P32; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM1_3_3');
data120=importdata('SM1_gnd_3_3');
P33 = [P33; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM2_3_1');
data110=importdata('SM2_gnd_3_1');
P31 = [P31; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM2_3_2');
data120=importdata('SM2_gnd_3_2');
P32 = [P32; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM2_3_3');
data120=importdata('SM2_gnd_3_3');
P33 = [P33; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM3_3_1');
data110=importdata('SM3_gnd_3_1');
P31 = [P31; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM3_3_2');
data120=importdata('SM3_gnd_3_2');
P32 = [P32; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM3_3_3');
data120=importdata('SM3_gnd_3_3');
P33 = [P33; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM4_3_1');
data110=importdata('SM4_gnd_3_1');
P31 = [P31; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM4_3_2');
data120=importdata('SM4_gnd_3_2');
P32 = [P32; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM4_3_3');
data120=importdata('SM4_gnd_3_3');
P33 = [P33; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM5_3_1');
data110=importdata('SM5_gnd_3_1');
P31 = [P31; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM5_3_2');
data120=importdata('SM5_gnd_3_2');
P32 = [P32; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM5_3_3');
data120=importdata('SM5_gnd_3_3');
P33 = [P33; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM6_3_1');
data110=importdata('SM6_gnd_3_1');
P31 = [P31; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM6_3_2');
data120=importdata('SM6_gnd_3_2');
P32 = [P32; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM6_3_3');
data120=importdata('SM6_gnd_3_3');
P33 = [P33; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM7_3_1');
data110=importdata('SM7_gnd_3_1');
P31 = [P31; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM7_3_2');
data120=importdata('SM7_gnd_3_2');
P32 = [P32; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM7_3_3');
data120=importdata('SM7_gnd_3_3');
P33 = [P33; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM8_3_1');
data110=importdata('SM8_gnd_3_1');
P31 = [P31; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM8_3_2');
data120=importdata('SM8_gnd_3_2');
P32 = [P32; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM8_3_3');
data120=importdata('SM8_gnd_3_3');
P33 = [P33; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM9_3_1');
data110=importdata('SM9_gnd_3_1');
P31 = [P31; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM9_3_2');
data120=importdata('SM9_gnd_3_2');
P32 = [P32; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM9_3_3');
data120=importdata('SM9_gnd_3_3');
P33 = [P33; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM10_3_1');
data110=importdata('SM10_gnd_3_1');
P31 = [P31; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM10_3_2');
data120=importdata('SM10_gnd_3_2');
P32 = [P32; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM10_3_3');
data120=importdata('SM10_gnd_3_3');
P33 = [P33; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM11_3_1');
data110=importdata('SM11_gnd_3_1');
P31 = [P31; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM11_3_2');
data120=importdata('SM11_gnd_3_2');
P32 = [P32; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM11_3_3');
data120=importdata('SM11_gnd_3_3');
P33 = [P33; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM12_3_1');
data110=importdata('SM12_gnd_3_1');
P31 = [P31; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM12_3_2');
data120=importdata('SM12_gnd_3_2');
P32 = [P32; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM12_3_3');
data120=importdata('SM12_gnd_3_3');
P33 = [P33; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM13_3_1');
data110=importdata('SM13_gnd_3_1');
P31 = [P31; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM13_3_2');
data120=importdata('SM13_gnd_3_2');
P32 = [P32; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM13_3_3');
data120=importdata('SM13_gnd_3_3');
P33 = [P33; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM14_3_1');
data110=importdata('SM14_gnd_3_1');
P31 = [P31; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM14_3_2');
data120=importdata('SM14_gnd_3_2');
P32 = [P32; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM14_3_3');
data120=importdata('SM14_gnd_3_3');
P33 = [P33; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM15_3_1');
data110=importdata('SM15_gnd_3_1');
P31 = [P31; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM15_3_2');
data120=importdata('SM15_gnd_3_2');
P32 = [P32; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM15_3_3');
data120=importdata('SM15_gnd_3_3');
P33 = [P33; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM16_3_1');
data110=importdata('SM16_gnd_3_1');
P31 = [P31; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM16_3_2');
data120=importdata('SM16_gnd_3_2');
P32 = [P32; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM16_3_3');
data120=importdata('SM16_gnd_3_3');
P33 = [P33; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

%------------------------------------------------------------------------------------------------------------
data11=importdata('SM1_4_1');
data110=importdata('SM1_gnd_4_1');
P41 = [P41; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM1_4_2');
data120=importdata('SM1_gnd_4_2');
P42 = [P42; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM1_4_3');
data120=importdata('SM1_gnd_4_3');
P43 = [P43; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM2_4_1');
data110=importdata('SM2_gnd_4_1');
P41 = [P41; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM3_4_2');
data120=importdata('SM2_gnd_4_2');
P42 = [P42; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM2_4_3');
data120=importdata('SM2_gnd_4_3');
P43 = [P43; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM3_4_1');
data110=importdata('SM3_gnd_4_1');
P41 = [P41; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM3_4_2');
data120=importdata('SM3_gnd_4_2');
P42 = [P42; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM3_4_3');
data120=importdata('SM3_gnd_4_3');
P43 = [P43; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM4_4_1');
data110=importdata('SM4_gnd_4_1');
P41 = [P41; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM4_4_2');
data120=importdata('SM4_gnd_4_2');
P42 = [P42; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM4_4_3');
data120=importdata('SM4_gnd_4_3');
P43 = [P43; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM5_4_1');
data110=importdata('SM5_gnd_4_1');
P41 = [P41; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM5_4_2');
data120=importdata('SM5_gnd_4_2');
P42 = [P42; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM5_4_3');
data120=importdata('SM5_gnd_4_3');
P43 = [P43; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM6_4_1');
data110=importdata('SM6_gnd_4_1');
P41 = [P41; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM6_4_2');
data120=importdata('SM6_gnd_4_2');
P42 = [P42; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM6_4_3');
data120=importdata('SM6_gnd_4_3');
P43 = [P43; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM7_4_1');
data110=importdata('SM7_gnd_4_1');
P41 = [P41; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM7_4_2');
data120=importdata('SM7_gnd_4_2');
P42 = [P42; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM7_4_3');
data120=importdata('SM7_gnd_4_3');
P43 = [P43; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM8_4_1');
data110=importdata('SM8_gnd_4_1');
P41 = [P41; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM8_4_2');
data120=importdata('SM8_gnd_4_2');
P42 = [P42; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM8_4_3');
data120=importdata('SM8_gnd_4_3');
P43 = [P43; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM9_4_1');
data110=importdata('SM9_gnd_4_1');
P41 = [P41; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM9_4_2');
data120=importdata('SM9_gnd_4_2');
P42 = [P42; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM9_4_3');
data120=importdata('SM9_gnd_4_3');
P43 = [P43; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM10_4_1');
data110=importdata('SM10_gnd_4_1');
P41 = [P41; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM10_4_2');
data120=importdata('SM10_gnd_4_2');
P42 = [P42; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM10_4_3');
data120=importdata('SM10_gnd_4_3');
P43 = [P43; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM11_4_1');
data110=importdata('SM11_gnd_4_1');
P41 = [P41; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM11_4_2');
data120=importdata('SM11_gnd_4_2');
P42 = [P42; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM11_4_3');
data120=importdata('SM11_gnd_4_3');
P43 = [P43; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM12_4_1');
data110=importdata('SM12_gnd_4_1');
P41 = [P41; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM12_4_2');
data120=importdata('SM12_gnd_4_2');
P42 = [P42; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM12_4_3');
data120=importdata('SM12_gnd_4_3');
P43 = [P43; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM13_4_1');
data110=importdata('SM13_gnd_4_1');
P41 = [P41; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM13_4_2');
data120=importdata('SM13_gnd_4_2');
P42 = [P42; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM13_4_3');
data120=importdata('SM13_gnd_4_3');
P43 = [P43; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM14_4_1');
data110=importdata('SM14_gnd_4_1');
P41 = [P41; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM14_4_2');
data120=importdata('SM14_gnd_4_2');
P42 = [P42; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM14_4_3');
data120=importdata('SM14_gnd_4_3');
P43 = [P43; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM15_4_1');
data110=importdata('SM15_gnd_4_1');
P41 = [P41; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM15_4_2');
data120=importdata('SM15_gnd_4_2');
P42 = [P42; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM15_4_3');
data120=importdata('SM15_gnd_4_3');
P43 = [P43; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM16_4_1');
data110=importdata('SM16_gnd_4_1');
P41 = [P41; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM16_4_2');
data120=importdata('SM16_gnd_4_2');
P42 = [P42; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM16_4_3');
data120=importdata('SM16_gnd_4_3');
P43 = [P43; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

%------------------------------------------------------------------------------------------------------------
data11=importdata('SM1_5_1');
data110=importdata('SM1_gnd_5_1');
P51 = [P51; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM1_5_2');
data120=importdata('SM1_gnd_5_2');
P52 = [P52; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM1_5_3');
data120=importdata('SM1_gnd_5_3');
P53 = [P53; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM2_5_1');
data110=importdata('SM2_gnd_5_1');
P51 = [P51; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM2_5_2');
data120=importdata('SM2_gnd_5_2');
P52 = [P52; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM2_5_3');
data120=importdata('SM2_gnd_5_3');
P53 = [P53; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM3_5_1');
data110=importdata('SM3_gnd_5_1');
P51 = [P51; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM3_5_2');
data120=importdata('SM3_gnd_5_2');
P52 = [P52; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM3_5_3');
data120=importdata('SM3_gnd_5_3');
P53 = [P53; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM4_5_1');
data110=importdata('SM4_gnd_5_1');
P51 = [P51; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM4_5_2');
data120=importdata('SM4_gnd_5_2');
P52 = [P52; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM4_5_3');
data120=importdata('SM4_gnd_5_3');
P53 = [P53; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM5_5_1');
data110=importdata('SM5_gnd_5_1');
P51 = [P51; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM5_5_2');
data120=importdata('SM5_gnd_5_2');
P52 = [P52; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM5_5_3');
data120=importdata('SM5_gnd_5_3');
P53 = [P53; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM6_5_1');
data110=importdata('SM6_gnd_5_1');
P51 = [P51; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM6_5_2');
data120=importdata('SM6_gnd_5_2');
P52 = [P52; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM6_5_3');
data120=importdata('SM6_gnd_5_3');
P53 = [P53; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM7_5_1');
data110=importdata('SM7_gnd_5_1');
P51 = [P51; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM7_5_2');
data120=importdata('SM7_gnd_5_2');
P52 = [P52; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM7_5_3');
data120=importdata('SM7_gnd_5_3');
P53 = [P53; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM8_5_1');
data110=importdata('SM8_gnd_5_1');
P51 = [P51; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM8_5_2');
data120=importdata('SM8_gnd_5_2');
P52 = [P52; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM8_5_3');
data120=importdata('SM8_gnd_5_3');
P53 = [P53; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM9_5_1');
data110=importdata('SM9_gnd_5_1');
P51 = [P51; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM9_5_2');
data120=importdata('SM9_gnd_5_2');
P52 = [P52; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM9_5_3');
data120=importdata('SM9_gnd_5_3');
P53 = [P53; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM10_5_1');
data110=importdata('SM10_gnd_5_1');
P51 = [P51; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM10_5_2');
data120=importdata('SM10_gnd_5_2');
P52 = [P52; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM10_5_3');
data120=importdata('SM10_gnd_5_3');
P53 = [P53; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM11_5_1');
data110=importdata('SM11_gnd_5_1');
P51 = [P51; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM11_5_2');
data120=importdata('SM11_gnd_5_2');
P52 = [P52; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM11_5_3');
data120=importdata('SM11_gnd_5_3');
P53 = [P53; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM12_5_1');
data110=importdata('SM12_gnd_5_1');
P51 = [P51; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM12_5_2');
data120=importdata('SM12_gnd_5_2');
P52 = [P52; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM12_5_3');
data120=importdata('SM12_gnd_5_3');
P53 = [P53; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM13_5_1');
data110=importdata('SM13_gnd_5_1');
P51 = [P51; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM13_5_2');
data120=importdata('SM13_gnd_5_2');
P52 = [P52; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM13_5_3');
data120=importdata('SM13_gnd_5_3');
P53 = [P53; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM14_5_1');
data110=importdata('SM14_gnd_5_1');
P51 = [P51; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM14_5_2');
data120=importdata('SM14_gnd_5_2');
P52 = [P52; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM14_5_3');
data120=importdata('SM14_gnd_5_3');
P53 = [P53; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM15_5_1');
data110=importdata('SM15_gnd_5_1');
P51 = [P51; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM15_5_2');
data120=importdata('SM15_gnd_5_2');
P52 = [P52; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM15_5_3');
data120=importdata('SM15_gnd_5_3');
P53 = [P53; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM16_5_1');
data110=importdata('SM16_gnd_5_1');
P51 = [P51; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM16_5_2');
data120=importdata('SM16_gnd_5_2');
P52 = [P52; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM16_5_3');
data120=importdata('SM16_gnd_5_3');
P53 = [P53; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

%------------------------------------------------------------------------------------------------------------
data11=importdata('SM1_6_1');
data110=importdata('SM1_gnd_6_1');
P61 = [P61; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM1_6_2');
data120=importdata('SM1_gnd_6_2');
P62 = [P62; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM1_6_3');
data120=importdata('SM1_gnd_6_3');
P63 = [P63; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM2_6_1');
data110=importdata('SM2_gnd_6_1');
P61 = [P61; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM2_6_2');
data120=importdata('SM2_gnd_6_2');
P62 = [P62; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM2_6_3');
data120=importdata('SM2_gnd_6_3');
P63 = [P63; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM3_6_1');
data110=importdata('SM3_gnd_6_1');
P61 = [P61; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM3_6_2');
data120=importdata('SM3_gnd_6_2');
P62 = [P62; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM3_6_3');
data120=importdata('SM3_gnd_6_3');
P63 = [P63; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM4_6_1');
data110=importdata('SM4_gnd_6_1');
P61 = [P61; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM4_6_2');
data120=importdata('SM4_gnd_6_2');
P62 = [P62; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM4_6_3');
data120=importdata('SM4_gnd_6_3');
P63 = [P63; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM5_6_1');
data110=importdata('SM5_gnd_6_1');
P61 = [P61; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM5_6_2');
data120=importdata('SM5_gnd_6_2');
P62 = [P62; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM5_6_3');
data120=importdata('SM5_gnd_6_3');
P63 = [P63; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM6_6_1');
data110=importdata('SM6_gnd_6_1');
P61 = [P61; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM6_6_2');
data120=importdata('SM6_gnd_6_2');
P62 = [P62; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM6_6_3');
data120=importdata('SM6_gnd_6_3');
P63 = [P63; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM7_6_1');
data110=importdata('SM7_gnd_6_1');
P61 = [P61; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM7_6_2');
data120=importdata('SM7_gnd_6_2');
P62 = [P62; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM7_6_3');
data120=importdata('SM7_gnd_6_3');
P63 = [P63; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM8_6_1');
data110=importdata('SM8_gnd_6_1');
P61 = [P61; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM8_6_2');
data120=importdata('SM8_gnd_6_2');
P62 = [P62; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM8_6_3');
data120=importdata('SM8_gnd_6_3');
P63 = [P63; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM9_6_1');
data110=importdata('SM9_gnd_6_1');
P61 = [P61; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM9_6_2');
data120=importdata('SM9_gnd_6_2');
P62 = [P62; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM9_6_3');
data120=importdata('SM9_gnd_6_3');
P63 = [P63; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM10_6_1');
data110=importdata('SM10_gnd_6_1');
P61 = [P61; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM10_6_2');
data120=importdata('SM10_gnd_6_2');
P62 = [P62; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM10_6_3');
data120=importdata('SM10_gnd_6_3');
P63 = [P63; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM11_6_1');
data110=importdata('SM11_gnd_6_1');
P61 = [P61; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM11_6_2');
data120=importdata('SM11_gnd_6_2');
P62 = [P62; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM11_6_3');
data120=importdata('SM11_gnd_6_3');
P63 = [P63; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM12_6_1');
data110=importdata('SM12_gnd_6_1');
P61 = [P61; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM12_6_2');
data120=importdata('SM12_gnd_6_2');
P62 = [P62; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM12_6_3');
data120=importdata('SM12_gnd_6_3');
P63 = [P63; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM13_6_1');
data110=importdata('SM13_gnd_6_1');
P61 = [P61; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM13_6_2');
data120=importdata('SM13_gnd_6_2');
P62 = [P62; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM13_6_3');
data120=importdata('SM13_gnd_6_3');
P63 = [P63; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM14_6_1');
data110=importdata('SM14_gnd_6_1');
P61 = [P61; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM14_6_2');
data120=importdata('SM14_gnd_6_2');
P62 = [P62; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM14_6_3');
data120=importdata('SM14_gnd_6_3');
P63 = [P63; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM15_6_1');
data110=importdata('SM15_gnd_6_1');
P61 = [P61; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM15_6_2');
data120=importdata('SM15_gnd_6_2');
P62 = [P62; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM15_6_3');
data120=importdata('SM15_gnd_6_3');
P63 = [P63; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM16_6_1');
data110=importdata('SM16_gnd_6_1');
P61 = [P61; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM16_6_2');
data120=importdata('SM16_gnd_6_2');
P62 = [P62; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM16_6_3');
data120=importdata('SM16_gnd_6_3');
P63 = [P63; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];
%------------------------------------------------------------------------------------------------------------
data11=importdata('SM1_7_1');
data110=importdata('SM1_gnd_7_1');
P71 = [P71; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM1_7_2');
data120=importdata('SM1_gnd_7_2');
P72 = [P72; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM1_7_3');
data120=importdata('SM1_gnd_7_3');
P73 = [P73; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM2_7_1');
data110=importdata('SM2_gnd_7_1');
P71 = [P71; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM2_7_2');
data120=importdata('SM2_gnd_7_2');
P72 = [P72; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM2_7_3');
data120=importdata('SM2_gnd_7_3');
P73 = [P73; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM3_7_1');
data110=importdata('SM3_gnd_7_1');
P71 = [P71; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM3_7_2');
data120=importdata('SM3_gnd_7_2');
P72 = [P72; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM3_7_3');
data120=importdata('SM3_gnd_7_3');
P73 = [P73; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM4_7_1');
data110=importdata('SM4_gnd_7_1');
P71 = [P71; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM4_7_2');
data120=importdata('SM4_gnd_7_2');
P72 = [P72; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM4_7_3');
data120=importdata('SM4_gnd_7_3');
P73 = [P73; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM5_7_1');
data110=importdata('SM5_gnd_7_1');
P71 = [P71; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM5_7_2');
data120=importdata('SM5_gnd_7_2');
P72 = [P72; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM5_7_3');
data120=importdata('SM5_gnd_7_3');
P73 = [P73; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];



data11=importdata('SM6_7_1');
data110=importdata('SM6_gnd_7_1');
P71 = [P71; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM6_7_2');
data120=importdata('SM6_gnd_7_2');
P72 = [P72; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM6_7_3');
data120=importdata('SM6_gnd_7_3');
P73 = [P73; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM7_7_1');
data110=importdata('SM7_gnd_7_1');
P71 = [P71; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM7_7_2');
data120=importdata('SM7_gnd_7_2');
P72 = [P72; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM7_7_3');
data120=importdata('SM7_gnd_7_3');
P73 = [P73; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM8_7_1');
data110=importdata('SM8_gnd_7_1');
P71 = [P71; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM8_7_2');
data120=importdata('SM8_gnd_7_2');
P72 = [P72; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM8_7_3');
data120=importdata('SM8_gnd_7_3');
P73 = [P73; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM9_7_1');
data110=importdata('SM9_gnd_7_1');
P71 = [P71; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM9_7_2');
data120=importdata('SM9_gnd_7_2');
P72 = [P72; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM9_7_3');
data120=importdata('SM9_gnd_7_3');
P73 = [P73; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM10_7_1');
data110=importdata('SM10_gnd_7_1');
P71 = [P71; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM10_7_2');
data120=importdata('SM10_gnd_7_2');
P72 = [P72; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM10_7_3');
data120=importdata('SM10_gnd_7_3');
P73 = [P73; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM11_7_1');
data110=importdata('SM11_gnd_7_1');
P71 = [P71; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM11_7_2');
data120=importdata('SM11_gnd_7_2');
P72 = [P72; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM11_7_3');
data120=importdata('SM11_gnd_7_3');
P73 = [P73; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM12_7_1');
data110=importdata('SM12_gnd_7_1');
P71 = [P71; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM12_7_2');
data120=importdata('SM12_gnd_7_2');
P72 = [P72; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM12_7_3');
data120=importdata('SM12_gnd_7_3');
P73 = [P73; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM13_7_1');
data110=importdata('SM13_gnd_7_1');
P71 = [P71; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM13_7_2');
data120=importdata('SM13_gnd_7_2');
P72 = [P72; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM13_7_3');
data120=importdata('SM13_gnd_7_3');
P73 = [P73; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM14_7_1');
data110=importdata('SM14_gnd_7_1');
P71 = [P71; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM14_7_2');
data120=importdata('SM14_gnd_7_2');
P72 = [P72; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM14_7_3');
data120=importdata('SM14_gnd_7_3');
P73 = [P73; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM15_7_1');
data110=importdata('SM15_gnd_7_1');
P71 = [P71; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM15_7_2');
data120=importdata('SM15_gnd_7_2');
P72 = [P72; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM15_7_3');
data120=importdata('SM15_gnd_7_3');
P73 = [P73; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM16_7_1');
data110=importdata('SM16_gnd_7_1');
P71 = [P71; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM16_7_2');
data120=importdata('SM16_gnd_7_2');
P72 = [P72; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM16_7_3');
data120=importdata('SM16_gnd_7_3');
P73 = [P73; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];
%------------------------------------------------------------------------------------------------------------
data11=importdata('SM1_8_1');
data110=importdata('SM1_gnd_8_1');
P81 = [P81; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM1_8_2');
data120=importdata('SM1_gnd_8_2');
P82 = [P82; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM1_8_3');
data120=importdata('SM1_gnd_8_3');
P83 = [P83; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM2_8_1');
data110=importdata('SM2_gnd_8_1');
P81 = [P81; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM2_8_2');
data120=importdata('SM2_gnd_8_2');
P82 = [P82; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM2_8_3');
data120=importdata('SM2_gnd_8_3');
P83 = [P83; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM3_8_1');
data110=importdata('SM3_gnd_8_1');
P81 = [P81; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM3_8_2');
data120=importdata('SM3_gnd_8_2');
P82 = [P82; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM3_8_3');
data120=importdata('SM3_gnd_8_3');
P83 = [P83; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM4_8_1');
data110=importdata('SM4_gnd_8_1');
P81 = [P81; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM4_8_2');
data120=importdata('SM4_gnd_8_2');
P82 = [P82; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM4_8_3');
data120=importdata('SM4_gnd_8_3');
P83 = [P83; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM5_8_1');
data110=importdata('SM5_gnd_8_1');
P81 = [P81; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM5_8_2');
data120=importdata('SM5_gnd_8_2');
P82 = [P82; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM5_8_3');
data120=importdata('SM5_gnd_8_3');
P83 = [P83; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM6_8_1');
data110=importdata('SM6_gnd_8_1');
P81 = [P81; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM6_8_2');
data120=importdata('SM6_gnd_8_2');
P82 = [P82; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM6_8_3');
data120=importdata('SM6_gnd_8_3');
P83 = [P83; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM7_8_1');
data110=importdata('SM7_gnd_8_1');
P81 = [P81; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM7_8_2');
data120=importdata('SM7_gnd_8_2');
P82 = [P82; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM7_8_3');
data120=importdata('SM7_gnd_8_3');
P83 = [P83; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM8_8_1');
data110=importdata('SM8_gnd_8_1');
P81 = [P81; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM8_8_2');
data120=importdata('SM8_gnd_8_2');
P82 = [P82; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM8_8_3');
data120=importdata('SM8_gnd_8_3');
P83 = [P83; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM9_8_1');
data110=importdata('SM9_gnd_8_1');
P81 = [P81; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM9_8_2');
data120=importdata('SM9_gnd_8_2');
P82 = [P82; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM9_8_3');
data120=importdata('SM9_gnd_8_3');
P83 = [P83; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM10_8_1');
data110=importdata('SM10_gnd_8_1');
P81 = [P81; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM10_8_2');
data120=importdata('SM10_gnd_8_2');
P82 = [P82; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM10_8_3');
data120=importdata('SM10_gnd_8_3');
P83 = [P83; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM11_8_1');
data110=importdata('SM11_gnd_8_1');
P81 = [P81; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM11_8_2');
data120=importdata('SM11_gnd_8_2');
P82 = [P82; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM11_8_3');
data120=importdata('SM11_gnd_8_3');
P83 = [P83; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM12_8_1');
data110=importdata('SM12_gnd_8_1');
P81 = [P81; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM13_8_2');
data120=importdata('SM12_gnd_8_2');
P82 = [P82; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM12_8_3');
data120=importdata('SM12_gnd_8_3');
P83 = [P83; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM13_8_1');
data110=importdata('SM13_gnd_8_1');
P81 = [P81; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM13_8_2');
data120=importdata('SM13_gnd_8_2');
P82 = [P82; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM13_8_3');
data120=importdata('SM13_gnd_8_3');
P83 = [P83; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM14_8_1');
data110=importdata('SM14_gnd_8_1');
P81 = [P81; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM14_8_2');
data120=importdata('SM14_gnd_8_2');
P82 = [P82; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM14_8_3');
data120=importdata('SM14_gnd_8_3');
P83 = [P83; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM15_8_1');
data110=importdata('SM15_gnd_8_1');
P81 = [P81; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM15_8_2');
data120=importdata('SM15_gnd_8_2');
P82 = [P82; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM15_8_3');
data120=importdata('SM15_gnd_8_3');
P83 = [P83; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM16_8_1');
data110=importdata('SM16_gnd_8_1');
P81 = [P81; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM16_8_2');
data120=importdata('SM16_gnd_8_2');
P82 = [P82; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM16_8_3');
data120=importdata('SM16_gnd_8_3');
P83 = [P83; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];
%------------------------------------------------------------------------------------------------------------

data11=importdata('SM1_9_1');
data110=importdata('SM1_gnd_9_1');
P91 = [P91; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM1_9_2');
data120=importdata('SM1_gnd_9_2');
P92 = [P92; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM1_9_3');
data120=importdata('SM1_gnd_9_3');
P93 = [P93; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM2_9_1');
data110=importdata('SM2_gnd_9_1');
P91 = [P91; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM2_9_2');
data120=importdata('SM2_gnd_9_2');
P92 = [P92; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM2_9_3');
data120=importdata('SM2_gnd_9_3');
P93 = [P93; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM3_9_1');
data110=importdata('SM3_gnd_9_1');
P91 = [P91; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM3_9_2');
data120=importdata('SM3_gnd_9_2');
P92 = [P92; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM3_9_3');
data120=importdata('SM3_gnd_9_3');
P93 = [P93; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM4_9_1');
data110=importdata('SM4_gnd_9_1');
P91 = [P91; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM4_9_2');
data120=importdata('SM4_gnd_9_2');
P92 = [P92; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM4_9_3');
data120=importdata('SM4_gnd_9_3');
P93 = [P93; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM5_9_1');
data110=importdata('SM5_gnd_9_1');
P91 = [P91; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM5_9_2');
data120=importdata('SM5_gnd_9_2');
P92 = [P92; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM5_9_3');
data120=importdata('SM5_gnd_9_3');
P93 = [P93; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM6_9_1');
data110=importdata('SM6_gnd_9_1');
P91 = [P91; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM6_9_2');
data120=importdata('SM6_gnd_9_2');
P92 = [P92; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM6_9_3');
data120=importdata('SM6_gnd_9_3');
P93 = [P93; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM7_9_1');
data110=importdata('SM7_gnd_9_1');
P91 = [P91; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM7_9_2');
data120=importdata('SM7_gnd_9_2');
P92 = [P92; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM7_9_3');
data120=importdata('SM7_gnd_9_3');
P93 = [P93; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM8_9_1');
data110=importdata('SM8_gnd_9_1');
P91 = [P91; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM8_9_2');
data120=importdata('SM8_gnd_9_2');
P92 = [P92; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM8_9_3');
data120=importdata('SM8_gnd_9_3');
P93 = [P93; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM9_9_1');
data110=importdata('SM9_gnd_9_1');
P91 = [P91; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM9_9_2');
data120=importdata('SM9_gnd_9_2');
P92 = [P92; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM9_9_3');
data120=importdata('SM9_gnd_9_3');
P93 = [P93; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM10_9_1');
data110=importdata('SM10_gnd_9_1');
P91 = [P91; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM10_9_2');
data120=importdata('SM10_gnd_9_2');
P92 = [P92; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM10_9_3');
data120=importdata('SM10_gnd_9_3');
P93 = [P93; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM11_9_1');
data110=importdata('SM11_gnd_9_1');
P91 = [P91; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM11_9_2');
data120=importdata('SM11_gnd_9_2');
P92 = [P92; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM11_9_3');
data120=importdata('SM11_gnd_9_3');
P93 = [P93; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM12_9_1');
data110=importdata('SM12_gnd_9_1');
P91 = [P91; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM12_9_2');
data120=importdata('SM12_gnd_9_2');
P92 = [P92; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM12_9_3');
data120=importdata('SM12_gnd_9_3');
P93 = [P93; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM13_9_1');
data110=importdata('SM13_gnd_9_1');
P91 = [P91; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM13_9_2');
data120=importdata('SM13_gnd_9_2');
P92 = [P92; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM13_9_3');
data120=importdata('SM13_gnd_9_3');
P93 = [P93; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM14_9_1');
data110=importdata('SM14_gnd_9_1');
P91 = [P91; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM14_9_2');
data120=importdata('SM14_gnd_9_2');
P92 = [P92; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM14_9_3');
data120=importdata('SM14_gnd_9_3');
P93 = [P93; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM15_9_1');
data110=importdata('SM15_gnd_9_1');
P91 = [P91; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM15_9_2');
data120=importdata('SM15_gnd_9_2');
P92 = [P92; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM15_9_3');
data120=importdata('SM15_gnd_9_3');
P93 = [P93; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM16_9_1');
data110=importdata('SM16_gnd_9_1');
P91 = [P91; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM16_9_2');
data120=importdata('SM16_gnd_9_2');
P92 = [P92; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM16_9_3');
data120=importdata('SM16_gnd_9_3');
P93 = [P93; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];
%-------------------------------------------------------------------------------------------------
data11=importdata('SM1_10_1');
data110=importdata('SM1_gnd_10_1');
P101 = [P101; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM1_10_2');
data120=importdata('SM1_gnd_10_2');
P102 = [P102; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM1_10_3');
data120=importdata('SM1_gnd_10_3');
P103 = [P103; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM2_10_1');
data110=importdata('SM2_gnd_10_1');
P101 = [P101; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM2_10_2');
data120=importdata('SM2_gnd_10_2');
P102 = [P102; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM2_10_3');
data120=importdata('SM2_gnd_10_3');
P103 = [P103; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM3_10_1');
data110=importdata('SM3_gnd_10_1');
P101 = [P101; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM3_10_2');
data120=importdata('SM3_gnd_10_2');
P102 = [P102; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM3_10_3');
data120=importdata('SM3_gnd_10_3');
P103 = [P103; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM4_10_1');
data110=importdata('SM4_gnd_10_1');
P101 = [P101; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM4_10_2');
data120=importdata('SM4_gnd_10_2');
P102 = [P102; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM4_10_3');
data120=importdata('SM4_gnd_10_3');
P103 = [P103; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM5_10_1');
data110=importdata('SM5_gnd_10_1');
P101 = [P101; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM5_10_2');
data120=importdata('SM5_gnd_10_2');
P102 = [P102; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM5_10_3');
data120=importdata('SM5_gnd_10_3');
P103 = [P103; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM6_10_1');
data110=importdata('SM6_gnd_10_1');
P101 = [P101; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM6_10_2');
data120=importdata('SM6_gnd_10_2');
P102 = [P102; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM6_10_3');
data120=importdata('SM6_gnd_10_3');
P103 = [P103; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM7_10_1');
data110=importdata('SM7_gnd_10_1');
P101 = [P101; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM7_10_2');
data120=importdata('SM7_gnd_10_2');
P102 = [P102; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM7_10_3');
data120=importdata('SM7_gnd_10_3');
P103 = [P103; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM8_10_1');
data110=importdata('SM8_gnd_10_1');
P101 = [P101; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM8_10_2');
data120=importdata('SM8_gnd_10_2');
P102 = [P102; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM8_10_3');
data120=importdata('SM8_gnd_10_3');
P103 = [P103; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM9_10_1');
data110=importdata('SM9_gnd_10_1');
P101 = [P101; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM10_10_2');
data120=importdata('SM9_gnd_10_2');
P102 = [P102; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM9_10_3');
data120=importdata('SM9_gnd_10_3');
P103 = [P103; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM10_10_1');
data110=importdata('SM10_gnd_10_1');
P101 = [P101; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM10_10_2');
data120=importdata('SM10_gnd_10_2');
P102 = [P102; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM10_10_3');
data120=importdata('SM10_gnd_10_3');
P103 = [P103; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM11_10_1');
data110=importdata('SM11_gnd_10_1');
P101 = [P101; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM11_10_2');
data120=importdata('SM11_gnd_10_2');
P102 = [P102; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM11_10_3');
data120=importdata('SM11_gnd_10_3');
P103 = [P103; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM12_10_1');
data110=importdata('SM12_gnd_10_1');
P101 = [P101; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM12_10_2');
data120=importdata('SM12_gnd_10_2');
P102 = [P102; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM12_10_3');
data120=importdata('SM12_gnd_10_3');
P103 = [P103; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM13_10_1');
data110=importdata('SM13_gnd_10_1');
P101 = [P101; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM13_10_2');
data120=importdata('SM13_gnd_10_2');
P102 = [P102; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM13_10_3');
data120=importdata('SM13_gnd_10_3');
P103 = [P103; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM14_10_1');
data110=importdata('SM14_gnd_10_1');
P101 = [P101; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM14_10_2');
data120=importdata('SM14_gnd_10_2');
P102 = [P102; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM14_10_3');
data120=importdata('SM14_gnd_10_3');
P103 = [P103; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM15_10_1');
data110=importdata('SM15_gnd_10_1');
P101 = [P101; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM15_10_2');
data120=importdata('SM15_gnd_10_2');
P102 = [P102; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM15_10_3');
data120=importdata('SM15_gnd_10_3');
P103 = [P103; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM16_10_1');
data110=importdata('SM16_gnd_10_1');
P101 = [P101; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM16_10_2');
data120=importdata('SM16_gnd_10_2');
P102 = [P102; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM16_10_3');
data120=importdata('SM16_gnd_10_3');
P103 = [P103; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


%-------------------------------------------------------------------------------------------------
%bh = boxplot([P11 P12 0./P12 P21 P22 0./P12 P31 P32 0./P12 P41 P42 0./P12 P51 P52 0./P12 P61 P62 0./P12 P71 P72 0./P12 P81 P82 0./P12 P91 P92 0./P12 P101 P102], 'symbol','');
data11=importdata('SM1_13_1');
data110=importdata('SM1_gnd_13_1');
P131 = [P131; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM1_13_2');
data120=importdata('SM1_gnd_13_2');
P132 = [P132; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM1_13_3');
data120=importdata('SM1_gnd_13_3');
P133 = [P133; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM2_13_1');
data110=importdata('SM2_gnd_13_1');
P131 = [P131; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM2_13_2');
data120=importdata('SM2_gnd_13_2');
P132 = [P132; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM2_13_3');
data120=importdata('SM2_gnd_13_3');
P133 = [P133; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM3_13_1');
data110=importdata('SM3_gnd_13_1');
P131 = [P131; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM3_13_2');
data120=importdata('SM3_gnd_13_2');
P132 = [P132; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM3_13_3');
data120=importdata('SM3_gnd_13_3');
P133 = [P133; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM4_13_1');
data110=importdata('SM4_gnd_13_1');
P131 = [P131; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM4_13_2');
data120=importdata('SM4_gnd_13_2');
P132 = [P132; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM4_13_3');
data120=importdata('SM4_gnd_13_3');
P133 = [P133; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM5_13_1');
data110=importdata('SM5_gnd_13_1');
P131 = [P131; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM5_13_2');
data120=importdata('SM5_gnd_13_2');
P132 = [P132; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM5_13_3');
data120=importdata('SM5_gnd_13_3');
P133 = [P133; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM6_13_1');
data110=importdata('SM6_gnd_13_1');
P131 = [P131; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM6_13_2');
data120=importdata('SM6_gnd_13_2');
P132 = [P132; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM6_13_3');
data120=importdata('SM6_gnd_13_3');
P133 = [P133; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM7_13_1');
data110=importdata('SM7_gnd_13_1');
P131 = [P131; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM7_13_2');
data120=importdata('SM7_gnd_13_2');
P132 = [P132; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM7_13_3');
data120=importdata('SM7_gnd_13_3');
P133 = [P133; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM8_13_1');
data110=importdata('SM8_gnd_13_1');
P131 = [P131; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM8_13_2');
data120=importdata('SM8_gnd_13_2');
P132 = [P132; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM8_13_3');
data120=importdata('SM8_gnd_13_3');
P133 = [P133; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM9_13_1');
data110=importdata('SM9_gnd_13_1');
P131 = [P131; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM9_13_2');
data120=importdata('SM9_gnd_13_2');
P132 = [P132; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM9_13_3');
data120=importdata('SM9_gnd_13_3');
P133 = [P133; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM13_10_1');
data110=importdata('SM10_gnd_13_1');
P131 = [P131; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM13_13_2');
data120=importdata('SM10_gnd_13_2');
P132 = [P132; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM10_13_3');
data120=importdata('SM10_gnd_13_3');
P133 = [P133; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM11_13_1');
data110=importdata('SM11_gnd_13_1');
P131 = [P131; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM11_13_2');
data120=importdata('SM11_gnd_13_2');
P132 = [P132; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM11_13_3');
data120=importdata('SM11_gnd_13_3');
P133 = [P133; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM12_13_1');
data110=importdata('SM12_gnd_13_1');
P131 = [P131; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM13_13_2');
data120=importdata('SM12_gnd_13_2');
P132 = [P132; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM12_13_3');
data120=importdata('SM12_gnd_13_3');
P133 = [P133; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM13_13_1');
data110=importdata('SM13_gnd_13_1');
P131 = [P131; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM13_13_2');
data120=importdata('SM13_gnd_13_2');
P132 = [P132; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM13_13_3');
data120=importdata('SM13_gnd_13_3');
P133 = [P133; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM14_13_1');
data110=importdata('SM14_gnd_13_1');
P131 = [P131; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM14_13_2');
data120=importdata('SM14_gnd_13_2');
P132 = [P132; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM14_13_3');
data120=importdata('SM14_gnd_13_3');
P133 = [P133; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];


data11=importdata('SM15_13_1');
data110=importdata('SM15_gnd_13_1');
P131 = [P131; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM15_13_2');
data120=importdata('SM15_gnd_13_2');
P132 = [P132; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM15_13_3');
data120=importdata('SM15_gnd_13_3');
P133 = [P133; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

data11=importdata('SM16_13_1');
data110=importdata('SM16_gnd_13_1');
P131 = [P131; data11(start1:1:(start1+length1),2) - data110(start1:1:(start1+length1),2)];
data12=importdata('SM16_13_2');
data120=importdata('SM16_gnd_13_2');
P132 = [P132; data12(start2:1:(start2+length2),2) - data120(start2:1:(start2+length2),2)];
data12=importdata('SM16_13_3');
data120=importdata('SM16_gnd_13_3');
P133 = [P133; data12(start3:1:(start3+length3),2) - data120(start3:1:(start3+length3),2)];

bh1 = boxplot([P11 0./P11 0./P11 0./P11 P21 0./P21 0./P21 0./P21 P31 0./P31 0./P31 0./P31 P41 0./P41 0./P41 0./P41 P51 0./P51 0./P51 0./P51 P61 0./P61 0./P61 0./P61 P71 0./P71 0./P71 0./P71 P81 0./P81 0./P81 0./P81 P91 0./P91 0./P91 0./P91 P101 0./P101 0./P101 0./P101 P131 0./P131 0./P131], 'symbol','');
hold on;
bh2 = boxplot([0./P13 P13 0./P13 0./P13 0./P13 P23 0./P23 0./P23 0./P23 P33 0./P33 0./P33 0./P33 P43 0./P43 0./P43 0./P43 P53 0./P53 0./P53 0./P53 P63 0./P63 0./P63 0./P63 P73 0./P73 0./P73 0./P73 P83 0./P83 0./P83 0./P83 P93 0./P93 0./P93 0./P93 P103 0./P103 0./P103 0./P103 P133 0./P133], 'symbol','');
hold on;
bh3 = boxplot([0./P12 0./P12 P12 0./P12 0./P22 0./P22 P22 0./P22 0./P32 0./P32 P32 0./P32 0./P42 0./P42 P42 0./P42 0./P52 0./P52 P52 0./P52 0./P62 0./P62 P62 0./P62 0./P72 0./P72 P72 0./P72 0./P82 0./P82 P82 0./P82 0./P92 0./P92 P72 0./P92 0./P102 0./P102 P102 0./P102 0./P132 0./P132 P132], 'symbol','');
hold on;

for j =1:4:43
for i=1:size(bh1,1)
set(bh1(i,j),'linewidth',1);
set(bh1(i,j),'color','b');
end
end
for j =2:4:43
for i=1:size(bh2,1)
set(bh2(i,j),'linewidth',1);
set(bh2(i,j),'color','k');
end
end
for j =3:4:43
for i=1:size(bh2,1)
set(bh3(i,j),'linewidth',1);
set(bh3(i,j),'color','r');
end
end


axis([0 44 0 2])

set(gca,'ytick',[0 0.2 0.4 0.6 0.8 1 1.2 1.4 1.6 1.8 2.0]);
set(gca,'yticklabel',{'0','0.2','0.4','0.6','0.8', '1','1.2','1.4','1.6','1.8','2.0'},'fontsize',14);


set(gca,'xtick',[2 6 10 14 18 22 26 30 34 38 42]);
set(gca,'xticklabel',{'Backp','Bfs','Pathfinder','Hotspot','LavaMD','Blackscholes','Sortnetwork','Dxtc', 'Mergesort', 'Transpose','Worst'},'fontsize',14);

h = gca;
th=rotateticklabel(h, 30);

 ylabel('Supply Voltage(V)')
 
 grid on