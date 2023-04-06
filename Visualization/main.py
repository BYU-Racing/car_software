from Plots import *
from Converter import *

# if this is your first time using this program, main has been deprecated. Please use AVA.py

if __name__ == "__main__":
    pass
    # create a plotly plot using data
    file_name = 'Data/Master.csv'
    all_sensors = readData(file_name)
    display_dashboard(all_sensors).show()


