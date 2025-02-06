/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                    /
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

#define CS_LOW()  LATBbits.LATB0 = 0  // Broche CS active (LOW)
#define CS_HIGH() LATBbits.LATB0 = 1  // Broche CS inactive (HIGH)
// Alias pour les LEDs
#define LED1 LATAbits.LATA0 // LED1 connectée à RA0
#define LED2 LATCbits.LATC9 // LED2 connectée à RC9

void InitApp(void);         /* I/O and Peripheral Initialization */
void SPI_Init(void);
void CS_Init(void);
void RST(void);
