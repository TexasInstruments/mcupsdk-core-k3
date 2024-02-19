# Memcopy benchmarking demo {#EXAMPLES_KERNEL_FREERTOS_MEMCPY_BENCHMARK}

[TOC]

# Introduction

This application, internally called as AUTOSAR benchmarking application is used for benchmarking several KPIs such as:

- I-cache miss
- D-cache miss
- memory copy performance on different cores
- with options such as XIP, non-XIP
- ability to run software on other cores
- run with CCS or SBL etc.

# Supported Combinations

\cond SOC_AM62X

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER, @VAR_SK_LP_BOARD_NAME_LOWER, @VAR_SIP_SK_BOARD_NAME_LOWER
 Example folder | examples/kernel/freertos/memcpy_benchmark/

 \endcond

\cond SOC_AM62AX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 freertos
 ^              | r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/kernel/freertos/memcpy_benchmark/

\endcond

\cond SOC_AM62PX

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 freertos
 ^              | wkup-r5fss0-0 freertos
 Toolchain      | ti-arm-clang
 Board          | @VAR_BOARD_NAME_LOWER
 Example folder | examples/kernel/freertos/memcpy_benchmark/

\endcond

# Steps to Run the Example

- **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE).
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE

# See Also

\ref KERNEL_FREERTOS_PAGE

# Sample Output

Shown below is a sample output when the benchmark application is run,
\if SOC_AM62X
**Board: am62x-sk, Core: r5f**
\code

Memcpy Benchmarking for DDR memory:
Filling up the gBuffers
Sanity checking for PMU counters
Inst Cache Miss: 0
Inst Cache Access: 0
Number of instructions: 39
Data Cache Miss: 0
Created MasterTask
Created all 15 slaveTasks

Master_task

Master_task -- start sending

MemCopy Size : 0
Exec Time in Usec : 2693
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1405
Instruction Cache Access : 912
Number of Instructions Executed : 398497
Data Cache Miss : 1405
InstructionCacheMiss/sec : 521722
Instructions/sec : 147975120
DataCacheMiss/sec : 338655

MemCopy Size : 50
Exec Time in Usec : 3207
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1347
Instruction Cache Access : 919
Number of Instructions Executed : 602215
Data Cache Miss : 1347
InstructionCacheMiss/sec : 420018
Instructions/sec : 187781415
DataCacheMiss/sec : 286560

MemCopy Size : 100
Exec Time in Usec : 3409
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1163
Instruction Cache Access : 814
Number of Instructions Executed : 736783
Data Cache Miss : 1163
InstructionCacheMiss/sec : 341155
Instructions/sec : 216128776
DataCacheMiss/sec : 238779

MemCopy Size : 200
Exec Time in Usec : 4387
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1338
Instruction Cache Access : 922
Number of Instructions Executed : 1090857
Data Cache Miss : 1338
InstructionCacheMiss/sec : 304992
Instructions/sec : 248656713
DataCacheMiss/sec : 210166

MemCopy Size : 500
Exec Time in Usec : 6441
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1127
Instruction Cache Access : 934
Number of Instructions Executed : 1957388
Data Cache Miss : 1127
InstructionCacheMiss/sec : 174972
Instructions/sec : 303895047
DataCacheMiss/sec : 145008

MemCopy Size : 750
Exec Time in Usec : 9095
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1179
Instruction Cache Access : 1085
Number of Instructions Executed : 2991991
Data Cache Miss : 1179
InstructionCacheMiss/sec : 129631
Instructions/sec : 328970973
DataCacheMiss/sec : 119296

MemCopy Size : 1000
Exec Time in Usec : 10017
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1063
Instruction Cache Access : 1645
Number of Instructions Executed : 3342803
Data Cache Miss : 1063
InstructionCacheMiss/sec : 106119
Instructions/sec : 333712987
DataCacheMiss/sec : 164220

MemCopy Size : 1250
Exec Time in Usec : 11656
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1048
Instruction Cache Access : 1901
Number of Instructions Executed : 3991428
Data Cache Miss : 1048
InstructionCacheMiss/sec : 89910
Instructions/sec : 342435483
DataCacheMiss/sec : 163091

MemCopy Size : 1500
Exec Time in Usec : 14322
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1282
Instruction Cache Access : 2183
Number of Instructions Executed : 4990088
Data Cache Miss : 1282
InstructionCacheMiss/sec : 89512
Instructions/sec : 348421170
DataCacheMiss/sec : 152422

MemCopy Size : 2048
Exec Time in Usec : 23841
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1502
Instruction Cache Access : 4866
Number of Instructions Executed : 8565960
Data Cache Miss : 1502
InstructionCacheMiss/sec : 63000
Instructions/sec : 359295331
DataCacheMiss/sec : 204102

All tests have passed!!

\endcode

