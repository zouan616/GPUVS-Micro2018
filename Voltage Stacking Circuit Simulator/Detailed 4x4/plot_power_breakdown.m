figure
N = 6;
C = linspecer(N);

x = 1:1:10001;

plot(x,I_r_1,'LineWidth',0.5,'color',C(2,:));

le = legend('global current','Location','NorthEast');
set(le,'box','on','fontsize',20);
set(le, 'fontname', 'Arial');



axis([0 10000 0 10]); 

%title('GTX 480 Power trace')
xlabel('cycle');
ylabel('Current(A)');
set(gca,'FontSize',20);


grid on