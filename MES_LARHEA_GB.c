/*******************************************************************//**
 *  \file MES_LARHEA_GB.C
 *  \brief Brief
 *
 *  \author
 *  \date
 *  \version
 ***********************************************************************/
#include "config.h"
#include "LANG_DEF.H"

#ifdef LANGUAGE_GB

#ifdef ABIL_PROGRAMMAZIONE_PARZIALE
const u8 __far GB_MS_PROG_ESTESA[16] = {"TOTAL           ",};
const u8 __far GB_MS_PROG_RIDOTTA[16] = {"PARTIAL         ",};
#endif

/*---------------------------------------------*/
const u8 __far GB_MSA_1[MAX_MSA][32] = {

    /* MSA n.  0 */        NOME_MACCHINA_1
                           DATA_VERSIONE_1

    #ifdef CUSTOMER_RHEA
        #ifdef BUSINESS_LINE
            #ifdef MODELLO_ESPRESSO
    /* MSA n.  1 */        "   laRhea BL    "
                           "                ",
            #else
    /* MSA n.  1 */        "   laRhea BL    "
                           "   Speed Mix    ",
            #endif
        #else
    /* MSA n.  1 */        "   laRhea V+    "
                           "                ",
        #endif
    #else
    /* MSA n.  1 */        "           place"
                           "your cup        ",
    #endif

    /* MSA n.  2 */        " switching on..."
                           "   please wait  ",
    #ifdef MODELLO_DOPPIO
    /* MSA n.  3 */        "  preselection  "
                           " -   Sugar    + ",
    #else
      #ifdef CUSTOMER_NESTLE
    /* MSA n.  3 */        "           place"
                           "your cup        ",
      #else		   
    /* MSA n.  3 */        "           place"
                           "your cup        ",
      #endif 
    #endif

    #ifdef CUSTOMER_NESTLE
    /* MSA n.  4 */        "      remove cup"
                           "Please          ",
    #else					   
    /* MSA n.  4 */        "      remove cup"
                           "Please          ",
    #endif

    /* MSA n.  5 */        "  preparing     "
                           "drink nr. \1\2    ",

    /* MSA n.  6 */        "\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
                           "  preparing     ",

    #ifdef CUSTOMER_NESTLE
    /* MSA n.  7 */        "          insert"
                           "exact change    ",
    #else					   
    /* MSA n.  7 */        "          insert"
                           "exact change    ",
    #endif

    #ifdef CUSTOMER_NESTLE
    /* MSA n.  8 */        "    check coffee"
                           "brewer          ",
    #else					   
    /* MSA n.  8 */        "    check coffee"
                           "brewer          ",
    #endif	 

    /* MSA n.  9 */        "Programming     "
                           "OK              ",

    /* MSA n. 10 */        "Error during    "
                           "programming     ",

    /* MSA n. 11 */        "1= KEY ---> VMC "
                           "2= VMC ---> KEY ",

    /* MSA n. 12 */        "Programming     "
                           "EPROM data      ",

    /* MSA n. 13 */        "Programming-----"
                           "RHEA FLASH------",

    /* MSA n. 14 */        "product reserve "
                           "\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F",

    /* MSA n. 15 */        "  WATER FILTER  "
                           "CLEAN.  10=START",

    /* MSA n. 16 */        "         machine"
                           "ready           ",

    /* MSA n. 17 */        "  Service       "
                           "        Card    ",

    /* MSA n. 18 */        " Not available  "
                           "                ",

    #ifdef MODELLO_TS
    /* MSA n. 19 */        "    reset coffee"
                           "  grounds=RESET ",
    #else
    /* MSA n. 19 */        "    reset coffee"
                           "  grounds = P1  ",
    #endif

    /* MSA n. 20 */        "                "
                           "                ",

    /* MSA n. 21 */        "Credit:         "
                           "        \1\2\3\4\5\6\7\x08",

    /* MSA n. 22 */        "  Out of service"
                           "water filter    ",

    #ifdef CUSTOMER_NESTLE
    /* MSA n. 23 */        "         service"
                           "clean  brewer   ",
    #else
    /* MSA n. 23 */        "         service"
                           "clean  brewer   ",
    #endif 

    /* MSA n. 24 */        "Price :    \4\5\6\7\x08"
                           "                ",

    /* MSA n. 25 */        " Out of service "
                           " coffee grounds ",

    /* MSA n. 26 */        " no  product    "
                           "                ",

    /* MSA n. 27 */        " refilling water"
                           "wait            ",

    /* MSA n. 28 */        "     wait       "
                           "                ",

    /* MSA n. 29 */        "            wait"
                           "temperature     ",

    /* MSA n. 30 */        "Out of service  "
                           "OFF \x08\x09\x0A \0       ",

    /* MSA n. 31 */        "machine off     "
                           "           \5\6:\7\x08",

    #ifdef CUSTOMER_NESTLE

    /* MSA n. 32 */        "................"
                           "start at:  \5\6:\7\x08",

    /* MSA n. 33 */        "   TEST VEND    "
                           "                ",

    /* MSA n. 34 */        "   take a moment"
                           "to relax        ",

    /* MSA n. 35 */        "           Fresh"
                           "Milk            ",

    /* MSA n. 36 */        "messaggio 3     "
                           "programmabile   ",

    /* MSA n. 37 */        "  enjoy a break "
                           "                ",

    /* MSA n. 38 */        "          Always"
                           "at your service ",

    /* MSA n. 39 */        "  insert coins  "
                           "                ",
    #else

    /* MSA n. 32 */        "................"
                           "start at:  \5\6:\7\x08",

    /* MSA n. 33 */        "   TEST VEND    "
                           "                ",

    /* MSA n. 34 */        "   take a moment"
                           "to relax        ",

    /* MSA n. 35 */        "           Fresh"
                           "Milk            ",

    /* MSA n. 36 */        "messaggio 3     "
                           "programmabile   ",

    #ifdef CUSTOMER_KP
    /* MSA n. 37 */        " Please hold    "
                           "   the card     ",
    #else

    /* MSA n. 37 */        "  enjoy a break "
                           "                ",
    #endif
    /* MSA n. 38 */        "          Always"
                           "at your service ",

    /* MSA n. 39 */        "  insert coins  "
                           "                ",

    #endif

    #ifdef MODELLO_SOLUBILE

    /* MSA n. 40 */        "t. inst.     \6\7\x08"
                           "----------------",

    #else
    /*MSA n. 40*/          "t.c \x0A\x0B\x0C  t.s \6\7\x08"
                           "t.h \x0E\x0F          ",

    #endif
    /* MSA n. 41 */        "  Card Reader   "
                           " Not Connected  ",

    /* MSA n. 42 */        "   DATA AUDIT   "
                           "  PLEASE  WAIT  ",

    /* MSA n. 43 */        "     J U G      "
                           "                ",

    #if defined (CUSTOMER_RHEA) || defined (MODELLO_BONA)
    /* MSA n. 44 */        "  rheavendors   "
                           "                ",
    #else
    /* MSA n. 44 */        "           place"
                           "your cup        ",
    #endif

    /* MSA n. 45 */         "  no  selections"
                           "F.Milk   OFF \x09\x0A\x0B",

    /* MSA n. 46 */        "HAPPY           "
                           "           HOUR ",

    /* MSA n. 47 */        "   FREE VEND    "
                           "\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F",
    #ifdef MODELLO_ESPRESSO
    /* MSA n. 48 */        "no coffee beans "
                           "         OFF \x09\x0A\x0B",
    #else
    /* MSA n. 48 */        "mes 48          "
                           "                ",
    #endif

    #ifdef CUSTOMER_NESTLE
    /* MSA n. 49 */        " Out of service "
                           "    no water    ",
    #else
    /* MSA n. 49 */        " Out of service "
                           "    no water    ",
    #endif

    /* MSA n. 50 */        " fill water and "
                           "press button -1-",

#ifdef CAPPUCCINATORE_INDUX
    /* MSA n. 51 */        "  Hydrodynamic  "      	 //"       automatic"
                           " Emptying phase ",       //"steam cleaning  ",    
#else					   
    /* MSA n. 51 */        "       automatic"
                           "steam rinsing   ",
#endif  

    /* MSA n. 52 */        "SERVICE         "
                           "                ",

    /* MSA n. 53 */        "error  on KEY   "
                           "code  \x09\x0A        ",

//------------------------------------------------------
#if defined(ABIL_MILKER_DESCALING)  //#4419
 #if defined(MODELLO_ESPRESSO) 
  #ifdef ABIL_DESCALING
    #ifdef ENABLE_GRINDER_CLEANING
    /* MSA n. 54 */        "1-4=Mx M:5=C 6=D" 			//5=Cleaning Milk Module 6=descaling Milk Circuit
                           "7=Gr 8=BC 9=Desc",
    #else 
    /* MSA n. 54 */        "1-4=Mix 5=MilkMd" 
                           "6=DeM 8=BC 9=Des",
    #endif
  #else  //#ifdef ABIL_DESCALING
    #ifdef ENABLE_GRINDER_CLEANING
    /* MSA n. 54 */        "1-4=Rinse 5=Milk" 
                           "6=D.M 7=Gr. 8=BC",
    #else
    /* MSA n. 54 */        "1-4=Rinse 5=Milk" 
                           "6=Desc.Milk 8=BC",
    #endif
  #endif  //#ifdef ABIL_DESCALING
 #endif	  //#if defined(MODELLO_ESPRESSO) 
#endif    //#if defined(ABIL_MILKER_DESCALING)  //#4419

#if !defined(ABIL_MILKER_DESCALING)
#if defined(MODELLO_ESPRESSO) 
#if defined(ABIL_CAPPUCCINATORE) && defined(ABIL_DESCALING)
#ifdef ENABLE_GRINDER_CLEANING
    /* MSA n. 54 */        "1-4=Mix 5=MilkMd"
                           "7=Gr 8=BC 9=Desc",
#else
    /* MSA n. 54 */        "1-4=Mix 5=MilkMd"
                           "  8=BC 9=Desc   ",
#endif

#elif defined(ABIL_DESCALING) && !defined(ABIL_CAPPUCCINATORE)
#ifdef ENABLE_GRINDER_CLEANING
    /* MSA n. 54 */        "   1-4=Rinse    "
                           "7=Gr 8=BC 9=Desc",
#else
    /* MSA n. 54 */        "   1-4=Rinse    "
                           "   8=BC 9=Desc  ",
#endif

#elif !defined(ABIL_DESCALING) && defined(ABIL_CAPPUCCINATORE)
#ifdef ENABLE_GRINDER_CLEANING
    /* MSA n. 54 */        "1-4=Rinse 5=Milk"
                           " 7=grinder 8=BC ",
#else                      
    /* MSA n. 54 */        "1-4=Rinse 5=Milk"
                           "      8=BC      ",
#endif

#else

#ifdef ENABLE_GRINDER_CLEANING
    /* MSA n. 54 */        "    1-4=Rinse   "
                           " 7=grinder 8=BC ",
#else                      
    /* MSA n. 54 */        "    1-4=Rinse   "
                           "      8=BC      ",
#endif

#endif  
#else 
    /* MSA n. 54 */        "    1-4=Rinse   "
                           "                ",
#endif 
#endif  //#if !defined(ABIL_MILKER_DESCALING)

    /* MSA n. 55 */        "rinsing   \0\1    "
                           "             \6\7\x08",

    /* MSA n. 56 */        "RFID reader card"
                           "connected       ",
    #ifdef SUMMERTIME
    /* MSA n. 57 */        "Hello     \0\1\2\x0E\x0F "
                           "\4\5-\6\7-\x08\x09 \3 \x0A\x0B:\x0C\x0D",
    #else
    /* MSA n. 57 */        " Enter the exact"
                           " amount         ",
    #endif
    /* MSA n. 58 */        "          change"
                           "water filter    ",

    #ifdef CUSTOMER_NESTLE
    /* MSA n. 59 */        "           clean"
                           "brewer          ",

    /* MSA n. 60 */        "           empty"
                           "coffee grounds  ",
    #else
    /* MSA n. 59 */        "           clean"
                           "brewer          ",

    /* MSA n. 60 */        "           empty"
                           "coffee grounds  ",
    #endif

    /* MSA n. 61 */        "  SET  PRODUKT  "
                           "  ---- OK ----  ",

    /* MSA n. 62 */        " INSTALLATION   "
                           "                ",

    /* MSA n. 63 */        "      end       "
                           "  installation  ",

    /* MSA n. 64 */        "  credit = 0    "
                           "                ",

    /* MSA n. 65 */        "    place the   "
                           "      card      ",

    /* MSA n. 66 */        "SELECTION CARD  "
                           "                ",

    /* MSA n. 67 */        "product reserve "
                           " REFILL COFFEE  ",

    /* MSA n. 68 */        "Not available   "
                           "\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F",

    /* MSA n. 69 */        "-  S U G A R   +"
                           "                ",

    /* MSA n. 70 */        "    make a      "
                           "  selection     ",

    /* MSA n. 71 */        "door  module    "
                           "        vers. \0\1",

    /* MSA n. 72 */        "espresso module "
                           "        vers. \0\1",
                          
    /* MSA n. 73 */        "  Milk module   "
                           " version    \0\1  ",

    /* MSA n. 74 */        " Periodic rinse "
                           "  in \0 seconds  ",

    /* MSA n. 75 */        "                "
                           "       OFF \x09\x0A  \x0B",
                           
    /* MSA n. 76 */        "      Remove Cup"
                           "Please          ",
                           
    /* MSA n. 77 */        "  wait charging "
                           " steam boiler   ",
                           
    /* MSA n. 78 */        "invalid customer"
                           "   card code    ",
                           
    /* MSA n. 79 */        "invalid machine "
                           "   card code    ",
                           
    /* MSA n. 80 */        "    lucky       "
                           "  selection     ",
                           
    /* MSA n. 81 */        "TOKEN           "
                           "                ",
                           
    /* MSA n. 82 */        "  wait please   "
                           "steam temperat. ",
                           
    /* MSA n. 83 */        "Price :    \x0B\x0C\x0D\x0E\x0F"
                           "Credit: \1\2\3\4\5\6\7\x08",
                           
    /* MSA n. 84 */        "First coffee    " //libero disponibile 
                           "in progress     ",
                           
    /* MSA n. 85 */        "emptying        "
                           "coffee grounds  ",
                           
    #ifdef CUSTOMER_NESTLE 
                           
    /* MSA n. 86 */        "     remove     "
                           "    driptray    ",
                           
    /* MSA n. 87 */        "     insert     "
                           "    driptray    ",
                           
    #else                  
                           
    /* MSA n. 86 */        "     remove     "
                           "    driptray    ",
                           
    /* MSA n. 87 */        "     insert     "
                           "    driptray    ",
                           
    #endif                 
                           
    /* MSA n. 88 */        "steam flushing  "
                           "        10=START",
                           
    /* MSA n. 89 */        "fill detergent  "//lavaggio vapore con detergente
                           "        10=START",

#ifdef CAPPUCCINATORE_INDUX
    /* MSA n. 90 */        "filling water..."
                           "conduc.=\4\5\6\7\x08 uS",
#else                      
    /* MSA n. 90 */        "fill water      "
                           "        10=START",
#endif	                   
                           
    /* MSA n. 91 */        "warm water      "//lavaggio vapore con detergente
                           "flush.  10=START",
                           
    /* MSA n. 92 */        "   Milk Module  "
                           " switching on...",
                           
    /* MSA n. 93 */        "  Milk container"
                           "empty           ",
                           
    /* MSA n. 94 */        "    S T O P     "
                           "                ",
                           
    /* MSA n. 95 */        "   RFID Card    "
                           "    Blocked     ",

    #ifndef TEST_CICLICO
        #ifdef CAPPUCCINATORE_INDUX
    /* MSA n. 96 */        "  Milk  Module  "
                           "  Please clean  ",
        #else              
    /* MSA n. 96 */        "  Milk  Module  "
                           "  Please clean  ",
        #endif             
                           
    /* MSA n. 97 */        "      clean with"//lavaggio vapore con detergente     
                           "deterg. 10=START",
    #else                  
    /* MSA n. 96 */        "  Cyclic Test   "
                           "  round #\4\5\6\7\x08  ",
                           
    /* MSA n. 97 */        "  Cyclic Test   "//lavaggio vapore con detergente     
                           "  Stopped!!!    ",
    #endif                 
                           
    /* MSA n. 98 */        "rinse with cold "//lavaggio vapore con detergente   
                           "water   10=START",
                           
#ifdef CAPPUCCINATORE_INDUX
    /* MSA n. 99 */        "  END Cleaning  "	//lavaggio vapore con detergente     
                           " with Detergent ",
#else                      
    /* MSA n. 99 */        "      END       "//lavaggio vapore con detergente     
                           "steam flushing  ",
#endif		               
                           
    /* MSA n. 100 */       "    wait milk   " //attendere lavaggio cappuccinatore
                           "  unit cleaning ",
                           
    /* MSA n. 101 */       "       Place Cup" //attendere lavaggio cappuccinatore
                           "please          ",
                           
    /* MSA n. 102 */       " setting grinder" //attendere Regolazione della macina. Granulometria della selezione
                           "  Please wait   ",
                           
    /* MSA n. 103 */       "\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F" // non usato su progetto BL
                           "   HOT WATER    ",

    /* MSA n. 104 */       "Warning products"
                           "   level   low  ",

    /* MSA n. 105 */       "xxxxxxx         "
                           "                ",

    /* MSA n. 106 */       "Catch Coffee    " //era in prog 209
                           "Push PROG Button",

    /* MSA n. 107 */       "                " //era in prog 215
                           "autom. reset    ",

    /* MSA n. 108 */       "      End       " //era in prog 219
                           "   uninstall    ",

    /* MSA n. 109 */       "Final Result:\6\7\x08"	//Risulta finale test vuoto macina
                           "KEY PRESS <PROG>",

    /* MSA n. 110 */       " Cleaning  Time " //ricetta errata
                           " Milker Updated ",

    /* MSA n. 111 */       "TEST RUNNING    " //era MSP n.  68 */
                           "                ",

    /* MSA n. 112 */       "confirm partial " // era in /* MSP n. 97 */ 
                           "reset  press P10",

    /* MSA n. 113 */       " Starting Test  "
                           "4=start PROG=end",

    /* MSA n. 114 */       "TEST MOTOR - \x0A\x0B "
                           "sx \x0C\x0D\x0E\x0F  dx \5\6\7\x08",

    /* MSA n. 115 */       "TEST - \x0A\x0B  Tp: \3"
                           "up \x0C\x0D\x0E\x0F  dn \5\6\7\x08",

    /* MSA n. 116 */       "  Final Result  "
                           "    TEST - \x0A\x0B   ",

#ifdef RESET_SANITARY_WASH
    /* MSA n. 117*/        " System halted  "
                           " Please restart!",
#else
    /* MSA n. 117 */       "Empty the waste "						//20201007 (104)
                           "liquid tank     ",						//20201007
#endif 

    /* MSA n. 118 */       "Insert the waste"						//20201007 (103)
                           "liquid tank     ",						//20201007					  

    /* MSA n. 119 */       "rinsing \0\1   \6\7\x08" 						//20201007 (105)
                           "........uS=\x09\x0A\x0B\x0C\x0D",       					//20201007								  

#ifdef MODELLO_TS
    /* MSA n. 120 */       "Have you done   "						//20201106 
                           "checks?>START/10",						//20201106	
#else
    /* MSA n. 120 */       "Clean.Deter.type"			//#3876		//"Have you done   "						//20201106 
                           "10=Tab 12=Liquid",			//#3876		//"checks? 10=start",						//20201106
#endif                      	

    /* MSA n. 121 */ 	   "check milk      "						//20201007 (103)
                           "                ",						//20201007					  

    /* MSA n. 122 */       "Check Detergent "						//"warning.. troppo"	//20201007 (103)
                           "of the water mix",						//20201007		

    /* MSA n. 123 */       "Milk Mod.Clean.:"
                           "check deter. \x09\x0A\x0B",

    /* MSA n. 124 */       "Cleaning \0\1  \6\7\x08" 				//20201007 
                           "........uS=\x09\x0A\x0B\x0C\x0D",       	//20201007		

    /* MSA n. 125 */       "   Dissolving   "
                           "Detergent \0\1 \6\7\x08",

#ifdef MODELLO_TS
    /* MSA n. 126 */	   "Insert the milk "
                           "tube.10:now 9:no",
#else
    /* MSA n. 126 */	   "Ins. Tube/refill"
                           "Milk 10:now 9:no",
#endif

    /* MSA n. 127 */       "  check milk    "
                           "   presence     ",

    /* MSA n. 128 */       "   check milk   "
                           "    quality     ",

    /* MSA n. 129 */       "check milk and  "
                           "make cleaning   ",

    /* MSA n. 130 */       "Gest. rhMM1.v+ ?"
                           "B1=Enable B2=no ",

    /* MSA n. 131 */       "Clean. rhMM1.v+ "
                           "Time \5\6:\7\x08 Ok=P1",

    /* MSA n. 132 */       "Milk Mod.Clean.:"        //"rhMM1.v+ Clean.:"
                           "low deterg. \x09\x0A\x0B ",

    /* MSA n. 133 */       "check tank cold "
                           "milk temperature",

    /* MSA n. 134 */       "Available       "
                           "                ",

    /* MSA n. 135 */       "  Close  Coffee "   // era 117
                           "KEY PRESS <PROG>",

    /* MSA n. 136 */       "  Open   Coffee "   // era 118
                           "KEY PRESS <PROG>",

    /* MSA n. 137 */       "1/13 Clean Grin."
                           "1=Grin1; 2=Grin2",

    /* MSA n. 138 */       "2/13 G^ Close   "
                           "shutter.  10=ok ",

    /* MSA n. 139 */       "3/13 Rem. brewer"
                           "& bean hop 10=ok",

    /* MSA n. 140 */       "4/13 Inst. clean"
                           "device.    10=ok",

    /* MSA n. 141 */       "5/13 Grinder    "
                           "clean   10=start",

    /* MSA n. 142 */       "Cycle ^ of )    "
                           "                ",

    /* MSA n. 143 */       "6/13 Rep. Clean "
                           "10=Yes; other=NO",

    /* MSA n. 144 */       "7/13 Ref. Clean "
                           "device.    10=ok",

    /* MSA n. 145 */       "8/13 Put back   "
                           "bean hop.  10=ok",

    /* MSA n. 146 */       "9/13 Open hopp. "
                           "shutter.  10=ok ",

    /* MSA n. 147 */       "10/13 Coffee    "
                           "grind.  10=Start",

    /* MSA n. 148 */       "Cycle ^ of )    "
                           "timeout \7\x08 sec  ",

    /* MSA n. 149 */       "11/13 Rep. Proc."
                           "10=Yes; other=NO",

    /* MSA n. 150 */       "12/13 Put back  "
                           "Brewer.  10 = ok",

    /* MSA n. 151 */       "13/13 Coffee?   "
                           "10=Yes; other=NO",

    /* MSA n. 152 */       "ESPRESSO        "
                           "preparing       ",

    /* MSA n. 153 */       "Forthcoming     "
                           "sched maintenan.",

    /* MSA n. 154 */       "Maintenance must"
                           "be performed    ",

    /* MSA n. 155 */       "  Enter Weight  "
                           "  1 = Save  \5\6\7\x08",

    /* MSA n. 156 */       "END PROGRAMMING " //era msp 50
                           "wait..........  ",

    /* MSA n. 157 */       "access code     " //era msp 116 mi sembra non sia usato
                           "INHIBITED       ",

    /* MSA n.  158 */      "uninstallation  " //era msp 174
                           "in progress...  ",

    /* MSA n.  159 */      "                " //era msp 47 mi sembra non sia usato
                           "                ",

    /* MSA n.  160 */      "CALIBRATION IS  " //era msp 184 mi sembra non sia usato
                           "NOT POSSIBLE    ",

    /* MSA n.  161 */      "Remove Brewer   " //era msp 185
                           "Push PROG button",

    /* MSA n.  162 */      "Replace Brewer  " //era msp 186
                           "Push PROG Button",

    /* MSA n.  163 */      "Open boiler tap " //era msp 200
                           "       10=start ",

    /* MSA n.  164 */      "   KEY PRESS    " // era msp 187
                           "     >PROG<     ",

    /* MSA n.  165 */      " end uninstall  " //era msp 201
                           "close boiler tap",

    /* MSA n.  166 */      "Water supply    " //era msp 212    //version E3-E3 servomat
                           "conn.? Start=10 ",                 //4

    #ifdef CUSTOMER_NESTLE
    /* MSA n.  167 */      "driptray        "  //era msp 213
                           "inside? 10=START",
    #else
    /* MSA n.  167 */      "driptray        "  //era msp 213
                           "inside? 10=START",
    #endif

    /* MSA n.  168 */      "remove coffee   " // era msp 224
                           "grounds 10=START",

    /* MSA n.  169 */      "Drip tray       " //era msp 218
                           "empty? Start=10 ",

    #ifdef CUSTOMER_NESTLE
    /* MSA n.  170 */      "REGISTRATION out" //era msp 40
                           "of service      ",
    #else
    /* MSA n.  170 */      "REGISTRATION out" //era msp 40
                           "of service      ",
    #endif

    /* MSA n.  171 */      "PROGRAMMING-----" //era msp 72
                           "----------------",

    /* MSA n.  172 */      "Preselection    " //era msp 235
                           "not used        ",

    /* MSA n.  173 */      "PRODUCT  \x0A\x0B     " //era msp 241
                           "0=inhib.    \6\7.\x08",

    /* MSA n. 174 */       "coffee time     "
                           "grinder     \6\7.\x08",

    /* MSA n. 175 */       "Ent. Weight \5\6\7\x08" //era 183
                           "1=Save  2=Repeat",

    /* MSA n. 176 */       "Ent. ML of water"				//#1885
                           "1=Save 2=rep \6\7\x08",			//#1885

    /* MSA n. 177 */       "Empties test jug"				//#1885
                           "Test:  1=ok 2=no",				//#1885		

    /* MSA n. 178 */       "Fill H2O FM tank"				//#1885
                           "t.tube 1=ok 2=no",				//#1885	

    /* MSA n. 179 */       "Confirm Action  "				//#2311
                           "10=YES      9=NO",				//#2311	

    /* MSA n. 180 */       "ENERGY SAVING   "				//	@AI #4300  Dyn_energy_save
                           "                ",	

    /* MSA n. 181 */       "Credit:         "				
                           "       Card     ",
                                
    /* MSA n. 182 */       "   NEED GRINDER "               // "NEED GRINDER CALIBRATION"
                           "CALIBRATION     ",

   
    /* MSA n. 183 */       "Refill   cups   "                //#4791
                           "                ",                //#4791
                           
    /* MSA n. 184 */       "Use own cups    "
                           "                ",

}
;

