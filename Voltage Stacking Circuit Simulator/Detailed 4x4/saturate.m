function B = saturate(A,up,low)
% B = saturate(A,up,low)
% 限制数值矩阵A的最大值为up，最小值为low
% Example1:   A = rand(10);
%             B = saturate(A,0.8,0.4)   
% Example2:   A = 'abcdefghijklmnopqrst';
%             B = saturate(A,'k','d')  
% By ZFS@wust 2012.04.22

Up  = repmat(up,size(A));
Low = repmat(low,size(A));
B = arrayfun(@limit_value,A,Up,Low);


function y = limit_value(x,up,low)
% y = limit_value(x,up,low)
% 限制标量x大小在范围[low up]之间

if x <= low
    y = low;
elseif x >= up
    y = up;
else
    y = x;
end