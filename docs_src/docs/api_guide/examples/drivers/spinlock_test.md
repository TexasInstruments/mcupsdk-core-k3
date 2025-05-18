# Spinlock Test {#EXAMPLES_DRIVERS_SPINLOCK_TEST}

[TOC]

# Introduction

This example application illustrates the SPINLOCK functionality by acquiring and releasing different locks from the same core.
The Spinlock module provides hardware assistance for synchronizing the processes running on multiple
processors in the device.
The SPINLOCK example application provides 2 test cases -

 - First, to aqcuire all the 256 locks.
 - Followed by resetting the SPINLOCK module, to test the functionality of releasing locks of both kinds - taken and free.

# Supported Combinations {#EXAMPLES_DRIVERS_SPINLOCK_TEST_COMBOS}

 Parameter      | Value
 ---------------|-----------
 CPU + OS       | mcu-r5fss0-0 nortos
 ^              | wkup-r5fss0-0 nortos
 ^              | main-r5fss0-0 nortos
 ^              | c75ss0-0 freertos
 ^              | c75ss1-0 freertos
 Toolchain      | ti-arm-clang, ti-c7000
 Boards         | @VAR_BOARD_NAME_LOWER
 Example folder | examples/drivers/spinlock/spinlock_test

# Steps to Run the Example

<!-- - **When using CCS projects to build**, import the CCS project for the required combination
  and build it using the CCS project menu (see \ref CCS_PROJECTS_PAGE). -->
- **When using makefiles to build**, note the required combination and build using
  make command (see \ref MAKEFILE_BUILD_PAGE)
- Launch a CCS debug session and run the executable, see \ref CCS_LAUNCH_PAGE
\cond SOC_AM62X
\attention As the wake-up R5 is the device manager, it needs to be started by the SBL. So it can not be loaded through CCS. It should be flashed and booted through SBL.

- Refer \ref GETTING_STARTED_FLASH for flashing the application.
\endcond
# See Also

\ref DRIVERS_SPINLOCK_PAGE

# Sample Output

Shown below is a sample output when the application is run,

\code

