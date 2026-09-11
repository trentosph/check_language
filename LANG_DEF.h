#ifndef _LANG_DEF_
#define _LANG_DEF_

#include "rhea_mapping.h"

#define MAX_MULTILANGUAGES          28

#define MAX_MSG_TABLES				17

#define MSA_INDEX					1
#define MSAP_INDEX					2 
#define NOME_SELEZ_INDEX			3	
#define NOME_PRESEL_INDEX			4	
#define PROG_NOME_PRESEL_INDEX 		5	
#define TIPO_SCHIUMA_INDEX			6	
#define TIPO_FLUSSO_INDEX			7	
#define NOME_GIORNO_INDEX			8	
#define LAV_GRUPPO_INDEX			9	
#define MES_ERRORI_AGGIUNTI_INDEX	10	
#define ParGrEspresso_INDEX			11	
#define PAR_MACINA_MOT_INDEX		12	
#define TIPO_GRANULOMETRIA_INDEX	13	
#define PAR_MAINTENANCE_INDEX		14	
#define CAPPUCCINATORE_INDEX		15	
#define TIPO_PALETTA_INDEX			16	
#define MODULI_EST_INDX				17

#define MAX_MSA 				185	 // Messaggi da 32 caratteri
#define MAX_MSAP				256 // Messaggi da 32 caratteri
#define MAX_NOME_SELEZ			21	// Messaggi da 16 caratteri

#ifdef EASY_PRESEL // Messaggi da 16 o 7 caratteri (dipende dalla define EASY_PRESEL)
#define MAX_NOME_PRESEL			14	
#else
#define MAX_NOME_PRESEL			13
#endif

#define MAX_PROG_NOME_PRESEL 	10	// Messaggi da 8 caratteri
#define MAX_TIPO_SCHIUMA		8	// Messaggi da 16 caratteri
#define MAX_TIPO_FLUSSO			3	// Messaggi da 8 caratteri
#define MAX_NOME_GIORNO			7	// Messaggi da 5 caratteri
#define MAX_LAV_GRUPPO			39	// Messaggi da 32 caratteri
#define MAX_MES_ERRORI_AGGIUNTI	7	// Messaggi da 32 caratteri
#define MAX_ParGrEspresso		16	// Messaggi da 32 caratteri
#define MAX_PAR_MACINA_MOT		7	// Messaggi da 32 caratteri
#define MAX_TIPO_GRANULOMETRIA	4	// Messaggi da 16 caratteri
#define MAX_PAR_MAINTENANCE		8	// Messaggi da 32 caratteri
#ifndef CAPPUCCINATORE_INDUX	
#define MAX_CAPPUCCINATORE		8	// Messaggi da 32 caratteri
#else
#define MAX_CAPPUCCINATORE		32  // Messaggi da 32 caratteri
#endif //#ifndef CAPPUCCINATORE_INDUX
#define MAX_TIPO_PALETTA		4	// Messaggi da 16 caratteri
#define MAX_MSG_SLAVE			12

#endif //_LANG_DEF_
