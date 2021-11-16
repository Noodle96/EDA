import numpy as np
import pandas as pd
 
# importing matplotlib.pyplot package from
# python
import matplotlib.pyplot as plt
 
# Creating an empty figure
# or plot
fig = plt.figure()
 
# Defining the axes as a
# 3D axes so that we can plot 3D
# data into it.
ax = fig.gca(projection="3d")

colnames=['X', 'Y', 'Z'] 
database = pd.read_csv('testX.csv', names=colnames, header=None)
databaseKNN = pd.read_csv('kdtree_knn.csv', names=colnames, header=None)
target = pd.read_csv('target.csv', names=colnames, header=None)
print(databaseKNN)

one = ax.scatter3D(database['X'], database['Y'], database['Z'],color = 'red')
two = ax.scatter3D(databaseKNN['X'], databaseKNN['Y'], databaseKNN['Z'],color = 'blue')
three = ax.scatter3D(target['X'], target['Y'], target['Z'],color = 'green')

# Showing the above plot
plt.show()