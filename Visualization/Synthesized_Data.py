#Data Collection
import numpy as np
import bitstring
import pandas as pd
from main import Sensor

def getBinary(num, bits):
    """
    Take in an integer and return an 11 bit binary representation
    """
    return bin(num)[2:].zfill(bits)
    
def floatBinary(floats, length = 64):
    """
    
    """
    return bitstring.BitArray(float = floats, length = length).bin

def timeStamp(f, interval):
    """

    """
    samples = interval[1] - interval[0] + 1
    x = np.linspace(interval[0], interval[1], samples)
    time_stamp = [getBinary(int(x[i]), 16) for i in range(len(x))]

    y_vals = f(x)
    data = [floatBinary(y_vals[i]) for i in range(len(y_vals))]

    return time_stamp, data

def dataFrame(f, interval):

    time_stamp, data = timeStamp(f, interval)

    idBinary = getBinary(Sensor.BRAKE.value, 11)

    datas = [[idBinary, time_stamp[i], data[i]] for i in range(len(data))]
  
    df = pd.DataFrame(datas, columns=['ID', 'Timestamp', 'Data'])
    
    return df



if __name__ == "__main__":
    # f = lambda x: np.sin(x/1000)
    # interval = [0, 5000]
    # df = dataFrame(f, interval)
    # df.to_csv('synthesized_data.csv')

    # f = lambda x: np.cos(x/1000) + np.cos(3*x/1000) + 2
    # interval = [0, 5000]
    # df = dataFrame(f, interval)
    # df.to_csv('synthesized_data1.csv')

    pass
