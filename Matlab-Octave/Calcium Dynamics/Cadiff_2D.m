% Cadiff_2D.m

%% initialization of variables

tic
plot_num = 0; 
num_ions = 100000;

SR_xboundary = 50;
SR_yboundary = 0; % plots from 0 to 25
div = 2;
ybound_endSR = SR_yboundary+div;

Cyto_xboundary = 50;
Cyto_yboundary = 10; % plots from 20 to 30
ybound_endC = Cyto_yboundary+div;

% number of iterations
Iter = 10000;
%cru_range = 50; 

% position of ions in the SR
xpos_SR = randi([-SR_xboundary,SR_xboundary],num_ions,1);
ypos_SR = randi([SR_yboundary,ybound_endSR],num_ions,1);

%ions_SR = [xpos_SR ypos_SR];

% initialization positions of ions in cytosol. Set them to NaN
xpos_Cytosol = zeros(num_ions,1);
ypos_Cytosol = zeros(num_ions,1);

xpos_Cytosol(1:end) = NaN;
ypos_Cytosol(1:end) = NaN;

%ions_cyto  = [xpos_Cytosol ypos_Cytosol];

%% number of CRUs
num_openx = SR_xboundary;
num_openy = div; % it will be this number minus 1 due to boundary conditions
distx_cru = ((SR_xboundary*2)/num_openx);
disty_cru = (abs(SR_yboundary + (ybound_endSR))/num_openy);

cru_range = sqrt(distx_cru^2+disty_cru^2); 

CRUx = -SR_xboundary+1:distx_cru:SR_xboundary-1;
CRUy = SR_yboundary:disty_cru:ybound_endSR;
CRUx = round(CRUx);
CRUy = round(CRUy);

New = zeros(num_openx, num_openy);
%tic
for i = 1:num_openx
    
    New(i) = CRUx(i);
    
    for j = 2:num_openy
        
       New(i,j) = CRUy(j);
        
    end
    
end
%toc
%fprintf('Done with cru set up\n')

%tic
CRU = New(1:end,1:2);
for j = 3:num_openy
    
    CRU = [CRU; New(1:end,1) New(1:end,j)];
    
end
%toc
%fprintf('Done with cru set up B\n')

% obtain the number of CRUs
num_cru = length(CRU);


%% Probability function
pmax = 0.3;
pmin = 0.0001;
hillc = 10;
phalf = 100;

% S%tochas%tic Probability Function
fprob = @(n_ions) pmin+pmax*n_ions.^hillc./(n_ions.^hillc+phalf.^hillc);

% Determinis%tic Probability Function
%fprob = @(n_ions) 1*(n_ions>5); 

%% initialization of states
% 0 = closed; 1 = open; -1 = inactive. REFER to Markov Model

states = zeros((num_cru),1);
states(1) = 1;
t_inactive = zeros((num_cru),1);
t_open = zeros((num_cru),1);
t_open(1) = 1;

tau_open = 50; % time constant for how long open state will be
tau_inactive = 200; % time constant for how long inactive state will be

% radius. takes one step
r = 1;

