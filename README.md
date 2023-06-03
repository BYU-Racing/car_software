# FormulaE
BYU Racing Team Repo

#### In order for our car to drive and be legal it must have:
<p> A go pedal that is monitored by two sensors with different transfer functions<br>
 An inertial switch as specified in the rules<br>
 A rotary or key switch<br>
 A brake over travel switch<br>
 A brake light<br>
 A tractive system active light</p>
 
#### In order for our car to gather useful data it must:
<p>  Store data to an sd card<br>
  Send information through each component to a central data logger<br>
  Have an accelerometer</p>
  
#### We would like our car to be able to measure:
<p>  Wheel speed<br>
  Brake pressure<br>
  damper deflection (Damper potentiometers)<br>
  steering wheel angle</p>
  
#### The car will have the following states and behavior
* Idle/inactive
* Idle (with brakelight on)
* Active
* Active Braking
* Limited Active
* Limited Braking

##### Idle
* Tractive system will be off
* Either the inertia switch has been triggered or the key is off
* If the brake pedal is pressed it will switch to the idle braking state
* If the key is on and the inertia switch is OK it will switch to the active State

##### Idle Braking
* behaves the same as Idle, but with the brake light on

##### Active
* Tractive System will be active
* The "go pedal" will be active
* brake pedal activation will send it to the Active braking state
* if the key is switched off or the inertia switch is triggered it will switch to the idle mode
* if the HV system gives a warning (temp or voltage) it will switch to limited active

##### Active Braking
* The brake light will be activated
* The go pedal will be disabled
* (does it need to do anything to recharge?)
* Behaves like Active but sends to the associated braking state instead

##### Limited Active
* Limits certian behaviors as needed until the system returns to normal
* Other details to be determined

##### Limited Braking
* same as active braking but for limited mode
