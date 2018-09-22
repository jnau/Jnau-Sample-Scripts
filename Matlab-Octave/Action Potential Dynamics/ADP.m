% APD.m
% code written is finding Action Potential Duration (APD) for time = n+1 based on the data found by APD at time = n. 

% declare constants
tauso = 15.0; 
taufi = 0.8;
tauh1 = 4.8;
tauh2 = 10.0;
tausi = 4.0;
tauf1 = 100.0;
tauf2 = 30.0;

dt = 0.1; % time step in (ms)

% intial values
v = 0.0; %membrane voltage
h = 0.8; %Na channel inactivation gate
f = 0.5; %Ca channel inactivation gate

% create arrays for results

resultapd = [];
resultpcl = []; % pacing cycle length (PCL)
resultdi = []; % Diastolic Interval (DI)
resultapdn = [];
resultdif = []; 

for pcl=400:-1:130 %varying pacing cycle length in (ms)

    itr = 200; %number of beats
    tmax = pcl*itr; %total time
    
    %converting to integer
    tnmax = round(tmax/dt);
    pcln = round(pcl/dt);
    durn = round(2.0/dt);
    
    %main loop
    oldv = 0;

    for tn=0:tnmax
        
        %stimulation
        stim = 0;
        if (mod(tn,pcln)<durn) 
            stim = 0.3;
        end;
        
        minf = ((v/0.2).^6)./(1 + ((v/0.2).^6));
        hinf = 1./(1+((v/0.1).^6));
        dinf = ((v/0.4).^4)./(1+((v/0.4).^4));
        finf = 1./(1+(v/0.1).^4);

        tauh = tauh1 + tauh2*exp(-20*((v-0.1).^2));
        tauf = tauf2 + (tauf1-tauf2).*v.^3;
        
        %tauf = tauf*1.6;

        jfi = h.*minf.*(v-1.3)/taufi;
        jso = (1-exp(-4*v))/tauso;
        jsi = f.*dinf.*(v-1.4)/tausi;
        ion = -(jfi+jsi+jso-stim);

        %update variables here
        oldv = v;
        v = v + ion*dt;
        h = h + dt*(hinf - h)./tauh;
        f = f + dt*(finf - f)./tauf;
        
        if (v > 0.1 && oldv < 0.1)
            aV = (oldv-v)/dt;
            bV = oldv-aV*tn*dt;
            APDt1 = (0.1-bV)/aV;
            
           
        elseif (v<0.1 && oldv > 0.1)
            aV = (oldv-v)/dt;
            bV = oldv-aV*tn*dt; 
            APDt2 = (0.1-bV)/aV;
            
            
            if (tn*dt>pcl*(itr-2)) 
          
                apd = APDt2 - APDt1;
                di = pcl - apd;
            
                resultdi = [resultdi di]; 
                resultapd = [resultapd apd];
                resultpcl = [resultpcl pcl];

            end
        end   
    end
end

%APD_n+1 is found after DI_n. Used brute force 
resultapdn = [resultapdn resultapd(1,2:end)];
resultdif = [resultdif resultdi(1,1:end-1)];

%plot results
figure
plot(resultpcl, resultapd, '.'); %APD vs PCL

%figure
%plot(resultdif, resultapdn, '.');
%plot(resultapdn, resultdif, '.'); %APD_n+1 vs DI_n