/*------------- MESSAGGI PROGRAMMAZIONE -------*/

const u8 __far GB_MSAP_1[MAX_MSAP][32] = {

    /* MSP n.  0 */        "                "
                           "                ",

    /* MSP n. 1 */         "insert code     "
                           "             \6\7\x08",

    /* MSP n.  2 */        "START F1:       "
                           "HAPPY HOUR \5\6:\7\x08",

    /* MSP n.  3 */        "END F1:         "
                           "HAPPY HOUR \5\6:\7\x08",

    /* MSP n.  4 */        "START F2:       "
                           "HAPPY HOUR \5\6:\7\x08",

    /* MSP n.  5 */        "END F2:         "
                           "HAPPY HOUR \5\6:\7\x08",

    /* MSP n.  6 */        "START F3:       "
                           "HAPPY HOUR \5\6:\7\x08",

    /* MSP n.  7 */        "END F3:         "
                           "HAPPY HOUR \5\6:\7\x08",

    /* MSP n.  8 */        "coin        \x0A  \x08"
                           "card      0=acc.",

    /* MSP n.  9 */        "coin        \x0A  \x08"
                           "no card   0=acc.",

    /* MSP n. 10 */        "max. credit card"
                           "        \1\2\3\4\5\6\7\x08",
#ifdef ABIL_MANUTENZIONE
    /* MSP n. 11 */        "1=PROGRAMMING   "
                           "2=DATA 3=TESTV. ",

    /* MSP n. 12 */        "4=RINSE - CLEAN "
                           "5=MAINT. 6=MODEM",
#else
    /* MSP n. 11 */        "1=PROGR  2=DATA "
                           "3=TEST   4=CLEAN",
    /* MSP n. 12 */        "1=PROGR  2=DATA "
                           "3=TEST   4=CLEAN",
#endif
    /* MSP n. 13 */        "discount        "
                           "card     -  \7\x08 %",

    /* MSP n. 14 */        "Def. Vibr. mot. " 		//VIBR_MOT_TIME_GRINDER_1, 2, 3, 4
                           "Time gr.  \x0A  \6\7\x08",

    /* MSP n. 15 */        "FUNCTIONING     "
                           "                ",

    /* MSP n. 16 */        "not used        "
                           "                ",
    #ifdef DISABILITA_CONVERSIONE_GRAMMI
    /* MSP n. 17 */        "PRODUCT  \x0A\x0B     "
                           "0=inhib.    \6\7.\x08",
    #else
    /* MSP n. 17 */        "DOSAGE grams    "
                           "PRODUCT \x0A\x0B  \6\7.\x08",
    #endif

    /* MSP n. 18 */        "start delay     "
                           "PRODUCT  \x0A\x0B \6\7.\x08",

    #ifdef CUSTOMER_NESTLE
    /* MSP n. 19 */        "breaks number   "
                           "0-2 15=Max    \7\x08",
    #else                  
    /* MSP n. 19 */        "breaks number   "
                           "0-2 12=Max -  \7\x08",	//"0 - 2         \7\x08",
    #endif

    /* MSP n. 20 */        "WATER \x0A\x0B time   "
                           "0=inhib.    \6\7.\x08",

    /* MSP n. 21 */        "start delay     "
                           "WATER \x0A\x0B    \6\7.\x08",

    /* MSP n. 22 */        "MIXER \x0A\x0B        "
                           "0=inhib.    \6\7.\x08",

    /* MSP n. 23 */        "start delay     "
                           "MIXER \x0A\x0B    \6\7.\x08",

    /* MSP n. 24 */        "water flow  : \x0A\x0B"
                           "        \0\1\2\3\4\5\6\7",

    /* MSP n.  25 */       "selection name)^"
                           "\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F",

    /* MSP n. 26 */        "delay station   "								//ezio 11/05/2015
                           "            \6\7.\x08",

    /* MSP n. 27 */        "Programming:    "
                           "\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F",  /* estesa-ridotta */

    /* MSP n. 28 */        "MIXER speed   \x0A\x0B"
                           "        \0\1\2\3\4\5\6\7",

    /* MSP n. 29 */        "day of week     "
                           "\0\1\2\3\4.          ",

    #ifdef CUSTOMER_NESTLE
    /* MSP n. 30 */        "SWITCHING ON:   "
                           "\0\1\2\3\4.     \5\6:\7\x08",
    #else
    /* MSP n. 30 */        "SWITCHING ON:   "
                           "\0\1\2\3\4.     \5\6:\7\x08",
    #endif

    /* MSP n. 31 */        "SWITCHING OFF:  "
                           "\0\1\2\3\4.     \5\6:\7\x08",

    /* MSP n. 32 */        "RINSING:        "
                           "           \5\6:\7\x08",

    /* MSP n. 33 */        "HOUR:           "
                           "           \5\6:\7\x08",

    /* MSP n. 34 */        "DAY:            "
                           "              \7\x08",

    /* MSP n. 35 */        "MONTH:          "
                           "              \7\x08",

    /* MSP n. 36 */        "YEAR :          "
                           "              \7\x08",

    /* MSP n. 37 */        "COFFEE WATER    "
                           "0=inhib.  cc:\6\7\x08",

    /* MSP n. 38 */        "COFFEE SEQUENCE "
                           "1=cof. before  \x08",

    /* MSP n. 39 */        "Kilowatt hours  "
                           "      \0\1\2\3\4\5\6\7.\x08",

    #ifdef CUSTOMER_NESTLE
    /* MSP n.  40 */       "X4 rinse 2 wat. " //"REGISTRATION out"
                           "in brewer  \6\7\x08ml", //"of service      ",
    #else
    /* MSP n.  40 */       "X4 rinse 2 wat. " //"REGISTRATION out"
                           "in brewer  \6\7\x08ml", //"of service      ",
    #endif

    /* MSP n. 41 */        "first installat."
                           " 0=first       \x08",
    #ifndef CAPPUCCINATORE_INDUX
    /* MSP n. 42 */        "not used        "
                           "                ",
    #else
    /* MSP n. 42 */        "Fresh Milk      "
                           "    \0\1\2\3\4\5\6\7\x08\x09\x0A\x0B",
    #endif 

    #ifdef CUSTOMER_NESTLE
    /* MSP n. 43 */        "VOLTAGE         "
                           "volt:       \6\7.\x08",
    #else
    /* MSP n. 43 */        "VOLTAGE         "
                           "volt:       \6\7.\x08",
    #endif

    #ifdef COMPILO_TEST_MODEM
    /* MSP n. 44 */        "   TEST MODEM   "
                           "      SEL 4     ",
    #else
    /* MSP n. 44 */        "not used        "
                           "                ",
    #endif                                          
    /* MSP n. 45 */        "PRESELECTION    "
                           "                ",

    /* MSP n. 46 */        "INHIBITED       "
                           "----------------",

    /* MSP n. 47 */        "X5 wait time 2  " //"                "
                           "wat. brew. \6\7.\x08s", //"                ",

    /* MSP n. 48 */        "Def. Vibr. mot. " 		//VIBR_MOT_SPEED_GRINDER_1, 2, 3, 4
                           "Speed gr. \x0A  \6\7\x08",

    /* MSP n. 49 */        "ENABLE DISPLAY  "
                           "TEMPERA. 1=YES \x08",

    /* MSP n. 50 */        "X6 wait time 3  " //era "END PROGRAMMING "
                           "empty wat. \6\7.\x08s", //"wait..........  ",

    /* MSP n.  51 */       "TOTAL SELECTIONS"
                           "       \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  52 */       "PART. SELECTIONS"
                           "       \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  53 */       "TOTAL  MONEY    "
                           "       \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  54 */       "PARTIAL MONEY   "
                           "       \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  55 */       "TOTAL TESTS     "
                           "       \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  56 */       "PARTIAL TESTS   "
                           "       \0\1\2\3\4\5\6\7\x08",
    #ifdef COMPILO_DB_CASHLESS
    /* MSP n.  57 */       "total loaded on "
                           "card\x0C  \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  58 */       "part. loaded on "
                           "card\x0C  \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  59 */       "total unloaded  "
                           "card\x0C  \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  60 */       "part. unloaded  "
                           "card\x0C  \0\1\2\3\4\5\6\7\x08",
    #endif
    #ifndef COMPILO_DB_CASHLESS
    #ifdef ABIL_RFID                     
    #ifdef ABIL_CREDIT_RFID
    /* MSP n.  57 */       "total loaded on "
                           "card   \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  58 */       "part. loaded on "
                           "card   \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  59 */       "total unloaded  "
                           "card   \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  60 */       "part. unloaded  "
                           "card   \0\1\2\3\4\5\6\7\x08",
    #else
    /* MSP n.  57 */       " not used       "
                           "                ",

    /* MSP n.  58 */       " not used       "
                           "                ",

    /* MSP n.  59 */       " not used       "
                           "                ",

    /* MSP n.  60 */       " not used       "
                           "                ",
    #endif
    #else
    /* MSP n.  57 */       " not used       "
                           "                ",

    /* MSP n.  58 */       " not used       "
                           "                ",

    /* MSP n.  59 */       " not used       "
                           "                ",

    /* MSP n.  60 */       " not used       "
                           "                ",
    #endif
    #endif
        #ifdef COMPILO_4_LISTE_PREZZI 
    /* MSP n.  61 */       "PART. ^ SEL.  \x0A\x0B"
                           "       \0\1\2\3\4\5\6\7\x08",
        #else
    /* MSP n.  61 */       "PART.  SEL.  \x0A\x0B "
                           "       \0\1\2\3\4\5\6\7\x08",
        #endif
    /* MSP n.  62 */       "PART.  SEL.  \x0A\x0B "
                           "HAPPY  \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  63 */       "PART.  SEL.  \x0A\x0B "
                           "FRE.JUG\0\1\2\3\4\5\6\7\x08",

    /* MSP n.  64 */       "COIN   \x0A        "
                           "          \3\4\5\6\7\x08",

    /* MSP n.  65 */       "PRICE  \x0A\x0B       "
                           "          \3\4\5\6\7\x08",

    /* MSP n.  66 */       "   TEMPERATURE  "
                           "Temp. EV1   \6\7\x08\x09",
    #ifdef BUSINESS_LINE
    /* MSP n.  67 */       "   DEFINITION   "
                           "first coffee \6\7\x08",
    #else
    /* MSP n.  67 */       "   TEMPERATURE  "
                           "Temp. EV2   \6\7\x08\x09",
    #endif
    /* MSP n.  68 */	   "PL for cash     "									//"TEST RUNNING    " spostato in 111 MSA
                           "0=PL1 1=PL2    \x08",							//"   

    #if (GRINDER_MAX_NUM == 2)
    /* MSP n.  69 */       "select grinder 2"
                           "1=yes          \x08",
    #else 
    /* MSP n.  69 */       "  not used      "
                           "                ",
    #endif 
    /* MSP n.  70 */       "preselection    "
                           "BARLEY          ",

    #ifdef CUSTOMER_NESTLE

    /* MSP n.  71 */       "REGISTRATION----"
                           "-OUT OF SERVICE ",
    #else

    /* MSP n.  71 */       "REGISTRATION----"
                           "-OUT OF SERVICE ",
    #endif

    /* MSP n.  72 */       "Selection repeat" 
                           "              \7\x08", 

    #ifdef BUSINESS_LINE
    /* MSP n.  73 */       "heating time    "
                           "      sec.: \6\7.\x08",
    #else
    /* MSP n.  73 */       "   TEMPERATURE  "
                           "Temp. EV3   \6\7\x08\x09",
    #endif
    /* MSP n.  74 */       "PROGRAMMING-----"
                           "-BUTTON \x0A\x0B------",

    /* MSP n.  75 */       "PROGRAMMING-----"
                           "-CLOCK----------",
    #ifdef COMPILO_4_LISTE_PREZZI 
    /* MSP n.  76 */       "PROGRAMMING-----"
                           " PRICES       ^ ",
    #else
    /* MSP n.  76 */       "PROGRAMMING-----"
                           "-PRICES---------",
    #endif
    /* MSP n.  77 */       "PROGRAMMING-----"
                           "-COINS----------",

    /* MSP n.  78 */       "PROGRAMMING-----"
                           "-TEMPERATURE----",

    /* MSP n.  79 */       "PROGRAMMING-----"
                           "-MISCELLANEOUS--",

    /* MSP n.  80 */       "DIAGNOSTICS-----"
                           "----------------",

    /* MSP n.  81 */       "SALES AUDIT-----"
                           "----------------",
    #ifdef COMPILO_4_LISTE_PREZZI 
    /* MSP n.  82 */       "PROGRAMMING-----"
                           " HAPPY PRICE=^  ",
    #else
    /* MSP n.  82 */       "PROGRAMMING-----"
                           "-HAPPY PRICE    ",
    #endif
    /* MSP n.  83 */       "PROGRAMMING-----"
                           "PRODUCT QTY     ",

    /* MSP n.  84 */       "PROGRAMMING-----"
                           "-MAINTENANCE----",

    /* MSP n.  85 */       "PROGRAMMING-----"
                           "RFID CARD       ",

    /* MSP n.  86 */       "TEST MOV. SUGAR "
                           "sel 4           ",

    /* MSP n.  87 */       "Tea Bag         "
                           "0=inhibit     \7\x08",
    #ifdef TEST_CICLICO
    /* MSP n. 88 */        "numero cicli    "
                           "           \4\5\6\7\x08",

    /* MSP n. 89 */        "pausa ciclico   "
                           "sec:       \4\5\6\7\x08",

    /* MSP n. 90 */        "selez. ciclico  "
                           "0=fissa        \x08",
    #else
    /* MSP n. 88 */        "machine code    "
                           "  A        \4\5\6\7\x08",

    /* MSP n. 89 */        "machine code    "
                           "  B        \4\5\6\7\x08",

    /* MSP n. 90 */        "message number  "
                           "               \x08",
    #endif
    /* MSP n. 91 */        "coin-mech type  "
                           "\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F",
    #ifdef CODICE_ACCESSO_PROG
    /* MSP n. 92 */        "prog menu       "
                           "access code  \6\7\x08",
    #else
    /* MSP n. 92 */        "not used        "
                           "                ",
    #endif

    #ifdef CUSTOMER_NESTLE
    /* MSP n. 93 */        "stirrer 0=before"
                           " 1=after       \x08",
    #else
    /* MSP n. 93 */        "stirrer 0=before"
                           " 1=after       \x08",
    #endif

    /* MSP n. 94 */        "fan time        "
                           "min.        \5\6\7\x08",

    /* MSP n. 95 */        "Beep time       "
                           "             \7.\x08",

    #ifdef CUSTOMER_NESTLE
    /* MSP n. 96 */        "decimal number  "
                           "               \x08",
    #else
    /* MSP n. 96 */        "decimal number  "
                           "               \x08",
    #endif

    /* MSP n. 97 */		   "PL for cashless "								//"confirm partial " spostato in 112 MSA
                           "0=PL1 1=PL2    \x08",								//"reset  press P10",

    /* MSP n. 98 */        "language:       "
						   "        english ",
    #ifdef ABIL_TASTO_STOP                        
    /* MSP n. 99 */        "    SEL STOP    "
                           "   no=0 yes=1  \x08",
    #else
    /* MSP n. 99 */        "not used        "
                           "                ",
    #endif
    #ifdef ABIL_DELTA_TEMPERATURA
    /* MSP n. 100 */       "   TEMPERATURE  "
                           "Delta        \6\7\x08",
    #else                       
    /* MSP n. 100 */       "not used        "
                           "                ",
    #endif
    #ifdef MODELLO_ESPRESSO
    /* MSP n.101 */        "not used        "
                           "                ",
    #endif
    #ifdef MODELLO_SOLUBILE
    /* MSP n. 101 */        "tuning pump   \x09\x0A"
                            "         \4 \6\7\x08 %",
    #endif
    /* MSP n.102 */        "tuning motor  \x09\x0A"
                           "         \4 \6\7\x08 %",
    #ifdef MODELLO_ESPRESSO
        #ifdef DISABILITA_CONVERSIONE_GRAMMI
    /* MSP n. 103 */       "coffee time     "
                           "grinder     \6\7.\x08",
        #else
    /* MSP n. 103 */       "coffee grams    "
                           "grinder     \6\7.\x08",
        #endif
        #ifdef ABIL_CALIBRAZIONE_MACINA
    /* MSP n.104 */        "tuning grinder  "
                           "         \4 \6\7\x08 %",
        #else
    /* MSP n. 104 */       "Preselection    "
                           "NO SUGAR        ",
        #endif                       
    #else
    /* MSP n. 103 */       "TEST MOV. SUGAR "
                           "sel 4           ",

    /* MSP n. 104 */       "Preselection    "
                           "NO SUGAR        ",
    #endif
    /* MSP n. 105 */       "extra milk      "
                           "quantity    +\7.\x08",
    #ifdef ABIL_MOTORI_VIRTUALI
    /* MSP n. 106 */       "Latte-Macchiato "
                           "START BREWER\6\7.\x08",
    #else
    /* MSP n.106 */        "not used        "
                           "                ",
    #endif
    #ifdef ABIL_LIMIT_CURRENT
    /* MSP n. 107 */       "Limiting current"
                           "10 A            ",
    #else
    /* MSP n. 107 */       "    Not Used    "
                           "                ",
    #endif                        
    #ifdef ABIL_RISCALDATORE
    /* MSP n.  108*/       "   TEMPERATURE  "
                           "heater:      \6\7\x08",
    #else
    /* MSP n.108 */        "not used        "
                           "                ",
    #endif
    /* MSP n. 109 */       "coffee grains   "
                           "[\x0A\x0B\x0C\x0D.\x0E]  \4\5\6\7.\x08",

    /* MSP n. 110 */       "water quantity  "
                           "ESPRESSO   -\7\x08 %",

    /* MSP n. 111 */       "canister        "
                           "Cafe 2    n:   \x08",

    /* MSP n. 112 */       "Cafe 2  price   "
                           "0=+ 1=-       \7\x08",

    #if defined(MODELLO_SOLUBILE) && defined(UPDATE_DECAF)
    /* MSP n. 113 */       "ev-mixer        "
                           "CAFE 2    n:   \x08",
    #else
    /* MSP n. 113 */       "ev-mixer        "
                           "CAFE 2    n:   \x08",
    #endif

    /* MSP n. 114 */       "Enable preselect"
                           "button  \0\1:\2\3\4\5\6",

    /* MSP n. 115 */       "canister        "
                           "SUGAR        n:\x08",

    /* MSP n. 116 */       "X7 rinsing      " //"access code     "
                           "temperat.  \6\7\x08  ", //"INHIBITED       ",

    /* MSP n. 117 */       "Preselection    "
                           "ESPRESSO        ",

    /* MSP n. 118 */       "Preselection    "
                           "EXTRA SUGAR     ",

    /* MSP n. 119 */       "PRODUCT         "
                           "MILK  LM     n:\x08",

    /* MSP n. 120 */       "Enable  counter "
                           " 0=no  1=yes   \x08",

    /* MSP n. 121 */       "extra sugar     "
                           "quantity    +\7.\x08",

    /* MSP n. 122 */       "canister        "
                           "BARLEY       n:\x08",

    /* MSP n. 123 */       "ev-mixer        "
                           "BARLEY       n:\x08",

    /* MSP n. 124 */       "BARLEY price    "
                           "0=+ 1=-       \7\x08",

    /* MSP n. 125 */       "n.\x0E\x0F off \0\1\2 \3  "
                           "\4\5:\6\7 \x08\x09-\x0A\x0B-20\x0C\x0D",

    /* MSP n. 126 */       "n.\x0F  NO         "
                           "OUT OF SERVICE  ",

    #ifdef CUSTOMER_NESTLE

    /* MSP n. 127 */       "stirrer         "
                           "\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F",

    /* MSP n. 128 */       "cup sensor      "
                           "1=Enable       \x08",

    #else
    /* MSP n. 127 */       "stirrer         "
                           "\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F",

    /* MSP n. 128 */       "cup sensor      "
                           "1=Enable       \x08",
    #endif

    /* MSP n. 129 */       "Vibr.mot.       " 		//VIBR_MOT_TIME_GRINDER_1, 2, 3, 4
                           "Time gr.     \6\7\x08",

    /* MSP n. 130 */       "Vibr. mot.      " 		//VIBR_MOT_SPEED_GRINDER_1, 2, 3, 4
                           "Speed gr.    \6\7\x08",

    /* MSP n. 131 */       "PWM Pump        "
                           "  \x0A\x0B\x0C%          ",
#ifdef MODELLO_ESPRESSO
#ifdef SELECT_TYPE_FREE_VEND
    /* MSP n. 132*/        "FREE VEND enable"
                           "0=no 1=1 2=++  \x08",
#else
    /* MSP n. 132*/        "not used        "
                           "                ",
#endif
    /* MSP n. 133 */       "dec. cof.grounds"
                           "[\x0A\x0B\x0C\x0D\x0E]    \4\5\6\7\x08",
#endif

#ifdef MODELLO_SOLUBILE
#ifdef SELECT_TYPE_FREE_VEND
    /* MSP n. 132*/        "FREE VEND enable"
                           "0=no 1=1 2=++  \x08",
#else
    /* MSP n. 132*/        "not used        "
                           "                ",
#endif
    /* MSP n. 133 */       "not used        "
                           "                ",
#endif

    /* MSP n. 134 */       "product qty   \x0F "
                           "[\x0A\x0B\x0C\x0D.\x0E]  \4\5\6\7.\x08",

    /* MSP n. 135 */       "Preselection    "
                           "JUG             ",
    #ifdef ABIL_CAPPUCCINATORE
    /* MSP n. 136 */       "EV Fresh-milk   "//ev latte fresco
                           "            \6\7.\x08",
                           #else
    /* MSP n. 136 */       "not used        "
                           "                ",
    #endif
    /* MSP n. 137 */       "prod. \x0F warning "
                           "thresold: \4\5\6\7.\x08",

    /* MSP n. 138 */       "abil stop prod \x0F"
                           "1=stop         \x08",

    /* MSP n. 139 */       "TOTAL  FREE     "      //VA_302 num. vendite gratuite storico
                           "       \0\1\2\3\4\5\6\7\x08",

    /* MSP n. 140 */       "PART.    FREE   "      //VA_304 num.vendite gratuite parziale
                           "       \0\1\2\3\4\5\6\7\x08",

    /* MSP n. 141 */	   "TOTAL  CASH     "      //CA_201 valore venduto cash storico
                           "CASH   \0\1\2\3\4\5\6\7\x08",

    /* MSP n. 142 */       "PART.  CASH     "      //CA_203 valore venduto cash parziale
                           "CASH   \0\1\2\3\4\5\6\7\x08",

    /* MSP n. 143 */	   "N.TOT. SEL. CASH"      //CA_202 num.vendite per cassa storico
                           "       \0\1\2\3\4\5\6\7\x08",

    /* MSP n. 144*/        "N.PART.SEL. CASH"	   //CA_204 num. vendite per cassa parziale
                           "       \0\1\2\3\4\5\6\7\x08",

    /* MSP n. 145 */       "TOTAL  CASH-BOX "      //CA_305 valore della  cassa storico
                           "       \0\1\2\3\4\5\6\7\x08",

    /* MSP n. 146 */       "PART.  CASH-BOX "      //CA_301 valore della  cassa parziale
                           "       \0\1\2\3\4\5\6\7\x08",
    #ifdef COMPILO_DB_CASHLESS
    /* MSP n. 147 */       "TOTAL SEL. CARD\x0C"      //DA_202  num. vendite per carta storico
                           "       \0\1\2\3\4\5\6\7\x08",

    /* MSP n. 148 */       "PART. SEL. CARD\x0C"      //DA_204	  num. vendite per carta parziale
                           "       \0\1\2\3\4\5\6\7\x08",
    #else
    /* MSP n. 147 */       "TOTAL  SEL. CARD"      //DA_202  num. vendite per carta storico
                           "       \0\1\2\3\4\5\6\7\x08",

    /* MSP n. 148 */       "PART.  SEL. CARD"      //DA_204	  num. vendite per carta parziale
                           "       \0\1\2\3\4\5\6\7\x08",
    #endif
    /* MSP n.149 */        "Ejection tubes  "
                           "b. :4-5-7-8-9-10",

    /* MSP n.150 */        "escrow enable   "
                           "0=enab. 1=dis. \x08",

    /* MSP n.151 */        "credit max      "
                           "        \1\2\3\4\5\6\7\x08",

    /* MSP n.152 */        "rest  max       "
                           "        \1\2\3\4\5\6\7\x08",

    /* MSP n.153 */        "Sell type       "
                           "0=sing. 1=mult.\x08",

    /* MSP n.154 */        "Token value     "
                           "        \1\2\3\4\5\6\7\x08",

    /* MSP n.155 */        "coin rest   \x0A  \x08"
                           " 0=acc. 1=disab.",

    /* MSP n.156 */        "coin no rest \x0A \x08"
                           " 0=acc. 1=disab.",

    /* MSP n.157 */        "MDB tubes value "
                           "        \1\2\3\4\5\6\7\x08",

    /* MSP n.158 */        "Bill validator  "
                           "enab=  0;1;2  =\x08",

    /* MSP n.159 */        "PROGRAMMING-----"
                           "- MDB ----------",

    /* MSP n.  160 */      "Preselection    "
                           "EXTRA MILK      ",

    /* MSP n.  161 */      "Preselection    "
                           "ESPRESSO        ",
    #ifdef EASY_PRESEL
    /* MSP n.  162 */      "Preselection    "
                           "SELECTIONS 25-36",
    #else
    /* MSP n.  162 */      "Preselection    "
                           "DECAFFEINATED   ",
    #endif                      
    #ifdef TIPO_NO_CUP
    /* MSP n.  163 */      "Preselection    "
                           "not used        ",
    #else
    /* MSP n.  163 */      "Preselection    "
                           "NO CUP          ",
    #endif
    /* MSP n.  164 */      "Preselection    "
                           "BARLEY          ",

    /* MSP n.  165 */      "   TEST GROUP   "
                           "Absorption  sel4",



#ifdef BUSINESS_LINE
	#if !defined(MODELLO_EC) && defined(MODELLO_ESPRESSO)
    /* MSP n.  166 */      "boiler  cc:     "
                           "0=400   1=800  \x08",
    #else
    /* MSP n.  166 */      "not used        "
                           "                ",
    #endif
#else
    /* MSP n.  166 */      "Power adj. pump "
                           "0=no 1=yes     \x08",
#endif	
	
    /* MSP n. 167 */	   "quick menu      "		/* @AS Issue_#1598: limited access to quick menù functionalities */
                           "access code  \6\7\x08",
    #ifdef ABIL_CAPPUCCINATORE
    /* MSP n.  168 */      "EV air          "
                           "Fresh-milk  \6\7.\x08",
    #else
    /* MSP n.  168 */       "not used        "
                            "                ",
    #endif
    /* MSP n.  169 */       "TUNING          "
                            "MOTORS          ",

    /* MSP n. 170  */       "Calibrate Coffee"
                            "Push PROG   \5\6\7\x08",
    #ifdef ABIL_LATTE_MACCHIATO
    /* MSP n.  171 */       "LM Milk water   "		//EV virtuale     
                            "Number=        \x08",
    #else
    /* MSP n.  171 */       "not used        "
                            "                ",
    #endif
    #ifdef MODELLO_ESPRESSO
    /* MSP n.  172 */       " uninstallation "
                            "   10=START     ",

    /* MSP n.  173 */       "   TEMPERATURE  "
                            "Espresso    \6\7\x08\x09",
    #else
    /* MSP n.  172 */       "not used        "
                            "                ",

    /* MSP n.  173 */       "   TEMPERATURE  "
                            "boiler      \6\7\x08\x09",
    #endif

    /* MSP n.  174 */       "X8 Clousure     " //"uninstallation  "
                            "brewer      \6\7\x08%", //"in progress...  ",

    /* MSP n.  175 */       "   TEMPERATURE  "
                            "Latte Mac.  \6\7\x08\x09",

    /* MSP n.  176 */       "code   ID 101   "
                            "       \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  177 */       "code   ID 104   "
                            "       \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  178 */       "code   ID 106   "
                            "       \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  179 */       "address VIDTS   "
                            "             \6\7\x08",
    #ifdef  UPD_PROG_EVADTS
    /* MSP n.  180 */       "Protocol        "
                            "\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F",
    #else
    #ifdef SELECT_TYPE_DATA_AUDIT
    /* MSP n.  180 */       "DataAudit 0=TMON"
                            "1=DDCMP 2=DIAG \x08",
    #else
    /* MSP n.  180 */       "not  used       "
                            "                ",
    #endif
    #endif
    /* MSP n.  181 */       "PROGRAMMING-----"
                            "-ID. MACHINE    ",
    #ifdef SUMMERTIME
    /* MSP n. 182 */        "Summer Time     "
                            "1=yes          \x08",
    #else                   
    /* MSP n. 182 */        "not used        "
                            "                ",
    #endif  

    /* MSP n. 183 */        "LOW PRESSURE    "
                            "                ", //"1=Save  2=Repeat",
                            
    /* MSP n. 184 */        "X9 wait time 3  " //era "CALIBRATION IS  "
                            "last cof. \7\x08 min", //"NOT POSSIBLE    ",
                            
    /* MSP n. 185 */        "X10 min cof. qty" //era "Remove Brewer   "
                            "to engage \6\7\x08 cc", //"Push PROG button",
                            
    /* MSP n. 186 */        "A1 PWM Variflex " //era "Replace Brewer  "
                            "move        \6\7\x08%", //"Push PROG Button",
                            
    /* MSP n. 187 */        "A2 Pump On time " //era "   KEY PRESS    "
                            "         \6\7.\x08[s]", //"     >PROG<     ",
                #ifdef COMP_PREZZO_ECO_BIC
    #ifdef EASY_PRESEL
    /* MSP n.  188 */       "Preselection    "
                            "SELECTIONS 37-48",
    #else
    /* MSP n.  188 */       "  Preselection  "
                            "    BIG CUP     ",
    #endif
    #ifdef ABILITAZIONE_SENSORE_CAFFE
    /* MSP n.  189 */       " Coffee Sensor  "
                            " 1=Enable      \x08",
    #else											
    /* MSP n.  189 */       "not used        "
                            "                ",
    #endif
    /* MSP n. 190 */       "WATER           "
                           "percent    +\7\x08 %",

    /* MSP n. 191 */       "+ or   -  PRICE "
                           "0=+  1=-      \7\x08",

    /* MSP n. 192 */       "PRODUCT         "
                           "percent    +\7\x08 %",
                #else
    /* MSP n.  188 */      "not used        "
                           "                ",
    /* MSP n.  189 */      " not used       "
                           "                ",
    /* MSP n.  190 */      "not used        "
                           "                ",
    /* MSP n.  191 */      " not used       "
                           "                ",
    /* MSP n.  192 */      "not used        "
                           "                ",
                #endif                    
    /* MSP n. 193 */       "PREINFUSION     "
                           "0=no   sec.:\7\x08  ",
                           
    /* MSP n. 194 */       "JUG             "
                           "0=no        n:\7\x08",
                           
    /* MSP n. 195 */       "preselection    "
                           "SUGAR           ",
                           
    /* MSP n.  196 */      "preselection    "
                           "LONG            ",
                           
    /* MSP n. 197 */       "water           "
                           "LONG       +\7\x08 %",
        #ifdef DAL_HAPPY_HOUR
    /* MSP n. 198 */       "number of selec."
                           "Bingo       \5\6\7\x08",

    /* MSP n. 199 */       "price with card "
                           "1=price happy  \x08",
        #else
            #ifdef COMPILO_DATI_STANDARD
    /* MSP n. 198 */       "push <PROG> to  "
                           "load:   \0\1\2\3\4\5\6\7",
    #else
    /* MSP n. 198 */       "Default sugar   "
                           "LED:0-5       =\x08",
            #endif
    /* MSP n. 199 */       "not used        "
                           "                ",
        #endif
    /* MSP n. 200*/        "A3 Pump OFF time" //"Open boiler tap "
                            "         \6\7.\x08[s]", //"       10=start ",

    /* MSP n. 201*/        "A5 pressure     " //" end uninstall  "
                           "number        \7\x08", //"close boiler tap",

    /* MSP n. 202*/        "PROGRAMMING-----"
                           "-MDB USD--------",
        #ifdef TRE_USD
    /* MSP n.  203*/       "PROGR. MDB USD \x0F"
                           "  SEL. 4        ",
                            #else
    /* MSP n.  203*/       "PROGR. MDB USD  "
                           "  SEL. 4        ",
       #endif

    /* MSP n.  204 */      "Calibr. motor \x0A\x0B"
                           "gr/sec    \3\4\5\6\7\x08",

    /* MSP n. 205 */       "product \x0A\x0B used "
                           "part.g.\0\1\2\3\4\5\6\7\x08",

    /* MSP n. 206 */       "product \x0A\x0B used "
                           "Tot. g.\0\1\2\3\4\5\6\7\x08",

    /* MSP n. 207 */       "CALIBRATION-----"
                           "PRODUCT FLUX    ",

    /* MSP n. 208 */       "PRODUCT AUDIT---"
                           "------FLUX----- ",

    /* MSP n.  209 */      "   TEST MOTOR   "
                           "Absorption  sel4",

    #ifdef MODELLO_ESPRESSO
    /* MSP n. 210 */       "tun. grinder  \x09\x0A"  // sull ´espresso  non c´e´
                           "         \4 \6\7\x08 %",
    #endif
    #ifdef MODELLO_SOLUBILE
    /* MSP n. 210 */       "not used        "
                           "                ",
    #endif
    #ifdef ABILITO_RESET_DECONTATORE_FILTRO
    /* MSP n. 211 */       "activ.H2o filter"//Frei
                           "Reset  0=no    \x08",
    #else
    /* MSP n. 211 */       "not used        "
                           "                ",
    #endif

    /* MSP n.  212 */      "A6 water after  " //era "Water supply    "    //version E3-E3 servomat
                           "coffee   \6\7\x08[ml]", //"conn.? Start=10 ",   //4

    #ifdef CUSTOMER_NESTLE
    /* MSP n.  213 */      "A7 chamber      " //era "driptray        "
                           "aperture    \6\7\x08%", //"inside? 10=START",
    #else
    /* MSP n.  213 */      "A7 chamber      " //era "driptray        "
                           "aperture    \6\7\x08%", //"inside? 10=START",
    #endif

    /* MSP n.  214 */      "DA rotation     "			// "first install.  " //LIBERO spostato in user 105
                           "0=auto 1=man.  \x08",		//"starts automat. ",

    /* MSP n.  215 */	   "Set preheating  "						//"                "
                           "selection \6\7\x08   ",				//"autom. reset    ", spostato in user 107

    /* MSP n.  216 */      "MDB offset own  "
                           "cup 0=no 1=yes \x08",
    #ifdef VARIGRIND_PRESENCE
    /* MSP n. 217 */       "granulometry    "  // sull ´espresso  non c´e´
                           "\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F",
    #else 
    /* MSP n. 217 */       "not used        "
                           "                ",
    #endif 
    /* MSP n.  218 */      "pricehold query "
                           "no=0 yes=1     \x08",

    /* MSP n.  219 */      "Side water pump "
                           " 0-4           \x08",
    #ifdef ENABLE_BREWER_VARIFLEX
    /* MSP n.  220*/       "Brewer pressure "
                           "0=max 10=min. \7\x08",
    #else
    /* MSP n. 220*/        "Double coffee   "
                           "0=no 1=yes     \x08",
    #endif
    #ifdef ABILITA_PRESENZA_VASCHETTA
    /* MSP n. 221 */       "driptray        "
                           "identif. yes=1-\x08",
    #else
    /* MSP n.  221 */      "not used        "
                           "                ",
    #endif
    #ifdef PROGRAMMABLE_PRESEL_MSG
    /* MSP n.  222*/       "Preselection    "
                           "name:   \0\1\2\3\4\5\6\7",
    #else
    /* MSP n.  222 */      "not used        "
                           "                ",
    #endif

    /* MSP n. 223 */       "Cup size        "
                           "               \x08",

    /* MSP n.  224 */      "vend payment    "
                           "timeout \6\7\x08 sec.",

    #ifdef ABIL_CAPPUCCINATORE
    /* MSP n. 225 */       "ev fresh milk   "
                           "delay       \6\7.\x08",

    /* MSP n. 226 */       "ev air fresh    "
                           "milk delay  \6\7.\x08",
    #else
    /* MSP n.  225 */      "   not  used    "
                           "                ",

    /* MSP n.  226 */      "   not  used    "
                           "                ",
    #endif

    /* MSP n.  227*/       "PROGRAMMING ----"
                           "  VARIGRIND ^   ",

    /* MSP n.  228*/       "PROGRAMMING ----"
                           "- MILKER    ----",
    #ifdef MODELLO_DOPPIO
    #ifdef DISABILITA_BICC   
    /* MSP n. 229 */       "dispensing cup  "
                           "0=yes 1=no     \x08",
    #else
    /* MSP n. 229 */       "   not  used    "
                           "                ",
    #endif
    #else
    /* MSP n. 229 */       "   not  used    "
                           "                ",
    #endif
    /* MSP n.230  */   	   "PROGRAMMING ----"
                           "  VARIGRIND 2   ",

    /* MSP n.231  */   	   "PRESEL. NUM ^)  " 		// PP1 (PP101) presel number
                           "           \4\5\6\7\x08",

    /* MSP n.232  */   	   "Verified data   "
                           "\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F",         // 	"         <4>=yes",

    /* MSP n.  233 */      "Water Flush mode"		// ex PP1 (PP103) presel identification
                           "1=ON 0=OFF     \x08",		//

    /* MSP n.  234 */      "xxxxxx          "		// ex PP1 (PP107) presel number since reset
                           "                ",		//

    /* MSP n.  235 */      "xxxxxx          "		//"Preselection    "
                           "                ",		// "not used        ",

    /* MSP n.  236 */      "PROGRAMMING ----"
                           "RFID BLACK LIST ",

    /* MSP n.  237 */      "block card \x09\x0A   "
                           "number      \5\6\7\x08",
    #ifdef  MODELLO_DOPPIO
    /* MSP n. 238*/        "TEST CUP STATION"
                           "sel 4           ",
    #else
    /* MSP n. 238 */       "not used        "
                           "                ",
    #endif

#if defined ENABLE_BREWER_VARIFLEX
    /* MSP n. 239 */       "PROGRAMMING ----"
                           "   VARIFLEX     ",

#elif defined ABIL_GRUPPO_MICRO
    /* MSP n. 239 */       "PROGRAMMING ----"
                           "   MICRO        ",
#else
    /* MSP n. 239 */       "PROGRAMMING ----"
                           "                ",
#endif

    /* MSP n. 240 */       "   TEMPERATURE  "
                           "Temp. EV4   \6\7\x08\x09",

    /* MSP n. 241 */       "Preselection    "
                           "SELECTIONS 49-60",

    /* MSP n. 242 */       "xxxxxx          "		//"coffee time     "
                           "                ",

#ifdef CAPPUCCINATORE_INDUX
    /* MSP n. 243 */       "not used        " // "Time cleaning   "
                           "                ", //"rhMM1.v+  \5\6:\7\x08 ",   // nome commerciale MILK module
#else
    /* MSP n. 243 */ 	   "Time cleaning   "
                           "MILK Mod.  \5\6:\7\x08",
#endif

    /* MSP n. 244*/        "F.Milk  Topping-"
                           "switch  yes=1- \x08",

    /* MSP n. 245*/        "Calibrate Cof  2"
                           "Push PROG   \5\6\7\x08",

    /* MSP n. 246*/        "cup sens.thresh."
                           "0=dis  \6\7\x08 - \x0A\x0B\x0C",

    /* MSP n. 247*/        "  Set Free Vend "
                           "Ins hours   \5\6\7\x08",

    /* MSP n. 248*/        "Enable dataaudit"
                           "before  1=yes  \x08",

    /* MSP n. 249 */       "Instant Scaling "
                           "Factor   \4 \6\7\x08 %",

    /* MSP n. 250 */       "TEST STIRRER    "
                           "sel 4           ",

    /* MSP n. 251 */       " Security Level "
                           "level 1-4      \x08",

    /* MSP n. 252*/        "Calibrate Cof  3"
                           "Push PROG   \5\6\7\x08",

    /* MSP n. 253*/        "Calibrate Cof  4"
                           "Push PROG   \5\6\7\x08",

    /* MSP n. 254 */       "coffee repeat   "
                           "0=disabled     \x08",

    /* MSP n. 255 */       "Current language"
                           "\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F",

};

