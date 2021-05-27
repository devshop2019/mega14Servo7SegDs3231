#include "MainFunction.h"
// #include "DebugManager.h"

//Update y20d02m03: Offset 0 is command string
String splitString2(String v_G_motherString, String v_G_Command, String v_G_Start_symbol, String v_G_Stop_symbol, unsigned char v_G_Offset){
    unsigned char tem_Offset = v_G_Offset - 1;
    unsigned char lenOfCommand = v_G_Command.length();
    int posOfCommand = v_G_motherString.indexOf(v_G_Command);
    int PosOfStartSymbol = v_G_motherString.indexOf(v_G_Start_symbol);
    if(PosOfStartSymbol <= 0) return "";

    PosOfStartSymbol = v_G_motherString.indexOf(v_G_Start_symbol, posOfCommand + lenOfCommand);

    int PosOfStartSymboluu = v_G_motherString.indexOf(v_G_Start_symbol);

    if(posOfCommand < 0) return "";

    String tem__ = v_G_motherString.substring(posOfCommand, PosOfStartSymbol);
    if(tem__ != v_G_Command){
        return "";
    }
    
    if(v_G_Offset == 0) return  tem__;
    
    while(tem_Offset > 0){
        tem_Offset--;
        PosOfStartSymbol = v_G_motherString.indexOf(v_G_Start_symbol, PosOfStartSymbol + 1);
    }
  
  if(v_G_Stop_symbol != ""){
    int PosOfStopSymbol = v_G_motherString.indexOf(v_G_Stop_symbol,PosOfStartSymbol + 1);
    if(PosOfStopSymbol == -1){
      return "";
    }else;    
    return v_G_motherString.substring(PosOfStartSymbol+1,PosOfStopSymbol);
  }else{
    return v_G_motherString.substring(PosOfStartSymbol+1);
  }
}

