#ifndef __ColourCalculation__hpp__
#define __ColourCalculation__hpp__

typedef struct{
	int r,g,b;
}rgb;

namespace ColourCalculation{
//erster teil planksches strahlungsgesetz fuer rot 622nm
const static float p1r = 1;
//erster teil planksches strahlungsgesetz fuer gruen 522nm
const static float p1g = 1;
//erster teil planksches strahlungsgesetz fuer blau 462nm
const static float p1b = 1;
static rgb temp2RGB(int temp);

}
#endif
