%input
N = 15; % number of atoms
L = 10; % size of system

%declare vectors
p = zeros(N,2);
v = zeros(N,2);
a = zeros(N,2);
p1 = zeros(N,2); % position at n-1
pn = zeros(N,2); % position at n+1

%initialization of position
xp = randi([1 2*L], N, 1);
yp = randi([1 2*L], N, 1);
deltar = 0.25;

p(1:N) = 2.*(xp-0.5).*deltar;
p(N+1:N*2) = 2.*(yp-0.5).*deltar;

%initialization of velocity
v0 = 1; % same as book
v(1:N) = abs(2.*(p(1:N)-0.5).*v0);
v(N+1:N*2) = abs(2.*(p(N+1:2*N)-0.5).*v0);

% initialization of position at t = -1
dt = .001;
time = 100;
tmax = time/dt;

p1(1:N) = abs(p(1:N)-(v(1:N)*dt));
p1(N+1:N*2) = abs(p(N+1:N*2)-(v(N+1:N*2)*dt));

% initialize vectors
r = zeros(N, 2);
f = zeros(N, 2);

% acceleration vectors: ax, ay
% sum acceleration vectors: sx, sy (dummy variables)
ax = zeros(N,2);
ay = zeros(N,2);
sx = zeros(N,2);
sy = zeros(N,2);


%verlet algorithm
for t = 1:tmax %every time interval that updating
  
    % find distances for all atoms and their forces
    for i = 1:N
        for j = 1:N
            r(i,j) = (sqrt((p(j)-p(i))^2 + (p(j+N)-p(i+N))^2));
            
            if i ~= j && r(i,j) < 3.0 && r(i,j) > 1.1
                f(i,j) = abs(24*((2/(r(i,j)^13))-(1/r(i,j)^7)));
                
            %magnitude of 24. I will explain in write up. 
            elseif i ~=j && r(i,j) > 0.0 && r(i,j) <= 1.1
                f(i,j) = (168)/r(i,j);
            else
                f(i,j) = 0;
            end
        end
    end


    % acceleration of components
    for i = 1:N
        for j = 1:N
            dx = (p(j)-p(i));
            dy = (p(j+N)-p(i+N));
            
            if j ~= i 
                sx(i,j) = f(i,j)*(dx/(r(i,j)));
                sy(i,j) = f(i,j)*(dy/(r(i,j)));
            else 
                sx(i,j) = 0;
                sy(i,j) = 0;
            end
        end

        
    end
    ax = sum(sx);
    ay = sum(sy);
    
    % update positions 
    pn(1:N) = ((2*p(1:N))-p1(1:N) + ax(1:N).*dt^2); 
    pn(N+1:2*N) = ((2*p(N+1:2*N))-p1(N+1:2*N) + ay(1:N).*dt^2); 

    % boundary conditions, comes after updating position
    for i = 1:N
        for j = 1:2
            if (pn(i,j) > L); 
                pn(i,j) = pn(i,j) - 2*L; 
            end
            if (pn(i,j) < 0.0); 
                pn(i,j) = pn(i,j) + 2*L; 
            end
        end
    end
    
    % update velocity (after pbc)
    v(1:N) = abs(pn(1:N)-p1(1:N)/(2*dt));
    v(N+1:2*N) = abs(pn(N+1:2*N)-p1(N+1:2*N)/(2*dt));

    % new (n-1), and n
    p1(1:N) = p(1:N);
    p1(N+1:2*N) = p(N+1:2*N);
    
    p(1:N) = pn(1:N);
    p(N+1:2*N) = pn(N+1:2*N);
   
    %AvoNum = 6.02*10^23
   % R = 8.31
   
   % molecular mass of argon: 39.948 g/mol, convert to kg. 
  
    B = 1.38*10^-23;
    T= (((9.96e-25)/2)*mean(v(1:N).^2+v(N+1:2*N).^2))/(B);
    
    %totalV = sum(sum(v.^2,1)); %first v^2, then take sum of col's then total sum
    %KinE = .5*totalV; %in reduced units 39.948 should be 1?
    %T = 2*KinE/(N*(3)); %in reduced units no R no AvoNum
    %display (KinE);
    %KinE = (1/2)*(9.95*10^-19)*mean(v(1:N).^2+v(N+1:2*N).^2);
    %Ts = (2*KinE)/(3*B);
    %T2 = sum(Ts);
    
    % make simulation
    plot(p(1:N),p(N+1:N*2), 'ro');
    grid;
    axis([0 2*L 0 2*L]);
    axis square;
    pause(0.0001);   

    display(T);

   
end

