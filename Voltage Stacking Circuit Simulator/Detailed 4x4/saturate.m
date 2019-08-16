function B = saturate(A,up,low)
% B = saturate(A,up,low)
% ������ֵ����A�����ֵΪup����СֵΪlow
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
% ���Ʊ���x��С�ڷ�Χ[low up]֮��

if x <= low
    y = low;
elseif x >= up
    y = up;
else
    y = x;
end