**Board: am62x-sk-lp, Core: r5f**
\code

Memcpy Benchmarking for DDR memory:
Filling up the gBuffers
Sanity checking for PMU counters
Inst Cache Miss: 0
Inst Cache Access: 0
Number of instructions: 39
Data Cache Miss: 0
Created MasterTask
Created all 15 slaveTasks

Master_task

Master_task -- start sending

MemCopy Size : 0
Exec Time in Usec : 2724
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1420
Instruction Cache Access : 899
Number of Instructions Executed : 398349
Data Cache Miss : 1420
InstructionCacheMiss/sec : 521292
Instructions/sec : 146236784
DataCacheMiss/sec : 330029

MemCopy Size : 50
Exec Time in Usec : 3253
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1413
Instruction Cache Access : 934
Number of Instructions Executed : 602215
Data Cache Miss : 1413
InstructionCacheMiss/sec : 434368
Instructions/sec : 185126037
DataCacheMiss/sec : 287119

MemCopy Size : 100
Exec Time in Usec : 3449
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1196
Instruction Cache Access : 858
Number of Instructions Executed : 736919
Data Cache Miss : 1196
InstructionCacheMiss/sec : 346767
Instructions/sec : 213661641
DataCacheMiss/sec : 248767

MemCopy Size : 200
Exec Time in Usec : 4420
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1352
Instruction Cache Access : 914
Number of Instructions Executed : 1090811
Data Cache Miss : 1352
InstructionCacheMiss/sec : 305882
Instructions/sec : 246789819
DataCacheMiss/sec : 206787

MemCopy Size : 500
Exec Time in Usec : 6471
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1114
Instruction Cache Access : 945
Number of Instructions Executed : 1957388
Data Cache Miss : 1114
InstructionCacheMiss/sec : 172152
Instructions/sec : 302486169
DataCacheMiss/sec : 146036

MemCopy Size : 750
Exec Time in Usec : 9108
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1095
Instruction Cache Access : 1050
Number of Instructions Executed : 2991991
Data Cache Miss : 1095
InstructionCacheMiss/sec : 120223
Instructions/sec : 328501427
DataCacheMiss/sec : 115283

MemCopy Size : 1000
Exec Time in Usec : 10073
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1080
Instruction Cache Access : 1678
Number of Instructions Executed : 3342809
Data Cache Miss : 1080
InstructionCacheMiss/sec : 107217
Instructions/sec : 331858334
DataCacheMiss/sec : 166583

MemCopy Size : 1250
Exec Time in Usec : 11706
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1054
Instruction Cache Access : 1861
Number of Instructions Executed : 3991405
Data Cache Miss : 1054
InstructionCacheMiss/sec : 90039
Instructions/sec : 340970869
DataCacheMiss/sec : 158978

MemCopy Size : 1500
Exec Time in Usec : 14384
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1210
Instruction Cache Access : 2224
Number of Instructions Executed : 4990230
Data Cache Miss : 1210
InstructionCacheMiss/sec : 84121
Instructions/sec : 346929226
DataCacheMiss/sec : 154616

MemCopy Size : 2048
Exec Time in Usec : 23918
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1463
Instruction Cache Access : 4741
Number of Instructions Executed : 8566108
Data Cache Miss : 1463
InstructionCacheMiss/sec : 61167
Instructions/sec : 358144828
DataCacheMiss/sec : 198218

All tests have passed!!

\endcode

**Board: am62x-sip-sk, Core: r5f**
\code
Memcpy Benchmarking for DDR memory:
Filling up the gBuffers
Sanity checking for PMU counters
Inst Cache Miss: 0
Inst Cache Access: 0
Number of instructions: 39
Data Cache Miss: 0
Created MasterTask
Created all 15 slaveTasks

Master_task

Master_task -- start sending

MemCopy Size : 0
Exec Time in Usec : 2656
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1320
Instruction Cache Access : 870
Number of Instructions Executed : 398354
Data Cache Miss : 1320
InstructionCacheMiss/sec : 496987
Instructions/sec : 149982680
DataCacheMiss/sec : 327560

MemCopy Size : 50
Exec Time in Usec : 3191
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1304
Instruction Cache Access : 912
Number of Instructions Executed : 602237
Data Cache Miss : 1304
InstructionCacheMiss/sec : 408649
Instructions/sec : 188729865
DataCacheMiss/sec : 285803

MemCopy Size : 100
Exec Time in Usec : 3399
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1135
Instruction Cache Access : 797
Number of Instructions Executed : 736918
Data Cache Miss : 1135
InstructionCacheMiss/sec : 333921
Instructions/sec : 216804354
DataCacheMiss/sec : 234480

MemCopy Size : 200
Exec Time in Usec : 4370
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1294
Instruction Cache Access : 922
Number of Instructions Executed : 1090674
Data Cache Miss : 1294
InstructionCacheMiss/sec : 296109
Instructions/sec : 249582151
DataCacheMiss/sec : 210983

