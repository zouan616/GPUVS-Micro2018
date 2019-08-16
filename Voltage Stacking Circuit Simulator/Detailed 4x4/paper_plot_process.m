

N = 6;
C = linspecer(N);

figure
data1=importdata('hotspot_power.txt');
data2=importdata('hotspot_2level_power.txt');

length = 1000;
start = 56000;


y1 = data1(start:1:(start+length),1);

y2 = data1(start:1:(start+length),2);

%y3 = data1(start:1:(start+length),3);

x1 = 0:1:length;

%A = [y1 y2 y3];

A = [y1 y2];

[max_A,index]=max(A,[],2);
[min_A,index]=min(A,[],2);

Delta_A = max_A -min_A;

%x1 = x1.*1.5e-9;

%x1 = x1.*1e6;

plot(x1,y1,'LineWidth',2,'color',C(1,:),'DisplayName','SM1');
hold on;
plot(x1,y2,'LineWidth',2,'color',C(2,:),'DisplayName','SM2');
hold on;
%plot(x1,y3,'LineWidth',1.5,'color',C(3,:),'DisplayName','SM3');
%hold on;

%title('GTX 480 Power trace')
xlabel('cycle');ylabel('Power(W)');
set(gca,'FontSize',25);

le = legend('SM1','SM2','Location','NorthEast');
set(le,'box','on','fontsize',20);
set(le, 'fontname', 'Arial');

grid on

figure


y11 = data2(start:1:(start+length),1);

y22 = data2(start:1:(start+length),2);

plot(x1,y11,'LineWidth',2,'color',C(1,:),'DisplayName','SM1');
hold on;
plot(x1,y22,'LineWidth',2,'color',C(2,:),'DisplayName','SM2');
hold on;
%plot(x1,y3,'LineWidth',1.5,'color',C(3,:),'DisplayName','SM3');
%hold on;

%title('GTX 480 Power trace')
xlabel('cycle');ylabel('Power(W)');
set(gca,'FontSize',25);

le = legend('SM1','SM2','Location','NorthEast');
set(le,'box','on','fontsize',20);
set(le, 'fontname', 'Arial');





grid on






figure
plot(x1,Delta_A,'LineWidth',2,'color',C(1,:));


B = [y11 y22];

[max_B,index]=max(B,[],2);
[min_B,index]=min(B,[],2);

Delta_B = max_B -min_B;
%axis([0 5 0 15]); 
hold on;


plot(x1,Delta_B,'LineWidth',2,'color',C(2,:));



%title('GTX 480 Unbalanced power trace')
xlabel('cycle');ylabel('{\Delta}Power(W)');
set(gca,'FontSize',25);

le = legend('before','after','Location','NorthEast');
set(le,'box','on','fontsize',20);
set(le, 'fontname', 'Arial');



grid on