On
Spinlock App

 acquired lock number:0
 acquired lock number:1
 acquired lock number:2
 acquired lock number:3
 acquired lock number:4
 acquired lock number:5
 acquired lock number:6
 acquired lock number:7
 acquired lock number:8
 acquired lock number:9
 acquired lock number:10
 acquired lock number:11
 acquired lock number:12
 acquired lock number:13
 acquired lock number:14
 acquired lock number:15
 acquired lock number:16
 acquired lock number:17
 acquired lock number:18
 acquired lock number:19
 acquired lock number:20
 acquired lock number:21
 acquired lock number:22
 acquired lock number:23
 acquired lock number:24
 acquired lock number:25
 acquired lock number:26
 acquired lock number:27
 acquired lock number:28
 acquired lock number:29
 acquired lock number:30
 acquired lock number:31
 acquired lock number:32
 acquired lock number:33
 acquired lock number:34
 acquired lock number:35
 acquired lock number:36
 acquired lock number:37
 acquired lock number:38
 acquired lock number:39
 acquired lock number:40
 acquired lock number:41
 acquired lock number:42
 acquired lock number:43
 acquired lock number:44
 acquired lock number:45
 acquired lock number:46
 acquired lock number:47
 acquired lock number:48
 acquired lock number:49
 acquired lock number:50
 acquired lock number:51
 acquired lock number:52
 acquired lock number:53
 acquired lock number:54
 acquired lock number:55
 acquired lock number:56
 acquired lock number:57
 acquired lock number:58
 acquired lock number:59
 acquired lock number:60
 acquired lock number:61
 acquired lock number:62
 acquired lock number:63
 acquired lock number:64
 acquired lock number:65
 acquired lock number:66
 acquired lock number:67
 acquired lock number:68
 acquired lock number:69
 acquired lock number:70
 acquired lock number:71
 acquired lock number:72
 acquired lock number:73
 acquired lock number:74
 acquired lock number:75
 acquired lock number:76
 acquired lock number:77
 acquired lock number:78
 acquired lock number:79
 acquired lock number:80
 acquired lock number:81
 acquired lock number:82
 acquired lock number:83
 acquired lock number:84
 acquired lock number:85
 acquired lock number:86
 acquired lock number:87
 acquired lock number:88
 acquired lock number:89
 acquired lock number:90
 acquired lock number:91
 acquired lock number:92
 acquired lock number:93
 acquired lock number:94
 acquired lock number:95
 acquired lock number:96
 acquired lock number:97
 acquired lock number:98
 acquired lock number:99
 acquired lock number:100
 acquired lock number:101
 acquired lock number:102
 acquired lock number:103
 acquired lock number:104
 acquired lock number:105
 acquired lock number:106
 acquired lock number:107
 acquired lock number:108
 acquired lock number:109
 acquired lock number:110
 acquired lock number:111
 acquired lock number:112
 acquired lock number:113
 acquired lock number:114
 acquired lock number:115
 acquired lock number:116
 acquired lock number:117
 acquired lock number:118
 acquired lock number:119
 acquired lock number:120
 acquired lock number:121
 acquired lock number:122
 acquired lock number:123
 acquired lock number:124
 acquired lock number:125
 acquired lock number:126
 acquired lock number:127
 acquired lock number:128
 acquired lock number:129
 acquired lock number:130
 acquired lock number:131
 acquired lock number:132
 acquired lock number:133
 acquired lock number:134
 acquired lock number:135
 acquired lock number:136
 acquired lock number:137
 acquired lock number:138
 acquired lock number:139
 acquired lock number:140
 acquired lock number:141
 acquired lock number:142
 acquired lock number:143
 acquired lock number:144
 acquired lock number:145
 acquired lock number:146
 acquired lock number:147
 acquired lock number:148
 acquired lock number:149
 acquired lock number:150
 acquired lock number:151
 acquired lock number:152
 acquired lock number:153
 acquired lock number:154
 acquired lock number:155
 acquired lock number:156
 acquired lock number:157
 acquired lock number:158
 acquired lock number:159
 acquired lock number:160
 acquired lock number:161
 acquired lock number:162
 acquired lock number:163
 acquired lock number:164
 acquired lock number:165
 acquired lock number:166
 acquired lock number:167
 acquired lock number:168
 acquired lock number:169
 acquired lock number:170
 acquired lock number:171
 acquired lock number:172
 acquired lock number:173
 acquired lock number:174
 acquired lock number:175
 acquired lock number:176
 acquired lock number:177
 acquired lock number:178
 acquired lock number:179
 acquired lock number:180
 acquired lock number:181
 acquired lock number:182
 acquired lock number:183
 acquired lock number:184
 acquired lock number:185
 acquired lock number:186
 acquired lock number:187
 acquired lock number:188
 acquired lock number:189
 acquired lock number:190
 acquired lock number:191
 acquired lock number:192
 acquired lock number:193
 acquired lock number:194
 acquired lock number:195
 acquired lock number:196
 acquired lock number:197
 acquired lock number:198
 acquired lock number:199
 acquired lock number:200
 acquired lock number:201
 acquired lock number:202
 acquired lock number:203
 acquired lock number:204
 acquired lock number:205
 acquired lock number:206
 acquired lock number:207
 acquired lock number:208
 acquired lock number:209
 acquired lock number:210
 acquired lock number:211
 acquired lock number:212
 acquired lock number:213
 acquired lock number:214
 acquired lock number:215
 acquired lock number:216
 acquired lock number:217
 acquired lock number:218
 acquired lock number:219
 acquired lock number:220
 acquired lock number:221
 acquired lock number:222
 acquired lock number:223
 acquired lock number:224
 acquired lock number:225
 acquired lock number:226
 acquired lock number:227
 acquired lock number:228
 acquired lock number:229
 acquired lock number:230
 acquired lock number:231
 acquired lock number:232
 acquired lock number:233
 acquired lock number:234
 acquired lock number:235
 acquired lock number:236
 acquired lock number:237
 acquired lock number:238
 acquired lock number:239
 acquired lock number:240
 acquired lock number:241
 acquired lock number:242
 acquired lock number:243
 acquired lock number:244
 acquired lock number:245
 acquired lock number:246
 acquired lock number:247
 acquired lock number:248
 acquired lock number:249
 acquired lock number:250
 acquired lock number:251
 acquired lock number:252
 acquired lock number:253
 acquired lock number:254
 acquired lock number:255
Acquired all available locks. Mark test as Pass.
This testcase requires board power cycle.

Spinlock test for freeing the lock
Case 1: Releasing a taken lock
Lock released successfully
Case 2: Releasing a free lock
                             Lock released successfully
Released locks successfully. Mark test as Pass.

All tests have passed..

\endcode
