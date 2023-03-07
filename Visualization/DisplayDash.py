from dash import Dash, dcc, html, ctx
from dash.dependencies import Input, Output
import plotly.express as px
import pandas as pd
import numpy as np
import main

# TODO play button
# TODO select theme
# TODO write README
# TODO make loading screen
# TODO fix steering wheel
# TODO add logo and name

# create Dash object
app = Dash(__name__)

# load data
file_name = 'Data/Master.csv'
all_sensors = main.readData(file_name)

# initialize local starting variables
time_end = 5
freq = 250
view = "Jarvis"

# construct initial plots
fig = main.display_dashboard(all_sensors, theme=view)
spd = main.speedometer(0, theme=view)
pdl = main.pedals(theme=view)

# styles
button_style = [    # selected
                {'font-family': main.themes[view]["font"]["title"],
                 'color': main.themes[view]["color"][0][0],
                 'background-color': main.themes[view]["color"][2][2],
                 'font-size': main.themes[view]["size"]["medium"] + "px",
                 'display': 'inline-block', 'width': '10%', 'marginLeft': '8px',
                 'marginBottom': '25px',
                 'border': "1.5px solid " + main.themes[view]["color"][0][0],
                 },
                    # deselected
                {'font-family': main.themes[view]["font"]["title"],
                 'color': main.themes[view]["color"][2][2],
                 'background-color': main.themes[view]["color"][0][0],
                 'font-size': main.themes[view]["size"]["medium"] + "px",
                 'display': 'inline-block', 'width': '10%', 'marginLeft': '8px',
                 'marginBottom': '25px',
                 'border': "1.5px solid " + main.themes[view]["color"][2][2],
                 },
                ]

# set dashboard layout
app.layout = html.Div([
    html.Div([
        # title
        html.H1('A.V.A.', style={'color': main.themes[view]["color"][2][2],
                                 'paddingLeft': '30px', 'paddingTop': '10px',
                                 'paddingBottom': '0px', 'margin': '0px',
                                 'display': 'inline-block', 'width': '16%',
                                 'font-family': main.themes[view]["font"]["title"],
                                 'font-style': 'italic'
                                 },
                id='dashboard-title'),
        html.Button('Accelerator', id='acc-button', n_clicks=0,
                    style=button_style[0]),
        html.Button('Brake', id='brk-button', n_clicks=0,
                    style=button_style[0]),
        html.Button('Tires', id='tir-button', n_clicks=0,
                    style=button_style[0]),
        html.Button('Steering', id='str-button', n_clicks=0,
                    style=button_style[0]),
        html.Button('Dampers', id='dmp-button', n_clicks=0,
                    style=button_style[0]),
        html.Button('Battery', id='bat-button', n_clicks=0,
                    style=button_style[0]),
        dcc.RadioItems(['Expanded', 'Condensed'], 'Expanded',
                       id='size_radio',
                       style={
                         'font-family': main.themes[view]["font"]["title"],
                         'color': main.themes[view]["color"][2][2],
                         # 'background-color': main.themes[view]["color"][2][2],
                         'font-size': main.themes[view]["size"]["small"] + "px",
                         'display': 'inline-block', 'width': '12%', "padding": '0px',
                         'marginLeft': '15px', 'marginTop': '20px'
                       })
    ]),
    # main line charts
    dcc.Graph(
        id='car_go_fast',
        figure=fig,
        style={'width': '100%', 'height': '120vh', 'margin': '0px'}
    ),
    # slider to select and view instantaneous values
    html.Div([
        dcc.Slider(id='time-slider', min=0, max=time_end, step=0.001, value=0,
                   marks={0: "0", time_end / 2: str(time_end / 2), time_end: str(time_end)}),
        # dcc.Interval(id='interval-component', interval=freq, n_intervals=0)
    ], style={'marginLeft': '50px', 'width': '80%'}),
    html.Div([
        # speedometer
        dcc.Graph(
            id='speedometer',
            figure=spd,
            style={'width': '50vh', 'height': '40vh', 'display': 'inline-block', }
        ),
        # bar chart for brake and accelerator
        dcc.Graph(
            id='pedals',
            figure=pdl,
            style={'width': '50vh', 'height': '40vh', 'display': 'inline-block', }
        ),
        # steering wheel
        dcc.Graph(id='steering-wheel',
                  config={'displayModeBar': False},
                  style={'width': '50vh', 'height': '40vh', 'display': 'inline-block', }),
        # additional text data
        html.P(id='output-values',
               style={'width': '50vh', 'height': '40vh', 'display': 'inline-block',
                      'color': main.themes[view]["color"][2][2],
                      'font-family': main.themes[view]["font"]["p"],
                      'font-size': main.themes[view]["size"]["small"] + "px",
                      'vertical-align': 'top', 'white-space': 'pre-line'}),
    ])
],
    style={'background-color': main.themes[view]["color"][0][2],
           'color': main.themes[view]["color"][0][2],
           'margin': '0px', 'padding': '0px', 'border': '0px', 'outline': '0px'})


# # Define the callback function
# @app.callback(Output('time-slider', 'value'),
#               Input('interval-component', 'n_intervals'))
# def update_slider_graph(n):
#     return ((n*freq) % (time_end * 1000)) / 1000


