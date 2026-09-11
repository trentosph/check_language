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

#ifdef LANGUAGE_ML2

#ifdef ABIL_PROGRAMMAZIONE_PARZIALE
const u8 __far ML_MS_PROG_ESTESA[16] = { "@U001           ", };
const u8 __far ML_MS_PROG_RIDOTTA[16] = { "@V001           ", };
#endif       

/*---------------------------------------------*/
const u8 __far ML_MSA_1[MAX_MSA][32] = {

    /* MSA n.  0 */        NOME_MACCHINA_1
                           DATA_VERSIONE_1

    #ifdef CUSTOMER_RHEA
        #ifdef BUSINESS_LINE
            #ifdef MODELLO_ESPRESSO
    /* MSA n.  1 */        "@A001           "							//"   laRhea BL    "
                           "                ",							//"                "
            #else
    /* MSA n.  1 */        "@A002           "							//"   laRhea BL    "
                           "                ",							//"   Speed Mix    "
            #endif
        #else
    /* MSA n.  1 */        "@A003           "							//"   laRhea V+    "
                           "                ",							//"                "
        #endif
    #else
    /* MSA n.  1 */        "@A004           "							//"           place"
                           "                ",							//"your cup        "
    #endif

    /* MSA n.  2 */        "@A005           "							//" switching on..."
                           "                ",							//"   please wait  "
    #ifdef MODELLO_DOPPIO
    /* MSA n.  3 */        "@A006           "							//"  preselection  "
                           "                ",							//" -   Sugar    + "
    #else
      #ifdef CUSTOMER_NESTLE
    /* MSA n.  3 */        "@A007           "							//"           place"
                           "                ",							//"your cup        "
      #else		   
    /* MSA n.  3 */        "@A184           "							//"Colocar El Vaso "
                           "                ",							//"   Por Favor    "
      #endif 					   

    #endif

    #ifdef CUSTOMER_NESTLE
    /* MSA n.  4 */        "@A008           " 							//"      remove cup" "  Boisson servie"
                           "                ",							//"Please          " "enlever tasse   ",
    #else					   
    /* MSA n.  4 */        "@A177           "							//"      remove cup" "  Boisson prête "
                           "                ",							//"Please          " "enlever tasse   ",
    #endif	 

    /* MSA n.  5 */        "@A009§\1\2        "							//"  preparing     "
                           "                ",							//"drink nr. \1\2    "

    /* MSA n.  6 */        "@A010§\0\1\2\3\4\5\6\7\x08\x09"				//"\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"
                           "\x0A\x0B\x0C\x0D\x0E\x0F          ",	//"  preparing     "

    #ifdef CUSTOMER_NESTLE
    /* MSA n.  7 */        "@A011           " 							//"          insert"  "         Inserte"
                           "                ",							//"exact change    "  "cambio exacto   ",
    #else					   
    /* MSA n.  7 */        "@A185           "							//"          insert"  "   Introducir   "
                           "                ",							//"exact change    "  "  precio exacto ",
    #endif	 

   #ifdef CUSTOMER_NESTLE
    /* MSA n.  8 */        "@A012           "							//"    check coffee"  "       Verifique"
                           "                ",							//"brewer          "  "molinillo café  ",
    #else					   
    /* MSA n.  8 */        "@A186           "							//"      remove cup" " Control Grupo  "
                           "                ",							//"Please          " "     Cafe'      ",
    #endif	 

    /* MSA n.  9 */        "@A013           "							//"Programming     "
                           "                ",							//"OK              "

    /* MSA n. 10 */        "@A014           "							//"Error during    "
                           "                ",							//"programming     "

    /* MSA n. 11 */        "@A015           "							//"1= KEY ---> VMC "
                           "                ",							//"2= VMC ---> KEY "

    /* MSA n. 12 */        "@A016           "							//"Programming     "
                           "                ",							//"EAROM data      " (EAROM -> EPROM)

    /* MSA n. 13 */        "@A017           "							//"Programming-----"
                           "                ",							//"RHEA FLASH------"

    /* MSA n. 14 */        "@A018§\0\1\2\3\4\5\6\7\x08\x09"					//"product reserve "
                           "\x0A\x0B\x0C\x0D\x0E\x0F          ", 	//"\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F"

    /* MSA n. 15 */        "@A019           "							//"  WATER FILTER  "
                           "                ",							//"CLEAN.  10=START"

    /* MSA n. 16 */        "@A020           "                           //"         machine"
                           "                ",                          //"ready           ",

    /* MSA n. 17 */        "@A021           "                           //"  Service       "
                           "                ",                          //"        Card    ",

    /* MSA n. 18 */        "@A022           "                           //" Not available  "
                           "                ",                          //"                ",

    #ifdef MODELLO_TS
    /* MSA n. 19 */        "@A023           "                           //"    reset coffee"
                           "                ",                          //"  grounds=RESET ",
    #else
    /* MSA n. 19 */        "@A024           "                           //"    reset coffee"
                           "                ",                          //"  grounds = P1  ",
    #endif
    /* MSA n. 20 */        "@A025           "                           //"                "
                           "                ",                          //"                ",

    /* MSA n. 21 */        "@A026§\1\2\3\4\5\6\7\x08  "                 //"Credit:         "
                           "                ",                          //"        \1\2\3\4\5\6\7\x08",

    /* MSA n. 22 */        "@A027           "                           //"  Out of service"
                           "                ",                          //"water filter    ",

    #ifdef CUSTOMER_NESTLE
    /* MSA n. 23 */        "@A028           "                           //"         service"
                           "                ",                          //"clean  brewer   ",		   
    #else
    /* MSA n. 23 */        "@A187           "                           //"         service"  " FUERA SERVICIO "
                           "                ",                          //"clean  brewer   ", " Limpieza Grupo ",	   
    #endif 

    /* MSA n. 24 */        "@A029§\4\5\6\7\x08     "                    //"price :    \4\5\6\7\x08"
                           "                ",                          //"                ",

    /* MSA n. 25 */        "@A030           "                           //" Out of service "
                           "                ",                          //" coffee grounds ",

    /* MSA n. 26 */        "@A031           "                           //" no  product    "
                           "                ",                          //"                ",

    /* MSA n. 27 */        "@A032           "                           //" refilling water"
                           "                ",                          //"wait            ",

    /* MSA n. 28 */        "@A033           "                           //"     wait       "
                           "                ",                          // "                ",

    /* MSA n. 29 */        "@A034           "                           //"            wait"
                           "                ",                          //"temperature     ",	

    /* MSA n. 30 */        "@A035§\x08\x09\x0A§\0     "                     //"Out of service  "
                           "                ",                         //"OFF \x08\x09\x0A \0       ",

    /* MSA n. 31 */        "@A036§\5\6§\7\x08     "                     //"machine off     "
                           "                ",                          //"           \5\6:\7\x08",

   #ifdef CUSTOMER_NESTLE
    /* MSA n. 32 */        "@A037§\5\6§\7\x08     "                     //"................"
                           "                ",                          //"start at:  \5\6:\7\x08",

    /* MSA n. 33 */        "@A038           "                           //"   TEST VEND    "
                           "                ",                          //"                ",

    /* MSA n. 34 */        "@A039           "                           //"   take a moment"
                           "                ",                          //"to relax        ",

    /* MSA n. 35 */        "@A040           "                           //"           Fresh"
                           "                ",                          //"Milk            ",

    /* MSA n. 36 */        "@A041           "                           //"messaggio 3     "
                           "                ",                          //"programmabile   ",

    /* MSA n. 37 */        "@A042           "                           //"  enjoy a break "
                           "                ",                          //"                ",

    /* MSA n. 38 */        "@A043           "                           //"          Always"
                           "                ",                          //"at your service ",	

    /* MSA n. 39 */        "@A044           "                           //"  insert coins  "
                           "                ",                          //"                ",

   #else
    /* MSA n. 32 */        "@A188§\5\6§\7\x08     "                     //"................"  "Encendiendo VMC "
                           "                ",                          //"start at:  \5\6:\7\x08",  "a:         \5\6:\7\x08",

    /* MSA n. 33 */        "@A189           "                           //"   TEST VEND    "  "  VENTA LIBRE   "
                           "                ",                          //"                ", "                ",

    /* MSA n. 34 */        "@A190           "                           //"   take a moment"  "  Permitase un  "
                           "                ",                          //"to relax        ", Momento de Relax",

    /* MSA n. 35 */        "@A191           "                           //"           Fresh"  "     LECHE      "
                           "                ",                          //"Milk            ", "     FRESCA     ",

    /* MSA n. 36 */        "@A192           "                           //"messaggio 3     "  "   mensaje  3   "
                           "                ",                          //"programmabile   ", "  programable   ",
    #ifdef CUSTOMER_KP
    /* MSA n. 37 */        "@A235           "                           //" Please hold    "  " the card       "
                           "                ",
    #else
    /* MSA n. 37 */        "@A193           "                           //"  enjoy a break "  "  Permitase un  "
                           "                ",                          //"                ", "Momento de Relax",
    #endif
    /* MSA n. 38 */        "@A194           "                           //"          Always"  "   Rheavendors  "
                           "                ",                          //"at your service ", " a Su Servicio  ",	

    /* MSA n. 39 */        "@A195           "                           //"  insert coins  "  "    Insertar    "
                           "                ",                          //"                ", "     Monedas    ",

    #endif
    #ifdef MODELLO_SOLUBILE

    /* MSA n. 40 */        "@A045§\6\7\x08       "                      //"t. inst.     \6\7\x08"
                           "                ",                          //"----------------",  

    #else 
    /*MSA n. 40*/         "@A046§\x0A\x0B\x0C§\6\7\x08§\x0E\x0F"           //"t.c \x0A\x0B\x0C  t.s \6\7\x08"         
                          "                ",                        //"t.h \x0E\x0F          ",                          

    #endif
    /* MSA n. 41 */        "@A047           "                           //"  Card Reader   "
                           "                ",                          //" Not Connected  ",

    /* MSA n. 42 */        "@A048           "                           //"   DATA AUDIT   "
                           "                ",                          //"  PLEASE  WAIT  ",

    /* MSA n. 43 */        "@A049           "                           //"     J U G      "
                           "                ",                          //"                ",

    #if defined (CUSTOMER_RHEA) || defined (MODELLO_BONA)
    /* MSA n. 44 */        "@A050           "                           //"  rheavendors   "
                           "                ",                          //"                ",
    #else
    /* MSA n. 44 */        "@A051           "                           //"           place"
                           "                ",                          //"your cup        ",
    #endif

    /* MSA n. 45 */        "@A052§\x09\x0A\x0B       "                  //"  no  selections"
                           "                ",                          //"F.Milk   OFF \x09\x0A\x0B",

    /* MSA n. 46 */        "@A053           "                           //"HAPPY           "
                           "                ",                          //"           HOUR ",       

    /* MSA n. 47 */        "@A054§\0\1\2\3\4\5\6\7\x08\x09"                //"   FREE VEND    "
                           "\x0A\x0B\x0C\x0D\x0E\x0F          ",     //"\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F",
    #ifdef MODELLO_ESPRESSO
    /* MSA n. 48 */        "@A055§\x09\x0A\x0B       "                  //"no coffee beans "
                           "                ",                          //"         OFF \x09\x0A\x0B",
    #else // MODELLO_SOLUBILE
    /* MSA n. 48 */        "@A056           "                           //"mes 48          "
                           "                ",                          //"                ",
    #endif

    #ifdef CUSTOMER_NESTLE
    /* MSA n. 49 */        "@A057           "                           //" Out of service "
                           "                ",                          //"    no water    ",
    #else
    /* MSA n. 49 */        "@A178           " 							//"  HORS SERVICE  "
                           "                ",							//" Manque d'eau   ",
    #endif

    /* MSA n. 50 */        "@A058           "                           //" fill water and "
                           "                ",                          //"press button -1-",

#ifdef CAPPUCCINATORE_INDUX
    /* MSA n. 51 */        "@A059           "      	 					//" Hydrodynamic  "
                           "                ",       					//" Emptying phase ",    
#else					   
    /* MSA n. 51 */        "@A060           "                           //"       automatic"
                           "                ",                          //"steam cleaning  ",
#endif  

    /* MSA n. 52 */        "@A061           "                           //"SERVICE         "
                           "                ",                          //"                ",

    /* MSA n. 53 */        "@A062§\x09\x0A        "                     //"error  on KEY   "
                           "                ",                          //"code  \x09\x0A        ",


#if defined(ABIL_MILKER_DESCALING)  //#4419
 #if defined(MODELLO_ESPRESSO) 
  #ifdef ABIL_DESCALING
    #ifdef ENABLE_GRINDER_CLEANING
    /* MSA n. 54 */     "@A229           "		//"1-4=Mx M:5=C 6=D" 			//5=Cleaning Milk Module 6=descaling Milk Circuit
                        "                ",		//"7=Gr 8=BC 9=Desc",
    #else 
    /* MSA n. 54 */     "@A230           "		//"1-4=Mix 5=MilkMd" 
                        "                ",		//"6=DeM 8=BC 9=Des",
    #endif
  #else  //#ifdef ABIL_DESCALING
    #ifdef ENABLE_GRINDER_CLEANING
    /* MSA n. 54 */     "@A231           "		//"1-4=Rinse 5=Milk" 
                        "                ",		//"6=D.M 7=Gr. 8=BC",
    #else
    /* MSA n. 54 */     "@A232           "		//"1-4=Rinse 5=Milk" 
                        "                ",		//"6=Desc.Milk 8=BC",
    #endif
  #endif  //#ifdef ABIL_DESCALING
 #endif	  //#if defined(MODELLO_ESPRESSO) 
#endif    //#if defined(ABIL_MILKER_DESCALING)  //#4419

#if !defined(ABIL_MILKER_DESCALING)
#ifdef MODELLO_ESPRESSO
#if defined(ABIL_CAPPUCCINATORE) && defined(ABIL_DESCALING)
#ifdef ENABLE_GRINDER_CLEANING
    /* MSA n. 54 */        "@A063           "  // "1-4=Mix 5=MilkMd"
                           "                ", // "7=Gr 8=BC 9=Desc"
#else                  
    /* MSA n. 54 */        "@A225           "  // "1-4=Mix 5=MilkMd"
                           "                ", // "  8=BC 9=Desc   "
#endif

#elif defined(ABIL_DESCALING) && !defined(ABIL_CAPPUCCINATORE)
#ifdef ENABLE_GRINDER_CLEANING
    /* MSA n. 54 */        "@A064           "  // "   1-4=Rinse    " 
                           "                ", // "7=Gr 8=BC 9=Desc"
#else                  
    /* MSA n. 54 */        "@A226           "  // "   1-4=Rinse    "
                           "                ", // "   8=BC 9=Desc  "
#endif

#elif !defined(ABIL_DESCALING) && defined(ABIL_CAPPUCCINATORE)
#ifdef ENABLE_GRINDER_CLEANING
    /* MSA n. 54 */        "@A065           "  // "1-4=Rinse 5=Milk"
                           "                ", // " 7=grinder 8=BC "
#else                  
    /* MSA n. 54 */        "@A227           "  // "1-4=Rinse 5=Milk"
                           "                ", // "      8=BC      "
#endif

#else

#ifdef ENABLE_GRINDER_CLEANING
    /* MSA n. 54 */        "@A228           "  // "    1-4=Rinse   "
                           "                ", // " 7=grinder 8=BC "
#else                  
    /* MSA n. 54 */        "@A066           "  // "    1-4=Rinse   "
                           "                ", // "      8=BC      "
#endif

#endif 
#else  
    /* MSA n. 54 */        "@A067           "    //"    1-4=Rinse   "
                           "                ",   //"                ",
#endif 
#endif 		//#if !defined(ABIL_MILKER_DESCALING)

    /* MSA n. 55 */        "@A068§\0\1§\6\7\x08    "                    //"cleaning  \0\1    "
                           "                ",                          //"             \6\7\x08",

    /* MSA n. 56 */        "@A069           "                           //"RFID reader card"
                           "                ",                          //"connected       ",
    #ifdef SUMMERTIME
    /* MSA n. 57 */        "@A070§\0\1\2\x0E\x0F§\4\5§\6"                    //Hello      \0\1\2\x0E\x0F"
                           "\7§\x08\x09§\3§\x0A\x0B§\x0C\x0D    ",       //"\4\5-\6\7-\x08\x09 \3 \x0A\x0B:\x0C\x0D",
    #else
    /* MSA n. 57 */        "@A071           "                           //" Enter the exact"
                           "                ",                          //" amount         ",
    #endif
    /* MSA n. 58 */        "@A072           "                           //"          change"
                           "                ",                          //"water filter    ",

    #ifdef CUSTOMER_NESTLE
    /* MSA n. 59 */        "@A073           "                           //"           clean"
                           "                ",                          //"brewer          ",

    /* MSA n. 60 */        "@A074           "                           //"           empty"
                           "                ",                          //"coffee grounds  ",
    #else				   
    /* MSA n. 59 */        "@A196           "                           //"           clean"  "Hacer el Lavado "
                           "                ",                          //"brewer          ", "    de Grupo    ",

    /* MSA n. 60 */        "@A197           "                           //"           empty"  "Vaciar Residuos "
                           "                ",                          //"coffee grounds  ", "Cajon de  Cafe' ",
    #endif					   

    /* MSA n. 61 */        "@A075           "                           //"  SET  PRODUKT  "
                           "                ",                          //"  ---- OK ----  ",

    /* MSA n. 62 */        "@A076           "                           //" INSTALLATION   "
                           "                ",                          //"                ",

    /* MSA n. 63 */        "@A077           "                           //"      end       "
                           "                ",                          //"  installation  ",

    /* MSA n. 64 */        "@A078           "                           //"  credit = 0    "
                           "                ",                          //"                ",

    /* MSA n. 65 */        "@A079           "                           //"    place the   "
                           "                ",                          //"      card      ",

    /* MSA n. 66 */        "@A080           "                           //"SELECTION CARD  "
                           "                ",                          //"                ",

    /* MSA n. 67 */        "@A081           "                           //"product reserve "
                           "                ",                          //" REFILL COFFEE  ",

    /* MSA n. 68 */        "@A082§\0\1\2\3\4\5\6\7\x08\x09"                //"Not available   "
                           "\x0A\x0B\x0C\x0D\x0E\x0F          ",     //"\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F",

    /* MSA n. 69 */        "@A083           "                           //"-  S U G A R   +"
                           "                ",                          //"                ",

    /* MSA n. 70 */        "@A084           "                           //"    make a      "
                           "                ",                          //"  selection     ",

    /* MSA n. 71 */        "@A085§\0\1        "                         //"door  module    "
                           "                ",                          //"        vers. \0\1",

    /* MSA n. 72 */        "@A086§\0\1        "                         //"espresso module "
                           "                ",                          //"        vers. \0\1",

    /* MSA n. 73 */        "@A087§\0\1        "                         //"  Milk module   "
                           "                ",                          //" version    \0\1  ",

    /* MSA n. 74 */        "@A088§\0         "                         //" Periodic rinse "
                           "                ",                          //"  in \0 seconds  ",

    /* MSA n. 75 */        "@A089§\x09\x0A§\x0B      "                  //"                "
                           "                ",                          //"       OFF \x09\x0A  \x0B",

    /* MSA n. 76 */        "@A090           "                           //"      Remove Cup" 
                           "                ",                          //"Please          ",   

    /* MSA n. 77 */        "@A091           "                           //"  wait charging "
                           "                ",                          //" steam boiler   ",

    /* MSA n. 78 */        "@A092           "                           //"invalid customer"
                           "                ",                          //"   card code    ",

    /* MSA n. 79 */        "@A093           "                           //"invalid machine "
                           "                ",                          //"   card code    ",

    /* MSA n. 80 */        "@A094           "                           //"    lucky       "		
                           "                ",                          //"  selection     ",

    /* MSA n. 81 */        "@A095           "                           //"TOKEN           "		
                           "                ",                          //"                ",		

    /* MSA n. 82 */        "@A096           "                           //"  wait please   " 
                           "                ",                          //"steam temperat. ",

    /* MSA n. 83 */        "@A097§\x0B\x0C\x0D\x0E\x0F§\1\2\3\4"        //"Price :    \x0B\x0C\x0D\x0E\x0F"
                           "\5\6\7\x08            ",                    //"Credit: \1\2\3\4\5\6\7\x08",

    /* MSA n. 84 */        "@A098           "                           //libero disponibile "                "		
                           "                ",                          //                      "                ",

    /* MSA n. 85 */        "@A099           "                           //"emptying        "
                           "                ",                          //"coffee grounds  ",

    #ifdef CUSTOMER_NESTLE
    /* MSA n. 86 */        "@A100           "                           //"     remove     "
                           "                ",                          //"    driptray    ",

    /* MSA n. 87 */        "@A101           "                           //"     insert     "
                           "                ",                          //"    driptray    ",
    #else
    /* MSA n. 86 */        "@A180           "							//"  Enlever le bac"
                           "                ",							//"des eaux usées  ",

    /* MSA n. 87 */        "@A181           "							//"  Mettre le bac "
                           "                ",							//"des eaux usées  ",
    #endif	

    /* MSA n. 88 */        "@A102           "                           //"steam flushing  "
                           "                ",                          //"        10=START",

    /* MSA n. 89 */        "@A103           "                           //"fill detergent  "//lavaggio vapore con detergente
                           "                ",                          //"        10=START",

#ifdef CAPPUCCINATORE_INDUX
    /* MSA n. 90 */       "@A104§\4\5\6\7\x08     "                     //"filling water..."
                          "                ",                          //"conduc.=\4\5\6\7\x08 uS",
#else
    /* MSA n. 90 */       "@A105           "                           //"fill water      "//lavaggio vapore con detergente
                          "                ",                          //"        10=START",
#endif	

    /* MSA n. 91 */        "@A106           "                           //"warm water      "//lavaggio vapore con detergente
                           "                ",                          //"flush.  10=START",

    /* MSA n. 92 */        "@A107           "                           //"   Milk Module  "
                           "                ",                          //" switching on...",

    /* MSA n. 93 */        "@A108           "                           //"  Milk container"
                           "                ",                          //"empty           ",

    /* MSA n. 94 */        "@A109           "                           //"    S T O P     "
                           "                ",                          //"                ",

    /* MSA n. 95 */        "@A110           "                           //"   RFID Card    "
                           "                ",                          //"    Blocked     ",

    #ifndef TEST_CICLICO
    #ifdef CAPPUCCINATORE_INDUX
    /* MSA n. 96 */        "@A111           "                           //"  Milk  Module  "  "  Cappu-Indux   "
                           "                ",                          //"  Please clean  ", " fare lavaggio  ",
    #else
    /* MSA n. 96 */        "@A183           "                           //"  Milk  Module  "  "  Cappuccino-R  "
                           "                ",                          //"  Please clean  ", " fare lavaggio  ",
    #endif

    /* MSA n. 97 */        "@A112           "                           //"      clean with"//lavaggio vapore con detergente 
                           "                ",                          //"deterg. 10=START",
    #else
    /* MSA n. 96 */       "@A113§\4\5\6\7\x08     "                     //"  Cyclic Test   "
                          "                ",                           //"  round #\4\5\6\7\x08  ",

    /* MSA n. 97 */       "@A114           "                            //"  Cyclic Test   "//lavaggio vapore con detergente     
                          "                ",                           //"  Stopped!!!    ",
    #endif 

    /* MSA n. 98 */        "@A115           "                           //"rinse with cold "//lavaggio vapore con detergente   
                           "                ",                          //"water   10=START",          

#ifdef CAPPUCCINATORE_INDUX
    /* MSA n. 99 */        "@A116           "                           //"  END Cleaning  "	//lavaggio vapore con detergente     
                           "                ",                          //" with Detergent ",
#else
    /* MSA n. 99 */        "@A117           "                           //"      END       "//lavaggio vapore con detergente     
                           "                ",                          //"steam flushing  ",  
#endif		

    /* MSA n. 100 */       "@A118           "                           //"    wait milk   " //attendere lavaggio cappuccinatore
                           "                ",                          //"  unit cleaning ",

    /* MSA n. 101 */       "@A119           "                           //"       Place Cup" //attendere lavaggio cappuccinatore
                           "                ",                          //"please          ",

    /* MSA n. 102 */       "@A120           "                           //" setting grinder" //attendere Regolazione della macina. Granulometria della selezione
                           "                ",                          //"  Please wait   ",	

    /* MSA n. 103 */      "@A121§\0\1\2\3\4\5\6\7\x08\x09" // non usato su progetto BL HOT WATER 
                          "\x0A\x0B\x0C\x0D\x0E\x0F          ",

    /* MSA n. 104 */       "@A122           "                           //"Warning products"
                           "                ",                          //"   level   low  ",

    /* MSA n. 105 */       "@A123           "                           // libero disponibile (era: "first install.  " era in prog 214
                           "                ",                          //                          "starts automat. ",

    /* MSA n. 106 */       "@A124           "                          //"Catch Coffee    " //era in prog 209
                           "                ",                         //"Push PROG Button",

    /* MSA n. 107 */       "@A125           "                          //"                " //era in prog 215
                           "                ",                         //"autom. reset    ",

    /* MSA n. 108 */       "@A126           "                          //"      End       " //era in prog 219
                           "                ",                         //"   uninstall    ",	

    /* MSA n. 109 */	   "@A127§\6\7\x08       "					   //"Final Result:\6\7\x08"	//Risulta finale test vuoto macina
                           "                ",						   //"KEY PRESS <PROG>",

    /* MSA n. 110 */		"@A128           "						// " Rinsing   Time " //ricetta errata
                            "                ",						//" Milker Updated ",

    /* MSA n. 111 */       "@A129           "						//"TEST RUNNING    " //era MSP n.  68 */
                            "                ",						//"                ",

    /* MSA n. 112 */        "@A130           "						//"confirm partial " // era in /* MSP n. 97 */ 
                            "                ",						//"reset  press P10",

    /* MSA n. 113 */        "@A131           "                      //" Starting Test  "
                            "                ",                     //"4=start PROG=end",

    /* MSA n. 114 */        "@A132§\x0A\x0B§\x0C\x0D\x0E\x0F§\5\6"  //"TEST MOTOR - \x0A\x0B "
                            "\7\x08              ",                 //"sx \x0C\x0D\x0E\x0F  dx \5\6\7\x08",

    /* MSA n. 115 */        "@A133§\x0A\x0B§\3§\x0C\x0D\x0E\x0F§"   //"TEST - \x0A\x0B  Tp: \3"
                            "\5\6\7\x08            ",                           // "up \x0C\x0D\x0E\x0F  dn \5\6\7\x08",

    /* MSA n. 116 */        "@A134§\x0A\x0B        "                //"  Final Result  "
                            "                ",                     //"    TEST -    ",

#ifdef RESET_SANITARY_WASH
    /* MSA n. 117*/         "@A135           "                      //" System halted  "
                            "                ",                     //" Please restart!",
#else
    /* MSA n. 117 */    	"@A136           "						//"Empty the tank  "						//20201007 (104)
                            "                ",						//"waste milk/water",						//20201007
#endif 

    /* MSA n. 118 */   		"@A137           "						//"Insert the tank "						//20201007 (103)
                            "                ",						//"waste milk/water",						//20201007					  

    /* MSA n. 119 */        "@A138§\0\1§\6\7\x08§\x09\x0A\x0B"		//"rinsing \0\1  \6\7\x08" 						//20201007 (105)
                            "\x0C\x0D              ",       		//"........uS=\x09\x0A\x0B\x0C\x0D",			//20201007								  

#ifdef MODELLO_TS
    /* MSA n. 120 */      	"@A139           "						//"Have you done   "						//20201106 
                            "                ",						//"checks?>START/10",						//20201106	
#else
    /* MSA n. 120 */      	"@A140           "						//"Clean.Deter.type"						//20201106 
                            "                ",						//"10=Tab 12=Liquid",						//20201106
#endif                      	

    /* MSA n. 121 */ 	    "@A141           "						//"check milk      "						//20201007 (103)
                            "                ",						//"                ",						//20201007					  

    /* MSA n. 122 */      	"@A142           "						//"Check Detergent "						//"warning.. troppo"	//20201007 (103)
                            "                ",						//"of the water mix",						//20201007		

    /* MSA n. 123 */      	"@A143§\x09\x0A\x0B       "				//"Check the milk  "						//20201007 (103)
                            "                ",						//"quality         ",						//20201007					  

    /* MSA n. 124 */      	"@A144§\0\1§\6\7\x08§\x09\x0A\x0B"		//"Cleaning \0\1  \6\7\x08" 				//20201007 
                            "\x0C\x0D              ",				//"........uS=\x09\x0A\x0B\x0C\x0D",       	//20201007		

    /* MSA n. 125 */      	"@A145§\0\1§\6\7\x08    "				//"   Dissolving   "
                            "                ",						//"Detergent \0\1 \6\7\x08",

#ifdef MODELLO_TS
    /* MSA n. 126 */        "@A146           "						//"Insert the milk "
                            "                ",						//"tube.10:now 9:no",
    #else
    /* MSA n. 126 */      	"@A147           "						//"Ins. Tube/refil"
                            "                ",						//"Milk 10:now 9:no",
    #endif 
    /* MSA n. 127 */      	"@A148           "						//"  check milk    "
                            "                ",						//"   presence     ",

    /* MSA n. 128 */      	"@A149           "						//"   check milk   "
                            "                ",						//"    quality     ",

    /* MSA n. 129 */      	"@A150           "						//"check milk and  "
                            "                ",						//"make cleaning   ",

    /* MSA n. 130 */        "@A151           "						//"Gest. rhMM1.v+ ?"
                            "                ",						//"B1=Enable B2=no ",

    /* MSA n. 131 */      	"@A152§\5\6§\7\x08     "				//"Clean. rhMM1.v+ "
                            "                ",						//"Time \5\6:\7\x08 Ok=P1",

    /* MSA n. 132 */      	"@A153§\x09\x0A\x0B       "				//"Milk Mod.Clean.:"        //"rhMM1.v+ Clean.:"
                            "                ",						//"low deterg. \x09\x0A\x0B ",

    /* MSA n. 133 */      	"@A154           "						//"check tank cold "
                            "                ",						//"milk temperature",

    /* MSA n. 134 */      	"@A155           "						//"Available       "
                            "                ",						//"                ",

    /* MSA n. 135 */       	"@A156           "						//"  Close  Coffee "   // era 117
                            "                ",						//"KEY PRESS <PROG>",

    /* MSA n. 136 */       	"@A157           "						//"  Open   Coffee "   // era 118
                            "                ",						//"KEY PRESS <PROG>",

    /* MSA n. 137 */       	"@A158           "						//"1/13 Clean Grin."
                            "                ",						//"1=Grin1; 2=Grin2",

    /* MSA n. 138 */       	"@A159§^         "						//"2/13 G^ Close   "
                            "                ",						//"shutter.  10=ok ",

    /* MSA n. 139 */       	"@A160           "						//"3/13 Rem. brewer"
                            "                ",						//"& bean hop 10=ok",

    /* MSA n. 140 */       	"@A161           "						//"4/13 Inst. clean"
                            "                ",						//"device.    10=ok",

    /* MSA n. 141 */       	"@A162           "						//"5/13 Grinder    "
                            "                ",						//"clean   10=start",

    /* MSA n. 142 */       	"@A163§^§)       "						//"Cycle ^ of )    "
                            "                ",						//"                ",

    /* MSA n. 143 */       	"@A164           "						//"6/13 Rep. Clean "
                            "                ",						//"10=Yes; other=NO",

    /* MSA n. 144 */       	"@A165           "						//"7/13 Ref. Clean "
                            "                ",						//"device.    10=ok",

    /* MSA n. 145 */       	"@A166           "						//"8/13 Put back   "
                            "                ",						//"bean hop.  10=ok",

    /* MSA n. 146 */       	"@A167           "						//"9/13 Open hopp. "
                            "                ",						//"shutter.  10=ok ",

    /* MSA n. 147 */       	"@A168           "						//"10/13 Coffee    "
                            "                ",						//"grind.  10=Start",

    /* MSA n. 148 */       	"@A169§^§)§\7\x08    "					//"Cycle ^ of )    "
                            "                ",						//"timeout \7\x08 sec  ",

    /* MSA n. 149 */       	"@A170           "						//"11/13 Rep. Proc."
                            "                ",						//"10=Yes; other=NO",

    /* MSA n. 150 */       	"@A171           "						//"12/13 Put back  "
                            "                ",						//"Brewer.  10 = ok",

    /* MSA n. 151 */       	"@A172           "						//"13/13 Coffee?   "
                            "                ",						//"10=Yes; other=NO",

    /* MSA n. 152 */       	"@A173           "						//"ESPRESSO        "
                            "                ",						//"preparing       ",

    /* MSA n. 153 */        "@A174           "						//"Forthcoming     "
                            "                ",						//"sched maintenan.",

    /* MSA n. 154 */        "@A175           "						//"Maintenance must"
                            "                ",						//"be performed    ",

    /* MSA n. 155 */        "@A176§\5\6\7\x08      "				//"  Enter Weight  "
                            "                ",						//"  1 = Save  \5\6\7\x08",

    /* MSA n. 156 */        "@A198           "						//"END PROGRAMMING "
                            "                ",						//"wait..........  ",

    /* MSA n. 157 */        "@A199           "						//"access code     "
                            "                ",						//"INHIBITED       ",

    /* MSA n. 158 */        "@A200           "						//"uninstallation  "
                            "                ",						//"in progress...  ",

    /* MSA n. 159 */        "@A201           "						//"                "
                            "                ",						//"                ",

    /* MSA n. 160 */        "@A202           "						//"CALIBRATION IS  "
                            "                ",						//"NOT POSSIBLE    ",

    /* MSA n. 161 */        "@A203           "						//"Remove Brewer   "
                            "                ",						//"Push PROG button",

    /* MSA n. 162 */        "@A204           "						//"Replace Brewer  "
                            "                ",						//"Push PROG Button",

    /* MSA n. 163 */        "@A205           "						//"Open boiler tap "
                            "                ",						//"       10=start ",

    /* MSA n. 164 */        "@A206           "						//"   KEY PRESS    "
                            "                ",						//"     >PROG<     ",

    /* MSA n. 165 */        "@A207           "						//" end uninstall  "
                            "                ",						//"close boiler tap",

    /* MSA n. 166 */        "@A208           "						//"Water supply    "
                            "                ",						//"conn.? Start=10 ",

#ifdef CUSTOMER_NESTLE
    /* MSA n. 167 */        "@A209           "						//"driptray        "   "Bac de liquides "
                            "                ",						//"inside? 10=START",  "insere? 10=Avant",  
#else
    /* MSA n. 167 */        "@A210           "						//"driptray        "   "Bac  eaux usées "
                            "                ",						 //"inside? 10=START",  "insere? 10=Avant",     
#endif

    /* MSA n. 168 */        "@A211           "						//"remove coffee   "
                            "                ",						//"grounds 10=START",

    /* MSA n. 169 */        "@A212           "						//"Drip tray       "
                            "                ",						//"empty? Start=10 ",

#ifdef CUSTOMER_NESTLE 
    /* MSA n. 170 */        "@A213           "						//"REGISTRATION out"
                            "                ",						//"of service      ",
#else
    /* MSA n. 170 */        "@A214           "						//"REGISTRATION out"   "Historique des  "
                            "                ",						//"of service      ",  "hors service    ",
#endif

    /* MSA n. 171 */        "@A215           "						//"PROGRAMMING-----"
                            "                ",						//"----------------",

    /* MSA n. 172 */        "@A216           "						//"Preselection    "
                            "                ",						//"not used        ",

    /* MSA n. 173 */        "@A217§\x0A\x0B§\6\7§\x08   "			//"PRODUCT  \x0A\x0B     "
                            "                ",						//"0=inhib.    \6\7.\x08",

    /* MSA n. 174 */        "@A219§\6\7§\x08      "					//"coffee time     "
                            "                ",						//"grinder     \6\7.\x08",

    /* MSA n. 175 */        "@A220§\5\6\7\x08      "				//"Ent. Weight \5\6\7\x08"
                            "                ",						//"1=Save  2=Repeat",

    /* MSA n. 176 */        "@A221§\6\7\x08       "					//"Ent. ML of water"				//#1885
                            "                ",						//"1=Save 2=rep \6\7\x08",			//#1885

    /* MSA n. 177 */        "@A222           "						//"Empties test jug"				//#1885
                            "                ",						//"Test:  1=ok 2=no",				//#1885		

    /* MSA n. 178 */       	"@A223           "						//"Fill H2O FM tank"				//#1885
                            "                ",						//"t.tube 1=ok 2=no",				//#1885		

    /* MSA n. 179 */        "@A224           "	                    //  "Confirm Action  "			//#2311
                            "                ",				        // "10=YES      9=NO"          #2311	

    /* MSA n. 180 */        "@A233           "	                    // "ENERGY SAVING  " #4300
                            "                ",			        	

    /* MSA n. 181 */        "@A234           "	                    // "Kredit: Karte" #4814
                            "                ",
        
    /* MSA n. 182 */        "@A236           "                      // "NEED GRINDER CALIBRATION"
                            "                ",
			        
    /* MSA n. 183 */        "@A237          "	                    // "Refill   cups   "
                            "                ",				        
    /* MSA n. 184 */        "@A238          "                       // "Use own cups    "
                            "                ",				        
};

