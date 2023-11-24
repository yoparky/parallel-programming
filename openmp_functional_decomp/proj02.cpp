#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// setting the number of threads:
#ifndef NUMT
#define NUMT		    4
#endif

#define CSV

int	NowYear  = 2023;		// 2023 - 2028
int	NowMonth = 0;		// 0 - 11

float	NowPrecip = 14;		// inches of rain per month
float	NowTemp = 60;		// temperature this month
float	NowHeight = 5.;		// rye grass height in inches
int	NowNumRabbits = 1;		// number of rabbits in the current population
int	NowNumHunters = 0;		// number of rabbits in the current population

// Inches, Fahrenheit
const float RYEGRASS_GROWS_PER_MONTH =		20.0;
const float ONE_RABBITS_EATS_PER_MONTH =	 1.0;

const float AVG_PRECIP_PER_MONTH =	       12.0;	// average
const float AMP_PRECIP_PER_MONTH =		4.0;	// plus or minus
const float RANDOM_PRECIP =			2.0;	// plus or minus noise

const float AVG_TEMP =				60.0;	// average
const float AMP_TEMP =				20.0;	// plus or minus
const float RANDOM_TEMP =			10.0;	// plus or minus noise

const float MIDTEMP =				60.0;
const float MIDPRECIP =				14.0;

unsigned int seed = 0;

float
Sqr( float x )
{
	return x*x;
}

float
Ranf( unsigned int *seedp, float low, float high )
{
        float r = (float) rand_r( seedp );              // 0 - RAND_MAX

        return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}

void
Watcher()
{
        while( NowYear < 2029 )
        {       
                // do nothing
                #pragma omp barrier
                // do nothing
                #pragma omp barrier
                // Write NOW state of data
                fprintf(stderr, "%4d, %4d, %6.2f, %6.2f, %6.2f, %4d, %4d\n",
                NowYear, NowMonth, NowPrecip, NowTemp, NowHeight, NowNumRabbits, NowNumHunters);
                // Advance time and re-compute environmnetal variables
                // Time
                if (NowMonth == 11) {
                        NowYear++;
                        NowMonth = 0;
                } else {
                        NowMonth++;
                }
                // Temperature
                float ang = (  30.*(float)NowMonth + 15.  ) * ( M_PI / 180. );
                float temp = AVG_TEMP - AMP_TEMP * cos( ang );
                NowTemp = temp + Ranf(&seed, -RANDOM_TEMP, RANDOM_TEMP );
                // Precipitation
                float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin( ang );
                NowPrecip = precip + Ranf(&seed, -RANDOM_PRECIP, RANDOM_PRECIP );
                if( NowPrecip < 0. )
                        NowPrecip = 0.;
                
                #pragma omp barrier
        }
}

void
Rabbits()
{
        while( NowYear < 2029 )
        {         
                // Compute next number of Rabits
                int nextNumRabbits = NowNumRabbits;
                int carryingCapacity = (int)( NowHeight );
                int hunterNumber = (int)(NowNumHunters);
                if(hunterNumber > 2) {
                        nextNumRabbits--;
                }
                if( nextNumRabbits < carryingCapacity )
                        nextNumRabbits = nextNumRabbits + 3;
                else
                        if( nextNumRabbits > carryingCapacity )
                                nextNumRabbits--;

                if( nextNumRabbits < 0 )
                        nextNumRabbits = 0;

                #pragma omp barrier

                // copy the computed next state to now state
                NowNumRabbits = nextNumRabbits;
                #pragma omp barrier
                // do nothing
                #pragma omp barrier
        }
}

void
RyeGrass()
{
        while( NowYear < 2029 )
        {         
                // Compute next number of Rye Grass Height               
                float tempFactor = exp(   -Sqr(  ( NowTemp - MIDTEMP ) / 10.  )   );
                float precipFactor = exp(   -Sqr(  ( NowPrecip - MIDPRECIP ) / 10.  )   );

                float nextHeight = NowHeight;
                nextHeight += tempFactor * precipFactor * RYEGRASS_GROWS_PER_MONTH;
                nextHeight -= (float)NowNumRabbits * ONE_RABBITS_EATS_PER_MONTH;
                // clamp to 0 in case negative
                if( nextHeight < 0. ) nextHeight = 0.;

                #pragma omp barrier
                // copy the computed next state to now state
                NowHeight = nextHeight;
                #pragma omp barrier
                // do nothing
                #pragma omp barrier
        }
}

void
Hunter()
{
        while( NowYear < 2029 )
        {         
                // Compute next number of Rabits
                int nextNumHunters = NowNumHunters;
                // more than 5 rabbits require pest control
                int hunterCapacity = (int) ( NowNumRabbits - 5);
                if( nextNumHunters < hunterCapacity )
                        nextNumHunters++;
                else
                        if( nextNumHunters > hunterCapacity )
                                nextNumHunters = nextNumHunters - 2;

                if( nextNumHunters < 0 )
                        nextNumHunters = 0;

                #pragma omp barrier
                // copy the computed next state to now state
                NowNumHunters = nextNumHunters;
                #pragma omp barrier
                // do nothing
                #pragma omp barrier
        }
}

float x = Ranf(&seed, -1.f, 1.f );

int
main( int argc, char *argv[ ] )
{
#ifdef _OPENMP
	//fprintf( stderr, "OpenMP is supported -- version = %d\n", _OPENMP );
#else
        fprintf( stderr, "No OpenMP support!\n" );
        return 1;
#endif      

        omp_set_num_threads( NUMT );    // set the number of threads
        
        #pragma omp parallel sections
        {
                #pragma omp section
                {
                        Rabbits( );
                }

                #pragma omp section
                {
                        RyeGrass( );
                }

                #pragma omp section
                {
                        Watcher( );
                }

                #pragma omp section
                {
                        Hunter( );	// your own
                }
        }       // implied barrier -- all functions must return in order
	// to allow any of them to get past here

}
