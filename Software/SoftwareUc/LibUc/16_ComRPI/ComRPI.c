/**
  ******************************************************************************
  * @file    ComRPI.c
  * @author  Mace Robotics
  * @version V1.0
  * @date    04/12/2015
  * @brief  Communication between µC STM32 and raspberry pi board.
  *
 *******************************************************************************/
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "ComRPI.h"
#include "Board.h"



/************************************************************************
 * Private functions
***********************************************************************/
static bool ComRPI_checkParameter(uint32_t Parameter, uint32_t Min , uint32_t Max );
static void ComRPI_DoCommand(enum_NameComdRPi NameCommand);


struct_trapezoid trapezoid_distance;

/************************************************************************
 * Variable definitions
***********************************************************************/
struct_ComRPI ComRPI;

/************************************************************************
 * List commands
***********************************************************************/
const char List_Command[NUMBER_COMMAND][SIZE_COMMAND]=
{
"LED",
"LEDT",
"TE",
"BAT",
"MF",
"MB",
"TR",
"TL",
"STP",
"GR",
"FV",
"PROX",
"AL",
"MOTR",
"MOTL",
"SW",
"SPE",
"SPD",
"SMR",
"SML",
"MFC",
"MBC",
"TRC",
"TLC",
"TGS",
"EDR",
"EDL",
"CRE",
"CRD",
"RC5",
"SRLW",
"SRLR",
"RST",
"ACCX",
"ACCY",
"ACCZ"
};




/**********************************************************
 * @brief  Communication initialisation 
 * @param  None
 * @retval None
**********************************************************/
void ComRPI_init(void)
{
  // Setup serial connection
  Uart4_init(115200, UART_MODE_TX_RX, UART_PARITY_NONE, UART_STOPBITS_1, UART_WORDLENGTH_8B);

  // Init string (end of array)
  ComRPI.Command[SIZE_COMMAND-1] = '\0';
  ComRPI.Parameter1[SIZE_COMMAND-1] = '\0';
  ComRPI.Parameter2[SIZE_COMMAND-1] = '\0';

}


/**********************************************************
 * @brief  Communication management 
 * @param  cara receive by uart
 * @retval None
**********************************************************/
void ComRPI_manage(char cara)
{
static enum_ComRPI StateComRPI = WAIT_START_COM;
static uint8_t Count = 0;
 

  // Finit state machine
  switch(StateComRPI)
  {
    // State wait for begin command (#)
    case WAIT_START_COM:
	
	  Count = 0;
	
      if(cara == '#')
	    StateComRPI = READ_COM_RPI;// Go State Read the command
	  else
	    StateComRPI = WAIT_START_COM;// wait '#'

    break;
	// End State : WAIT_START_COM

	// State read the command
    case READ_COM_RPI:

      if(cara == '!')
      {
    	  ComRPI.SizeCommand = Count;
		  ComRPI.SizeParameter1 = 0;
		  ComRPI.SizeParameter2 = 0;
    	  StateComRPI = WAIT_START_COM;
      }
      else if(cara == '#')
      {
    	  Count = 0;
    	  ComRPI.SizeCommand = 0;
		  ComRPI.SizeParameter1 = 0;
		  ComRPI.SizeParameter2 = 0;
		  memset(ComRPI.Command, 0, sizeof(ComRPI.Command));// Reset string
		  memset(ComRPI.Parameter1, 0, sizeof(ComRPI.Parameter1));// Reset string
		  memset(ComRPI.Parameter2, 0, sizeof(ComRPI.Parameter2));// Reset string
    	  StateComRPI = READ_COM_RPI;
      }
      else if(cara == ',')
      {
    	  ComRPI.SizeCommand = Count;
		  Count = 0;
    	  StateComRPI = READ_P1_RPI;
      }
      else
      {
    	  if(Count < SIZE_COMMAND)
    	  {
    	    ComRPI.Command[Count++] = cara;
    	    StateComRPI = READ_COM_RPI;
    	  }
    	  else
    	  {
    		  // Command error
    		  StateComRPI = WAIT_START_COM;
    	  }


      }

    break;
	// End State : READ_COM_RPI
	
	// State read the parameter 1
    case READ_P1_RPI:
	
	  if(cara == '!')
      {
        StateComRPI = WAIT_START_COM;
		ComRPI.SizeParameter1 = Count;
      }
	  else if(cara == ',')
      {
    	  StateComRPI = READ_P2_RPI;
		  ComRPI.SizeParameter1 = Count;
		  Count = 0;
      }
	  else
	  {
	    ComRPI.Parameter1[Count++] = cara;
        StateComRPI = READ_P1_RPI;  
	  }
	
	break;
	// End State : READ_P1_RPI
	
	// State read the parameter 2
    case READ_P2_RPI:
	
	  if(cara == '!')
      {
        StateComRPI = WAIT_START_COM;
		ComRPI.SizeParameter2 = Count;
		Count = 0;
      }
	  else
	  {
	    ComRPI.Parameter2[Count++] = cara;
        StateComRPI = READ_P2_RPI;  
	  }
	break;
	// End State : READ_P1_RPI
  }
  

  // If State = WAIT_START_COM, read the command.
  if(StateComRPI == WAIT_START_COM )
  {
	ComRPI_ReadCommand();
  }

  
  
  
}


