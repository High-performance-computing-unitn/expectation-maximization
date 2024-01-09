from matplotlib import pyplot as plt
import math
from statistics import mean

x_values = [1, 2, 4, 8, 16, 32, 64]
x_values_HD = [2, 4, 8, 16, 32, 64]

#Parallel 1 small dataset data
parallel_1_S_pack = [248, 124, 62, 34, 18, 8, 8] 
parallel_1_S_pack_excl = [199, 108, 50, 35, 16, 10, 5]
parallel_1_S_scatter = [600, 464, 311, 272, 174, 39, 28] 
parallel_1_S_scatter_excl = [274, 127, 61, 29, 15, 11, 5] 

#Parallel 1 medium dataset data
parallel_1_M_pack = [541, 251, 126, 64, 31, 19, 10] 
parallel_1_M_pack_excl = [540, 249, 126, 75, 37, 24, 11] 
parallel_1_M_scatter = [513, 365, 306, 178, 81, 61, 27] 
parallel_1_M_scatter_excl = [627, 290, 206, 139, 83, 49, 37] 

#Parallel 1 big dataset data
parallel_1_B_pack = [1086, 455, 250, 140, 68, 33, 21] 
parallel_1_B_pack_excl = [1024, 649, 324, 176, 72, 40, 26]
parallel_1_B_scatter = [1064, 521, 302, 179, 75, 64, 68] 
parallel_1_B_scatter_excl = [1025, 691, 436, 225, 164, 61, 50] 

#Parallel 1 small dataset speedup
parallel_1_S_pack_speedup = [parallel_1_S_pack[0] / element for element in parallel_1_S_pack]
parallel_1_S_pack_excl_speedup = [parallel_1_S_pack_excl[0] / element for element in parallel_1_S_pack_excl]
parallel_1_S_scatter_speedup = [parallel_1_S_scatter[0] / element for element in parallel_1_S_scatter]
parallel_1_S_scatter_excl_speedup = [parallel_1_S_scatter_excl[0] / element for element in parallel_1_S_scatter_excl]

#Parallel 1 medium dataset speedup
parallel_1_M_pack_speedup = [parallel_1_M_pack[0] / element for element in parallel_1_M_pack]
parallel_1_M_pack_excl_speedup = [parallel_1_M_pack_excl[0] / element for element in parallel_1_M_pack_excl]
parallel_1_M_scatter_speedup = [parallel_1_M_scatter[0] / element for element in parallel_1_M_scatter]
parallel_1_M_scatter_excl_speedup = [parallel_1_M_scatter_excl[0] / element for element in parallel_1_M_scatter_excl]

#Parallel 1 big dataset speedup
parallel_1_B_pack_speedup = [parallel_1_B_pack[0] / element for element in parallel_1_B_pack]
parallel_1_B_pack_excl_speedup = [parallel_1_B_pack_excl[0] / element for element in parallel_1_B_pack_excl]
parallel_1_B_scatter_speedup = [parallel_1_B_scatter[0] / element for element in parallel_1_B_scatter]
parallel_1_B_scatter_excl_speedup = [parallel_1_B_scatter_excl[0] / element for element in parallel_1_B_scatter_excl]

#Parallel 1 small dataset efficiency
parallel_1_S_pack_efficiency = [parallel_1_S_pack_speedup[i] / x_values[i] for i in range(len(parallel_1_S_pack_speedup))]
parallel_1_S_pack_excl_efficiency = [parallel_1_S_pack_excl_speedup[i] / x_values[i] for i in range(len(parallel_1_S_pack_excl_speedup))]
parallel_1_S_scatter_efficiency = [parallel_1_S_scatter_speedup[i] / x_values[i] for i in range(len(parallel_1_S_scatter_speedup))]
parallel_1_S_scatter_excl_efficiency = [parallel_1_S_scatter_excl_speedup[i] / x_values[i] for i in range(len(parallel_1_S_scatter_excl_speedup))]

#Parallel 1 medium dataset efficiency
parallel_1_M_pack_efficiency = [parallel_1_M_pack_speedup[i] / x_values[i] for i in range(len(parallel_1_M_pack_speedup))]
parallel_1_M_pack_excl_efficiency = [parallel_1_M_pack_excl_speedup[i] / x_values[i] for i in range(len(parallel_1_M_pack_excl_speedup))]
parallel_1_M_scatter_efficiency = [parallel_1_M_scatter_speedup[i] / x_values[i] for i in range(len(parallel_1_M_scatter_speedup))]
parallel_1_M_scatter_excl_efficiency = [parallel_1_M_scatter_excl_speedup[i] / x_values[i] for i in range(len(parallel_1_M_scatter_excl_speedup))]

