figure
data1=importdata('per_core_power_record.txt');
%data1=importdata('leakage_power.txt');

length = 5000;
start = 1;


y1 = data1(start:1:(start+length),2);

x1 = start:1:(start+length);

x1 = x1.*1.5e-9;


x1 = x1 - x1./x1.*start.*1.5e-9;
x1 = x1.*1e6;
plot(x1,y1);

%axis([0 15 0 15]); 

%title('SM2')
xlabel('time({\mu}s)');ylabel('Power(W)');
set(gca,'FontSize',12);

hold
mean(y1)