/*frame.hh 
Largerly based off of the frame.h interface
from 'modern compiler implementation in c' by
andrew w. appel. Will be implemented in mipsframe.cpp*/
//machine dependent word size
extern const int F_wordSize;

//Frame struct
using std::shared_ptr<F_frame_> F_frame;
F_frame F_newFrame(Temp_label name, F_formalsList formals);
using std::shared_ptr<F_access_> F_access;
//accesses/formals interface
using std::vector<bool> F_formalsList;
using std::shared_ptr<F_access_> F_access;

using std::vector<F_access> F_accessList;
F_access F_allocLocal(F_frame f, bool escape);
F_accessList F_formals(F_frame f);

string F_getlabel(F_frame frame);

//========Temps interface=================
Temp_map F_tempMap;
Temp_tempList F_registers(void);
T_exp F_Exp(F_access acc, T_exp framePtr);
Temp_label F_name(F_frame f);
Temp_temp F_FP(void);
Temp_temp F_SP(void);
Temp_temp F_ZERO(void);
Temp_temp F_RA(void);
Temp_temp F_RV(void);

//Misc T_exps 
T_exp F_externalCall(string s, T_expList args);
//T_stm F_procEntryExit1(F_frame frame, T_stm stm);

//========fragement interface for strings and function(procedures)
using std::shared_ptr<F_frag_> F_frag;
F_frag F_StringFrag(Temp_label label, string str);
F_frag F_ProcFrag(T_stm body, F_frame frame);

//F_frag F_string (Temp_label lab, string str);
//F_frag F_newProcFrag(T_stem body, F_frame frame);
using std::vector<F_frag> F_fragList;