@app.callback(
    Output(component_id='acc-button', component_property='style'),
    Output(component_id='brk-button', component_property='style'),
    Output(component_id='tir-button', component_property='style'),
    Output(component_id='str-button', component_property='style'),
    Output(component_id='dmp-button', component_property='style'),
    Output(component_id='bat-button', component_property='style'),
    Output(component_id='car_go_fast', component_property='figure'),
    Output(component_id='car_go_fast', component_property='style'),
    Input(component_id='acc-button', component_property='n_clicks'),
    Input(component_id='brk-button', component_property='n_clicks'),
    Input(component_id='tir-button', component_property='n_clicks'),
    Input(component_id='str-button', component_property='n_clicks'),
    Input(component_id='dmp-button', component_property='n_clicks'),
    Input(component_id='bat-button', component_property='n_clicks'),
    Input(component_id='size_radio', component_property='value'),
)
def select_plots(n_click0, n_click1, n_click2, n_click3, n_click4, n_click5, size):
    index = [n_click0, n_click1, n_click2, n_click3, n_click4, n_click5]
    on = [i % 2 for i in index]
    avail = []
    for i in range(len(on)):
        if i == 0 and on[i] == 0:
            avail.append(main.Sensor.ACC1.value)
            avail.append(main.Sensor.ACC2.value)
        elif i == 1 and on[i] == 0:
            avail.append(main.Sensor.BRAKE.value)
        elif i == 2 and on[i] == 0:
            avail.append(main.Sensor.TIRE1.value)
            avail.append(main.Sensor.TIRE2.value)
            avail.append(main.Sensor.TIRE3.value)
            avail.append(main.Sensor.TIRE4.value)
        elif i == 3 and on[i] == 0:
            avail.append(main.Sensor.ANGLE.value)
        elif i == 4 and on[i] == 0:
            avail.append(main.Sensor.DAMP1.value)
            avail.append(main.Sensor.DAMP2.value)
            avail.append(main.Sensor.DAMP3.value)
            avail.append(main.Sensor.DAMP4.value)
        elif i == 5 and on[i] == 0:
            avail.append(main.Sensor.TEMP.value)

    buttons = [button_style[i % 2] for i in index]

    new_plot = main.display_dashboard(all_sensors, theme=view, avail=avail, num_plots=len(on)-sum(on))
    buttons.append(new_plot)

    if size == "Expanded":
        tall = '120vh'
    else:
        tall = '60vh'
    reformat = {'width': '100%', 'height': tall, 'margin': '0px'}
    buttons.append(reformat)

    return buttons



# define a callback function to update the output values based on the input time
@app.callback(
    Output(component_id='output-values', component_property='children'),
    Output(component_id='speedometer', component_property='figure'),
    Output(component_id='pedals', component_property='figure'),
    Output(component_id='steering-wheel', component_property='figure'),
    Output(component_id='speedometer', component_property='style'),
    Output(component_id='pedals', component_property='style'),
    Output(component_id='steering-wheel', component_property='style'),
    Input(component_id='time-slider', component_property='value'),
    Input(component_id='size_radio', component_property='value'),
)
def update_output_div(input_value, size):
    """
    Update each chart based on the input time from the slider object
    Parameters:
        :param input_value: (string) the desired time to view data at
    Returns:
        :return: list of updated plots
    """
    # parse the input time and convert it to an integer
    try:
        time = float(input_value)
    except ValueError:
        time = None
    # if the input is not a valid integer, display an error message
    if time is None:
        return 'Please enter a valid decimal time greater than zero.', \
               main.speedometer(0, maxim=10), \
               main.pedals(), \
               main.steering()

    else:
        # get the values of each subplot at the input time
        values = []
        for i in range(1, len(main.legend) + 1):
            trace = fig['data'][i - 1]
            value = round(trace['y'][int(time * 1000)], 4) if time * 1000 < len(trace['y']) else None
            values.append(f'{main.legend[i - 1]}: {value}')

        # compute the average speed to display
        speed = np.mean([float(values[i].split(":")[1][1:]) for i in range(3, 7)])

        # get brake and accelerator values
        brake = float(values[2].split(":")[1][1:])
        acceleration = np.mean([float(values[i].split(":")[1][1:]) for i in range(0, 2)])

        # display extra values
        extra = html.P("Time: " + str(input_value) + "\n\n" + '\n'.join(values[-5:]),
                       id='output-values',
                       style={'width': '50vh', 'height': '40vh', 'display': 'inline-block',
                              'color': main.themes[view]["color"][2][2],
                              'font-family': main.themes[view]["font"]["p"],
                              'font-size': main.themes[view]["size"]["small"] + "px",
                              'vertical-align': 'top', 'white-space': 'pre-line'}
                       )

        # get steering angle
        angle = float(values[9].split(":")[1][1:])

        # update sizes
        if size == "Expanded":
            wide = '50vh'
            tall = '40vh'
        else:
            wide = '35vh'
            tall = '28vh'
        update = {'width': wide, 'height': tall, 'display': 'inline-block'}

        # return figures
        return extra, \
               main.speedometer(speed, maxim=2, theme=view), \
               main.pedals(brake, acceleration, maxim=5, theme=view), \
               main.steering(angle=angle, theme=view), \
               update, update, update


if __name__ == '__main__':
    app.run_server(debug=True)
