figure
N = 6;
C = linspecer(N);


I_global = [0.091 0.037 0.06 0.071 0.06 0.034 0.061 0.055]./2;
I_stack = [0.067 0.1213 0.045 0.05 0.05 0.04 0.05 0.04]./2
I_res = [1 0.85 0.41 0.6 0.5 0.28 0.55 0.58]./2;





y = [I_stack' I_global' I_res'];
b = bar(y,0.7,'stacked');

b(1).FaceColor = [89 89 89]/255
b(2).FaceColor = [254 61 67]/255
b(3).FaceColor = [0 114 189]/255


legend('V_{stack}','V_{global}','V_{residual}','Location','NorthWest');
%_______________________________________________________________________%




set(gca, 'fontname', 'Arial');
set(gca, 'fontsize', 16);
set(gca, 'linewidth',1);
%set(gca, 'FontWeight','bold')

%stop using science count
y_formatstring = '%3.0f'; 
axis([0.5 8.5 0 0.8])

%xl = xlabel('\bfGTX480 Power');
yl = ylabel({'Noise(V)'});
%set(xl,'fontsize',20);
set(yl,'fontsize',20,'Rotation',90);
%set(xl, 'fontname', 'Arial');
set(yl, 'fontname', 'Arial');

set(gca,'xticklabel',{'backprop','hotspot','lavaMD','pathfinder','streamcluster','kmeans','MGST','leukocyte'})
h = gca;
th=rotateticklabel(h, 15);

%set(yl,'Position',get(yl,'Position') + [0 -1 0]);
%set(gca,'yticklabel',{'0','10%','20%','30%','40%','50%','60%','70%','80%','90%','100%'},'fontsize',18);










%----------------------------------------------------------------------------------------%
figure
N = 6;
C = linspecer(N);


I_global = [0.09 0.04 0.06 0.07 0.06 0.04 0.06 0.05].*0.7;
I_stack = [0.07 0.1013 0.055 0.06 0.06 0.04 0.05 0.04].*0.7;
I_res = [0 0 0 0 0 0 0 0];




y = [I_stack' I_global'];
b = bar(y,0.7,'stacked');

b(1).FaceColor = [89 89 89]/255
b(2).FaceColor = [254 61 67]/255
%b(3).FaceColor = [0 114 189]/255


legend('V_{stack}','V_{global}','Location','NorthWest');
%_______________________________________________________________________%




set(gca, 'fontname', 'Arial');
set(gca, 'fontsize', 16);
set(gca, 'linewidth',1);
%set(gca, 'FontWeight','bold')

%stop using science count
y_formatstring = '%3.0f'; 
axis([0.5 8.5 0 0.8])

%xl = xlabel('\bfGTX480 Power');
yl = ylabel({'Noise(V)'});
%set(xl,'fontsize',20);
set(yl,'fontsize',20,'Rotation',90);
%set(xl, 'fontname', 'Arial');
set(yl, 'fontname', 'Arial');

set(gca,'xticklabel',{'backprop','hotspot','lavaMD','pathfinder','streamcluster','kmeans','MGST','leukocyte'})
h = gca;
th=rotateticklabel(h, 15);

%set(yl,'Position',get(yl,'Position') + [0 -1 0]);
%set(gca,'yticklabel',{'0','10%','20%','30%','40%','50%','60%','70%','80%','90%','100%'},'fontsize',18);
