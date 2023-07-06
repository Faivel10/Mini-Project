import matplotlib.pyplot as plt

#just for testing!!!!!!

#first set points to test
points = []

# Create a new figure and axis
fig, ax = plt.subplots()

# Plot the points
ax.plot(*zip(*points), 'ro')

# Connect the points based on the condition
for i in range(len(points)):
    for j in range(i + 1, len(points)):
        x1, y1 = points[i]
        x2, y2 = points[j]
        if x1 < x2 and y1 < y2:
            ax.plot([x1, x2], [y1, y2], 'b-')
        if x1 > x2 and y1 > y2:
            ax.plot([x2, x1], [y2, y1], 'b-')


# Set axis labels
ax.set_xlabel('X')
ax.set_ylabel('Y')

# Set the title
ax.set_title('Points with Connections')

# Display the plot
plt.show()
