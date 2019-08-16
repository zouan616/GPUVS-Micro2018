%--------------------------linear programming--------------------------------------%

% Low frequency 10MHz, Medium frequency~75-100MHz,  High frequency ~300MHz
Z_G_L = 0.0145;
Z_G_M = 0.0361;
Z_G_H = 0.32;

Z_ST_L = 0.0086;
Z_ST_M = 0.009;
Z_ST_H = 0.0092;

Z_R_L = 0.425;
Z_R_M = 0.08;
Z_R_H = 0.0662;

Z_R_L_other = 0.415;
Z_R_M_other = 0.08;
Z_R_H_other = 0.0662;

a1= 1/16 * Z_G_L + 3/16 * Z_ST_L + 12/16 * Z_R_L + 2/16 * Z_R_L_other;
a2 = 1/16 * Z_G_M + 3/16 * Z_ST_M + 12/16 * Z_R_M + 2/16 * Z_R_M_other;
a3 = 1/16 * Z_G_H + 3/16 * Z_ST_H + 12/16 * Z_R_H + 2/16 * Z_R_H_other;

a4= 1/16 * Z_G_L + 3/16 * Z_ST_L - 4/16 * Z_R_L + 2/16 * Z_R_L_other;
a5 = 1/16 * Z_G_M + 3/16 * Z_ST_M - 4/16 * Z_R_M + 2/16 * Z_R_M_other;
a6 = 1/16 * Z_G_H + 3/16 * Z_ST_H - 4/16 * Z_R_H + 2/16 * Z_R_H_other;

a7= 1/16 * Z_G_L + 1/16 * Z_ST_L - 2/16 * Z_R_L - 2/16 * Z_R_L_other;
a8 = 1/16 * Z_G_M + 1/16 * Z_ST_M - 2/16 * Z_R_M - 2/16 * Z_R_M_other;
a9 = 1/16 * Z_G_H + 1/16 * Z_ST_H - 2/16 * Z_R_H - 2/16 * Z_R_H_other;

a10 = 1/16 * Z_G_L + 1/16 * Z_ST_L - 2/16 * Z_R_L + 14/16 * Z_R_L_other;
a11 = 1/16 * Z_G_M + 1/16 * Z_ST_M - 2/16 * Z_R_M + 14/16 * Z_R_M_other;
a12 = 1/16 * Z_G_H + 1/16 * Z_ST_H - 2/16 * Z_R_H + 14/16 * Z_R_H_other;

f = -[a1 a2 a3 a4 a5 a6 a7 a8 a9 a10 a11 a12];
lb = [0 0 0 0 0 0 0 0 0 0 0 0];
ub = [14 14 14 14*3 14*3 14*3 14*8 14*8 14*8 14*3 14*3 14*3];

A = [1 1 1 0 0 0 0 0 0 0 0 0; 0 0 0 1 1 1 0 0 0 0 0 0; 0 0 0 0 0 0 1 1 1 0 0 0; 0 0 0 0 0 0 0 0 0 1 1 1];
b = [14 14*3 14*8 14*3];

Aeq = [0 0 0 0 0 0 0 0 0 0 0 0];
beq = [0];

[x, fval] = linprog(f, A, b, Aeq, beq, lb, ub);

x
fval = -fval