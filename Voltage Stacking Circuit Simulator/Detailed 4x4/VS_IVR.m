figure

N = 6;
C = linspecer(N);

data1=importdata('SM3_original.data');
x1 = data1(1:1:507152,1);
y1 = data1(1:1:507152,2);
data2=importdata('SM8_original.data');
x2 = data2(1:1:507152,1);
y2 = data2(1:1:507152,2);

[y,x]=hist(y1-y2,100); 

y=y/length(y1-y2)/mean(diff(x));

voltage = y1 - y2 - 1;


[mu,sigma]=normfit(voltage);
xlim([mu-3*sigma,mu+3*sigma])
a2=axes;
ezplot(@(x)normpdf(x,mu,sigma),[mu-3*sigma,mu+3*sigma])

hold on;

data1=importdata('SM3.data');
x11 = data1(1:1:507152,1);
y11 = data1(1:1:507152,2);
data2=importdata('SM8.data');
x22 = data2(1:1:507152,1);
y22 = data2(1:1:507152,2);

[y,x]=hist(y11-y22,100); 

y=y/length(y11-y22)/mean(diff(x));

voltage = y11 - y22 - 1;


[mu,sigma]=normfit(voltage);
xlim([mu-3*sigma,mu+3*sigma])
a2=axes;
ezplot(@(x)normpdf(x,mu,sigma),[mu-3*sigma,mu+3*sigma])
set(a2,'box','off','yaxislocation','right','color','none')