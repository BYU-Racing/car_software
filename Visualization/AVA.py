from dash import Dash, dcc, html
from dash.dependencies import Input, Output
import plotly.express as px

import webbrowser
import cProfile

from Plots import *
from Config import themes, Sensor

# TODO play button

# create Dash object
app = Dash(__name__)

# load data
# all_sensors, duration = readData(SOURCE)
all_sensors = readData(SOURCE)

# initialize local starting variables
duration = 5
ready = False
view = THEME[1]

# construct initial plots
fig = display_dashboard(all_sensors, theme=view)
spd = speedometer(0, theme=view)
pdl = pedals(theme=view)

# styles
button_style = [  # selected
    {'fontFamily': themes[view]["font"]["title"],
     'color': themes[view]["color"][1][2],
     'backgroundColor': themes[view]["color"][2][2],
     'fontSize': themes[view]["size"]["medium"] + "px",
     'display': 'inline-block', 'width': '9%', 'marginLeft': '6px',
     'marginBottom': '10px',
     'border': "1.5px solid " + themes[view]["color"][0][0],
     },
    # deselected
    {'fontFamily': themes[view]["font"]["title"],
     'color': themes[view]["color"][2][2],
     'backgroundColor': themes[view]["color"][0][0],
     'fontSize': themes[view]["size"]["medium"] + "px",
     'display': 'inline-block', 'width': '9%', 'marginLeft': '6px',
     'marginBottom': '10px',
     'border': "1.5px solid " + themes[view]["color"][2][2],
     },
]

# DISPLAY DASHBOARD
app.layout = html.Div([
    html.Div([

        # loading animation
        dcc.Loading(
            id="loading-1",
            type="default",
            children=html.Div(id="loading-output-1"),
            style={'width': '100px', 'display': 'inline-block', 'textAlign': 'center', },
            color=themes[view]["color"][2][2],
        ),

        # logo
        # html.Img(src=app.get_asset_url("club_logo.JPG"),
        #          style={'width': '8%', 'height': 'auto', 'marginLeft': '10px', 'marginBottom': '5px',
        #                 'display': 'inline-block', 'verticalAlign': 'bottom'}),

        # title
        html.H1('A.V.A.', style={'color': themes[view]["color"][2][2],
                                 'paddingLeft': '10px', 'paddingTop': '0px',
                                 'paddingBottom': '0px', 'margin': '0px',
                                 'display': 'inline-block', 'width': '10%',
                                 'fontFamily': themes[view]["font"]["title"],
                                 'fontStyle': 'italic', 'verticalAlign': 'bottom',
                                 'marginBottom': '5px',
                                 },
                id='dashboard-title'),

        # tab buttons
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
        html.Button('G-Force', id='g-button', n_clicks=0,
                    style=button_style[0]),

        # display toggle
        dcc.RadioItems(['Expanded', 'Condensed'], 'Expanded',
                       id='size_radio',
                       labelStyle={'display': 'block'},
                       style={
                           'fontFamily': themes[view]["font"]["title"],
                           'color': themes[view]["color"][2][2],
                           'fontSize': themes[view]["size"]["small"] + "px",
                           'display': 'inline-block', 'width': '12%', "padding": '0px',
                           'marginLeft': '15px', 'marginTop': '0px', 'verticalAlign': 'bottom',
                           'marginBottom': '5px',
                       }),
    ]),

    # main line charts
    dcc.Graph(
        id='car_go_fast',
        figure=fig,
        style={'width': '100%', 'height': '120vh', 'margin': '0px'}
    ),

    # slider to select and view instantaneous values
    html.Div([
        dcc.Slider(id='time-slider', min=0, max=duration, step=1 / PARTITION, value=0,
                   marks={0: {'label': "0",
                              'style': {'color': themes[view]["color"][2][2]}},
                          duration / 2: {'label': str(duration / 2),
                                         'style': {'color': themes[view]["color"][2][2]}},
                          duration: {'label': str(duration),
                                     'style': {'color': themes[view]["color"][2][2]}}
                          },
                   updatemode='drag',
                   ),
        ], style={'marginLeft': '50px', 'width': '80%',
                  'fontFamily': themes[view]["font"]["title"],
                  'color': themes[view]["color"][2][2],
                  'fontSize': themes[view]["size"]["small"] + "px",},
    ),

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

        # accelerometer g force
        dcc.Graph(id='g-force',
                  config={'displayModeBar': False},
                  style={'width': '50vh', 'height': '40vh', 'display': 'inline-block', }),

        # steering wheel
        dcc.Graph(id='steering-wheel',
                  config={'displayModeBar': False},
                  style={'width': '50vh', 'height': '40vh', 'display': 'inline-block', }),

        # track position
        dcc.Graph(id='track-position',
                  config={'displayModeBar': False},
                  style={'width': '50vh', 'height': '40vh', 'display': 'inline-block', }),

        # additional text data
        html.P(id='output-values', children="",
               style={'width': '50vh', 'height': '40vh', 'display': 'inline-block',
                      'margin': '10px',
                      'color': themes[view]["color"][2][2],
                      'fontFamily': themes[view]["font"]["p"],
                      'fontSize': themes[view]["size"]["small"] + "px",
                      'verticalAlign': 'top', 'whiteSpace': 'pre-line'})
    ])

],  # overall styling
    style={'backgroundColor': themes[view]["color"][0][2],
           'color': themes[view]["color"][0][2],
           'margin': '0px', 'padding': '0px', 'border': '0px', 'outline': '0px'})