#Parallel 1 big dataset efficiency
parallel_1_B_pack_efficiency = [parallel_1_B_pack_speedup[i] / x_values[i] for i in range(len(parallel_1_B_pack_speedup))]
parallel_1_B_pack_excl_efficiency = [parallel_1_B_pack_excl_speedup[i] / x_values[i] for i in range(len(parallel_1_B_pack_excl_speedup))]
parallel_1_B_scatter_efficiency = [parallel_1_B_scatter_speedup[i] / x_values[i] for i in range(len(parallel_1_B_scatter_speedup))]
parallel_1_B_scatter_excl_efficiency = [parallel_1_B_scatter_excl_speedup[i] / x_values[i] for i in range(len(parallel_1_B_scatter_excl_speedup))]


print("PARALLEL 1 DATA")

print("SMALL DATASET")

print("packed")
print(parallel_1_S_pack)
print(parallel_1_S_pack_speedup)
print(parallel_1_S_pack_efficiency)

print("packed exclusive")
print(parallel_1_S_pack_excl)
print(parallel_1_S_pack_excl_speedup)
print(parallel_1_S_pack_excl_efficiency)

print("scattered")
print(parallel_1_S_scatter)
print(parallel_1_S_scatter_speedup)
print(parallel_1_S_scatter_efficiency)

print("scattered exclusive")
print(parallel_1_S_scatter_excl)
print(parallel_1_S_scatter_excl_speedup)
print(parallel_1_S_scatter_excl_efficiency)

print("MEDIUM DATASET")

print("packed")
print(parallel_1_M_pack)
print(parallel_1_M_pack_speedup)
print(parallel_1_M_pack_efficiency)

print("packed exclusive")
print(parallel_1_M_pack_excl)
print(parallel_1_M_pack_excl_speedup)
print(parallel_1_M_pack_excl_efficiency)

print("scattered")
print(parallel_1_M_scatter)
print(parallel_1_M_scatter_speedup)
print(parallel_1_M_scatter_efficiency)

print("scattered exclusive")
print(parallel_1_M_scatter_excl)
print(parallel_1_M_scatter_excl_speedup)
print(parallel_1_M_scatter_excl_efficiency)

print("BIG DATASET")

print("packed")
print(parallel_1_B_pack)
print(parallel_1_B_pack_speedup)
print(parallel_1_B_pack_efficiency)

print("packed exclusive")
print(parallel_1_B_pack_excl)
print(parallel_1_B_pack_excl_speedup)
print(parallel_1_B_pack_excl_efficiency)

print("scattered")
print(parallel_1_B_scatter)
print(parallel_1_B_scatter_speedup)
print(parallel_1_B_scatter_efficiency)

print("scattered exclusive")
print(parallel_1_B_scatter_excl)
print(parallel_1_B_scatter_excl_speedup)
print(parallel_1_B_scatter_excl_efficiency)

#Parallel 2 small dataset data
parallel_2_S_pack = [527, 373, 124, 55, 51, 29, 44] 
parallel_2_S_pack_excl = [583, 364, 132, 74, 46, 26, 49]
parallel_2_S_scatter = [415, 173, 137, 86, 46, 29, 17]
parallel_2_S_scatter_excl = [491, 298, 184, 55, 36, 28, 42]

#Parallel 2 medium dataset data
parallel_2_M_pack = [975, 542, 297, 163, 111, 67, 86]
parallel_2_M_pack_excl = [922, 531, 227, 101, 74, 69, 84]
parallel_2_M_scatter = [906, 527, 255, 211, 117, 53, 65]
parallel_2_M_scatter_excl = [898, 520, 234, 190, 112, 57, 62]

#Parallel 2 big dataset data
parallel_2_B_pack = [2203, 1127, 541, 373, 186, 106, 195] 
parallel_2_B_pack_excl = [2002, 1088, 562, 310, 202, 113, 206] 
parallel_2_B_scatter = [1912, 906, 497, 291, 229, 116, 83]
parallel_2_B_scatter_excl = [1890, 979, 540, 312, 355, 221, 147]

#Parallel 2 small dataset speedup
parallel_2_S_pack_speedup = [parallel_2_S_pack[0] / element for element in parallel_2_S_pack]
parallel_2_S_pack_excl_speedup = [parallel_2_S_pack_excl[0] / element for element in parallel_2_S_pack_excl]
parallel_2_S_scatter_speedup = [parallel_2_S_scatter[0] / element for element in parallel_2_S_scatter]
parallel_2_S_scatter_excl_speedup = [parallel_2_S_scatter_excl[0] / element for element in parallel_2_S_scatter_excl]

