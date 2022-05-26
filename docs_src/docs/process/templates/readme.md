# Requirement Import

1. Fill the requirement details in the requirement_import_template.xlsx

2. Save the excel as .csv delimited with , option

3. Open the CSV file and remove empty and dummy lines with just , and save the file

4. Login to JIRA: jira.itg.ti.com

5. Go to Issues -> "Import Issues from CSV" option

6. Click Browse and provide the CSV file

7. Select "Use an existing configuration file" and provide the "requirement_import_config.txt" file as input

8. Click Next and Select "MCUSDK" as project and click Next

9. Review the field mapping. If more Platform columns are added, ensure to enable the extra platform columns

10. Click Next and again review the various field value mapping

11. Click  "Validate" to check for any warnings and errors

12. In case of warnings/errors, fix them and restart the same procedure

13. Click Import

14. Review the created issue list

# Testcase Import

1. Fill the testcase details in the testcase_import_template.xlsx

2. Follow steps 2 to 14 of "Requirement Import" steps with configuration file as testcase_import_config.txt instead

3. The above step doesn't map some of the fields like step data. Follow next step to do these as well

4. Copy the created issue ID to the "JIRA ID" column of the excel sheet

5. One time setup

    - Install JIRA QCLI as provided in https://confluence.itg.ti.com/display/JKB/Qmetry+Process+or+how+to+write+and+execute+test+cases
    - pip install excelrd

6. Run below command

    python qmetry_req_step_mapping.py testcase_import_template.xlsx

7. Check the testcases in JIRA and see if they are mapped to the right requirements
