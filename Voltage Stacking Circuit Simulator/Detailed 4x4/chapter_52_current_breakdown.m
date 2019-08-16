figure

current_r1 = [7.0108 0 8.5 0 4.7956 0 5.6912 0 5.5685 0 3.9318 0 5.8 0 9.2 0];
current_r2 = [0 6.0124/7.0108 0 7.5/8.5 0 4.46/4.7956 0 5.2670/5.6912 0 4.4597/5.5685 0 3.6957/3.9318 0 4.9/5.8 0 8.6/9.2];
current_r1 = [1 0 1 0 1 0 1 0 1 0 1 0 1 0 1 0];


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


legend('Before Power-aware Instruction Issue','After Power-aware Instruction Issue','Location','NorthWest');

axis([0.5 16.5 0 1.1])
set(gca,'xtick',2.5:2:18)
set(gca,'xticklabel',{'backprop','hotspot','lavaMD','pathfinder','streamcluster','kmeans','BFS','leukocyte'})
h = gca;
th=rotateticklabel(h, 15);