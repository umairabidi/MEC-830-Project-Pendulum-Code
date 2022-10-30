Vth_high = @(R1,R2,R3,Vcc,Vout)(R2*(R3*Vcc+R1*Vout))/(R1*R2+R1*R3+R2*R3);
Vth_low = @(R1,R2,R3,Vcc,Vout)(R2*R3*Vcc)/(R1*R2+R1*R3+R2*R3);

R1 = 47000;
R2 = 47000;
R3 = 1000;
Vcc = 3.5;
Vout = 3.5;

Vth_low_val = Vth_low(R1,R2,R3,Vcc,Vout)
Vth_high_val = Vth_high(R1,R2,R3,Vcc,Vout)