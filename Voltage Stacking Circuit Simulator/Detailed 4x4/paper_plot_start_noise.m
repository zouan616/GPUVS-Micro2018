N = 6;
C = linspecer(N);


figure
data1=importdata('SM6_before.data');
x1 = data1(1:1:566152,1);
y1 = data1(1:1:566152,2);
data2=importdata('SM11_before.data');
x2 = data2(1:1:566152,1);
y2 = data2(1:1:566152,2);


x1 = x1 - 1.5e-6;
x1 = x1*1e6;
x1 = x1./0.0015;
x1 = x1 - 1240 + 720;

plot(x1,y1-y2,'LineWidth',1.5,'color',C(1,:));
hold on;

data1=importdata('SM6_after.data');
x11 = data1(1:1:566152,1);
y11 = data1(1:1:566152,2);
data2=importdata('SM11_after.data');
x22 = data2(1:1:566152,1);
y22 = data2(1:1:566152,2);

x11 = x11 - 1.5e-6;

x11 = x11*1e6;

x11 = x11./0.0015;

x11 = x11 - 1280 + 720;
plot(x11,y11-y22,'LineWidth',1.5,'color',C(2,:));


le = legend('before','after','Location','NorthEast');
set(le,'box','on','fontsize',20);
set(le, 'fontname', 'Arial');


axis([0 300 0.7 1.25]); 



xlabel('cycle');
ylabel('Voltage(V)');
set(gca,'FontSize',25);

%text(1.25,0.64,'1000 cycle','FontSize',20)
%text(2.75,0.64,'2000 cycle','FontSize',20)
%text(4.25,0.64,'3000 cycle','FontSize',20)

grid on
