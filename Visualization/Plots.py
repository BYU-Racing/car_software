import plotly.graph_objects as go
from plotly.subplots import make_subplots
import numpy as np

from Config import themes, sensors, Sensor
from Converter import *


# legend that maps display order to sensor
legend = {}

# fake track data
n = 433
tim = np.ones(n)

domain = np.linspace(0, 2 * np.pi, n)
deg = np.round(2 * np.sin(domain), 1)
spd = np.ones(n)

x, y = convert_position(spd, tim, deg)


def display_dashboard(all_frames, theme="Dark", size="medium", avail=None, num_plots=7, num_ticks=1):
    """
    Display a Dash dashboard with racing sensor data
    Parameters:
        :param size: (string) select desired title font size such as 'small', 'medium', or 'large'
        :param all_frames: (dataframe) pandas dataframe with every sensor at every time interval
        :param theme: (string) select desired display theme such as 'Dark' or 'Jarvis'
        :param avail: (list) data available or desired to display, ie select subplots
        :param num_plots: (int) the number of subplots to display
        :param num_ticks: (int) the number of y-axis tick marks on each subplot
    :return:
        fig: (plotly figure) figure to display main data
    """
    # set default availability
    if avail is None:
        avail = list(range(len(Config.sensor_names)))

    # initialize figure with subplots
    fig = make_subplots(rows=num_plots, cols=1, vertical_spacing=0.02, shared_xaxes=True)
    row = 0
    graph_mode = 'lines'
    index_trace = 0
    dots = 1 / PARTITION
    frameLength = len(all_frames[Sensor.ACC1.value]["Timestamp"])

    # PLOT 1: ACCELERATORS ---------------------------------------------------------------------------------------------
    if Sensor.ACC1.value in avail:
        # increment row index for subplots
        row += 1

        # update legend dictionary with correct sensor for other plots
        legend.update({index_trace: sensors[Sensor.ACC1.value]})

        # increment trace so that other plots can stay consistent with order
        index_trace += 1

        # add a trace to the growth subplot using data on the corresponding row from all_frames
        fig.add_trace(go.Scatter(x=all_frames[Sensor.ACC1.value]["Timestamp"],
                                 y=all_frames[Sensor.ACC1.value]["Data"],
                                 marker=dict(color=themes[theme]["trace"][0][2]),
                                 mode=graph_mode, name=sensors[Sensor.ACC1.value]), row=row, col=1, ),

    # repeat for every other sensor
    if Sensor.ACC2.value in avail:
        legend.update({index_trace: sensors[Sensor.ACC2.value]})
        index_trace += 1
        fig.add_trace(go.Scatter(x=all_frames[Sensor.ACC2.value]["Timestamp"],
                                 y=all_frames[Sensor.ACC2.value]["Data"],
                                 marker=dict(color=themes[theme]["trace"][1][2]),
                                 mode=graph_mode, name=sensors[Sensor.ACC2.value]), row=row, col=1)

        fig.update_yaxes(nticks=num_ticks, title_text="Accelerator", row=row, col=1)
        fig.update_xaxes(visible=False, showticklabels=False)

    # PLOT 2: BRAKE SENSORS --------------------------------------------------------------------------------------------
    if Sensor.BRAKE.value in avail:
        row += 1
        legend.update({index_trace: sensors[Sensor.BRAKE.value]})
        index_trace += 1

        fig.add_trace(go.Scatter(x=all_frames[Sensor.BRAKE.value]["Timestamp"],
                                 y=all_frames[Sensor.BRAKE.value]["Data"],
                                 marker=dict(color=themes[theme]["trace"][1][2]),
                                 mode=graph_mode, name=sensors[Sensor.BRAKE.value]), row=row, col=1)

        fig.update_yaxes(nticks=num_ticks, title_text="Brake", row=row, col=1)
        fig.update_xaxes(visible=False, showticklabels=False)

    # PLOT 3: TIRE SPEEDS ----------------------------------------------------------------------------------------------
    if Sensor.TIRE1.value in avail:
        row += 1
        legend.update({index_trace: sensors[Sensor.TIRE1.value]})
        index_trace += 1

        fig.add_trace(go.Scatter(x=all_frames[Sensor.TIRE1.value]["Timestamp"],
                                 y=all_frames[Sensor.TIRE1.value]["Data"],
                                 marker=dict(color=themes[theme]["trace"][2][2],
                                             size=dots),
                                 mode=graph_mode, name=sensors[Sensor.TIRE1.value]), row=row, col=1)
    # TIRE 2 PLOT
    if Sensor.TIRE2.value in avail:
        legend.update({index_trace: sensors[Sensor.TIRE2.value]})
        index_trace += 1

        fig.add_trace(go.Scatter(x=all_frames[Sensor.TIRE2.value]["Timestamp"],
                                 y=all_frames[Sensor.TIRE2.value]["Data"],
                                 marker=dict(color=themes[theme]["trace"][3][2],
                                             size=dots),
                                 mode=graph_mode, name=sensors[Sensor.TIRE2.value]), row=row, col=1)
    # TIRE 3 PLOT
    if Sensor.TIRE3.value in avail:
        legend.update({index_trace: sensors[Sensor.TIRE3.value]})
        index_trace += 1

        fig.add_trace(go.Scatter(x=all_frames[Sensor.TIRE3.value]["Timestamp"],
                                 y=all_frames[Sensor.TIRE3.value]["Data"],
                                 marker=dict(color=themes[theme]["trace"][4][2],
                                             size=dots),
                                 mode=graph_mode, name=sensors[Sensor.TIRE3.value]), row=row, col=1)
    # TIRE 4 PLOT
    if Sensor.TIRE4.value in avail:
        legend.update({index_trace: sensors[Sensor.TIRE4.value]})
        index_trace += 1

        fig.add_trace(go.Scatter(x=all_frames[Sensor.TIRE4.value]["Timestamp"],
                                 y=all_frames[Sensor.TIRE4.value]["Data"],
                                 marker=dict(color=themes[theme]["trace"][5][2],
                                             size=dots),
                                 mode=graph_mode, name=sensors[Sensor.TIRE4.value]), row=row, col=1)

    if Sensor.TIRE1.value in avail:
        fig.update_yaxes(nticks=num_ticks, title_text="Tires", row=row, col=1)
        fig.update_xaxes(visible=False, showticklabels=False)

    # PLOT 4: STEERING WHEEL -------------------------------------------------------------------------------------------
    if Sensor.ANGLE.value in avail:
        row += 1
        legend.update({index_trace: sensors[Sensor.ANGLE.value]})
        index_trace += 1

        fig.add_trace(go.Scatter(x=all_frames[Sensor.ANGLE.value]["Timestamp"],
                                 y=all_frames[Sensor.ANGLE.value]["Data"],
                                 marker=dict(color=themes[theme]["trace"][1][2]),
                                 mode=graph_mode, name=sensors[Sensor.ANGLE.value]), row=row, col=1)

        fig.update_yaxes(nticks=num_ticks, title_text="Steering", row=row, col=1)
        fig.update_xaxes(visible=False, showticklabels=False)

    # PLOT 5: DAMPER POSITIONS -----------------------------------------------------------------------------------------
    if Sensor.DAMP1.value in avail:
        row += 1
        legend.update({index_trace: sensors[Sensor.DAMP1.value]})
        index_trace += 1

        fig.add_trace(go.Scatter(x=all_frames[Sensor.DAMP1.value]["Timestamp"],
                                 y=all_frames[Sensor.DAMP1.value]["Data"],
                                 marker=dict(color=themes[theme]["trace"][2][2],
                                             size=dots),
                                 mode=graph_mode, name=sensors[Sensor.DAMP1.value]), row=row, col=1)
    # DAMPER 2
    if Sensor.DAMP2.value in avail:
        legend.update({index_trace: sensors[Sensor.DAMP2.value]})
        index_trace += 1

        fig.add_trace(go.Scatter(x=all_frames[Sensor.DAMP2.value]["Timestamp"],
                                 y=all_frames[Sensor.DAMP2.value]["Data"],
                                 marker=dict(color=themes[theme]["trace"][3][2],
                                             size=dots),
                                 mode=graph_mode, name=sensors[Sensor.DAMP2.value]), row=row, col=1)
    # DAMPER 3
    if Sensor.DAMP3.value in avail:
        legend.update({index_trace: sensors[Sensor.DAMP3.value]})
        index_trace += 1

        fig.add_trace(go.Scatter(x=all_frames[Sensor.DAMP3.value]["Timestamp"],
                                 y=all_frames[Sensor.DAMP3.value]["Data"],
                                 marker=dict(color=themes[theme]["trace"][4][2],
                                             size=dots),
                                 mode=graph_mode, name=sensors[Sensor.DAMP3.value]), row=row, col=1)
    # DAMPER 4
    if Sensor.DAMP4.value in avail:
        legend.update({index_trace: sensors[Sensor.DAMP4.value]})
        index_trace += 1

        fig.add_trace(go.Scatter(x=all_frames[Sensor.DAMP4.value]["Timestamp"],
                                 y=all_frames[Sensor.DAMP4.value]["Data"],
                                 marker=dict(color=themes[theme]["trace"][5][2],
                                             size=dots),
                                 mode=graph_mode, name=sensors[Sensor.DAMP4.value]), row=row, col=1)

        fig.update_yaxes(nticks=num_ticks, title_text="Dampers", row=row, col=1)
        fig.update_xaxes(visible=False, showticklabels=False)

    # PLOT 6: BATTERY TEMPERATURE --------------------------------------------------------------------------------------
    if Sensor.TEMP.value in avail:
        row += 1

        legend.update({index_trace: sensors[Sensor.TEMP.value]})
        index_trace += 1

        fig.add_trace(go.Scatter(x=all_frames[Sensor.TEMP.value]["Timestamp"],
                                 y=all_frames[Sensor.TEMP.value]["Data"],
                                 marker=dict(color=themes[theme]["trace"][1][2]),
                                 mode=graph_mode, name=sensors[Sensor.TEMP.value]), row=row, col=1)

        fig.update_yaxes(nticks=num_ticks, title_text="Battery", row=row, col=1)
        fig.update_xaxes(visible=False, showticklabels=False)

    # PLOT 7: ACCELEROMETER SENSORS ------------------------------------------------------------------------------------
    if Sensor.GFORCE.value in avail:
        row += 1
        legend.update({index_trace: sensors[Sensor.GFORCE.value]})
        index_trace += 1

        # TODO get fake g force data and remove the -2
        fig.add_trace(go.Scatter(x=all_frames[Sensor.GFORCE.value-2]["Timestamp"],
                                 y=all_frames[Sensor.GFORCE.value-2]["Data"],
                                 marker=dict(color=themes[theme]["trace"][1][2]),
                                 mode=graph_mode, name=sensors[Sensor.GFORCE.value]), row=row, col=1)

        fig.update_yaxes(nticks=num_ticks, title_text="G-Force", row=row, col=1)
        fig.update_xaxes(visible=False, showticklabels=False)

    # END SUBPLOTS -----------------------------------------------------------------------------------------------------


    # update display layout based on theme
    fig.update_layout(title_font_family=themes[theme]["font"]["p"],
                      font_family=themes[theme]["font"]["p"],
                      font=dict(size=int(themes[theme]["size"][size])),
                      margin=dict(l=75, r=75, t=10, b=20),
                      )

    # update layout based on and theme
    fig.update_layout(paper_bgcolor=themes[theme]["color"][0][1],
                      plot_bgcolor=themes[theme]["color"][1][1],
                      legend=dict(
                          font=dict(
                              color=themes[theme]["color"][2][2]
                          )
                      ),
                      font_color=themes[theme]["color"][2][2],
                      title_font_color=themes[theme]["color"][2][2],
                      legend_title_font_color=themes[theme]["color"][2][2],
                      )



    # fig.show()
    return fig