# CALLBACK FUNCTIONS ---------------------------------------------------------------------------------------------------

# SELECT SUBPLOT BUTTONS
@app.callback(
    Output(component_id='acc-button', component_property='style'),
    Output(component_id='brk-button', component_property='style'),
    Output(component_id='tir-button', component_property='style'),
    Output(component_id='str-button', component_property='style'),
    Output(component_id='dmp-button', component_property='style'),
    Output(component_id='bat-button', component_property='style'),
    Output(component_id='g-button', component_property='style'),
    Output(component_id='car_go_fast', component_property='figure'),
    Output(component_id='car_go_fast', component_property='style'),
    Output(component_id="loading-output-1", component_property="children"),

    Input(component_id='acc-button', component_property='n_clicks'),
    Input(component_id='brk-button', component_property='n_clicks'),
    Input(component_id='tir-button', component_property='n_clicks'),
    Input(component_id='str-button', component_property='n_clicks'),
    Input(component_id='dmp-button', component_property='n_clicks'),
    Input(component_id='bat-button', component_property='n_clicks'),
    Input(component_id='g-button', component_property='n_clicks'),
    Input(component_id='size_radio', component_property='value'),
)
def select_plots(n_click0, n_click1, n_click2, n_click3, n_click4, n_click5, n_click6, size):
    """
    Select which subplots to show and the size of the overall chart
    :param n_click0: number of times the accelerator tab has been clicked
    :param n_click1: number of times the brake tab has been clicked
    :param n_click2: number of times the tires tab has been clicked
    :param n_click3: number of times the steering wheel tab has been clicked
    :param n_click4: number of times the damper position tab has been clicked
    :param n_click5: number of times the battery tab has been clicked
    :param n_click6: number of times the g-force tab has been clicked
    :param size: selection for display size
    :return: button style and new main line chart
    """
    # turn click input into a list
    index = [n_click0, n_click1, n_click2, n_click3, n_click4, n_click5, n_click6]
    on = [i % 2 for i in index]

    # build available list based on which subplots to display
    avail = []
    for i in range(len(on)):
        if i == 0 and on[i] == 0:
            avail.append(Sensor.ACC1.value)
            avail.append(Sensor.ACC2.value)
        elif i == 1 and on[i] == 0:
            avail.append(Sensor.BRAKE.value)
        elif i == 2 and on[i] == 0:
            avail.append(Sensor.TIRE1.value)
            avail.append(Sensor.TIRE2.value)
            avail.append(Sensor.TIRE3.value)
            avail.append(Sensor.TIRE4.value)
        elif i == 3 and on[i] == 0:
            avail.append(Sensor.ANGLE.value)
        elif i == 4 and on[i] == 0:
            avail.append(Sensor.DAMP1.value)
            avail.append(Sensor.DAMP2.value)
            avail.append(Sensor.DAMP3.value)
            avail.append(Sensor.DAMP4.value)
        elif i == 5 and on[i] == 0:
            avail.append(Sensor.TEMP.value)
        elif i == 6 and on[i] == 0:
            avail.append(Sensor.GFORCE.value)

    # built output list
    buttons = [button_style[i % 2] for i in index]

    # resize the additional charts based on size input
    if size == "Expanded":
        tall = '120vh'
        resize = "small"
    else:
        tall = '60vh'
        resize = "mini"

    # rebuild the main plot with the new availability list
    new_plot = display_dashboard(all_sensors, theme=view, size=resize, avail=avail, num_plots=len(on) - sum(on))
    buttons.append(new_plot)

    reformat = {'width': '100%', 'height': tall, 'margin': '0px'}
    buttons.append(reformat)
    buttons.append(size)

    # return output list
    return buttons