/*------------- MESSAGGI PROGRAMMAZIONE -------*/

const u8 __far ML_MSAP_1[MAX_MSAP][32] = {

    /* MSP n.  0 */        "@B001           "                           //"                "
                           "                ",                          //"                ",

    /* MSP n. 1 */         "@B002§\6\7\x08       "                      //"insert code     "
                           "                ",                          //"             \6\7\x08",

    /* MSP n.  2 */        "@B003§\5\6§\7\x08     "                     //"START F1:       "
                           "                ",                          //"HAPPY HOUR \5\6:\7\x08",

    /* MSP n.  3 */        "@B004§\5\6§\7\x08     "                     //"END F1:         "
                           "                ",                          //"HAPPY HOUR \5\6:\7\x08",

    /* MSP n.  4 */        "@B005§\5\6§\7\x08     "                     //"START F2:       "
                           "                ",                          //"HAPPY HOUR \5\6:\7\x08",

    /* MSP n.  5 */        "@B006§\5\6§\7\x08     "                     //"END F2:         "
                           "                ",                          //"HAPPY HOUR \5\6:\7\x08",

    /* MSP n.  6 */        "@B007§\5\6§\7\x08     "                     //"START F3:       "
                           "                ",                          //"HAPPY HOUR \5\6:\7\x08",

    /* MSP n.  7 */        "@B008§\5\6§\7\x08     "                     //"END F3:         "
                           "                ",                          //"HAPPY HOUR \5\6:\7\x08",

    /* MSP n.  8 */        "@B009§\x0A§\x08       "                     //"coin        \x0A  \x08"
                           "                ",                          //"card      0=acc.",

    /* MSP n.  9 */        "@B010§\x0A§\x08       "                     //"coin        \x0A  \x08"
                           "                ",                          //"no card   0=acc.",

    /* MSP n. 10 */        "@B011§\1\2\3\4\5\6\7\x08  "                 //"max. credit card"
                           "                ",                          //"        \1\2\3\4\5\6\7\x08",
    #ifdef ABIL_MANUTENZIONE
    /* MSP n. 11 */        "@B012           "                           //"1=PROGRAMMING   "
                           "                ",                          //"2=DATA 3=TESTV. ",

    /* MSP n. 12 */        "@B013           "                           //"4=RINSE - CLEAN "
                           "                ",                          //"5=MAINT. 6=MODEM",
    #else
    /* MSP n. 11 */        "@B014           "                           //"1=PROGR  2=DATA "
                           "                ",                          //"3=TEST   4=CLEAN",
    /* MSP n. 12 */        "@B015           "                           //"1=PROGR  2=DATA "
                           "                ",                          //"3=TEST   4=CLEAN",
    #endif
    /* MSP n. 13 */        "@B016§\7\x08        "                       //"discount        "
                           "                ",                          //"card     -  \7\x08 %",

    /* MSP n. 14 */        "@B017§\x0A§\6\7\x08     "                           //"COLD            "
                           "                ",                          //"                ",

    /* MSP n. 15 */        "@B018           "                           //"FUNCTIONING     "
                           "                ",                          //"                ",

    /* MSP n. 16 */        "@B019           "                           //"not used        "
                           "                ",                          //"                ",
    #ifdef DISABILITA_CONVERSIONE_GRAMMI
    /* MSP n. 17 */        "@B020§\x0A\x0B§\6\7§\x08   "                //"PRODUCT  \x0A\x0B     "
                           "                ",                          //"0=inhib.    \6\7.\x08",
    #else
    /* MSP n. 17 */        "@B021§\x0A\x0B§\6\7§\x08   "                //"DOSAGE grams    "
                           "                ",                          //"PRODUCT \x0A\x0B  \6\7.\x08",
    #endif

    /* MSP n. 18 */        "@B022§\x0A\x0B§\6\7§\x08   "                //"start delay     "
                           "                ",                          //"PRODUCT  \x0A\x0B \6\7.\x08",

    #ifdef CUSTOMER_NESTLE
    /* MSP n. 19 */        "@B023§\7\x08        "                       //"breaks number   "       
                           "                ",                          //"0 - 15        \7\x08",
    #else
    /* MSP n. 19 */        "@B348§\7\x08        "                       //"breaks number   "       
                           "                ",                          //"0 - 15        \7\x08",
    #endif

    /* MSP n. 20 */        "@B024§\x0A\x0B§\6\7§\x08   "                //"WATER \x0A\x0B time   "
                           "                ",                          //"0=inhib.    \6\7.\x08",

    /* MSP n. 21 */        "@B025§\x0A\x0B§\6\7§\x08   "                //"start delay     "
                           "                ",                          //"WATER \x0A\x0B    \6\7.\x08",

    /* MSP n. 22 */        "@B026§\x0A\x0B§\6\7§\x08   "                //"MIXER \x0A\x0B        "
                           "                ",                          //"0=inhib.    \6\7.\x08",

    /* MSP n. 23 */        "@B027§\x0A\x0B§\6\7§\x08   "                //"start delay     "
                           "                ",                          //"MIXER \x0A\x0B    \6\7.\x08",

    /* MSP n. 24 */        "@B028§\x0A\x0B§\0\1\2\3\4\5\6"                           //"water flow  : \x0A\x0B"
                           "\7               ",                        //"        \0\1\2\3\4\5\6\7",

    /* MSP n. 25 */        "@B029§)§^§\0\1\2\3\4\5"                  //"selection name)^"
                           "\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F      ", //"\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F",

    /* MSP n. 26 */        "@B030§\6\7§\x08      "                      //"delay station   "								//ezio 11/05/2015
                           "                ",                          //"            \6\7.\x08",

    /* MSP n. 27 */        "@B031§\0\1\2\3\4\5\6\7\x08\x09"                //"Programming:    "
                           "\x0A\x0B\x0C\x0D\x0E\x0F          ",      //"\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F",  /* estesa-ridotta */

    /* MSP n. 28 */        "@B032§\x0A\x0B§\0\1\2\3\4\5\6"               //"MIXER speed   \x0A\x0B"
                           "\7               ",                        //"        \0\1\2\3\4\5\6\7",

    /* MSP n. 29 */        "@B033§\0\1\2\3\4     "                      //"day of week     "
                           "                ",                          //"\0\1\2\3\4.          ",

   #ifdef CUSTOMER_NESTLE
    /* MSP n. 30 */        "@B339§\0\1\2\3\4§\5\6§\7"					//"Heure Allumage  "
                           "\x08               ",						//"\0\1\2\3\4.     \5\6:\7\x08",
    #else
    /* MSP n. 30 */        "@B034§\0\1\2\3\4§\5\6§\7"                    //"SWITCHING ON:   "
                           "\x08               ",                      //"\0\1\2\3\4.     \5\6:\7\x08",
    #endif

    /* MSP n. 31 */        "@B035§\0\1\2\3\4§\5\6§\7"                    //"SWITCHING OFF:  "
                           "\x08               ",                      //"\0\1\2\3\4.     \5\6:\7\x08",

    /* MSP n. 32 */        "@B036§\5\6§\7\x08     "                     //"RINSING:        "
                           "                ",                          //"           \5\6:\7\x08",

    /* MSP n. 33 */        "@B037§\5\6§\7\x08     "                     //"HOUR:           "
                           "                ",                          //"           \5\6:\7\x08",

    /* MSP n. 34 */        "@B038§\7\x08        "                       //"DAY:            "
                           "                ",                          //"              \7\x08",

    /* MSP n. 35 */        "@B039§\7\x08        "                       //"MONTH:          "
                           "                ",                          //"              \7\x08",

    /* MSP n. 36 */        "@B040§\7\x08        "                       //"YEAR :          "
                           "                ",                          //"              \7\x08",

    /* MSP n. 37 */        "@B041§\6\7\x08       "                      //"COFFEE WATER    "
                           "                ",                          //"0=inhib.  cc:\6\7\x08",

    /* MSP n. 38 */        "@B042§\x08         "                        //"COFFEE SEQUENCE "
                           "                ",                          //"1=cof. before  \x08",

    /* MSP n. 39 */        "@B043§\0\1\2\3\4\5\6\7§\x08"                //"Kilowatt hours  "
                           "                ",                          //"      \0\1\2\3\4\5\6\7.\x08",
    #ifdef CUSTOMER_NESTLE
    /* MSP n.  40 */       "@B044§\6\7\x08       "                           //"X4 rinse 2 wat. "
                           "                ",                          //"in brewer  \6\7\x08ml"
    #else
    /* MSP n.  40 */       "@B340§\6\7\x08       "							//"X4 rinse 2 wat. "
                           "                ",							//"in brewer  \6\7\x08ml"
    #endif

    /* MSP n. 41 */        "@B045§\x08         "                        //"first installat."      
                           "                ",                          //" 0=first       \x08", 
    #ifndef CAPPUCCINATORE_INDUX
    /* MSP n. 42 */        "@B046           "                           //"not used        "
                           "                ",                          //"                ",
    #else
    /* MSP n. 42 */        "@B047§\0\1\2\3\4\5\6\7\x08\x09"             //"Fresh Milk      "
                           "\x0A\x0B              ",                    //"    \0\1\2\3\4\5\6\7\x08\x09\x0A\x0B",
    #endif   

    #ifdef CUSTOMER_NESTLE
    /* MSP n. 43 */        "@B048§\6\7§\x08      "                      //"VOLTAGE         "
                           "                ",                          //"volt:       \6\7.\x08",
    #else
    /* MSP n. 43 */        "@B341§\6\7§\x08      "						//"VOLTAGE         "       "     Tension    "
                           "                ",							//"volt:       \6\7.\x08", "Volt:       \6\7.\x08",
    #endif

    #ifdef COMPILO_TEST_MODEM
    /* MSP n. 44 */        "@B049           "                           //"   TEST MODEM   "
                           "                ",                          //"      SEL 4     ",
    #else
    /* MSP n. 44 */        "@B050           "                           //"not used        "
                           "                ",                          //"                ",   
    #endif                                          
    /* MSP n. 45 */        "@B051           "                           //"PRESELECTION    "
                           "                ",                          //"                ",

    /* MSP n. 46 */        "@B052           "                           //"INHIBITED       "
                           "                ",                          //"----------------",

    /* MSP n. 47 */        "@B053§\6\7§\x08      "                           //"X5 wait time 2  "
                           "                ",                          //"wat. brew. \6\7.\x08s",

    /* MSP n. 48 */        "@B054§\x0A§\6\7\x08     "					//"Def. Vibr. mot. " 		//VIBR_MOT_SPEED_GRINDER_1, 2, 3, 4
                           "                ",							//"Speed gr. \x0A  \6\7\x08",

    /* MSP n. 49 */        "@B055§\x08         "                        //"ENABLE DISPLAY  "
                           "                ",                          //"TEMPERA. 1=YES \x08",

    /* MSP n. 50 */        "@B056§\6\7§\x08      "                      //"X6 wait time 3  "
                           "                ",                          //"empty wat. \6\7.\x08s",

    /* MSP n.  51 */       "@B057§\0\1\2\3\4\5\6\7\x08 "                //"TOTAL SELECTIONS"
                           "                ",                          //"       \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  52 */       "@B058§\0\1\2\3\4\5\6\7\x08 "                //"PART. SELECTIONS"
                           "                ",                          //"       \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  53 */       "@B059§\0\1\2\3\4\5\6\7\x08 "                //"TOTAL  MONEY    "
                           "                ",                          //"       \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  54 */       "@B060§\0\1\2\3\4\5\6\7\x08 "                //"PARTIAL MONEY   "
                           "                ",                          //"       \0\1\2\3\4\5\6\7\x08",                       

    /* MSP n.  55 */       "@B061§\0\1\2\3\4\5\6\7\x08 "                //"TOTAL TESTS     "
                           "                ",                          //"       \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  56 */       "@B062§\0\1\2\3\4\5\6\7\x08 "                //"PARTIAL TESTS   "
                           "                ",                          //"       \0\1\2\3\4\5\6\7\x08",                     
    #ifdef COMPILO_DB_CASHLESS
    /* MSP n.  57 */       "@B063§\x0C§\0\1\2\3\4\5\6\7"                 //"total loaded on "
                           "\x08               ",                      //"card\x0C  \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  58 */       "@B064§\x0C§\0\1\2\3\4\5\6\7"                 //"part. loaded on "
                           "\x08               ",                      //"card\x0C  \0\1\2\3\4\5\6\7\x08",                       

    /* MSP n.  59 */       "@B065§\x0C§\0\1\2\3\4\5\6\7"                 //"total unloaded  "
                           "\x08               ",                      //"card\x0C  \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  60 */       "@B066§\x0C§\0\1\2\3\4\5\6\7"                 //"part. unloaded  "
                           "\x08               ",                      //"card\x0C  \0\1\2\3\4\5\6\7\x08",
    #endif
    #ifndef COMPILO_DB_CASHLESS
    #ifdef ABIL_RFID                     
    #ifdef ABIL_CREDIT_RFID
    /* MSP n.  57 */       "@B067§\0\1\2\3\4\5\6\7\x08 "                //"total loaded on "
                           "                ",                          //"card   \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  58 */       "@B068§\0\1\2\3\4\5\6\7\x08 "                //"part. loaded on "
                           "                ",                          //"card   \0\1\2\3\4\5\6\7\x08",                       

    /* MSP n.  59 */       "@B069§\0\1\2\3\4\5\6\7\x08 "                //"total unloaded  "
                           "                ",                          //"card   \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  60 */       "@B070§\0\1\2\3\4\5\6\7\x08 "                //"part. unloaded  "
                           "                ",                          //"card   \0\1\2\3\4\5\6\7\x08",
    #else
    /* MSP n.  57 */       "@B071           "                           //" not used       "
                           "                ",                          //"                ",

    /* MSP n.  58 */       "@B072           "                           //" not used       "
                           "                ",                          //"                ",

    /* MSP n.  59 */       "@B073           "                           //" not used       "
                           "                ",                          //"                ",

    /* MSP n.  60 */       "@B074           "                           //" not used       "
                           "                ",                          //"                ",
    #endif
    #else
    /* MSP n.  57 */       "@B075           "                           //" not used       "
                           "                ",                          //"                ",

    /* MSP n.  58 */       "@B076           "                           //" not used       "
                           "                ",                          //"                ",

    /* MSP n.  59 */       "@B077           "                           //" not used       "
                          "                ",                           //"                ",

    /* MSP n.  60 */       "@B078           "                           //" not used       "
                           "                ",                          //"                ",
    #endif
    #endif
        #ifdef COMPILO_4_LISTE_PREZZI 
    /* MSP n.  61 */       "@B079§^§\x0A\x0B§\0\1\2\3\4"               //"PART. ^ SEL.  \x0A\x0B"
                           "\5\6\7\x08            ",                     //"       \0\1\2\3\4\5\6\7\x08",
        #else
    /* MSP n.  61 */       "@B080§\x0A\x0B§\0\1\2\3\4\5\6"               //"PART.  SEL.  \x0A\x0B "
                           "\7\x08              ",                     //"       \0\1\2\3\4\5\6\7\x08",
        #endif
    /* MSP n.  62 */       "@B081§\x0A\x0B§\0\1\2\3\4\5\6"               //"PART.  SEL.  \x0A\x0B "
                           "\7\x08              ",                     //"HAPPY  \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  63 */       "@B082§\x0A\x0B§\0\1\2\3\4\5\6"               //"PART.  SEL.  \x0A\x0B "
                           "\7\x08              ",                     //"FRE.JUG\0\1\2\3\4\5\6\7\x08",

    /* MSP n.  64 */       "@B083§\x0A§\3\4\5\6\7\x08  "                //"COIN   \x0A        "
                           "                ",                          //"          \3\4\5\6\7\x08",

    /* MSP n.  65 */       "@B084§\x0A\x0B§\3\4\5\6\7\x08 "             //"PRICE  \x0A\x0B       "
                           "                ",                          //"          \3\4\5\6\7\x08",

    /* MSP n.  66 */       "@B085§\6\7\x08\x09      "                     //"   TEMPERATURE  "
                           "                ",                          //"Temp. EV1    \6\7\x08",
    #ifdef BUSINESS_LINE
    /* MSP n.  67 */       "@B086§\6\7\x08       "                     //"   DEFINITION   "
                           "                ",                          //"first coffee \6\7\x08",
    #else
    /* MSP n.  67 */       "@B087§\6\7\x08\x09      "                     //"   TEMPERATURE  "
                           "                ",                          //"Temp. EV2    \6\7\x08",
    #endif
    /* MSP n.  68 */       "@B088§\x08         "					//"PL for cash     "        //"TEST RUNNING    "
                           "                ",						//"0=PL1 1=PL2    \x08",         //"                ",
    #if (GRINDER_MAX_NUM == 2)
    /* MSP n.  69 */       "@B089§\x08         "                        //"select grinder 2"
                           "                ",                          //"1=yes          \x08",
    #else 
    /* MSP n.  69 */       "@B090           "                           //"  not used      "
                           "                ",                          //"                ",
    #endif 
    /* MSP n.  70 */       "@B091           "                           //"preselection    "
                           "                ",                          //"BARLEY          ",

    #ifdef CUSTOMER_NESTLE
    /* MSP n.  71 */       "@B092           "                           //"REGISTRATION----"  "ENREGISTREMENT  "
                           "                ",                          //"-OUT OF SERVICE ", " -HORS SERVICE- ",
    #else
    /* MSP n.  71 */       "@B342           "                           //"REGISTRATION----"  "Historique des  "
                           "                ",                          //"-OUT OF SERVICE ", " -HORS SERVICE- ",
    #endif

    /* MSP n.  72 */       "@B093§\7\x08        "                       //"Selection repeat"        
                           "                ",                          //"              \7\x08",

    #ifdef BUSINESS_LINE
    /* MSP n.  73 */       "@B094§\6\7§\x08      "                      //"heating time    "
                           "                ",                          //"      sec.: \6\7.\x08",
    #else
    /* MSP n.  73 */       "@B095§\6\7\x08\x09      "                      //"   TEMPERATURE  "
                           "                ",                          //"Temp. EV3    \6\7\x08",        
    #endif
    /* MSP n.  74 */       "@B096§\x0A\x0B        "                     //"PROGRAMMING-----"
                           "                ",                          //"-BUTTON \x0A\x0B------",

    /* MSP n.  75 */       "@B097           "                           //"PROGRAMMING-----"
                           "                ",                          //"-CLOCK----------",
            #ifdef COMPILO_4_LISTE_PREZZI 
    /* MSP n.  76 */       "@B098§^         "                           //"PROGRAMMING-----"
                           "                ",                          //" PRICES       ^ ",
            #else
    /* MSP n.  76 */       "@B099           "                           //"PROGRAMMING-----"
                           "                ",                          //"-PRICES---------",
            #endif
    /* MSP n.  77 */       "@B100           "                           //"PROGRAMMING-----"
                           "                ",                          //"-COINS----------",

    /* MSP n.  78 */       "@B101           "                           //"PROGRAMMING-----"
                           "                ",                          //"-TEMPERATURE----",

    /* MSP n.  79 */       "@B102           "                           //"PROGRAMMING-----"
                           "                ",                          //"-MISCELLANEOUS--",

    /* MSP n.  80 */       "@B103           "                           //"DIAGNOSTICS-----"
                           "                ",                          //"----------------",

    /* MSP n.  81 */       "@B104           "                           //"SALES AUDIT-----"
                           "                ",                          //"----------------",
            #ifdef COMPILO_4_LISTE_PREZZI 
    /* MSP n.  82 */       "@B105§^         "                           //"PROGRAMMING-----"
                           "                ",                          //" HAPPY PRICE=^  ",
            #else
    /* MSP n.  82 */       "@B106           "                           //"PROGRAMMING-----"
                           "                ",                          //"-HAPPY PRICE    ",
            #endif
    /* MSP n.  83 */       "@B107           "                           //"PROGRAMMING-----"
                           "                ",                          //"PRODUCT QTY     ",

    /* MSP n.  84 */       "@B108           "                           //"PROGRAMMING-----"
                           "                ",                          //"-MAINTENANCE----",

    /* MSP n.  85 */       "@B109           "                           //"PROGRAMMING-----"
                           "                ",                          //"RFID CARD       ",

    /* MSP n.  86 */       "@B110           "                           //"TEST MOV. SUGAR "
                           "                ",                          //"sel 4           ",

    /* MSP n.  87 */       "@B111§\7\x08        "                       //"Tea Bag         "
                           "                ",                          //"0=inhibit     \7\x08",  
    #ifdef TEST_CICLICO
    /* MSP n. 88 */        "@B112§\4\5\6\7\x08     "                    //"numero cicli    "
                           "                ",                          //"           \4\5\6\7\x08",

    /* MSP n. 89 */        "@B113§\4\5\6\7\x08     "                    //"pausa ciclico   "
                           "                ",                          //"sec:       \4\5\6\7\x08",

    /* MSP n. 90 */        "@B114§\x08         "                        //"selez. ciclico  "
                           "                ",                          //"0=fissa        \x08",                       
    #else
    /* MSP n. 88 */        "@B115§\4\5\6\7\x08     "                    //"machine code    "
                           "                ",                          //"  A        \4\5\6\7\x08",

    /* MSP n. 89 */        "@B116§\4\5\6\7\x08     "                    //"machine code    "
                           "                ",                          //"  B        \4\5\6\7\x08",

    /* MSP n. 90 */        "@B117§\x08         "                        //"message number  "
                           "                ",                          //"               \x08",
    #endif
    /* MSP n. 91 */        "@B118§\0\1\2\3\4\5\6\7\x08\x09"                //"coin-mech type  "
                           "\x0A\x0B\x0C\x0D\x0E\x0F          ",     //"\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F",
    #ifdef CODICE_ACCESSO_PROG
    /* MSP n. 92 */        "@B119§\6\7\x08       "                    //"access code     "
                           "                ",                          //"           \4\5\6\7\x08",
    #else
    /* MSP n. 92 */        "@B120           "                           //"not used        "
                           "                ",                          //"                ",
    #endif

    #ifdef CUSTOMER_NESTLE
    /* MSP n. 93 */        "@B121§\x08         "                        //"stirrer 0=before"      "Palette 0=avant "
                           "                ",                          //" 1=after       \x08",  "1=après        \x08",
    #else
    /* MSP n. 93 */        "@B343§\x08         "                        //"stirrer 0=before"      "Spatule  0=avant"
                           "                ",                          //" 1=after       \x08",  "1=après        \x08",
    #endif

    /* MSP n. 94 */        "@B122§\5\6\7\x08      "                     //"fan time        "
                           "                ",                          //"min.        \5\6\7\x08",

    /* MSP n. 95 */        "@B123§\7§\x08       "                       //"Beep time       "
                           "                ",                          //"             \7.\x08",

    #ifdef CUSTOMER_NESTLE
    /* MSP n. 96 */        "@B124§\x08         "                        //"decimal number  " "Nombre décimaux "
                           "                ",                          //"               \x08", "               \x08",
     #else
    /* MSP n. 96 */        "@B344§\x08         "                        //"decimal number  " "Nombre décimale "
                           "                ",                          //"               \x08", "               \x08",
    #endif

    /* MSP n. 97 */        "@B125§\x08         "						//"PL for cashless "      //"confirm partial "
                           "                ",                          //"0=PL1 1=PL2    \x08",	//"reset  press P10",

    ///* MSP n. 98 */        "@B126           "                            //"language:       "
    //					   "                ",                          //"        english ",
    /* MSP n. 98 */        "language:       "                            //"language:       "
                           "Multilanguage   ",                          //"        english ",
    #ifdef ABIL_TASTO_STOP                        
    /* MSP n. 99 */        "@B127§\x08         "                        //"    SEL STOP    "
                           "                ",                          //"   no=0 yes=1  \x08",
    #else
    /* MSP n. 99 */        "@B128           "                           //"not used        "
                           "                ",                          //"                ",
    #endif
    #ifdef ABIL_DELTA_TEMPERATURA
    /* MSP n. 100 */       "@B129§\6\7\x08       "                      //"   TEMPERATURE  "
                           "                ",                          //"Delta        \6\7\x08",
    #else                       
    /* MSP n. 100 */       "@B130           "                           //"not used        "
                           "                ",                          //"                ",
    #endif
    #ifdef MODELLO_ESPRESSO
    /* MSP n.101 */        "@B131           "                           //"not used        "    
                           "                ",                          //"                ",
    #endif
    #ifdef MODELLO_SOLUBILE
    /* MSP n. 101 */       "@B132§\x09\x0A§\4§\6\7\x08  "               //"tuning pump   \x09\x0A"  
                           "                ",                          //"         \4 \6\7\x08 %",
    #endif
    /* MSP n.102 */        "@B133§\x09\x0A§\4§\6\7\x08  "               //"tuning motor  \x09\x0A"
                           "                ",                          //"         \4 \6\7\x08 %",              
    #ifdef MODELLO_ESPRESSO
        #ifdef DISABILITA_CONVERSIONE_GRAMMI
    /* MSP n. 103 */       "@B134§\6\7§\x08      "                      //"coffee time     "
                           "                ",                          //"grinder     \6\7.\x08",
        #else
    /* MSP n. 103 */       "@B135§\6\7§\x08      "                      //"coffee grams    "
                           "                ",                          //"grinder     \6\7.\x08",
        #endif
        #ifdef ABIL_CALIBRAZIONE_MACINA
    /* MSP n.104 */        "@B136§\4§\6\7\x08     "                     //"tuning grinder  "
                           "                ",                          //"         \4 \6\7\x08 %",
        #else
    /* MSP n. 104 */       "@B137           "                           //"Preselection    "
                           "                ",                          //"NO SUGAR        ",
        #endif                       
    #else
    /* MSP n. 103 */       "@B138           "                           //"TEST MOV. SUGAR "
                           "                ",                          //"sel 4           ",

    /* MSP n. 104 */       "@B139           "                           //"Preselection    "
                           "                ",                          //"NO SUGAR        ",
    #endif
    /* MSP n. 105 */       "@B140§\7§\x08       "                       //"extra milk      "
                           "                ",                          //"quantity    +\7.\x08",
    #ifdef ABIL_MOTORI_VIRTUALI
    /* MSP n. 106 */       "@B141§\6\7§\x08      "                      //"Latte-Macchiato "
                           "                ",                          //"START BREWER\6\7.\x08",
    #else
    /* MSP n.106 */        "@B142           "                      		//"not used        "
                           "                ",                          //"            \6\7.\x08",
    #endif
    #ifdef ABIL_LIMIT_CURRENT
    /* MSP n. 107 */       "@B143           "                           //"Limiting current"
                           "                ",                          //"10 A            ",
    #else
    /* MSP n. 107 */       "@B144           "                           //"    Not Used    "
                           "                ",                          //"                ",
    #endif                        
    #ifdef ABIL_RISCALDATORE
    /* MSP n.  108*/       "@B145§\6\7\x08       "                      //"   TEMPERATURE  "
                           "                ",                          //"heater:      \6\7\x08",
    #else
    /* MSP n.108 */        "@B146           "							//"not used        "
                           "                ",                          //"                ",
    #endif
    /* MSP n. 109 */       "@B147§\x0A\x0B\x0C\x0D§\x0E§\4\5\6"          //"coffee grains   "
                           "\7§\x08             ",                     //"[\x0A\x0B\x0C\x0D.\x0E]  \4\5\6\7.\x08",

    /* MSP n. 110 */       "@B148§\7\x08        "                       //"water quantity  "
                           "                ",                          //"ESPRESSO   -\7\x08 %",

    /* MSP n. 111 */       "@B149§\x08         "                        //"canister        "
                           "                ",                          //"Cafe 2    n:   \x08",

    /* MSP n. 112 */       "@B150§\7\x08        "                     //"Cafe 2  price   "
                           "                ",                          //"0=+ 1=-       \7\x08",

#if defined(MODELLO_SOLUBILE) && defined(UPDATE_DECAF)
    /* MSP n. 113 */       "@B346§\x08         "                      	//"ev-mixer        "
                           "                ",                          //"CAFE 2    n:   \x08",
#else
    /* MSP n. 113 */       "@B151§\x08         "                        //"ev-mixer        "
                           "                ",                          //"CAFE 2    n:   \x08",
#endif	

    /* MSP n. 114 */       "@B152§\0\1§\2\3\4\5\6  "                      //"Enable preselect"
                           "                ",                          //"button    \0\1:\2\3\4",

    /* MSP n. 115 */       "@B153§\x08         "                        //"canister        "
                           "                ",                          //"SUGAR        n:\x08",

    /* MSP n. 116 */       "@B154§\6\7\x08       "                      //"X7 rinsing      "
                           "                ",                          //"temperat.  \6\7\x08  ",

    /* MSP n. 117 */       "@B155           "                           //"Preselection    "
                           "                ",                          //"ESPRESSO        ",

    /* MSP n. 118 */       "@B157           "                           //"Preselection    "
                           "                ",                          //"EXTRA SUGAR     ",

    /* MSP n. 119 */       "@B158§\x08         "                        //"PRODUCT         "
                           "                ",                          //"MILK  LM     n:\x08",

    /* MSP n. 120 */       "@B159§\x08         "                        //"Enable  counter "
                           "                ",                          //" 0=no  1=yes   \x08",

    /* MSP n. 121 */       "@B160§\7§\x08       "                       //"extra sugar     "
                           "                ",                          //"quantity    +\7.\x08",

    /* MSP n. 122 */       "@B161§\x08         "                        //"canister        "
                           "                ",                          //"BARLEY       n:\x08",

    /* MSP n. 123 */       "@B162§\x08         "                        //"ev-mixer        "
                           "                ",                          //"BARLEY       n:\x08",

    /* MSP n. 124 */       "@B163§\7\x08        "                     //"BARLEY price    "
                           "                ",                          //"0=+ 1=-       \7\x08",

    /* MSP n. 125 */       "@B164§\x0E\x0F§\0\1\2§\3§\4"             //"n.\x0E\x0F  off \0\1 \2  "
                           "\5§\6\7§\x08\x09§\x0A\x0B§\x0C\x0D   ",    //"\3\4:\5\6 \7\x08-\x09\x0A-20\x0B\x0C",

    /* MSP n. 126 */       "@B165§\x0F         "                        //"n.\x0F  NO         "
                           "                ",                          //"OUT OF SERVICE  ",

    #ifdef CUSTOMER_NESTLE
    /* MSP n. 127 */       "@B166§\0\1\2\3\4\5\6\7\x08\x09"             //"stirrer         " "palette         "
                           "\x0A\x0B\x0C\x0D\x0E\x0F          ",           	//"\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F",

    /* MSP n. 128 */       "@B167§\x08         "                        //"cup sensor      "  "Capteur tasse   "
                           "                ",                          //"1=Enable       \x08", "Gobelet 1=hab. \x08",
    #else
    /* MSP n. 127 */       "@B156§\0\1\2\3\4\5\6\7\x08\x09"             //"stirrer         " "Spatule         "
                           "\x0A\x0B\x0C\x0D\x0E\x0F          ",           	//"\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F",

    /* MSP n. 128 */       "@B345§\x08         "                        //"cup sensor      "  "Détecteur tasse   "
                           "                ",                          //"1=Enable       \x08", "Gobelet 1=hab. \x08",
    #endif

    /* MSP n. 129 */       "@B168§\6\7\x08       "						//"Vibr.mot.       " 	//VIBR_MOT_TIME_GRINDER_1, 2, 3, 4
                           "                ",							//"Time gr.     \6\7\x08",

    /* MSP n. 130 */       "@B169§\6\7\x08       "						//"Vibr. mot.      " 	//VIBR_MOT_SPEED_GRINDER_1, 2, 3, 4
                           "                ",							//"Speed gr.    \6\7\x08",

    /* MSP n. 131*/        "@B170§\x0A\x0B\x0C       "                           //"PWM Pump        "
                           "                ",                          //"  \x0A\x0B\x0C%          ",
    #ifdef MODELLO_ESPRESSO
    #ifdef SELECT_TYPE_FREE_VEND
    /* MSP n. 132*/        "@B171§\x08         "                        //"FREE VEND enable"
                           "                ",                          //"0=no 1=1 2=++  \x08",
    #else
    /* MSP n. 132*/        "@B172           "                           //"not used        "
                           "                ",                          //"                ",
    #endif
    /* MSP n. 133 */       "@B173§\x0A\x0B\x0C\x0D\x0E§\4\5\6\7"         //"dec. cof.grounds"
                           "\x08               ",                      //"[\x0A\x0B\x0C\x0D\x0E]    \4\5\6\7\x08",
    #endif

    #ifdef MODELLO_SOLUBILE
      #ifdef SELECT_TYPE_FREE_VEND
    /* MSP n. 132*/        "@B174§\x08         "                        //"FREE VEND enable"
                           "                ",                          //"0=no 1=1 2=++  \x08",
      #else
    /* MSP n. 132*/        "@B175           "                           //"not used        "
                           "                ",                          //"                ",
      #endif			   
    /* MSP n. 133 */       "@B176           "                           //"not used        "
                           "                ",                          //"                ",
    #endif   

    /* MSP n. 134 */       "@B177§\x0F§\x0A\x0B\x0C\x0D§\x0E§\4"         //"product qty   \x0F "
                           "\5\6\7§\x08           ",                   //"[\x0A\x0B\x0C\x0D.\x0E]  \4\5\6\7.\x08",

    /* MSP n. 135 */       "@B178           "                           //"Preselection    "
                           "                ",                          //"JUG             ",
    #ifdef ABIL_CAPPUCCINATORE
    /* MSP n. 136 */       "@B179§\6\7§\x08      "                      //"EV Fresh-milk   "//ev latte fresco
                           "                ",                          //"            \6\7.\x08",
    #else
    /* MSP n. 136 */       "@B180           "							//"not used        "
                           "                ",                          //"                ",
    #endif
    /* MSP n. 137 */       "@B181§\x0F§\4\5\6\7§\x08  "                 //"prod. \x0F warning "
                           "                ",                          //"thresold: \4\5\6\7.\x08",

    /* MSP n. 138 */       "@B182§\x0F§\x08       "                     //"abil stop prod \x0F"
                           "                ",                          //"1=stop         \x08",

    /* MSP n. 139 */       "@B183§\0\1\2\3\4\5\6\7\x08 "                //"TOTAL  FREE     "      //VA_302 num. vendite gratuite storico
                           "                ",                          //"       \0\1\2\3\4\5\6\7\x08",

    /* MSP n. 140 */       "@B184§\0\1\2\3\4\5\6\7\x08 "                //"PART.    FREE   "      //VA_304 num.vendite gratuite parziale
                           "                ",                          //"       \0\1\2\3\4\5\6\7\x08",

    /* MSP n. 141 */	   "@B185§\0\1\2\3\4\5\6\7\x08 "                //"TOTAL  CASH     "      //CA_201 valore venduto cash storico
                           "                ",                          //"CASH   \0\1\2\3\4\5\6\7\x08",

    /* MSP n. 142 */       "@B186§\0\1\2\3\4\5\6\7\x08 "                //"PART.  CASH     "      //CA_203 valore venduto cash parziale
                           "                ",                          //"CASH   \0\1\2\3\4\5\6\7\x08",

    /* MSP n. 143 */	   "@B187§\0\1\2\3\4\5\6\7\x08 "                //"N.TOT. SEL. CASH"      //CA_202 num.vendite per cassa storico
                           "                ",                          //"       \0\1\2\3\4\5\6\7\x08",

    /* MSP n. 144*/        "@B188§\0\1\2\3\4\5\6\7\x08 "                //"N.PART.SEL. CASH"	   //CA_204 num. vendite per cassa parziale
                           "                ",                          //"       \0\1\2\3\4\5\6\7\x08",

    /* MSP n. 145 */       "@B189§\0\1\2\3\4\5\6\7\x08 "                //"TOTAL  CASH-BOX "      //CA_305 valore della  cassa storico
                           "                ",                          //"       \0\1\2\3\4\5\6\7\x08",

    /* MSP n. 146 */       "@B190§\0\1\2\3\4\5\6\7\x08 "                //"PART.  CASH-BOX "      //CA_301 valore della  cassa parziale
                           "                ",                          //"       \0\1\2\3\4\5\6\7\x08",
    #ifdef COMPILO_DB_CASHLESS
    /* MSP n. 147 */       "@B191§\x0C§\0\1\2\3\4\5\6\7"                 //"TOTAL SEL. CARD\x0C"      //DA_202  num. vendite per carta storico
                           "\x08               ",                      //"       \0\1\2\3\4\5\6\7\x08",

    /* MSP n. 148 */       "@B192§\x0C§\0\1\2\3\4\5\6\7"                 //"PART. SEL. CARD\x0C"      //DA_204	  num. vendite per carta parziale
                           "\x08               ",                      //"       \0\1\2\3\4\5\6\7\x08",
    #else
    /* MSP n. 147 */       "@B193§\0\1\2\3\4\5\6\7\x08 "                //"TOTAL  SEL. CARD"      //DA_202  num. vendite per carta storico
                           "                ",                          //"       \0\1\2\3\4\5\6\7\x08",

    /* MSP n. 148 */       "@B194§\0\1\2\3\4\5\6\7\x08 "                //"PART.  SEL. CARD"      //DA_204	  num. vendite per carta parziale
                           "                ",                          //"       \0\1\2\3\4\5\6\7\x08",
    #endif
    /* MSP n.149 */        "@B195           "                           //"Ejection tubes  "
                           "                ",                          //"b. :4-5-7-8-9-10",

    /* MSP n.150 */        "@B196§\x08         "                        //"escrow enable   "
                           "                ",                          //"0=enab. 1=dis. \x08",

    /* MSP n.151 */        "@B197§\1\2\3\4\5\6\7\x08  "                 //"credit max      "
                           "                ",                          //"        \1\2\3\4\5\6\7\x08",

    /* MSP n.152 */        "@B198§\1\2\3\4\5\6\7\x08  "                 //"rest  max       "
                           "                ",                          //"        \1\2\3\4\5\6\7\x08",

    /* MSP n.153 */        "@B199§\x08         "                        //"Sell type       "
                           "                ",                          //"0=sing. 1=mult.\x08",

    /* MSP n.154 */        "@B200§\1\2\3\4\5\6\7\x08  "                 //"Token value     "
                           "                ",                          //"        \1\2\3\4\5\6\7\x08",

    /* MSP n.155 */        "@B201§\x0A§\x08       "                     //"coin rest   \x0A  \x08"
                           "                ",                          //" 0=acc. 1=disab.",

    /* MSP n.156 */        "@B202§\x0A§\x08       "                     //"coin no rest \x0A \x08"
                           "                ",                          //" 0=acc. 1=disab.",

    /* MSP n.157 */        "@B203§\1\2\3\4\5\6\7\x08  "                 //"MDB tubes value "
                           "                ",                          //"        \1\2\3\4\5\6\7\x08",

    /* MSP n.158 */        "@B204§\x08         "                        //"Bill validator  "
                           "                ",                          //"enab=  0;1;2  =\x08",

    /* MSP n.159 */        "@B205           "                           //"PROGRAMMING-----"
                           "                ",                          //"- MDB ----------",

    /* MSP n.  160 */      "@B206           "                           //"Preselection    "
                           "                ",                          //"EXTRA MILK      ",

    /* MSP n.  161 */      "@B207           "                           //"Preselection    "
                           "                ",                          //"ESPRESSO        ",
    #ifdef EASY_PRESEL
    /* MSP n.  162 */      "@B208           "                           //"Preselection    "
                           "                ",                          //"SELECTIONS 25-36",
    #else
    /* MSP n.  162 */      "@B209           "                           //"Preselection    "
                           "                ",                          //"DECAFFEINATED   ",
    #endif                       
    #ifdef TIPO_NO_CUP
    /* MSP n.  163 */      "@B210           "                           //"Preselection    "
                           "                ",                          //"not used        ",
    #else
    /* MSP n.  163 */      "@B211           "                           //"Preselection    "
                           "                ",                          //"NO CUP          ",
    #endif
    /* MSP n.  164 */      "@B212           "                           //"Preselection    "
                           "                ",                          //"BARLEY          ",

    /* MSP n.  165 */      "@B213           "                           //"   TEST GROUP   "
                           "                ",                          //"Absorption  sel4",

#ifdef BUSINESS_LINE
	#if !defined(MODELLO_EC) && defined(MODELLO_ESPRESSO)
    /* MSP n.  166 */      "@B214§\x08         "                        //"boiler  cc:     "                   
                           "                ",                          //"0=400   1=800  \x08",                       
    #else
    /* MSP n.  166 */      "@B215           "                           //"not used        "
                           "                ",                          //"                ",
    #endif
#else
    /* MSP n.  166 */      "@B349§\x08         " 						//"POWER ADJ. PUMP "
                           "                ",							//"0=NO 1=YES     \x08",
#endif	

    /* MSP n.  167 */      "@B216§\6\7\x08       "                      //"quick menu      "		/* @AS Issue_#1598: limited access to quick menù functionalities */
                           "                ",                          //"access code  \6\7\x08",
    #ifdef ABIL_CAPPUCCINATORE
    /* MSP n.  168 */      "@B217§\6\7§\x08      "                      //"EV air          "
                           "                ",                          //"Fresh-milk  \6\7.\x08",
    #else
    /* MSP n.  168 */      "@B218           "							 //"not used        "
                           "                ",                          //"                 ",
    #endif
    /* MSP n.  169 */      "@B219           "                           //"TUNING          "
                           "                ",                          //"MOTORS          ",

    /* MSP n. 170  */      "@B220§\5\6\7\x08      "                     //"Calibrate Coffee"            	         
                           "                ",                          //"Push PROG   \5\6\7\x08",
    #ifdef ABIL_LATTE_MACCHIATO
    /* MSP n.  171 */      "@B221§\x08         "                        //"LM Milk water   "		//EV virtuale     
                           "                ",                          //"Number=        \x08",
    #else
    /* MSP n.  171 */      "@B222           "                           //"not used        "
                           "                ",                          //"                ",
    #endif
    #ifdef MODELLO_ESPRESSO
    /* MSP n.  172 */      "@B223           "                           //" uninstallation "
                           "                ",                          //"   10=START     ",

    /* MSP n.  173 */      "@B224§\6\7\x08\x09      "                      //"   TEMPERATURE  "
                           "                ",                          //"Espresso     \6\7\x08",        
    #else
    /* MSP n.  172 */      "@B225           "                           //"not used        "
                           "                ",                          //"                ",

    /* MSP n.  173 */      "@B226§\6\7\x08\x09      "                      //"   TEMPERATURE  "
                           "                ",                          //"boiler       \6\7\x08",
    #endif

    /* MSP n.  174 */      "@B227§\6\7\x08       "                      //"X8 Clousure     "
                           "                ",                          //"brewer      \6\7\x08%"   

    /* MSP n.  175 */      "@B228§\6\7\x08\x09      "                      //"   TEMPERATURE  "
                           "                ",                          //"Latte Mac.   \6\7\x08",        

    /* MSP n.  176 */      "@B229§\0\1\2\3\4\5\6\7\x08 "                 //"code   ID 101   "
                           "                ",                          //"       \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  177 */      "@B230§\0\1\2\3\4\5\6\7\x08 "                 //"code   ID 104   "
                           "                ",                          //"       \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  178 */      "@B231§\0\1\2\3\4\5\6\7\x08 "                 //"code   ID 106   "
                           "                ",                          //"       \0\1\2\3\4\5\6\7\x08",

    /* MSP n.  179 */      "@B232§\6\7\x08       "                      //"address VIDTS   "
                           "                ",                          //"             \6\7\x08",
    #ifdef  UPD_PROG_EVADTS
    /* MSP n.  180 */      "@B233§\0\1\2\3\4\5\6\7\x08\x09"                //"Protocol        "
                           "\x0A\x0B\x0C\x0D\x0E\x0F          ",     //"\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F",
    #else
    #ifdef SELECT_TYPE_DATA_AUDIT
    /* MSP n.  180 */      "@B234§\x08         "                        //"DataAudit 0=TMON"
                           "                ",                          //"1=DDCMP 2=DIAG \x08",
    #else
    /* MSP n.  180 */      "@B235           "							//"not  used       "
                           "                ",                          //"                ",
    #endif
    #endif
    /* MSP n.  181 */      "@B236           "                           //"PROGRAMMING-----"
                           "                ",                          //"-ID. MACHINE    ",
    #ifdef SUMMERTIME
    /* MSP n. 182 */       "@B237§\x08         "                        //"Summer Time     "
                           "                ",                          //"1=yes          \x08",
    #else
    /* MSP n. 182 */       "@B238           "							 //"not used        "
                           "                ",                          //"                 ",
    #endif  
    /* MSP n. 183 */       "@B239           "							//"DRIP FILTER     "
                           "                ",                          //"                "                      

    /* MSP n. 184 */       "@B240§\7\x08        "                   	//"X9 wait time 3  "
                           "                ",                          //"last cof. \7\x08 min",                     

    /* MSP n. 185 */       "@B241§\6\7\x08       "                      //"X10 min cof. qty"
                           "                ",                          //"to engage \6\7\x08 cc",

    /* MSP n. 186 */       "@B242§\6\7\x08       "                      //"A1 PWM Variflex "
                           "                ",                          //"move        \6\7\x08%",

    /* MSP n. 187 */       "@B243§\6\7§\x08      "                      //"A2 Pump On time "
                           "                ",                          //"         \6\7.\x08[s]"
                #ifdef COMP_PREZZO_ECO_BIC
    #ifdef EASY_PRESEL
    /* MSP n.  188 */      "@B244           "                           //"Preselection    "
                           "                ",                          //"SELECTIONS 37-48",
    #else
    /* MSP n.  188 */      "@B245           "                           //"  Preselection  "
                           "                ",                          //"    BIG CUP     ",
    #endif
    #ifdef ABILITAZIONE_SENSORE_CAFFE
    /* MSP n.  189 */      "@B246§\x08         "                        //" Coffee Sensor  "
                           "                ",                          //" 1=Enable      \x08",
    #else											
    /* MSP n.  189 */      "@B247           "                           //"not used        "
                           "                ",                          //"                ",           					   
    #endif
    /* MSP n. 190 */       "@B248§\7\x08        "                       //"WATER           "
                           "                ",                          //"percent    +\7\x08 %",

    /* MSP n. 191 */       "@B249§\7\x08        "                     //"+ or   -  PRICE "   
                           "                ",                          //"0=+  1=-      \7\x08",

    /* MSP n. 192 */       "@B250§\7\x08        "                       //"PRODUCT         "
                           "                ",                          //"percent    +\7\x08 %",
                #else
    /* MSP n.  188 */      "@B251           "                           //"not used        "
                           "                ",                          //"                ",
    /* MSP n.  189 */      "@B252           "                           //" not used       "
                           "                ",                          //"                ",
    /* MSP n.  190 */      "@B253           "                           //"not used        "
                           "                ",                          //"                ",
    /* MSP n.  191 */      "@B254           "                           //" not used       "
                           "                ",                          //"                ",
    /* MSP n.  192 */      "@B255           "                           //"not used        "
                           "                ",                          //"                ",
                #endif                     
    /* MSP n. 193 */       "@B256§\7\x08        "                     //"PREINFUSION     "
                           "                ",                          //"0=no   sec.:\7\x08  ",

    /* MSP n. 194 */       "@B257§\7\x08        "                     //"JUG             "
                           "                ",                          //"0=no        n:\7\x08",

    /* MSP n. 195 */       "@B258           "                           //"preselection    "
                           "                ",                          //"SUGAR           ",

    /* MSP n.  196 */      "@B259           "                           //"preselection    "
                           "                ",                          //"LONG            ",

    /* MSP n. 197 */       "@B260§\7\x08        "                       //"water           "
                           "                ",                          //"LONG       +\7\x08 %",
        #ifdef DAL_HAPPY_HOUR
    /* MSP n. 198 */       "@B261§\5\6\7\x08      "                     //"number of selec."
                           "                ",                          //"Bingo       \5\6\7\x08",

    /* MSP n. 199 */       "@B262§\x08         "                        //"price with card "
                           "                ",                          //"1=price happy  \x08",
        #else
            #ifdef COMPILO_DATI_STANDARD
    /* MSP n. 198 */       "@B263§\0\1\2\3\4\5\6\7  "                   //"push <PROG> to  "
                           "                ",                          //"load:   \0\1\2\3\4\5\6\7",
            #else
    /* MSP n. 198 */       "@B264§\x08         "                        //"Default sugar   "
                           "                ",                          //"LED:0-5       =\x08",
            #endif
    /* MSP n. 199 */       "@B265           "							//"not used        "
                           "                ",                          //"               \x08",
        #endif
    /* MSP n. 200*/        "@B266§\6\7§\x08      "                      //"A3 Pump OFF time"
                           "                ",                          //"         \6\7.\x08[s]",

    /* MSP n. 201*/        "@B267§\7\x08        "                       //"A5 pressure     " 
                           "                ",                          //"number        \7\x08",

    /* MSP n. 202*/        "@B268           "                           //"PROGRAMMING-----"
                           "                ",                          //"-MDB USD--------",
        #ifdef TRE_USD
    /* MSP n.  203*/       "@B269§\x0F         "                        //"PROGR. MDB USD \x0F"
                           "                ",                          //"  SEL. 4        ",
        #else
    /* MSP n.  203*/       "@B270           "                           //"PROGR. MDB USD  "
                           "                ",                          //"  SEL. 4        ",
       #endif

    /* MSP n.  204 */      "@B271§\x0A\x0B§\3\4\5\6\7\x08 "             //"Calibr. motor \x0A\x0B"
                           "                ",                          //"gr/sec    \3\4\5\6\7\x08",

    /* MSP n. 205 */       "@B272§\x0A\x0B§\0\1\2\3\4\5\6"               //"product \x0A\x0B used "
                           "\7\x08              ",                     //"part.g.\0\1\2\3\4\5\6\7\x08",

    /* MSP n. 206 */       "@B273§\x0A\x0B§\0\1\2\3\4\5\6"               //"product \x0A\x0B used "
                           "\7\x08              ",                     //"Tot. g.\0\1\2\3\4\5\6\7\x08",

    /* MSP n. 207 */       "@B274           "                           //"CALIBRATION-----"
                           "                ",                          //"PRODUCT FLUX    ",

    /* MSP n. 208 */       "@B275           "                           //"PRODUCT AUDIT---"
                           "                ",                          //"------FLUX----- ",

    /* MSP n.  209 */      "@B276           "                           //"   TEST MOTOR   "
                           "                ",                          //"Absorption  sel4",
    #ifdef MODELLO_ESPRESSO
    /* MSP n. 210 */       "@B277§\x09\x0A§\4§\6\7\x08  "               //"tun. grinder  \x09\x0A"  // sull ´espresso  non c´e´
                           "                ",                          //"         \4 \6\7\x08 %",
    #endif
    #ifdef MODELLO_SOLUBILE
    /* MSP n. 210 */       "@B278           "                           //"not used        "
                           "                ",                          //"                ",
    #endif
    #ifdef ABILITO_RESET_DECONTATORE_FILTRO
    /* MSP n. 211 */       "@B279§\x08         "                        //"activ.H2o filter"//Frei
                           "                ",                          //"Reset  0=no    \x08",
    #else
    /* MSP n. 211 */       "@B280           "                           //"not used        "
                           "                ",                          //"                ",
    #endif
    /* MSP n.  212 */      "@B281§\6\7\x08       "                      //"A6 water after  " 
                           "                ",                          //"coffee   \6\7\x08[ml]",

    #ifdef CUSTOMER_NESTLE
    /* MSP n.  213 */      "@B282§\6\7\x08       "                      //"A7 chamber      "
                           "                ",                          //"aperture    \6\7\x08%",                       
    #else
    /* MSP n.  213 */      "@B303§\6\7\x08       "                      //"A7 chamber      "
                           "                ",                          //"aperture    \6\7\x08%",                      
    #endif	

    /* MSP n.  214 */      "@B283§\x08         "                        //"DA rotation     "  // "first install.  " //spostato in user 105
                           "                ",                          //"0=auto 1=man.  \x08", //"starts automat. ",

    /* MSP n.  215 */      "@B284§\6\7\x08       "           			//"Set preheating  "                //"                "  spostato in user 107
                           "                ",         					//"selection \6\7\x08   ",                 //"autom. reset    ",

    /* MSP n.  216 */      "@B285§\x08         "                           //"                "   //messaggio vuoto st030310
                           "                ",                          //"                ",  

    #ifdef VARIGRIND_PRESENCE
    /* MSP n. 217 */       "@B286§\0\1\2\3\4\5\6\7\x08\x09"                //"granulometry    "  // sull ´espresso  non c´e´
                           "\x0A\x0B\x0C\x0D\x0E\x0F          ",     //"\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F", 
    #else 
    /* MSP n. 217 */       "@B287           "                           //"not used        "
                           "                ",                          //"                ",
    #endif 
    /* MSP n.  218 */      "@B288§\x08         "                        //"pricehold query "
                           "                ",                          //"no=0 yes=1     \x08",

    /* MSP n.  219 */      "@B289§\x08         "                  		//"Side water pump "
                           "                ",                  		//" 0-4           \x08",
    #ifdef ENABLE_BREWER_VARIFLEX
    /* MSP n.  220*/       "@B290§\7\x08        "                       //"Brewer pressure "
                           "                ",                          //"0=max 10=min. \7\x08",
    #else
    /* MSP n. 220*/        "@B291§\x08         "                        //"Double coffee   "
                           "                ",                          //"0=no 1=yes     \x08",
    #endif
    #ifdef ABILITA_PRESENZA_VASCHETTA
    /* MSP n. 221 */       "@B292§\x08         "                        //"driptray        "
                           "                ",                          //"identif. yes=1-\x08",
    #else
    /* MSP n.  221 */      "@B293           "                           //"not used        "
                           "                ",                          //"                ",
    #endif
    #ifdef PROGRAMMABLE_PRESEL_MSG
    /* MSP n.  222*/       "@B294§\0\1\2\3\4\5\6\7  "                   //"Preselection    "
                           "                ",                          //"name:   \0\1\2\3\4\5\6\7",
    #else
    /* MSP n.  222 */      "@B295           "                           //"not used        "
                           "                ",                          //"                ",
    #endif

    /* MSP n.  223 */      "@B296§\x08         "                        //"Cup size        "
                           "                ",							//"               \x08",

    /* MSP n.  224 */      "@B297§\6\7\x08       "                       //"vend payment    " // messaggio libero/utilizzabile
                           "                ",                          //"timeout  \7\x08 sec.",                        
    #ifdef ABIL_CAPPUCCINATORE
    /* MSP n. 225 */       "@B298§\6\7§\x08      "                      //"ev fresh milk   "
                           "                ",                          //"delay       \6\7.\x08",

    /* MSP n. 226 */       "@B299§\6\7§\x08      "                      //"ev air fresh    "
                           "                ",                          //"milk delay  \6\7.\x08",                      
    #else
    /* MSP n.  225 */      "@B300           "                           //"   not  used    "
                           "                ",                          //"                ",

    /* MSP n.  226 */      "@B301           "                           //"   not  used    "
                           "                ",                          //"                ",
    #endif

    /* MSP n.  227*/       "@B302§^         "                           //"PROGRAMMING ----"
                           "                ",                          //"  VARIGRIND ^   ",

    /* MSP n.  228*/       "@B304           "                           //"PROGRAMMING ----"
                           "                ",                          //"- MILKER    ----",
    #ifdef MODELLO_DOPPIO
    #ifdef DISABILITA_BICC   
    /* MSP n. 229 */       "@B305§\x08         "                        //"dispensing cup  "
                           "                ",                          //"0=yes 1=no     \x08",  
    #else
    /* MSP n. 229 */       "@B306           "                           //"   not  used    "
                           "                ",                          //"                ",
    #endif
    #else
    /* MSP n. 229 */       "@B307           "                           //"   not  used    "
                           "                ",                          //"                ",
    #endif
    /* MSP n.230  */   	   "@B308           "                           //"PROGRAMMING ----"
                           "                ",                          //"  VARIGRIND 2   ",

    /* MSP n.231  */   	   "@B309§^§)§\4\5\6\7\x08 "                    //"PRESEL. NUM ^)  "
                           "                ",                          //"           \4\5\6\7\x08",

    /* MSP n.232  */   	   "@B310§\0\1\2\3\4\5\6\7\x08\x09"                //"Verified data   "
                           "\x0A\x0B\x0C\x0D\x0E\x0F          ",           //"\0\1\2\3\4\5\6\7\x08\x09\x0A\x0B\x0C\x0D\x0E\x0F",         // 	"         <4>=yes",

    /* MSP n.  233 */      "@B311§\x08         "                        //"Water Flush mode"  // messaggio libero/utilizzabile
                           "                ",                          //"1=ON 0=OFF \x08 ",

    /* MSP n.  234 */      "@B312           "                           //"available       "  // messaggio libero/utilizzabile
                           "                ",                          //"                ",

    /* MSP n.  235 */      "@B313           "                           //"xxxxxxx         " // messaggio libero/utilizzabile
                           "                ",                          //"                ",

    /* MSP n.  236 */      "@B314           "                           //"PROGRAMMING ----"
                           "                ",                          //"RFID BLACK LIST ",

    /* MSP n.  237 */      "@B315§\x09\x0A§\5\6\7\x08   "               //"block card \x09\x0A   "
                           "                ",                          //"number      \5\6\7\x08",
    #ifdef  MODELLO_DOPPIO
    /* MSP n. 238*/        "@B316           "                           //"TEST CUP STATION"
                           "                ",                          //"sel 4           ",
    #else
    /* MSP n. 238 */       "@B317           "                           //"not used        "
                           "                ",                          //"                ",
    #endif

#if defined ENABLE_BREWER_VARIFLEX
    /* MSP n. 239 */       "@B318           "                           //"PROGRAMMING ----"
                           "                ",                          //"   VARIFLEX     ",
#elif defined ABIL_GRUPPO_MICRO
    /* MSP n. 239 */       "@B319           "                           //"PROGRAMMING ----"
                           "                ",                          //"   MICRO        ",
#else
    /* MSP n. 239 */       "@B320           "                           //"PROGRAMMING ----"
                           "                ",                          //"                ",
#endif

    /* MSP n. 240 */       "@B321§\6\7\x08\x09      "                      //"   TEMPERATURE  "
                           "                ",                          //"Temp. EV4    \6\7\x08",

    /* MSP n. 241 */       "@B322           "							//"Preselection    " 
                           "                ",                          //"SELECTIONS 49-60",

    /* MSP n. 242 */       "@B324           "							//"xxxxxxx         " // messaggio libero/utilizzabile
                           "                ",                          //"                ",

#ifdef CAPPUCCINATORE_INDUX
    /* MSP n. 243 */       "@B325           "						    //"not used        " //"Time cleaning   "
                           "                ",							//"                ",//"rhMM1.v+  \5\6:\7\x08 ",   // nome commerciale MILK module
#else
    /* MSP n. 243 */       "@B326§\5\6§\7\x08     "                     //"Time cleaning   "
                           "                ",                          //"MILK Mod.  \5\6:\7\x08",
#endif 

    /* MSP n. 244*/        "@B327§\x08         "                        //"F.Milk  Topping-"
                           "                ",                          //"switch  yes=1- \x08",

    /* MSP n. 245*/        "@B328§\5\6\7\x08      "                     //"Calibrate Cof  2"            	         
                           "                ",                          //"Push PROG   \5\6\7\x08",

    /* MSP n. 246*/        "@B329§\6\7\x08§\x0A\x0B\x0C   "             //"cup sens.thresh."            	         
                           "                ",                          //"0=dis  \6\7\x08 - \x0A\x0B\x0C",

    /* MSP n. 247*/        "@B330§\5\6\7\x08      "                     //"  Set Free Vend "            	         
                           "                ",                          //"Ins hours   \5\6\7\x08",

    /* MSP n. 248*/        "@B331§\x08         "                        //"Enable dataaudit"
                           "                ",                          //"before  1=yes  \x08",

    /* MSP n. 249 */       "@B332§\4§\6\7\x08     "                     //"Scaling   Factor"
                           "                ",                          //"          \4 \6\7\x08 %",

    /* MSP n. 250 */       "@B333           "                           //"TEST STIRRER    "
                           "                ",                          //"sel 4           ",

    /* MSP n. 251 */       "@B334§\x08         "                        //" Security Level "
                           "                ",                          //"level 1-4      \x08",

    /* MSP n. 252 */       "@B335§\5\6\7\x08      "         			//"Calibrate Cof  3"
                           "                ",                      	//"Push PROG   \5\6\7\x08",

    /* MSP n. 253 */       "@B336§\5\6\7\x08      "                     //"Calibrate Cof  4"
                           "                ",                          //"Push PROG   \5\6\7\x08",

    /* MSP n. 254 */       "@B337§\x08         "                        //"coffee repeat	  "
                           "                ",                          //"0=disabled     \x08",

    /* MSP n. 255 */        "@B338§\0\1\2\3\4\5\6\7\x08\x09"
                            "\x0A\x0B\x0C\x0D\x0E\x0F          ",
};