const u8 __far GB_MS_NOME_SELEZ_1[MAX_NOME_SELEZ][16] = {
#ifdef CUSTOMER_NESTLE
    /* 00 */          "standard        ",
    /* 01 */          "Ristretto       ",
    /* 02 */          "Espresso        ",
    /* 03 */          "Double Espresso ",
    /* 04 */          "Americano       ",
    /* 05 */          "Lungo           ",
    /* 06 */          "Babyccino       ",
    /* 07 */          "Hot Chocolate   ",
    /* 08 */          "Mochaccino      ",
    /* 09 */          "Flat White      ",
    /* 10 */          "Latte Macchiato ",
    /* 11 */          "Cappuccino      ",
    /* 12 */          "Esp. Macchiato  ",
    /* 13 */          "White Coffee    ",
    /* 14 */          "Cortado         ",
    /* 15 */          "Hot Water       ",
    /* 16 */          "Tea             ",
    /* 17 */          "Chococcino      ",
    /* 18 */          "Milk Chocolate  ",
    /* 19 */          "Dark Chocolate  ",
    /* 20 */          "custom          ",
    #else

    /* 00 */          "standard        ",
    /* 01 */          "Cappuccino      ",
    /* 02 */          "Capp-cioc       ",
    /* 03 */          "Latte Macchiato ",
    /* 04 */          "Cafe Latte      ",
    /* 05 */          "Espresso        ",
    /* 06 */          "Espresso Macch. ",
    /* 07 */          "MoccaCino       ",
    /* 08 */          "Chocolate       ",
    /* 09 */          "Choco-Milk      ",
    /* 10 */          "Hot Water       ",
    /* 11 */          "Milk            ",
    /* 12 */          "Cafe Au Lait    ",
    /* 13 */          "Instant coffee  ",
    /* 14 */          "Tea             ",
    /* 15 */          "Instant white   ",
    /* 16 */          "Strong choco    ",
    /* 17 */          "Barley          ",
    /* 18 */          "Barley Cappucc. ",
    /* 19 */          "Cafe Macchiato  ",
    /* 20 */          "custom          ",
        #endif

};