#Parallel 2 medium dataset speedup
parallel_2_M_pack_speedup = [parallel_2_M_pack[0] / element for element in parallel_2_M_pack]
parallel_2_M_pack_excl_speedup = [parallel_2_M_pack_excl[0] / element for element in parallel_2_M_pack_excl]
parallel_2_M_scatter_speedup = [parallel_2_M_scatter[0] / element for element in parallel_2_M_scatter]
parallel_2_M_scatter_excl_speedup = [parallel_2_M_scatter_excl[0] / element for element in parallel_2_M_scatter_excl]

#Parallel 2 big dataset speedup
parallel_2_B_pack_speedup = [parallel_2_B_pack[0] / element for element in parallel_2_B_pack]
parallel_2_B_pack_excl_speedup = [parallel_2_B_pack_excl[0] / element for element in parallel_2_B_pack_excl]
parallel_2_B_scatter_speedup = [parallel_2_B_scatter[0] / element for element in parallel_2_B_scatter]
parallel_2_B_scatter_excl_speedup = [parallel_2_B_scatter_excl[0] / element for element in parallel_2_B_scatter_excl]

#Parallel 2 small dataset efficiency
parallel_2_S_pack_efficiency = [parallel_2_S_pack_speedup[i] / x_values[i] for i in range(len(parallel_2_S_pack_speedup))]
parallel_2_S_pack_excl_efficiency = [parallel_2_S_pack_excl_speedup[i] / x_values[i] for i in range(len(parallel_2_S_pack_excl_speedup))]
parallel_2_S_scatter_efficiency = [parallel_2_S_scatter_speedup[i] / x_values[i] for i in range(len(parallel_2_S_scatter_speedup))]
parallel_2_S_scatter_excl_efficiency = [parallel_2_S_scatter_excl_speedup[i] / x_values[i] for i in range(len(parallel_2_S_scatter_excl_speedup))]

#Parallel 2 medium dataset efficiency
parallel_2_M_pack_efficiency = [parallel_2_M_pack_speedup[i] / x_values[i] for i in range(len(parallel_2_M_pack_speedup))]
parallel_2_M_pack_excl_efficiency = [parallel_2_M_pack_excl_speedup[i] / x_values[i] for i in range(len(parallel_2_M_pack_excl_speedup))]
parallel_2_M_scatter_efficiency = [parallel_2_M_scatter_speedup[i] / x_values[i] for i in range(len(parallel_2_M_scatter_speedup))]
parallel_2_M_scatter_excl_efficiency = [parallel_2_M_scatter_excl_speedup[i] / x_values[i] for i in range(len(parallel_2_M_scatter_excl_speedup))]

#Parallel 2 big dataset efficiency
parallel_2_B_pack_efficiency = [parallel_2_B_pack_speedup[i] / x_values[i] for i in range(len(parallel_2_B_pack_speedup))]
parallel_2_B_pack_excl_efficiency = [parallel_2_B_pack_excl_speedup[i] / x_values[i] for i in range(len(parallel_2_B_pack_excl_speedup))]
parallel_2_B_scatter_efficiency = [parallel_2_B_scatter_speedup[i] / x_values[i] for i in range(len(parallel_2_B_scatter_speedup))]
parallel_2_B_scatter_excl_efficiency = [parallel_2_B_scatter_excl_speedup[i] / x_values[i] for i in range(len(parallel_2_B_scatter_excl_speedup))]

print("PARALLEL 2 DATA")

print("SMALL DATASET")

print("packed")
print(parallel_2_S_pack)
print(parallel_2_S_pack_speedup)
print(parallel_2_S_pack_efficiency)

print("packed exclusive")
print(parallel_2_S_pack_excl)
print(parallel_2_S_pack_excl_speedup)
print(parallel_2_S_pack_excl_efficiency)

print("scattered")
print(parallel_2_S_scatter)
print(parallel_2_S_scatter_speedup)
print(parallel_2_S_scatter_efficiency)

print("scattered exclusive")
print(parallel_2_S_scatter_excl)
print(parallel_2_S_scatter_excl_speedup)
print(parallel_2_S_scatter_excl_efficiency)

print("MEDIUM DATASET")

print("packed")
print(parallel_2_M_pack)
print(parallel_2_M_pack_speedup)
print(parallel_2_M_pack_efficiency)

print("packed exclusive")
print(parallel_2_M_pack_excl)
print(parallel_2_M_pack_excl_speedup)
print(parallel_2_M_pack_excl_efficiency)

print("scattered")
print(parallel_2_M_scatter)
print(parallel_2_M_scatter_speedup)
print(parallel_2_M_scatter_efficiency)

print("scattered exclusive")
print(parallel_2_M_scatter_excl)
print(parallel_2_M_scatter_excl_speedup)
print(parallel_2_M_scatter_excl_efficiency)

print("BIG DATASET")

print("packed")
print(parallel_2_B_pack)
print(parallel_2_B_pack_speedup)
print(parallel_2_B_pack_efficiency)

