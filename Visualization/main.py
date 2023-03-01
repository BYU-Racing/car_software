import pandas as pd
import plotly.graph_objects as go
from enum import Enum
from bitstring import BitArray
from plotly.subplots import make_subplots
# import plotly.io as pio
# import panel as pn

"""
Assumptions:
1. Data is sent in IEEE 64 bit floating point binary representation
2. Time is sent as number of milliseconds since the start
3. We have control over how we encode data and timestamps
4. We have control over how we encode the entire signal (metadata)
5. CSV File has one signal per line and optionally one field per column
6. Signals follow CAN Bus Protocol Draft format
"""
# TODO add comments


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
legend = {}


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
                ['Total', 121], ]

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
    # TODO update data conversion for 12 bit data
    # convert binary data into a float
    # input: data (string) or (list of strings) of zeros and ones
    # returns: data (int) or (list of ints) of data
    if type(id) is str:
        return BitArray(bin=str(data)).float
    return pd.DataFrame([BitArray(bin=str(d)).float for d in data])


def crc(message, cycCheck):
    # initialize local variables
    n = 8
    primes = [5, 7, 11, 13, 17, 19, 23, 29]
    # split message into 8 bytes
    message = [message[i:i + n] for i in range(0, len(message), n)]
    # convert bytes to integers
    message = [int(str(m), 2) for m in message]
    # recompute crc using message and primes
    check = bin(sum([m * p for m, p in zip(message, primes)]))[2:].rjust(15, "0")
    # return comparison between computed and received crc value
    return check == cycCheck


def plot(frame):
    # https://plotly.com/python/range-slider/
    # https://plotly-r.com/arranging-views.html
    time = frame["Timestamp"]
    speed = frame["Data"]

    # fig = go.Figure()
    fig = make_subplots(rows=3, cols=1,
                        specs=[[{'type': 'xy'}], [{'type': 'xy'}], [{'type': 'indicator'}]])
    fig.add_trace(go.Scatter(x=time, y=speed, mode='lines', name='acc1'), row=1, col=1)
    fig.add_trace(go.Scatter(x=time, y=speed, mode='lines', name='acc2'), row=2, col=1)
    fig.update_yaxes(nticks=1)

    fig.update_layout(title=sensors[0],
                      paper_bgcolor='rgba(60,60,60,1)',
                      plot_bgcolor='rgba(40,40,40,1)',
                      legend=dict(
                          font=dict(
                              color="white"
                          )
                      ),
                      font_family="Courier New",
                      font_color="white",
                      title_font_family="Times New Roman",
                      title_font_color="white",
                      legend_title_font_color="white",
                      )
    fig.update_yaxes(title_text="Value", row=1, col=1)

    fig.add_trace(go.Indicator(
        mode="gauge+number",
        value=270,
        domain={'x': [0, 1], 'y': [0, 1]},
        title={'text': "Speed"}),
        row=3, col=1
    )

    if False:
        fig.update_layout(
            xaxis=dict(
                autorange=True,
                # range=["2012-10-31 18:36:37.3129", "2016-05-10 05:23:22.6871"],
                rangeslider=dict(
                    autorange=True,
                    # range=["2012-10-31 18:36:37.3129", "2016-05-10 05:23:22.6871"]
                ),
                type="date"
            ),
            yaxis=dict(
                anchor="x",
                autorange=True,
                # domain=[0, 0.2],
                linecolor="#673ab7",
                mirror=True,
                # range=[-60.0858369099, 28.4406294707],
                showline=True,
                side="right",
                tickfont={"color": "#673ab7"},
                tickmode="auto",
                ticks="",
                titlefont={"color": "#673ab7"},
                type="linear",
                zeroline=False
            ),
            yaxis2=dict(
                anchor="x",
                autorange=True,
                # domain=[0.2, 0.4],
                linecolor="#E91E63",
                mirror=True,
                # range=[29.3787777032, 100.621222297],
                showline=True,
                side="right",
                tickfont={"color": "#E91E63"},
                tickmode="auto",
                ticks="",
                titlefont={"color": "#E91E63"},
                type="linear",
                zeroline=False
            )
        )

    fig.show()