#ifdef EASY_PRESEL
//	nomi preselezioni estesi a 16 caratteri
const u8 __far GB_MS_NOME_PRESEL_1[MAX_NOME_PRESEL][16] = {
    /* 00 */      	  "SELECTIONS 25-36",
    /* 01 */          "BARLEY          ",
    /* 02 */          "NO CUP          ",
    /* 03 */          "EXTRA MILK      ",
    /* 04 */          "ESPRESSO        ",
    /* 05 */          "NO SUGAR        ",
    /* 06 */          "EXTRA SUGAR     ",
    /* 07 */          "WITH CUP        ",
    /* 08 */          "SUGAR 1         ",
    /* 09 */          "MORE SUGAR      ",
    /* 10 */          "SELECTIONS 37-48",
    /* 11 */          "LONG            ",
    /* 12 */          "JUG             ",
    /* 13 */          "SELECTIONS 49-60",
}
#else

const u8 __far GB_MS_NOME_PRESEL_1[MAX_NOME_PRESEL][7] = {
    /* 00 */      	  "DECAF. ",//st- presel per + 10 selezioni dirette  (sel 11-20) ( presel Nr 0 - mes 162 ) / ( presel 0 + 7 = sel 31-40 )  servomat     
    /* 01 */          "BARLEY ",
    /* 02 */          "NO CUP ",
    /* 03 */          "EX-MIL.",
    /* 04 */          "ESPRES.",
    /* 05 */          "NO SUG.",
    /* 06 */          "EX SUG.",
    /* 07 */          "CUP    ",
    /* 08 */          "SUGAR 1",
    /* 09 */          "SUG.++ ",
            #ifdef COMP_PREZZO_ECO_BIC
    /* 10 */          "BIG CUP",//st- presel per + 10 selezioni dirette  (sel 21-30) ( presel Nr 7 - mes 188 ) / ( presel 0 + 7 = sel 31-40 )  
            #else
    /* 10 */          "       ",
            #endif
    /* 11 */          "LONG   ",
    /* 12 */          "JUG    ",//st- presel caraffa usata anche per la KP    
};
#endif

