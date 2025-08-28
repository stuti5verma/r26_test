# R26_test

<p align="center">
  <img src="https://github.com/teamrudra/r26_test/blob/main/misc/rover.webp" width="480" height="480"/>

#### Some Instructions
1. You may use any online resources, datasheets, or documentation needed, but be mindful of your time and stay focused on the task.
2. The duration of the test is 90 mins from 5:15pm to 6:45 pm.
3. There will be a MCQ test conducted [here](https://rudra26test.vercel.app/)
4. There are 4 tasks in the tests. Complete all of them.
5. In case you are not able to complete all the tasks, do upload whatever you are able to.
6. In the `README.md` of your repository include your thought process, places where you got stuck, where you used the help of AI, google or other online resources.
7. Even if you are not able to solve anything, do fill the readme and what your thought process would have been.
8. Carefully read the instructions to implement the required functionality.
9. Install [mingw(c compiler)](https://www.mingw-w64.org/downloads/#w64devkit) and [git](https://git-scm.com/downloads) if you haven't already done it.
10. After finishing your test, provide the link to your forked repository in the google form provided at the end.

### Aim/Objective: To decode GPS data of start and goal position, and create a path planning algorithm which computes an optimal path over a predefined gridmap

## Description
You are implementing code to decode GPS position data, received from a u-blox GNSS module on-board a rover (check out the [datasheet](https://drive.google.com/file/d/1rOcPxpP-3JE8l39kBMiQV6KKe8B6zlDf/view)). You are given the current/start position of the rover and the goal position where the rover has to reach, your goal is to develop a path planning algorithm to traverse over a pre-defined gridmap and generate necessary odometry commands (total time & angle traversed) to guide the rover along the generated path. 

### Task 0: Fork the provided repository and ensure it is set to PUBLIC so we can access and assess your work.
### Task 1: Decoding gps data (in ubx format) from u-blox reciever.
Working with UBX format and extracted relevant navigation data for use in the planner.
### Task 2: Develop a path planning algorithm to traverse over a gridmap.
Implemented a grid-based path planner that computes an optimal route from start to goal.
### Task 3: Generate odometry commands to guide the rover along the generated path.
Converted the path into motion commands (direction and timing) based on wheel parameters.
### Task 4: Compile and run the code.
Verified the workflow on sample inputs and ensured the project compiles successfully with g++.

#### Code
1. [src/main.cpp](src/main.cpp): Code for running the test.
2. [src/ublox_reader.cpp](src/ublox_reader.cpp): Recitfy errors in this code to compute correct lat & lon coordinates.
3. [src/planning.cpp](src/planning.cpp): Complete the defined `Planner::pathplanning` function 
4. [src/odometry.cpp](src/odometry.cpp): Complete the defined `Odometry::computeCommands` function 

#### How to Compile & Check your code
(make sure you are in the root directory)   
1. Compile your code by running: `make build`
2. To check if your code is implemented correctly run: `make check`
   
If you are able to compile your code successfully you should see something like this on your screen:

```
*** Success: ***
--------------------------------------------
```

4. If your make check was unsuccesfull, you can clean your attempt by running `make clean`, review your implementation and repeat the previous steps.

# Solution
## Understanding
Describe what you understood about the problem.
The task is to make a rover navigate from a start GPS position to a goal GPS position using data from a u-blox GNSS module.
The workflow involves three main parts:
Decoding UBX GPS data: Parsing the binary .ubx file to extract latitude and longitude in usable floating-point values.
Path Planning: Mapping start and goal positions onto a predefined grid and finding an optimal route (using A* algorithm) while avoiding obstacles.
Odometry Commands: Translating the planned path into motion commands (time and angle) that the rover can follow, considering its wheel parameters.
Finally, the code must be compiled and tested to ensure correctness.

## Thought Process
After understanding the problem, describe how you decided to proceed towards solving the question.
My approach was to divide the problem into modular tasks:
GPS decoding (Task 1):
Study the UBX protocol (NAV-POSLLH message structure).
Extract fields like latitude, longitude, and convert them to degrees.
Ensure checksum validation so that only correct UBX messages are used.

Path Planning (Task 2):
Represent the map as a 2D grid.
Convert lat/long coordinates into grid indices (row, col).
Use the A* algorithm to search for the shortest path from start to goal.
Store the path as a sequence of grid cells.

Odometry (Task 3):
Calculate the distance and heading change between consecutive path points.
Use robot parameters (wheel radius, base length, speed) to compute total traversal time and rotation angle.
Output odometry commands (time, angle).

Testing (Task 4):
Compile the project with make build.
Run with test UBX inputs to verify correct GPS parsing.
Use make check to validate correctness with the provided test framework.
This step-wise approach ensured that each component could be debugged independently before integration.

## Implementation
How did you decide to implement your solution.
Mention the details, such as the path planning & odometry how you tested it.

GPS Decoder (ublox_reader.cpp):
Implemented readUbloxFile to open the UBX file, validate UBX sync bytes, extract the NAV-POSLLH payload, and compute latitude/longitude in decimal degrees. This provided the rover’s start and goal positions.

Planner (planning.cpp):
Implemented Planner::pathplanning using the A* algorithm. The function converts GPS coordinates into grid cells and then searches for the optimal path using cost functions (g, h, f). The resulting path is returned as a list of coordinates.

Odometry (odometry.cpp):
Implemented Odometry::computeCommands. For each step in the path, compute displacement and heading. Then, calculate the required motion parameters (total time, final angle). These are written to an output file and printed.

Integration & Testing (main.cpp):
Orchestrated the workflow: read UBX file → run path planner → compute odometry → save results.
Verified correctness by compiling with make build and checking results with make check. Also tested using a custom UBX file to confirm proper GPS parsing and path generation.

# Google Form
[Link to Repo Submission](https://docs.google.com/forms/d/e/1FAIpQLSdlVJ2LzP8wUOATRD804zDVL611rwwGMO1y_ecYu5aoV5YQfw/viewform)


<p align="center">
  <img src="https://github.com/teamrudra/r25-test/blob/main/datasheets/feynman-simple.jpg" width="600" height="600"/>
</p>
     