const u8 __far ML_MS_NOME_SELEZ_1[MAX_NOME_SELEZ][16] = {
#ifdef CUSTOMER_NESTLE
    /* 00 */          "@C001           ",                                //"standard        ",
    /* 01 */          "@C002           ",                                //"Ristretto       ",
    /* 02 */          "@C003           ",                                //"Espresso        ",
    /* 03 */          "@C004           ",                                //"Double Espresso ",
    /* 04 */          "@C005           ",                                //"Americano       ",
    /* 05 */          "@C006           ",                                //"Lungo           ",
    /* 06 */          "@C007           ",                                //"Babyccino       ",
    /* 07 */          "@C008           ",                                //"Hot Chocolate   ",
    /* 08 */          "@C009           ",                                //"Mochaccino      ",
    /* 19 */          "@C010           ",                                //"Flat White      ",
    /* 10 */          "@C011           ",                                //"Latte Macchiato ",
    /* 11 */          "@C012           ",                                //"Cappuccino      ",
    /* 12 */          "@C013           ",                                //"Esp. Macchiato  ",
    /* 13 */          "@C014           ",                                //"White Coffee    ",
    /* 14 */          "@C015           ",                                //"Cortado         ",
    /* 15 */          "@C016           ",                                //"Hot Water       ",
    /* 16 */          "@C017           ",                                //"Tea             ",
    /* 17 */          "@C018           ",                                //"Chococcino      ",
    /* 18 */          "@C019           ",                                //"Milk Chocolate  ",
    /* 19 */          "@C020           ",                                //"Dark Chocolate  ",
    /* 20 */          "@C021           ",                                //"custom          ",
    #else
    /* 00 */          "@C022           ",                                //"standard        ",
    /* 01 */          "@C023           ",                                //"Cappuccino      ", 
    /* 02 */          "@C024           ",                                //"Capp-cioc       ",
    /* 03 */          "@C025           ",                                //"Latte Macchiato ",
    /* 04 */          "@C026           ",                                //"Cafe Latte      ",
    /* 05 */          "@C027           ",                                //"Espresso        ",
    /* 06 */          "@C028           ",                                //"Espresso Macch. ",
    /* 07 */          "@C029           ",                                //"MoccaCino       ",
    /* 08 */          "@C030           ",                                //"Chocolate       ",
    /* 09 */          "@C031           ",                                //"Choco-Milk      ",
    /* 10 */          "@C032           ",                                //"Hot Water       ",
    /* 11 */          "@C033           ",                                //"Milk            ",
    /* 12 */          "@C034           ",                                //"Cafe Au Lait    ",
    /* 13 */          "@C035           ",                                //"Instant coffee  ",
    /* 14 */          "@C036           ",                                //"Tea             ",
    /* 15 */          "@C037           ",                                //"Instant white   ",
    /* 16 */          "@C038           ",                                //"Strong choco    ", 
    /* 17 */          "@C039           ",                                //"Barley          ",
    /* 18 */          "@C040           ",                                //"Barley Cappucc. ",
    /* 19 */          "@C041           ",                                //"Cafe Macchiato  ",  
    /* 20 */          "@C042           ",                                //"custom          ",  
    #endif
};

