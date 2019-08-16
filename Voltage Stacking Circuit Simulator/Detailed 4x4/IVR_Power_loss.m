
%IVR_efficiency
ac =  [1/3 2/3 2/3 1/3];
ar = [1/3 0 1/3 0 2/3 0];

C = 5e-6;
fsw = 100e6;
Rsw = 0.01;


Rssl = sum(ac.*ac/(C*fsw),2);

Rfsl = 2*sum(ar.*ar*Rsw*12);

Rseries = sqrt(Rssl*Rssl + Rfsl*Rfsl)




data1=importdata('leukocyte-2-5.txt');


length = 1000;
start = 100000;

y1 = data1(start:1:(start+length),1);
y2 = data1(start:1:(start+length),2);
y3 = data1(start:1:(start+length),3);
y4 = data1(start:1:(start+length),4);
y5 = data1(start:1:(start+length),5);

y6 = data1(start:1:(start+length),6);
y7 = data1(start:1:(start+length),7);
y8 = data1(start:1:(start+length),8);
y9 = data1(start:1:(start+length),9);
y10 = data1(start:1:(start+length),10);

y11 = data1(start:1:(start+length),11);
y12 = data1(start:1:(start+length),12);
y13 = data1(start:1:(start+length),13);
y14 = data1(start:1:(start+length),14);
y15 = data1(start:1:(start+length),15);


I16 = (y1 - y6)/2;
I27 = (y2 - y7)/2;
I38 = (y3 - y8)/2;
I49 = (y4 - y9)/2;
I510 = (y5 - y10)/2;
I611 = (y6 - y11)/2;
I712 = (y7 - y12)/2;
I813 = (y8 - y13)/2;
I914 = (y9 - y14)/2;
I1015 = (y10 - y15)/2;


P_core = y1+y2+y3+y4+y5+y6+y7+y8+y9+y10+y11+y12+y13+y14+y15;
P_out = I16.*I16 + I27.*I27 + I38.*I38 + I49.*I49 + I510.*I510 + I611.*I611 + I712.*I712 + I813.*I813 + I914.*I914 + I1015.*I1015;
P_loss = (I16.*I16 + I27.*I27 + I38.*I38 + I49.*I49 + I510.*I510 + I611.*I611 + I712.*I712 + I813.*I813 + I914.*I914 + I1015.*I1015)*Rseries;


P_core = mean(P_core)

P_IVR_out = mean(P_out)

P_loss = mean(P_loss)


