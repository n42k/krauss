
# Krauss
A project that implements the Krauss' car following model in C++.
You can brake the front car by pressing the space key.

![Screenshot](https://github.com/n42k/krauss/raw/master/screenshot.png)

# Dependencies
* SFML

# Output
More than simply displaying a window, the program also outputs 3 CSV files:
* `position.csv` - has the position of each car relative to time
* `velocity.csv` - has the velocity of each car relative to time
* `acceleration.csv` - has the acceleration of each car relative to time

# Graphs
With the default parameters for the model, we can see shockwaves forming when the front car brakes, as can be seen from the following graphs, generated from the files above:

![Position relative to time](https://github.com/n42k/krauss/raw/master/position.png)

![Position relative to time](https://github.com/n42k/krauss/raw/master/velocity.png)

![Acceleration relative to time](https://github.com/n42k/krauss/raw/master/acceleration.png)
Note that in this last graph, V1 is not present, to improve the visualization.

# License
MIT
