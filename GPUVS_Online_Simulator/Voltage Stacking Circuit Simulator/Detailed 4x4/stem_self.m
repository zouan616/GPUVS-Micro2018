function h_p = stem_self(ha,x,y,color)
% �Զ���stem������ȥ��ϵͳ�����е�0λ�ߣ����ʺϴ���������ͼ
% ����ֵΪ������������markԲ���

axes(ha);
hold on
n = length(x);
for ii = 1:n
   h_p(ii) = line([x(ii) x(ii)],[0 y(ii)],'color',color );
end

h_o = plot(ha,x,y,'o');
set(h_o,'color',color);

h_p = [h_p h_o];