from matplotlib import pyplot as plt

serial_file_SDS = 0
serial_algo_SDS = 0
serial_file_MDS = 0
serial_algo_MDS = 0
serial_file_BDS = 0
serial_algo_BDS = 0

parallel_1_file_SDS = []
parallel_1_algo_SDS = []
parallel_1_file_MDS = []
parallel_1_algo_MDS = []
parallel_1_file_BDS = []
parallel_1_algo_BDS = []

parallel_2_file_SDS = []
parallel_2_algo_SDS = []
parallel_2_file_MDS = []
parallel_2_algo_MDS = []
parallel_2_file_BDS = []
parallel_2_algo_BDS = []

parallel_1_file_6D = [0.08, 0.03, 0.03, 0.15, 0.03, 0.14]
parallel_1_algo_6D = [304, 166, 83, 42, 20, 19]

parallel_2_file_6D = [0.02, 0.01, 0.007, 0.01, 0.02, 0.01]
parallel_2_algo_6D = [17, 15, 12, 7, 4, 8]

parallel_1_file_8D = [0.03, 0.04, 0.01, 0.3, 0.008, 0.008]
parallel_1_algo_8D = [4347, 2032, 1476, 705, 415, 114]

parallel_2_file_8D = [0.006, 0.003, 0.005, 0.005, 0.02, 0.006]
parallel_2_algo_8D = [4.6, 4.4, 2.3, 2.4, 0.7, 1]

version = 0
dataset = 0

with open('../results_formatted.txt') as f:
    while True:
        line = f.readline()
        if not line:
            break

        if(line.strip() == 'v'):
            version += 1
            dataset = 0
            continue
        
        if(line.strip() == 'd'):
            dataset += 1
            continue

        words = line.strip().split("-")

        if(version == 0):
            if(dataset == 0):
                serial_file_SDS = float(words[0])
                serial_algo_SDS = int(words[1])
            if(dataset == 1):
                serial_file_MDS = float(words[0])
                serial_algo_MDS = int(words[1])
            if(dataset == 2):
                serial_file_BDS = float(words[0])
                serial_algo_BDS = int(words[1])
        
        if(version == 1):
            if(dataset == 0):
                parallel_1_file_SDS.append(float(words[0]))
                parallel_1_algo_SDS.append(int(words[1]))
            if(dataset == 1):
                parallel_1_file_MDS.append(float(words[0]))
                parallel_1_algo_MDS.append(int(words[1]))
            if(dataset == 2):
                parallel_1_file_BDS.append(float(words[0]))
                parallel_1_algo_BDS.append(int(words[1]))

        if(version == 2):
            if(dataset == 0):
                parallel_2_file_SDS.append(float(words[0]))
                parallel_2_algo_SDS.append(int(words[1]))
            if(dataset == 1):
                parallel_2_file_MDS.append(float(words[0]))
                parallel_2_algo_MDS.append(int(words[1]))
            if(dataset == 2):
                parallel_2_file_BDS.append(float(words[0]))
                parallel_2_algo_BDS.append(int(words[1]))

x_values = [1, 2, 4, 8, 16, 32, 64, 80]
x_ticks_HD = [2, 4, 8, 16, 32, 64]

# SMALL DATASET PLOT

plt.rcParams["figure.figsize"] = [8, 8]
plt.rcParams["figure.autolayout"] = True

fig, (file, algo) = plt.subplots(2, 1)

