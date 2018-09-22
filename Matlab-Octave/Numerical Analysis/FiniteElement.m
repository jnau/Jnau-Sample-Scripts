function C = finelement(N, x, p,q,f)

    h = zeros(N,1);
    
    Q1 = zeros(N,1);
    Q2 = zeros(N,1);
    Q3 = zeros(N,1);
    Q4 = zeros(N,1);
    Q5 = zeros(N,1);
    Q6 = zeros(N,1);
    a = zeros(N,1);
    b = zeros(N,1);
    alpha = zeros(N,1);
    beta = zeros(N,1);
    chi = zeros(N,1);
    z = zeros(N,1);
    c = zeros(N,1);
    
    for i = 1:N
        
        h(i) = x(i+1)-x(i);
        
        if i <= N-1

            Q1(i) = (h(i)/12)*(q(x(i))+q(x(i+1)));
            Q3(i) = (h(i)/12)*(3*q(x(i))+q(x(i+1)));
            Q6(i) = (h(i)/6)*(2*f(x(i))+f(x(i+1)));
            
        end
        
        if i > 1

            Q2(i-1) = (h(i)/12)*(3*q(x(i))+q(x(i-1)));
            Q5(i-1) = (h(i-1)/6)*(2*f(x(i))+f(x(i-1)));
            Q4(i-1) = (p(x(i))+p(i-1))*(1/(2*h(i-1)));
            
        end
  
    end
    
    for k = 1:N-1
        
        alpha(k) = Q4(k) + Q4(k+1) + Q2(k) + Q3(k);
        beta(k) = -Q4(k+1) + Q1(k);
        b(k) = Q5(i) + Q6(i); 

    end
    
    alpha(N) = Q4(N) + Q4(N+1) +Q2(N) + Q3(N);
    b(N) = Q5(N) + Q6(N);
    
    a(1) = alpha(1);
    chi(1) = beta(1)/alpha(1);
    z(1) = b(1)/a(1);
    
    for j = 2:N-1
        
        a(j) = alpha(j) - beta(j-1)*chi(j-1);
        chi(j) = beta(j)/a(j);
        z(j) = (b(j) - beta(j-1)*z(j-1))/a(j);
        
    end

    a(N) = alpha(N) - beta(N-1)*chi(N-1);
    z(N) = (b(N) - beta(N-1)*z(N-1))/a(N);
    
    
    c(N) = z(N); 
    
    for l = N-1:1
        
        c(l) = z(l)-chi(l)*c(l+1);
        
    end
    
    C = c;

end
