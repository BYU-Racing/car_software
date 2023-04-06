from enum import Enum


MPS = 0.000278
PARTITION = 1000.
THEME = ["Arduino", "Jarvis", "Daylight"]
SHOW_INSTANTS = False

SOURCE = 'Data/Master.csv'
LOCAL_HOST = "http://127.0.0.1:8050/"
CHROME = "C:/Program Files (x86)/Google/Chrome/Application/chrome.exe %s"

# convert each sensor to a number
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
    GFORCE = 15


# sensor constants
weights = {
    "W_ACC1": 0.0,
    "W_ACC2": 0.0,
    "W_BRAKE": 0.0,
    "W_SWITCH": 0.0,
    "W_ANGLE": 0.0,
    "W_TIRE1": 0.0,
    "W_TIRE2": 0.0,
    "W_TIRE3": 0.0,
    "W_TIRE4": 0.0,
    "W_DAMP1": 0.0,
    "W_DAMP2": 0.0,
    "W_DAMP3": 0.0,
    "W_DAMP4": 0.0,
    "W_TEMP": 0.0,
    "W_LIGHT": 0.0,
    "W_GFORCE": 0.0,
}

biases = {
    "B_ACC1": 0.0,
    "B_ACC2": 0.0,
    "B_BRAKE": 0.0,
    "B_SWITCH": 0.0,
    "B_ANGLE": 0.0,
    "B_TIRE1": 0.0,
    "B_TIRE2": 0.0,
    "B_TIRE3": 0.0,
    "B_TIRE4": 0.0,
    "B_DAMP1": 0.0,
    "B_DAMP2": 0.0,
    "B_DAMP3": 0.0,
    "B_DAMP4": 0.0,
    "B_TEMP": 0.0,
    "B_LIGHT": 0.0,
    "B_GFORCE": 0.0,
}

minimums = {
    "N_ACC1": 0.0,
    "N_ACC2": 0.0,
    "N_BRAKE": 0.0,
    "N_SWITCH": 0.0,
    "N_ANGLE": 0.0,
    "N_TIRE1": 0.0,
    "N_TIRE2": 0.0,
    "N_TIRE3": 0.0,
    "N_TIRE4": 0.0,
    "N_DAMP1": 0.0,
    "N_DAMP2": 0.0,
    "N_DAMP3": 0.0,
    "N_DAMP4": 0.0,
    "N_TEMP": 0.0,
    "N_LIGHT": 0.0,
    "N_GFORCE": 0.0,
}

maximums = {
    "X_ACC1": 1.0,
    "X_ACC2": 1.0,
    "X_BRAKE": 1.0,
    "X_SWITCH": 1.0,
    "X_ANGLE": 1.0,
    "X_TIRE1": 1.0,
    "X_TIRE2": 1.0,
    "X_TIRE3": 1.0,
    "X_TIRE4": 1.0,
    "X_DAMP1": 1.0,
    "X_DAMP2": 1.0,
    "X_DAMP3": 1.0,
    "X_DAMP4": 1.0,
    "X_TEMP": 1.0,
    "X_LIGHT": 1.0,
    "X_GFORCE": 1.0,
}

# convert each sensor index to its abbreviated name
sensor_names = {
    0: "ACC1",
    1: "ACC2",
    2: "BRAKE",
    3: "SWITCH",
    4: "ANGLE",
    5: "TIRE1",
    6: "TIRE2",
    7: "TIRE3",
    8: "TIRE4",
    9: "DAMP1",
    10: "DAMP2",
    11: "DAMP3",
    12: "DAMP4",
    13: "TEMP",
    14: "LIGHT",
    15: "GFORCE",
}

# convert an index to a sensor display name
sensors = {
    0: 'Accelerator 1',
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
    13: 'Battery Temperature',
    14: 'Rain Light',
    15: 'G-Force',
}