def speedometer(value, maxim=60, theme="Dark", size="medium"):
    """
    Create a speedometer plot to show instantaneous speed
    Parameters:
        :param size: (string) select the size of the title
        :param value: (int) instantaneous speed
        :param maxim: (int) maximum value on speedometer
        :param theme: (string) change display based on theme
    Returns:
        :return: fig: (plotly figure) customized speedometer plot
    """
    # initialize figure and plot parameters
    figSpeed = go.Figure()
    maxim = int(maxim)

    tick0 = 0
    tick1 = round(maxim / 4, 2)
    tick2 = round(maxim / 2, 2)
    tick3 = 3 * tick1
    tick4 = maxim

    # Add a gauge chart
    figSpeed.add_trace(go.Indicator(
        mode="gauge+number",
        value=value,

        gauge={
            'axis': {'range': [None, maxim], 'nticks': 7},
            'bar': {'color': themes[theme]["color"][2][2]},

            # set steps
            'steps': [
                {'range': [tick0, tick1], 'color': themes[theme]["color"][1][2]},
                {'range': [tick1, tick2], 'color': themes[theme]["color"][1][2]},
                {'range': [tick2, tick3], 'color': themes[theme]["color"][1][2]},
                {'range': [tick3, tick4], 'color': themes[theme]["color"][1][2]}],

            # set threshold
            'threshold': {
                'line': {'color': themes[theme]["trace"][1][2], 'width': 4},
                'thickness': 0.75,
                'value': maxim * .9}
        }
    ))

    # Update the layout
    figSpeed.update_layout(
        title="Speedometer",
        font=dict(
            family=themes[theme]["font"]["graph"],
            size=int(themes[theme]["size"][size]),
            color=themes[theme]["color"][2][2]
        ),
        margin=dict(l=15, r=15, t=40, b=0),
        paper_bgcolor=themes[theme]["color"][0][1],
    )
    return figSpeed


