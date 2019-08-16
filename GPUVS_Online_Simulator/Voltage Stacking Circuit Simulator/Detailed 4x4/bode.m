L = 2.91e-15;
C = 50e-6;
num=[L 0];
den = [L*C 0 1];
H=tf(num,den);
bode(H)