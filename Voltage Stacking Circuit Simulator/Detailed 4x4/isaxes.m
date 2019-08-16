function flag = isaxes(h)   
% flag = isaxes(h)
% ÅĞ¶ÏhÊÇ·ñÎª×ø±êÖá¾ä±ú
% See Also: isfigure£¬ plot_with_arrow

if ishandle(h)
    if strcmp( 'axes' , get(h,'type') )
       flag = 1;
    else
        flag = 0;
    end
else
    flag = 0;
end;