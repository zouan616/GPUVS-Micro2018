figure
data1=importdata('SM7_Voltage_1');
x1 = data1(1:1:186735,1);
y1 = data1(1:1:186735,2);

x1 = x1 - 2e-6*x1./x1;
y1= y1 - 2.12 * y1./y1;



data1=importdata('SM7_Voltage_2');
x2 = data1(1:1:186735,1);
y2 = data1(1:1:186735,2);

x2 = x2 - 2e-6*x2./x2;
y2= y2 - 2.12 * y2./y2;






subplot(211),
plot(x1,y1);


set(gca,'xlim',[0 5e-6]);
set(gca,'ylim',[0.9 1.1]);

set(gca,'xticklabel',[]);

set(gca,'box','on');

set(gca,'position',[0.15 0.65 0.75 0.27]);


subplot(212),

plot(x2,y2);

set(gca,'xlim',[0 5e-6]);
set(gca,'ylim',[0.9 1.1]);

%set(gca,'xticklabel',[]);

set(gca,'box','on');

set(gca,'position',[0.15 0.38 0.75 0.27]);


xlabel('Time')
ylabel('Voltage(V)')