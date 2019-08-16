N = 6;
my_Color = linspecer(N);


figure


f = [10 20 30 40 50 70 100 150 200]
Vf = [0.421 0.374 0.343 0.299 0.261 0.245 0.234 0.223 0.22]



C = [2 3 4 5 6 7 8 10 12];
Vc = [0.42 0.36 0.30 0.26 0.234 0.21 0.202 0.201 0.199];


values = spcrv([[f(1) f f(end)];[Vf(1) Vf Vf(end)]],3)

plot(values(1,:),values(2,:),'LineWidth',3,'color', my_Color(2,:));

hold on
plot(f,Vf,'^','color','k','markersize',10,'Markerfacecolor','k','markeredgecolor','k')

axis([0 220 0.1 0.5]); 


%title('global')

xlabel('frequency(MHz)');ylabel('voltage noise(V)');
set(gca,'FontSize',25);
grid minor

figure

values = spcrv([[C(1) C C(end)];[Vc(1) Vc Vc(end)]],3);

plot(values(1,:),values(2,:),'LineWidth',3,'color',my_Color(2,:));

hold on;

plot(C,Vc,'^','color','k','markersize',10,'Markerfacecolor','k','markeredgecolor','k')

axis([1 13 0.1 0.5]);

xlabel('Capacitor size({\mu}F)');ylabel('voltage noise(V)');
set(gca,'FontSize',25);
grid minor