/**********************************************************
 * @brief  Communication execution command
 * @param  None
 * @retval None
**********************************************************/
void ComRPI_ReadCommand(void)
{
bool Command_Ok = false;
uint8_t Count = 0;


  for(Count=0; Count < NUMBER_COMMAND; Count++)
  {
	  // Compare receive string with command lis.
	  if (strcmp(ComRPI.Command, List_Command[Count]) == 0)
	  {

		  Command_Ok = true;
		  ComRPI_DoCommand(Count);// Do the command
		  Count = NUMBER_COMMAND;// end of loop
	  }
  }


  if(Command_Ok == false)
  {
    // Reset string
	memset(ComRPI.Command, 0, sizeof(ComRPI.Command));// Reset string
  }

}


/**********************************************************
 * @brief  ComRPI_DoCommand : do the command
 * @param  Name of the Command
 * @retval None
**********************************************************/
static void ComRPI_DoCommand(enum_NameComdRPi NameCommand)
{
uint32_t parameter1 = 0;
uint32_t parameter2 = 0;
bool Test_check_P1 = false;
bool Test_check_P2 = false;
enum_stateTrapezoid stateTrapezoid;
char string_uart3[10];

  // Reset Command
  memset(ComRPI.Command, 0, sizeof(ComRPI.Command));// Reset string

  // Read parameter and convert string to number.
  parameter1 = atol(ComRPI.Parameter1);
  parameter2 = atol(ComRPI.Parameter2);




  switch(NameCommand)
  {
    // Led management
    case COM_LED :

     // Check the parameter
     Test_check_P1 = ComRPI_checkParameter(parameter1, 1 , 4 );
     Test_check_P2 = ComRPI_checkParameter(parameter2, 0 , 1 );

     if( (Test_check_P1 == true)&&(Test_check_P2 == true) )
     {
       Leds_Write(parameter1, parameter2);// Led On or Off
     }


    break;

    // Led toggle
    case COM_LEDT :

     // Check the parameter
     Test_check_P1 = ComRPI_checkParameter(parameter1, 1 , 4 );

     if(Test_check_P1 == true)
     {
    	 Leds_toggle(parameter1);// Led toggle
     }

    break;

    // Get temperature
    case COM_TE :
      Usart_Send_Character(UART4, '$');// start
      Usart_Send_float(UART4, TempSensor_get() );// Read temperature
      Usart_Send_Character(UART4, '\n'); // end
    break;

    // Get battery tension
    case COM_BAT :
      Usart_Send_Character(UART4, '$');
      Usart_Send_float(UART4, BatteryTension_get() );// Read battery tension
      Usart_Send_Character(UART4, '\n'); // end
    break;

    // move forward
    case COM_MF :

     // Check the parameter
     Test_check_P1 = ComRPI_checkParameter(parameter1, 0 , 100 );

     if(Test_check_P1 == true)
     {
       MoveRobot_forward(parameter1);
     }

    break;

    // move back
    case COM_MB :

        // Check the parameter
        Test_check_P1 = ComRPI_checkParameter(parameter1, 0 , 100 );

        if(Test_check_P1 == true)
        {
          MoveRobot_back(parameter1);
        }

    break;

    // turn right
    case COM_TR :

        // Check the parameter
        Test_check_P1 = ComRPI_checkParameter(parameter1, 0 , 100 );

        if(Test_check_P1 == true)
        {
        	MoveRobot_turn_right(parameter1);
        }

    break;

    // turn left
    case COM_TL :

        // Check the parameter
        Test_check_P1 = ComRPI_checkParameter(parameter1, 0 , 100 );

        if(Test_check_P1 == true)
        {
        	MoveRobot_turn_left(parameter1);
        }

    break;

    // stop
    case COM_STP :
    	MoveRobot_stop();
    break;

    // get ground sensor
    case COM_GR :

    	// Check the parameter
    	Test_check_P1 = ComRPI_checkParameter(parameter1, 1 , 3 ); //1 to 3

    	if(Test_check_P1 == true)
    	{
    		Usart_Send_Character(UART4, '$');// start
    		Usart_Send_uint(UART4, GroundSensor_read(parameter1) );// Read ground sensor

    	}

    	Usart_Send_Character(UART4, '\n');

    break;

    // firmware version
    case COM_FV :
        Usart_Send_Character(UART4, '$');// start
        Usart_Send_float(UART4, FirmwareVersion_read() );// Read firmware version
        Usart_Send_Character(UART4, '\n');
    break;

    // proximity sensors
    case COM_PROX :

        // Check the parameter
        Test_check_P1 = ComRPI_checkParameter(parameter1, 1 , 6 ); // IR1 to IR6


        if(Test_check_P1 == true)
        {
        	Usart_Send_Character(UART4, '$');// start
        	Usart_Send_uint(UART4, ProxSensors_read_ir(parameter1-1) );
        }

        Usart_Send_Character(UART4, '\n');
    break;

    // ambiant light
    case COM_AL :

        // Check the parameter
        Test_check_P1 = ComRPI_checkParameter(parameter1, 1 , 6 );// IR1 to IR6


        if(Test_check_P1 == true)
        {
        	Usart_Send_Character(UART4, '$');// start
        	Usart_Send_uint(UART4, ProxSensors_read_ambiantLight(parameter1-1) );
        }

        Usart_Send_Character(UART4, '\n');
    break;

    // motor right
    case COM_MOTR :

        // Check the parameter
        Test_check_P1 = ComRPI_checkParameter(parameter1, 0 , 1 );
        Test_check_P2 = ComRPI_checkParameter(parameter2, 0 , 100 );

        if( (Test_check_P1 == true)&&(Test_check_P2 == true) )
        {
        	Motor_right(parameter1, parameter2);
        }

    break;

    // motor left
    case COM_MOTL :

        // Check the parameter
        Test_check_P1 = ComRPI_checkParameter(parameter1, 0 , 1 );
        Test_check_P2 = ComRPI_checkParameter(parameter2, 0 , 100 );

        if( (Test_check_P1 == true)&&(Test_check_P2 == true) )
        {
        	Motor_left(parameter1, parameter2);
        }

    break;

    // read switch
    case COM_SW :
    	Usart_Send_Character(UART4, '$');
    	Usart_Send_uint(UART4, Switchs_read());
    	Usart_Send_Character(UART4, '\n');
    break;

    // speaker enable
    case COM_SPE :
    	Speaker_enable();
    break;

    // speaker disable
    case COM_SPD :
    	Speaker_disable();
    break;

    //speed motor right
    case COM_SMR :

      // Check the parameter
      Test_check_P1 = ComRPI_checkParameter(parameter1, 0 , 100 );// speed 0 to 100

      if(Test_check_P1 == true)
      {
        MotorRight_speedWrite(parameter1);
      }

    break;

    //speed motor left
    case COM_SML :

        // Check the parameter
        Test_check_P1 = ComRPI_checkParameter(parameter1, 0 , 100 );// speed 0 to 100

        if(Test_check_P1 == true)
        {
          MotorLeft_speedWrite(parameter1);
        }

    break;

    // move robot with control
    case COM_MFC :

    	trapezoidGenerator_create(TRAPEZOID_DISTANCE_FORWARD, parameter1, parameter2);

    break;

    // move robot back with control
    case COM_MBC :

    	trapezoidGenerator_create(TRAPEZOID_DISTANCE_BACK, parameter1, parameter2);

    break;

    // move robot with control
    case COM_TRC :

    	trapezoidGenerator_create(TRAPEZOID_ORIENTATION_RIGHT, parameter1, parameter2);

    break;

    //turn left with control
    case COM_TLC :

    	trapezoidGenerator_create(TRAPEZOID_ORIENTATION_LEFT, parameter1, parameter2);

    break;

    //trapezoid generator state
    case COM_TGS:

    	if(parameter1 == 1)
    	{
    	  stateTrapezoid = trapezoidGenerator_state(TRAPEZOID_DISTANCE_FORWARD);
    	}
    	else
    	{
    	  stateTrapezoid = trapezoidGenerator_state(TRAPEZOID_ORIENTATION_RIGHT);
    	}

    	Usart_Send_Character(UART4, '$');
    	Usart_Send_uint(UART4, stateTrapezoid);
    	Usart_Send_Character(UART4, '\n');


    break;

    // read encoder right
    case COM_EDR :
    	Usart_Send_Character(UART4, '$');
    	Usart_Send_int(UART4, encodeurRight());
    	Usart_Send_Character(UART4, '\n');
    break;

    // read encoder left
    case COM_EDL :
    	Usart_Send_Character(UART4, '$');
    	Usart_Send_int(UART4, encodeurLeft());
    	Usart_Send_Character(UART4, '\n');
    break;

    // enable control robot
    case COM_CRE :
    	encodeur_reset();
    	controlEnable(true);
    break;

    // disable control robot
    case COM_CRD :
    	trapezoidGenerator_reset();
    	controlEnable(false);
    break;

    //
    case COM_RC5 :
    	Usart_Send_Character(UART4, '$');
    	Usart_Send_int(UART4, IRremote_read());
    	Usart_Send_Character(UART4, '\n');
    break;

    case COM_SRLW :
    	Usart_Send_String(USART3, ComRPI.Parameter1);
    break;

    case COM_SRLR :
    	Usart_Send_Character(UART4, '$');
    	Usart3_Read_String(string_uart3);
    	Usart_Send_Character(UART4, '\n');
    	Usart_Send_String(UART4, string_uart3);
    	Usart_Send_Character(UART4, '\n');
    break;

    // Reset
    case COM_RST :
    	NVIC_SystemReset();
    break;

    // Accelerometer axe X
    case COM_ACCX :
        Usart_Send_Character(UART4, '$');
        Usart_Send_float(UART4, Accelerometer_ReadAxeX() );// Read accelerometer axe X
        Usart_Send_Character(UART4, '\n'); // end
    break;

    // Accelerometer axe Y
    case COM_ACCY :
        Usart_Send_Character(UART4, '$');
        Usart_Send_float(UART4, Accelerometer_ReadAxeY() );// Read accelerometer axe Y
        Usart_Send_Character(UART4, '\n'); // end
    break;

    // Accelerometer axe Z
    case COM_ACCZ :
        Usart_Send_Character(UART4, '$');
        Usart_Send_float(UART4, Accelerometer_ReadAxeZ() );// Read accelerometer axe Z
        Usart_Send_Character(UART4, '\n'); // end
    break;


    //
    case COM_NONE :

    break;

  }

  // Reset string
  memset(ComRPI.Parameter1, 0, sizeof(ComRPI.Parameter1));// Reset string
  memset(ComRPI.Parameter2, 0, sizeof(ComRPI.Parameter2));// Reset string


}



/**********************************************************
 * @brief  ComRPI_checkParameter
 * @param  None
 * @retval None
**********************************************************/
static bool ComRPI_checkParameter(uint32_t Parameter, uint32_t Min , uint32_t Max )
{
  if( (Parameter < Min)||(Parameter > Max) )
  {
    return(false);
  }
  else
  {
	  return(true);
  }

}

 // End Of file
