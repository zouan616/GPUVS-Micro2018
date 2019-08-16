function isc = ischild(hc,hp)
% isc = ischild(hc,hp)
% 判断句柄hc是不是hp的子对象

hc_list = allchild(hp);
% isc = any( arrayfun( @(x) x == hc , hc_list ) );   % 这里直接使用的等号判断，不知是否会存在数值误差问题
                                                     % 下面予以更正  
eps = 1e-8;
isc = any( arrayfun( @(x) abs(x-hc)<=eps , hc_list ) );                                      