print("packed exclusive")
print(parallel_2_B_pack_excl)
print(parallel_2_B_pack_excl_speedup)
print(parallel_2_B_pack_excl_efficiency)

print("scattered")
print(parallel_2_B_scatter)
print(parallel_2_B_scatter_speedup)
print(parallel_2_B_scatter_efficiency)

print("scattered exclusive")
print(parallel_2_B_scatter_excl)
print(parallel_2_B_scatter_excl_speedup)
print(parallel_2_B_scatter_excl_efficiency)

#Parallel 1 small dataset data log
parallel_1_S_pack_l = [math.log(x) for x in parallel_1_S_pack]
parallel_1_S_pack_excl_l = [math.log(x) for x in parallel_1_S_pack_excl]
parallel_1_S_scatter_l = [math.log(x) for x in parallel_1_S_scatter]
parallel_1_S_scatter_excl_l = [math.log(x) for x in parallel_1_S_scatter_excl]

#Parallel 1 medium dataset data log
parallel_1_M_pack_l = [math.log(x) for x in parallel_1_M_pack]
parallel_1_M_pack_excl_l = [math.log(x) for x in parallel_1_M_pack_excl]
parallel_1_M_scatter_l = [math.log(x) for x in parallel_1_M_scatter]
parallel_1_M_scatter_excl_l = [math.log(x) for x in parallel_1_M_scatter_excl]

#Parallel 1 big dataset data log
parallel_1_B_pack_l = [math.log(x) for x in parallel_1_B_pack]
parallel_1_B_pack_excl_l = [math.log(x) for x in parallel_1_B_pack_excl]
parallel_1_B_scatter_l = [math.log(x) for x in parallel_1_B_scatter]
parallel_1_B_scatter_excl_l = [math.log(x) for x in parallel_1_B_scatter_excl]


#Parallel 2 small dataset data log
parallel_2_S_pack_l = [math.log(x) for x in parallel_2_S_pack]
parallel_2_S_pack_excl_l = [math.log(x) for x in parallel_2_S_pack_excl]
parallel_2_S_scatter_l = [math.log(x) for x in parallel_2_S_scatter]
parallel_2_S_scatter_excl_l = [math.log(x) for x in parallel_2_S_scatter_excl]

#Parallel 2 medium dataset data log
parallel_2_M_pack_l = [math.log(x) for x in parallel_2_M_pack]
parallel_2_M_pack_excl_l = [math.log(x) for x in parallel_2_M_pack_excl]
parallel_2_M_scatter_l = [math.log(x) for x in parallel_2_M_scatter]
parallel_2_M_scatter_excl_l = [math.log(x) for x in parallel_2_M_scatter_excl]

#Parallel 2 big dataset data log
parallel_2_B_pack_l = [math.log(x) for x in parallel_2_B_pack]
parallel_2_B_pack_excl_l = [math.log(x) for x in parallel_2_B_pack_excl]
parallel_2_B_scatter_l = [math.log(x) for x in parallel_2_B_scatter]
parallel_2_B_scatter_excl_l = [math.log(x) for x in parallel_2_B_scatter_excl]

#Parallel 1 high dim dataset data
parallel_1_6D = [304, 166, 83, 42, 20, 19]
parallel_1_8D = [4347, 2032, 1476, 705, 415, 114]

#Parallel 1 high dim dataset data log
parallel_1_6D_l = [math.log(x) for x in parallel_1_6D]
parallel_1_8D_l = [math.log(x) for x in parallel_1_8D]

#Parallel 2 high dim dataset data
parallel_2_6D = [17, 15, 12, 7, 4, 8]
parallel_2_8D = [4.6, 4.4, 2.3, 2.4, 0.7, 1]

#Parallel 2 high dim dataset data log
parallel_2_6D_l = [math.log(x) for x in parallel_2_6D]
parallel_2_8D_l = [math.log(x) for x in parallel_2_8D]


#Parallel 1 small dataset data
parallel_1_S_pack_file = [0.478, 0.266, 0.285, 0.316, 0.380, 0.461, 0.523] 
parallel_1_S_pack_excl_file = [0.216, 0.215, 0.217, 0.226, 0.224, 0.253, 0.277]
parallel_1_S_scatter_file = [0.813, 0.315, 0.266, 0.48, 0.298, 0.69, 0.263] 
parallel_1_S_scatter_excl_file = [0.426, 0.261, 0.259, 0.268, 0.273, 0.275, 0.298] 

parallel_1_S_file_mean = [
    mean(values)
    for values in zip(
        parallel_1_S_pack_file,
        parallel_1_S_pack_excl_file,
        parallel_1_S_scatter_file,
        parallel_1_S_scatter_excl_file
    )
]