MemCopy Size : 500
Exec Time in Usec : 6432
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1062
Instruction Cache Access : 949
Number of Instructions Executed : 1957381
Data Cache Miss : 1062
InstructionCacheMiss/sec : 165111
Instructions/sec : 304319185
DataCacheMiss/sec : 147543

MemCopy Size : 750
Exec Time in Usec : 9085
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1115
Instruction Cache Access : 1095
Number of Instructions Executed : 2991990
Data Cache Miss : 1115
InstructionCacheMiss/sec : 122729
Instructions/sec : 329332966
DataCacheMiss/sec : 120528

MemCopy Size : 1000
Exec Time in Usec : 9937
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1025
Instruction Cache Access : 1381
Number of Instructions Executed : 3342802
Data Cache Miss : 1025
InstructionCacheMiss/sec : 103149
Instructions/sec : 336399516
DataCacheMiss/sec : 138975

MemCopy Size : 1250
Exec Time in Usec : 11553
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 969
Instruction Cache Access : 1552
Number of Instructions Executed : 3991268
Data Cache Miss : 969
InstructionCacheMiss/sec : 83874
Instructions/sec : 345474595
DataCacheMiss/sec : 134337

MemCopy Size : 1500
Exec Time in Usec : 14249
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1180
Instruction Cache Access : 2029
Number of Instructions Executed : 4990110
Data Cache Miss : 1180
InstructionCacheMiss/sec : 82812
Instructions/sec : 350207733
DataCacheMiss/sec : 142395

MemCopy Size : 2048
Exec Time in Usec : 23657
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1415
Instruction Cache Access : 4153
Number of Instructions Executed : 8565965
Data Cache Miss : 1415
InstructionCacheMiss/sec : 59813
Instructions/sec : 362090079
DataCacheMiss/sec : 175550

All tests have passed!!

\endcode
\elseif SOC_AM62AX

**mcu r5f core:**
\code

Memcpy Benchmarking for MSRAM memory:
Filling up the gBuffers
Sanity checking for PMU counters
Inst Cache Miss: 1
Inst Cache Access: 0
Number of instructions: 39
Data Cache Miss: 0
Created MasterTask
Created all 15 slaveTasks

Master_task

Master_task -- start sending

MemCopy Size : 0
Exec Time in Usec : 1000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 969
Instruction Cache Access : 764
Number of Instructions Executed : 389860
Data Cache Miss : 969
InstructionCacheMiss/sec : 969000
Instructions/sec : 389860000
DataCacheMiss/sec : 764000

MemCopy Size : 50
Exec Time in Usec : 1000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 956
Instruction Cache Access : 850
Number of Instructions Executed : 593379
Data Cache Miss : 956
InstructionCacheMiss/sec : 956000
Instructions/sec : 593379000
DataCacheMiss/sec : 850000

MemCopy Size : 100
Exec Time in Usec : 2000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 910
Instruction Cache Access : 747
Number of Instructions Executed : 728511
Data Cache Miss : 910
InstructionCacheMiss/sec : 455000
Instructions/sec : 364255500
DataCacheMiss/sec : 373500

MemCopy Size : 200
Exec Time in Usec : 2000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 983
Instruction Cache Access : 841
Number of Instructions Executed : 1082113
Data Cache Miss : 983
InstructionCacheMiss/sec : 491500
Instructions/sec : 541056500
DataCacheMiss/sec : 420500

MemCopy Size : 500
Exec Time in Usec : 4000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 822
Instruction Cache Access : 855
Number of Instructions Executed : 1949171
Data Cache Miss : 822
InstructionCacheMiss/sec : 205500
Instructions/sec : 487292750
DataCacheMiss/sec : 213750

MemCopy Size : 750
Exec Time in Usec : 5000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 907
Instruction Cache Access : 1004
Number of Instructions Executed : 2983315
Data Cache Miss : 907
InstructionCacheMiss/sec : 181400
Instructions/sec : 596663000
DataCacheMiss/sec : 200800

MemCopy Size : 1000
Exec Time in Usec : 5000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 819
Instruction Cache Access : 1231
Number of Instructions Executed : 3334291
Data Cache Miss : 819
InstructionCacheMiss/sec : 163800
Instructions/sec : 666858200
DataCacheMiss/sec : 246200

MemCopy Size : 1250
Exec Time in Usec : 5000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 786
Instruction Cache Access : 1512
Number of Instructions Executed : 3982721
Data Cache Miss : 786
InstructionCacheMiss/sec : 157200
Instructions/sec : 796544200
DataCacheMiss/sec : 302400

