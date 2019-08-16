figure
data1=importdata('SM1');
x1 = data1(20000:1:120000,1);
y1 = data1(20000:1:120000,2);
data2=importdata('SM1_gnd');
x2 = data2(20000:1:120000,1);
y2 = data2(20000:1:120000,2);



histogram((y1 - y2),[0.8:0.02:1.2], 'FaceAlpha',0.3)

samples = 70000

ylim([0 samples*0.4])

set(gca,'ytick',[samples*0 samples*0.1 samples*0.2 samples*0.3 samples*0.4 samples*0.8 samples]);
set(gca,'yticklabel',{'0%','10%','20%','30%','40%','80%','100%'});


set(gca,'FontSize',15);


ylabel('Samples (%)','FontSize',20);
xlabel('Voltage (V)','FontSize',20);

grid on

hold on


data1=importdata('SM2');
x1 = data1(20000:1:120000,1);
y1 = data1(20000:1:120000,2);
data2=importdata('SM2_gnd');
x2 = data2(20000:1:120000,1);
y2 = data2(20000:1:120000,2);



histogram((y1 - y2),[0.8:0.02:1.2], 'FaceAlpha',0.6)

samples = 70000

ylim([0 samples*0.4])

set(gca,'ytick',[samples*0 samples*0.1 samples*0.2 samples*0.3 samples*0.4 samples*0.8 samples]);
set(gca,'yticklabel',{'0%','10%','20%','30%','40%','80%','100%'});


set(gca,'FontSize',14);


ylabel('Samples (%)','FontSize',14);
xlabel('Voltage (V)','FontSize',14);

grid on

hold on