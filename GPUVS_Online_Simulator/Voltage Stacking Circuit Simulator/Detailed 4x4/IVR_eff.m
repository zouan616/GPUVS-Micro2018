ac =  [1/3 2/3 2/3 1/3]
ar = [1/3 0 1/3 0 2/3 0]

C = 5e-6;
fsw = 100e6;
Rsw = 0.001;


Rssl = sum(ac.*ac/(C*fsw),2)

Rfsl = 2*sum(ar.*ar*Rsw)

Rseries = sqrt(Rssl*Rssl + Rfsl*Rfsl)