#ifdef EASY_PRESEL
//	nomi preselezioni estesi a 16 caratteri
const u8 __far ML_MS_NOME_PRESEL_1[MAX_NOME_PRESEL][16] = {
    /* 01 */      	  "@D001           ",                                //"SELECTIONS 25-36",
    /* 02 */          "@D002           ",                                //"BARLEY          ",          
    /* 03 */          "@D003           ",                                //"NO CUP          ",   
    /* 04 */          "@D004           ",                                //"EXTRA MILK      ",            
    /* 05 */          "@D005           ",                                //"ESPRESSO        ",          
    /* 06 */          "@D006           ",                                //"NO SUGAR        ",
    /* 07 */          "@D007           ",                                //"EXTRA SUGAR     ",         
    /* 08 */          "@D008           ",                                //"WITH CUP        ",         
    /* 09 */          "@D009           ",                                //"SUGAR 1         ",  
    /* 10 */          "@D010           ",                                //"MORE SUGAR      ",  
    /* 11 */          "@D011           ",                                //"SELECTIONS 37-48",
    /* 12 */          "@D012           ",                                //"LONG            ",  
    /* 13 */          "@D013           ",                                //"JUG             ",
    /* 14 */          "@D028           ",                                //"SELECTIONS 49-60"
};
#else

