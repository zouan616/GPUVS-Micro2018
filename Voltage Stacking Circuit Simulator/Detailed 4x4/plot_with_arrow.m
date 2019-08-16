function  [h h_a h_p h_arrow] = plot_with_arrow( h,x,y,style,pos,plot_fun,Attribute_Set,options )
% [h h_a h_p h_arrow] = plot_with_arrow( h,x,y,style,pos,plot_fun,Attribute_Set,options )
% ������ͷ��ͼ��
% ���룺
%   h������ѡ�� 1. ������      []          ������figure��axes
%                2. ͼ�ξ��    h_figure    ������axes
%                3. ��������  h_axes  
%   x-yΪ���ݶԣ����ݶ�Ϊ[]ʱ��ֻ���Ƽ�ͷ�����ᣬ���������ߣ�����ֵ h_p = []
%   styleΪ������ʽ����ɫ
%   pos���ڿ����������λ��
%                          p  ��   n  ��    a ȫ 
%              'pp' �������ڵ�1����     
%              'pa' �������ڵ�1��4����
%              'ap' �������ڵ�1��2����  
%              'aa' �������ڵ�1��2��3��4����
%               'n' ��ʾ��ͷ����������λ��λ��2��3���� 
%               Ҳ����pos��ֱ�������ͷ��ʼλ�����꣬��ʽΪ [X0 Y0 Xi Yi X_y Y_x]
%                                                  ����������Ӻ���   Arrow_XY 
%               plot_fun  ��ͼ�����������ʽ��Ĭ��Ϊplot
%               Attribute_Set Ϊ��ͷ���ԣ�����Ԫ�����飬��һ��Ϊ���������ڶ���Ϊ����ֵ 
%                             Ҳ�ɶԷ��صļ�ͷ���h_arrow������������������  
%    options��ͼ����ѡ�ֵ��Ϊ��     ѡ����          ���           ����
%                                FixAxesPosition      1         �̶�������λ�� 
%                              CorrectArrowPos_pp     2         У����ͷ����λ�ã�ʹ����axes��ȫ����
% ����ֵ 
%     h       ͼ�ξ��
%     h_a     �������� 
%     h_p     ���߾��
%     h_arrow ��ͷ��� [h_xa h_ya] �������
% �����ļ���plot_with_arrow_Test.m
% By ZFS@wust  2011.11.29                 
% 2012.04.19 �ģ��������� pos    plot_fun
%                �������� Attribute_Set ��������Ԫ������    
%                ������� h_arrow   h_arrow������typeΪhggroup
%       04.21    pos�м���ѡ�n��  ����ѡ��options
% See Also: Arrow_Xlabel, Arrow_Ylabel,  Arrow_XY,  isaxes,  isfigure�� saturate

  

% ����Ĭ��ֵ
if nargin < 8 
    options = {'FixAxesPosition','CorrectArrowPos_pp'};
end
if nargin < 7 
    Attribute_Set = [];
end
if nargin < 6 
    plot_fun = @plot;
end
if nargin < 5
    pos = 'pp';
end
if nargin < 4
    style = 'k';
end
if nargin < 2
    x = [];
end
if nargin < 1
    h = [];
end


% ���������ʱ��ʹ��Ĭ��ֵ
if isempty(plot_fun)
    plot_fun = @plot;
end
if isempty(pos)
    pos = 'pp';
end
if isempty(style)
    style = 'k';
end

% ���h��ƥ��
if isempty(h)        % δ����hʱ
    h = figure; 
    h_a = get(h,'CurrentAxes');       % ���figure�ĵ�ǰ������λ��
elseif  isfigure(h)             % �����h��figure���ʱ
    h_a = get(h,'CurrentAxes');       % ���figure�ĵ�ǰ������λ�� 
elseif isaxes(h)  % �����h����������ʱ
    h_a = h;
    h = get(h,'parent');                 
else
    error('h����Ϊ������һ�֣�1.������(�½�ͼ�κ�������)  2.��������  3.ͼ�ξ��');
end

rec = get(h_a,'position');         % ���axes��λ�� 
if isempty(rec)                    % ��axesΪ�գ����½�axes
    h_a = axes('parent',h);         % ����һ��axes,ʹ����Ϊfigure���Ӷ���
    rec = get(h_a,'position');  
