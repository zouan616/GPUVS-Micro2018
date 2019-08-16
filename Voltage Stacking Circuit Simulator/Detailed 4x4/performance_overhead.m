base = [1 1 1 1 1 1 1 1 1 1 1]; 
level25 = [1/(1-5177/200000) 1/(1-15000/200000) 1/(1-(2865680-2862880)/2865680) 1/(1-(30099616 - 29983465)/30099616)  1/(1-(164896-154746)/154746) 1/(1-(753812-720000)/720000) 1/(1-((142812968-132603374)/132603374)) 1.035 1.045 1.041 1.043]; %backp hotspot


b=bar([1 2 3 4 5 6 7 8 9 10 11],[base' level25'],1);
legend('Base line','Architecture Assistance');

set(gca,'xticklabel',{'backprop','hotspot','kmeans','lavaMD','pathfinder','streamcluster','leukocyte','BLS','CVLS','DCT','BO'})

ylabel('Normalized Execution Time');
set(gca,'FontSize',26);


h = gca;
th=rotateticklabel(h, 10);

axis([0.5 11.5 0 1.2]); 
b(1).FaceColor = [8 108 162]./255;
b(2).FaceColor = [194 24 24]./255;