const u8 __far ML_MS_NOME_PRESEL_1[13][7] = { //@FT controllare l'excel per il multilingua perchè si e' disallineato
    /* 01 */      	  "@D014  ",                                //"DECAF. ",//st- presel per + 10 selezioni dirette  (sel 11-20) ( presel Nr 0 - mes 162 ) / ( presel 0 + 7 = sel 31-40 )  servomat     
    /* 02 */          "@D015  ",                                //"BARLEY ",          
    /* 03 */          "@D016  ",                                //"NO CUP ",         
    /* 04 */          "@D017  ",                                //"EX-MIL.",            
    /* 05 */          "@D018  ",                                //"ESPRES.",          
    /* 06 */          "@D019  ",                                //"NO SUG.",
    /* 07 */          "@D020  ",                                //"EX SUG.",         
    /* 08 */          "@D021  ",                                //"CUP    ",         
    /* 09 */          "@D022  ",                                //"SUGAR 1",
    /* 10 */          "@D023  ",                                //"SUG.++ ",  
            #ifdef COMP_PREZZO_ECO_BIC
    /* 11 */          "@D024  ",                                //"BIG CUP",//st- presel per + 10 selezioni dirette  (sel 21-30) ( presel Nr 7 - mes 188 ) / ( presel 0 + 7 = sel 31-40 )  
            #else
    /* 11 */          "@D025  ",                                //"       ",         
            #endif
    /* 12 */          "@D026  ",                                //"LONG   ",  
    /* 13 */          "@D027  ",                                //"JUG    ",//st- presel caraffa usata anche per la KP    
};
#endif

