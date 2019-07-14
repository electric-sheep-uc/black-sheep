# Design (Hardware)

For the platform, we had several requirements:

1. The platform must be low-cost. The reason for this was two-fold, firstly our
team operates on a relatively low-budget and secondly the cost-to-entry into
the RoboCup humanoid league has been gradually increasing (many platforms are
easily more than 10k euros each for a single robot). We believe that it's still
possible for low-cost entries to make a large impact in the league and hope
that this release will add to such efforts.
2. It must be easy (relatively speaking) to design and build. None of our team
are electrical engineers, for a while we didn't have any 3D designers and only
a few with any kind of background in robotics. Using off-the-shelf components
as much as possibly greatly reduces the risk in such an ambitious project.
3. The platform must be open-sourced at the end, regardless of performance in
the competition. If somebody decided to replicate our work then we need to be
able to beat our past selves in order to progress year-on-year. We also hope
that we are able to make some small contribution to the future success of the
leagues (even if this be a lesson in what not to do).

We decided on the following features:

* Raspberry Pi 3B as a main board - it offers just about enough computational
power for simple behaviours, but most importantly it's well understood and
doing low-level hardware communications is relatively simple.
* Large PWM motors for arms - As the arms are barely used in most games and
mostly used for standing after a fall, we decided if anywhere we were to use
cheaper motors, it would be here. PWM motors have a horrible habit of being
twitchy at the best of times, but especially when the PWM signal is noisy. The
cost of these motors is somewhere between a fifth and a tenth of their smart
motor counterparts.
* Smart motors for legs - We did decide that at least some accuracy was
required in the system, especially for walking. The obvious choice was
magnetically encoded smart motors that daisy-chain power and communicate on a
serial bus.
* Standard voltage step-down converters - The final voltage out of the power
PCB was much higher than we wanted for our components, so step-down is
required. We decided not to design/build our own as power system design tends
to be some form of magical art.

## BOM

The following are components used in our build:

