hFig = figure
%set(hFig, 'Units','normalized','Position',[0.1 0.1 0.6 0.5])
length = 100000;
start = 20000;


data11=importdata('SM1_IVR');
P11 = data11(start:1:(start+length),2);
data12=importdata('SM1_gnd_IVR');
P12 = data12(start:1:(start+length),2);

data21=importdata('SM2_IVR');
P21 = data21(start:1:(start+length),2);
data22=importdata('SM2_gnd_IVR');
P22 = data22(start:1:(start+length),2);

data31=importdata('SM3_IVR');
P31 = data31(start:1:(start+length),2);
data32=importdata('SM3_gnd_IVR');
P32 = data32(start:1:(start+length),2);

data41=importdata('SM4_IVR');
P41 = data41(start:1:(start+length),2);
data42=importdata('SM4_gnd_IVR');
P42 = data42(start:1:(start+length),2);

data51=importdata('SM5_IVR');
P51 = data51(start:1:(start+length),2);
data52=importdata('SM5_gnd_IVR');
P52 = data52(start:1:(start+length),2);

data61=importdata('SM6_IVR');
P61 = data61(start:1:(start+length),2);
data62=importdata('SM6_gnd_IVR');
P62 = data62(start:1:(start+length),2);

data71=importdata('SM7_IVR');
P71 = data71(start:1:(start+length),2);
data72=importdata('SM7_gnd_IVR');
P72 = data72(start:1:(start+length),2);

data81=importdata('SM8_IVR');
P81 = data81(start:1:(start+length),2);
data82=importdata('SM8_gnd_IVR');
P82 = data82(start:1:(start+length),2);

data91=importdata('SM9_IVR');
P91 = data91(start:1:(start+length),2);
data92=importdata('SM9_gnd_IVR');
P92 = data92(start:1:(start+length),2);

data101=importdata('SM10_IVR');
P101 = data101(start:1:(start+length),2);
data102=importdata('SM10_gnd_IVR');
P102 = data102(start:1:(start+length),2);

data111=importdata('SM11_IVR');
P111 = data111(start:1:(start+length),2);
data112=importdata('SM11_gnd_IVR');
P112 = data112(start:1:(start+length),2);

data121=importdata('SM12_IVR');
P121 = data121(start:1:(start+length),2);
data122=importdata('SM12_gnd_IVR');
P122 = data122(start:1:(start+length),2);

data131=importdata('SM13_IVR');
P131 = data131(start:1:(start+length),2);
data132=importdata('SM13_gnd_IVR');
P132 = data132(start:1:(start+length),2);

data141=importdata('SM14_IVR');
P141 = data141(start:1:(start+length),2);
data142=importdata('SM14_gnd_IVR');
P142 = data142(start:1:(start+length),2);

data151=importdata('SM15_IVR');
P151 = data151(start:1:(start+length),2);
data152=importdata('SM15_gnd_IVR');
P152 = data152(start:1:(start+length),2);

data161=importdata('SM16_IVR');
P161 = data161(start:1:(start+length),2);
data162=importdata('SM16_gnd_IVR');
P162 = data162(start:1:(start+length),2);


length = 70000;
start = 20000;


data11=importdata('SM1_noivr');
P11_noivr = data11(start:1:(start+length),2);
data12=importdata('SM1_gnd_noivr');
P12_noivr = data12(start:1:(start+length),2);

data21=importdata('SM2_noivr');
P21_noivr = data21(start:1:(start+length),2);
data22=importdata('SM2_gnd_noivr');
P22_noivr = data22(start:1:(start+length),2);

data31=importdata('SM3_noivr');
P31_noivr = data31(start:1:(start+length),2);
data32=importdata('SM3_gnd_noivr');
P32_noivr = data32(start:1:(start+length),2);

data41=importdata('SM4_noivr');
P41_noivr = data41(start:1:(start+length),2);
data42=importdata('SM4_gnd_noivr');
P42_noivr = data42(start:1:(start+length),2);

data51=importdata('SM5_noivr');
P51_noivr = data51(start:1:(start+length),2);
data52=importdata('SM5_gnd_noivr');
P52_noivr = data52(start:1:(start+length),2);

data61=importdata('SM6_noivr');
P61_noivr = data61(start:1:(start+length),2);
data62=importdata('SM6_gnd_noivr');
P62_noivr = data62(start:1:(start+length),2);

data71=importdata('SM7_noivr');
P71_noivr = data71(start:1:(start+length),2);
data72=importdata('SM7_gnd_noivr');
P72_noivr = data72(start:1:(start+length),2);

data81=importdata('SM8_noivr');
P81_noivr = data81(start:1:(start+length),2);
data82=importdata('SM8_gnd_noivr');
P82_noivr = data82(start:1:(start+length),2);

data91=importdata('SM9_noivr');
P91_noivr = data91(start:1:(start+length),2);
data92=importdata('SM9_gnd_noivr');
P92_noivr = data92(start:1:(start+length),2);

data101=importdata('SM10_noivr');
P101_noivr = data101(start:1:(start+length),2);
data102=importdata('SM10_gnd_noivr');
P102_noivr = data102(start:1:(start+length),2);

data111=importdata('SM11_noivr');
P111_noivr = data111(start:1:(start+length),2);
data112=importdata('SM11_gnd_noivr');
P112_noivr = data112(start:1:(start+length),2);

data121=importdata('SM12_noivr');
P121_noivr = data121(start:1:(start+length),2);
data122=importdata('SM12_gnd_noivr');
P122_noivr = data122(start:1:(start+length),2);

