## SensorySculpt Production Guide 


## 🏁 Getting Started 
This device translates ambient noise levels to 



### Materials 
- Arduino UNO WIFI  
- LCD display  
- Two servos (360 continuous & non-continuous) 
- Gravity noise level sensor 
- HC-05 bluetooth – to communicate with the API and the App

  
- Iron Filings
- Sand
- Lasercutter + 3mm wood board
- Wood Stain + Sponge

## Step 1: Assembling Hardware
Overall, our SensorySculpt device 
1) Monitors sensor data (today just noise levels),
2) subscribes to API topics,
3) reads user commands from the APP and
4) visualises data in real-time through the lens of pre-determined mode thresholds.​
   
### Follow the Schematic 
Use the following schematic to set up the servos, screen, and noise sensor. The noise sensor works by ...  
<img width="300" alt="servo, sensor, led schematic" src="https://github.com/CASA0020-group-1/SensorySculpt/assets/127933946/42c0abd6-7dde-4c09-9f27-c51c699ba884">


### Create your Enclosure
- File available here 
- Bend the plywood and stain it 
This 

### Select your Pattern Creation Materials
We tried multiple iterations of pattern face, sand substrate, and pattern tracer materals before we settled on our current device. Considering consumer reviews of the [sisyphus table](https://sisyphus-industries.com/shop/) prompted us to weigh pattern clarity and noise levels above most other elements.  
### Pattern faces
<img src="https://github.com/CASA0020-group-1/SensorySculpt/assets/127933946/ea5c5818-ab2c-4427-8a51-8bc4adfbdd46" width="200">
<img src="https://github.com/CASA0020-group-1/SensorySculpt/assets/127933946/66e0a0b0-78f4-4e38-b1db-681e923f5b9e" width="200">

While it is tempting (and satisfying) to fill the entire pattern face with sand, this results in markedly worse pattern clarity across attempts and is a little messy to clean up. An appropriate amount of sand will allow you to still see the pattern face through the sand. 

<img width="200" alt="quantity of sand" src="https://github.com/CASA0020-group-1/SensorySculpt/assets/127933946/ca0de091-0901-4b22-9854-cb1ccbd58d38">


## Step 2: Flash the Board with the Rotation Software
The pattern creation software is available here. 

### Pattern / Visual Feedback Guide  
<img width="483" alt="image" src="https://github.com/CASA0020-group-1/SensorySculpt/assets/127933946/5c8d787a-d9c2-4861-8a42-b68cbcb4b330">


## Step 3: Download App and Flashing Firmware  
The full potential of our product can be realized when you connect it to an API. This allows you to swich between different streams of environmental data that is controllable via an app. As is, our product displays noise data alone, but visualizations can easily be made for other data topics. Download the app apk from this repository. 

```
ControlAPP.apk
```
The app sends commands to the physical device, and users can pick data points to visualise​. See the video below for an example. 

https://github.com/CASA0020-group-1/SensorySculpt/assets/127933946/5e9fdb4e-0f51-469d-bb3d-0aa275fe0916




## 🎈 Usage  
Add notes about how to use the system. Video  and leaflet information guide are available here 

## 🚀 Additional Explorations 
The most common method of these sand-based visualization devices is using an x,y plotter. This allows the most flexibility and creativity in pattern creation, and we hope to develop that feature with investment. There are build tutorials for the x,y plotter [here](https://www.thingiverse.com/thing:248009). With this possibility, you can easily explore custom patterns.

## ✍️ Authors
- [@Edita](https://github.com/StrikeEB) - Idea & Initial work
- [@Elinor]() - Idea & Initial work
- [@Ertong](https://github.com/youdianhaoxiao) - Idea & Initial work
- [@Xin](https://github.com/zczqxc5) - Idea & Initial work

## Acknowledgement 
Thank you Simon Gosling for your assistance bending the wood. 


