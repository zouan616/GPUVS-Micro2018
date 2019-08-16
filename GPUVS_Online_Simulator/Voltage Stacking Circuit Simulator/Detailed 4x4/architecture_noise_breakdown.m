figure
data1=importdata('SM4_before.data');
data11=importdata('SM9_before.data');
data2=importdata('SM4_after..data');
data22=importdata('SM9_after..data');


length = 100000;
start = 1;


y1 = data1(start:1:(start+length),2);
y11 = data11(start:1:(start+length),2);
V1 = y1 - y11 - 1.055;

y2 = data2(start:1:(start+length),2);
y22 = data22(start:1:(start+length),2);
V2 = y2 - y22 - 1.055;

x = -0.5:0.05:0.5;

histogram(V1,x, 'FaceColor',[194 24 24]./255, 'EdgeColor', 'k','LineWidth',0.5,'FaceAlpha',0.5)
hold on
histogram(V2,x, 'FaceAlpha',0.5, 'EdgeColor', 'k', 'LineWidth',0.5,'FaceColor',[8 108 162]./255)
legend('No Architecture Assistance','Power-aware Instruction Issue')

hold on

set(gca,'FontSize',16);

grid on

axis([-0.4 0.4 0 0.4e5]);

xl = xlabel('Voltage noise (V)');