clear
figure
data1=importdata('atom.txt');

length = 49998;
start = 1;

y1 = data1(start:1:(start+length),1);
y2 = data1(start:1:(start+length),2);

y = y2 - y1;

n1 = find(abs(y)>12);
[a1 b1] = size(n1);

n1 = find(abs(y)>9);
[a2 b2] = size(n1);

n1 = find(abs(y)>6);
[a3 b3] = size(n1);

n1 = find(abs(y)>3);
[a4 b4] = size(n1);

n1 = find(abs(y)>=0);
[a5 b5] = size(n1);


x1 = (a5 - a4)/length;  %0-20%
x2 = (a4 - a3)/length;  %20-40%
x3 = (a3 - a2)/length;  %40-60%
x4 = (a2 - a1)/length;  %60-80%
x5 = (a1)/length;      %>80%

g1 = x1 %0-20%
g2 = x2 %20-40%
g3 = x3 %40-60%
g4 = x4 + x5 % >60 %





%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

data1=importdata('atom75.txt');

length = 49998;
start = 1;

y1 = data1(start:1:(start+length),1);
y2 = data1(start:1:(start+length),2);

y = y2 - y1;

n1 = find(abs(y)>12);
[a1 b1] = size(n1);

n1 = find(abs(y)>9);
[a2 b2] = size(n1);

n1 = find(abs(y)>6);
[a3 b3] = size(n1);

n1 = find(abs(y)>3);
[a4 b4] = size(n1);

n1 = find(abs(y)>=0);
[a5 b5] = size(n1);


x1 = (a5 - a4)/length;  %0-20%
x2 = (a4 - a3)/length;  %20-40%
x3 = (a3 - a2)/length;  %40-60%
x4 = (a2 - a1)/length;  %60-80%
x5 = (a1)/length;      %>80%

h1 = x1 %0-20%
h2 = x2 %20-40%
h3 = x3 %40-60%
h4 = x4 + x5 % >60 %


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

data1=importdata('atom50.txt');

length = 49998;
start = 1;

y1 = data1(start:1:(start+length),1);
y2 = data1(start:1:(start+length),2);

y = y2 - y1;

n1 = find(abs(y)>12);
[a1 b1] = size(n1);

n1 = find(abs(y)>9);
[a2 b2] = size(n1);

n1 = find(abs(y)>6);
[a3 b3] = size(n1);

n1 = find(abs(y)>3);
[a4 b4] = size(n1);

n1 = find(abs(y)>=0);
[a5 b5] = size(n1);


x1 = (a5 - a4)/length;  %0-20%
x2 = (a4 - a3)/length;  %20-40%
x3 = (a3 - a2)/length;  %40-60%
x4 = (a2 - a1)/length;  %60-80%
x5 = (a1)/length;      %>80%

j1 = x1 %0-20%
j2 = x2 %20-40%
j3 = x3 %40-60%
j4 = x4 + x5 % >60 %

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

data1=importdata('atom50.txt');

length = 49998;
start = 1;

y1 = data1(start:1:(start+length),1);
y2 = data1(start:1:(start+length),2);

y = y2 - y1;

n1 = find(abs(y)>12);
[a1 b1] = size(n1);

n1 = find(abs(y)>9);
[a2 b2] = size(n1);

n1 = find(abs(y)>6);
[a3 b3] = size(n1);

n1 = find(abs(y)>3);
[a4 b4] = size(n1);

n1 = find(abs(y)>=0);
[a5 b5] = size(n1);


x1 = (a5 - a4)/length;  %0-20%
x2 = (a4 - a3)/length;  %20-40%
x3 = (a3 - a2)/length;  %40-60%
x4 = (a2 - a1)/length;  %60-80%
x5 = (a1)/length;      %>80%

j1 = x1 %0-20%
j2 = x2 %20-40%
j3 = x3 %40-60%
j4 = x4 + x5 % >60 %

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
data1=importdata('atom25.txt');

length = 49998;
start = 1;

y1 = data1(start:1:(start+length),1);
y2 = data1(start:1:(start+length),2);

y = y2 - y1;

n1 = find(abs(y)>12);
[a1 b1] = size(n1);

n1 = find(abs(y)>9);
[a2 b2] = size(n1);

n1 = find(abs(y)>6);
[a3 b3] = size(n1);

n1 = find(abs(y)>3);
[a4 b4] = size(n1);

n1 = find(abs(y)>=0);
[a5 b5] = size(n1);


x1 = (a5 - a4)/length;  %0-20%
x2 = (a4 - a3)/length;  %20-40%
x3 = (a3 - a2)/length;  %40-60%
x4 = (a2 - a1)/length;  %60-80%
x5 = (a1)/length;      %>80%

k1 = x1 %0-20%
k2 = x2 %20-40%
k3 = x3 %40-60%
k4 = x4 + x5 % >60 %

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
data1=importdata('atom.txt');
data2=importdata('atom_leakage.txt');

length = 49998;
start = 1;

y1 = data1(start:1:(start+length),1);
y2 = data1(start:1:(start+length),2);

y3 = data2(start:1:(start+length),1);
y4 = data2(start:1:(start+length),2);

y = y2 - y1 + y3 - y4;

n1 = find(abs(y)>12);
[a1 b1] = size(n1);

n1 = find(abs(y)>9);
[a2 b2] = size(n1);

n1 = find(abs(y)>6);
[a3 b3] = size(n1);

n1 = find(abs(y)>3);
[a4 b4] = size(n1);

n1 = find(abs(y)>=0);
[a5 b5] = size(n1);


x1 = (a5 - a4)/length;  %0-20%
x2 = (a4 - a3)/length;  %20-40%
x3 = (a3 - a2)/length;  %40-60%
x4 = (a2 - a1)/length;  %60-80%
x5 = (a1)/length;      %>80%

l1 = x1 %0-20%
l2 = x2 %20-40%
l3 = x3 %40-60%
l4 = x4 + x5 % >60 %

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


y = [g1 g2 g3 g4; h1 h2 h3 h4; j1 j2 j3 j4; k1 k2 k3 k4; l1 l2 l3 l4]
c = bar(y,'stack')

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
axis([0.4 5.6 0 1])

set(gca,'ytick',[0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1]);
set(gca,'yticklabel',{'0%','10%','20%','30%','40%','50%','60%','70%','80%','90%','100%'});

set(gca,'XTick',1:5)
set(gca,'XTickLabel',{'GPUVS','GRAPE:75%','GRAPE:50%','GRAPE:20%','Warped Gates'})
h = gca;
th=rotateticklabel(h, 30);

color=[[52 142 202]./255;[36,147,110]./255;[251, 226,81]./255;[217 82 84]./255];
for i=1:4
    set(c(i),'FaceColor',color(i,:));
end

legend('0-20% imbalance','20-40% imbalance','40-60% imbalance','> 60% imbalance')

xlabel('High level power optimization')
ylabel('Distribution ratio')