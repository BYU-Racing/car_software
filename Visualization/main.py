import pandas as pd
import plotly.graph_objects as go
from enum import Enum
from bitstring import BitArray
import plotly.io as pio
import panel as pn

"""
Assumptions:
1. Data is sent in IEEE 64 bit floating point binary representation
2. Time is sent as number of milliseconds since the start
3. We have control over how we encode data and timestamps
4. We have control over how we encode the entire signal (metadata)
5. CSV File has one signal per line and optionally one field per column
6. Signals follow CAN Bus Protocol Draft format
"""


class Sensor(Enum):
    ACC1 = 0
    ACC2 = 1
    BRAKE = 2
    SWITCH = 3
    ANGLE = 4
    TIRE1 = 5
    TIRE2 = 6
    TIRE3 = 7
    TIRE4 = 8
    DAMP1 = 9
    DAMP2 = 10
    DAMP3 = 11
    DAMP4 = 12
    TEMP = 13
    LIGHT = 14

sensors = {0: 'Accelerator 1',
           1: 'Accelerator 2',
           2: 'Brake Pressure',
           3: 'Power Switch',
           4: 'Steering Wheel Angle',
           5: 'Front Left Tire',
           6: 'Front Right Tire',
           7: 'Back Left Tire',
           8: 'Back Right Tire',
           9: 'Front Left Damper',
           10: 'Front Right Damper',
           11: 'Back Left Damper',
           12: 'Back Right Damper',
           13: 'Batter Temperature',
           14: 'Rain Light'}

def readData(filename):
    # read csv into a data frame
    # parameters: none
    # returns: nothing
    """
    CAN BUS Protocol
    1. Start of frame:  (1 bit)     Always 1. Denotes the start of frame transmission
    2. ID:              (11 bits)   A (unique) identifier which also represents the message priority
    3. Stuff bit:       (1 bit)     A bit of the opposite polarity to maintain synchronisation
    4. IDE:             (1 bit)     Identifier extension bit. Must be dominant (0)
    5. Reserved bit     (1 bit)     Reserved bit. Must be dominant (0)
    6. Message length:  (4 bits)    Number of bytes of data (0–8 bytes)
    7. Timestamp:       (16 bits)   Timestamp (number of milliseconds from start)
    7. Data field:      (8-64 bits) 1-8 bytes. Data to be transmitted (length in bytes dictated by DLC field)
    8. CRC:             (15 bits)   Cyclic redundancy check
    9. CRC delimiter:   (1 bit)     Must be recessive (1)
    10. ACK slot:       (1 bit)     Transmitter sends recessive (1) and any receiver can assert a dominant (0)
    11. ACK delimiter:  (1 bit)     Must be recessive (1)
    12. End-of-frame:   (1 bit)     (EOF) Must be recessive (1)
    13. IFS:            (3 bits)    Inter-frame spacing. Must be recessive (1)
    Total Signal:       (65-121 bits)

    Toy Signal
    1. ID (11 bits)
    2. Timestamp (16 bits)
    3. Data (64 bits)
    Total: 91 bits
    :return:
    """
    df = pd.read_csv(filename, sep=',', usecols=['ID', 'Timestamp', 'Data'])
    df['ID'] = convertID(df['ID'])
    df['Timestamp'] = convertTime(df['Timestamp'])
    df['Data'] = convertData(df['Data'])

    all_data = {}
    for i in range(len(sensors)):
        all_data.update({i: df[df["ID"] == sensors[i]]})

    return all_data


def parseBits(signals):
    protocol = [['Start of frame', 1],
                ['ID', 11],
                ['Stuff bit', 1],
                ['IDE', 1],
                ['Reserved bit', 1],
                ['Message length', 4],
                ['Timestamp', 16],
                ['Data field', 64],
                ['CRC', 15],
                ['CRC delimiter', 1],
                ['ACK slot', 1],
                ['ACK delimiter', 1],
                ['EOF', 1],
                ['IFS', 3],
                ['Total', 121],]

    processed = []
    for signal in signals:
        if type(signal) is not str:
            raise TypeError(f"Signal is not of type string. Instead received {type(signal)}."
                            f"\nSignal: {signal}")
        if len(signal) != protocol[-1][1]:
            raise ValueError(f"Signal is not the right length. Expected {protocol[-1][1]} but received {len(signal)}."
                             f"\nSignal: {signal}")
        parsed = []
        for field in protocol[:-1]:
            parsed.append(signal[:field[1]])
            signal = signal[field[1]:]
        processed.append(parsed)
    return pd.DataFrame(processed)


def convertTime(timestamp):
    # convert binary timestamp into human-readable text
    # input: timestamp (string) or (list of strings) of zeros and ones
    # returns: timestamp (string) or (list of strings) of times
    if type(timestamp) is str:
        return int(str(timestamp), 2) / 1000.
    return pd.DataFrame([int(str(time), 2) / 1000. for time in timestamp])


def convertID(id_sensor):
    # convert binary ID into an integer, maybe use enumerators?
    # input: id (string) or (list of strings) of zeros and ones
    # returns: id (int) or (list of ints) of IDs
    if type(id_sensor) is str:
        return sensors[int(str(id_sensor), 2)]
    return pd.DataFrame([sensors[int(str(i), 2)] for i in id_sensor])


def convertData(data):
    # convert binary data into a float
    # input: data (string) or (list of strings) of zeros and ones
    # returns: data (int) or (list of ints) of data
    if type(id) is str:
        return BitArray(bin=str(data)).float
    return pd.DataFrame([BitArray(bin=str(d)).float for d in data])


def plot(frame, index):
    time = frame["Timestamp"]
    speed = frame["Data"]

    fig = go.Figure()
    fig.add_trace(go.Scatter(x=time, y=speed, mode='lines', name='acceleration'))
    fig.update_layout(title=sensors[index],
                      xaxis_title='Time (seconds)',
                      yaxis_title="Value")
    fig.show()


if __name__ == "__main__":
    pass
    # file_name = 'synthesized_data1.csv'
    # all_sensors = readData(file_name)
    # plot(all_sensors[Sensor.BRAKE.value], Sensor.BRAKE.value)
