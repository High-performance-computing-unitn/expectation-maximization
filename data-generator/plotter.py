from matplotlib import pyplot as plt
import math

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