/*
 * animaly_detection_util.cpp
 *
 * Author: 208943555 Hila Shechter
 */

#include <math.h>
#include "anomaly_detection_util.h"

float avg(float* x, int size){
    float sum = 0;
    for (int i=0; i<size; i++){
        sum += x[i];
    }
	return sum/(float)size;
}

// returns the variance of X and Y
float var(float* x, int size){
    float sum = 0;
    float average = avg(x,size);
    for(int i=0; i<size; i++){
        sum += pow(x[i]- average,2);
    }
	return (1/(float)size)*sum;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){
    float sum = 0;
    float avg_x = avg(x,size);
    float avg_y = avg(y,size);
    for(int i = 0; i<size; i++){
        sum += (x[i]- avg_x)*(y[i]-avg_y);
    }
	return sum/(float)size;
}


// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){
    float var_x = sqrt(var(x, size));
    float var_y = sqrt(var(y,size));
    float covariance = cov(x,y,size);
	return covariance/(var_x*var_y);
}

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size){
    float* array_x = new float[size];
    float* array_y = new float[size]; 
    for (int i = 0; i<size; i++){
        array_x[i] = points[i]->x;
        array_y[i] = points[i]->y;
    }
    float a = cov(array_x, array_y,size)/ var(array_x,size);
    float b = avg(array_y,size)- (a*avg(array_x,size));
	return Line(a,b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
    Line line = linear_reg(points,size);
    float fx = (line.a * p.x) + line.b;
	return fabs(p.y - fx);
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
    float fx = (l.a * p.x) + l.b;
	return fabs(p.y - fx);
}




