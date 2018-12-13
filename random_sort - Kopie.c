/*
Compile: make random_sort
Run: ./random_sort
make random_sort && ./random_sort
*/

#include "base.h"

//template code

char* brands[] = {"VW", "BMW", "Mercedes", "Fiat", "Ford", "Dacia", "Audi", "Citroen"};
int brand_count = sizeof(brands) / sizeof(char*);
int min_year = 1950;
int max_year = 2017;
int max_km = 250000;

struct Car{
	char* brand;
	int year;
	int km;
	double price;
};

typedef struct Car Car;

// Initialize a Car structure
Car make_car(char* brand, int year, int km, double price) {
    Car c = { brand, year, km, price};
    return c;
}

//print car information
void print_car(Car* car){
	printf("Caryear: %4d\tbrand: %8s\tKM: %6dkm\tPrice: %8.2lfEuro\n", car->year, car->brand, car->km, car->price);	
}

//print carArray
void print_car_array(Car* car_park, int car_count){
	for(int i = 0; i < car_count; i++){
		print_car(car_park + i);
	}
}

// Creates an array with random cars. Returns a pointer to the array.
Car* create_car_park(int car_count){
	//next statement is part of the following lectures. Don't worry.
	Car* car = (Car*) xmalloc(sizeof(Car) * car_count);
	
	//fill the array with random cars
	for(int i = 0; i < car_count; i++){
		int random_brand_index = i_rnd(brand_count); // car brand index in interval: [0,7]

		car[i].brand = brands[random_brand_index];
		int random_year = i_rnd(max_year - min_year) + min_year; //years between min and max year
		car[i].year = random_year;
		
		int random_km = 0;
		// On MinGW: max random number is 32767. To overcome this two 16 bit random numbers are glued together.
		if(RAND_MAX == 32767){
			random_km = (i_rnd(max_km >> 16) << 16 ) | i_rnd(max_km); //dirty hack
		}else{
			random_km = i_rnd(max_km); 
		}
		car[i].km = random_km; //max 250.000km
		
		car[i].price = 30000.00 * pow(0.85, (random_year - min_year)) + 20000.00 * pow(0.75, random_km / 10000.0)  ; // car price max 50.000 Euro
	}
	return car;
}

// Deletes a car array. Call the function, when you don't need the array anymore.
void delete_car_park(Car* cars){
	free(cars);
}

//end of template code

//now it is your turn ... 

// (a) todo: implement compare function
int compare (Car car1, Car car2) {
    if      (car1.year > car2.year)    { return 1; }
    else if (car1.year < car2.year )   { return -1; }
    else {
        int y;
        y = strcmp(car1.brand, car2.brand); // Lexiografisch Sortieren und mit strcmp(char* str1, char* str2)
        return y;
    }

}

// (b) todo: write compare test function
void compare_test(Car* car) {
    test_equal_i(compare(car[4], car[5]),1);
    test_equal_i(compare(car[2], car[3]),1);
    test_equal_i(compare(car[1], car[1]),0);
    test_equal_i(compare(car[6], car[7]),1);
    test_equal_i(compare(car[8], car[9]),1);

}

// (c) todo: implement sorted function
bool sorted(Car* a, int length) {
    int i = 0;
    for (i = 1; i < length-1 ; i++) {
    if (compare(a[i], a[i+1]) != 1) { return false;}
    }
}
// (d,e) todo: implement random_sort function
int random_sort(Car* a, int length) {
    int i = 0;
    bool y;
    do {
        int number1, number2;
        number1 = rand () % 10;
        number2 = rand () % 10;
        Car car_random;
        car_random = a[number2];
        a[number2] = a[number1];
        a[number1] = car_random;
        y = sorted(a, length);
        i ++;
    }
    while (y == false);
    printf ("Es wurde %d mal sortiert. \n",i);
    return 0;
}

int main(void) {
	
	// (b) todo: test compare function
	compare_test();
	
	
	//some output
	int number_of_random_cars = 10;
	Car* car_park = create_car_park(number_of_random_cars);
	print_car_array(car_park, number_of_random_cars);
	
	printf("Sorting...\n");
	
	//todo: sort the car_park array.
	random_sort(car_park, 10);
	
	print_car_array(car_park, number_of_random_cars);
	
	delete_car_park(car_park);
	
	
	
	// (f) todo: compare the number of swaps and compare calls.


    return 0;
}
