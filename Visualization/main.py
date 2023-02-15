import pandas as pd
import plotly.graph_objects as go
from enum import Enum
from bitstring import BitArray

class Sensor(Enum):
    ACC1 = 0
    ACC2 = 1
    BRAK = 2
    SWCH = 3
    ANGL = 4
    TIRE1 = 5
    TIRE2 = 6
    TIRE3 = 7
    TIRE4 = 8
    DAMP1 = 9
    DAMP2 = 10
    DAMP3 = 11
    DAMP4 = 12
    TEMP = 13
    LITE = 14

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
    1. Start of frame   (1 bit)     Always 1. Denotes the start of frame transmission
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

    plot(all_data[Sensor.BRAK.value], Sensor.BRAK.value)


def convertTime(timestamp):
    # convert binary timestamp into human-readable text
    # input: timestamp (string) or (list of strings) of zeros and ones
    # returns: timestamp (string) or (list of strings) of times
    if type(timestamp) is str:
        return int(str(timestamp), 2) / 1000.
    return pd.DataFrame([int(str(time), 2) / 1000. for time in timestamp])


def convertID(id):
    # convert binary ID into an integer, maybe use enumerators?
    # input: id (string) or (list of strings) of zeros and ones
    # returns: id (int) or (list of ints) of IDs
    if type(id) is str:
        return sensors[int(str(id), 2)]
    return pd.DataFrame([sensors[int(str(i), 2)] for i in id])


def convertData(data):
    # convert binary data into a float
    # input: data (string) or (list of strings) of zeros and ones
    # returns: data (int) or (list of ints) of data
    if type(id) is str:
        return BitArray(bin=str(data)).float
    return pd.DataFrame([BitArray(bin=str(d)).float for d in data])


def synthesizeData():
    driving = pd.DataFrame()


def updateSensorIDs():
    pass


def plot(frame, index):
    # Create data
    time = frame["Timestamp"]
    speed = frame["Data"]
    # Create figure
    fig = go.Figure()
    # Add traces
    fig.add_trace(go.Scatter(x=time, y=speed, mode='lines', name='acceleration'))
    # Edit the layout
    fig.update_layout(title=sensors[index],
                      xaxis_title='Time (seconds)',
                      yaxis_title="Value")
    # Plot
    fig.show()


if __name__ == "__main__":
    filename = 'synthesized_data1.csv'
    readData(filename)