def display_dashboard(all_frames, dark_mode=True, avail=None, num_plots=6, num_ticks=1):
    if avail is None:
        avail = list(range(15))
    fig = make_subplots(rows=num_plots, cols=1, vertical_spacing=0.02)
    row = 0
    graph_mode = 'lines'
    index_trace = 0

    # Plot 1: Accelerators
    if Sensor.ACC1.value in avail:
        row += 1
        legend.update({index_trace: sensors[Sensor.ACC1.value]})
        index_trace += 1
        fig.add_trace(go.Scatter(x=all_frames[Sensor.ACC1.value]["Timestamp"],
                                 y=all_frames[Sensor.ACC1.value]["Data"],
                                 mode=graph_mode, name=sensors[Sensor.ACC1.value]), row=row, col=1)
    if Sensor.ACC2.value in avail:
        legend.update({index_trace: sensors[Sensor.ACC2.value]})
        index_trace += 1
        fig.add_trace(go.Scatter(x=all_frames[Sensor.ACC2.value]["Timestamp"],
                                 y=all_frames[Sensor.ACC2.value]["Data"],
                                 mode=graph_mode, name=sensors[Sensor.ACC2.value]), row=row, col=1)
        fig.update_yaxes(nticks=num_ticks, title_text="Acc.", row=row, col=1)
        fig.update_xaxes(visible=False, showticklabels=False)

    # Plot 2: Brake Pressure
    if Sensor.BRAKE.value in avail:
        row += 1
        legend.update({index_trace: sensors[Sensor.BRAKE.value]})
        index_trace += 1
        fig.add_trace(go.Scatter(x=all_frames[Sensor.BRAKE.value]["Timestamp"],
                                 y=all_frames[Sensor.BRAKE.value]["Data"],
                                 mode=graph_mode, name=sensors[Sensor.BRAKE.value]), row=row, col=1)
        fig.update_yaxes(nticks=num_ticks, title_text="Brake", row=row, col=1)
        fig.update_xaxes(visible=False, showticklabels=False)

    # Plot 3: Tire speeds
    if Sensor.TIRE1.value in avail:
        row += 1
        legend.update({index_trace: sensors[Sensor.TIRE1.value]})
        index_trace += 1
        fig.add_trace(go.Scatter(x=all_frames[Sensor.TIRE1.value]["Timestamp"],
                                 y=all_frames[Sensor.TIRE1.value]["Data"],
                                 mode=graph_mode, name=sensors[Sensor.TIRE1.value]), row=row, col=1)
    if Sensor.TIRE2.value in avail:
        legend.update({index_trace: sensors[Sensor.TIRE2.value]})
        index_trace += 1
        fig.add_trace(go.Scatter(x=all_frames[Sensor.TIRE2.value]["Timestamp"],
                                 y=all_frames[Sensor.TIRE2.value]["Data"],
                                 mode=graph_mode, name=sensors[Sensor.TIRE2.value]), row=row, col=1)
    if Sensor.TIRE3.value in avail:
        legend.update({index_trace: sensors[Sensor.TIRE3.value]})
        index_trace += 1
        fig.add_trace(go.Scatter(x=all_frames[Sensor.TIRE3.value]["Timestamp"],
                                 y=all_frames[Sensor.TIRE3.value]["Data"],
                                 mode=graph_mode, name=sensors[Sensor.TIRE3.value]), row=row, col=1)
    if Sensor.TIRE4.value in avail:
        legend.update({index_trace: sensors[Sensor.TIRE4.value]})
        index_trace += 1
        fig.add_trace(go.Scatter(x=all_frames[Sensor.TIRE4.value]["Timestamp"],
                                 y=all_frames[Sensor.TIRE4.value]["Data"],
                                 mode=graph_mode, name=sensors[Sensor.TIRE4.value]), row=row, col=1)
    fig.update_yaxes(nticks=num_ticks, title_text="Tires", row=row, col=1)
    fig.update_xaxes(visible=False, showticklabels=False)

    # Plot 4: Steering Wheel
    if Sensor.ANGLE.value in avail:
        row += 1
        legend.update({index_trace: sensors[Sensor.ANGLE.value]})
        index_trace += 1
        fig.add_trace(go.Scatter(x=all_frames[Sensor.ANGLE.value]["Timestamp"],
                                 y=all_frames[Sensor.ANGLE.value]["Data"],
                                 mode=graph_mode, name=sensors[Sensor.ANGLE.value]), row=row, col=1)
        fig.update_yaxes(nticks=num_ticks, title_text="Steering", row=row, col=1)
        fig.update_xaxes(visible=False, showticklabels=False)

    # Plot 5: Damper Position
    if Sensor.DAMP1.value in avail:
        row += 1
        legend.update({index_trace: sensors[Sensor.DAMP1.value]})
        index_trace += 1
        fig.add_trace(go.Scatter(x=all_frames[Sensor.DAMP1.value]["Timestamp"],
                                 y=all_frames[Sensor.DAMP1.value]["Data"],
                                 mode=graph_mode, name=sensors[Sensor.DAMP1.value]), row=row, col=1)
    if Sensor.DAMP2.value in avail:
        legend.update({index_trace: sensors[Sensor.DAMP2.value]})
        index_trace += 1
        fig.add_trace(go.Scatter(x=all_frames[Sensor.DAMP2.value]["Timestamp"],
                                 y=all_frames[Sensor.DAMP2.value]["Data"],
                                 mode=graph_mode, name=sensors[Sensor.DAMP2.value]), row=row, col=1)
    if Sensor.DAMP3.value in avail:
        legend.update({index_trace: sensors[Sensor.DAMP3.value]})
        index_trace += 1
        fig.add_trace(go.Scatter(x=all_frames[Sensor.DAMP3.value]["Timestamp"],
                                 y=all_frames[Sensor.DAMP3.value]["Data"],
                                 mode=graph_mode, name=sensors[Sensor.DAMP3.value]), row=row, col=1)
    if Sensor.DAMP4.value in avail:
        legend.update({index_trace: sensors[Sensor.DAMP4.value]})
        index_trace += 1
        fig.add_trace(go.Scatter(x=all_frames[Sensor.DAMP4.value]["Timestamp"],
                                 y=all_frames[Sensor.DAMP4.value]["Data"],
                                 mode=graph_mode, name=sensors[Sensor.DAMP4.value]), row=row, col=1)
        fig.update_yaxes(nticks=num_ticks, title_text="Dampers", row=row, col=1)
        fig.update_xaxes(visible=False, showticklabels=False)

    # Plot 6: Battery Temperature
    if Sensor.TEMP.value in avail:
        row += 1
        legend.update({index_trace: sensors[Sensor.TEMP.value]})
        index_trace += 1
        fig.add_trace(go.Scatter(x=all_frames[Sensor.TEMP.value]["Timestamp"],
                                 y=all_frames[Sensor.TEMP.value]["Data"],
                                 mode=graph_mode, name=sensors[Sensor.TEMP.value]), row=row, col=1)
        fig.update_yaxes(nticks=num_ticks, title_text="Battery", row=row, col=1)
        fig.update_xaxes(visible=False, showticklabels=False)

    # update display layout
    fig.update_layout(title_font_family="Courier New",
                      font_family="Courier New",
                      font=dict(size=15),
                      margin=dict(l=75, r=75, t=10, b=20),
                      )

    if dark_mode:
        fig.update_layout(paper_bgcolor='rgba(60,60,60,1)',
                          plot_bgcolor='rgba(40,40,40,1)',
                          legend=dict(
                              font=dict(
                                  color="white"
                              )
                          ),
                          font_color="white",
                          title_font_color="white",
                          legend_title_font_color="white",
                          )

    # fig.show()
    return fig


if __name__ == "__main__":
    pass
    file_name = 'Data/Master.csv'
    all_sensors = readData(file_name)
    # plot(all_sensors[0])
    display_dashboard(all_sensors, dark_mode=True).show()
    # print(all_sensors[Sensor.DAMP1.value]["Timestamp"])
