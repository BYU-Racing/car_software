import pandas as pd
import plotly.graph_objects as go
from enum import Enum


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

def readData():
    # read csv into a data frame
    # parameters: none
    # returns: nothing
    pass


def convertTime(timestamp):
    # convert binary timestamp into human-readable text
    # input: timestamp (string) or (list of strings) of zeros and ones
    # returns: timestamp (string) or (list of strings) of times
    pass


def convertID(id):
    # convert binary ID into an integer, maybe use enumerators?
    # input: id (string) or (list of strings) of zeros and ones
    # returns: id (int) or (list of ints) of IDs
    if type(id) is str:
        return sensors[int(id, 2)]
    return [sensors[int(i, 2)] for i in id]


def convertData(data):
    # convert binary data into a float
    # input: data (string) or (list of strings) of zeros and ones
    # returns: data (int) or (list of ints) of data
    if type(data) is str:
        return int(data, 2)
    return [int(d, 2) for d in data]


def synthesizeData():
    driving = pd.DataFrame()


def updateSensorIDs():
    pass


def plot():
    # Create data
    time = [0, 1, 2, 3, 4, 5]
    speed = [0, 2, 4, 6, 8, 10]
    # Create figure
    fig = go.Figure()
    # Add traces
    fig.add_trace(go.Scatter(x=time, y=speed, mode='lines', name='speed'))
    # Edit the layout
    fig.update_layout(title='Speed vs Time',
                      xaxis_title='Time',
                      yaxis_title='Speed')
    # Plot
    fig.show()


if __name__ == "__main__":
    print(convertData(["00000011", "00000111", "00000010", "00000001"]))
    pass
