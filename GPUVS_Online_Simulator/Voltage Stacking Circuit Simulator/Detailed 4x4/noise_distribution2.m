figure

N = 6;
C = linspecer(N);


data1=importdata('SM1_original.data');
x1 = data1(10000:1:510000,1);
y1 = data1(10000:1:510000,2);
data2=importdata('SM6_original.data');
x2 = data2(10000:1:510000,1);
y2 = data2(10000:1:510000,2);

data3=importdata('SM4_IVR.data');
x11 = data3(10000:1:510000,1);
y11 = data3(10000:1:510000,2);
data4=importdata('SM9_IVR.data');
x22 = data4(10000:1:510000,1);
y22 = data4(10000:1:510000,2);

data5=importdata('SM4_dis.data');
x111 = data5(10000:1:510000,1);
y111 = data5(10000:1:510000,2);
data6=importdata('SM9_dis.data');
x222 = data6(10000:1:510000,1);
y222 = data6(10000:1:510000,2);

original = y1 - y2 -1.041;
%original = y1 - 0.12;


%IVR = y11 - y22 - 1.041;
IVR = y11 -y22 - 0.02;


%dis = y111 - y222 - 1.041;
dis = y111 - y222 -  0.02;
x = 0.7:0.02:1.3;



%histogram(original,x, 'FaceColor',[194 24 24]./255, 'EdgeColor', 'k','LineWidth',0.5,'FaceAlpha',1)
%hold on
%histogram(IVR,x, 'FaceAlpha',1, 'EdgeColor', 'k', 'LineWidth',0.5,'FaceColor',[8 108 162]./255)
%legend('VS','VS+IVR')

%histogram(IVR,x, 'FaceColor',[194 24 24]./255, 'EdgeColor', 'k','LineWidth',0.5,'FaceAlpha',1)
%hold on
histogram(dis,x, 'FaceAlpha',1, 'EdgeColor', 'k', 'LineWidth',0.5,'FaceColor',[8 108 162]./255)
%legend('Voltage stacking with centralized IVR','Voltage stacking')

text(0.8,2e5,{'\fontsize{30}\bf SM4'},'Color','k','HorizontalAlignment','Center', 'fontname', 'Arial','fontsize',12);
%xlabel('Voltage noise(V)');ylabel('Distribution');
%xlabel('SM13');
set(gca,'FontSize',30);
grid minor

axis([0.7 1.3 0 3e5]);

hold on;