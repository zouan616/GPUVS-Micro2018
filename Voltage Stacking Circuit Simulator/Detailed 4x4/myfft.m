figure
data1=importdata('SM1.data');
x1 = data1(2097152/2-1:1:2097152,1);
y1 = data1(2097152/2-1:1:2097152,2);
data2=importdata('SM6.data');
x2 = data2(2097152/2-1:1:2097152,1);
y2 = data2(2097152/2-1:1:2097152,2);

y = y1 - y2;

y = y - (y./y).*mean(y);

N = 2097152/2; %2^20

fs = (1/14)*10^12;

n = 0:N-1;


F = fft(y,N);

f=n/N*fs;

plot(f,abs(F));
