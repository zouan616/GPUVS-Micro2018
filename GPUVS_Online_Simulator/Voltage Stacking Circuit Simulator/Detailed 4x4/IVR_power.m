base = [2.24 2.3471 2.214 1.41 1.71 1.2183 1.875 2.22 2.17 1.81 2.02]; 
level25 = [1.42 1.466 1.751 1.0407 1.617 0.9064 1.58 1.63 1.21 1.01 1.54]; 


b=bar([1 2 3 4 5 6 7 8 9 10 11],[base' level25'],1);
legend('Hardware Only','Hardware + Architecture Assistance');

set(gca,'xticklabel',{'backprop','hotspot','kmeans','lavaMD','pathfinder','streamcluster','leukocyte','BLS','CVLS','DCT','BO'})

ylabel('IVR Power Loss(W)');
set(gca,'FontSize',26);

h = gca;
th=rotateticklabel(h, 11);

axis([0.5 11.5 0 2.5]); 
b(1).FaceColor = [8 108 162]./255;
b(2).FaceColor = [194 24 24]./255;