file.plot(range(0, len(x_values)), parallel_1_file_SDS, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
file.plot(range(0, len(x_values)), parallel_2_file_SDS, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)
file.plot([0], [serial_file_SDS], label = "serial", color = 'green', marker='o', markerfacecolor='green', markersize=5)

file.set_xlabel('processes') 
file.set_ylabel('seconds') 

file.set_xticks(range(len(x_values)), x_values)
file.set_xlim(-0.5, len(x_values) - 0.5)

file.set_title('Small dataset file reading time') 
file.legend()

algo.plot(range(0, len(x_values)), parallel_1_algo_SDS, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
algo.plot(range(0, len(x_values)), parallel_2_algo_SDS, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)
algo.plot([0], [serial_algo_SDS], label = "serial", color = 'green', marker='o', markerfacecolor='green', markersize=5)

algo.set_xlabel('processes') 
algo.set_ylabel('seconds') 

algo.set_xticks(range(len(x_values)), x_values)
algo.set_xlim(-0.5, len(x_values) - 0.5)

algo.set_title('Small dataset algorithm time') 
algo.legend()
  
plt.show() 

# MEDIUM DATASET PLOT

plt.rcParams["figure.figsize"] = [8, 8]
plt.rcParams["figure.autolayout"] = True

fig, (file, algo) = plt.subplots(2, 1)

file.plot(range(0, len(x_values)), parallel_1_file_MDS, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
file.plot(range(0, len(x_values)), parallel_2_file_MDS, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)
file.plot([0], [serial_file_MDS], label = "serial", color = 'green', marker='o', markerfacecolor='green', markersize=5)

file.set_xlabel('processes') 
file.set_ylabel('seconds') 

file.set_xticks(range(len(x_values)), x_values)
file.set_xlim(-0.5, len(x_values) - 0.5)

file.set_title('Medium dataset file reading time') 
file.legend()

algo.plot(range(0, len(x_values)), parallel_1_algo_MDS, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
algo.plot(range(0, len(x_values)), parallel_2_algo_MDS, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)
algo.plot([0], [serial_algo_MDS], label = "serial", color = 'green', marker='o', markerfacecolor='green', markersize=5)

algo.set_xlabel('processes') 
algo.set_ylabel('seconds') 

algo.set_xticks(range(len(x_values)), x_values)
algo.set_xlim(-0.5, len(x_values) - 0.5)

algo.set_title('Medium dataset algorithm time') 
algo.legend()
  
plt.show() 

# BIG DATASET PLOT

plt.rcParams["figure.figsize"] = [8, 8]
plt.rcParams["figure.autolayout"] = True

fig, (file, algo) = plt.subplots(2, 1)

file.plot(range(0, len(x_values)), parallel_1_file_BDS, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
file.plot(range(0, len(x_values)), parallel_2_file_BDS, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)
file.plot([0], [serial_file_BDS], label = "serial", color = 'green', marker='o', markerfacecolor='green', markersize=5)

file.set_xlabel('processes') 
file.set_ylabel('seconds') 

file.set_xticks(range(len(x_values)), x_values)
file.set_xlim(-0.5, len(x_values) - 0.5)

file.set_title('Big dataset file reading time') 
file.legend()

algo.plot(range(0, len(x_values)), parallel_1_algo_BDS, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
algo.plot(range(0, len(x_values)), parallel_2_algo_BDS, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)
algo.plot([0], [serial_algo_BDS], label = "serial", color = 'green', marker='o', markerfacecolor='green', markersize=5)

algo.set_xlabel('processes') 
algo.set_ylabel('seconds') 

algo.set_xticks(range(len(x_values)), x_values)
algo.set_xlim(-0.5, len(x_values) - 0.5)

algo.set_title('Big dataset algorithm time') 
algo.legend()
  
plt.show() 

# 6 DIMENSIONAL DATASET PLOT

plt.rcParams["figure.figsize"] = [8, 8]
plt.rcParams["figure.autolayout"] = True

fig, (file, algo) = plt.subplots(2, 1)

file.plot(range(len(x_ticks_HD)), parallel_1_file_6D, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
file.plot(range(len(x_ticks_HD)), parallel_2_file_6D, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)

file.set_xlabel('processes') 
file.set_ylabel('seconds') 

file.set_xticks(range(len(x_ticks_HD)), x_ticks_HD)
file.set_xlim(-0.5, len(x_ticks_HD) - 0.5)

file.set_title('Six dimensional dataset file reading time') 
file.legend()

algo.plot(range(len(x_ticks_HD)), parallel_1_algo_6D, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
algo.plot(range(len(x_ticks_HD)), parallel_2_algo_6D, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)

algo.set_xlabel('processes') 
algo.set_ylabel('seconds') 

algo.set_xticks(range(len(x_ticks_HD)), x_ticks_HD)
algo.set_xlim(-0.5, len(x_ticks_HD) - 0.5)

algo.set_title('Six dimensional dataset algorithm time') 
algo.legend()
  
plt.show() 

# 8 DIMENSIONAL DATASET PLOT

plt.rcParams["figure.figsize"] = [8, 8]
plt.rcParams["figure.autolayout"] = True

fig, (file, algo) = plt.subplots(2, 1)

file.plot(range(len(x_ticks_HD)), parallel_1_file_8D, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
file.plot(range(len(x_ticks_HD)), parallel_2_file_8D, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)

file.set_xlabel('processes') 
file.set_ylabel('seconds') 

file.set_xticks(range(len(x_ticks_HD)), x_ticks_HD)
file.set_xlim(-0.5, len(x_ticks_HD) - 0.5)

file.set_title('Eight dimensional dataset file reading time') 
file.legend()

algo.plot(range(len(x_ticks_HD)), parallel_1_algo_8D, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
algo.plot(range(len(x_ticks_HD)), parallel_2_algo_8D, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)

algo.set_xlabel('processes') 
algo.set_ylabel('seconds') 

algo.set_xticks(range(len(x_ticks_HD)), x_ticks_HD)
algo.set_xlim(-0.5, len(x_ticks_HD) - 0.5)

algo.set_title('Eight dimensional dataset algorithm time') 
algo.legend()
  
plt.show() 


## EVALUATION SPEEDUP AND EFFICIENCY

parallel_1_algo_Speedup_SDS = []
parallel_1_algo_Efficiency_SDS = []

parallel_1_algo_Speedup_MDS = []
parallel_1_algo_Efficiency_MDS = []

parallel_1_algo_Speedup_BDS = []
parallel_1_algo_Efficiency_BDS = []

parallel_2_algo_Speedup_SDS = []
parallel_2_algo_Efficiency_SDS = []

parallel_2_algo_Speedup_MDS = []
parallel_2_algo_Efficiency_MDS = []

parallel_2_algo_Speedup_BDS = []
parallel_2_algo_Efficiency_BDS = []

for index, time in enumerate(parallel_1_algo_SDS):
    speedup = parallel_1_algo_SDS[0] / time
    efficiency = speedup / x_values[index]

    parallel_1_algo_Speedup_SDS.append(speedup)
    parallel_1_algo_Efficiency_SDS.append(efficiency)

for index, time in enumerate(parallel_1_algo_MDS):
    speedup = parallel_1_algo_MDS[0] / time
    efficiency = speedup / x_values[index]

    parallel_1_algo_Speedup_MDS.append(speedup)
    parallel_1_algo_Efficiency_MDS.append(efficiency)

for index, time in enumerate(parallel_1_algo_BDS):
    speedup = parallel_1_algo_BDS[0] / time
    efficiency = speedup / x_values[index]

    parallel_1_algo_Speedup_BDS.append(speedup)
    parallel_1_algo_Efficiency_BDS.append(efficiency)

for index, time in enumerate(parallel_2_algo_SDS):
    speedup = parallel_2_algo_SDS[0] / time
    efficiency = speedup / x_values[index]

    parallel_2_algo_Speedup_SDS.append(speedup)
    parallel_2_algo_Efficiency_SDS.append(efficiency)

for index, time in enumerate(parallel_2_algo_MDS):
    speedup = parallel_2_algo_MDS[0] / time
    efficiency = speedup / x_values[index]

    parallel_2_algo_Speedup_MDS.append(speedup)
    parallel_2_algo_Efficiency_MDS.append(efficiency)

for index, time in enumerate(parallel_2_algo_BDS):
    speedup = parallel_2_algo_BDS[0] / time
    efficiency = speedup / x_values[index]

    parallel_2_algo_Speedup_BDS.append(speedup)
    parallel_2_algo_Efficiency_BDS.append(efficiency)

# SMALL DATASET SPEEDUP AND EFFICIENCY
    
plt.rcParams["figure.figsize"] = [8, 8]
plt.rcParams["figure.autolayout"] = True

fig, (speedup, efficiency) = plt.subplots(2, 1)

speedup.plot(range(0, len(x_values)), parallel_1_algo_Speedup_SDS, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
speedup.plot(range(0, len(x_values)), parallel_2_algo_Speedup_SDS, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)

speedup.set_xlabel('processes') 
speedup.set_ylabel('speedup') 

speedup.set_xticks(range(len(x_values)), x_values)
speedup.set_xlim(-0.5, len(x_values) - 0.5)

speedup.set_title('Small dataset speedup comparison') 
speedup.legend()

efficiency.plot(range(0, len(x_values)), parallel_1_algo_Efficiency_SDS, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
efficiency.plot(range(0, len(x_values)), parallel_2_algo_Efficiency_SDS, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)

efficiency.set_xlabel('processes') 
efficiency.set_ylabel('effciency') 

efficiency.set_xticks(range(len(x_values)), x_values)
efficiency.set_xlim(-0.5, len(x_values) - 0.5)

efficiency.set_title('Small dataset efficiency comaprison') 
efficiency.legend()
  
plt.show() 

# MEDIUM DATASET SPEEDUP AND EFFICIENCY
    
plt.rcParams["figure.figsize"] = [8, 8]
plt.rcParams["figure.autolayout"] = True

fig, (speedup, efficiency) = plt.subplots(2, 1)

speedup.plot(range(0, len(x_values)), parallel_1_algo_Speedup_MDS, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
speedup.plot(range(0, len(x_values)), parallel_2_algo_Speedup_MDS, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)

speedup.set_xlabel('processes') 
speedup.set_ylabel('speedup') 

speedup.set_xticks(range(len(x_values)), x_values)
speedup.set_xlim(-0.5, len(x_values) - 0.5)

speedup.set_title('Medium dataset speedup comparison') 
speedup.legend()

efficiency.plot(range(0, len(x_values)), parallel_1_algo_Efficiency_MDS, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
efficiency.plot(range(0, len(x_values)), parallel_2_algo_Efficiency_MDS, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)

efficiency.set_xlabel('processes') 
efficiency.set_ylabel('effciency') 

efficiency.set_xticks(range(len(x_values)), x_values)
efficiency.set_xlim(-0.5, len(x_values) - 0.5)

efficiency.set_title('Medium dataset efficiency comaprison') 
efficiency.legend()
  
plt.show() 

# BIG DATASET SPEEDUP AND EFFICIENCY
    
plt.rcParams["figure.figsize"] = [8, 8]
plt.rcParams["figure.autolayout"] = True

fig, (speedup, efficiency) = plt.subplots(2, 1)

speedup.plot(range(0, len(x_values)), parallel_1_algo_Speedup_BDS, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
speedup.plot(range(0, len(x_values)), parallel_2_algo_Speedup_BDS, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)

speedup.set_xlabel('processes') 
speedup.set_ylabel('speedup') 

speedup.set_xticks(range(len(x_values)), x_values)
speedup.set_xlim(-0.5, len(x_values) - 0.5)

speedup.set_title('Big dataset speedup comparison') 
speedup.legend()

efficiency.plot(range(0, len(x_values)), parallel_1_algo_Efficiency_BDS, label = "parallel 1", color = 'blue', linewidth = 2, marker='o', markerfacecolor='blue', markersize=5)
efficiency.plot(range(0, len(x_values)), parallel_2_algo_Efficiency_BDS, label = "parallel 2", color = 'red', linewidth = 2, marker='o', markerfacecolor='red', markersize=5)

efficiency.set_xlabel('processes') 
efficiency.set_ylabel('effciency') 

efficiency.set_xticks(range(len(x_values)), x_values)
efficiency.set_xlim(-0.5, len(x_values) - 0.5)

efficiency.set_title('Big dataset efficiency comaprison') 
efficiency.legend()
  
plt.show() 