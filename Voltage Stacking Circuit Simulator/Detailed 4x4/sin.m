figure


x = 0:0.1:5*pi;
y = sin(x);
plot(x,y,'-','LineWidth',2)
hold on
plot(x,y+1,'-','LineWidth',2)
hold on
plot(x,y+2,'-','LineWidth',2)

axis([0 2.5*pi -2 5]);