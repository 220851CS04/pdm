import math
def calculate_trajectory(radius, frequency, point_angle):
angular_velocity = 2 * math.pi * frequency
x = radius * math.cos(angular_velocity * point_angle)
y = radius * math.sin(angular_velocity * point_angle)
return (x, y)
radius = 10
frequency = 5
point_angle = 1.55 
trajectory = calculate_trajectory(radius, frequency, point_angle)
print("Trajectory:", trajectory)