MemCopy Size : 1500
Exec Time in Usec : 7000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 898
Instruction Cache Access : 1960
Number of Instructions Executed : 4981020
Data Cache Miss : 898
InstructionCacheMiss/sec : 128285
Instructions/sec : 711574285
DataCacheMiss/sec : 280000

MemCopy Size : 2048
Exec Time in Usec : 12000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1160
Instruction Cache Access : 3928
Number of Instructions Executed : 8555920
Data Cache Miss : 1160
InstructionCacheMiss/sec : 96666
Instructions/sec : 712993333
DataCacheMiss/sec : 327333

All tests have passed!!

Memcpy Benchmarking for DDR memory:
Filling up the gBuffers
Sanity checking for PMU counters
Inst Cache Miss: 1
Inst Cache Access: 0
Number of instructions: 39
Data Cache Miss: 0
Created MasterTask
Created all 15 slaveTasks

Master_task

Master_task -- start sending

MemCopy Size : 0
Exec Time in Usec : 1000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1147
Instruction Cache Access : 909
Number of Instructions Executed : 399352
Data Cache Miss : 1147
InstructionCacheMiss/sec : 1147000
Instructions/sec : 399352000
DataCacheMiss/sec : 909000

MemCopy Size : 50
Exec Time in Usec : 1000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1051
Instruction Cache Access : 784
Number of Instructions Executed : 556188
Data Cache Miss : 1051
InstructionCacheMiss/sec : 1051000
Instructions/sec : 556188000
DataCacheMiss/sec : 784000

MemCopy Size : 100
Exec Time in Usec : 2000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1001
Instruction Cache Access : 849
Number of Instructions Executed : 801227
Data Cache Miss : 1001
InstructionCacheMiss/sec : 500499
Instructions/sec : 400613500
DataCacheMiss/sec : 424500

MemCopy Size : 200
Exec Time in Usec : 2000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 952
Instruction Cache Access : 977
Number of Instructions Executed : 1065900
Data Cache Miss : 952
InstructionCacheMiss/sec : 476000
Instructions/sec : 532950000
DataCacheMiss/sec : 488500

MemCopy Size : 500
Exec Time in Usec : 4000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1080
Instruction Cache Access : 1235
Number of Instructions Executed : 2262393
Data Cache Miss : 1080
InstructionCacheMiss/sec : 270000
Instructions/sec : 565598250
DataCacheMiss/sec : 308750

MemCopy Size : 750
Exec Time in Usec : 4000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 985
Instruction Cache Access : 1282
Number of Instructions Executed : 2952018
Data Cache Miss : 985
InstructionCacheMiss/sec : 246250
Instructions/sec : 738004500
DataCacheMiss/sec : 320500

MemCopy Size : 1000
Exec Time in Usec : 6000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1049
Instruction Cache Access : 1572
Number of Instructions Executed : 3635131
Data Cache Miss : 1049
InstructionCacheMiss/sec : 174833
Instructions/sec : 605855166
DataCacheMiss/sec : 262000

MemCopy Size : 1250
Exec Time in Usec : 7000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 897
Instruction Cache Access : 2080
Number of Instructions Executed : 4755039
Data Cache Miss : 897
InstructionCacheMiss/sec : 128142
Instructions/sec : 679291285
DataCacheMiss/sec : 297142

MemCopy Size : 1500
Exec Time in Usec : 7000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 888
Instruction Cache Access : 2167
Number of Instructions Executed : 5439723
Data Cache Miss : 888
InstructionCacheMiss/sec : 126857
Instructions/sec : 777103285
DataCacheMiss/sec : 309571

MemCopy Size : 2048
Exec Time in Usec : 10000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 913
Instruction Cache Access : 3412
Number of Instructions Executed : 7196748
Data Cache Miss : 913
InstructionCacheMiss/sec : 91300
Instructions/sec : 719674800
DataCacheMiss/sec : 341200

All tests have passed!!

\endcode

**r5f core:**
\code

Memcpy Benchmarking for MSRAM memory:
Filling up the gBuffers
Sanity checking for PMU counters
Inst Cache Miss: 0
Inst Cache Access: 39
Number of Instructions: 53
Data Cache Miss: 0
Created MasterTask
Created all 15 slaveTasks

Master_task

Master_task -- start sending

MemCopy Size : 0
Exec Time in Usec : 1372
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1271
Instruction Cache Access : 398370
Number of Instructions Executed : 398384
Data Cache Miss : 857
InstructionCacheMiss/sec : 926384
Instructions/sec : 290367346
DataCacheMiss/sec : 624635

MemCopy Size : 50
Exec Time in Usec : 1633
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1230
Instruction Cache Access : 601931
Number of Instructions Executed : 601945
Data Cache Miss : 892
InstructionCacheMiss/sec : 753214
Instructions/sec : 368612982
DataCacheMiss/sec : 546233

