data1=importdata('HS.txt');
p1 = data1(1:1:5152,1);
p2 = data1(1:1:5152,2);
p3 = data1(1:1:5152,3);
p4 = data1(1:1:5152,4);
p5 = data1(1:1:5152,5);
p6 = data1(1:1:5152,6);
p7 = data1(1:1:5152,7);
p8 = data1(1:1:5152,8);
p9 = data1(1:1:5152,9);
p10 = data1(1:1:5152,10);
p11 = data1(1:1:5152,11);
p12 = data1(1:1:5152,12);
p13 = data1(1:1:5152,13);
p14 = data1(1:1:5152,14);
p15 = data1(1:1:5152,15);
p16 = data1(1:1:5152,16);



SM1 = [p1 p1 p1 p1 p1 p1]./6;
SM2 = [p2 p2 p2 p2 p2 p2]./6;
SM3 = [p3 p3 p3 p3 p3 p3]./6;
SM4 = [p4 p4 p4 p4 p4 p4]./6;
SM5 = [p5 p5 p5 p5 p5 p5]./6;
SM6 = [p6 p6 p6 p6 p6 p6]./6;
SM7 = [p7 p7 p7 p7 p7 p7]./6;
SM8 = [p8 p8 p8 p8 p8 p8]./6;
SM9 = [p9 p9 p9 p9 p9 p9]./6;
SM10 = [p10 p10 p10 p10 p10 p10]./6;
SM11 = [p11 p11 p11 p11 p11 p11]./6;
SM12 = [p12 p12 p12 p12 p12 p12]./6;
SM13 = [p13 p13 p13 p13 p13 p13]./6;
SM14 = [p14 p14 p14 p14 p14 p14]./6;
SM15 = [p15 p15 p15 p15 p15 p15]./6;
SM16 = [p16 p16 p16 p16 p16 p16]./6;




P = [SM1 SM2 SM3 SM4 SM5 SM6 SM7 SM8 SM9 SM10 SM11 SM12 SM13 SM14 SM15 SM16];

csvwrite('global_100K.txt',P)