# SELECT TIME SLIDER AND DISPLAY MODE RADIO BUTTONS
@app.callback(
    Output(component_id='output-values', component_property='children'),
    Output(component_id='speedometer', component_property='figure'),
    Output(component_id='pedals', component_property='figure'),
    Output(component_id='steering-wheel', component_property='figure'),
    Output(component_id='track-position', component_property='figure'),
    Output(component_id='g-force', component_property='figure'),
    Output(component_id='speedometer', component_property='style'),
    Output(component_id='pedals', component_property='style'),
    Output(component_id='steering-wheel', component_property='style'),
    Output(component_id='track-position', component_property='style'),
    Output(component_id='g-force', component_property='style'),

    Input(component_id='time-slider', component_property='value'),
    Input(component_id='size_radio', component_property='value'),
)
def update_output_div(input_value, size):
    """
    Update each chart based on the input time from the slider object
    Parameters:
        :param size: (string) the size of the display
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
               speedometer(0, maxim=10, theme=view), \
               pedals(theme=view), \
               steering(theme=view), \
               track(theme=view), \
               g_force(0, 0, theme=view)

    else:
        # get the values of each subplot at the input time
        values = []
        for i in range(len(legend)):
            trace = fig['data'][i]
            value = round(trace['y'][int(time * PARTITION)], 4) if time * PARTITION < len(trace['y']) else None
            values.append(f'{legend[i]}: {value}')

        # compute the average speed to display
        speed = np.mean([float(values[i].split(":")[1][1:]) for i in range(3, 7)])

        # get brake and accelerator values
        brake = float(values[2].split(":")[1][1:])
        acceleration = np.mean([float(values[i].split(":")[1][1:]) for i in range(0, 2)])

        # compute the instantaneous g-force to display
        lat_g = brake
        lon_g = speed

        # display extra values
        extra = "Time: " + str(input_value) + "\n\n" + '\n'.join(values[-5:])
        """id='output-values',
        style={'width': '50vh', 'height': '40vh', 'display': 'inline-block',
          'color': themes[view]["color"][2][2],
          'fontFamily': themes[view]["font"]["p"],
          'fontSize': themes[view]["size"]["small"] + "px",
          'verticalAlign': 'top', 'whiteSpace': 'pre-line'}
        )"""

        # get steering angle
        angle = float(values[9].split(":")[1][1:])

        # update sizes
        if size == "Expanded":
            wide = '50vh'
            tall = '40vh'
            resize = "medium"
        else:
            wide = '35vh'
            tall = '28vh'
            resize = "small"

        update = {'width': wide, 'height': tall, 'display': 'inline-block'}

        # return figures
        global ready
        if not ready:
            print("AVA is ready")
            ready = True
        return extra, \
               speedometer(speed, maxim=2, theme=view, size=resize), \
               pedals(brake, acceleration, maxim=5, theme=view, size=resize), \
               steering(angle=angle, theme=view, size=resize), \
               track(time_stamp=input_value, theme=view, size=resize), \
               g_force(lat_g, lon_g, theme=view, size=resize), \
               update, update, update, update, update


def do_the_thing():
    app.run_server(debug=True)

if __name__ == '__main__':
    # webbrowser.get(CHROME).open(LOCAL_HOST)
    # app.run_server(debug=False)
    cProfile.run('do_the_thing()', filename='my_profiling_results')
