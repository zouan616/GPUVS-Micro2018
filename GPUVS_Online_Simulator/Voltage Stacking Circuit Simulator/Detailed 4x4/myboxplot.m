figure
data1=importdata('SM3.data');
x1 = data1(1:1:57152,1);
y1 = data1(1:1:57152,2);


x1 = x1.*1e8;



plot(x1,y1);



title('SM3')