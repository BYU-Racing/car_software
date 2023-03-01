from dash import Dash, dcc, html
from dash.dependencies import Input, Output
import plotly.express as px
import pandas as pd
import main

app = Dash(__name__)

file_name = 'Data/Master.csv'
all_sensors = main.readData(file_name)
# plot(all_sensors[0])
fig = main.display_dashboard(all_sensors, dark_mode=True)
spd = main.speedometer(0)

app.layout = html.Div([
    html.Div([
        html.H1('Car Go Fast!', style={'color': '#FFFFFF',
                                       'paddingLeft': '30px', 'paddingTop': '10px',
                                       'paddingBottom': '0px', 'margin': '0px',
                                       'display': 'inline-block', 'width': '33%'},
                id='dashboard-title'),
        dcc.Input(
            id='input-time',
            type='text',
            placeholder='Enter a time in seconds',
            value='',
            style={'width': '15%', 'margin': '10px', 'font': "Courier New", }
        ),
        html.Div(id='output-values',
                 style={'width': '40%', 'color': '#FFFFFF', 'display': 'inline-block',
                        'font-family': "Courier New", 'font-size': '14px'})
    ]),
    dcc.Graph(
        id='car_go_fast',
        figure=fig,
        style={'width': '210vh', 'height': '120vh', 'margin': '0px'}
    ),
    dcc.Graph(
        id='speedometer',
        figure=spd,
        style={'width': '50vh', 'height': '40vh'}
    )
],
    style={'background-color': '#3C3C3C', 'color': '#3C3C3C',
           'margin': '0px', 'padding': '0px', 'border': '0px', 'outline': '0px'})


# define a callback function to update the output values based on the input time
@app.callback(
    Output(component_id='output-values', component_property='children'),
    Output(component_id='speedometer', component_property='figure'),
    Input(component_id='input-time', component_property='value')
)
def update_output_div(input_value):
    # parse the input time and convert it to an integer
    # time = int(input_value) if input_value.isdigit() else None
    try:
        time = float(input_value)
    except ValueError:
        time = None
    # if the input is not a valid integer, display an error message
    if time is None:
        return 'Please enter a valid decimal time greater than zero.', main.speedometer(0, max=10)

    else:
        # get the values of each subplot at the input time
        values = []
        for i in range(1, 7):
            trace = fig['data'][i - 1]
            value = round(trace['y'][int(time * 1000)], 4) if time * 1000 < len(trace['y']) else None
            values.append(f'{main.legend[i - 1]}: {value}')
        # create a `Div` element to display the values
        return html.Div(', '.join(values)), main.speedometer(float(values[2].split(":")[1][1:]), max=10)


if __name__ == '__main__':
    app.run_server(debug=True)