MemCopy Size : 100
Exec Time in Usec : 1731
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1026
Instruction Cache Access : 736499
Number of Instructions Executed : 736513
Data Cache Miss : 803
InstructionCacheMiss/sec : 592720
Instructions/sec : 425484113
DataCacheMiss/sec : 463893

MemCopy Size : 200
Exec Time in Usec : 2224
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1214
Instruction Cache Access : 1090533
Number of Instructions Executed : 1090547
Data Cache Miss : 916
InstructionCacheMiss/sec : 545863
Instructions/sec : 490353866
DataCacheMiss/sec : 411870

MemCopy Size : 500
Exec Time in Usec : 3267
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 980
Instruction Cache Access : 1956962
Number of Instructions Executed : 1956976
Data Cache Miss : 1278
InstructionCacheMiss/sec : 299969
Instructions/sec : 599013161
DataCacheMiss/sec : 391184

MemCopy Size : 750
Exec Time in Usec : 4600
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1105
Instruction Cache Access : 2991423
Number of Instructions Executed : 2991437
Data Cache Miss : 1480
InstructionCacheMiss/sec : 240217
Instructions/sec : 650312391
DataCacheMiss/sec : 321739

MemCopy Size : 1000
Exec Time in Usec : 4997
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 952
Instruction Cache Access : 3342099
Number of Instructions Executed : 3342113
Data Cache Miss : 1452
InstructionCacheMiss/sec : 190514
Instructions/sec : 668823894
DataCacheMiss/sec : 290574

MemCopy Size : 1250
Exec Time in Usec : 5795
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 892
Instruction Cache Access : 3990559
Number of Instructions Executed : 3990573
Data Cache Miss : 1625
InstructionCacheMiss/sec : 153925
Instructions/sec : 688623468
DataCacheMiss/sec : 280414

MemCopy Size : 1500
Exec Time in Usec : 7204
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1118
Instruction Cache Access : 4989094
Number of Instructions Executed : 4989108
Data Cache Miss : 2839
InstructionCacheMiss/sec : 155191
Instructions/sec : 692546918
DataCacheMiss/sec : 394086

MemCopy Size : 2048
Exec Time in Usec : 11856
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1421
Instruction Cache Access : 8564404
Number of Instructions Executed : 8564418
Data Cache Miss : 4233
InstructionCacheMiss/sec : 119854
Instructions/sec : 722369939
DataCacheMiss/sec : 357034

All tests have passed!!

Memcpy Benchmarking for DDR memory:
Filling up the gBuffers
Sanity checking for PMU counters
Inst Cache Miss: 0
Inst Cache Access: 39
Number of Instructions: 53
Data Cache Miss: 0
Created MasterTask
Created all 15 slaveTasks

Master_task

Master_task -- start sending

MemCopy Size : 0
Exec Time in Usec : 1478
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1236
Instruction Cache Access : 407329
Number of Instructions Executed : 407343
Data Cache Miss : 955
InstructionCacheMiss/sec : 836265
Instructions/sec : 275604194
DataCacheMiss/sec : 646143

MemCopy Size : 50
Exec Time in Usec : 1598
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1134
Instruction Cache Access : 563776
Number of Instructions Executed : 563790
Data Cache Miss : 809
InstructionCacheMiss/sec : 709637
Instructions/sec : 352809762
DataCacheMiss/sec : 506257

MemCopy Size : 100
Exec Time in Usec : 1918
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1148
Instruction Cache Access : 808769
Number of Instructions Executed : 808783
Data Cache Miss : 841
InstructionCacheMiss/sec : 598540
Instructions/sec : 421680396
DataCacheMiss/sec : 438477

MemCopy Size : 200
Exec Time in Usec : 2259
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1148
Instruction Cache Access : 1073508
Number of Instructions Executed : 1073522
Data Cache Miss : 904
InstructionCacheMiss/sec : 508189
Instructions/sec : 475220008
DataCacheMiss/sec : 400177

MemCopy Size : 500
Exec Time in Usec : 3822
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1197
Instruction Cache Access : 2270043
Number of Instructions Executed : 2270057
Data Cache Miss : 1593
InstructionCacheMiss/sec : 313186
Instructions/sec : 593944793
DataCacheMiss/sec : 416797

MemCopy Size : 750
Exec Time in Usec : 4635
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1066
Instruction Cache Access : 2959640
Number of Instructions Executed : 2959654
Data Cache Miss : 1605
InstructionCacheMiss/sec : 229989
Instructions/sec : 638544552
DataCacheMiss/sec : 346278

MemCopy Size : 1000
Exec Time in Usec : 5487
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1100
Instruction Cache Access : 3642493
Number of Instructions Executed : 3642507
Data Cache Miss : 1752
InstructionCacheMiss/sec : 200473
Instructions/sec : 663843083
DataCacheMiss/sec : 319300

