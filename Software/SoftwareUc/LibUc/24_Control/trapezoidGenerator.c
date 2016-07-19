/**
  ******************************************************************************
  * @file    trapezoidGenerator.c
  * @author  Mace Robotics (www.macerobotics.com)
  * @version V1.0
  * @date    30/12/2015
  * @brief   trapezoid generator :
  *
  *
  *
  *  speed
  *  .
  *  .
  *  .           . . . . . . . . . maximum
  *  .         .                  .
  *  .        .                    .
  *  ........                      ..........  time
  *
  *
  *
  *
  *
 *******************************************************************************/
#include <stdbool.h>
#include <stdio.h>

#include "Usart.h"
#include "trapezoidGenerator.h"

static void trapezoidGenerator_calcul(struct_trapezoid *trapezoid);
static bool trapezoidGenerator_check(struct_trapezoid *trapezoid, float area);
static void trapezoidGenerator_manage(struct_trapezoid *trapezoid);


static struct_trapezoid trapezoid_distance;
static struct_trapezoid trapezoid_orientation;


// Consigne (unit = ticks)
// maximum (maximum speed)  unit = ticks/(sample frequency)
// acceleration (tick^2)/(sample frequency)
// periode (unit = ms)


/**********************************************************
 * @brief  trapezoidGenerator_init
 * @param  None
 * @retval None
**********************************************************/
bool trapezoidGenerator_init( struct_trapezoid *trapezoid,
                              unsigned int consigne, //
                              unsigned int maximum,  // maximum speed
                              float acceleration,
                              float deceleration,
                              unsigned int periode,
                              enum_typeTrapezoid type
                             )
{
bool result = false;

  if((trapezoid->state == END_STATE )||(trapezoid->state == NO_INIT_STATE )||(trapezoid->state == ERROR_STATE ))
  {
	  trapezoid->consigne = consigne;
	  trapezoid->maximum = maximum;
	  trapezoid->acceleration = acceleration;
	  trapezoid->deceleration = deceleration;
	  trapezoid->periode = periode;
	  trapezoid->state = NO_INIT_STATE;
	  trapezoid->time_trapezoid = 0;
	  trapezoid->type = type;
	  trapezoid->time1 = 0.0;
	  trapezoid->time2 = 0.0;
	  trapezoid->time3 = 0.0;

	  trapezoidGenerator_calcul(trapezoid);

	  if(trapezoid->state != INIT_STATE)
	  {
		  result =  false;
	  }
	  else
	  {
		  result =  true;
	  }


  }
  else
  {
	  result = false;
  }

  return(result);

}


/**********************************************************
 * @brief  trapezoidGenerator_create
 * @param  Trapezoid, Consigne value and speed value
 * @retval bool : result
**********************************************************/
bool trapezoidGenerator_create(enum_CreateTrapezoid Trapezoid, uint32_t consigne, uint32_t speed)
{
bool result = false;

/*
  encodeur_reset();
  trapezoid_distance.distance_out = 0;
  trapezoid_orientation.distance_out = 0;
*/

  switch(Trapezoid)
  {
    case TRAPEZOID_DISTANCE_FORWARD:
    	result = trapezoidGenerator_init(&trapezoid_distance, consigne, speed,0.5,0.5,1,POSITIF_TRAPEZOID );
    break;

    case TRAPEZOID_DISTANCE_BACK:
    	result = trapezoidGenerator_init(&trapezoid_distance, consigne, speed,0.5,0.5,1,NEGATIF_TRAPEZOID );
    break;

    case TRAPEZOID_ORIENTATION_LEFT:
    	result = trapezoidGenerator_init(&trapezoid_orientation, consigne, speed,0.5,0.5,1,POSITIF_TRAPEZOID );
    break;

    case TRAPEZOID_ORIENTATION_RIGHT:
    	result = trapezoidGenerator_init(&trapezoid_orientation, consigne, speed,0.5,0.5,1,NEGATIF_TRAPEZOID );
    break;
  }

  return result;

}


/**********************************************************
 * @brief  trapezoidGenerator_management
 * @param  None
 * @retval None
**********************************************************/
void trapezoidGenerator_management(void)
{
  trapezoidGenerator_manage(&trapezoid_distance);
  trapezoidGenerator_manage(&trapezoid_orientation);

}