end

box off

if ~isempty(x)
    h_p = plot_fun( h_a,x,y,style );   % ��axes�ϻ�ͼ
else
    h_p =[];
end
    
hold on

if isnumeric(pos) && length(pos) == 6
    [X0 Y0 Xi Yi X_y Y_x] =  deal( pos(1),pos(2),...
      pos(3),pos(4),pos(5),pos(6)  );         % ֱ������ļ�ͷ����ʼλ��                
else
    [X0 Y0 Xi Yi X_y Y_x] = Arrow_XY(rec,pos);         % �����Զ��庯��ȷ����ͷ����ʼλ��
end

pos_temp = saturate([X0 Y0 Xi Yi X_y Y_x],1,0);        % ���Ʒ�ֵ  
[X0 Y0 Xi Yi X_y Y_x] =  deal( pos_temp(1),pos_temp(2),...
      pos_temp(3),pos_temp(4),pos_temp(5),pos_temp(6)  );
  
arrowY = annotation(h,'arrow',[X_y X_y],[Y0 Yi]);    % Y��
set(arrowY,'HeadStyle','plain','HeadWidth',6);       % �޸ļ�ͷ����
arrowX = annotation(h,'arrow',[X0 Xi],[Y_x Y_x]);    % X��
set(arrowX,'HeadStyle','plain','HeadWidth',6);       % �޸ļ�ͷ����

% Attribute_Set�������������
if ~isempty(Attribute_Set)
  [m n] = size(Attribute_Set);    % mΪ��Ҫ���õ�������Ŀ��n����Ϊ2                        
  if m == 2 && n == 1
      set( arrowY,Attribute_Set{1},Attribute_Set{2} );
      set( arrowX,Attribute_Set{1},Attribute_Set{2} );
  elseif n ~= 2
      error('Attribute_Set must be Two-Row Cell Matrix��');
  else
      for ii = 1:m
             set( arrowY,Attribute_Set{ii},Attribute_Set{2} );
             set( arrowX,Attribute_Set{ii},Attribute_Set{2} );
      end
  end
end

h_arrow = [arrowX arrowY];   % ���ؼ�ͷ��������


% ѡ��optionsת��Ϊֵvalues
if ~isempty(options)             % options �ǿ�ʱ 
    if iscell( options )         % options Ϊ�ַ���Ԫ��ʱ
          values = option2value(options);
    elseif isnumeric( options )  % ֱ���������ѡ��ֵʱ
          values = options;
    end
else                             % option����Ϊ[]ʱ            
    values = [];
end

% ����ѡ����������
for ii = 1:length(values)
    opt_value = values(ii);
    switch opt_value
        case 1           % �̶������ᣬ��ʹfigure�ڵ�����С�����У�Ҳ�ܱ�֤axesλ�ù̶�������ʹ��axes���ͷ��������ȫ����
           rec_axes = get(h_a,'position'); 
           set(h_a,'position',rec_axes);

        case 2           % У����ͷ�����ᣬʹ����ȫ��axes����    
            if strcmp(pos,'pp')     % ����������λ��ΪppʱУ��
                % ����x��
                rec1 = get(h_arrow(1),'position');
                rec1(2) = rec1(2) - 0.001;
                rec1(1) = rec1(1) + 0.001;
                set(h_arrow(1),'position',rec1);
                % ����y��
                rec2 = get(h_arrow(2),'position');
                rec2(1) = rec2(1) +0.001;
                set(h_arrow(2),'position',rec2);
            end
            
        otherwise
            warning('��Чѡ��');
    end
end


% ͼ����ʾ����
hold off
set(h,'color','w')
if strcmp(pos,'pp')  % ����pos='pp'ʱ��������������
   box off
else
   axis off
end


function values = option2value(options)
% ��ѡ���ַ�Ԫ�������ֵ����
% options �ַ���Ԫ������
% values  ��ֵ����

options_all = {'FixAxesPosition','CorrectArrowPos_pp'};
n = length( options );
values = [];
for ii = 1:n
    sub = strmatch(options{ii},options_all,'exact');
    values = [values sub];
end



