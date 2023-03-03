#plot race track

import numpy as np
from matplotlib import pyplot as plt
import scipy
from scipy.interpolate import interp1d
from scipy.misc import derivative

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

    x =  speed * np.cos(theta)
    y =  speed * np.sin(theta)



    return x, y

if __name__ == "__main__":

    time = np.linspace(0, 10, 1000)
    angle = np.sin(time)+1
    speed = np.cos(time)+1

    f_speed = scipy.interpolate.interp1d(time, speed, kind = 'cubic')
    # print(f_speed.coeffs)
    ysnew = f_speed(time)

    f_angle = scipy.interpolate.interp1d(time, angle, kind = 'cubic')
    yanew = f_angle(time)

    # plt.subplot(121)
    # plt.plot(time, ysnew)

    # plt.subplot(122)
    # plt.plot(time, yanew)

    speed_der = f_speed.derivative()

    f_angle = [derivative(f_angle, i) for i in time]

    ysder = f_speed(time)

    yader = f_angle(time)

    plt.subplot(121)
    plt.plot(time, ysder)

    plt.subplot(122)
    plt.plot(time, yader)




    plt.show()

    pass