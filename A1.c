/*
* File:		A1.c
* Author:	Andrew Mercer	B00768289
* Date:		2020/5/15
* Version:	1.0
*
* Purpose:	To simulate a Barber Shop with a given set of parameters 
*			and output Average wait time, number of customers that left per day
*			daily standard deviation of wait times, customers waiting at the end of the day,
*			and some additional overall statistics.
*
* Notes:	For some reason, when the user enters low values for # of days to simulate, (eg, 3,4,5 etc), The summary values 
*			are not calculated correctly.
*/


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define GetHairCutTime_Max_chance		11
#define customer_queue_size 			5
#define waittimearray_size				40
#define GetHairCutTime_increase_amount 	10
#define Leave_Persentage				20
#define Max_Customer_Daily				40
#define Max_customers_waiting 			5
#define Max_minutes_daily				480
#define New_Customer_Persentage			20
#define Inital_number_of_customers		5	
#define Inital_last_item_in_queue 		2			

struct customer 
{
	int haircut_time;
	int wait_time;
};

struct customer queue[customer_queue_size];
int number_of_customers = 0;
float waittimearray[waittimearray_size];




/*
* Name:			GetHairCutTime
* Purpose:		To return a random time between 10 and 20mins inclusive 
*
* Arguments:	Void 
* Output:		A random interger between 10 and 20 inclusive 
* Modifies:		
* Returns:		Retuns a Time variable set to a random number between 10 and 20  
*
* Assumptions:	None 
* Bugs:			None 
* Notes:		
*
*
*/
int GetHairCutTime(void)
{
	int time = random() % GetHairCutTime_Max_chance;
	time = time + GetHairCutTime_increase_amount;
	return time;
}
/* This function will pass a 1 even 20*N times; passed in the variable N*/

/*
* Name:			GetLeaveBoolean
* Purpose:		To retun a 1 if the customer leaves or a 0 if the customer stays  
*
* Arguments:	number_of_customers
* Output:		returns a variable Boolean set to either a 1 or a 0 
* Modifies:		none
* Returns:		returns a variable Boolean set to either a 1 or a 0 
*
* Assumptions:	none
* Bugs:			none
* Notes:		This will create a random number between 0 and 19 to check if the customer leaves
*				the if else structure is to deal with the edge cases of no customers being in the store 
*				and the store being full.
*/
int GetLeaveBoolean(int number_of_customers)
{
	int Boolean = 0;
	if (number_of_customers == 0)
	{
		Boolean = 0;
	}
	else if (number_of_customers == Max_customers_waiting)
	{
		Boolean = 1;
	}
	else
	{
		
		int chance = random() % (Leave_Persentage*number_of_customers);
		if (chance == 1)
		{
		Boolean = 1;
		}
	}
	return Boolean;
}

