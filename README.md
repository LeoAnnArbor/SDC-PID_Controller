# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

## Introduction

In this project, we are asked to build a PID controller and tune the hyperparameters such that the car can be driven reliably around the simulator track.

## Discussion
* Describe the effect each of the P, I, D components had in your implementation.

The proportional(P) controller affects the car's behavior most significantly. It helps the car to maintain in the middle of the lane by compensentaing the difference from the lane center, named as the cross-track error (CTE) provided by the simulator. P controller provides correction that is proportianal, hence the name proportianl control, to the cross track error (CTE) via stearing angle. If the car is to the right of the lane, P controller tries to steer it to the left and vice versa. In theory it will reduce the CTE to zero, however affected by vehicle dynamics, the car will cross the center of the lane under P controller alone and cause undesired oscillation (overshoot) of vehicle trajectory. This effect is demonstrated in the video below

[![IMAGE ALT TEXT](http://img.youtube.com/vi/--NLQ9fG4gA/0.jpg)](https://youtu.be/--NLQ9fG4gA "Autonomous car with P control only")

The differential(D) controller compensates the P controller's tendency to overshoot the center line by tuning proportiaonl to the change rate of CTE through the steering angle as well. A properly tuned D parameter will make the car approaching the center line smoothly without overshooting. This effect is demonstrated in the video below. As shown in the video by including the D component, the trajectory of vehicle becomes much smoother and does not overshoot.

[![IMAGE ALT TEXT](http://img.youtube.com/vi/D3crA2dlhDI/0.jpg)](https://youtu.be/D3crA2dlhDI "Autonomous car with PD control")

The integral(I) controller is able to reduce the bias in the CTE from the the center line. This bias can take several forms, such as a steering drifts, uncertainty in measurements, etc. Performance of the car with full PID controller implementated is shown in the following video. In this particular example, since there are many subsequent left and right turns along the track, the bias of vehicle position can be compensated largely by the P and D components during the turning process. Yet, slightly bias due to the remove of I component in the previous video can still be observed particularly on the straight portion of the track uopon carefullly examination.

[![IMAGE ALT TEXT](http://img.youtube.com/vi/73__LHPynQc/0.jpg)](https://youtu.be/73__LHPynQc "Autonomous car with full PID control")

* Describe how the final hyperparameters were chosen.

The hyperparameters used for PID control are tuned manually in this exploration. The steps are as follows:
Step 1, to start the process, I set Kp, Ki, and Kd to 0, disabling all control authority for now. I then gradually increase parameter Kp for P controller, before the car runs with stable and consistent oscillations. For now, I don't worry to much about the oscillation since it will be taken care of by D controller.

Step 2, I then gradually increase Kd until any overshoot observed is fairly minimal. At the same time, some miner modifications are also made to Kp.

Step 3, Lastly, I incrementally crank up Ki until visible bias error is eliminated. The starting number of Ki is chosen to be 0.0001. The final hyperparmeter tuned the above video is Kp = 0.135, Ki = 0.00027, and Kd = 3.0;

## Suggested improvements

In class, we discussed about automate parameter optimization using techniques such as Twiddle. Once we found parameters that were able to get the car around the track reliably, implementing Twiddle one top of the manually tuned coarse parameter value can potentially save time while improving performance for fine tuning the hyperparameters. 

Another improvement can be made on adding a secoond controller for the throttle, to maximize the car's speed around the track. Some modifications shall be made for instance the P controller should be proportional to the magnitude of the CTE instead of CTE as before since whether the car is to the left or to the right side of the track does not make a difference. Likewise, influence of other parameters on both the speed and reliability of the vehicle are also worth exploring.

---

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets)
  * Run either `./install-mac.sh` or `./install-ubuntu.sh`.
  * If you install from source, checkout to commit `e94b6e1`, i.e.
    ```
    git clone https://github.com/uWebSockets/uWebSockets 
    cd uWebSockets
    git checkout e94b6e1
    ```
    Some function signatures have changed in v0.14.x. See [this PR](https://github.com/udacity/CarND-MPC-Project/pull/3) for more details.
* Simulator. You can download these from the [project intro page](https://github.com/udacity/self-driving-car-sim/releases) in the classroom.

There's an experimental patch for windows in this [PR](https://github.com/udacity/CarND-PID-Control-Project/pull/3)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./

## How to write a README
A well written README file can enhance your project and portfolio.  Develop your abilities to create professional README files by completing [this free course](https://www.udacity.com/course/writing-readmes--ud777).