def pedals(brake=0, accel=0, minim=0, maxim=1, theme="Dark", size="medium"):
    """
    Create a bar chart to show instantaneous brake and accelerator pressure
    Parameters:
        :param size: (string) select size of the title and axis labels
        :param brake: (int) instantaneous value of the break
        :param accel: (int) instantaneous value of the accelerator
        :param minim: (int) minimum chart value
        :param maxim: (int) maximum chart value
        :param theme: (string) select display theme such as 'Dark' or 'Jarvis'
    Returns:
        :return: fig: (plotly figure) customized bar chart
    """
    # instantiate figure object
    fig = go.Figure()

    # add bars for brake and accelerator
    fig.add_trace(go.Bar(
        x=['Brake', 'Go Pedal'],
        y=[brake, accel],
        marker=dict(color=[themes[theme]["trace"][1][2], themes[theme]["trace"][0][2]]),
        width=0.5,
    ))
    if size == "small":
        fig.update_xaxes(showticklabels=False)

    # Update the layout based on the theme
    fig.update_layout(
        title="Pedals",
        font=dict(
            family=themes[theme]["font"]["graph"],
            size=int(themes[theme]["size"][size]),
            color=themes[theme]["color"][2][2]
        ),
        margin=dict(l=50, r=30, t=40, b=10),
        yaxis_range=[minim, maxim],
        paper_bgcolor=themes[theme]["color"][0][1],
        plot_bgcolor=themes[theme]["color"][1][1],
    )

    return fig