data131=importdata('SM13_noivr');
P131_noivr = data131(start:1:(start+length),2);
data132=importdata('SM13_gnd_noivr');
P132_noivr = data132(start:1:(start+length),2);

data141=importdata('SM14_noivr');
P141_noivr = data141(start:1:(start+length),2);
data142=importdata('SM14_gnd_noivr');
P142_noivr = data142(start:1:(start+length),2);

data151=importdata('SM15_noivr');
P151_noivr = data151(start:1:(start+length),2);
data152=importdata('SM15_gnd_noivr');
P152_noivr = data152(start:1:(start+length),2);

data161=importdata('SM16_noivr');
P161_noivr = data161(start:1:(start+length),2);
data162=importdata('SM16_gnd_noivr');
P162_noivr = data162(start:1:(start+length),2);

bh1 = boxplot([(P11-P12) 0./(P11-P12) 0./(P11-P12) (P21-P22) 0./(P11-P12) 0./(P11-P12) (P31-P32) 0./(P11-P12) 0./(P11-P12) (P41-P42) 0./(P11-P12) 0./(P11-P12) (P51-P52)  0./(P11-P12) 0./(P11-P12) (P61-P62) 0./(P11-P12) 0./(P11-P12) (P71-P72) 0./(P11-P12) 0./(P11-P12) (P81-P82) 0./(P11-P12) 0./(P11-P12) (P91-P92) 0./(P11-P12) 0./(P11-P12) (P101-P102)  0./(P11-P12) 0./(P11-P12) (P111-P112) 0./(P11-P12) 0./(P11-P12) (P121-P122) 0./(P11-P12) 0./(P11-P12) (P131-P132) 0./(P11-P12) 0./(P11-P12) (P141-P142) 0./(P11-P12) 0./(P11-P12) (P151-P152) 0./(P11-P12) 0./(P11-P12) (P161-P162) 0./(P11-P12) 0./(P11-P12)], 'Whisker', 10 ,'symbol','');

hold on;

bh2 = boxplot([0./(P11_noivr-P12_noivr) (P11_noivr-P12_noivr) 0./(P11_noivr-P12_noivr) 0./(P11_noivr-P12_noivr) (P21_noivr-P22_noivr) 0./(P11_noivr-P12_noivr) 0./(P11_noivr-P12_noivr) (P31_noivr-P32_noivr) 0./(P11_noivr-P12_noivr) 0./(P11_noivr-P12_noivr) (P41_noivr-P42_noivr) 0./(P11_noivr-P12_noivr) 0./(P11_noivr-P12_noivr) (P51_noivr-P52_noivr) 0./(P11_noivr-P12_noivr) 0./(P11_noivr-P12_noivr) (P61_noivr-P62_noivr) 0./(P11_noivr-P12_noivr) 0./(P11_noivr-P12_noivr) (P71_noivr-P72_noivr) 0./(P11_noivr-P12_noivr) 0./(P11_noivr-P12_noivr) (P81_noivr-P82_noivr) 0./(P11_noivr-P12_noivr) 0./(P11_noivr-P12_noivr) (P91_noivr-P92_noivr) 0./(P11_noivr-P12_noivr) 0./(P11_noivr-P12_noivr) (P101_noivr-P102_noivr) 0./(P11_noivr-P12_noivr) 0./(P11_noivr-P12_noivr) (P111_noivr-P112_noivr) 0./(P11_noivr-P12_noivr) 0./(P11_noivr-P12_noivr) (P121_noivr-P122_noivr) 0./(P11_noivr-P12_noivr) 0./(P11_noivr-P12_noivr) (P131_noivr-P132_noivr) 0./(P11_noivr-P12_noivr) 0./(P11_noivr-P12_noivr) (P141_noivr-P142_noivr) 0./(P11_noivr-P12_noivr) 0./(P11_noivr-P12_noivr) (P151_noivr-P152_noivr) 0./(P11_noivr-P12_noivr) 0./(P11_noivr-P12_noivr) (P161_noivr-P162_noivr) 0./(P11_noivr-P12_noivr)], 'Whisker', 10, 'symbol','');



for j =1:3:47
for i=1:size(bh1,1)
set(bh1(i,j),'linewidth',1);
set(bh1(i,j),'color','b');
end
end
for j =2:3:47
for i=1:size(bh2,1)
set(bh2(i,j),'linewidth',1);
set(bh2(i,j),'color','r');
end
end


axis([0 48 0.4 1.6])

set(gca,'xtick',[1.5 4.5 7.5 10.5 13.5 16.5 19.5 22.5 25.5 28.5 31.5 34.5 37.5 40.5 43.5 46.5]);
set(gca,'xticklabel',{'SM1','SM2','SM3','SM4','SM5','SM6','SM7','SM8', 'SM9', 'SM10','SM11','SM12','SM13','SM14','SM15','SM16'},'fontsize',14);

set(gca,'ytick',[0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1 1.1 1.2 1.3 1.4 1.5 1.6 1.7 1.8 1.9 2.0]);
set(gca,'yticklabel',{'0','0.1','0.2','0.3','0.4','0.5','0.6','0.7','0.8', '0.9', '1','1.1','1.2','1.3','1.4','1.5','1.6','1.7','1.8','1.9','2.0'},'fontsize',14);



h = gca;
th=rotateticklabel(h, 30);

ylabel('Supply Voltage(V)')
 
grid on
