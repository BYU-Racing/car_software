function dx = Acc_eom(t,x,n,motor,vehicle)
% x = [vel, disp]
% dx = [acc, vel]
dx = zeros(2,1);

v1 = x(1);
x1 = x(2);

%%%%%%%%%%%%%%%%%%%%%%% Motor paramenters %%%%%%%%%%%%%%%%%%%%%%

transition_rpm = motor(1); % point at which torque drops
max_rpm = motor(2);
max_torque = motor(3); % torque at the max power level (80kw*efficiency)
% controller_efficiency = 0.75;
% motor_efficiency = 0.85;
torque_decay = motor(4); % N*m/rpm

%%%%%%%%%%%%%%%%%%%%%%% Vehicle paramenters %%%%%%%%%%%%%%%%%%%%%%

r = vehicle(1); % distance from axle center to ground, m
m_driver = vehicle(2);% driver mass, kg
m_car = vehicle(3); % vehicle mass, kg
m = vehicle(4); % combined mass
g = vehicle(5); % gravity, m/s^2

Cd = vehicle(6); % coeff of aero drag
p = vehicle(7); % air density, kg/m^3
A = vehicle(8); % frontal area, m^2

Cr = vehicle(9); % estimate for rolling coefficient
C_motor = vehicle(10); % sum of damping on the motor side
C_axle = vehicle(11); % sum of damping on the axle side

mu = vehicle(12); % traction coefficient
l = vehicle(13); % wheelbase, m
la = vehicle(14); % center of gravity to the front axle, m
Rb = vehicle(15); % static normal weight on the rear tires, N
h = vehicle(16); % height of center of gravity off ground, m

%%%%%%%%%%%% Motor. Speed in, torque out %%%%%%%%%%%

if v1 <= r*(transition_rpm*2*pi/(n*60)) % v = r*omega
    T = max_torque;
elseif v1 > r*(transition_rpm*2*pi/(n*60)) && v1 < r*(max_rpm*2*pi/(n*60))
    T = torque_decay*(v1*n*60/(pi*2))/r - torque_decay*max_rpm; % m*omega+b
else
    T = 0;
end

%%%%%%%%%%%% Force balance equations %%%%%%%%%%%

F = T*n/r; % simple unlimited traction, N*m
if F > mu*Rb
    F = mu*Rb; % traction limit
end

drag = .5*Cd*p*v1*abs(v1)*A; % aerodynamic drag
rolling = 4*Cr*m*g/r; % rolling resistance, appx constant
spinning = C_motor*n*v1/r + C_axle*v1/r; % damping force of bearings, chains...
m_eq = m; %+ J*n* % INCLUDE BOTH VEHICLE MASS AND REFLECTED ROTATIONAL INERTIA

d_dx = 1; % greater than .01 to get into while loop
dx_prev = 0; % assume 0 m/s^2
while d_dx >= 0.01 % Iterate until change in acceleration < .01 m/s^2
    dx(1) = ( F - drag - rolling - spinning )/m_eq; % vdot, or acceleration
    if T*n/r > mu*(Rb+h*m*dx(1)/l) % If wheels can break traction w/ load transfer
        F = mu*(Rb+h*m*dx(1)/l); % new, higher estimate for F
    else
        F = T*n/r; % now power limited, loop exits
    end
    d_dx = abs(dx(1)-dx_prev); % change in acceleration
    dx_prev = dx(1); % store previous acceleration to compare
end

dx(2) = x(1); % xdot, or velocity

