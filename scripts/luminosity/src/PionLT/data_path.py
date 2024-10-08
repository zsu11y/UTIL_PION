#! /usr/bin/python
#
# Description: Grabs lumi data from corresponding csv depending on run setting. Then plots the yields and creates a comprehensive table.
# Variables calculated: current, rate_HMS, rate_SHMS, sent_edtm_PS, uncern_HMS_evts_scaler, uncern_SHMS_evts_scaler, uncern_HMS_evts_notrack, uncern_SHMS_evts_notrack, uncern_HMS_evts_track, uncern_SHMS_evts_track
# ================================================================
# Time-stamp: "2022-06-27 02:10:13 trottar"
# ================================================================
#
# Author:  Richard L. Trotta III <trotta@cua.edu>
#
# Update - Nathan Heinrich (heinricn)
# Reworked Paths so that Data for PionLT experiment would be read in instead
#

def get_file(inp_name,SCRIPTPATH):
    '''
    Grab proper lumi data file
    '''
    
    # Depending on input, the corresponding data setting csv data will be grabbed
    if "9-2" in inp_name:
        if "pt1" in inp_name.lower():
            if "LH2" in inp_name.upper():
                target = "LH2"
                inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi9-2/pt1/lumi_data_LH2.csv"
                out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi9-2/pt1/yield_data_LH2.csv"
                print("\nGrabbing input...\n\n%s" % str(inp_f))
            if "LD2" in inp_name.upper():
                target = "LD2"
                inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi9-2/pt1/lumi_data_LD2.csv"
                out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi9-2/pt1/yield_data_LD2.csv"
                print("\nGrabbing input...\n\n%s" % str(inp_f))
            if "C" in inp_name:
                target = "carbon"
                inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi9-2/pt1/lumi_data_Carbon.csv"
                out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi9-2/pt1/yield_data_Carbon.csv"
                print("\nGrabbing input...\n\n%s" % str(inp_f))
        if "pt2" in inp_name.lower():
            if "LH2" in inp_name.upper():
                target = "LH2"
                inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi9-2/pt2/lumi_data_LH2.csv"
                out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi9-2/pt2/yield_data_LH2.csv"
                print("\nGrabbing input...\n\n%s" % str(inp_f))
            if "LD2" in inp_name.upper():
                target = "LD2"
                inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi9-2/pt2/lumi_data_LD2.csv"
                out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi9-2/pt2/yield_data_LD2.csv"
                print("\nGrabbing input...\n\n%s" % str(inp_f))
            if "C" in inp_name:
                target = "carbon"
                inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi9-2/pt2/lumi_data_Carbon.csv"
                out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi9-2/pt2/yield_data_Carbon.csv"
                print("\nGrabbing input...\n\n%s" % str(inp_f))
    elif "6-4" in inp_name:
        if "SHMS" in inp_name.upper():
            if "LH2" in inp_name.upper():
                target = "LH2"
                inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi6-4/SHMS/lumi_data_LH2.csv"
                out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi6-4/SHMS/yield_data_LH2.csv"
                print("\nGrabbing input...\n\n%s" % str(inp_f))
            if "LD2" in inp_name.upper():
                target = "LD2"
                inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi6-4/SHMS/lumi_data_LD2.csv"
                out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi6-4/SHMS/yield_data_LD2.csv"
                print("\nGrabbing input...\n\n%s" % str(inp_f))
            if "C" in inp_name:
                target = "carbon"
                inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi6-4/SHMS/lumi_data_Carbon.csv"
                out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi6-4/SHMS/yield_data_Carbon.csv"
                print("\nGrabbing input...\n\n%s" % str(inp_f))
        else:
            if "LH2" in inp_name.upper():
                target = "LH2"
                inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi6-4/HMS/lumi_data_LH2.csv"
                out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi6-4/HMS/yield_data_LH2.csv"
                print("\nGrabbing input...\n\n%s" % str(inp_f))
            if "LD2" in inp_name.upper():
                target = "LD2"
                inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi6-4/HMS/lumi_data_LD2.csv"
                out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi6-4/HMS/yield_data_LD2.csv"
                print("\nGrabbing input...\n\n%s" % str(inp_f))
            if "C" in inp_name:
                target = "carbon"
                inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi6-4/HMS/lumi_data_Carbon.csv"
                out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi6-4/HMS/yield_data_Carbon.csv"
                print("\nGrabbing input...\n\n%s" % str(inp_f))
    #add else if statement for new file created in /u/group/c-pionlt/USERS/zsully/hallc_replay_lt/UTIL_PION/scripts/luminosity/OUTPUTS 
    elif "2022" in inp_name:
        if "SHMS" in inp_name.upper():
            if "LH2" in inp_name.upper():
                    target = "LH2"
                    inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2022/6-4/SHMS/lumi_data_LH2.csv"
                    out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2022/6-4/SHMS/yield_data_LH2.csv"
                    print("\nGrabbing input...\n\n%s" % str(inp_f))
            if "LD2" in inp_name.upper():
                    target = "LD2"
                    inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2022/6-4/SHMS/lumi_data_LD2.csv"
                    out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2022/6-4/SHMS/yield_data_LD2.csv"
                    print("\nGrabbing input...\n\n%s" % str(inp_f))
            if "C" in inp_name:
                    target = "carbon"
                    inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2022/6-4/SHMS/lumi_data_Carbon.csv"
                    out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2022/6-4/SHMS/yield_data_Carbon.csv"
                    print("\nGrabbing input...\n\n%s" % str(inp_f))
        else:
            if "LH2" in inp_name.upper():
                    target = "LH2"
                    inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2022/6-4/HMS/lumi_data_LH2.csv"
                    out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2022/6-4/HMS/yield_data_LH2.csv"
                    print("\nGrabbing input...\n\n%s" % str(inp_f))
            if "LD2" in inp_name.upper():
                    target = "LD2"
                    inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2022/6-4/HMS/lumi_data_LD2.csv"
                    out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2022/6-4/HMS/yield_data_LD2.csv"
                    print("\nGrabbing input...\n\n%s" % str(inp_f))
            if "C" in inp_name:
                    target = "carbon"
                    inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2022/6-4/HMS/lumi_data_Carbon.csv"
                    out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2022/6-4/HMS/yield_data_Carbon.csv"
                    print("\nGrabbing input...\n\n%s" % str(inp_f))
    elif "2021" in inp_name:
        if "pt1" in inp_name.lower(): #add if conditionals such that it will output a csv file to the corresponding beam energy directories
            if "LH2" in inp_name.upper():
                    target = "LH2"
                    inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2021/pt1/lumi_data_LH2.csv"
                    out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2021/pt1/yield_data_LH2.csv"
                    print("\nGrabbing input...\n\n%s" % str(inp_f))
            if "LD2" in inp_name.upper():
                    target = "LD2"
                    inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2021/pt1/lumi_data_LD2.csv"
                    out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2021/pt1/yield_data_LD2.csv"
                    print("\nGrabbing input...\n\n%s" % str(inp_f))
            if "C" in inp_name:
                    target = "carbon"
                    inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2021/pt1/lumi_data_Carbon.csv"
                    out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2021/pt1/yield_data_Carbon.csv"
                    print("\nGrabbing input...\n\n%s" % str(inp_f))
        if "pt2" in inp_name.lower():
            if "LH2" in inp_name.upper():
                    target = "LH2"
                    inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2021/pt2/lumi_data_LH2.csv"
                    out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2021/pt2/yield_data_LH2.csv"
                    print("\nGrabbing input...\n\n%s" % str(inp_f))
            if "LD2" in inp_name.upper():
                    target = "LD2"
                    inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2021/pt2/lumi_data_LD2.csv"
                    out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2021/pt2/yield_data_LD2.csv"
                    print("\nGrabbing input...\n\n%s" % str(inp_f))
            if "C" in inp_name:
                    target = "carbon"
                    inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2021/pt2/lumi_data_Carbon.csv"
                    out_f = SCRIPTPATH+"/luminosity/OUTPUTS/Lumi2021/pt2/yield_data_Carbon.csv"
                    print("\nGrabbing input...\n\n%s" % str(inp_f))
    else:
        target = "carbon"
        inp_f = SCRIPTPATH+"/luminosity/OUTPUTS/lumi_data.csv"
        out_f = SCRIPTPATH+"/luminosity/OUTPUTS/yield_data.csv"
        print("\nError: Invalid input...\nGrabbing default input...\n\n%s" % str(inp_f))
    
    
    
    
    
    return [target, inp_f,out_f]
