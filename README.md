## SensorySculpt Production Guide 
The SensorySculpt brings technology, mindfulness practices, art, and environmental data visualisation together. Inspired by the aesthetic of traditional Zen garden sandpits, this project seeks to modernise the concept, not only fostering mindfulness and aiding focus restoration but also providing a distinctive platform for real-time interaction with environmental data. Through the transformation of abstract data, such as noise levels and temperature, into tangible and aesthetically pleasing sand art, the Sensory Sculpt invites users to engage with their environment in a profound and meaningful manner.

## 🏁 Getting Started 

### Materials 
- Arduino UNO WIFI  
- LCD display  
- Two servos (360 continuous & non-continuous) 
- [Gravity noise level sensor](https://www.dfrobot.com/product-1663.html)
- HC-05 bluetooth – to communicate with the API and the App

  
- Iron Filings
- Sand 
- Lasercutter + 3mm wood board
- Wood Stain + Sponge
- Wood Glue 

## 🔨 Step 1: Assembling Hardware
Overall, our SensorySculpt device 
1) Monitors sensor data (today just noise levels),
2) subscribes to API topics,
3) reads user commands from the APP and
4) visualises data in real-time through the lens of pre-determined mode thresholds.​
   
### 🔸 Follow the Schematic 
Use the following schematic to set up the servos, screen, and noise sensor. 

<img width="300" alt="servo, sensor, led schematic" src="https://github.com/CASA0020-group-1/SensorySculpt/assets/127933946/42c0abd6-7dde-4c09-9f27-c51c699ba884">

> The noise sensor is pre-calibrated and decibel value is linear with its output voltage. This results in a super simple 'plug-and-play' implementation.

### 🔸 Create your Enclosure
We created our enclosure by bending several boards of plywood and lasercutting the pattern face. Our initial test prototype used cardboard fashioned into a lid, and this worked quite well! If you're using wood, be sure to stain it to give your final product a more refined appearance; we used a walnut tone.

### 🔸 Select your Pattern Creation Materials
We tried multiple iterations of pattern face, sand substrate, and pattern tracer materals before we settled on our current device. Considering consumer reviews of the [sisyphus table](https://sisyphus-industries.com/shop/) prompted us to weigh pattern clarity and noise levels above most other elements.  

#### Materials + Attempts 
- acrylic face

  <img src="https://github.com/CASA0020-group-1/SensorySculpt/assets/127933946/ea5c5818-ab2c-4427-8a51-8bc4adfbdd46" width="200">
  
- wood face

  <img src="https://github.com/CASA0020-group-1/SensorySculpt/assets/127933946/66e0a0b0-78f4-4e38-b1db-681e923f5b9e" width="200">
  
- [coin magnet](https://www.amazon.co.uk/dp/B09W8R43Q8?ref=ppx_pop_mob_ap_share&th=1)
- [ball magnet](https://www.amazon.co.uk/dp/B081SPMJ97?ref=ppx_pop_mob_ap_share&th=1)
- [iron filings](https://www.amazon.co.uk/dp/B007JTMVD4?starsLeft=1&ref_=cm_sw_r_cso_wa_apin_dp_RMVPF1YZPGKMDCGC78PR&th=1)
- [fine silica sand](https://amzn.eu/d/1xmJNqX)

<img width="600" alt="attempts table" src="https://github.com/CASA0020-group-1/SensorySculpt/assets/127933946/56ac24cd-8226-40f5-acb5-1017824675b1">

We ultimately proceeded with the iron filings + wood face – attempt 4. 

> [!TIP]
> While it is tempting (and satisfying) to fill the entire pattern face with sand, this results in markedly worse pattern clarity across attempts and is a little messy to clean up. An appropriate amount of sand will allow you to still see the pattern face through the sand. 

<img width="200" alt="quantity of sand" src="https://github.com/CASA0020-group-1/SensorySculpt/assets/127933946/ca0de091-0901-4b22-9854-cb1ccbd58d38">


## 💫 Step 2: Flash the Board with the Rotation Software
The pattern creation software is available in `two_servo_rotation.ino`. This code can create three patterns, each corresponding with different ambient noise levels. This presents as a visual metaphor for the influence of noise levels on focus and productivity, where louder noise levels correspond with a more dynamic pattern.

### Pattern / Visual Feedback Guide  
<img width="483" alt="image" src="https://github.com/CASA0020-group-1/SensorySculpt/assets/127933946/5c8d787a-d9c2-4861-8a42-b68cbcb4b330">


## 🪄 Step 3: Download App   
The full potential of our product can be realized when you connect it to an API. This allows you to swich between different streams of environmental data that is controllable via an app. As is, our product displays noise data alone, but visualizations can easily be made for other data topics. Download the app apk from `ControlAPP.apk` in this repository.

The app sends commands to the physical device, and users can pick data points to visualise​. See the video below for an example. 

https://github.com/CASA0020-group-1/SensorySculpt/assets/127933946/5e9fdb4e-0f51-469d-bb3d-0aa275fe0916


## 🎈 Usage  
Notes about how to use the system. Our product overview video, leaflet information guide, are available [here](https://drive.google.com/drive/folders/1PVUKZVuuEFIjHochCqNxEP5Qj6Y1M1UK) 

## 🚀 Additional Explorations 
### 🔹 Pattern Creation
The most common method of these sand-based visualization devices is using an x,y plotter. This allows the most flexibility and creativity in pattern creation, and we hope to develop that feature with investment. There are build tutorials for the x,y plotter [here](https://www.thingiverse.com/thing:248009). With this possibility, you can easily explore custom patterns.

### 🔹 Sand Colours 
Using sand with various glittery mica powders can create a rather stunning visual effect, as seen in the Oasis device [here](https://youtube.com/shorts/F3zMZAem-_E?feature=shared).

## ✍️ Team Members
- [@Edita](https://github.com/StrikeEB) 
- [@Elinor](https://github.com/elinor-oren) 
- [@Ertong](https://github.com/youdianhaoxiao) 
- [@Xin](https://github.com/zczqxc5) 

## Acknowledgement 
Thank you Simon Gosling for your assistance in creating our enclosure.  