# theme customization
themes = {"Arduino": {  # theme name
    "color": {  # color palette for graphs and backgrounds
        0: ["gray", "rgba(60,60,60,1)", "#3C3C3C"],  # assigned to overall background
        1: ["dark-gray", "rgba(40,40,40,1)", "#222222"],  # subplot background to differentiate from background
        2: ["green", "rgba(0,154,0,1)", "#009900"],  # Text color
        3: ["white", "rgba(255,2555,255,1)", "#FFFFFF"],  # Alternate text color, also just white
        4: ["black", "rgba(0,0,0,1)", "#000000"],  # Steering wheel color, also just black
    },
    "trace": {
        0: ["green", "rgba(0,154,0,1)", "#009900"],  # color for traces and bar charts
        1: ["red", "rgba(154,0,0,1)", "#990000"],
        2: ["green", "rgba(0,154,0,1)", "#009900"],  # color for traces and bar charts
        3: ["green", "rgba(0,154,0,1)", "#009900"],
        4: ["green", "rgba(0,154,0,1)", "#009900"],  # color for traces and bar charts
        5: ["green", "rgba(0,154,0,1)", "#009900"],
        6: ["green", "rgba(0,154,0,1)", "#009900"],  # color for traces and bar charts
    },
    "size": {
        "large": "22",  # large text like graph titles
        "medium": "16",  # medium text like like legends
        "small": "14",  # small text like graph ticks
        "mini": "10",  # mini text like graph ticks
    },
    "font": {
        "title": "Courier New",  # dashboard title
        "p": "Courier New",  # most text
        "graph": "Courier New",  # alt text font for some graphs
    }
},
    "Jarvis": {
        "color": {
            0: ["black", "rgba(0,0,0,1)", "#000000"],  # assigned to overall background
            1: ["dark-gray", "rgba(16, 16, 20,1)", "#111111"],  # subplot background to differentiate from background
            2: ["neon_blue", "rgba(2, 255, 252, 1)", "#02fffc"],  # Text color
            3: ["white", "rgba(255,2555,255,1)", "#FFFFFF"],  # Alternate text color, also just white
            4: ["dark-gray", "rgba(216, 216, 216,1)", "#888888"],  # Steering wheel color, also just black
        },
        "trace": {
            0: ["neon_blue", "rgba(2, 255, 252, 1)", "#02fffc"],
            1: ["neon_yellow", "rgba(248, 255, 51, 1)", "#f8ff33"],
            2: ["neon_blue", "rgba(2, 255, 252, 1)", "#02fffc"],
            3: ["olive", "rgba(2, 207, 252, 1)", "#02cffc"],
            4: ["pond", "rgba(2, 255, 220, 1)", "#02ffcc"],
            5: ["forest_idk_main", "rgba(2, 169, 252, 1)", "#029ffc"],
            6: ["white", "rgba(255,255,255,1)", "#FFFFFF"],  # Alternate text color, also just white
        },
        "size": {
            "large": "24",
            "medium": "18",
            "small": "15",
            "mini": "10",
        },
        "font": {
            "title": "Arial, sans-serif",
            "p": "Arial, sans-serif",
            "graph": "Arial, sans-serif",
        }
    },
    "Daylight": {
        "color": {
            0: ["white", "rgba(255,255,255,1)", "#FFFFFF"],  # assigned to overall background
            1: ["light-gray", "rgba(239, 239, 239,1)", "#EEEEEE"],
            # subplot background to differentiate from background
            2: ["black", "rgba(0,0,0,1)", "#000000"],  # Text color
            3: ["black", "rgba(0,0,0,1)", "#000000"],  # Alternate text color, also just white
            4: ["black", "rgba(0,0,0,1)", "#000000"],  # Steering wheel color, also just black
        },
        "trace": {
            0: ["red", "rgba(255,0,0,1)", "#ff0000"],
            1: ["red", "rgba(255,0,0,1)", "#ff0000"],
            2: ["red", "rgba(255,0,0,1)", "#ff0000"],
            3: ["red", "rgba(255,0,0,1)", "#ff0000"],
            4: ["red", "rgba(255,0,0,1)", "#ff0000"],
            5: ["red", "rgba(255,0,0,1)", "#ff0000"],
            6: ["red", "rgba(255,0,0,1)", "#ff0000"],
        },
        "size": {
            "large": "28",
            "medium": "22",
            "small": "18",
            "mini": "12",
        },
        "font": {
            "title": "Arial, sans-serif",
            "p": "Arial, sans-serif",
            "graph": "Arial, sans-serif",
        }
    }
}