MemCopy Size : 1250
Exec Time in Usec : 6905
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1091
Instruction Cache Access : 4762435
Number of Instructions Executed : 4762449
Data Cache Miss : 1922
InstructionCacheMiss/sec : 158001
Instructions/sec : 689710209
DataCacheMiss/sec : 278349

MemCopy Size : 1500
Exec Time in Usec : 7796
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1018
Instruction Cache Access : 5446929
Number of Instructions Executed : 5446943
Data Cache Miss : 2808
InstructionCacheMiss/sec : 130579
Instructions/sec : 698684325
DataCacheMiss/sec : 360184

MemCopy Size : 2048
Exec Time in Usec : 10037
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1038
Instruction Cache Access : 7203928
Number of Instructions Executed : 7203942
Data Cache Miss : 3398
InstructionCacheMiss/sec : 103417
Instructions/sec : 717738567
DataCacheMiss/sec : 338547

All tests have passed!!

\endcode

\elseif SOC_AM62PX

**mcu-r5f core:**
\code

Memcpy Benchmarking for MSRAM memory:
Filling up the gBuffers
Sanity checking for PMU counters
Inst Cache Miss: 1
Inst Cache Access: 0
Number of instructions: 39
Data Cache Miss: 0
Created MasterTask
Created all 15 slaveTasks

Master_task

Master_task -- start sending

MemCopy Size : 0
Exec Time in Usec : 1000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1007
Instruction Cache Access : 769
Number of Instructions Executed : 389890
Data Cache Miss : 1007
InstructionCacheMiss/sec : 1006999
Instructions/sec : 389890000
DataCacheMiss/sec : 769000

MemCopy Size : 50
Exec Time in Usec : 1000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 968
Instruction Cache Access : 809
Number of Instructions Executed : 593390
Data Cache Miss : 968
InstructionCacheMiss/sec : 968000
Instructions/sec : 593390000
DataCacheMiss/sec : 809000

MemCopy Size : 100
Exec Time in Usec : 2000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 917
Instruction Cache Access : 969
Number of Instructions Executed : 755184
Data Cache Miss : 917
InstructionCacheMiss/sec : 458500
Instructions/sec : 377592000
DataCacheMiss/sec : 484500

MemCopy Size : 200
Exec Time in Usec : 2000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1122
Instruction Cache Access : 1251
Number of Instructions Executed : 1135437
Data Cache Miss : 1122
InstructionCacheMiss/sec : 561000
Instructions/sec : 567718500
DataCacheMiss/sec : 625500

MemCopy Size : 500
Exec Time in Usec : 3000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 900
Instruction Cache Access : 1285
Number of Instructions Executed : 2002335
Data Cache Miss : 900
InstructionCacheMiss/sec : 300000
Instructions/sec : 667445000
DataCacheMiss/sec : 428333

MemCopy Size : 750
Exec Time in Usec : 5000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1017
Instruction Cache Access : 1623
Number of Instructions Executed : 2952423
Data Cache Miss : 1017
InstructionCacheMiss/sec : 203400
Instructions/sec : 590484600
DataCacheMiss/sec : 324600

MemCopy Size : 1000
Exec Time in Usec : 5000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1156
Instruction Cache Access : 2385
Number of Instructions Executed : 3467601
Data Cache Miss : 1156
InstructionCacheMiss/sec : 231200
Instructions/sec : 693520200
DataCacheMiss/sec : 477000

MemCopy Size : 1250
Exec Time in Usec : 6000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1082
Instruction Cache Access : 2643
Number of Instructions Executed : 3839319
Data Cache Miss : 1082
InstructionCacheMiss/sec : 180333
Instructions/sec : 639886500
DataCacheMiss/sec : 440500

MemCopy Size : 1500
Exec Time in Usec : 8000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1461
Instruction Cache Access : 4058
Number of Instructions Executed : 5525335
Data Cache Miss : 1461
InstructionCacheMiss/sec : 182625
Instructions/sec : 690666875
DataCacheMiss/sec : 507250

MemCopy Size : 2048
Exec Time in Usec : 12000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1847
Instruction Cache Access : 6671
Number of Instructions Executed : 8573229
Data Cache Miss : 1847
InstructionCacheMiss/sec : 153916
Instructions/sec : 714435750
DataCacheMiss/sec : 555916

All tests have passed!!

Memcpy Benchmarking for DDR memory:
Filling up the gBuffers
Sanity checking for PMU counters
Inst Cache Miss: 1
Inst Cache Access: 0
Number of instructions: 39
Data Cache Miss: 0
Created MasterTask
Created all 15 slaveTasks

Master_task

Master_task -- start sending

MemCopy Size : 0
Exec Time in Usec : 2000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1329
Instruction Cache Access : 1268
Number of Instructions Executed : 427512
Data Cache Miss : 1329
InstructionCacheMiss/sec : 664500
Instructions/sec : 213756000
DataCacheMiss/sec : 634000

