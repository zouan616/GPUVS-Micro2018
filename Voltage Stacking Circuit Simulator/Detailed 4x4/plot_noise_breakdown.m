N = 6;
C = linspecer(N);





figure
data1=importdata('SM1.data');
x1 = data1(30000:1:1106933,1);
y1 = data1(30000:1:1106933,2);
data2=importdata('SM6.data');
x2 = data2(30000:1:1106933,1);
y2 = data2(30000:1:1106933,2);

x1 = x1;
x1 = x1*1e6;
x1 = x1./0.0015;
plot(x1,y1-y2 -1.10,'LineWidth',1.5,'color',C(2,:));


le = legend('stack noise','Location','NorthEast');
set(le,'box','on','fontsize',20);
set(le, 'fontname', 'Arial');



axis([0 10000 -0.5 0.5]); 

%title('GTX 480 Power trace')
%xlabel('cycle');
%ylabel('Power(W)');
set(gca,'FontSize',20);


grid on