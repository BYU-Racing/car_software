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

%%%%%%%%%%%%%%%%%%%%%% ODE Solver and parameters %%%%%%%%%%%%%%%%%%%%%%

n = 4; % gear ratio, driven/driver
x_goal = 75; % target distance, meters
v_goal = 22; % target velocity, m/s

tspan = [0 7]; % [T0 TFINAL]
x0 = [0 0]; % Initial conditions [velocity, displacement]
[t,x] = ode45(@(t,x) Acc_eom(t,x,n,em_208_1,vehicle_1), tspan, x0);
 
v1 = x(:,1); % 1st column, velocity
x1 = x(:,2); % 2nd column, displacement

[ d_x, ix_x ] = min( abs( x1-x_goal ) ); % find index closes to target
[ d_v, ix_v ] = min( abs( v1-v_goal ) );

disp([num2str(t(ix_x)), ' seconds to ', num2str(x_goal), ' m'])
disp([num2str(t(ix_v)), ' seconds to ', num2str(v_goal), ' m/s'])

% figure(1);
% subplot(211);
% plot(t,v1);
% title('Full Throttle Step Input Response');
% ylabel('Velocity (m/s)');
% subplot(212);
% plot(t,x1);
% ylabel('Displacement (m)');
% xlabel('time (sec)');


