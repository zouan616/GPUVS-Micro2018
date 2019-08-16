figure
P_core = [210*0.77 210*0.77 210*0.77 210*0.77];
P_Margin = [210*0.23 210*0.23 210*0.23 210*0.23]
P_PDN = [210*210*(0.65*0.002) 210*210*(0.65*0.002)/3 210*210*(0.65*0.002)/3*1.01*1.01 210*210*(0.65*0.002)/3];
P_VR = [(210 + 210*210*(0.65*0.002))*0.1 (210 + 210*210*(0.65*0.002)/3)*0.15 4 3];

P_total = P_core + P_Margin + P_PDN + P_VR



y = [P_core' P_PDN' P_VR' P_Margin'];
b = bar(y,0.5,'stacked');

b(1).FaceColor = [8 108 162]./255;
b(2).FaceColor = [194 24 24]./255;
b(3).FaceColor = [255 215 0]./255;
b(4).FaceColor = [128 26 26]./255;

legend('P_{Core}','P_{Voltage Margin}','P_{PDN}','P_{VR}','Location','NorthWest');
%_______________________________________________________________________%





set(gca, 'fontname', 'Arial');
set(gca, 'fontsize', 16);
set(gca, 'linewidth',1);
set(gca,'FontWeight','bold');

%stop using science count
y_formatstring = '%3.0f'; 
axis([0.5 4.5 0 300])




xl = xlabel('\bfGTX480');
yl = ylabel({'\bfNormalized Power Breakdown'});
set(xl,'fontsize',20);
set(yl,'fontsize',20,'Rotation',90);
set(xl, 'fontname', 'Arial');
set(yl, 'fontname', 'Arial');



set(gca,'xtick',[],'xticklabel',[])

%set(yl,'Position',get(yl,'Position') + [0 -1 0]);

text(1,-23,{'\fontsize{12}\bfOne Layer'; 'with off-chip VR'},'Color','k','HorizontalAlignment','Center', 'fontname', 'Arial','fontsize',12);
text(2,-23,{'\fontsize{12}\bfOne Layer';'with IVR'},'Color','k','HorizontalAlignment','Center', 'fontname', 'Arial','fontsize',12);
text(3,-23,{'\fontsize{12}\bfVoltageStacking';'Hardware'; 'Only'},'Color','k','HorizontalAlignment','Center', 'fontname', 'Arial','fontsize',12);
text(4,-23,{'\fontsize{12}\bfVoltageStacking';'Hardware'; 'Architecture'},'Color','k','HorizontalAlignment','Center', 'fontname', 'Arial','fontsize',12);