N = 6;
my_Color = linspecer(N);


figure


f1 = [10 20 30 40 50 70 100 150 200]
Vf1 = [0.421 0.374 0.343 0.299 0.261 0.245 0.234 0.223 0.22]
C1 = [2 3 4 5 6 7 8 10 12].*4;
Vc1 = [0.42 0.36 0.30 0.26 0.234 0.21 0.202 0.201 0.199];

f2 = [10 20 30 40 50 70 100 150 200]
Vf2 = [0.1903 0.1413 0.1209 0.0987 0.091 0.085 0.081 0.076 0.071]
C2 = [0.2 0.3 0.4 0.5 0.6 0.7 0.8 1 1.2 1.4 1.6 1.8 2 2.5 3].*5.*4;
Vc2 = [0.1776 0.1378 0.117 0.1049 0.102 0.092 0.0907 0.083 0.0766 0.0734 0.0719 0.07 0.069 0.0658 0.0645];
plot(f1,Vf1,'-^','color',my_Color(1,:),'markersize',10,'Markerfacecolor',my_Color(1,:),'markeredgecolor',my_Color(1,:))
hold on
plot(f1,Vf2,'-O','color',my_Color(2,:),'markersize',10,'Markerfacecolor',my_Color(2,:),'markeredgecolor',my_Color(2,:))
hold on

values1 = spcrv([[f1(1) f1 f1(end)];[Vf1(1) Vf1 Vf1(end)]],3)
plot(values1(1,:),values1(2,:),'LineWidth',2,'color', my_Color(1,:));
hold on
values2 = spcrv([[f2(1) f2 f2(end)];[Vf2(1) Vf2 Vf2(end)]],3)
plot(values2(1,:),values2(2,:),'LineWidth',2,'color', my_Color(2,:));





axis([0 220 0 0.5]); 
%title('global')
xlabel('Frequency(MHz)');ylabel('Worst voltage noise(V)');
set(gca,'FontSize',15);
grid minor

legend('Centralized IVR','Distributed IVR');



figure
plot(C1,Vc1,'-^','color',my_Color(1,:),'markersize',10,'Markerfacecolor',my_Color(1,:),'markeredgecolor',my_Color(1,:))
hold on
plot(C2,Vc2,'-O','color',my_Color(2,:),'markersize',10,'Markerfacecolor',my_Color(2,:),'markeredgecolor',my_Color(2,:))
hold on

values1 = spcrv([[C1(1) C1 C1(end)];[Vc1(1) Vc1 Vc1(end)]],3)
plot(values1(1,:),values1(2,:),'LineWidth',3,'color', my_Color(1,:),'LineWidth',2);

values2 = spcrv([[C2(1) C2 C2(end)];[Vc2(1) Vc2 Vc2(end)]],3)
plot(values2(1,:),values2(2,:),'LineWidth',3,'color', my_Color(2,:),'LineWidth',2);
hold on
%plot(C1,Vc1,'-^','color',my_Color(1,:),'markersize',10,'Markerfacecolor',my_Color(1,:),'markeredgecolor',my_Color(1,:))
hold on
%plot(C2,Vc2,'-O','color',my_Color(2,:),'markersize',10,'Markerfacecolor',my_Color(2,:),'markeredgecolor',my_Color(2,:))

axis([0 52 0 0.5]); 
%title('global')
xlabel('Total capacitor size({\mu}F)');ylabel('Worst voltage noise(V)');
set(gca,'FontSize',15);
grid minor

legend('Centralized IVR','Distributed IVR');