const u8 __far ML_MSAP_PAR_MAINTENANCE[MAX_PAR_MAINTENANCE][32] = {
    /* n. 0 */       	"@E001§\x0A\x0B\x0C\x0D\x0E§\4\5\6\7"			//"water filter cnt"  // ex 129 MSP
                        "\x08               ",							//"[\x0A\x0B\x0C\x0D\x0E]    \4\5\6\7\x08",
    #ifdef MODELLO_ESPRESSO
    /* n. 1 */    		"@E002§\x0A\x0B\x0C\x0D\x0E§\4\5\6\7"			//"dec. cof. brewer"  // ex 130 MSP
                        "\x08               ",							//"[\x0A\x0B\x0C\x0D\x0E]    \4\5\6\7\x08",

    /* n. 2 */    		"@E003§\x0A\x0B\x0C\x0D\x0E§\4\5\6\7"			//"dec. cof.grounds"  // ex 131 MSP
                        "\x08               ",							//"[\x0A\x0B\x0C\x0D\x0E]    \4\5\6\7\x08",
    #else 
    /* n. 1 */    		"@E004           "								//"not used        "  // ex 130 MSP
                        "                ",								//"                ",

    /* n. 2 */    		"@E005           "								//"not used        "  // ex 131 MSP
                        "                ",								//"                ",
    #endif  

    /* n. 3 */        	"@E006§\x0A\x0B\x0C\x0D\x0E§\4\5\6\7"			//"Blocking counter"  // ex 252 MSP
                        "\x08               ",							//"[\x0A\x0B\x0C\x0D\x0E]    \4\5\6\7\x08",

    /* n. 4 */        	"@E007§\7\x08        "			//"Perc. threshold "  // ex 253 MSP
                        "                ",							//"0=disabled    \7\x08",

    /* n. 5 */        	"@E008§\6\7\x08       "							//"insert code     "  // ex 1 MSP
                        "                ",								//"             \6\7\x08",

    /* n. 6 */        	"@E009§\x09\x0A\x0B\x0C\x0D\x0E§\4\5\6"			//"Mainten. counter"  // ex 252 MSP
                        "\7\x08              ",							//"[\x09\x0A\x0B\x0C\x0D\x0E]  \4\5\6\7\x08\x30",

    /* n. 7 */        	"@E010§\4\5\6\7\x08     "						//"Maint. threshold"  // ex 252 MSP
                        "                ",								//"          \4\5\6\7\x08\x30",

};

