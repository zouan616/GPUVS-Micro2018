
data1=importdata('srad_leakage_power.txt');
length = 22998;
start = 1;
y1 = data1(start:1:(start+length),1);
tabulate(y1(:))