
p = rand(1,12000);
p = p';



SM1 = 1.*[p p p p p p]./6;
p = rand(1,12000);
p = p';


SM2 = 1.*[p p p p p p]./6;
p = rand(1,12000);
p = p';

SM3 = 1.*[p p p p p p]./6;
p = rand(1,12000);
p = p';

SM4 = 1.*[p p p p p p]./6;
p = rand(1,12000);
p = p';

SM5 = 1.*[p p p p p p]./6;
p = rand(1,12000);
p = p';

SM6 = 1.*[p p p p p p]./6;
p = rand(1,12000);
p = p';

SM7 = 1.*[p p p p p p]./6;
p = rand(1,12000);
p = p';

SM8 = 1.*[p p p p p p]./6;
p = rand(1,12000);
p = p';

SM9 = 1.*[p p p p p p]./6;
p = rand(1,12000);
p = p';

SM10 = 1.*[p p p p p p]./6;
p = rand(1,12000);
p = p';

SM11 = 1.*[p p p p p p]./6;
p = rand(1,12000);
p = p';

SM12 = 1.*[p p p p p p]./6;
p = rand(1,12000);
p = p';

SM13 = 1.*[p p p p p p]./6;
p = rand(1,12000);
p = p';


SM14 = 1.*[p p p p p p]./6;
p = rand(1,12000);
p = p';

SM15 = 1.*[p p p p p p]./6;
p = rand(1,12000);
p = p';

SM16 = 1.*[p p p p p p]./6;
p = rand(1,12000);
p = p';


P = [SM1 SM2 SM3 SM4 SM5 SM6 SM7 SM8 SM9 SM10 SM11 SM12 SM13 SM14 SM15 SM16];




csvwrite('global_100K.txt',P)

