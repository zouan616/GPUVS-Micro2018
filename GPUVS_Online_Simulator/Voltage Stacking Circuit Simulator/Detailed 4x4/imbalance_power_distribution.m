data1=importdata('srad.txt');
%data1=importdata('srad_power_gating.txt');
%data2=importdata('srad_leakage_power.txt');
length = 49998;
start = 1;


y1 = data1(start:1:(start+length),1);
y2 = data1(start:1:(start+length),2);


%y = y2 - y1 + y4 - y3;

y = y2 - y1;

[f,xi]=ksdensity(y);
plot(xi,f,'k','LineWidth',1.5);

xlim([0 15])
hold on
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
data1=importdata('srad75.txt');
%data1=importdata('srad_power_gating.txt');
%data2=importdata('srad_leakage_power.txt');
length = 49998;
start = 1;


y1 = data1(start:1:(start+length),1);
y2 = data1(start:1:(start+length),2);


%y = y2 - y1 + y4 - y3;

y = y2 - y1;

[f,xi]=ksdensity(y);
plot(xi,f,'--','LineWidth',1.5);

xlim([0 15])
hold on

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
data1=importdata('srad50.txt');
%data1=importdata('srad_power_gating.txt');
%data2=importdata('srad_leakage_power.txt');
length = 49998;
start = 1;


y1 = data1(start:1:(start+length),1);
y2 = data1(start:1:(start+length),2);


%y = y2 - y1 + y4 - y3;

y = y2 - y1;

[f,xi]=ksdensity(y);
plot(xi,f,'-.','LineWidth',1.5);

xlim([0 15])
hold on


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
data1=importdata('srad25.txt');
%data1=importdata('srad_power_gating.txt');
%data2=importdata('srad_leakage_power.txt');
length = 49998;
start = 1;


y1 = data1(start:1:(start+length),1);
y2 = data1(start:1:(start+length),2);


%y = y2 - y1 + y4 - y3;

y = y2 - y1;

[f,xi]=ksdensity(y);
plot(xi,f,':','LineWidth',1.5);

xlim([0 15])
hold on

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5
data1=importdata('srad.txt');
data2=importdata('srad_leakage.txt');
length = 49998;
start = 1;


y1 = data1(start:1:(start+length),1);
y2 = data1(start:1:(start+length),2);

y3 = data2(start:1:(start+length),1);
y4 = data2(start:1:(start+length),2);

y = y2 - y1 + y3 - y4;


[f,xi]=ksdensity(y);
plot(xi,f,'^','LineWidth',1.5);

xlim([0 5])
ylim([0 0.3])
hold on


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
legend('No High Level Power Optimization','Grape DFS (75%)','Grape DFS (50%)','Grape DFS (25%)','Warped Gates Power Gating')

xlabel('Imbalance power')
ylabel('Probability distribution density')