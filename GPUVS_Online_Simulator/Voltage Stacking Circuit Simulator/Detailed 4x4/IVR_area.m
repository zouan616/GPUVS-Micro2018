
base = [0.52 0.38 0.5 0.6 0.62 0.37 0.55 0.48 0.54 0.51 0.44]; 
level25 = [0.38 0.28 0.35 0.4 0.43 0.28 0.39 0.35 0.38 0.37 0.32]; 

base = base./0.7.*4.*5*7;
level25 = level25./0.7.*4.*5*7;



b = bar([1 2 3 4 5 6 7 8 9 10 11],[base' level25'],1);
legend('Hardware Only','Hardware + Architecture Assistance');
axis([0.5 11.5 0 130]); 
set(gca,'xticklabel',{'backprop','hotspot','kmeans','lavaMD','pathfinder','streamcluster','leukocyte','BLS','CVLS','DCT','BO'})

ylabel('IVR Area(mm^2)');
set(gca,'FontSize',26);

h = gca;
th=rotateticklabel(h, 16);

b(1).FaceColor = [8 108 162]./255;
b(2).FaceColor = [194 24 24]./255;