def steering(angle=0, theme="Dark", size="medium"):
    """
    Create a scatter plot to show instantaneous steering wheel position
    Parameters:
        :param size: (string) select display size such as 'small', 'medium', or 'large'
        :param angle: (int) angle in radians that the steering wheel is turned
        :param theme: (string) select display theme such as 'Dark' or 'Jarvis'
    Returns:
        :return: fig: (plotly figure) steering wheel view
    """
    # set handlebar location
    density = 100
    t_right = np.linspace(-np.pi / 8, np.pi / 8, density)
    x = np.cos(t_right)
    y = np.sin(t_right)

    t_left = np.linspace(np.pi - np.pi / 8, np.pi + np.pi / 8, density)
    x1 = np.cos(t_left)
    y1 = np.sin(t_left)

    # Rotate the points by the input angle
    # theta = angle * np.pi / 180.0
    theta = angle
    c, s = np.cos(theta), np.sin(theta)

    # compute x and y positions of points that construct the steering wheel
    x_right = x * c - y * s
    y_right = x * s + y * c
    x_left = x1 * c - y1 * s
    y_left = x1 * s + y1 * c

    # Create a scatter plot with markers arranged in a circular pattern
    right_bar = go.Scatter(
        x=x_right, y=y_right, mode='markers',
        marker=dict(size=20, color=themes[theme]["color"][4][2]),
        showlegend=False
    )

    left_bar = go.Scatter(
        x=x_left, y=y_left, mode='markers',
        marker=dict(size=20, color=themes[theme]["color"][4][2]),
        showlegend=False
    )

    # place points on the top of the wheel to indicate orientation
    right_top = go.Scatter(
        x=[x_right[-1]], y=[y_right[-1]], mode='markers',
        marker=dict(size=20, color=themes[theme]["color"][1][2]),
        showlegend=False
    )

    left_top = go.Scatter(
        x=[x_left[0]], y=[y_left[0]], mode='markers',
        marker=dict(size=20, color=themes[theme]["color"][1][2]),
        showlegend=False
    )

    # initialize display figure and plot points
    fig = go.Figure()
    fig.add_trace(right_bar)
    fig.add_trace(left_bar)
    fig.add_trace(right_top)
    fig.add_trace(left_top)

    # update layout to match theme
    fig.update_layout(
        # fix vertical and horizontal sizes
        xaxis=dict(
            range=[-1.15, 1.15],
            autorange=False,
        ),
        yaxis=dict(
            range=[-1.15, 1.15],
            autorange=False,
        ),
        title='Steering Wheel',
        font=dict(
            family=themes[theme]["font"]["graph"],
            size=int(themes[theme]["size"][size]),
            color=themes[theme]["color"][2][2]
        ),
        margin=dict(l=45, r=45, t=40, b=0),
        paper_bgcolor=themes[theme]["color"][0][1],
        plot_bgcolor=themes[theme]["color"][0][1],
    )

    # remove everything on the graph besides the points
    fig.update_yaxes(nticks=1, visible=False, showticklabels=False)
    fig.update_xaxes(nticks=1, visible=False, showticklabels=False)

    return fig


