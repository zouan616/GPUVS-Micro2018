figure
data1=importdata('SM1_random');
x1 = data1(1:1:160152,1);
y1 = data1(1:1:160152,2);
data2=importdata('SM1_gnd_random');
x2 = data2(1:1:160152,1);
y2 = data2(1:1:160152,2);



histogram((2.4*(y1 - y2 + 0.0125)-1.399),[0.6:0.04:1.4] )

samples = 160152

ylim([0 samples*0.4])

set(gca,'ytick',[samples*0 samples*0.1 samples*0.2 samples*0.3 samples*0.4 samples*0.8 samples]);
set(gca,'yticklabel',{'0%','10%','20%','30%','40%','80%','100%'});


set(gca,'FontSize',15);


ylabel('Samples (%)','FontSize',20);
xlabel('Voltage (V)','FontSize',20);

grid on
