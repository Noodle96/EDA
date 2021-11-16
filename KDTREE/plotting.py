import numpy as np
import pandas as pd
 
# importing matplotlib.pyplot package from
# python
import matplotlib.pyplot as plt
import matplotlib.pyplot as pltI
 
# Creating an empty figure
# or plot
fig = plt.figure()
 
# Defining the axes as a
# 3D axes so that we can plot 3D
# data into it.
#ax = fig.gca(projection="3d")

#colnames=['X', 'Y', 'Z'] 
#database = pd.read_csv('testX.csv', names=colnames, header=None)
#databaseKNN = pd.read_csv('kdtree_knn.csv', names=colnames, header=None)
#target = pd.read_csv('target.csv', names=colnames, header=None)
#print(databaseKNN)

#one = ax.scatter3D(database['X'], database['Y'], database['Z'],color = 'red')
#two = ax.scatter3D(databaseKNN['X'], databaseKNN['Y'], databaseKNN['Z'],color = 'blue')
#three = ax.scatter3D(target['X'], target['Y'], target['Z'],color = 'green')

# Showing the above plot
#plt.show()


#compare function insert
colnamesInsert = ['N','time']
databaseInsertKdtree = pd.read_csv('fileToTableComparationInsertKdtree.csv',names=colnamesInsert,header=None)
databaseInsertFB = pd.read_csv('fileToTableComparationInsertBruteForce.csv',names=colnamesInsert,header=None)

#pltI.plot(databaseInsertKdtree['N'],databaseInsertKdtree['time'],label="Kdtree")
#pltI.plot(databaseInsertFB['N'],databaseInsertFB['time'],label="Brute Force")
#pltI.xlabel("N")
#pltI.ylabel('time ms')
#pltI.title("Insert function")
#pltI.legend()
#pltI.show()



import matplotlib.pyplot as pltSearch
 
# labels for bars
tick_label = ['KDTREE','BRUTE FORCE']
colNamesSearch =['tipo','time']
# plotting a bar chart
databaseKNN = pd.read_csv('kdtree_time_knn_VS_bruteForce_time_knn.csv',names=colNamesSearch, header = None)
pltSearch.bar(databaseKNN['tipo'], databaseKNN['time'], tick_label = tick_label,
        width = 0.15, color = ['red', 'green'])
 
# naming the x-axis
pltSearch.xlabel('data Struct')
# naming the y-axis
pltSearch.ylabel('Time ms')
# plot title
pltSearch.title('Time 1-knn Kdtree vs Brute Force')
 
# function to show the plot
pltSearch.show()