const u8 __far GB_MSAP_PAR_MAINTENANCE[MAX_PAR_MAINTENANCE][32] = {
    /* n. 0 */       	"water filter cnt"  // ex 129 MSP
                        "[\x0A\x0B\x0C\x0D\x0E]    \4\5\6\7\x08",
    #ifdef MODELLO_ESPRESSO
    /* n. 1 */    		"dec. cof. brewer"  // ex 130 MSP
                        "[\x0A\x0B\x0C\x0D\x0E]    \4\5\6\7\x08",

    /* n. 2 */    		"dec. cof.grounds"  // ex 131 MSP
                        "[\x0A\x0B\x0C\x0D\x0E]    \4\5\6\7\x08",
    #else 
    /* n. 1 */    		"not used        "  // ex 130 MSP
                        "                ",

    /* n. 2 */    		"not used        "  // ex 131 MSP
                        "                ",
    #endif  

    /* n. 3 */        	"Blocking counter"  // ex 252 MSP
                        "[\x0A\x0B\x0C\x0D\x0E]    \4\5\6\7\x08",

    /* n. 4 */        	"Perc. threshold "  // ex 253 MSP
                        "0=disabled    \7\x08",

    /* n. 5 */        	"insert code     "  // ex 1 MSP
                        "             \6\7\x08",

    /* n. 6 */        	"Mainten. counter"  // ex 252 MSP
                        "[\x09\x0A\x0B\x0C\x0D\x0E]  \4\5\6\7\x08\x30",

    /* n. 7 */        	"Maint. threshold"  // ex 252 MSP
                        "          \4\5\6\7\x08\x30",

};

