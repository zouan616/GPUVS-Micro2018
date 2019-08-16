hFig = figure
%set(hFig, 'Units','normalized','Position',[0.1 0.1 0.6 0.5])
length = 400000;
start = 100000;


data11=importdata('SM1_original.data');
P11 = data11(start:1:(start+length),2);
data12=importdata('SM1_IVR.data');
P12 = data12(start:1:(start+length),2);

data21=importdata('SM2_original.data');
P21 = data21(start:1:(start+length),2);
data22=importdata('SM2_IVR.data');
P22 = data22(start:1:(start+length),2);

data31=importdata('SM3_original.data');
P31 = data31(start:1:(start+length),2);
data32=importdata('SM3_IVR.data');
P32 = data32(start:1:(start+length),2);

data41=importdata('SM4_original.data');
P41 = data41(start:1:(start+length),2);
data42=importdata('SM4_IVR.data');
P42 = data42(start:1:(start+length),2);

data51=importdata('SM5_original.data')
P51 = data51(start:1:(start+length),2);
data52=importdata('SM5_IVR.data');
P52 = data52(start:1:(start+length),2);

data61=importdata('SM6_original.data');
P61 = data61(start:1:(start+length),2);
data62=importdata('SM6_IVR.data');
P62 = data62(start:1:(start+length),2);

data71=importdata('SM7_original.data');
P71 = data71(start:1:(start+length),2);
data72=importdata('SM7_IVR.data');
P72 = data72(start:1:(start+length),2);

data81=importdata('SM8_original.data');
P81 = data81(start:1:(start+length),2);
data82=importdata('SM8_IVR.data');
P82 = data82(start:1:(start+length),2);

data91=importdata('SM9_original.data');
P91 = data91(start:1:(start+length),2);
data92=importdata('SM9_IVR.data');
P92 = data92(start:1:(start+length),2);

data101=importdata('SM10_original.data');
P101 = data101(start:1:(start+length),2);
data102=importdata('SM10_IVR.data');
P102 = data102(start:1:(start+length),2);

data111=importdata('SM11_original.data');
P111 = data111(start:1:(start+length),2);
data112=importdata('SM11_IVR.data');
P112 = data112(start:1:(start+length),2);

data121=importdata('SM12_original.data');
P121 = data121(start:1:(start+length),2);
data122=importdata('SM12_IVR.data');
P122 = data122(start:1:(start+length),2);

data131=importdata('SM13_original.data');
P131 = data131(start:1:(start+length),2);
data132=importdata('SM13_IVR.data');
P132 = data132(start:1:(start+length),2);

data141=importdata('SM14_original.data');
P141 = data141(start:1:(start+length),2);
data142=importdata('SM14_IVR.data');
P142 = data142(start:1:(start+length),2);

data151=importdata('SM15_original.data');
P151 = data151(start:1:(start+length),2);
data152=importdata('SM15_IVR.data');
P152 = data152(start:1:(start+length),2);


bh = boxplot([(P11-P61) (P12-P62) (0./(P12-P62)) (P21-P71) (P22-P72) (0./(P12-P62)) (P31-P81) (P32-P82) (0./(P12-P62)) (P41-P91) (P42-P92) (0./(P12-P62)) (P51-P101) (P52-P102) (0./(P12-P62)) (P61-P111) (P62-P112) (0./(P12-P62)) (P71-P121) (P72-P122) (0./(P12-P62)) (P81-P131) (P82-P132) (0./(P12-P62)) (P91-P141) (P92-P142) (0./(P12-P62)) (P101-P151) (P102-P152) (0./(P12-P62)) P111 P112 (0./(P12-P62)) P121 P122 (0./(P12-P62)) P131 P132 (0./(P12-P62)) P141 P142 (0./(P12-P62)) P151 P152], 'symbol','');

for j =1:3:44
for i=1:size(bh,1)
set(bh(i,j),'linewidth',1);
set(bh(i,j),'color','b');
end
end
for j =2:3:44
for i=1:size(bh,1)
set(bh(i,j),'linewidth',1);
set(bh(i,j),'color','r');
end
end


axis([0 45 0.2 1.7])

set(gca,'xtick',[1.5 4.5 7.5 10.5 13.5 16.5 19.5 22.5 25.5 28.5 31.5 34.5 37.5 40.5 43.5]);
set(gca,'xticklabel',{'SM1','SM2','SM3','SM4','SM5','SM6','SM7','SM8','SM9','SM10','SM11','SM12','SM13','SM14','SM15'},'fontsize',10);


