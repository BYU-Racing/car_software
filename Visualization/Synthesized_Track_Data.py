#plot race track

import numpy as np
from matplotlib import pyplot as plt
import scipy
from scipy.interpolate import interp1d
from scipy import integrate

#Accept Speed(mph), time(sec) and wheel angle(degrees) lists
#return a list of x and y values
def benj_position(speed, time, angle):

    #convert MPH to MPS
    speed = [x * 0.000278 for x in speed]

    #use speed and time to make distance traveled per second
    distance = speed * time

    theta = 0
    x = 0
    y = 0
    x_val = [0]
    y_val = [0]

    angle = np.deg2rad(angle)

    for dist, ang in zip(distance, angle):
        theta += ang

        x += dist * np.cos(theta)
        x_val.append(x)
        y += dist * np.sin(theta)
        y_val.append(y)

    return x_val, y_val

def dallin_position(speed, time, angle):

    theta = np.deg2rad(angle)

    x = speed * np.cos(theta)
    y = speed * np.sin(theta)

    return x, y


def derive(f, x0, h=1e-5):
    return (f(x0 + h) - f(x0)) / h

if __name__ == "__main__":
    minim = 0
    maxim = 10

    # time = np.linspace(minim, maxim, 1000)
    # angle = np.sin(time)+1
    # speed = np.cos(time)+1
    time = np.linspace(minim, maxim, 360)
    angle = np.arange(360)
    speed = np.ones(360)

    f_x = scipy.interpolate.interp1d(time, speed*np.cos(angle), kind='cubic')
    # print(f_speed.coeffs)
    ysnew = f_x(time)

    f_y = scipy.interpolate.interp1d(time, speed * np.sin(angle), kind='cubic')
    yanew = f_y(time)

    # integrate
    def f_distance(f, t):
        return scipy.integrate.quad(f, 0, t)[0]

    # Evaluate the integral of f_speed at some points
    x_pos = np.array([f_distance(f_x, t) for t in time])
    y_pos = np.array([f_distance(f_y, t) for t in time])

    plt.subplot(131)
    plt.plot(time, speed, label="Original Speed")
    plt.subplot(132)
    plt.plot(time, angle, label="Original Angle")

    # get interpolating points
    # time = time[:-1]
    ysder = f_x(time)
    yader = f_y(time)

    # derive and plot
    plt.subplot(131)
    plt.plot(time, ysder, label="Speed Interpolation")
    # plt.plot(time, derive(f_speed, time), label="Speed Derivative")
    plt.plot(time, x_pos, label="X Position")
    plt.legend()

    plt.subplot(132)
    plt.plot(time, yader, label="Angle Interpolation")
    # plt.plot(time, derive(f_angle, time), label="Angle Derivative")
    plt.plot(time, y_pos, label="Y Position")

    plt.subplot(133)
    plt.plot(x_pos, y_pos)
    plt.title("Position")

    plt.legend()
    plt.show()

    pass