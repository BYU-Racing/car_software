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

def dataFrame(f, Sensor, interval):

    time_stamp, data = timeStamp(f, interval)

    idBinary = getBinary(Sensor, 11)

    datas = [[idBinary, time_stamp[i], data[i]] for i in range(len(data))]
  
    df = pd.DataFrame(datas, columns=['ID', 'Timestamp', 'Data'])
    
    return df



if __name__ == "__main__":
    interval = [0, 5000]

    a1 = lambda x: 1.1*x
    a2 = lambda x: x
    dfa1 = dataFrame(a1, Sensor.ACC1.value, interval)
    dfa2 = dataFrame(a2, Sensor.ACC2.value, interval)
    dfa1.to_csv('ACC1.csv')
    dfa2.to_csv('ACC2.csv')

    br = lambda x: np.cos(x/1000) + np.cos(3*x/1000) + 2
    dfbr = dataFrame(br, Sensor.BRAKE.value, interval)
    dfbr.to_csv('BRAKE.csv')

    sw = lambda x: np.sin(x/1000)
    dfsw = dataFrame(sw, Sensor.SWITCH.value, interval)
    dfsw.to_csv('SWITCH.csv')

    ang = lambda x: np.cos(x/1000)
    dfang = dataFrame(ang, Sensor.ANGLE.value, interval)
    dfang.to_csv('ANGLE.csv')

    t1 = lambda x: np.sin(x/1000)
    t2 = lambda x: np.sin(x/1000) + 0.25
    t3 = lambda x: np.sin(x/1000) + 0.5
    t4 = lambda x: np.sin(x/1000) + 0.75
    dft1 = dataFrame(t1, Sensor.TIRE1.value, interval)
    dft2 = dataFrame(t2, Sensor.TIRE2.value, interval)
    dft3 = dataFrame(t3, Sensor.TIRE3.value, interval)
    dft4 = dataFrame(t4, Sensor.TIRE4.value, interval)
    dft1.to_csv('TIRE1.csv')
    dft2.to_csv('TIRE2.csv')
    dft3.to_csv('TIRE3.csv')
    dft4.to_csv('TIRE4.csv')

    d1 = lambda x: np.cos(x/1000)
    d2 = lambda x: np.cos(x/1000) + 0.25
    d3 = lambda x: np.cos(x/1000) + 0.5
    d4 = lambda x: np.cos(x/1000) + 0.75
    dfd1 = dataFrame(d1, Sensor.DAMP1.value, interval)
    dfd2 = dataFrame(d2, Sensor.DAMP2.value, interval)
    dfd3 = dataFrame(d3, Sensor.DAMP3.value, interval)
    dfd4 = dataFrame(d4, Sensor.DAMP4.value, interval)
    dfd1.to_csv('DAMP1.csv')
    dfd2.to_csv('DAMP2.csv')
    dfd3.to_csv('DAMP3.csv')
    dfd4.to_csv('DAMP4.csv')

    te = lambda x: np.sin(x/1000)
    dfte = dataFrame(te, Sensor.TEMP.value, interval)
    dfte.to_csv('TEMP.csv')

    l = lambda x: np.cos(x/1000) + np.cos(3*x/1000) + 2
    dfl = dataFrame(l, Sensor.LIGHT.value, interval)
    dfl.to_csv('LIGHT.csv')

    dfMaster = pd.concat([dfa1, dfa2, dfbr, dfang, dfsw, dft1, dft2, dft3, dft4, dfd1, dfd2, dfd3, dfd4, dfte, dfl], axis=0)
    dfMaster = dfMaster.sort_values(by=['Timestamp', 'ID'])
    dfMaster.to_csv('Master.csv')


    pass