#ifdef PROGRAMMABLE_PRESEL_MSG
const u8 __far ML_MS_PROG_NOME_PRESEL[MAX_PROG_NOME_PRESEL][8] = {
    /* 00 */          "@F001   ",                                //"standard",
    /* 01 */          "@F002   ",                                //"DECAF   ",
    /* 02 */          "@F003   ",                                //"LACTOSE ",
    /* 03 */          "@F004   ",                                //"MILK    ",
    /* 04 */          "@F005   ",                                //"SUGAR   ",
    /* 05 */          "@F006   ",                                //"F.MILK  ",
    /* 06 */          "@F007   ",                                //"COFFEE  ",
    /* 07 */          "@F008   ",                                //"COFFEE 2",
    /* 08 */          "@F009   ",                                //"VANILLA ",
    /* 09 */          "@F010   ",                                //"custom  ",
};
#endif 

const u8 __far ML_MS_TIPO_SCHIUMA[MAX_TIPO_SCHIUMA][16] = {

    /* 00 */          "@O001           ",						 //"Hot no Foam     ",
    /* 01 */          "@O002           ",						 //"Hot Classic Foam",
    /* 02 */          "@O003           ",						 //"Hot Fluffy  Foam",
    /* 03 */          "@O004           ",						 //"Hot Barista Foam",

    /* 04 */          "@O005           ",						 //"Cold no Foam    ",
    /* 05 */          "@O006           ",						 //"Cold Classic Fo.",
    /* 06 */          "@O007           ",						 //"Cold Fluffy Foam",
    /* 07 */          "@O008           ",						 //"Cold Barista Fo.",

};

const u8 __far ML_MS_TIPO_FLUSSO_1[MAX_TIPO_FLUSSO][8] = {

    /* 01 */          "@G001   ",                                //"     low",
    /* 02 */          "@G002   ",                                //"  medium",
    /* 03 */          "@G003   ",                                // "    high",
};

const u8 __far ML_MS_NOME_GIORNO_1[MAX_NOME_GIORNO][5] = {

    /* 01 */          "@H001",                                //"Monda",
    /* 02 */          "@H002",                                //"Tuesd",
    /* 03 */          "@H003",                                //"Wedne",
    /* 04 */          "@H004",                                //"Thurs",
    /* 05 */          "@H005",                                //"Frida",
    /* 06 */          "@H006",                                //"Satur",
    /* 07 */          "@H007",                                //"Sunda",
};

const u8 __far ML_MS_SI_1[5] = {
                  "@I001",                                //"YES",
};
const u8 __far ML_MS_NO_1[5] = {
                  "@L001",                                //" NO",
};

//............... lavaggio sanitario .............

const u8 __far  ML_MSG_LAV_GRUPPO[MAX_LAV_GRUPPO][32] = {

    /* MSA n. 00 */   "@M001           "                                 //"xxxxxxx         "
                      "                ",                                //"                "

#if !defined(MODELLO_BONA) || defined(MODELLO_DOPPIO)
    /* MSA n. 1  */   "@M002           "                                 //"2/16 Put tablet "      //put pastille    
                      "                ",                                //" push Start=10  ",     //and push  P8   

    /* MSA n. 2  */   "@M003§\3§\4§\0§\1\2  "                            //"\3/16 tab. diss.\4"       //P3 to continue  
                      "                ",                                //"wait    min \0:\1\2",//rinsing     //"3=weiter    \0:\1\2",//rinsing    (la tassini non vuole 3=weiter)
#else
    /* MSA n. 1  */   "@M004           "                                 //"Put pastille and"      //put pastille    
                      "                ",                                //"push   P10=START",     //and push  P8   

    /* MSA n. 2  */   "@M005§\0§\1\2      "                              //"tab dissolve    "       //P3 to continue  
                      "                ",                                //"    min  \0:\1\2   ",//rinsing     //"3=weiter    \0:\1\2",//rinsing    (la tassini non vuole 3=weiter)
#endif 

    /* MSA n. 3  */   "@M006§\2\3\4       "                              //"Cleaning brewer "      //cleaning        
                      "                ",                                //"6 X          \2\3\4",

    /* MSA n. 4  */   "@M007           "                                 //"wait please     "      // wait  please   
                      "                ",                                //"                ",

#ifdef ENABLE_BREWER_VARIFLEX
#ifndef MODELLO_TS
    /* MSA n. 5  */   "@M043           "                                 //"Proc.Type: 8=MAN"
                      "                ",                                //"9=A.Skip AUTO=10",
#else 
    /* MSA n. 5  */   "@M044           "                                 //"xxxxxxx         "
                      "                ",                                //"                "
#endif 
#else 
    /* MSA n. 5  */   "@M008           "                                 //"xxxxxxx         "
                      "                ",                                //"                "
#endif 

#if !defined(MODELLO_BONA) || defined(MODELLO_DOPPIO)
    /* MSA n. 6  */   "@M009           "     							 //"1/16 Cleaning   "      //Inizio Lavaggio 
                      "                ",     							 //" Active         ",
#else
    /* MSA n. 6  */   "@M010           "                                 //"Cleaning        "      //Inizio Lavaggio 
                      "                ",                                //" Active         ",
#endif
    /* MSA n. 7  */   "@M011           "                                 //"                "      //clear screen 
                      "                ",                                //"                ",

    /* MSA n. 8  */   "@M012           "                                 //"13/16 Skip final" 	//richiesta per il caffè di pulizia al termine del lavaggio sanitario
                      "                ",                                // "coffee YES=1    ",

    /* MSA n. 9  */   "@M013§\4\5§\x08      "							 //"\4\5/16 Rep. clean"
                      "                ", 								 //"\x08/2 YES=10 NO=ot",

    /* MSA n. 10  */  "@M014           "								//"10/16 Man. brush"
                      "                ",								//"  and push 10   ",

    /* MSA n. 11  */  "@M015           "      							//"3/16 Brewer is  "
                      "                ",								//"     closing    ",

    /* MSA n. 12  */  "@M016           "      							//"5/16 2nd diss.  "
                      "                ",			     				//cycle will start",

    /* MSA n. 13  */  "@M017§\4\5§\0\1\2§\x09\x0A\x0B"	     	 		//"\4\5/16 \0\1\2 Clean."
                      "                ",      							//"   active \x09\x0A\x0B   ",

    /* MSA n. 14  */  "@M018           "	      						//"9/16  Brewer in "
                      "                ",      							//" open position  ",

    /* MSA n. 15  */  "@M019           "      							//"16/16 Brew. Cle."
                      "                ",      							//"Done.    10=Exit",

    /* MSA n. 16  */  "@M020§\4\5\6\7\x08§\0   "      					//"\4\5\6\7\x08 Mixer \0   "
                      "                ",     							//"rinsing         ",

    /* MSA n. 17  */  "@M021§\4\5\6\7\x08     "      					//"\4\5\6\7\x08 Brewer    "
                      "                ",     							//"Rinsing         ",

    /* MSA n. 18  */  "@M022           "      							//"Start procedure?"
                      "                ",      							//"   YES=10 NO=8  ",

    /* MSA n. 19  */  "@M023§\4\5§\0\1\2    "     						//"\4\5/16 \0\1\2 Clean."
                      "                ",     							//"   wait please  ",

    /* MSA n. 20  */  "@M024           "     							//"14/16 Coffee    "
                      "                ",     							//"delivery        ",

    /* MSA n. 21  */  "@M025§\1§\2\3      "     						//"\1/\2\3 emptying   "
                      "                ",     							//"in progress     ",

    /* MSA n. 22  */  "@M026§\1§\2\3      "     						//"\1/\2\3 conn. desc."
                      "                ",     							//"solution   OK=10",

    /* MSA n. 23  */  "@M027§\1§\2\3      "     						//"\1/\2\3 fill. desc."
                      "                ",     							//"sol. in progress",

    /* MSA n. 24  */  "@M028§\0\1§\2\3     "     						//"\0\1/\2\3 water     " 
                      "                ",     							//"flows?    YES=10",

    /* MSA n. 25  */  "@M029§\0\1§\2\3     "     						//"\0\1/\2\3  descaling"
                      "                ",     							//"solution filling",

    /* MSA n. 26  */  "@M030§\1§\2\3§\4§\5\6 "     						//"\1/\2\3  solution  "
                      "                ",     							//"action=>min \4:\5\6",

    /* MSA n. 27  */  "@M031§\0\1§\2\3§\4§\5 "     						//"\0\1/\2\3 desc. sol."
                      "                ",     							//"draining \4/\5    ",

    /* MSA n. 28  */  "@M032§\0\1§\2\3     "     						//"\0\1/\2\3 result?   "
                      "                ",     							//"OK=10   NO=OTHER",

    /* MSA n. 29  */  "@M033§\0\1§\2\3     "     						//"\0\1/\2\3 connect   "
                      "                ",     							//"water      OK=10",

    /* MSA n. 30  */  "@M034§\0\1§\2\3     "     						//"\0\1/\2\3 filling   "
                      "                ",     							//"water in progr. ",

    /* MSA n. 31  */  "@M035§\0\1§\2\3     "     						//"\0\1/\2\3 rinsing   "
                      "                ",     							//"with water      ",

    /* MSA n. 32  */  "@M036§\0\1§\2\3     "     						//"\0\1/\2\3 disp. and " 
                      "                ",     							//"test water  Y=10",

    /* MSA n. 33  */  "@M037§\0\1§\2\3     "     						//"\0\1/\2\3 catch     "
                      "                ",     							//"water to test   ",

    /* MSA n. 34  */  "@M038§\0\1§\2\3     "     						//"\0\1/\2\3 descaling "
                      "                ",     							//"done. EXIT=10   ",

    /* MSA n. 35  */  "@M039§\0\1§\2\3     "     						//"\0\1/\2\3 open      "
                      "                ",     							//"boiler tap Y=10 ",

    /* MSA n. 36  */  "@M040§\0\1§\2\3     "     						//"\0\1/\2\3 close     "
                      "                ",     							//"boiler tap Y=10 ",

    /* MSA n. 37 */   "@M041           "   								//"  auto rinsing  "
                      "                ",     							//"   in progress  ",

    /* MSA n. 38 */   "@M042§\0         "   								//" Periodic rinse "
                      "                ",     							//"  in \0 seconds  "
};

#ifdef AGGIUNTA_MESSAGGI_OFF
const u8 __far ML_MES_ERRORI_AGGIUNTI[MAX_MES_ERRORI_AGGIUNTI][32] = {

    /*  n. 0   */      "@N001           "                                 //"                "
                       "                ",                                //"                ",
     #ifdef CUSTOMER_NESTLE
    /*  n. 1   */      "@N002           "                                 //"           drain"  " Veuillez vider "  //OFF 3  = 
                       "                ",                                //"drip tray       ", "bac récupération",
    /*  n. 2   */      "@N003           "                                 //"  out of service"  "    Hors Service" //OFF 6a / 6b  = 
                       "                ",                                //"NO WATER        ", "pas d'eau       ", 
    /*  n. 3   */      "@N004           "                                 //" Water flow too "  "Débit d'eau trop" //OFF 7  = 
                       "                ",                                //"low in H.circuit", "faible circuit.H",
    /*  n. 4   */      "@N005           "                                 //"           CHECK"	"       CONTRÔLER" //OFF 8 / 8b = 
                       "                ",                                //"BREWER          ",	"BREWER          ", 											
    /*  n. 5   */      "@N006           "                                 //" REFILL COFFEE  "  "REMPLIR LE CAFÉ " //OFF 9a / 9d  = 
                       "                ",                                //"                ", "                ",
   #else
    /*  n. 1   */      "@N007           "                                 //"           drain"  "Vider le bac des"   //OFF 3  =   
                       "                ",                                //"drip tray       ", "eaux usées      ",
    /*  n. 2   */      "@N008           "                                 //"  out of service"  "  Hors Service  "
                       "                ",                                //"NO WATER        ", "manque d'eau    ", 
    /*  n. 3   */      "@N009           "                                 //" Water flow too "  "Infusion trop   "   //OFF 7  =  
                       "                ",                                //"low in H.circuit", "longue          ",
    /*  n. 4   */      "@N010           "                                 //"           CHECK"	"   Contrôler le "	 //OFF 8 / 8b =  
                       "                ",                                //"BREWER          ",	"groupe à café   ",											
    /*  n. 5   */      "@N011           "                                 //" REFILL COFFEE  "  "Contrôler bac   "  
                       "                ",                                //"                ", "café et moulin  ",
  #endif
    /*  n. 6   */      "@N012           "                                 //"                "
                       "                ",                                //"                ",
};

#endif 

