figure

current_r1 = [6.0108 0 6.3234 0 4.6960 0 5.6912 0 4.7647 0 3.9318 0 5.8 0 5.5 0];
current_r2 = [0 5.051 0 3.4034 0 4.0335 0 4.5448 0 4.0707 0 3.6957 0 4.7 0 4.5396];




y= [current_r1' current_r2']

b = bar(y,0.7,'stacked');


b(1).FaceColor = [8 108 162]./255;
b(2).FaceColor = [194 24 24]./255;
yl = ylabel({'Max Residual Current(A)'});
set(yl,'fontsize',20,'Rotation',90);;
set(yl, 'fontname', 'Arial');

set(gca, 'fontsize', 16);
set(gca, 'linewidth',1);
grid on


legend('Before Synchronized SM Start','After Synchronized SM Start','Location','NorthWest');

axis([0.5 16.5 0 7])
set(gca,'xtick',2.5:2:18)
set(gca,'xticklabel',{'backprop','hotspot','lavaMD','pathfinder','streamcluster','kmeans','BFS','leukocyte'})
h = gca;
th=rotateticklabel(h, 15);
