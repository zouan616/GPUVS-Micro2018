function  [h h_a h_p h_arrow] = plot_with_arrow( h,x,y,style,pos,plot_fun,Attribute_Set,options )
% [h h_a h_p h_arrow] = plot_with_arrow( h,x,y,style,pos,plot_fun,Attribute_Set,options )
% 画带箭头的图形
% 输入：
%   h有三种选择： 1. 空数组      []          生成新figure及axes
%                2. 图形句柄    h_figure    新生成axes
%                3. 坐标轴句柄  h_axes  
%   x-y为数据对，数据对为[]时，只绘制箭头坐标轴，不绘制曲线，返回值 h_p = []
%   style为曲线样式或颜色
%   pos用于控制坐标轴的位置
%                          p  正   n  负    a 全 
%              'pp' 坐标轴在第1象限     
%              'pa' 坐标轴在第1、4象限
%              'ap' 坐标轴在第1、2象限  
%              'aa' 坐标轴在第1、2、3、4象限
%               'n' 表示箭头反向，坐标轴位置位于2、3象限 
%               也可在pos中直接输入箭头起始位置坐标，格式为 [X0 Y0 Xi Yi X_y Y_x]
%                                                  具体意义见子函数   Arrow_XY 
%               plot_fun  绘图函数，句柄格式，默认为plot
%               Attribute_Set 为箭头属性，两列元胞数组，第一列为属性名，第二列为属性值 
%                             也可对返回的箭头句柄h_arrow操作，来设置其属性  
%    options绘图设置选项，值可为：     选项名          标号           功能
%                                FixAxesPosition      1         固定坐标轴位置 
%                              CorrectArrowPos_pp     2         校正箭头坐标位置，使其与axes完全贴合
% 返回值 
%     h       图形句柄
%     h_a     坐标轴句柄 
%     h_p     曲线句柄
%     h_arrow 箭头句柄 [h_xa h_ya] 句柄向量
% 测试文件：plot_with_arrow_Test.m
% By ZFS@wust  2011.11.29                 
% 2012.04.19 改：增加输入 pos    plot_fun
%                增加输入 Attribute_Set 属性设置元胞数组    
%                增加输出 h_arrow   h_arrow的类型type为hggroup
%       04.21    pos中加上选项‘n’  增加选项options
% See Also: Arrow_Xlabel, Arrow_Ylabel,  Arrow_XY,  isaxes,  isfigure， saturate

  

% 参数默认值
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


% 参数输入空时，使用默认值
if isempty(plot_fun)
    plot_fun = @plot;
end
if isempty(pos)
    pos = 'pp';
end
if isempty(style)
    style = 'k';
end

% 句柄h的匹配
if isempty(h)        % 未输入h时
    h = figure; 
    h_a = get(h,'CurrentAxes');       % 获得figure的当前坐标轴位置
elseif  isfigure(h)             % 输入的h是figure句柄时
    h_a = get(h,'CurrentAxes');       % 获得figure的当前坐标轴位置 
elseif isaxes(h)  % 输入的h是坐标轴句柄时
    h_a = h;
    h = get(h,'parent');                 
else
    error('h必须为下列任一种：1.空数组(新建图形和坐标轴)  2.坐标轴句柄  3.图形句柄');
end

rec = get(h_a,'position');         % 获得axes的位置 
if isempty(rec)                    % 若axes为空，则新建axes
    h_a = axes('parent',h);         % 定义一个axes,使其作为figure的子对象
    rec = get(h_a,'position');  
end

box off

if ~isempty(x)
    h_p = plot_fun( h_a,x,y,style );   % 在axes上绘图
else
    h_p =[];
end
    
hold on

if isnumeric(pos) && length(pos) == 6
    [X0 Y0 Xi Yi X_y Y_x] =  deal( pos(1),pos(2),...
      pos(3),pos(4),pos(5),pos(6)  );         % 直接输入的箭头的起始位置                
else
    [X0 Y0 Xi Yi X_y Y_x] = Arrow_XY(rec,pos);         % 调用自定义函数确定箭头的起始位置
end

pos_temp = saturate([X0 Y0 Xi Yi X_y Y_x],1,0);        % 限制幅值  
[X0 Y0 Xi Yi X_y Y_x] =  deal( pos_temp(1),pos_temp(2),...
      pos_temp(3),pos_temp(4),pos_temp(5),pos_temp(6)  );
  
arrowY = annotation(h,'arrow',[X_y X_y],[Y0 Yi]);    % Y轴
set(arrowY,'HeadStyle','plain','HeadWidth',6);       % 修改箭头属性
arrowX = annotation(h,'arrow',[X0 Xi],[Y_x Y_x]);    % X轴
set(arrowX,'HeadStyle','plain','HeadWidth',6);       % 修改箭头属性

% Attribute_Set输入的属性设置
if ~isempty(Attribute_Set)
  [m n] = size(Attribute_Set);    % m为需要设置的属性数目，n必须为2                        
  if m == 2 && n == 1
      set( arrowY,Attribute_Set{1},Attribute_Set{2} );
      set( arrowX,Attribute_Set{1},Attribute_Set{2} );
  elseif n ~= 2
      error('Attribute_Set must be Two-Row Cell Matrix！');
  else
      for ii = 1:m
             set( arrowY,Attribute_Set{ii},Attribute_Set{2} );
             set( arrowX,Attribute_Set{ii},Attribute_Set{2} );
      end
  end
end

h_arrow = [arrowX arrowY];   % 返回箭头坐标轴句柄


% 选项options转换为值values
if ~isempty(options)             % options 非空时 
    if iscell( options )         % options 为字符串元胞时
          values = option2value(options);
    elseif isnumeric( options )  % 直接输入的是选项值时
          values = options;
    end
else                             % option输入为[]时            
    values = [];
end

% 根据选项设置属性
for ii = 1:length(values)
    opt_value = values(ii);
    switch opt_value
        case 1           % 固定坐标轴，即使figure在调整大小过程中，也能保证axes位置固定，进而使得axes与箭头坐标轴完全贴合
           rec_axes = get(h_a,'position'); 
           set(h_a,'position',rec_axes);

        case 2           % 校正箭头坐标轴，使其完全与axes贴合    
            if strcmp(pos,'pp')     % 仅在坐标轴位置为pp时校正
                % 设置x轴
                rec1 = get(h_arrow(1),'position');
                rec1(2) = rec1(2) - 0.001;
                rec1(1) = rec1(1) + 0.001;
                set(h_arrow(1),'position',rec1);
                % 设置y轴
                rec2 = get(h_arrow(2),'position');
                rec2(1) = rec2(1) +0.001;
                set(h_arrow(2),'position',rec2);
            end
            
        otherwise
            warning('无效选项');
    end
end


% 图形显示设置
hold off
set(h,'color','w')
if strcmp(pos,'pp')  % 仅在pos='pp'时，不消除坐标轴
   box off
else
   axis off
end


function values = option2value(options)
% 求选项字符元胞数组的值向量
% options 字符串元胞数组
% values  数值向量

options_all = {'FixAxesPosition','CorrectArrowPos_pp'};
n = length( options );
values = [];
for ii = 1:n
    sub = strmatch(options{ii},options_all,'exact');
    values = [values sub];
end