MemCopy Size : 50
Exec Time in Usec : 1000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1119
Instruction Cache Access : 1080
Number of Instructions Executed : 577012
Data Cache Miss : 1119
InstructionCacheMiss/sec : 1119000
Instructions/sec : 577012000
DataCacheMiss/sec : 1080000

MemCopy Size : 100
Exec Time in Usec : 2000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1031
Instruction Cache Access : 849
Number of Instructions Executed : 824925
Data Cache Miss : 1031
InstructionCacheMiss/sec : 515499
Instructions/sec : 412462500
DataCacheMiss/sec : 424500

MemCopy Size : 200
Exec Time in Usec : 3000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1221
Instruction Cache Access : 1249
Number of Instructions Executed : 1092852
Data Cache Miss : 1221
InstructionCacheMiss/sec : 407000
Instructions/sec : 364284000
DataCacheMiss/sec : 416333

MemCopy Size : 500
Exec Time in Usec : 4000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1774
Instruction Cache Access : 2465
Number of Instructions Executed : 2196190
Data Cache Miss : 1774
InstructionCacheMiss/sec : 443500
Instructions/sec : 549047500
DataCacheMiss/sec : 616250

MemCopy Size : 750
Exec Time in Usec : 6000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 2157
Instruction Cache Access : 3188
Number of Instructions Executed : 3376415
Data Cache Miss : 2157
InstructionCacheMiss/sec : 359500
Instructions/sec : 562735833
DataCacheMiss/sec : 531333

MemCopy Size : 1000
Exec Time in Usec : 7000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 2140
Instruction Cache Access : 3848
Number of Instructions Executed : 3822753
Data Cache Miss : 2140
InstructionCacheMiss/sec : 305714
Instructions/sec : 546107571
DataCacheMiss/sec : 549714

MemCopy Size : 1250
Exec Time in Usec : 7000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1611
Instruction Cache Access : 3491
Number of Instructions Executed : 4862341
Data Cache Miss : 1611
InstructionCacheMiss/sec : 230142
Instructions/sec : 694620142
DataCacheMiss/sec : 498714

MemCopy Size : 1500
Exec Time in Usec : 9000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 2191
Instruction Cache Access : 4338
Number of Instructions Executed : 5407615
Data Cache Miss : 2191
InstructionCacheMiss/sec : 243444
Instructions/sec : 600846111
DataCacheMiss/sec : 482000

MemCopy Size : 2048
Exec Time in Usec : 11000
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 2485
Instruction Cache Access : 6828
Number of Instructions Executed : 7091380
Data Cache Miss : 2485
InstructionCacheMiss/sec : 225909
Instructions/sec : 644670909
DataCacheMiss/sec : 620727

All tests have passed!!

\endcode

**wkup-r5f core:**
\code

Memcpy Benchmarking for MSRAM memory:
Filling up the gBuffers
Sanity checking for PMU counters
Inst Cache Miss: 1
Inst Cache Access: 0
Number of instructions: 39
Data Cache Miss: 0
Created MasterTask
Created all 15 slaveTasks

Master_task

Master_task -- start sending

MemCopy Size : 0
Exec Time in Usec : 1362
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1121
Instruction Cache Access : 892
Number of Instructions Executed : 398224
Data Cache Miss : 1121
InstructionCacheMiss/sec : 823054
Instructions/sec : 292381791
DataCacheMiss/sec : 654919

MemCopy Size : 50
Exec Time in Usec : 1643
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1261
Instruction Cache Access : 940
Number of Instructions Executed : 602242
Data Cache Miss : 1261
InstructionCacheMiss/sec : 767498
Instructions/sec : 366550213
DataCacheMiss/sec : 572124

MemCopy Size : 100
Exec Time in Usec : 1732
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1026
Instruction Cache Access : 803
Number of Instructions Executed : 736510
Data Cache Miss : 1026
InstructionCacheMiss/sec : 592378
Instructions/sec : 425236720
DataCacheMiss/sec : 463625

MemCopy Size : 200
Exec Time in Usec : 2219
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1188
Instruction Cache Access : 934
Number of Instructions Executed : 1090461
Data Cache Miss : 1188
InstructionCacheMiss/sec : 535376
Instructions/sec : 491420009
DataCacheMiss/sec : 420910

MemCopy Size : 500
Exec Time in Usec : 3383
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1173
Instruction Cache Access : 1237
Number of Instructions Executed : 1984290
Data Cache Miss : 1173
InstructionCacheMiss/sec : 346733
Instructions/sec : 586547443
DataCacheMiss/sec : 365651

MemCopy Size : 750
Exec Time in Usec : 5290
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 2058
Instruction Cache Access : 2973
Number of Instructions Executed : 3127838
Data Cache Miss : 2058
InstructionCacheMiss/sec : 389035
Instructions/sec : 591273724
DataCacheMiss/sec : 562003

