
N = 6;
C = linspecer(N);


data1=importdata('SM3_original.data');
x1 = data1(10000:1:507152,1);
y1 = data1(10000:1:507152,2);
data2=importdata('SM8_original.data');
x2 = data2(10000:1:507152,1);
y2 = data2(10000:1:507152,2);

data3=importdata('SM3_IVR.data');
x11 = data3(10000:1:507152,1);
y11 = data3(10000:1:507152,2);
data4=importdata('SM8_IVR.data');
x22 = data4(10000:1:507152,1);
y22 = data4(10000:1:507152,2);

data5=importdata('SM3_dis.data');
x111 = data5(10000:1:507152,1);
y111 = data5(10000:1:507152,2);
data6=importdata('SM8_dis.data');
x222 = data6(10000:1:507152,1);
y222 = data6(10000:1:507152,2);

x = y1 - y2;

x = x';



u = mean(x)

s = std(x)

sq=s;
 


a=u;sigma=sq; % 
x=0.5:0.0001:1.5;
y=(1/((sqrt(2*pi))*sigma))*exp(-((x-a).^2)/(2*sigma.^2));
plot(x,y,'b','LineWidth',2,'color',C(1,:));

hold on




x = y11 - y22;

x = x';


u = mean(x)

s = std(x)

sq = s
 
x= 0.5:0.001:1.5;



a=u;sigma=sq; % 
x=0.5:0.0001:1.5;
y=(1/((sqrt(2*pi))*sigma))*exp(-((x-a).^2)/(2*sigma.^2));

plot(x,y,'b','LineWidth',2,'color',C(2,:));


hold on




x = y111 - y222;

x = x';


u = mean(x)

s = std(x)

sq = s
 
x= 0.5:0.001:1.5;



a=u;sigma=sq; % 
x=0.5:0.0001:1.5;
y=(1/((sqrt(2*pi))*sigma))*exp(-((x-a).^2)/(2*sigma.^2));

plot(x,y,'b','LineWidth',2,'color',C(3,:));


xlabel('Voltage (V)');
ylabel('Probability Density');


set(gca,'FontSize',25);

le = legend('Voltage Stacking',['Voltage Stacking',sprintf('\n'),'(with IVR)'],['Voltage Stacking',sprintf('\n'),'(with Distributed IVR)'],'Location','NorthEast');
set(le,'box','on','fontsize',20);
set(le, 'fontname', 'Arial');


grid minor