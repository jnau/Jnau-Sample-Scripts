function R = rungekutta(x0,y0,a,b, h)

    %define functions
    fx = @(t,x,y) -1000*x + y;
    fy = @(t,x,y) -1/10*y;

    N = (b-a)/h;
    y = ones(N+1,1);
    x = ones(N+1,1);
    t = ones(N+1,1);
    
    y(1) = y0;
    x(1)= x0;
    t(1) = a;
    
    for i = 1:N
        q1x = fx(t(i), x(i), y(i));
        q1y = fy(t(i), x(i), y(i));
        
        q2x = fx(t(i)+(h/2), x(i)+((h/2)*q1x), y(i)+((h/2)*q1y));
        q2y = fx(t(i)+(h/2), x(i)+((h/2)*q1x), y(i)+((h/2)*q1y));
        
        q3x = fx(t(i)+(h/2), x(i)+((h/2)*q2x), y(i)+((h/2)*q2y));
        q3y = fx(t(i)+(h/2), x(i)+((h/2)*q2x), y(i)+((h/2)*q2y));
        
        q4x = fx(t(i)+(h), x(i)+(h*q3x), y(i)+(h*q3y));
        q4y = fx(t(i)+(h), x(i)+(h*q3x), y(i)+(h*q3y));
        
        x(i+1) = (h/6)*(q1x + 2*q2x + 2*q3x + q4x);
        y(i+1) = (h/6)*(q1y + 2*q2y + 2*q3y + q4y);
        
        t(i+1) = t(i) + h;
        
    end
    
    figure
    plot(t,y);
    R = y;

end