#Parallel 1 medium dataset data
parallel_1_M_pack_file = [0.847, 0.534, 0.529, 0.525, 0.556, 0.569, 0.624] 
parallel_1_M_pack_excl_file = [0.524, 0.521, 0.522, 0.533, 0.566, 0.575, 0.622] 
parallel_1_M_scatter_file = [0.904, 1.136, 0.681, 0.648, 0.672, 0.683, 0.716] 
parallel_1_M_scatter_excl_file = [0.99, 0.641, 0.953, 0.536, 0.53, 0.549, 0.568] 

parallel_1_M_file_mean = [
    mean(values)
    for values in zip(
        parallel_1_M_pack_file,
        parallel_1_M_pack_excl_file,
        parallel_1_M_scatter_file,
        parallel_1_M_scatter_excl_file
    )
]

#Parallel 1 big dataset data
parallel_1_B_pack_file = [1.613, 1.068, 1.06, 1.061, 1.142, 1.152, 1.405] 
parallel_1_B_pack_excl_file = [1.063, 1.059, 1.075, 1.071, 1.121, 1.157, 1.461]
parallel_1_B_scatter_file = [1.795, 1.099, 1.950, 1.368, 1.415, 1.613, 2.595] 
parallel_1_B_scatter_excl_file = [1.772, 1.288, 1.286, 1.291, 1.313, 1.422, 1.837] 

parallel_1_B_file_mean = [
    mean(values)
    for values in zip(
        parallel_1_B_pack_file,
        parallel_1_B_pack_excl_file,
        parallel_1_B_scatter_file,
        parallel_1_B_scatter_excl_file
    )
]

    
#Parallel 2 small dataset data
parallel_2_S_pack_file = [0.392, 0.12, 0.072, 0.05, 0.067, 0.11, 0.212] 
parallel_2_S_pack_excl_file = [0.218, 0.117, 0.068, 0.049, 0.067, 0.109, 0.215]
parallel_2_S_scatter_file = [0.436, 0.127, 0.068, 0.043, 0.031, 0.045, 0.086]
parallel_2_S_scatter_excl_file = [0.277, 0.370, 0.291, 0.065, 0.084, 0.145, 0.28]

parallel_2_S_file_mean = [
    mean(values)
    for values in zip(
        parallel_2_S_pack_file,
        parallel_2_S_pack_excl_file,
        parallel_2_S_scatter_file,
        parallel_2_S_scatter_excl_file
    )
]

#Parallel 2 medium dataset data
parallel_2_M_pack_file = [0.859, 0.286, 0.174, 0.103, 0.109, 0.168, 0.329]
parallel_2_M_pack_excl_file = [0.529, 0.301, 0.494, 0.170, 0.218, 0.383, 0.755]
parallel_2_M_scatter_file = [1.048, 0.313, 0.164, 0.113, 0.074, 0.591, 0.352]
parallel_2_M_scatter_excl_file = [0.890, 0.872, 0.680, 0.123, 0.302, 0.089, 0.597]

parallel_2_M_file_mean = [
    mean(values)
    for values in zip(
        parallel_2_M_pack_file,
        parallel_2_M_pack_excl_file,
        parallel_2_M_scatter_file,
        parallel_2_M_scatter_excl_file
    )
]

#Parallel 2 big dataset data
parallel_2_B_pack_file = [1.076, 0.569, 0.332, 0.246, 0.315, 0.539, 1.042] 
parallel_2_B_pack_excl_file = [1.663, 0.575, 0.349, 0.237, 0.319, 0.557, 1.082] 
parallel_2_B_scatter_file = [1.533, 0.624, 0.351, 0.213, 0.181, 0.291, 0.554]
parallel_2_B_scatter_excl_file = [1.280, 0.681, 0.377, 0.253, 0.169, 0.120, 0.347]

parallel_2_B_file_mean = [
    mean(values)
    for values in zip(
        parallel_2_B_pack_file,
        parallel_2_B_pack_excl_file,
        parallel_2_B_scatter_file,
        parallel_2_B_scatter_excl_file
    )
]
 
#############
# FILE PLOT #
#############

# plt.rcParams["figure.figsize"] = [8, 6]
# plt.rcParams["figure.autolayout"] = True

# fig, axs = plt.subplots(1, 1)

plt.plot(x_values, parallel_1_S_file_mean, label = "P1 small dataset mean", color = 'blue', linewidth = 0.8)
plt.plot(x_values, parallel_1_M_file_mean, label = "P1 medium dataset mean", color = 'purple', linewidth = 0.8)
plt.plot(x_values, parallel_1_B_file_mean, label = "P1 big dataset mean", color = 'cyan', linewidth = 0.8)

plt.plot(x_values, parallel_2_S_file_mean, label = "P2 small dataset mean", color = 'red', linewidth = 0.8)
plt.plot(x_values, parallel_2_M_file_mean, label = "P2 medium dataset mean", color = 'brown', linewidth = 0.8)
plt.plot(x_values, parallel_2_B_file_mean, label = "P2 big dataset mean", color = 'green', linewidth = 0.8)

