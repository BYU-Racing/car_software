<a name="readme-top"></a>

<div align="center">
    <h1 align="center">A.V.A.</h1>
    <p align="center">
        An Advanced Vehicle Analytics Application 
        </br>Created by the BYU Formula E Club 2022-2024
    </p>
</div>

<hr>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li><a href="#welcome">Welcome</a></li>
    <li><a href="#instructions">Instructions for Download</a></li>
    <li><a href="#use">Instructions for Use</a></li>
    <li><a href="#mods">Instructions for Modifications</a></li>
    <li><a href="#faq">FAQs</a></li>
  </ol>
</details>

<!-- Welcome -->
## Welcome

This is A.V.A., the Advanced Vehicle Analytics application for the BYU Formula E club.
A.V.A. is a dashboard that displays vehicle and driving data collected from an array of sensors
designed to collect everything from tire speed to steering wheel angle of an electric race car 
while driving. 
</br>
In addition to providing advanced analytics and feedback, A.V.A. visualizes driving information 
in a format that makes it easy to understand and gain insight from the data.
The name is inspired by Ava, the highly capable AI machine from Ex Machina, and the acronym captures 
the contribution this dashboard provides to the BYU Formula E club's engineering challenge of 
electric car racing.

### <a href="https://www.linkedin.com/company/byu-racing/">BYU Formula E</a>

BYU Formula E is an engineering team focused on designing, manufacturing, testing, and competing 
of an open-wheel, electrically-powered race car. It operates under the Formula program of the 
Society of Automotive Engineers (SAE). This team aims to fit all of its work to the yearly 
regulations of FSAE, and perform competitively with the end products of student engineers from around 
the globe.

<hr>


### Instructions for Download

You'll need to start by downloading a few python packages with these commands:
- pip install <a href=https://plotly.com/python/getting-started/>plotly</a>
- pip install <a href=https://dash.plotly.com/installation>dash</a>
- pip install <a href=https://pandas.pydata.org/docs/getting_started/install.html>pandas</a>
- pip install <a href=https://pypi.org/project/bitstring/>bitstring</a>

You can then <a href=https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository>
clone this project</a> to your own machine from GitHub and then run the dashboard in any Python development environment.

<hr>

### Instructions for Use

#### Running:
&emsp;After downloading, run the dash app by running the AVA.py file, then clicking on the
local host link that appears in the command line.
<br>
#### Buttons:
&emsp;The buttons along the top allow you to select with line graphs to display. The program defaults
to all the charts, and clicking on a button once will hide the corresponding chart.
<br>
#### Radio Buttons:
&emsp;The Expanded option is the default option, and displays all the chart in full dimension.
The Condensed option displays all the charts small enough to fit everything on one screen
as long as you are already in full screen on your computer.
<br>
#### Charts:
&emsp;Each chart displays the data from the sensor as described on the y-axis on the right and the
legend on the left with respect to time on the x-axis. The tick marks, values, and lines are hidden
to reduce clutter on the display. Hovering over the curve will display the time and value at that
point as desired.
<br>
#### Slider:
&emsp;Allows you to select the time at which you would like to view instantaneous values.
<br>
#### Speedometer:
&emsp;Displays instantaneous speed at the selected time.
<br>
#### Pedals:
&emsp;Bar chart that displays the pressure on the brake pedal acceleration pedal at the selected time.
<br>
#### Steering Wheel:
&emsp;Animation that displays the angle of the steering wheel at the selected time.
<br>
#### Track:
&emsp;Chart that displays the track the racecar followed, along with its position at the selected time.
<br>
#### Additional Data:
&emsp;Displays the instantaneous values of the rest of the sensors and the selected time at the selected
time.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<hr>

### Instructions for Modifications

Dash and Plotly both have lots of great documentation. If you have questions, contact the creators
at dallinpstewart@gmail.com or message me on LinkedIn. Hopefully the docstring and comments 
are enough to figure out what each function does.

### FAQ:
Why is nothing happening?
- If you click on something and nothing happens, wait a few seconds before retrying in case A.V.A.
is still loading. The interactions enabled either reformat the style of some graphs, or recreate the
graphs entirely, so some actions take a few seconds.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<hr>

### Packages

[![Plotly][Plotly-icon]][Plotly-url] &emsp; &emsp;  [![Dash][Dash-icon]][Dash-url] &emsp; &emsp;

[![Numpy][Numpy-icon]][Numpy-url] &emsp; &emsp; [![Python][Python-icon]][Python-url] &emsp; &emsp; [![Pandas][Pandas-icon]][Pandas-url]    



<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- CONTACT -->
## Contact

Dallin Stewart - dallinpstewart@gmail.com

[![LinkedIn][linkedin-icon]][linkedin-url]
[![GitHub][github-icon]][github-url]
[![Email][email-icon]][email-url]

Benjamin McMullin

[![LinkedIn][linkedin-icon]][linkedin-url2]
[![GitHub][github-icon]][github-url2]

<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- MARKDOWN LINKS & IMAGES -->
[Python-icon]: https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white
[Python-url]: https://www.python.org/

[NumPy-icon]: https://img.shields.io/badge/NumPy-2596be?style=for-the-badge&logo=numpy&logoColor=white
[NumPy-url]: https://numpy.org/

[Pandas-icon]: https://img.shields.io/badge/Pandas-120756?style=for-the-badge&logo=pandas&logoColor=white
[Pandas-url]: https://pandas.pydata.org/

[Plotly-icon]: https://img.shields.io/badge/Plotly-e5558f?style=for-the-badge&logo=plotly&logoColor=white
[Plotly-url]: https://plotly.com/

[Dash-icon]: https://img.shields.io/badge/Dash-7c74fb?style=for-the-badge&logo=dash&logoColor=white
[Dash-url]: https://plotly.com/dash/


[linkedIn-icon]: https://img.shields.io/badge/LinkedIn-0077B5?style=for-the-badge&logo=linkedin&logoColor=white
[linkedIn-url]: https://www.linkedin.com/in/dallinstewart/
[linkedIn-url2]: https://www.linkedin.com/in/benjamin-mcmullin/

[github-icon]: https://img.shields.io/badge/GitHub-100000?style=for-the-badge&logo=github&logoColor=white
[github-url]: https://github.com/binDebug3
[github-url2]: https://github.com/benjaminmcmullin4

[Email-icon]: https://img.shields.io/badge/Email-D14836?style=for-the-badge&logo=gmail&logoColor=white
[Email-url]: mailto:dallinpstewart@gmail.com