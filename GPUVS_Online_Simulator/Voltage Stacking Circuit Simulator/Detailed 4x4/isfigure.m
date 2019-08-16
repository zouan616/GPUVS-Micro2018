function flag = isfigure(h) 
% flag = isfigure(h) 
% 判断h是不是图形句柄
% See Also: isaxes, plot_with_arrow

if ishandle(h)
    if strcmp( 'figure' , get(h,'type') )
       flag = 1;
    else
        flag = 0;
    end
else
    flag = 0;
end

end