plt.xlabel('cores') 
plt.ylabel('seconds') 

plt.legend()

plt.title('Means of file reading time for different configurations')
plt.show() 


########################
# TIME PLOT PARALLEL 1 #
########################

plt.rcParams["figure.figsize"] = [12, 8]
plt.rcParams["figure.autolayout"] = True

fig, axs = plt.subplots(2, 2)

axs[0,0].plot(x_values, parallel_1_S_pack_l, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[0,0].plot(x_values, parallel_1_M_pack_l, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[0,0].plot(x_values, parallel_1_B_pack_l, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

axs[0,0].set_xlabel('cores') 
axs[0,0].set_ylabel('log(seconds)') 

axs[0,0].set_title('Packed') 
axs[0,0].legend()

axs[0,1].plot(x_values, parallel_1_S_pack_excl_l, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[0,1].plot(x_values, parallel_1_M_pack_excl_l, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[0,1].plot(x_values, parallel_1_B_pack_excl_l, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

axs[0,1].set_xlabel('cores') 
axs[0,1].set_ylabel('log(seconds)') 

axs[0,1].set_title('Packed exclusive') 
axs[0,1].legend()

axs[1,0].plot(x_values, parallel_1_S_scatter_l, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[1,0].plot(x_values, parallel_1_M_scatter_l, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[1,0].plot(x_values, parallel_1_B_scatter_l, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

axs[1,0].set_xlabel('cores') 
axs[1,0].set_ylabel('log(seconds)') 

axs[1,0].set_title('Scattered') 
axs[1,0].legend()

axs[1,1].plot(x_values, parallel_1_S_scatter_excl_l, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[1,1].plot(x_values, parallel_1_M_scatter_excl_l, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[1,1].plot(x_values, parallel_1_B_scatter_excl_l, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

axs[1,1].set_xlabel('cores') 
axs[1,1].set_ylabel('log(seconds)') 

axs[1,1].set_title('Scattered exclusive') 
axs[1,1].legend()

fig.suptitle('Parallel 1st implementation execution time over different configurations')
plt.show() 

########################
# TIME PLOT PARALLEL 2 #
########################

plt.rcParams["figure.figsize"] = [12, 8]
plt.rcParams["figure.autolayout"] = True

fig, axs = plt.subplots(2, 2)

axs[0,0].plot(x_values, parallel_2_S_pack_l, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[0,0].plot(x_values, parallel_2_M_pack_l, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[0,0].plot(x_values, parallel_2_B_pack_l, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

axs[0,0].set_xlabel('cores') 
axs[0,0].set_ylabel('log(seconds)') 

axs[0,0].set_title('Packed') 
axs[0,0].legend()

axs[0,1].plot(x_values, parallel_2_S_pack_excl_l, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[0,1].plot(x_values, parallel_2_M_pack_excl_l, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[0,1].plot(x_values, parallel_2_B_pack_excl_l, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

axs[0,1].set_xlabel('cores') 
axs[0,1].set_ylabel('log(seconds)') 

axs[0,1].set_title('Packed exclusive') 
axs[0,1].legend()

axs[1,0].plot(x_values, parallel_2_S_scatter_l, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[1,0].plot(x_values, parallel_2_M_scatter_l, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[1,0].plot(x_values, parallel_2_B_scatter_l, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

axs[1,0].set_xlabel('cores') 
axs[1,0].set_ylabel('log(seconds)') 

axs[1,0].set_title('Scattered') 
axs[1,0].legend()

axs[1,1].plot(x_values, parallel_2_S_scatter_excl_l, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[1,1].plot(x_values, parallel_2_M_scatter_excl_l, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[1,1].plot(x_values, parallel_2_B_scatter_excl_l, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

axs[1,1].set_xlabel('cores') 
axs[1,1].set_ylabel('log(seconds)') 

axs[1,1].set_title('Scattered exclusive') 
axs[1,1].legend()

fig.suptitle('Parallel 2nd implementation execution time over different configurations')
plt.show() 

###########################
# SPEEDUP PLOT PARALLEL 1 #
###########################

plt.rcParams["figure.figsize"] = [12, 8]
plt.rcParams["figure.autolayout"] = True

fig, axs = plt.subplots(2, 2)

axs[0,0].plot(x_values, parallel_1_S_pack_speedup, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[0,0].plot(x_values, parallel_1_M_pack_speedup, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[0,0].plot(x_values, parallel_1_B_pack_speedup, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)
axs[0,0].plot(x_values, x_values, color = 'grey', linewidth = 1.5, linestyle='dashed')

axs[0,0].set_xlabel('cores') 
axs[0,0].set_ylabel('speedup') 

axs[0,0].set_title('Packed') 
axs[0,0].legend()

axs[0,1].plot(x_values, parallel_1_S_pack_excl_speedup, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[0,1].plot(x_values, parallel_1_M_pack_excl_speedup, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[0,1].plot(x_values, parallel_1_B_pack_excl_speedup, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)
axs[0,1].plot(x_values, x_values, color = 'grey', linewidth = 1.5, linestyle='dashed')

axs[0,1].set_xlabel('cores') 
axs[0,1].set_ylabel('speedup') 

axs[0,1].set_title('Packed exclusive') 
axs[0,1].legend()

axs[1,0].plot(x_values, parallel_1_S_scatter_speedup, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[1,0].plot(x_values, parallel_1_M_scatter_speedup, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[1,0].plot(x_values, parallel_1_B_scatter_speedup, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)
axs[1,0].plot(x_values, x_values, color = 'grey', linewidth = 1.5, linestyle='dashed')

axs[1,0].set_xlabel('cores') 
axs[1,0].set_ylabel('speedup') 

axs[1,0].set_title('Scattered') 
axs[1,0].legend()

axs[1,1].plot(x_values, parallel_1_S_scatter_excl_speedup, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[1,1].plot(x_values, parallel_1_M_scatter_excl_speedup, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[1,1].plot(x_values, parallel_1_B_scatter_excl_speedup, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)
axs[1,1].plot(x_values, x_values, color = 'grey', linewidth = 1.5, linestyle='dashed')

axs[1,1].set_xlabel('cores') 
axs[1,1].set_ylabel('speedup') 

axs[1,1].set_title('Scattered exclusive') 
axs[1,1].legend()

fig.suptitle('Parallel 1st implementation speedup over different configurations')
plt.show() 

##############################
# EFFICIENCY PLOT PARALLEL 1 #
##############################

plt.rcParams["figure.figsize"] = [12, 8]
plt.rcParams["figure.autolayout"] = True

fig, axs = plt.subplots(2, 2)

axs[0,0].plot(x_values, parallel_1_S_pack_efficiency, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[0,0].plot(x_values, parallel_1_M_pack_efficiency, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[0,0].plot(x_values, parallel_1_B_pack_efficiency, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

axs[0,0].set_xlabel('cores') 
axs[0,0].set_ylabel('efficiency') 

axs[0,0].set_title('Packed') 
axs[0,0].legend()

axs[0,1].plot(x_values, parallel_1_S_pack_excl_efficiency, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[0,1].plot(x_values, parallel_1_M_pack_excl_efficiency, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[0,1].plot(x_values, parallel_1_B_pack_excl_efficiency, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

axs[0,1].set_xlabel('cores') 
axs[0,1].set_ylabel('efficiency') 

axs[0,1].set_title('Packed exclusive') 
axs[0,1].legend()

axs[1,0].plot(x_values, parallel_1_S_scatter_efficiency, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[1,0].plot(x_values, parallel_1_M_scatter_efficiency, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[1,0].plot(x_values, parallel_1_B_scatter_efficiency, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

axs[1,0].set_xlabel('cores') 
axs[1,0].set_ylabel('efficiency') 

axs[1,0].set_title('Scattered') 
axs[1,0].legend()

axs[1,1].plot(x_values, parallel_1_S_scatter_excl_efficiency, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[1,1].plot(x_values, parallel_1_M_scatter_excl_efficiency, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[1,1].plot(x_values, parallel_1_B_scatter_excl_efficiency, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

axs[1,1].set_xlabel('cores') 
axs[1,1].set_ylabel('efficiency') 

axs[1,1].set_title('Scattered exclusive') 
axs[1,1].legend()

fig.suptitle('Parallel 1st implementation efficiency over different configurations')
plt.show() 


###########################
# SPEEDUP PLOT PARALLEL 2 #
###########################

plt.rcParams["figure.figsize"] = [12, 8]
plt.rcParams["figure.autolayout"] = True

fig, axs = plt.subplots(2, 2)

axs[0,0].plot(x_values, parallel_2_S_pack_speedup, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[0,0].plot(x_values, parallel_2_M_pack_speedup, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[0,0].plot(x_values, parallel_2_B_pack_speedup, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)
axs[0,0].plot(x_values, x_values, color = 'grey', linewidth = 1.5, linestyle='dashed')

axs[0,0].set_xlabel('cores') 
axs[0,0].set_ylabel('speedup') 

axs[0,0].set_title('Packed') 
axs[0,0].legend()

axs[0,1].plot(x_values, parallel_2_S_pack_excl_speedup, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[0,1].plot(x_values, parallel_2_M_pack_excl_speedup, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[0,1].plot(x_values, parallel_2_B_pack_excl_speedup, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)
axs[0,1].plot(x_values, x_values, color = 'grey', linewidth = 1.5, linestyle='dashed')

axs[0,1].set_xlabel('cores') 
axs[0,1].set_ylabel('speedup') 

axs[0,1].set_title('Packed exclusive') 
axs[0,1].legend()

axs[1,0].plot(x_values, parallel_2_S_scatter_speedup, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[1,0].plot(x_values, parallel_2_M_scatter_speedup, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[1,0].plot(x_values, parallel_2_B_scatter_speedup, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)
axs[1,0].plot(x_values, x_values, color = 'grey', linewidth = 1.5, linestyle='dashed')

axs[1,0].set_xlabel('cores') 
axs[1,0].set_ylabel('speedup') 

axs[1,0].set_title('Scattered') 
axs[1,0].legend()

axs[1,1].plot(x_values, parallel_2_S_scatter_excl_speedup, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[1,1].plot(x_values, parallel_2_M_scatter_excl_speedup, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[1,1].plot(x_values, parallel_2_B_scatter_excl_speedup, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)
axs[1,1].plot(x_values, x_values, color = 'grey', linewidth = 1.5, linestyle='dashed')

axs[1,1].set_xlabel('cores') 
axs[1,1].set_ylabel('speedup') 

axs[1,1].set_title('Scattered exclusive') 
axs[1,1].legend()

fig.suptitle('Parallel 2nd implementation speedup over different configurations')
plt.show() 

##############################
# EFFICIENCY PLOT PARALLEL 2 #
##############################

plt.rcParams["figure.figsize"] = [12, 8]
plt.rcParams["figure.autolayout"] = True

fig, axs = plt.subplots(2, 2)

axs[0,0].plot(x_values, parallel_2_S_pack_efficiency, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[0,0].plot(x_values, parallel_2_M_pack_efficiency, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[0,0].plot(x_values, parallel_2_B_pack_efficiency, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

axs[0,0].set_xlabel('cores') 
axs[0,0].set_ylabel('efficiency') 

axs[0,0].set_title('Packed') 
axs[0,0].legend()

axs[0,1].plot(x_values, parallel_2_S_pack_excl_efficiency, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[0,1].plot(x_values, parallel_2_M_pack_excl_efficiency, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[0,1].plot(x_values, parallel_2_B_pack_excl_efficiency, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

axs[0,1].set_xlabel('cores') 
axs[0,1].set_ylabel('efficiency') 

axs[0,1].set_title('Packed exclusive') 
axs[0,1].legend()

axs[1,0].plot(x_values, parallel_2_S_scatter_efficiency, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[1,0].plot(x_values, parallel_2_M_scatter_efficiency, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[1,0].plot(x_values, parallel_2_B_scatter_efficiency, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

axs[1,0].set_xlabel('cores') 
axs[1,0].set_ylabel('efficiency') 

axs[1,0].set_title('Scattered') 
axs[1,0].legend()

axs[1,1].plot(x_values, parallel_2_S_scatter_excl_efficiency, label = "Small dataset", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
axs[1,1].plot(x_values, parallel_2_M_scatter_excl_efficiency, label = "Medium dataset", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)
axs[1,1].plot(x_values, parallel_2_B_scatter_excl_efficiency, label = "Big dataset", color = 'green', linewidth = 1.5, marker='o', markerfacecolor='green', markersize=3)

axs[1,1].set_xlabel('cores') 
axs[1,1].set_ylabel('efficiency') 

axs[1,1].set_title('Scattered exclusive') 
axs[1,1].legend()

fig.suptitle('Parallel 2nd implementation efficiency over different configurations')
plt.show() 


#################################
# HIGH DIMENSIONAL DATASET PLOT #
#################################

plt.rcParams["figure.figsize"] = [10, 8]
plt.rcParams["figure.autolayout"] = True

fig, (file, algo) = plt.subplots(2, 1)

file.plot(x_values_HD, parallel_1_6D_l, label = "parallel 1", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
file.plot(x_values_HD, parallel_2_6D_l, label = "parallel 2", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)

file.set_xlabel('cores') 
file.set_ylabel('log(seconds)') 

file.set_title('Six dimensional dataset time') 
file.legend()

algo.plot(x_values_HD, parallel_1_8D_l, label = "parallel 1", color = 'blue', linewidth = 1.5, marker='o', markerfacecolor='blue', markersize=3)
algo.plot(x_values_HD, parallel_2_8D_l, label = "parallel 2", color = 'red', linewidth = 1.5, marker='o', markerfacecolor='red', markersize=3)

algo.set_xlabel('cores') 
algo.set_ylabel('log(seconds)') 

algo.set_title('Eight dimensional dataset time') 
algo.legend()
  
fig.suptitle('Comparison between two implementations on high dimensional datasets')
plt.show() 