#ifdef PROGRAMMABLE_PRESEL_MSG
const u8 __far GB_MS_PROG_NOME_PRESEL[MAX_PROG_NOME_PRESEL][8] = {
    /* 00 */          "standard",
    /* 01 */          "DECAF   ",
    /* 02 */          "LACTOSE ",
    /* 03 */          "MILK    ",
    /* 04 */          "SUGAR   ",
    /* 05 */          "F.MILK  ",
    /* 06 */          "COFFEE  ",
    /* 07 */          "COFFEE 2",
    /* 08 */          "VANILLA ",
    /* 09 */          "custom  ",
};
#endif 

const u8 __far GB_MS_TIPO_SCHIUMA[MAX_TIPO_SCHIUMA][16] = {

    /* 00 */          "Hot no Foam     ",
    /* 01 */          "Hot Classic Foam",
    /* 02 */          "Hot Fluffy  Foam",
    /* 03 */          "Hot Barista Foam",

    /* 04 */          "Cold no Foam    ",
    /* 05 */          "Cold Classic Fo.",
    /* 06 */          "Cold Fluffy Foam",
    /* 07 */          "Cold Barista Fo.",

};

const u8 __far GB_MS_TIPO_FLUSSO_1[MAX_TIPO_FLUSSO][8] = {

    /* 00 */          "     low",
    /* 01 */          "  medium",
    /* 02 */          "    high",
};

