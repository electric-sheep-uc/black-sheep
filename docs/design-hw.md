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

**TODO**

## Discussion

**TODO**