def track(time_stamp=0, theme="Dark", size="medium"):
    index = int(time_stamp * PARTITION) % n

    highlight = go.Scatter(x=x, y=y, mode='lines',
                           line=dict(width=4, color=themes[theme]["trace"][6][2]),
                           showlegend=False
                           )

    line = go.Scatter(x=x, y=y, mode='lines',
                      line=dict(width=2, color=themes[theme]["trace"][0][2]),
                      showlegend=False
                      )

    # position = go.Scatter(x=[x[index]], y=[y[index]], mode='markers',
    position = go.Scatter(x=[x[index]], y=[y[index]], mode='markers',
                          marker=dict(size=16, color=themes[theme]["trace"][0][2],
                                      line=dict(width=4, color=themes[theme]["color"][0][2]),
                                      symbol="circle"),
                          showlegend=False,
                          )

    fig = go.Figure()
    fig.add_trace(highlight)
    fig.add_trace(line)
    fig.add_trace(position)

    # Set the plot title and axis labels
    fig.update_layout(title='Track',
                      font=dict(
                          family=themes[theme]["font"]["graph"],
                          size=int(themes[theme]["size"][size]),
                          color=themes[theme]["color"][2][2]
                      ),
                      margin=dict(l=45, r=45, t=40, b=0),
                      paper_bgcolor=themes[theme]["color"][0][1],
                      plot_bgcolor=themes[theme]["color"][0][1],
                      )

    # remove everything on the graph besides the points
    fig.update_yaxes(nticks=1, visible=False, showticklabels=False)
    fig.update_xaxes(nticks=1, visible=False, showticklabels=False)

    return fig


def g_force(lat, lon, max=10, theme="Dark", size="medium"):
    """
    Create a scatter plot with a single point to show instantaneous g-force
    :param max: (int) maximum value of the graph
    :param lon: (float) longitudinal g force
    :param lat: (float) latitudinal g force
    :param size: (string) select size of graph such as 'small', 'medium', or 'large'
    :param theme: (string) select display theme such as 'Dark' or 'Jarvis'
    :return: (figure) g-force plot
    """

    net = go.Scatter(
        x=[lat], y=[lon], mode='markers',
        marker=dict(size=30, color=themes[theme]["trace"][0][2]),
        showlegend=False
    )

    # initialize display figure and plot point
    fig = go.Figure()
    fig.add_trace(net)

    # update layout to match theme
    fig.update_layout(
        # fix vertical and horizontal sizes
        xaxis=dict(
            range=[-max, max],
            autorange=False,
        ),
        yaxis=dict(
            range=[-max, max],
            autorange=False,
        ),
        title='G Force',
        font=dict(
            family=themes[theme]["font"]["graph"],
            size=int(themes[theme]["size"][size]),
            color=themes[theme]["color"][2][2]
        ),
        margin=dict(l=45, r=45, t=40, b=0),
        paper_bgcolor=themes[theme]["color"][0][1],
        plot_bgcolor=themes[theme]["color"][1][1],
    )

    # remove everything on the graph besides the points
    fig.update_yaxes(nticks=1, visible=True, showticklabels=False)
    fig.update_xaxes(nticks=1, visible=True, showticklabels=False)

    return fig