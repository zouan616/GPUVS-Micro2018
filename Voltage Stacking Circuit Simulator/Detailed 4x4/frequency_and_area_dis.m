N = 6;
my_Color = linspecer(N);


figure


f = [10 20 30 40 50 70 100 150 200]
Vf = [0.1903 0.1413 0.1209 0.0987 0.091 0.085 0.081 0.076 0.071]



C = [0.2 0.3 0.4 0.5 0.6 0.7 0.8 1 1.2 1.4 1.6 1.8 2 2.5 3];
Vc = [0.1776 0.1378 0.117 0.1049 0.102 0.092 0.0907 0.083 0.0766 0.0734 0.0719 0.07 0.069 0.0658 0.0645];


values = spcrv([[f(1) f f(end)];[Vf(1) Vf Vf(end)]],3)

plot(values(1,:),values(2,:),'LineWidth',3,'color', my_Color(2,:));

hold on
plot(f,Vf,'^','color','k','markersize',10,'Markerfacecolor','k','markeredgecolor','k')

axis([0 220 0.04 0.2]); 


%title('global')

xlabel('frequency(MHz)');ylabel('voltage noise(V)');
set(gca,'FontSize',25);
grid minor

figure

values = spcrv([[C(1) C C(end)];[Vc(1) Vc Vc(end)]],3);

plot(values(1,:),values(2,:),'LineWidth',3,'color',my_Color(2,:));

hold on;

plot(C,Vc,'^','color','k','markersize',10,'Markerfacecolor','k','markeredgecolor','k')

axis([0 3.2 0.04 0.2]);

xlabel('Capacitor size({\mu}F)');ylabel('voltage noise(V)');
set(gca,'FontSize',25);
grid minor