from dash import Dash, dcc, html
import plotly.express as px
import pandas as pd
import main


app = Dash(__name__)


file_name = 'Data/Master.csv'
all_sensors = main.readData(file_name)
# plot(all_sensors[0])
fig = main.display_dashboard(all_sensors, dark_mode=True)

app.layout = html.Div([
    dcc.Graph(
        id='life-exp-vs-gdp',
        figure=fig,
        style={'width': '215vh', 'height': '100vh'}
    )
])

if __name__ == '__main__':
    app.run_server(debug=True)