const u8 __far GB_MS_NOME_GIORNO_1[MAX_NOME_GIORNO][5] = {

    /* 00 */          "Monda",
    /* 01 */          "Tuesd",
    /* 02 */          "Wedne",
    /* 03 */          "Thurs",
    /* 04 */          "Frida",
    /* 05 */          "Satur",
    /* 06 */          "Sunda",
};

const u8 __far GB_MS_SI_1[5] = {" YES ",};
const u8 __far GB_MS_NO_1[5] = {"  NO ",};

//............... lavaggio sanitario .............

const u8 __far  GB_MSG_LAV_GRUPPO[MAX_LAV_GRUPPO][32] = {

    /* MSA n. 00 */        "xxxxxxx         "       //libero disponibile era "Health cleaning "      //lav. sanitario  //entrata lavaggio sanit
                           "                ",                                                //"Brewer  P1=start",     
#if !defined(MODELLO_BONA) || defined(MODELLO_DOPPIO)
    /* MSA n. 1  */        "3/14 Put tablet "      //put pastille    
                           " push Start=10  ",     //and push  P8    

    /* MSA n. 2  */        "\3/14 tab. diss.\4"       //P3 to continue  
                           "wait    min \0:\1\2",
#else
    /* MSA n. 1  */        "Put pastille and"      //put pastille    
                           "push   P10=START",     //and push  P8    

    /* MSA n. 2  */        "tab dissolve    "       //P3 to continue  
                           "min         \0:\1\2",
#endif 

    /* MSA n. 3  */        "cleaning        "      	//cleaning
                           "6 X          \2\3\4",

    /* MSA n. 4  */        "wait please     "      	// wait  please
                           "                ",

#ifdef ENABLE_BREWER_VARIFLEX
#ifndef MODELLO_TS
    /* MSA n.  5 */		   "Proc.Type: 8=MAN"
                           "9=A.Skip AUTO=10",
#else 
    /* MSA n.  5 */        "xxxxxxx         "
                           "                ",	//"debug cleaning  ",     //debug Lav.gruppo
#endif 
#else 
    /* MSA n.  5 */        "xxxxxxx         "
                           "                ",                             //"debug cleaning  ",     //debug Lav.gruppo 
#endif 

#if !defined(MODELLO_BONA) || defined(MODELLO_DOPPIO)
    /* MSA n. 6  */        "2/14 Cleaning   "      //Inizio Lavaggio 
                           " Active         ",
#else
    /* MSA n. 6  */        "    Cleaning    "      //Inizio Lavaggio 
                           "     Active     ",
#endif 

    /* MSA n. 7  */        "                "      //clear screen 
                           "                ",

    /* MSA n. 8  */        "11/14 Skip final" 	//richiesta per il caffè di pulizia al termine del lavaggio sanitario
                           "coffee YES=1    ",

    /* MSA n. 9  */        "\4\5/14 Rep. clean"
                           "\x08/2 YES=10 NO=ot",

    /* MSA n. 10  */       "1/14 Man. brush "
                           "  and push 10   ",

    /* MSA n. 11  */       "4/14 Brewer is  "
                           "     closing    ",

    /* MSA n. 12  */       "5/14 2nd diss.  "
                           "cycle will start",

    /* MSA n. 13  */       "\4\5/14 \0\1\2 Clean."
                           "   active \x09\x0A\x0B   ",

    /* MSA n. 14  */       "      Brewer in "
                           " open position  ",

    /* MSA n. 15  */       "14/14 Brew. Cle."
                           "Done.    10=Exit",

    /* MSA n. 16  */       "\4\5\6\7\x08 Mixer \0   "
                           "rinsing         ",

    /* MSA n. 17  */       "\4\5\6\7\x08 Brewer    "
                           "Rinsing         ",

    /* MSA n. 18  */       "Start procedure?"
                           "   YES=10 NO=8  ",

    /* MSA n. 19  */       "\4\5/14 \0\1\2 Clean."
                           "   wait please  ",

    /* MSA n. 20  */       "12/14 Coffee    "
                           "delivery        ",

    /* MSA n. 21  */       "\1/\2\3 emptying   "
                           "in progress     ",

    /* MSA n. 22  */       "\1/\2\3 conn. desc."
                           "solution   OK=10",

    /* MSA n. 23  */       "\1/\2\3 fill. desc."
                           "sol. in progress",

    /* MSA n. 24  */       "\0\1/\2\3 water     "
                           "flows?    YES=10",

    /* MSA n. 25  */       "\0\1/\2\3  descaling"
                           "solution filling",

    /* MSA n. 26  */       "\1/\2\3  solution  "
                           "action=>min \4:\5\6",

    /* MSA n. 27  */       "\0\1/\2\3 desc. sol."
                           "draining \4/\5    ",

    /* MSA n. 28  */       "\0\1/\2\3 result?   "
                           "OK=10   NO=OTHER",

    /* MSA n. 29  */       "\0\1/\2\3 connect   "
                           "water      OK=10",

    /* MSA n. 30  */       "\0\1/\2\3 filling   "
                           "water in progr. ",

    /* MSA n. 31  */       "\0\1/\2\3 rinsing   "
                           "with water      ",

    /* MSA n. 32  */       "\0\1/\2\3 disp. and "
                           "test water  Y=10",

    /* MSA n. 33  */       "\0\1/\2\3 catch     "
                           "water to test   ",

    /* MSA n. 34  */       "\0\1/\2\3 descaling "
                           "done. EXIT=10   ",

    /* MSA n. 35  */       "\0\1/\2\3 open      "
                           "boiler tap Y=10 ",

    /* MSA n. 36  */       "\0\1/\2\3 close     "
                           "boiler tap Y=10 ",

    /* MSA n. 37 */       "  auto rinsing  "
                           "   in progress  ",

    /* MSA n. 38 */       " Periodic rinse "
                           "  in \0 seconds  ",

};

#ifdef AGGIUNTA_MESSAGGI_OFF
const u8 __far GB_MES_ERRORI_AGGIUNTI[MAX_MES_ERRORI_AGGIUNTI][32] = {

    /*  n. 0   */           "                "
                            "                ",

    #ifdef CUSTOMER_NESTLE

    /*  n. 1   */           "           drain"   //OFF 3  = 
                            "drip tray       ",

    /*  n. 2   */           "  out of service"   //OFF 6a / 6b  = 
                            "NO WATER        ",

    /*  n. 3   */           " Water flow too "   //OFF 7  = 
                            "low in H.circuit",

    /*  n. 4   */           "           CHECK"	 //OFF 8 / 8b = 
                            "BREWER          ",

    /*  n. 5   */           " REFILL COFFEE  "   //OFF 9a / 9d  = 
                            "                ",

#else
    /*  n. 1   */           "           drain"   //OFF 3  = 
                            "drip tray       ",

    /*  n. 2   */           "  out of service"   //OFF 6a / 6b  = 
                            "NO WATER        ",

    /*  n. 3   */           " Water flow too "   //OFF 7  = 
                            "low in H.circuit",

    /*  n. 4   */           "           CHECK"	 //OFF 8 / 8b = 
                            "BREWER          ",

    /*  n. 5   */           " REFILL COFFEE  "   //OFF 9a / 9d  = 
                            "                ",
#endif

    /*  n. 6   */           "                "
                            "                ",
};

#endif 

#ifdef PROG_PAR_GRUPPO_ESPRESSO

