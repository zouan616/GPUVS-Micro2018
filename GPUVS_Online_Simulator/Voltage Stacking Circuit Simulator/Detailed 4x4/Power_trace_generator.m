f = 68e6; %global
t = 0:1:12000;
t = t.*1.5e-9;
p = 1*cos(2*3.1415924*f*t);
p = p';

f1 = 200e6; % stack
t1 = 0:1:12000;
t1 = t1.*1.5e-9;
p1 = 1*cos(2*3.1415924*f1*t1);
p1 = p1';

f2 = 0e6; % residual
t2 = 0:1:12000;
t2 = t2.*1.5e-9;
p2 = 1*cos(2*3.1415924*f2*t2);
p2 = p2';



SM1 = 0.*[p p p p p p]./6 + 0.*[p1 p1 p1 p1 p1 p1]./6 + 1.*[p2 p2 p2 p2 p2 p2]./6;
SM2 = 0.*[p p p p p p]./6 + 0.*[p1 p1 p1 p1 p1 p1]./6 + 1.*[p2 p2 p2 p2 p2 p2]./6;
SM3 = 0.*[p p p p p p]./6 + 0.*[p1 p1 p1 p1 p1 p1]./6 + 1.*[p2 p2 p2 p2 p2 p2]./6;
SM4 = 0.*[p p p p p p]./6 + 0.*[p1 p1 p1 p1 p1 p1]./6 + 1.*[p2 p2 p2 p2 p2 p2]./6;
SM5 = 14.*[p p p p p p]./6 + 0.*[p1 p1 p1 p1 p1 p1]./6 + 0.*[p2 p2 p2 p2 p2 p2]./6;
SM6 = 14.*[p p p p p p]./6 + 0.*[p1 p1 p1 p1 p1 p1]./6 + 0.*[p2 p2 p2 p2 p2 p2]./6;
SM7 = 14.*[p p p p p p]./6 + 0.*[p1 p1 p1 p1 p1 p1]./6 + 0.*[p2 p2 p2 p2 p2 p2]./6;
SM8 = 14.*[p p p p p p]./6 + 0.*[p1 p1 p1 p1 p1 p1]./6 + 0.*[p2 p2 p2 p2 p2 p2]./6;
SM9 = 14.*[p p p p p p]./6 + 0.*[p2 p2 p2 p2 p2 p2]./6;
SM10 = 14.*[p p p p p p]./6 + 0.*[p2 p2 p2 p2 p2 p2]./6;
SM11 = 14.*[p p p p p p]./6 + 0.*[p2 p2 p2 p2 p2 p2]./6;
SM12 = 14.*[p p p p p p]./6 + 0.*[p2 p2 p2 p2 p2 p2]./6;
SM13 = 14.*[p p p p p p]./6 + 0.*[p2 p2 p2 p2 p2 p2]./6;
SM14 = 14.*[p p p p p p]./6 + 0.*[p2 p2 p2 p2 p2 p2]./6;
SM15 = 14.*[p p p p p p]./6 + 0.*[p2 p2 p2 p2 p2 p2]./6;
SM16 = 14.*[p p p p p p]./6 + 0.*[p2 p2 p2 p2 p2 p2]./6;




P = [SM1 SM2 SM3 SM4 SM5 SM6 SM7 SM8 SM9 SM10 SM11 SM12 SM13 SM14 SM15 SM16];




csvwrite('global_100K.txt',P)