%% Main Algorithm
for time = 1:Iter
    
    % Check state
    
    %tic 
    for i = 1:num_cru
        prand = rand(1);
        nc = 0;
        nc = sum(xpos_Cytosol<(CRU(i)+distx_cru/4) & xpos_Cytosol>(CRU(i)-distx_cru/4) & ypos_Cytosol>(CRU(i,2)+Cyto_yboundary-disty_cru/4)& ypos_Cytosol<(CRU(i,2)+Cyto_yboundary+disty_cru/4));
        tempx_Cytosol = xpos_Cytosol;
        tempx_Cytosol(isnan(tempx_Cytosol))=9001;
        tempy_Cytosol = ypos_Cytosol; 
        tempy_Cytosol(isnan(tempy_Cytosol)) = 9001; 
        
        %all_dist = sqrt((CRU(i,1)-tempx_Cytosol).^2+(CRU(i,2)-tempy_Cytosol).^2);
        %min(all_dist(:))
        %nc = sum(all_dist(:) < cru_range); 
        if nc > 0
            %fprintf(sprintf('CRU x=%f,y=%f; nc=%d\n', CRU(i,1), CRU(i,2), nc))
        end
        if states(i) == 0

            actual_prob = fprob(nc);

            if prand < actual_prob
               
                states(i) = 1;
                t_open(i) = time;
            end
            
        elseif states(i) == 1;
            
            if time >= (t_open(i) + tau_open)
                t_inactive(i) = time;
                states(i) = -1;
            end
            
        elseif states(i) == -1
            
            if time >= t_inactive(i) + tau_inactive
                states(i) = 0; 
            end

        end
        
        %when I am here i know what  my state is? 
        if states(i) == 1
            
            %rel_dist1 = cru_range;
            %rel_dist2 = disty_cru;
            %rel_dist = distx_cru/2;
            ind_move = abs(xpos_SR-CRU(i,1))<distx_cru/4 & abs(ypos_SR-CRU(i,2)<disty_cru/4);
            xpos_Cytosol(ind_move)=xpos_SR(ind_move);
            ypos_Cytosol(ind_move)=ypos_SR(ind_move) + Cyto_yboundary;
            
            xpos_SR(ind_move) = NaN;
            ypos_SR(ind_move) = NaN;

        end       
    end
    %toc
    %fprintf('Done counting ions at CRU\n')
 
    
    % Random Walk Simulation
    p1 = (rand(num_ions,1)*(2*pi));
    
    xpos_SR = xpos_SR + r*cos(p1);
    ypos_SR = ypos_SR + r*sin(p1);
    
    p2 = rand(num_ions,1)*(2*pi);
    
    xpos_Cytosol = xpos_Cytosol + r*cos(p2);
    ypos_Cytosol = ypos_Cytosol + r*sin(p2);
    
    % Boundary Conditions
    xpos_SR(xpos_SR<-SR_xboundary) = -SR_xboundary + abs(-SR_xboundary-xpos_SR(xpos_SR<-SR_xboundary));
    xpos_SR(xpos_SR>SR_xboundary) = SR_xboundary - abs(xpos_SR(xpos_SR>SR_xboundary)-SR_xboundary);
    
    ypos_SR(ypos_SR<SR_yboundary) = SR_yboundary + abs(SR_yboundary-ypos_SR(ypos_SR<SR_yboundary));
    ypos_SR(ypos_SR>ybound_endSR) = (ybound_endSR) - abs(ypos_SR(ypos_SR>ybound_endSR)-(ybound_endSR));    
    
    xpos_Cytosol(xpos_Cytosol<-Cyto_xboundary) = -Cyto_xboundary + abs(-Cyto_xboundary - xpos_Cytosol(xpos_Cytosol< -Cyto_xboundary));
    xpos_Cytosol(xpos_Cytosol>Cyto_xboundary) = Cyto_xboundary - abs(xpos_Cytosol(xpos_Cytosol>Cyto_xboundary) - Cyto_xboundary);
    
    ypos_Cytosol(ypos_Cytosol<=Cyto_yboundary) = Cyto_yboundary + abs(Cyto_yboundary- ypos_Cytosol(ypos_Cytosol<=Cyto_yboundary));
    ypos_Cytosol(ypos_Cytosol>=ybound_endC) = ybound_endC - abs(ypos_Cytosol(ypos_Cytosol>=ybound_endC)-ybound_endC);
    
    % Due to the random walk, they will be in decimal form. Therefore, I
    % rounded them to the nearest integer. 

    
    % move ions into the cytosol from SR.
    %xpos_SR = round(xpos_SR);
    %ypos_SR = round(ypos_SR);
    
    %xpos_Cytosol = round(xpos_Cytosol);
    %ypos_Cytosol = round(ypos_Cytosol);
    

        % Uptake  
        %random_num = rand(1, num_ions);
        %tic
        ind_uptake = rand(num_ions,1) < 0.01;
        ind_uptake = ind_uptake & ~isnan(xpos_Cytosol);
        xpos_SR(ind_uptake) = xpos_Cytosol(ind_uptake);
        ypos_SR(ind_uptake) = ypos_Cytosol(ind_uptake)-Cyto_yboundary;
        xpos_Cytosol(ind_uptake) = NaN;
        ypos_Cytosol(ind_uptake) = NaN;        
        %toc
        %fprintf('done the moving\n')
    % Status of states
    
   

        if mod(time,5) ==0
            
            f = figure('visible','off');
            % plot simulation
            %plot(xpos_SR, ypos_SR, 'ro');
            %hold on
            %plot(xpos_Cytosol, ypos_Cytosol, 'bo');
            h = histogram2(xpos_SR, ypos_SR, 'DisplayStyle', 'tile', 'FaceColor', 'flat', 'BinWidth', [distx_cru disty_cru], 'ShowEmptyBins', 'on');
            hold on
            plot([-SR_xboundary,SR_xboundary,SR_xboundary, -SR_xboundary,-SR_xboundary],[-SR_yboundary,-SR_yboundary,ybound_endSR,ybound_endSR, -SR_yboundary],'k-','linewidth', 3);
            hold on
            plot(CRU(:,1), CRU(:,2), 'ks');
            hold on
            l = histogram2(xpos_Cytosol, ypos_Cytosol,'DisplayStyle', 'tile', 'FaceColor', 'flat', 'BinWidth', [distx_cru disty_cru], 'ShowEmptyBins', 'on');
            hold on
            plot([-Cyto_xboundary,Cyto_xboundary,Cyto_xboundary, -Cyto_xboundary,-Cyto_xboundary],[Cyto_yboundary,Cyto_yboundary,ybound_endC,ybound_endC, Cyto_yboundary],'k-','linewidth', 3);
            hold on
            title(['time t=' num2str(time)]);
            hold on
            axis([-100 100 -5 15]);
            axis square
            %hold off
            c = colorbar;
            c.Limits = [0 200];
            caxis([0 200]);
            %ndhist([xpos_Cytosol, ypos_Cytosol]);
            %if(time==2)
            %    pause(0.5);
            %else
            %    pause(0.001);
            %end
            f_name = sprintf('fsave%.4d',plot_num);
            plot_num = plot_num+1; 
            saveas(f,f_name,'png');
            %fprintf('PING\n');
        end

end
toc