MemCopy Size : 1000
Exec Time in Usec : 5559
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1807
Instruction Cache Access : 2678
Number of Instructions Executed : 3454512
Data Cache Miss : 1807
InstructionCacheMiss/sec : 325058
Instructions/sec : 621426875
DataCacheMiss/sec : 481741

MemCopy Size : 1250
Exec Time in Usec : 6219
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1546
Instruction Cache Access : 2502
Number of Instructions Executed : 4075249
Data Cache Miss : 1546
InstructionCacheMiss/sec : 248593
Instructions/sec : 655290078
DataCacheMiss/sec : 402315

MemCopy Size : 1500
Exec Time in Usec : 8106
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 2456
Instruction Cache Access : 4173
Number of Instructions Executed : 5180228
Data Cache Miss : 2456
InstructionCacheMiss/sec : 302985
Instructions/sec : 639060942
DataCacheMiss/sec : 514803

MemCopy Size : 2048
Exec Time in Usec : 13563
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 3837
Instruction Cache Access : 8611
Number of Instructions Executed : 8891953
Data Cache Miss : 3837
InstructionCacheMiss/sec : 282902
Instructions/sec : 655603701
DataCacheMiss/sec : 634889

All tests have passed!!

Memcpy Benchmarking for DDR memory:
Filling up the gBuffers
Sanity checking for PMU counters
Inst Cache Miss: 1
Inst Cache Access: 0
Number of instructions: 39
Data Cache Miss: 0
Created MasterTask
Created all 15 slaveTasks

Master_task

Master_task -- start sending

MemCopy Size : 0
Exec Time in Usec : 1634
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1344
Instruction Cache Access : 1219
Number of Instructions Executed : 434602
Data Cache Miss : 1344
InstructionCacheMiss/sec : 822521
Instructions/sec : 265974296
DataCacheMiss/sec : 746022

MemCopy Size : 50
Exec Time in Usec : 1919
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1511
Instruction Cache Access : 1338
Number of Instructions Executed : 618342
Data Cache Miss : 1511
InstructionCacheMiss/sec : 787389
Instructions/sec : 322220948
DataCacheMiss/sec : 697238

MemCopy Size : 100
Exec Time in Usec : 1934
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1111
Instruction Cache Access : 858
Number of Instructions Executed : 808785
Data Cache Miss : 1111
InstructionCacheMiss/sec : 574457
Instructions/sec : 418192864
DataCacheMiss/sec : 443640

MemCopy Size : 200
Exec Time in Usec : 2607
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1560
Instruction Cache Access : 1530
Number of Instructions Executed : 1131344
Data Cache Miss : 1560
InstructionCacheMiss/sec : 598388
Instructions/sec : 433963943
DataCacheMiss/sec : 586881

MemCopy Size : 500
Exec Time in Usec : 4109
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1561
Instruction Cache Access : 1687
Number of Instructions Executed : 2324631
Data Cache Miss : 1561
InstructionCacheMiss/sec : 379897
Instructions/sec : 565741299
DataCacheMiss/sec : 410562

MemCopy Size : 750
Exec Time in Usec : 4962
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1463
Instruction Cache Access : 2142
Number of Instructions Executed : 3014239
Data Cache Miss : 1463
InstructionCacheMiss/sec : 294840
Instructions/sec : 607464530
DataCacheMiss/sec : 431680

MemCopy Size : 1000
Exec Time in Usec : 6407
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 2136
Instruction Cache Access : 3446
Number of Instructions Executed : 3806191
Data Cache Miss : 2136
InstructionCacheMiss/sec : 333385
Instructions/sec : 594067582
DataCacheMiss/sec : 537849

MemCopy Size : 1250
Exec Time in Usec : 8043
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 2463
Instruction Cache Access : 4382
Number of Instructions Executed : 4956686
Data Cache Miss : 2463
InstructionCacheMiss/sec : 306229
Instructions/sec : 616273281
DataCacheMiss/sec : 544821

MemCopy Size : 1500
Exec Time in Usec : 8529
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 1996
Instruction Cache Access : 3493
Number of Instructions Executed : 5586480
Data Cache Miss : 1996
InstructionCacheMiss/sec : 234025
Instructions/sec : 654998241
DataCacheMiss/sec : 409543

MemCopy Size : 2048
Exec Time in Usec : 11827
Iteration : 1
Task Calls : 500
Instruction Cache Miss : 3322
Instruction Cache Access : 7329
Number of Instructions Executed : 7504336
Data Cache Miss : 3322
InstructionCacheMiss/sec : 280882
Instructions/sec : 634508835
DataCacheMiss/sec : 619683

All tests have passed!!

\endcode
\endif