#ifdef PROG_PAR_GRUPPO_ESPRESSO
const u8 __far  ML_MSAP_ParGrEspresso[MAX_ParGrEspresso][32] = {

#ifdef ENABLE_BREWER_VARIFLEX
    /* MSA n. 1  */    "@P001§\6\7\x08       "                            //"BREWER SIZE     "  			
                       "                ",                                //"0=36   1=45  \6\7\x08",		
#else
    /* MSA n. 1  */    "@P002§\6\7\x08       "                            //"BREWER SIZE     "  				//"BREWER DIAMETER "
                       "                ",                                //"0=36   1=40  \6\7\x08",
#endif 
    /* MSA n. 2 */     "@P003§\7\x08        "                             //"BREWER POSITION "
                       "                ",                                //"0=CLOSE 1=OP. \7\x08",
#ifdef ENABLE_BREWER_VARIFLEX
    /* MSA n. 3  */    "@P004§\x08         "                              //"AUTOM.ADJUSTMENT" 
                       "                ",                                //"F.TUNING  1=yes\x08", 
    /* MSA n. 4  */    "@P005§\6§\7\x08      "                            //"    ENCODER     "
                       "                ",								  //"IMPULSE/GR. \6.\7\x08",
#else
    /* MSA n. 3  */    "@P006§\6\7\x08       "                              //"  OFF9  Grinder "
                       "                ",                                //"  Speed \6\7\x08     ",
    /* MSA n. 4  */    "@P007           "                            //"    NOT USED    "
                        "                ",    							  //"                ",
#endif 
    /* MSA n. 5  */    "@P008§\6\7\x08       "                            //"  TAB DISSOLVE  "          		//st tempo scioglimento pastiglia  provvisorio
                       "                ",                                //"PAUSE  SEC.  \6\7\x08",
    /* MSA n. 6  */    "@P009§\6§\7\x08      "                            //"ENCODER  GRIND 2"          		//"imp. per grammo "
                       "                ",                                //"IMPULSE/GR. \6.\7\x08", 		//"#3.75#      \6.\7\x08",
    /* MSA n. 7  */    "@P010§\x08         "                              //"GRINDER FUNCTION"          		//Modalità funzionamento macina:
                       "                ",                                //"IM EN/GR 1=yes \x08", 			//0--> GR/SEC 1--> IMP/GR
    /* MSA n. 8  */    "@P011           "                                 //"    NOT USED    "          		//Non usato
                       "                ",                                //"                ",
    /* MSA n. 9  */    "@P012§\x08         "                              //"GRIND 2 FUNCTION"          		//Modalità funzionamento seconda macina:
                       "                ",                                //"IM EN/GR 1=yes \x08", 			//0--> GR/SEC 1--> IMP/GR
#ifdef ENABLE_BREWER_VARIFLEX
    /* MSA n. 10 */    "@P013§\x08         "                              //"DELIVERY   PHASE"          		//Anticipa fine erogazione:
                       "                ",                                //"FASTER   1=yes \x08", 			//0--> NO 1--> SI
#else /* gruppo micro */
    /* MSA n. 10  */   "@P014           "          						  //Non usato
                       "                ",
#endif // ENABLE_BREWER_VARIFLEX
    /* MSA n. 11  */   "@P015§\6§\7\x08      "							  //"ENCODER  GRIND 3"       
                       "                ",   							  //"IMPULSE/GR. \6.\7\x08",
    /* MSA n. 12  */   "@P016§\x08         "							  //"GRIND 3 FUNCTION"
                       "                ",								  //"IM EN/GR 1=yes \x08",
    /* MSA n. 13  */   "@P017§\6§\7\x08      "							  //"ENCODER  GRIND 4"
                       "                ",							  	  //"IMPULSE/GR. \6.\7\x08",
    /* MSA n. 14  */   "@P018§\x08         "							  //"GRIND 4 FUNCTION"
                       "                ",							  	  //"IM EN/GR 1=yes \x08",
    /* MSA n. 15  */   "@P019§\x08         "							  //"RESET GROUP IN  "
                       "                ",							  	  //"ERROR    1=yes \x08",
    /* MSA n. 16  */   "@P020§\7\x08        "							  //"RINSE AFTER DOWN" 
                       "                ",							  	  //"TIME 0=NO \7\x08HOUR",
};

#endif

#ifdef VARIGRIND_PRESENCE

const u8 __far  ML_MSAP_PAR_MACINA_MOT[MAX_PAR_MACINA_MOT][32] = {

    /* MSP n. 0  */     "@Q001§^§\6\7\x08     "   						//   "p. grinder ^:\6\7\x08"
                        "                ",  							//	 " 4=open  5=close",
    /* MSP n. 1  */     "@Q002§^§\7\x08      "							//   "sel.rif. grind.^"
                        "                ",  							//   "PROG=save     \7\x08",
    /* MSP n. 2  */     "@Q003§^§\x08       "							//   "Habil.reg.gran.^"
                        "                ",  							//   "1=yes 2=test   \x08",
    /* MSP n. 3  */     "@Q004§^§\5\6§\7\x08   "						//   "Referring flux.^"
                        "                ",  							//   "cc/second  \5\6.\7\x08",
    /* MSP n. 4  */     "@Q005§^§\5\6\7\x08    "						//   "number samplings"
                        "                ",  							//   "grinder ^   \5\6\7\x08",
    /* MSP n. 5  */     "@Q006§^§\6\7\x08     "							//   "Referring posit."
                        "                ",
    /* MSP n. 6  */     "@Q007§^§\6\7\x08     "							//   "Referring posit."
                        "                ",
};

const u8 __far ML_MS_TIPO_GRANULOMETRIA[MAX_TIPO_GRANULOMETRIA][16] =			//ezio 11/05/2015
{
                   "@R001           ",                                //"   disabled     ",
                   "@R002           ",                                //"     fine       ",
                   "@R003           ",                                //"    referring   ",
                   "@R004           ",                                //"    roughly     ",

};
#endif 

#ifdef ABIL_CAPPUCCINATORE
#ifndef CAPPUCCINATORE_INDUX	

const u8 __far  ML_MSAP_CAPPUCCINATORE[MAX_CAPPUCCINATORE][32] = {

    /* MSP n. 0 */     "@S001§\6\7\x08       "                            //"   TEMPERATURE  "
                       "                ",                                //"steam        \6\7\x08",

    /* MSP n. 1 */     "@S002§\6\7\x08       "                            //"Rinsing period  "//periodo risciacq
                       "                ",                                //" min.        \6\7\x08",//"minuti       \6\7\x08",

    /* MSP n. 2 */     "@S003§\x08         "                              //"Rinse MILK MOD  "//risciacquo
                       "                ",                                //"   1=enable    \x08",//"1=abil.        \x08",

    /* MSP n. 3 */     "@S004§\6\7§\x08      "                            //"Rinse MILK MOD  "//rit. risciacquo.
                       "                ",                                //"delay  sec:\6\7.\x08 ",//"secondi:   \6\7.\x08",

    /* MSP n. 4 */     "@S005§\x08         "                              //"  Milk Sensor   "         //"rins. fresh milk"//tempo risciacquo
                       "                ",                                //"1=Enable       \x08",     //"time   sec:\6\7.\x08 ",//"secondi:   \6\7.\x08",


    /* MSP n. 5 */      "@S006§\x08         "                             // " Clean User Msg "			// Richiesta Risciaquo Utente durante check iniziale
                        "                ",                               //"1=Enable       \x08",

    /* MSP n. 6 */      "@S007§\4\5§\6\7§\x08\x09§\x0A"                             // "Next Milk Clean "			//Mostra l'ora del prossimo lavaggio
                        "\x0B§\x0C\x0D            ",                               //"\4\5:\6\7 \x08\x09-\x0A\x0B-20\x0C\x0D",

    /* MSP n. 7*/       "@S046§\x08         "                             //" Mlk. Wash Type "
                        "                ",                               // " 0=24h  1=30h  \x08",


};
#else   	
const u8 __far  ML_MSAP_CAPPUCCINATORE[MAX_CAPPUCCINATORE][32] = {

    /* MSP n. 0 */     "@S008§\6\7\x08       "  	//"   TEMPERATURE  "
                       "                ",  	//"steam        \6\7\x08",

    /* MSP n. 1 */     "@S009§\6\7\x08       "  //"HDE delay after "
                       "                ", 		//"drink min.   \6\7\x08",

#ifdef CUSTOMER_NESTLE    
    /* MSP n. 2 */     "@S010           "          //"not used        "
                       "                ",      //"HDE  1=Enable  \x08", 
#else
    /* MSP n. 2 */     "@S045§\x08         "      //2964 //"Cleaning period:"      //"not used        "     //"Hidrody.Emptying" 
                       "                ",      //2964 //"0=24H 1=48-72H \x08", //"                ",    //"HDE  1=Enable  \x08", 
#endif

    /* MSP n. 3 */     "@S011§\x08         "  	//"Fridge Position:"				//#2614 ex "Conducibility   "
                       "                ",  	//"0=SIDE 5=BOTT. \x08",			//#5614 ex "Sensor 1=Enab. \x08",//"Sensor 1=Enab. \x08",

    /* MSP n. 4 */     "@S012§\x08         " 	//"  Check Milk    "
                       "                ",  	//"presence 1=yes \x08",

#ifdef MODELLO_TS
    /* MSP n. 5 */     "@S048§\x08         "    //" Clean Msg Start"
                       "                ",      //"1=Enable       \x08"
#else

    /* MSP n. 5 */     "@S013           "  		//"not used        "     //" Rinse User Msg "			// Richiesta Risciaquo Utente durante check iniziale
                       "                ",  	//"                ",    //"1=Enable       \x08", 
#endif

    /* MSP n. 6 */     "@S014§\x08         "  	//"Ignore tank sens"	 //"not used        " //"Clean TimeUpdate"			//Aggiornamento automatico dell'ora per il lavaggio
                       "                ",     	//"clean/hde      \x08", //"                ",//"1=Enable       \x08",		//"1=abil.        \x08",

    /* MSP n. 7 */     "@S015§\x08         " 	//"Check Waste tank"
                       "                ",  	//"1=Enable       \x08",

    /* MSP n. 8 */     "@S016§\6\7\x08       "  //"Hot Classic Foam"
                       "                ",  	//"air        \6\7\x08 %",

    /* MSP n. 9 */     "@S017§\6\7\x08       "  //"Hot Classic Foam"
                       "                ",  	//"sped pump  \6\7\x08 %",

        #ifdef ABIL_SENSORE_PRESSIONE							 
    /* MSP n. 10 */   "@S018§\6§\7\x08      "   //"Hot Classic Foam"
                       "                ",  	//"pres. 0=dis.\6.\7\x08",
        #else
    /* MSP n. 10 */    "@S019           "  		//"not used        "
                       "                ",  	//"                ",
        #endif		

    /* MSP n.11 */     "@S020§\6\7\x08       "  //"Hot Fluffy Foam "
                       "                ",  	//"air        \6\7\x08 %",

    /* MSP n.12 */     "@S021§\6\7\x08       "  //"Hot Fluffy Foam "
                       "                ",  	//"sped pump  \6\7\x08 %",

        #ifdef ABIL_SENSORE_PRESSIONE							 
    /* MSP n.13 */     "@S022§\6§\7\x08      "  //"Hot Fluffy Foam "
                       "                ",  	//"pres. 0=dis.\6.\7\x08",
        #else
    /* MSP n.13 */     "@S023           " 		//"not used        "
                       "                ",  	//"                ",
        #endif		
    /* MSP n.14 */     "@S024§\6\7\x08       "  //"Hot Barista Foam"
                       "                ",  	//"air        \6\7\x08 %",

    /* MSP n.15 */     "@S025§\6\7\x08       "  //"Hot Barista Foam"
                       "                ",  	//"sped pump  \6\7\x08 %",

        #ifdef ABIL_SENSORE_PRESSIONE							 
    /* MSP n.16 */     "@S026§\6§\7\x08      "  //"Hot Barista Foam"
                       "                ",  	//"pres. 0=dis.\6.\7\x08",
        #else
    /* MSP n.16 */     "@S027           "  		//"not used        "
                       "                ",  	//"                ",
        #endif		

    /* MSP n.17 */     "@S028§\6\7\x08       "  //"Cold ClassicFoam"
                       "                ",  	//"air        \6\7\x08 %",

    /* MSP n.18 */     "@S029§\6\7\x08       "	//"  "Cold ClassicFoam"
                       "                ",  	//"sped pump  \6\7\x08 %",

        #ifdef ABIL_SENSORE_PRESSIONE							 
    /* MSP n.19 */     "@S030§\6§\7\x08      "  //"Cold ClassicFoam"
                       "                ",  	//"pres. 0=dis.\6.\7\x08",
        #else
    /* MSP n.19 */     "@S031           "  		//"not used        "
                       "                ",  	//"                ",
        #endif		

    /* MSP n.20 */     "@S032§\6\7\x08       "  //"Cold Fluffy Foam"
                       "                ", 		//"air        \6\7\x08 %",

    /* MSP n.21 */     "@S033§\6\7\x08       "  //"Cold Fluffy Foam"
                       "                ",   	//"sped pump  \6\7\x08 %",

        #ifdef ABIL_SENSORE_PRESSIONE							 
    /* MSP n.22 */     "@S034§\6§\7\x08      "  //"Cold Fluffy Foam"
                       "                ",  	//"pres. 0=dis.\6.\7\x08",
        #else
    /* MSP n.22 */     "@S035           "  		//"not used        "
                       "                ",  	//"                ",
        #endif		

    /* MSP n.23 */     "@S036§\6\7\x08       "  //"Cold BaristaFoam"
                       "                ",  	//"air        \6\7\x08 %",

    /* MSP n.24 */     "@S037§\6\7\x08       "  //"Cold BaristaFoam"
                       "                ",  	//"sped pump  \6\7\x08 %",

        #ifdef ABIL_SENSORE_PRESSIONE							 
    /* MSP n.25 */     "@S038§\6§\7\x08      "  //"Cold BaristaFoam"
                       "                ",  	//"pres. 0=dis.\6.\7\x08",
        #else
    /* MSP n.25 */     "@S039           " 		//"not used        "
                       "                ",  	//"                ",
        #endif	
    /* MSP n.26 */     "@S040§\6\7\x08       "  //"Deter.dissolving"
                       "                ",  	//"Seconds:     \6\7\x08",

    /* MSP n.27 */     "@S041§\x08         "	// "Check Tank Milk "
                       "                ", 		// "Temper. 1=yes  \x08",							   

    /* MSP n.28 */     "@S042§\6\7\x08       "  //"Hot No Foam     "
                       "                ",  	//"sped pump  \6\7\x08 %",

    /* MSP n.29 */     "@S043§\6\7\x08       "  //"Cold No Foam    "
                       "                ",  	//"sped pump  \6\7\x08 %",		

    /* MSP n.30 */     "@S044§\4§\6\7\x08     " //"Tuning milk pump"
                       "                ",      //"+/- 30%: \4 \6\7\x08 %",     

    /* MSP n.31 */     "@S047§\x08         "    //"Auto rins. mode "
                       "                ",      //"0=Dflt 1=HDE   \x08",

};
#endif  	
#endif //ABIL_CAPPUCCINATORE	

const u8 __far ML_MS_TIPO_PALETTA[4][16] =			//ezio 11/05/2015
{
                    "@T001           ",                                //"stirrers sugar  ",
                    "@T002           ",                                //"stirrers no sug.",
                    "@T003           ",                                //"stirrers always ",
                    "@T004           ",                                //"stirrers never  ",
};

const u8 __far ML_MS_MODULI_EST[30][32] =			
{
    /* MSP n. 0 */  "@Z001           "          	// "        use the "
                    "                ",         	// "dispensed cup   "                 

    /* MSP n. 1 */  "@Z002§\7\x08      "     		// "Place your cup  "
                    "                ",         	// "within \7\x08 sec.  "

    /* MSA n. 2 */  "@Z003           "          	//"Deter./tank cup "				//#4660
                    "                ",          	//"station 10=ok   ",				//#4660	

    /* MSA n. 3 */  "@Z004           "          	//"put syrup tube  "				//#4660
                    "                ",          	//"bottl>tank 10=ok",				//#4660		

    /* MSA n. 4 */  "@Z005§\0\1§\2\3     "      	//"\0\1/\2\3  H2O fill." 			//#4660
                    "                ",          	//"in tank with det",				//#4660	

    /* MSA n. 5 */  "@Z006           "          	//"Clean Tank under"				//#4660
                    "                ",          	//"cup stat.  10=ok",				//#4660	

	/* MSA n. 6 */  "@Z007§\0\1§\2\3     "         	//"\0\1/\2\3 SYRUP "				//#4660	
                    "                ",          	//"Cleanig End     ",				//#4660	

    /* MSA n. 7 */  "@Z008           "          	//"Hot H2O filling "			    //#4660
                    "                ",          	//"in clean tank   ",				//#4660				

    /* MSA n. 8 */  "@Z009           "          	//"Water/Clen.Sol. "				//#4660
                    "                ",          	//"through syr.tube",				//#4660	

    /* MSA n. 9 */  "@Z010§\0§\1§\2     "          	//"  Inst module   "			
                    "                ",          	//" version  \0.\1.\2 "				

    /* MSA n. 10 */  "@Z011§\0§\1§\2     "          //"  Syrup module  "			
                    "                ",          	//" version  \0.\1.\2 "	

    /* MSA n. 11 */ "@Z012§\4\5\6\7\x08§\0   "      //"\4\5\6\7\x08 Mixer \0   "
                    "                ",     		//"rinsing         ",
};


#endif 
