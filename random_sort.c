/*
Compile: make random_sort
Run: ./random_sort
make random_sort && ./random_sort
*/

#include "base.h"
#include <mem.h>

//template code

char* brands[] = {"VW", "BMW", "Mercedes", "Fiat", "Ford", "Dacia", "Audi", "Citroen"};
int brand_count = sizeof(brands) / sizeof(char*);
int min_year = 1950;
int max_year = 2017;
int max_km = 250000;

typedef struct Car{
	char* brand;
	int year;
	int km;
	double price;
} Car;

typedef struct Carpark {
    Car* cars;
    int len;
} Carpark;



long long int_arr_section_sum( int*, int, int);





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

Carpark* create_car_parks(int count, int min_cars, int max_cars) {
    Carpark* cars = (Carpark*) xmalloc(sizeof(Carpark) * count);
    int len;
    while(count--) {
        len = min_cars + (rand() % (max_cars - min_cars));
        cars[count].len = len;
        cars[count].cars = create_car_park(len);
    }
    return cars;
}

// Deletes a car array. Call the function, when you don't need the array anymore.
void delete_car_park(Car* cars){
	free(cars);
}
void delete_car_parks(Carpark* car_parks, int len) {
    while( len-- )
        free(car_parks[len].cars);
    free(car_parks);
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
void compare_test(Car* car, int len) {
    test_equal_i(compare(car[4], car[5]),1);
    test_equal_i(compare(car[2], car[3]),1);
    test_equal_i(compare(car[1], car[1]),0);
    test_equal_i(compare(car[6], car[7]),1);
    test_equal_i(compare(car[8], car[9]),1);

}

// (c) todo: implement sorted function
bool sorted(Car* a, int len) {
    if ( len < 2 ) return true;
    while (--len>1)
        if (compare(a[len-1], a[len]) != 1)
            return false;
    return true;
}
// (d,e) todo: implement random_sort function
int random_sort(Car* a, int len) {
    int swaps = 0, i1, i2;
    Car container;
    do {
        swaps++;
        i1=rand()%len;
        i2=rand()%len;
        container = a[i1];
        a[i1] = a[i2];
        a[i2] = container;
    } while (!sorted(a,len));
    return swaps;
}

double int_arr_avg(int* arr, int len) {
    long long sum = 0;
    int i = len;
    while(i--)
        sum += arr[i];
    return ((double) sum) / ((double)len);
}

double int_arr_section_avg( int* arr, int start, int end ) {
    return((double) int_arr_section_sum(arr,start,end)) / ((double)(end-start));
}

long long int_arr_section_sum( int* arr, int start, int end ) {
    long long sum = 0;
    for ( int i = start; i < end; i++ )
        sum += arr[ i ];
    return sum;
}

int main(void) {
	

	
	
	//some output
	int number_of_random_cars = 10;


	Car* car_park = create_car_park(number_of_random_cars);
	print_car_array(car_park, number_of_random_cars);
	
	printf("Sorting...\n");
	
	//todo: sort the car_park array.
	random_sort(car_park, number_of_random_cars);

    // (b) todo: test compare function
    compare_test(car_park, number_of_random_cars);
	
	print_car_array(car_park, number_of_random_cars);
	
	delete_car_park(car_park);
	
	
	
	// (f) todo: compare the number of swaps and compare calls.
	printf("(f) todo: compare the number of swaps and compare calls.\n");
    int max_arr_len = 10;
    int min_arr_len = 3;
    int num_arrays = 5;
    int num_sort_runs = 100;
    printf("Minimum length: %d\nMaximum length: %d\nNumber of arrays: %d\nNumber of sorts: %d\n", max_arr_len, min_arr_len, num_arrays, num_sort_runs);

    Carpark* car_parks = create_car_parks(num_arrays,min_arr_len,max_arr_len);
    int* swaps = xmalloc(sizeof(int)*num_arrays*num_sort_runs);
    for (int i = 0, j = 0; i < num_arrays; j++) {
        if (j >= num_sort_runs) {
            j = 0;
            i++;
            if ( i >= num_arrays ) break;
        }
        swaps[i * num_sort_runs + j] = random_sort(car_parks[i].cars, car_parks[i].len);
    }
    // avg
    for (int i = 0; i < num_arrays; i++) {
        printf("Durchschnittliche Anzahl an Swaps fuer Arrays mit Laenge %d: %lf\n", car_parks[i].len,
               int_arr_section_avg(swaps, i * num_sort_runs, (i + 1) * num_sort_runs));
        printf("Anzahl an Compares: %d\n",
               int_arr_section_sum(swaps, i * num_sort_runs, (i + 1) * num_sort_runs) * (car_parks[i].len - 1));
    }
    delete_car_parks(car_parks, num_arrays);
    free(swaps);

    return 0;
}
