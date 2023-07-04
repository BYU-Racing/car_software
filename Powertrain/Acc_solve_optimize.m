%%%%%%%%%%%%%%%%%%%%%%% Motor paramenters %%%%%%%%%%%%%%%%%%%%%%

em_208_1 = zeros(10,1); % Emrax 208 profile, 80 kw, 63.75% efficient
transition_rpm = 3500; % point at which torque drops
max_rpm = 7000;
max_torque = 125; % torque at the max power level (80kw*efficiency)
% controller_efficiency = 0.75;
% motor_efficiency = 0.85;
torque_decay = (-max_torque/(max_rpm-transition_rpm)); % N*m/rpm

em_208_1(1) = transition_rpm;
em_208_1(2) = max_rpm;
em_208_1(3) = max_torque;
em_208_1(4) = torque_decay;



em_228_1 = zeros(10,1); % Emrax 228 profile, 80 kw, 63.75% efficient
transition_rpm = 2225; % point at which torque drops
max_rpm = 6500;
max_torque = 168; % torque at the max power level (80kw*efficiency)
% controller_efficiency = 0.75;
% motor_efficiency = 0.92;
torque_decay = (-max_torque/(max_rpm-transition_rpm)); % N*m/rpm

em_228_1(1) = transition_rpm;
em_228_1(2) = max_rpm;
em_228_1(3) = max_torque;
em_228_1(4) = torque_decay;


%%%%%%%%%%%%%%%%%%%%%%% Vehicle paramenters %%%%%%%%%%%%%%%%%%%%%%

vehicle_1 = zeros(30,1); % Current vehicle profile
r = .2032; % distance from axle center to ground, m
m_driver = 68;% driver mass, kg
m_car = 164; % vehicle mass, kg
m = m_driver+m_car; % combined mass
g = 9.81; % gravity, m/s^2

Cd = .7; % coeff of aero drag
p = 1.1785; % air density, kg/m^3
A = .9593; % frontal area, m^2

Cr = 0.002; % estimate for rolling coefficient
C_motor = .001; % sum of damping on the motor side
C_axle = .01; % sum of damping on the axle side

mu = 1.1; % traction coefficient
l = 2; % wheelbase, m
la = l*.6; % center of gravity to the front axle, m
Rb = m*g*la/l; % static normal weight on the rear tires, N
h = .3; % height of center of gravity off ground, m

vehicle_1(1) = r;
vehicle_1(2) = m_driver;
vehicle_1(3) = m_car;
vehicle_1(4) = m;
vehicle_1(5) = g;
vehicle_1(6) = Cd;
vehicle_1(7) = p;
vehicle_1(8) = A;
vehicle_1(9) = Cr;
vehicle_1(10) = C_motor;
vehicle_1(11) = C_axle;
vehicle_1(12) = mu;
vehicle_1(13) = l;
vehicle_1(14) = la;
vehicle_1(15) = Rb;
vehicle_1(16) = h;

%%%%%%%%% Vehicle 2 is less optimistic %%%%%%%%%%

vehicle_2 = zeros(30,1); % Heavy vehicle profile
r = .2032; % distance from axle center to ground, m
m_driver = 68;% driver mass, kg
m_car = 220; % vehicle mass, kg
m = m_driver+m_car; % combined mass
g = 9.81; % gravity, m/s^2

Cd = .7; % coeff of aero drag
p = 1.1785; % air density, kg/m^3
A = .9593; % frontal area, m^2

Cr = 0.002; % estimate for rolling coefficient
C_motor = .001; % sum of damping on the motor side
C_axle = .01; % sum of damping on the axle side

mu = 1.1; % traction coefficient
l = 2; % wheelbase, m
la = l*.6; % center of gravity to the front axle, m
Rb = m*g*la/l; % static normal weight on the rear tires, N
h = .3; % height of center of gravity off ground, m

vehicle_2(1) = r;
vehicle_2(2) = m_driver;
vehicle_2(3) = m_car;
vehicle_2(4) = m;
vehicle_2(5) = g;
vehicle_2(6) = Cd;
vehicle_2(7) = p;
vehicle_2(8) = A;
vehicle_2(9) = Cr;
vehicle_2(10) = C_motor;
vehicle_2(11) = C_axle;
vehicle_2(12) = mu;
vehicle_2(13) = l;
vehicle_2(14) = la;
vehicle_2(15) = Rb;
vehicle_2(16) = h;

%%%%%%%%%%%%%%%%%%%%%% ODE Solver and parameters %%%%%%%%%%%%%%%%%%%%%%

x_goal = 75; % target distance, meters
v_goal = 26.822; % target velocity, m/s
gear_range = 2:.1:5;
t_x_goal = zeros(length(gear_range),1); % times to x target
t_v_goal = zeros(length(gear_range),1); % times to v target

for i = 1:length(gear_range)
    n = gear_range(i); % gear ratio, driven/driver

    tspan = [(0:.0005:6)]; % [T0:step_size:TFINAL]
    x0 = [0 0]; % Initial conditions [velocity, displacement]
    [t,x] = ode45(@(t,x) Acc_eom(t,x,n,em_228_1,vehicle_2), tspan, x0);

    v1 = x(:,1); % 1st column, velocity
    x1 = x(:,2); % 2nd column, displacement

    [ d_x, ix_x ] = min( abs( x1-x_goal ) );
    [ d_v, ix_v ] = min( abs( v1-v_goal ) );

    t_x_goal(i) = t(ix_x);
    t_v_goal(i) = t(ix_v);
end



figure(2);
subplot(211);
plot(gear_range,t_v_goal);
title('Times to Reach Target, Emrax 228');
ylabel(['time (s) to ', num2str(v_goal), ' m/s']);
subplot(212);
plot(gear_range,t_x_goal);
ylabel(['time (s) to ', num2str(x_goal), ' m']);
xlabel('Drive Ratio, driven/driver');


