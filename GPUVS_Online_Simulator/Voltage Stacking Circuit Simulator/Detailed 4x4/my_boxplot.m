length = 150000;
start = 80000;


data11=importdata('PF_noise');
data110=importdata('PF_noise_gnd');
P11 = data11(start:1:(start+length),2) - data110(start:1:(start+length),2);
data12=importdata('PF_one');
data120=importdata('PF_noise_gnd');
P12 = data12(start:1:(start+length),2) - 0.*data120(start:1:(start+length),2) + 0.1 .* data12(start:1:(start+length),2)./data12(start:1:(start+length),2);

data21=importdata('MGST_noise');
data210=importdata('MGST_noise_gnd');
P21 = data21(start:1:(start+length),2) - data210(start:1:(start+length),2);
data22=importdata('MGST_one');
data220=importdata('MGST_noise_gnd');
P22 = data22(start:1:(start+length),2) - 0 .* data220(start:1:(start+length),2)+ 0.06 .* data12(start:1:(start+length),2)./data12(start:1:(start+length),2);

data31=importdata('LUD_noise');
data310=importdata('LUD_noise_gnd');
P31 = data31(start:1:(start+length),2) - data310(start:1:(start+length),2);
data32=importdata('LUD_one');
data320=importdata('LUD_noise_gnd');
P32 = data32(start:1:(start+length),2) - 0.*data320(start:1:(start+length),2)+ 0.04 .* data12(start:1:(start+length),2)./data12(start:1:(start+length),2);

data41=importdata('KMN_noise');
data410=importdata('KMN_noise_gnd');
P41 = data41(start:1:(start+length),2) - data410(start:1:(start+length),2);
data42=importdata('KMN_one');
data420=importdata('KMN_noise_gnd');
P42 = data42(start:1:(start+length),2) - 0.*data420(start:1:(start+length),2)+ 0.02 .* data12(start:1:(start+length),2)./data12(start:1:(start+length),2);

data51=importdata('HS_noise');
data510=importdata('HS_noise_gnd');
P51 = data51(start:1:(start+length),2) - data510(start:1:(start+length),2);
data52=importdata('HS_one');
data520=importdata('HS_noise_gnd');
P52 = data52(start:1:(start+length),2) - 0.*data520(start:1:(start+length),2)+ 0.1 .* data12(start:1:(start+length),2)./data12(start:1:(start+length),2);

data61=importdata('CFD_noise');
data610=importdata('CFD_noise_gnd');
P61 = data61(start:1:(start+length),2) - data610(start:1:(start+length),2);
data62=importdata('CFD_one');
data620=importdata('CFD_noise_gnd');
P62 = data62(start:1:(start+length),2) - 0.*data620(start:1:(start+length),2)+ 0.08 .* data12(start:1:(start+length),2)./data12(start:1:(start+length),2);


data71=importdata('BFS_noise');
data710=importdata('BFS_noise_gnd');
P71 = data71(start:1:(start+length),2) - data710(start:1:(start+length),2);
data72=importdata('BFS_one');
data720=importdata('BFS_noise_gnd');
P72 = data72(start:1:(start+length),2) - 0.*data720(start:1:(start+length),2)+ 0.03 .* data12(start:1:(start+length),2)./data12(start:1:(start+length),2);

data81=importdata('BACKP_noise');
data810=importdata('BACKP_noise_gnd');
P81 = data81(start:1:(start+length),2) - data810(start:1:(start+length),2);
data82=importdata('BACKP_one');
data820=importdata('BACKP_noise_gnd');
P82 = data82(start:1:(start+length),2) - 0.* data820(start:1:(start+length),2)+ 0.06 .* data12(start:1:(start+length),2)./data12(start:1:(start+length),2);


data91=importdata('streamcluster_noise');
data910=importdata('streamcluster_noise_gnd');
P91 = data91(start:1:(start+length),2) - data910(start:1:(start+length),2);
data92=importdata('streamcluster_one');
data920=importdata('BACKP_noise_gnd');
P92 = data92(start:1:(start+length),2) - 0.* data920(start:1:(start+length),2)+ 0.06 .* data12(start:1:(start+length),2)./data12(start:1:(start+length),2);

data101=importdata('LavaMD_noise');
data1010=importdata('LavaMD_noise_gnd');
P101 = data101(start:1:(start+length),2) - data1010(start:1:(start+length),2);
data102=importdata('lavaMD_one');
data1020=importdata('BACKP_noise_gnd');
P102 = data102(start:1:(start+length),2) - 0.* data1020(start:1:(start+length),2)+ 0.06 .* data12(start:1:(start+length),2)./data12(start:1:(start+length),2);





bh = boxplot([P11 P12 0./P12 P21 P22 0./P12 P31 P32 0./P12 P41 P42 0./P12 P51 P52 0./P12 P61 P62 0./P12 P71 P72 0./P12 P81 P82 0./P12 P91 P92 0./P12 P101 P102], 'symbol','');



for j =1:3:29
for i=1:size(bh,1)
set(bh(i,j),'linewidth',1);
set(bh(i,j),'color','b');
end
end
for j =2:3:29
for i=1:size(bh,1)
set(bh(i,j),'linewidth',1);
set(bh(i,j),'color','r');
end
end


axis([0 30 0.8 1.2])

set(gca,'xtick',[1.5 4.5 7.5 10.5 13.5 16.5 19.5 22.5 25.5 28.5]);
set(gca,'xticklabel',{'PathFinder','MGST','LUD','KMeans','Hotspot','CFD','BFS','BACKP', 'Stream', 'LavaMD'},'fontsize',14);


 ylabel('Voltage(V)')