int main(void)
{
	printf("Do you want to Randomize: (y/n) \n");
	char ch;
	scanf("%ch",&ch);
	/* Allows for random numbers to be toggled on */
	if (ch == 'y'){				
		srandom(time(NULL));
	}
	

	int maxdays = 0;
	int days = 1;
	

	printf("Enter Number of Days to Simulate (as an interger): \n");
	scanf("%d",&maxdays);
	float array_of_SDs[maxdays];
	float array_of_daily_avg_wait[maxdays];
	int i = 0;
	/* makes every array location in array_of_SDs = 0 */
	while (i<maxdays)
	{
		array_of_SDs[i] = 0;
		i++;
	}
	while (maxdays >= days)
	{
		int array_clear_count = 0;
		/* Clears data from waittimearray*/
		while (array_clear_count <= Max_Customer_Daily)
		{
			waittimearray[array_clear_count] = 0;
			array_clear_count++;
		}
		int minutes = 0;
		int position_in_queue = 0;
		int last_item_in_queue = 0;
		int num_of_haircuts_completed = 0;
   		int new_customer = 0;
    	int num = 0;
    	int count = 0;
		int num_of_customer_leaves = 0;
		int array_count = 0;
		float avg_wait_time = 0;
		int wait_time_array_count = 0;
		float daily_standard_deviation = 0;
		while(minutes < Max_minutes_daily)
		{
			/* Used to break out of loop if 40 customers are served*/
			if (num_of_haircuts_completed >= Max_Customer_Daily){
				break;
			}
			/* Sets inital conditions for 9pm start time */
			if (minutes == 0)
			{
				queue[0].haircut_time = GetHairCutTime();
				queue[1].haircut_time = GetHairCutTime();
				queue[2].haircut_time = GetHairCutTime();
				position_in_queue = 0;
				last_item_in_queue = Inital_last_item_in_queue;
				number_of_customers = Inital_number_of_customers;            
			}
			
			/* Used to determine if a new customer has entered the store*/
			int new_customer = random() % New_Customer_Persentage;
			if (new_customer == 0)
			{
				int temp = GetLeaveBoolean(number_of_customers);
				if (temp != 1)
				{
					if (position_in_queue < (customer_queue_size-1))
					{
						number_of_customers++;
						last_item_in_queue++;
						queue[last_item_in_queue].haircut_time = GetHairCutTime();
						queue[last_item_in_queue].wait_time = 0;
					}
					else
					{
						number_of_customers++;
						last_item_in_queue = 0;
						queue[last_item_in_queue].haircut_time = GetHairCutTime();
						queue[last_item_in_queue].wait_time = 0;
					}

				}
				else
				{
					num_of_customer_leaves++;
				}

			}

			if (number_of_customers != 0){
				/* This checks if the primary position in the queue can rotates to the next person in line*/
				if ((queue[position_in_queue].haircut_time) == 0 ){
					if (position_in_queue == (customer_queue_size-1))
					{
						/* Populated an array with the person leaving the store's wait time for use later*/
						waittimearray[wait_time_array_count] = queue[position_in_queue].wait_time;
						position_in_queue = 0;
						num_of_haircuts_completed++;
						number_of_customers--;
						wait_time_array_count++;
						
					}
					else
					{
						/* Populated an array with the person leaving the store's wait time for use later*/
						waittimearray[wait_time_array_count] = queue[position_in_queue].wait_time;
						position_in_queue++;
						num_of_haircuts_completed++;
						number_of_customers--;
						wait_time_array_count++;
				
					}
				}else
				{
					/* Is called if the hair cut is not finished to decrease the amount of time left in haircut_time */
					queue[position_in_queue].haircut_time--;
				}

			}
			/* This loop is used to increase the wait_time of all customers waiting*/
			count = 0;
			num = position_in_queue + 1;
			while (count < number_of_customers-1)
			{
				if (position_in_queue == (customer_queue_size-1))
				{
					num = 0;
				}
				queue[num].wait_time++;
				count++;
				num++;
			}
			minutes++;

		}
		/* Sums wait time for each customer into avg_wait_time*/
		array_count = 0;
		while (array_count < num_of_haircuts_completed)
		{
			avg_wait_time = avg_wait_time + waittimearray[array_count];
			array_count++;
		}
		/* Calcualtes avg wait time*/
		avg_wait_time = avg_wait_time / (float)num_of_haircuts_completed;
		/*Stores the days avg_wait_time into array*/
		array_of_daily_avg_wait[days] = avg_wait_time;
		array_count = 0;
		/* Calculates the Standard Deviation of the avg wait times for the day */
		while (array_count < num_of_haircuts_completed)
		{
			daily_standard_deviation = daily_standard_deviation + pow((waittimearray[array_count] - avg_wait_time),2);
			array_count++;
		}
		daily_standard_deviation = sqrt(daily_standard_deviation / (float)num_of_haircuts_completed);

		printf("~~~DAY %d~~~\n",days);
		printf("Number of Customers that Left: %d \n",num_of_customer_leaves);
		printf("Average Customer Wait Time: %f \n",avg_wait_time);
		printf("Daily Standard Deviation of Wait Times: %f \n", daily_standard_deviation);
		/* Stores this days standard deviation in an array for later */
		array_of_SDs[days] = daily_standard_deviation;
		/* If there are people in the store, get number of customers no getting their hair cut*/
		if (number_of_customers > 0)
		{
			number_of_customers = number_of_customers -1;
		}
		
		printf("Customers Waititing at End of Day: %d \n \n \n",number_of_customers);
		days++;


	}
	
	float min_standard_deviation = array_of_SDs[1];
	float max_standard_deviation = array_of_SDs[1];
	float min_avg = array_of_daily_avg_wait[1]; 
	float max_avg = array_of_daily_avg_wait[1]; 
	/* This is used to sum all days standard deviation and calculated the min and max SD for all days*/
	float standard_deviation_avg = 0;
	int array_count = 0;
	while (array_count < maxdays)
	{
		standard_deviation_avg = standard_deviation_avg + array_of_SDs[array_count];
		
		if (array_count != 0)
		{
			if (min_standard_deviation > array_of_SDs[array_count]){
				min_standard_deviation = array_of_SDs[array_count];
			}
			if (max_standard_deviation < array_of_SDs[array_count]){
				max_standard_deviation = array_of_SDs[array_count];
			}
		}

		array_count++;
	}

	/* This sums all days avgs and calculated the min and max avg for all days*/
	float avg_of_avg = 0;
	array_count = 0;
	while (array_count < maxdays)
	{
		avg_of_avg = avg_of_avg + array_of_daily_avg_wait[array_count];
		
		if (array_count != 0)
		{
			if (min_avg > array_of_daily_avg_wait[array_count]){
				min_avg = array_of_daily_avg_wait[array_count];
			}
			if (max_avg < array_of_daily_avg_wait[array_count]){
				max_avg = array_of_daily_avg_wait[array_count];
			}
		}

		
		array_count++;
	}
	/* Gets AVG*/
	avg_of_avg = avg_of_avg / (float)days;
	/* Calculates SD of daily AVG wait time*/
	array_count = 0;
	float standard_deviation_of_avg;
	while (array_count < days)
	{
		standard_deviation_avg = standard_deviation_avg + pow((array_of_daily_avg_wait[days] - avg_of_avg),2);
		array_count++;
	}
	standard_deviation_avg = standard_deviation_avg / days;
	standard_deviation_avg = sqrt(standard_deviation_avg);

	standard_deviation_avg = standard_deviation_avg / (float)maxdays;
	
	/* Calculates SD of daily SDs*/
	array_count = 0;
	float standard_deviation_of_SDs = 0;
	while (array_count < maxdays)
	{
		standard_deviation_of_SDs = standard_deviation_of_SDs + pow((array_of_SDs[array_count] - standard_deviation_avg),2);
		array_count++;
	}
	standard_deviation_of_SDs = standard_deviation_of_SDs / (float)maxdays;
	standard_deviation_of_SDs = sqrt(standard_deviation_of_SDs);
	
	/*These values are not relevent if there is only one day simulated*/
	if(maxdays > 1){
		printf("~~SUMMARY~~\n \n \n");
		printf("Overall Average of Daily Averages: %f \n",avg_of_avg);
		printf("Overall Standard Deviations of Daily Averages: %f \n",standard_deviation_avg);
		printf("Overall Average of Standard Deviations: %f \n",standard_deviation_avg);
		printf("Overall Standard Deviations of Daily Standard Deviations: %f \n",standard_deviation_of_SDs);
		printf("Minimum Daily Average Wait Time: %f \n",min_avg);
		printf("Maximum Daily Average Wait Time: %f \n",max_avg);
		printf("Minimum Daily Average Standard Deviation of Wait Times: %f \n",min_standard_deviation);
		printf("Maximum Daily Average Standard Deviation of Wait Times: %f \n",max_standard_deviation);
	}
	
	return 0;
}