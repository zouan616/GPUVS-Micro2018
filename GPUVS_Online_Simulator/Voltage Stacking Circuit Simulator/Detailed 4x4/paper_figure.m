subplot(2,1,1);
data1=importdata('hotspot_power_cut.txt');


length = 4500;
start = 1;


y1 = data1(start:1:(start+length),2);

x1 = start:1:(start+length);

x1 = x1.*1.5e-9;

x1 = x1.*1e6;
x1 = x1 - 1;

plot(x1,y1);

axis([0 5 0 15]); 

%title('SM2')
%xlabel('time({\mu}s)');
ylabel('Power(W)');
set(gca,'FontSize',25);

subplot(2,1,2);
data1=importdata('SM2.data');
x1 = data1(1:1:620152,1);
y1 = data1(1:1:620152,2);
data2=importdata('SM7.data');
x2 = data2(1:1:620152,1);
y2 = data2(1:1:620152,2);

x1 = x1.*1e6;

x1 = x1 - 1;

plot(x1,y1-y2);



axis([0 5 0.6 1.4]); 

xlabel('time({\mu}s)');
ylabel('Power(W)');
set(gca,'FontSize',25);

