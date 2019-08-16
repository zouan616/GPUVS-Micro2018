N = 6;
C = linspecer(N);





figure
data1=importdata('SM4_before.data');
x1 = data1(1:1:916152,1);
y1 = data1(1:1:916152,2);
data2=importdata('SM9_before.data');
x2 = data2(1:1:916152,1);
y2 = data2(1:1:916152,2);


x1 = x1 - 1.5e-6;
x1 = x1*1e6;
x1 = x1./0.0015;
plot(x1,y1-y2,'LineWidth',1.5,'color',C(1,:));
hold on;

data1=importdata('SM4_after.data');
x11 = data1(1:1:916152,1);
y11 = data1(1:1:916152,2);
data2=importdata('SM9_after.data');
x22 = data2(1:1:916152,1);
y22 = data2(1:1:916152,2);

x11 = x11 - 1.5e-6;

x11 = x11*1e6;

x11 = x11./0.0015;

plot(x11,y11-y22,'LineWidth',1.5,'color',C(2,:));


le = legend('before','after','Location','NorthEast');
set(le,'box','on','fontsize',20);
set(le, 'fontname', 'Arial');



axis([0 1000 0.6 1.25]); 

%title('global')


grid on


xlabel('cycle');
ylabel('Voltage(V)');
set(gca,'FontSize',25);


