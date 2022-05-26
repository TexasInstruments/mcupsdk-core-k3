#--------------------------------------------------------------------
# Tool to generate tq_cli commands for linking Qmetry test cases to JIRA requirements
# Author: Vibha Pant (a0230241@ti.com)
# Pre-requisites: Install python, qmetry cli, foqus cli, xlrd python package
# Step 1: Use Import Option in JIRA to create Test cases using csv format of "input.xlsx"
# Step 2: Update JIRA IDs in "input.xlsx"
# Step 3: Use the script to link test steps and parent requirements to the created Test cases
# Input File : "input.xlsx" : excel with following details:
#               Column A : Qmetry test case JIRA Id,
#               Column I : Requirement IDs to be mapped to test cases
#               Column J : Step Summary
#               Column K : Step Data
#               Column L : Step Expected Result
# Output Files: Commands_step.txt : with commands to add test step to test cases
#             : Commands.txt : with commands to add requirements to test cases
# Also this script directly sends the commands to command prompt for linking
# Usage : python qmetry_req_step_mapping.py testcase_import_template.xlsx
# Date  : 10-Feb-2019
#
# Please report enhancements/issues to the author. Thanks!
#--------------------------------------------------------------------
import excelrd
import os
import sys

id = []
summary =[]
data = []
result =[]
def excelread(FILENAME):
    f1 = open('file_JIRA_id.txt', 'w')
    f2 = open('file_reqmap.txt', 'w')
    f3 = open('file_step_summary.txt', 'w')
    f4 = open('file_step_data.txt', 'w')
    f5 = open('file_step_result.txt', 'w')
    wb = excelrd.open_workbook(FILENAME)
    sheet = wb.sheet_by_index(0)
    sheet.cell_value(0, 0)
    #read 2 columns from excel into files
    for i in range(sheet.nrows):
        if (i != 0):
            #jira ids
            f1.write(sheet.cell_value(i,0)+"\n")
            #req to be mapped
            f2.write((sheet.cell_value(i,8)+"\n").lstrip(":"))
            #test step
            f3.write((sheet.cell_value(i,9)+"\n"))
            f4.write((sheet.cell_value(i,10)+"\n"))
            f5.write((sheet.cell_value(i,11)+"\n"))
    f1.close()
    f2.close()
    f3.close()
    f4.close()
    f5.close()

#req map
def req_map():
    f1 = open('file_JIRA_id.txt', 'r')
    f2 = open('file_reqmap.txt', 'r')
    f4 = open('CHECK.txt', 'w')
    f5 = open('Commands.txt', 'w')
    strn= []
    strn1 =[]
    for line1 in f1:
        if line1 != '\n':
            id.append(line1)
    len2=len(id)
    i=0
    for line in f2.readlines():
        if line != '\n':
            line = line.replace(":"," -Art "+id[i]+"\n")
            strn.append(line)
            i =i+1

    x= len(strn)
    for i in range(x):
        #print strn[i]
        f4.write((strn[i]))

    f4.close()
    f3 = open('CHECK.txt', 'r')
    for line in f3.readlines():
        #print line
        if len(line.strip()) >= 1:
            line = "ti_qcli -Ar " + line
            strn1.append(line)
            #print strn1

    y= len(strn1)
    for i in range(y):
        os.system((strn1[i]))
        f5.write((strn1[i]))
    f1.close()
    f2.close()
    f3.close()
    f5.close()
    os.remove("CHECK.txt")

#test step creation
def step_create():
    f1 = open('file_step_summary.txt', 'r')
    f2 = open('file_step_data.txt', 'r')
    f3 = open('file_step_result.txt', 'r')
    f4 = open('Commands_step.txt', 'w')
    strn= []
    strn1 =[]
    for line1 in f1:
        if line1 != '\n':
            summary.append(line1)
    for line2 in f2:
        if line2 != '\n':
            data.append(line2)
    for line3 in f3:
        if line3 != '\n':
            result.append(line3)
    len2=len(id)
    i=0
    for i in range(len2):
            line = "ti_qcli -ts \""+id[i].rstrip("\n")+"\" -tsD \""+data[i].rstrip("\n")+"\" -tsS \""+summary[i].rstrip("\n")+"\" -tsE \""+result[i].rstrip("\n")+ "\"\n"
            strn.append(line)

    x= len(strn)
    for i in range(x):
        os.system(strn[i])
        f4.write((strn[i]))

    f4.close()


#main
#read the columns from excel
FILENAME = sys.argv[1]
excelread(FILENAME)
#based on columns read from excel, update commands
req_map()
step_create()
os.remove('file_JIRA_id.txt')
os.remove('file_reqmap.txt')
os.remove('file_step_summary.txt')
os.remove('file_step_data.txt')
os.remove('file_step_result.txt')