/**********************************************************
 * @brief  trapezoidGenerator_manage
 * @param  None
 * @retval None
**********************************************************/
static void trapezoidGenerator_manage(struct_trapezoid *trapezoid)
{
float out_trapezoid=0;



  if( (trapezoid->state == INIT_STATE)||(trapezoid->state == PROCESS_STATE) )
  {
    trapezoid->state = PROCESS_STATE;



    // Acceleration phase
    if(trapezoid->time_trapezoid < trapezoid->time1)
    {
      out_trapezoid = trapezoid->acceleration_sample * trapezoid->time_trapezoid;

    }
    else
    {
       // constant speed
       if(trapezoid->time_trapezoid < trapezoid->time2)
       {
         out_trapezoid = trapezoid->maximum;

       }
       else
       {
           // Deceleration phase
           if(trapezoid->time_trapezoid < trapezoid->time3)
           {
             out_trapezoid = -trapezoid->acceleration_sample * (trapezoid->time_trapezoid - trapezoid->time2) + trapezoid->maximum;
           }
           else
           {
             out_trapezoid = 0;
             trapezoid->state = END_STATE;
           }// end Deceleration phase
       }// end constant phase
    }// end acceleration speed

    trapezoid->time_trapezoid++;
  }

  // output trapezoid
  trapezoid->out_trapezoid = out_trapezoid;

  if(trapezoid->type == POSITIF_TRAPEZOID)
  {
	  trapezoid->distance_out += trapezoid->out_trapezoid;
  }
  else
  {
	  trapezoid->distance_out -= trapezoid->out_trapezoid;
  }

}


/**********************************************************
 * @brief  trapezoidGenerator_state
 * @param  None
 * @retval None
**********************************************************/
enum_stateTrapezoid trapezoidGenerator_state(enum_CreateTrapezoid Trapezoid)
{
  if((Trapezoid == TRAPEZOID_ORIENTATION_LEFT)||(Trapezoid == TRAPEZOID_ORIENTATION_RIGHT))
  {
    return(trapezoid_orientation.state);
  }
  else
  {
    return(trapezoid_distance.state);
  }

}


/**********************************************************
 * @brief  trapezoidGenerator_calcul
 * @param  None
 * @retval None
**********************************************************/
static void trapezoidGenerator_calcul(struct_trapezoid *trapezoid)
{
float time1;
float time2;
float time3;
float area1, area2, area3;

  // time1 calcul
  time1 = (float)trapezoid->maximum / (float)trapezoid->acceleration;

  // area1
  area1 = ((float)time1*(float)trapezoid->maximum)/2;



  // check if consigne > area1
  if(trapezoidGenerator_check(trapezoid, area1) == true)
  {

    // time3 calcul
    time3 = (float)trapezoid->maximum / (float)trapezoid->deceleration;


    // area 3
    area3 = ((float)time3*(float)trapezoid->maximum)/2;

    if( (area1+area3) <= trapezoid->consigne)
    {
      // area 2
      area2 = (float)trapezoid->consigne - (area1 + area3);

      time2 = (area2)/(trapezoid->maximum) + time1;

      time3 = time3 + time2;

      trapezoid->state = INIT_STATE;

      // time calcul
      trapezoid->time1 = time1*(trapezoid->periode);
      trapezoid->time2 = time2*(trapezoid->periode);
      trapezoid->time3 = time3*(trapezoid->periode);

      trapezoid->acceleration_sample = (float)trapezoid->maximum / trapezoid->time1;


    }
    else
    {
        // Acceleration and deceleration too hight !!
        trapezoid->state = ERROR_STATE;
    }
  }
  else
  {
    // else consigne < area1
    trapezoid->state = END_STATE;

  }

}


/**********************************************************
 * @brief  trapezoidGenerator_out
 * @param  trapezoid, area
 * @retval boolean
**********************************************************/
int32_t trapezoidGenerator_out(enum_CreateTrapezoid Trapezoid)
{
  if((Trapezoid == TRAPEZOID_ORIENTATION_LEFT)||(Trapezoid == TRAPEZOID_ORIENTATION_RIGHT))
  {
	  return(trapezoid_orientation.distance_out);
  }
  else
  {
	  return(trapezoid_distance.distance_out);
  }

}


/**********************************************************
 * @brief  trapezoidGenerator_reset
 * @param  trapezoid, area
 * @retval boolean
**********************************************************/
void trapezoidGenerator_reset(void)
{
  trapezoid_distance.distance_out = 0;
  trapezoid_orientation.distance_out = 0;
}


/**********************************************************
 * @brief  trapezoidGenerator_check
 * @param  trapezoid, area
 * @retval boolean
**********************************************************/
static bool trapezoidGenerator_check(struct_trapezoid *trapezoid, float area)
{
bool result = false;

  if(area < trapezoid->consigne)
  {
    result = true;
  }
  else{
    result = false;
  }

  return(result);
}

 // End Of file

