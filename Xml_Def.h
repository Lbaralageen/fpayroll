// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

#ifndef Xml_DefHPP
#define Xml_DefHPP
#include <SysInit.hpp>
#include <System.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml_def
{
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
#define NODE_TAG_Default   "Default"
#define NODE_TAG_History	"History"
#define NODE_TAG_Plug_in	"Plug-in"

#define NODE_TAG_Unit       "Unit"
#define NODE_TAG_Code       "Code"
#define NODE_TAG_Screen    "Screen"
#define NODE_TAG_Station   "Station"
#define NODE_TAG_Field     "Field"
#define NODE_TAG_Project   "Project"
#define NODE_TAG_Projects  "Projects"
#define NODE_TAG_Remote    "Remote"
#define NODE_TAG_Index     "Index"
#define NODE_TAG_Options   "Options"
#define NODE_TAG_Grid      "Grid"
#define NODE_TAG_Well      "Well"
#define NODE_TAG_Control   "Control"
#define NODE_TAG_Item      "Item"
#define NODE_TAG_Current   "Current"
#define NODE_TAG_Engine    "Engine"
#define NODE_TAG_Group     "Group" 
#define NODE_TAG_System    "System" 
#define NODE_TAG_Template  "Template"
#define NODE_TAG_Field     "Field"
#define NODE_TAG_Param     "Param"
#define NODE_TAG_Input     "Input"
#define NODE_TAG_Output    "Output"
#define NODE_TAG_Database  "Database"
#define NODE_TAG_Chemical  "Chemical"
#define NODE_TAG_Title     "Title" 
#define NODE_TAG_Path      "Path"
#define NODE_TAG_Dir       "Dir"
#define NODE_TAG_County    "County" 
#define NODE_TAG_Instance  "Instance"
#define NODE_TAG_Table     "Table"
#define NODE_TAG_Province   "Province"
#define NODE_TAG_Installation  "Installation"
#define NODE_TAG_Line      "Line"
#define NODE_TAG_Drive      "Drive"
#define NODE_TAG_Copy       "Copy"
#define NODE_TAG_Data       "Data"
#define NODE_TAG_Version    "Version"
#define NODE_TAG_Type       "Type"
#define NODE_TAG_Units      "Units"
#define NODE_TAG_Category   "Category"
#define NODE_TAG_Local      "Local"
#define NODE_TAG_Manager    "Manager"
#define NODE_TAG_Client     "Client"
#define NODE_TAG_Staff      "Staff"
#define NODE_TAG_Coordinate "Coordinate"
#define NODE_TAG_List       "List"

// SQL
#define NODE_TAG_SQL       "SQL"
#define ATTR_TAG_STRING    "STRING"
#define ATTR_TAG_PHONE     "PHONE"
#define ATTR_TAG_VARCHAR   "VARCHAR"
#define ATTR_TAG_LONG      "LONG"
#define ATTR_TAG_INT       "INT"
#define ATTR_TAG_BOOL      "BOOL"
#define ATTR_TAG_DATE      "DATE"
#define ATTR_TAG_MONEY     "MONEY"

// Vborehole
#define ATTR_TAG_PSION     "PSION"
#define ATTR_TAG_WINCE     "WINCE"


#define ATTR_TAG_Drilling   "Drilling"
#define ATTR_TAG_Top_       "Top_"
#define ATTR_TAG_Top       "Top"
#define ATTR_TAG_Bottom     "Bottom"

#define ATTR_TAG_Coordinate "Coordinate"
#define ATTR_TAG_Map       "Map"
#define ATTR_TAG_Bit       "BIT"
#define ATTR_TAG_Fax       "Fax"
#define ATTR_TAG_State      "State"
#define ATTR_TAG_Hint       "Hint"
#define ATTR_TAG_City       "City"
#define ATTR_TAG_Address    "Address"
#define ATTR_TAG_Email      "Email"
#define ATTR_TAG_Web        "Web"
#define ATTR_TAG_Company   "Company"
#define ATTR_TAG_Scale     "Scale"
#define ATTR_TAG_Remote    "Remote"
#define ATTR_TAG_Metric    "Metric"
#define ATTR_TAG_PSW       "PSW" 
#define ATTR_TAG_Category  "Category"
#define ATTR_TAG_Primary   "Primary"
#define ATTR_TAG_List       "List"
#define ATTR_TAG_Projects  "Projects"
#define ATTR_TAG_Employee  "Employee"
#define ATTR_TAG_Visible   "Visible" 
#define ATTR_TAG_Root      "Root" 
#define ATTR_TAG_Local     "Local"
#define ATTR_TAG_Schedule  "Schedule"
#define ATTR_TAG_Flag      "Flag"
#define ATTR_TAG_Usage     "Usage"
#define ATTR_TAG_Driller   "Driller"
#define ATTR_TAG_Group     "Group"
#define ATTR_TAG_Space     "Space"
#define ATTR_TAG_Jump      "Jump"
#define ATTR_TAG_Geologist "Geologist"
#define ATTR_TAG_Spec      "Spec" 
#define ATTR_TAG_Start     "Start"
#define ATTR_TAG_Parent    "Parent"
#define ATTR_TAG_TProject  "TProject"
#define ATTR_TAG_Street    "Street"
#define ATTR_TAG_Index     "Index"
#define ATTR_TAG_Postbox    "Postbox"
#define ATTR_TAG_UNIQUE    "UNIQUE"
#define ATTR_TAG_General   "General"
#define ATTR_TAG_True      "True"
#define ATTR_TAG_Version   "Version"
#define ATTR_TAG_End_      "End_"
#define ATTR_TAG_INT        "INT"
#define ATTR_TAG_DATE       "DATE"
#define ATTR_TAG_BIT        "BIT"
#define ATTR_TAG_STRING     "STRING"
#define ATTR_TAG_View      "View"
#define ATTR_TAG_Personal   "Personal"
#define ATTR_TAG_Method    "Method"
#define ATTR_TAG_Filling   "Filling"
#define ATTR_TAG_Person     "Person"
#define ATTR_TAG_Height     "Height"
#define ATTR_TAG_ReadOnly   "ReadOnly"
#define ATTR_TAG_Time_Sheet "Time_Sheet"
#define ATTR_TAG_Title      "Title"
#define ATTR_TAG_Middle     "Middle"
#define ATTR_TAG_Diameter  "Diameter"
#define ATTR_TAG_Material  "Material"
#define ATTR_TAG_Formation "Formation"
#define ATTR_TAG_Table     "Table"
#define ATTR_TAG_Left      "Left"
#define ATTR_TAG_Right      "Right"
#define ATTR_TAG_Top       "Top"
#define ATTR_TAG_Structure "Structure"
#define ATTR_TAG_Consistency "Consistency"
#define ATTR_TAG_TSoil     "TSoil" 
#define ATTR_TAG_Wetness   "Wetness"
#define ATTR_TAG_Odour     "Odour"
#define ATTR_TAG_Lithology "Lithology"
#define ATTR_TAG_Penetration "Penetration"
#define ATTR_TAG_First_    "First_"
#define ATTR_TAG_Second_   "Second_"
#define ATTR_TAG_Third     "Third"
#define ATTR_TAG_Slot      "Slot"
#define ATTR_TAG_Screens   "Screens"
#define ATTR_TAG_Moisture  "Moisture"
#define ATTR_TAG_Sampling  "Sampling"
#define ATTR_TAG_Reading   "Reading"
#define ATTR_TAG_Measurment "Measurment"
#define ATTR_TAG_Details   "Details"
#define ATTR_TAG_StaticWater "StaticWater"
#define ATTR_TAG_Casing    "Casing" 
#define ATTR_TAG_Rig       "RIG"
#define ATTR_TAG_Button    "Button"
#define ATTR_TAG_Plot      "Plot"
#define ATTR_TAG_Project   "Project"
#define ATTR_TAG_Extension "Extension"
#define ATTR_TAG_Database  "Database"
#define ATTR_TAG_Manager   "Manager"
#define ATTR_TAG_Client    "Client" 
#define ATTR_TAG_Password  "Password"
#define ATTR_TAG_Location  "Location"
#define ATTR_TAG_User      "User" 
#define ATTR_TAG_Staff     "Staff" 
#define ATTR_TAG_Station   "Station"
#define ATTR_TAG_Template  "Template"
#define ATTR_TAG_Dir       "Dir" 
#define ATTR_TAG_ID        "ID"
#define ATTR_TAG_X         "X"
#define ATTR_TAG_Y         "Y"
#define ATTR_TAG_Elevation "Elevation"
#define ATTR_TAG_County    "County"
#define ATTR_TAG_Instance  "Instance"
#define ATTR_TAG_Modify    "Modify"
#define ATTR_TAG_Formula   "Formula"
#define ATTR_TAG_Separator "Separator"
#define ATTR_TAG_SQL       "SQL"
#define ATTR_TAG_SID       "SID"
#define ATTR_TAG_true      "true"
#define ATTR_TAG_false      "false"

// FieldWorker
#define ATTR_TAG_picklist   "picklist"
#define ATTR_TAG_multipick  "multipick"
#define ATTR_TAG_alpha      "alpha"
#define ATTR_TAG_mixed      "mixed"
#define ATTR_TAG_many       "many"
#define ATTR_TAG_formula    "formula"


// Airflow
#define NODE_TAG_Air       "Air"
#define NODE_TAG_NAPL      "NAPL"

#define ATTR_TAG_Yes    "Yes"
#define ATTR_TAG_No    "No"
#define ATTR_TAG_Supplied    "Supplied"
#define ATTR_TAG_Equilibrium    "Equilibrium"
#define ATTR_TAG_Depth     "Depth"
#define ATTR_TAG_Radius    "Radius"
#define ATTR_TAG_Column    "Column"
#define ATTR_TAG_Row       "Row"
#define ATTR_TAG_Vapour    "Vapour"
#define ATTR_TAG_Soil      "Soil"
#define ATTR_TAG_Length    "Length"
#define ATTR_TAG_Item      "Item"
#define ATTR_TAG_Caption   "Caption"
#define ATTR_TAG_Exe	   "exe"
#define ATTR_TAG_Dll	   "dll"
#define ATTR_TAG_Mode	   "Mode"
#define ATTR_TAG_Call		"Call"
#define ATTR_TAG_Color      "Color"
#define ATTR_TAG_Name		"Name"
#define ATTR_TAG_Date		"Date"
#define ATTR_TAG_Short_Name	"Short_Name"
#define ATTR_TAG_Description "Description"
#define ATTR_TAG_Value 		"Value"
#define ATTR_TAG_Type		"Type"
#define ATTR_TAG_Path		"Path"
#define ATTR_TAG_Mail		"Mail"
#define ATTR_TAG_Phone		"Phone"
#define ATTR_TAG_Module	   "Module"
#define ATTR_TAG_Default   "Default"
#define ATTR_TAG_RangeHi   "RangeHi"
#define ATTR_TAG_RangeLo   "RangeLo"
#define ATTR_TAG_Unit      "Unit"
#define ATTR_TAG_Units      "Units"
#define ATTR_TAG_File      "File"


// Airflow
#define NODE_TAG_Biodegradation      "Biodegradation"
#define NODE_TAG_Run       "Run"
#define NODE_TAG_Solver    "Solver"
#define NODE_TAG_Cover     "Cover"
#define NODE_TAG_Contaminant "Contaminant"
//    property SOIL
#define NODE_TAG_Soil       "Soil"
#define NODE_TAG_Fill       "Fill"
#define NODE_TAG_Value      "Value"
#define ATTR_TAG_Stagnant   "Stagnant"
#define ATTR_TAG_tau			 "tau"
#define ATTR_TAG_foc			 "foc"
#define ATTR_TAG_Cv			 "Cv"
//    property WELL
#define ATTR_TAG_Pulse             "Pulse"
#define ATTR_TAG_Extraction_Top    "Extraction_Top"
#define ATTR_TAG_Extraction_Bottom "Extraction_Bottom"
#define ATTR_TAG_Injection_Top     "Injection_Top"
#define ATTR_TAG_Injection_Bottom  "Injection_Bottom"
#define ATTR_TAG_Rate              "Rate"
#define ATTR_TAG_Pressure          "Pressure"
//    property RUN
#define ATTR_TAG_Max       "Max"
#define ATTR_TAG_Min       "Min"
#define ATTR_TAG_Output    "Output"
#define ATTR_TAG_Increase  "Increase"
#define ATTR_TAG_Decrease  "Decrease"
#define ATTR_TAG_Final     "Final"
#define ATTR_TAG_Initial   "Initial"
//    property SOIL
#define ATTR_TAG_Ci       "Ci"
#define ATTR_TAG_Sw       "Sw"
//    property AIR
#define ATTR_TAG_Temperature    "Temperature"
#define ATTR_TAG_Viscosity      "Viscosity"
#define ATTR_TAG_Weight         "Weight"
#define ATTR_TAG_Constant       "Constant"
#define ATTR_TAG_Coefficient    "Coefficient"
//    property NAPL
#define NODE_TAG_Bulk      "Bulk"
#define ATTR_TAG_TCE        "TCE"
#define ATTR_TAG_Propane    "Propane"
#define ATTR_TAG_Ceqv       "Ceq,v"
#define ATTR_TAG_Ceqw       "Ceq,w"
#define ATTR_TAG_Koc        "Koc"
#define ATTR_TAG_KGO        "KGO"
#define ATTR_TAG_BG         "BG"
#define ATTR_TAG_NAPL_M     "M"
#define ATTR_TAG_Vp         "Vp"
#define ATTR_TAG_Tb         "Tb"
#define ATTR_TAG_Rho_l      "rho l"
#define ATTR_TAG_Lambda     "lambda"
#define ATTR_TAG_K          "k"
#define ATTR_TAG_Dv         "Dv"
#define ATTR_TAG_Dw         "Dw"
#define ATTR_TAG_Dm         "Dm"
#define ATTR_TAG_Ks         "Ks"
#define ATTR_TAG_Koc        "Koc"
//    property LOAD
#define NODE_TAG_GRD      "grd"
#define NODE_TAG_BDY      "bdy"
#define NODE_TAG_PRP      "prp"
#define NODE_TAG_AIR      "air"
#define NODE_TAG_RO       "ro"
#define NODE_TAG_MTX      "mtx"
#define NODE_TAG_NPD      "npd"
#define NODE_TAG_VPD      "vpd"
#define NODE_TAG_TIM      "tim"
#define NODE_TAG_PAR      "par"
#define NODE_TAG_RUN      "run"
#define NODE_TAG_BIO      "bio"
#define NODE_TAG_SOP		  "sop"

#define NODE_TAG_CNC      "cnc"
#define NODE_TAG_QWR      "qwr"
#define NODE_TAG_CNW      "cnw"
#define NODE_TAG_CNS      "cns"
#define NODE_TAG_CTT      "ctt"
//    property BIO
#define ATTR_TAG_Bde        "Bde"
#define ATTR_TAG_Bgr        "Bgr"
#define ATTR_TAG_Kmer       "Kmer"
#define ATTR_TAG_X0         "X0"
#define ATTR_TAG_Tc         "Tc"
#define ATTR_TAG_Y          "Y"
#define ATTR_TAG_R0X0       "R0/X0"
#define ATTR_TAG_Ksr        "Ks,r"
#define ATTR_TAG_R0         "R0"
#define ATTR_TAG_Kr         "Kr"
#define ATTR_TAG_Alpha_c    "alpha c"
#define ATTR_TAG_Alpha_g    "alpha g"


}	/* namespace Xml_def */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Xml_def;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// Xml_Def


