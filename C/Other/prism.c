/*Purpose: asks the user for the vertices of a rectangular prism located in 3-D space,calculate surface area and volume.*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* here is the function to get the distance from the vertices. */

double get_dist (double distx0,double distx1, double disty0, double disty1, double distz0, double distz1){

	double dist = sqrt(((distx1-distx0)*(distx1-distx0))+((disty1-disty0)*(disty1-disty0))+((distz1-distz0)*(distz1-distz0)));
	
	
	return dist;
}
/*this is the function to obtain the rectangular area */
double get_rect_area(double dist1, double dist2){
	
	double area = dist1*dist2;
	
	return area;
}
/*function of the surface area*/
double get_surface_area(double area1, double area2, double area3){
	
	double sarea=2*(area1+area2+area3);
	
	return sarea;
}

/*function to obtain the volume of the prism. */
double get_volume(double length, double width, double height){
							
	double volume = length*width*height;
	
	return volume;
}

int main(){
/*to calculate the surface area and volume, we would only need 4 points from
 * the prism. */


/*With that, we only prompt the user for 4 points. */
	double point0x,point0y,point0z;							double point1x,point1y,point1z;
	double point2x,point2y,point2z;							double point6x,point6y,point6z;							double length, width, height, area_base, area_side, area_front, total_area, volume;
	double e;

/*e is for the empty space, we don't need. */
											printf("Enter the first coordinate in the form x y z: ");			scanf("%lf", &point0x);
	scanf("%lf", &point0y);								scanf("%lf", &point0z);								printf("Enter the second coordinate in the form x y z: ");			scanf("%lf", &point1x);
	scanf("%lf", &point1y);								scanf("%lf", &point1z);								printf("Enter the third coordinate in the form x y z: ");			scanf("%lf", &point2x);
	scanf("%lf", &point2y);
	scanf("%lf", &point2z);
	printf("Enter the fourth coordinate in the form x y z: ");
	scanf("%lf", &e);
	scanf("%lf", &e);
	scanf("%lf", &e);
	printf("Enter the fifth coordinate in the form x y z: ");
	scanf("%lf", &e);								scanf("%lf", &e);								scanf("%lf", &e);
	printf("Enter the sixth coordinate in the form x y z: ");
	scanf("%lf", &e);
	scanf("%lf", &e);
	scanf("%lf", &e);
	printf("Enter the seventh coordinate in the form x y z: ");
	scanf("%lf", &point6x);
	scanf("%lf", &point6y);
	scanf("%lf", &point6z);
	printf("Enter the eighth coordinate in the form x y z: ");
	scanf("%lf", &e);
	scanf("%lf", &e);
	scanf("%lf", &e);

/* we would then call the distance function for each side of the prism. */
										length = get_dist (point1x,point0x, point1y, point0y, point1z, point0z);
width = get_dist (point1x,point2x, point1y, point2y, point1z, point2z);
height = get_dist (point1x,point6x, point1y, point6y, point1z, point6z);
/* We would then call the area function to calculate its area. */												area_base = get_rect_area(length,width);
area_side = get_rect_area(width,height);
area_front = get_rect_area(length,height);

/* then call the total area function and the total volume function for the 
 * solution. */
total_area = get_surface_area(area_base, area_side, area_front);
volume = get_volume(length,width,height);
printf("The surface area of the prism is %.2lf\n",total_area);
printf("The volume of the prism is %.2lf\n",volume);

	return 0;																												}

