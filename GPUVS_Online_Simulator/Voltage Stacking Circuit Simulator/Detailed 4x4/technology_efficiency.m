hFig = figure
set(hFig, 'Units','normalized','Position',[0.1 0.1 0.6 0.8])

R_pkg = 0.0028;
n_offVR = [0.88 0.885 0.895 0.9 0.9 0.9 0.9];
L = [14 22 32 45 65 90 130];
V = [0.75 0.8 0.95 1.05 1.15 1.25 1.3];
Fo4 = [5 5.57 6.5 12.6 13.9 19.1 25.2];
f = 1./(0.06.*Fo4);
f = f.*10^9;
n_Dynamic = [0.8 0.7192 0.6267 0.45 0.41 0.57 0.66];

P_total = 50.*[1 1 1 1 1 1 1];

P_Dynamic = P_total .* n_Dynamic;
P_leakage = P_total .* (1 - n_Dynamic);

C = P_Dynamic ./ (V.*V.*f);

I_leakage = P_leakage ./ V;

V_margin = (C.*V.*f)*0.0003+0.06;

%V_margin = 0.2.*V;

%P_real = C.*(V+V_margin).*(V+V_margin).*f + I_leakage.*(V+V_margin)+ (C.*(V+V_margin).*f + I_leakage).*(C.*(V+V_margin).*f + I_leakage).*R_pkg;

P_margin = C.*(V+V_margin).*(V+V_margin).*f + I_leakage.*(V+V_margin) + (C.*(V+V_margin).*f + I_leakage).*(C.*(V+V_margin).*f + I_leakage).*R_pkg - (C.*V.*f + I_leakage).*(C.*V.*f + I_leakage).*R_pkg - P_total;


P_PDN = (C.*V.*f + I_leakage).*(C.*V.*f + I_leakage).*R_pkg;


P_offVR = (P_total + P_PDN + P_margin).*(1 - n_offVR);

P_sum = P_total + P_margin + P_PDN + P_offVR;

P_total = P_total./P_sum
P_margin = P_margin./P_sum;
P_total = P_total + P_margin;
P_PDN = P_PDN./P_sum;
P_offVR = P_offVR./P_sum;

y = [P_total' P_PDN' P_offVR'];
b = bar(y,0.6,'stacked');
b(1).FaceColor = [0 0 0]./255;
b(2).FaceColor = [162 101 64]./255;
b(3).FaceColor = [185 147 97]./255;
%b(4).FaceColor = [128 26 26]./255;
legend('P_{Used in Computation}','P_{PDN loss}','P_{Conversion loss}','Location','SouthEast');



%_______________________________________________________________________%






set(gca, 'fontname', 'Arial');
set(gca, 'fontsize', 16);
set(gca, 'linewidth',1);
set(gca, 'FontWeight','bold')

%stop using science count
y_formatstring = '%3.0f'; 
axis([0.5 7.5 0 1])


set(gca, 'fontname', 'Arial');
set(gca, 'fontsize', 16);
set(gca, 'linewidth',1);
set(gca,'FontWeight','bold');

%ti = title('\bfPower Delivery Efficiency Trends (Technology) ');
%set(ti, 'fontsize',22)
%set(ti,'Position',get(ti,'Position'));
%set(ti, 'fontname', 'Arial');


xl = xlabel('\bfNodes (nm)');
yl = ylabel({'\bfNormalized Power Breakdown'});
set(xl,'fontsize',20);
set(yl,'fontsize',20,'Rotation',90);
set(xl, 'fontname', 'Arial');
set(yl, 'fontname', 'Arial');


set(gca,'xticklabel',{'14nm','22nm','32nm','45nm','65nm','90nm','130nm','180nm','200nm'},'fontsize',18);

set(gca,'yticklabel',{'0','20%','40%','60%','80%','100%'},'fontsize',18);