* [IMU](https://www.banggood.com/6DOF-MPU-6050-3-Axis-Gyro-With-Accelerometer-Sensor-Module-For-Arduino-p-80862.html?rmmds=myorder&cur_warehouse=CN)
* [Header Connectors](https://www.banggood.com/10X-2AWG-60-Core-30cm-Male-to-Male-Futaba-Plug-Servo-Extension-Wire-Cable-Parallel-Cable-p-1102386.html?rmmds=search&cur_warehouse=CN)
* [Raspberry Pi 3 B](https://www.banggood.com/Raspberry-Pi-3-Model-B-ARM-Cortex-A53-CPU-1_2GHz-64-Bit-Quad-Core-1GB-RAM-10-Times-B-p-1041862.html?rmmds=search&cur_warehouse=CN)
* [T60 Battery Connector](https://www.banggood.com/5Pcs-30cm-Battery-ESC-XT60-Plug-Extension-Wire-Cable-Male-Female-p-1090915.html?rmmds=search&cur_warehouse=CN)
* [DC Barrel Female](https://www.banggood.com/10pcs-5_5-x-2_1mm-DC-Power-Supply-Female-Jack-Socket-p-1062018.html?rmmds=myorder&cur_warehouse=CN)
* [Power Switch](https://www.banggood.com/2Pin-15A-250V-AC20A-125V-AC-Gas-Generator-Kill-Stop-Run-Switch-Fr-Wen-Power-Pro-p-1242672.html?rmmds=search&cur_warehouse=CN)
* [Large PWM Motor](https://www.alibaba.com/product-detail/Feetech-FITEC-FS6535M-30kg-High-Torque_60200752064.html?spm=a2700.7724838.2017115.94.330e9334MVCmgi) x 6
* [Smart Motor](https://www.alibaba.com/product-detail/FEETECH-SM30-360T-M-Serial-s_60638962033.html?spm=a2700.7724838.2017115.1.6a888b05gjSW7X) x 12
* [Fuse Holder](https://www.banggood.com/Waterproof-Car-Auto-10-15-20-30A-Amp-In-Line-Blade-Fuse-Holder-Fuses-p-916113.html?rmmds=detail-left-hotproducts__15&ID=45357&cur_warehouse=CN)
* [Micro USB Cable](https://www.banggood.com/Bakeey-3A-Micro-USB-Braided-Fast-Charging-Cable-28cm-For-Xiaomi-Redmi-Note-4-4x-Samsung-S7-Edge-S6-p-1234852.html?rmmds=search&ID=512288&cur_warehouse=CN)
* [PWM PSU](https://www.banggood.com/8A-24V-TO-12V-Step-down-LED-Driver-Adjustable-Power-Supply-Module-p-927773.html?rmmds=myorder&cur_warehouse=CN) x 2
* [Raspberry Pi Cooling](https://www.banggood.com/CNC-V3-Aluminum-Alloy-Armor-Protective-Case-Dual-Cooling-Fan-Kit-For-Raspberry-Pi-3-Model-B-3BPlus-p-1456092.html?akmClientCountry=NZ&rmmds=search&cur_warehouse=CN)
* [Voltage Monitor](https://www.banggood.com/2-6S-Lipo-Battery-Low-Voltage-Tester-Buzzer-Alarm-For-RC-Model-p-1213452.html?rmmds=myorder&cur_warehouse=CN)
* [DC Fan](https://www.banggood.com/5000rmin-DC-12V-Motorcycle-Radiator-Charger-Cooling-Fan-Humidifier-Electric-Cooler-5x5cm-p-1133447.html?rmmds=search&cur_warehouse=CN) x 2
* [Relays](https://www.banggood.com/5V-2-Channel-Relay-Module-Control-Board-With-Optocoupler-Protection-For-Arduino-p-1142262.html?rmmds=search&cur_warehouse=CN)
* [PWM Motor Controller](https://www.banggood.com/PCA9685-16-Channel-12-bit-PWM-Servo-Motor-Driver-I2C-Module-For-Arduino-Robot-p-1170343.html?rmmds=search&cur_warehouse=CN)
* [Smart Motor Controller](https://www.alibaba.com/product-detail/Multi-function-serial-port-signal-converter_60707270225.html?spm=a2700.7724838.2017121.17.4e7bb5fbbG1VDk)
* [LiPo Battery (T60)](https://www.alibaba.com/product-detail/Factory-price-40C-14-8V-2200mah_60831078917.html?spm=a2700.7724838.2017115.40.78ba3wWY3wWYwf)
* [Push Buttons](https://www.alibaba.com/product-detail/DIY-Kit-1x4-4-Independent-Key_60772024013.html?spm=a2700.7724838.2017115.418.3b0datgHatgHPP)
* [DC Supply (Laptop Adapter)](https://www.banggood.com/96W-Universal-AC-Adapter-Power-Supply-Charger-Cord-For-Laptop-Notebook-p-1131283.html?rmmds=myorder&cur_warehouse=CN)
* [Balanced Charger](https://www.banggood.com/Wholesale-IMAX-B6-Digital-RC-Lipo-NiMH-battery-Balance-Charger-p-46220.html?rmmds=search&cur_warehouse=CN)
* [Camera](https://www.banggood.com/Mini-USB2_0-12MP-1080P-HD-Pro-Webcam-Camerawith-Microphone-Mic-for-PC-p-1122462.html?rmmds=search&cur_warehouse=CN)
* [USB Cable](https://www.banggood.com/30CM-Blue-Male-USB-2_0A-To-Mini-Male-USB-B-Cable-For-Arduino-p-999008.html?rmmds=search&cur_warehouse=CN)
* [Micro SD Card](https://www.banggood.com/Mixza-Year-of-the-Dog-Limited-Edition-U1-32GB-TF-Memory-Card-p-1295486.html?rmmds=myorder&cur_warehouse=CN)
* [PWM Extension Cables](https://www.banggood.com/22AWG-60-Core-20cm-Male-to-Male-JR-Plug-Servo-Extension-Wire-Cable-p-1056558.html?rmmds=search&ID=3416&cur_warehouse=CN)
* [MG995](https://www.banggood.com/4X-MG995-High-Torgue-Mental-Gear-Analog-Servo-p-999629.html?rmmds=search&cur_warehouse=CN)
* [MG995 Horn Mount](https://www.banggood.com/Robot-Biaxial-Servo-Spare-Part-Round-Servo-25T-Mount-Bracket-for-DIY-Robot-p-1068917.html?rmmds=search&cur_warehouse=CN) x 4
* [USB Step Down Converter](https://www.banggood.com/DC-DC-Buck-Module-6-24V-12V24V-to-5V-3A-USB-Step-Down-Power-Supply-Charger-Efficiency-97_5-p-1103973.html?rmmds=search&&cur_warehouse=CN)

And the following optional supporting parts:

* [Ethernet Cables](https://www.banggood.com/Original-Xiaomi-Power-Strip-Fast-5-Charging-Ports-Power-Plug-AU-Standard-Plug-p-1011763.html?rmmds=search&cur_warehouse=CN)
* [Ethernet Switch](https://www.alibaba.com/product-detail/High-Quality-Gigabit-Switch-16-port_60662482838.html?spm=a2700.galleryofferlist.normalList.180.62d325b9S73rcY)
* [Additional Fuses](https://www.banggood.com/Excellway-DC003-160Pcs-Blade-Fuse-Assortment-Auto-Car-Motorcycle-Fuses-35101520253040Amp-p-1436004.html?rmmds=detail-left-hotproducts__1&cur_warehouse=CN)
* [Power Cable Red](https://www.banggood.com/DANIU-10-Meter-Red-Silicone-Wire-Cable-10121416182022AWG-Flexible-Cable-p-1170297.html?rmmds=search&ID=520651&cur_warehouse=CN)
* [Power Cable Black](https://www.banggood.com/DANIU-10-Meter-Black-Silicone-Wire-Cable-10121416182022AWG-Flexible-Cable-p-1170303.html?rmmds=detail-top-buytogether-auto&ID=520651&cur_warehouse=CN)
* [JST Twin Connectors](https://www.banggood.com/10-Pairs-2-Pins-JST-Female-Male-Connector-Plug-Cable-Wire-Line-110mm-Red-p-1268119.html?rmmds=search&cur_warehouse=CN)
* [Black PLA Filament](https://www.amazon.com/HATCHBOX-3D-PLA-1KG3-00-ORN-Filament-Dimensional/dp/B01FKESAMA/)
* [Nuts and Bolts](https://www.banggood.com/Suleve-M3SS2-M3-442Pcs-Stainless-Steel-Allen-Bolt-Nut-Hex-Socket-Cap-Screw-Assortment-Kit-p-1076216.html?rmmds=search&cur_warehouse=CN)
* [Heat Shrink Tubes](https://www.banggood.com/Soloop-328pcs-21-Polyolefin-Halogen-Free-Heat-Shrink-Tube-Sleeving-5-Color-8-Size-p-969574.html?rmmds=search&cur_warehouse=CN)
* [LiPo Safe Bag](https://www.banggood.com/DUPU-Explosion-Proof-Fire-Proof-Bag-For-Li-Po-Battery-p-950215.html?rmmds=search&ID=3147&cur_warehouse=CN)

## Discussion

*For details, please see our technical report paper.*

In general we found the PWM motors (of all types) to be too large for their
power, get too hot and not be accurate enough. The support circuitry for their
required voltages, a dedicated controller and additional code to address them
requires large improvements.

If you are thinking of using this platform, please either wait or contact us
for details about version 2 - which will address many of these short comings.