const u8 __far  GB_MSAP_ParGrEspresso[MAX_ParGrEspresso][32] = {

#ifdef ENABLE_BREWER_VARIFLEX
    /* MSA n. 0  */        "BREWER SIZE     "  				//"BREWER DIAMETER "
                           "0=36   1=45  \6\7\x08",
#else /* gruppo micro */
    /* MSA n. 0  */        "BREWER SIZE     "  				//"BREWER DIAMETER "
                           "0=36   1=40  \6\7\x08",
#endif
    /* MSA n. 1 */         "BREWER POSITION "				//"POSIT. STAND BY "
                           "0=CLOSE 1=OP. \7\x08",
#ifdef ENABLE_BREWER_VARIFLEX
    /* MSA n. 2  */        "AUTOM.ADJUSTMENT"            	//"abil calib tempo"
                           "F.TUNING  1=yes\x08",
    /* MSA n. 3  */        "    ENCODER     "          		//"imp. per grammo "
                           "IMPULSE/GR. \6.\7\x08",
#else
    /* MSA n. 2  */        "  OFF9  Grinder "          		//Non usato
                           "  Speed \6\7\x08     ",
    /* MSA n. 3  */        "    NOT USED    "          		//Non usato
                           "                ",
#endif
    /* MSA n. 4  */         "  TAB DISSOLVE  "          		//st tempo scioglimento pastiglia  provvisorio
                           "PAUSE  SEC.  \6\7\x08",
    /* MSA n. 5  */        "ENCODER  GRIND 2"          		//"imp. per grammo "
                           "IMPULSE/GR. \6.\7\x08",
    /* MSA n. 6  */        "GRINDER FUNCTION"          		//Modalità funzionamento macina:
                           "IM EN/GR 1=yes \x08", 			//0--> GR/SEC 1--> IMP/GR
    /* MSA n. 7  */        "    NOT USED    "          		//Non usato
                           "                ",
    /* MSA n. 8  */        "GRIND 2 FUNCTION"          		//Modalità funzionamento seconda macina:
                           "IM EN/GR 1=yes \x08", 			//0--> GR/SEC 1--> IMP/GR
#ifdef ENABLE_BREWER_VARIFLEX
    /* MSA n. 9 */        "DELIVERY   PHASE"          		//Anticipa fine erogazione:
                           "FASTER   1=yes \x08", 			//0--> NO 1--> SI
#else /* gruppo micro */
    /* MSA n. 9  */       "    NOT USED    "          		//Non usato
                           "                ",
#endif

    /* MSA n. 10  */		"ENCODER  GRIND 3"          			//"imp. per grammo "
                            "IMPULSE/GR. \6.\7\x08",
    /* MSA n. 11  */		"GRIND 3 FUNCTION"						//Modalità funzionamento macina 3:
                            "IM EN/GR 1=yes \x08",					//0--> GR/SEC 1--> IMP/GR
    /* MSA n. 12  */		"ENCODER  GRIND 4"          			//"imp. per grammo "
                            "IMPULSE/GR. \6.\7\x08",
    /* MSA n. 13  */		"GRIND 4 FUNCTION"						//Modalità funzionamento macina 4:
                            "IM EN/GR 1=yes \x08",					//0--> GR/SEC 1--> IMP/GR
    /* MSA n. 14 */         "RESET GROUP IN  "          		//autorestart gruppo in errore
                            "ERROR    1=yes \x08", 			//1--> si 0--> no
    /* MSA n. 15 */         "RINSE AFTER DOWN"          		//periodo di iniezione acqua
                            "TIME 0=NO \7\x08HOUR", 			//0-->  NO 6, 12, 24 ore	
};

#endif

#ifdef VARIGRIND_PRESENCE

const u8 __far  GB_MSAP_PAR_MACINA_MOT[MAX_PAR_MACINA_MOT][32] = {
    /* MSP n. 0  */        "p. grinder ^:\6\7\x08"
                           " 4=open  5=close",
    /* MSP n. 1  */        "sel.rif. grind.^"
                           "PROG=save     \7\x08",
    /* MSP n. 2  */        "Habil.reg.gran.^"
                           "1=yes 2=test   \x08",
    /* MSP n. 3  */        "Referring flux.^"
                           "cc/second  \5\6.\7\x08",
    /* MSP n. 4  */        "number samplings"
                           "grinder ^   \5\6\7\x08",
    /* MSP n. 5  */        "Referring posit."
                           "grinder ^    \6\7\x08",
    /* MSP n. 6  */        "Open/Close ^ \6\7\x08"
                           "4=O  5=C 1=Go On",

};

const u8 __far GB_MS_TIPO_GRANULOMETRIA[MAX_TIPO_GRANULOMETRIA][16] =			//ezio 11/05/2015
{
    /* MSP n. 0 */      "   disabled     ",
    /* MSP n. 1 */      "     fine       ",
    /* MSP n. 2 */      "    referring   ",
    /* MSP n. 3 */      "    roughly     ",

};
#endif 

#ifdef ABIL_CAPPUCCINATORE
#ifndef CAPPUCCINATORE_INDUX	

const u8 __far  GB_MSAP_CAPPUCCINATORE[MAX_CAPPUCCINATORE][32] = {

    /* MSP n. 0 */       "   TEMPERATURE  "
                         "steam        \6\7\x08",

    /* MSP n. 1 */       "Rinsing period  "//periodo risciacq
                         " min.        \6\7\x08",

    /* MSP n. 2 */       "Rinse MILK MOD  "//risciacquo
                         "   1=enable    \x08",

    /* MSP n. 3 */       "Rinse MILK MOD  "//rit. risciacquo.
                         "delay  sec:\6\7.\x08 ",

    /* MSP n. 4 */   	 "  Milk Sensor   "         //"rins. fresh milk"//tempo risciacquo
                         "1=Enable       \x08",

    /* MSP n. 5 */       " Clean User Msg "			// Richiesta Risciaquo Utente durante check iniziale
                         "1=Enable       \x08",

    /* MSP n. 6 */       "Next Milk Clean "			//Mostra l'ora del prossimo lavaggio
                         "\4\5:\6\7 \x08\x09-\x0A\x0B-20\x0C\x0D",

    /* MSP n. 7*/        " Mlk. Wash Type "			
                         " 0=24h  1=30h  \x08",      
};
#else   	
const u8 __far  GB_MSAP_CAPPUCCINATORE[MAX_CAPPUCCINATORE][32] = {

    /* MSP n. 0 */       "   TEMPERATURE  "
                         "steam        \6\7\x08",

    /* MSP n. 1 */       "HDE delay after "
                         "drink min.   \6\7\x08",

#ifdef CUSTOMER_NESTLE                        //#2964
    /* MSP n. 2 */       "not used        "
                         "                ",
#else
    /* MSP n. 2 */       "Cleaning period:"     	//#2964 - "not used        "   //"Hidrody.Emptying" 
                         "0=24H 1=48-72H \x08",    	//#2964
#endif

    /* MSP n. 3 */       "Fridge Position:"				//#2614 ex "Conducibility   "
                         "0=SIDE 5=BOTT. \x08",			//#5614 ex "Sensor 1=Enab. \x08",

    /* MSP n. 4 */   	 "  Check Milk    "
                         "presence 1=yes \x08",

#ifdef MODELLO_TS
    /* MSP n. 5 */       " Clean Msg Start"     //" Rinse User Msg "			// Richiesta Risciaquo Utente durante check iniziale
                         "1=Enable       \x08",
#else

    /* MSP n. 5 */       "   not used     "     //" Rinse User Msg "			// Richiesta Risciaquo Utente durante check iniziale
                         "                ",
#endif

    /* MSP n. 6 */       "Ignore tank sens"			//#3980 - 		//"Clean TimeUpdate"			//Aggiornamento automatico dell'ora per il lavaggio
                         "clean/hde      \x08",		//"1=Enable       \x08",

    /* MSP n. 7 */   	 "Check Waste tank"
                         "1=Enable       \x08",

    /* MSP n. 8 */       "Hot Classic Foam"
                         "air        \6\7\x08 %",

    /* MSP n. 9 */       "Hot Classic Foam"
                         "sped pump  \6\7\x08 %",

        #ifdef ABIL_SENSORE_PRESSIONE							 
    /* MSP n. 10 */      "Hot Classic Foam"
                         "pres. 0=dis.\6.\7\x08",
        #else
    /* MSP n. 10 */      "not used        "
                         "                ",
        #endif		

    /* MSP n.11 */       "Hot Fluffy Foam "
                         "air        \6\7\x08 %",

    /* MSP n.12 */       "Hot Fluffy Foam "
                         "sped pump  \6\7\x08 %",

        #ifdef ABIL_SENSORE_PRESSIONE							 
    /* MSP n.13 */       "Hot Fluffy Foam "
                         "pres. 0=dis.\6.\7\x08",
        #else
    /* MSP n.13 */       "not used        "
                         "                ",
        #endif		
    /* MSP n.14 */       "Hot Barista Foam"
                         "air        \6\7\x08 %",

    /* MSP n.15 */       "Hot Barista Foam"
                         "sped pump  \6\7\x08 %",

        #ifdef ABIL_SENSORE_PRESSIONE							 
    /* MSP n.16 */       "Hot Barista Foam"
                         "pres. 0=dis.\6.\7\x08",
        #else
    /* MSP n.16 */       "not used        "
                         "                ",
        #endif		

    /* MSP n.17 */       "Cold ClassicFoam"
                         "air        \6\7\x08 %",

    /* MSP n.18 */       "Cold ClassicFoam"
                         "sped pump  \6\7\x08 %",

        #ifdef ABIL_SENSORE_PRESSIONE							 
    /* MSP n.19 */       "Cold ClassicFoam"
                         "pres. 0=dis.\6.\7\x08",
        #else
    /* MSP n.19 */       "not used        "
                         "                ",
        #endif		

    /* MSP n.20 */       "Cold Fluffy Foam"
                         "air        \6\7\x08 %",

    /* MSP n.21 */       "Cold Fluffy Foam"
                         "sped pump  \6\7\x08 %",

        #ifdef ABIL_SENSORE_PRESSIONE							 
    /* MSP n.22 */       "Cold Fluffy Foam"
                         "pres. 0=dis.\6.\7\x08",
        #else
    /* MSP n.22 */       "not used        "
                         "                ",
        #endif		

    /* MSP n.23 */       "Cold BaristaFoam"
                         "air        \6\7\x08 %",

    /* MSP n.24 */       "Cold BaristaFoam"
                         "sped pump  \6\7\x08 %",

        #ifdef ABIL_SENSORE_PRESSIONE							 
    /* MSP n.25 */       "Cold BaristaFoam"
                         "pres. 0=dis.\6.\7\x08",
        #else
    /* MSP n.25 */       "not used        "
                         "                ",
        #endif	
    /* MSP n.26 */       "Deter.dissolving"
                         "Seconds:     \6\7\x08",

    /* MSP n.27 */   	 "Check Tank Milk "
                         "Temper. 1=yes  \x08",

    /* MSP n.28 */       "Hot No Foam     "
                         "sped pump  \6\7\x08 %",

    /* MSP n.29 */       "Cold No Foam    "
                         "sped pump  \6\7\x08 %",

    /* MSP n.30 */       "Tun.M.pump +/-30"				//#1885 "Tuning milk pump"
                         "Push PROG \4 \6\7\x08%",

	/* MSP n.31 */       "Auto rins. mode "
						 "0=Dflt 1=HDE   \x08",

};
#endif  	
#endif //ABIL_CAPPUCCINATORE	

const u8 __far GB_MS_TIPO_PALETTA[MAX_TIPO_PALETTA][16] =			//ezio 11/05/2015
{
    /* MSP n. 0 */      "stirrers sugar  ",
    /* MSP n. 1 */      "stirrers no sug.",
    /* MSP n. 2 */      "stirrers always ",
    /* MSP n. 3 */      "stirrers never  ",
};

const u8 __far GB_MS_MODULI_EST[MAX_MSG_SLAVE][32] =			
{						
    /* MSA n. 0 */      "        use the "
                        "dispensed cup   ",

    /* MSA n. 1 */      "Place your cup  "
                        "within \7\x08 sec.  ",

	/* MSA n. 2 */      "Deter./tank cup "				//#4660
                        "station 10=ok   ",				//#4660	

    /* MSA n. 3 */      "put syrup tube  "				//#4660
                        "bottl>tank 10=ok",				//#4660		

	/* MSA n. 4 */      "\0\1/\2\3  H2O fill."          //#4660   //"Water filling in"
                        "in tank with det",				//#4660	  // "tank with deter.",

    /* MSA n. 5 */      "Clean tank cup  "				//#4660
                        "station 10=ok   ",				//#4660											

	/* MSA n. 6 */      "\0\1/\2\3 SYRUP     "			//#4660	
                        "Cleanig End     ",				//#4660	

    /* MSA n. 7 */      "Hot H2O filling "			    //#4660
                        "in clean tank   ",				//#4660	
						
    /* MSA n. 8 */      "Water/Clen.Sol. "				//#4660
                        "through syr.tube",				//#4660			

    /* MSA n. 9 */      "  Inst module   "
                        " version  \0.\1.\2 ",

    /* MSA n. 10 */     "  Syrup module  "
                        " version  \0.\1.\2 ",

    /* MSA n. 11  */    "\4\5\6\7\x08 EXT Mix \0 "
                        "rinsing         ",
};

#endif

