#include "arrayio.h"

void outputArray(abonent_t * arr, int n, int mode) {

	FILE * file_ptr;
	char filename[100];
	
	switch (mode) {
	
		case 0:
		
			for (int i = 0; i < n; i++) {
				abonent_t abonent = arr[i];
				printf("Name: %s\nPhone number: %s\nTimestamp: %d\n", abonent.name, abonent.phoneNumber, abonent.timestamp);
			}
			
			break;
			
		case 1:

			printf("Enter filename.\n");
			scanf("%s", filename);
			
			printf("Opening %s.\n", filename);
			file_ptr = fopen(filename, "w");
							
			if (file_ptr == NULL) {
				printf("Unable to open file %s.\n", filename);
				return;
			}

			fprintf(file_ptr, "%d\n", n);

			for (int i = 0; i < n; i++) {
				abonent_t abonent = arr[i];
				
				fprintf(file_ptr, "%s\n", abonent.name);
				fprintf(file_ptr, "%s\n", abonent.phoneNumber);
				fprintf(file_ptr, "%d\n", abonent.timestamp);
			}

			fclose(file_ptr);
			
			break;

		case 2:

			printf("Enter filename.\n");
			scanf("%s", filename);
			
			printf("Opening file %s.\n", filename);
			file_ptr = fopen(filename, "wb");

			if (file_ptr == NULL) {
				printf("Unable to open file %s.\n", filename);
				return;
			}

			fwrite(&n, sizeof(int), 1, file_ptr);

			for (int i = 0; i < n; i++) {
				abonent_t abonent = arr[i];
				
				int name_size = strlen(abonent.name);
				fwrite(&name_size, sizeof(int), 1, file_ptr);
				
				fwrite(abonent.name, sizeof(char), strlen(abonent.name), file_ptr);

				int phone_size = strlen(abonent.phoneNumber);
				fwrite(&phone_size, sizeof(int), 1, file_ptr);
				fwrite(abonent.phoneNumber, sizeof(char), strlen(abonent.phoneNumber), file_ptr);

				fwrite(&abonent.timestamp, sizeof(int), 1, file_ptr);
			}

			fclose(file_ptr);
			break;
			
	}
}

int getRandomNumber(int lower, int upper) {
	return rand() % (upper - lower + 1) + lower; 
}

char * getRandomString(int lower, int upper, int l) {
	int len = getRandomNumber(1, l);
	char * str = malloc(sizeof(char) * (len + 1));
	str[len] = '\0';

	for (int i = 0; i < len; i++) {
		str[i] = getRandomNumber(lower, upper);
	}
	
	return str;
}

char * getRandomPhoneNumber() {
	char symbols[] = "123456789 ";
	char * phone = malloc(sizeof(char) * 17);
	phone[0] = '+';
	for (int i = 1; i < 16; i++) {
		phone[i] = symbols[rand() % 10];
	}
	phone[16] = '\0';
	return phone;
}

int isPhoneNumberValid(char * phone) {
	if (phone == NULL) {
		return 0;
	}


	if (strlen(phone) >= 16 || strlen(phone) == 0) {	
		return 0;
	}

	char symbols[] = "+0123456789 ";
	for (char * p = phone; *p != '\0'; p++) {
		int good = 0;
		for (char * d = symbols; *d != '\0'; d++) {
			if (*p == *d) {
				good = 1;
				break;
			}
		}

		if (!good) {
			return 0;
		}
		
	}

	return 1;
}

// void generatePlotFileData() {
// 	int ns[10] = {100, 300, 500, 1000, 1500, 2000, 3500, 5000, 7500, 10000};
// 	FILE * file = fopen("plot_data_double_selection_2.txt", "w");
// 	if (file == NULL) {
// 		printf("%s", "AAA");
// 	}
// 	int field = 2;
// 	fprintf(file, "%s", "time;n;field\n");
// 	
// 	for (int i = 0; i < 10; i++) {
// 		int n = ns[i];
// 		printf("%d", n);	
// 		abonent_t * arr = malloc(sizeof(abonent_t) * n);
// 		
// 		for (int j = 0; j < n; j++) {
// 			char * name = getRandomString(97, 122, 100);
// 			char * phoneNumber = getRandomPhoneNumber();
// 			int timestamp = getRandomNumber(10, 1000);
// 		
// 			abonent_t abonent;
// 			abonent.name = name;
// 			abonent.phoneNumber = phoneNumber;
// 			abonent.timestamp = timestamp;
// 			arr[j] = abonent;
// 		}	
// 
// 		clock_t st = clock();
// 		
// 		sortDoubleSelection(arr, n, field, 1);
// 		clock_t end = clock();
// 
// 		double time = ((double) end - st) / CLOCKS_PER_SEC;
// 		fprintf(file, "%lf;%d;%d\n", time, n, field);
// 		
// 		
// 		free(arr);
// 	}
// 	fclose(file);
// }

abonent_t * readArray(int * n, int mode) {

	abonent_t * arr;
	FILE * file_ptr;
	char filename[100];
	
	switch (mode) {

		case 0:	

			printf("Enter array length.\n");
			
			while(scanf("%d", n) != 1 || * n < 1) {
				while (getchar() != '\n') {}
				fflush(stdin);
				printf("Enter valid array length.\n");	
			}
			
			arr = (abonent_t *) malloc(sizeof(abonent_t) * ( * n));

			for (int i = 0; i < ( * n); i++) {
				abonent_t abonent;

				abonent.name = readline("Enter abonent name:");

				abonent.phoneNumber = readline("Enter abonent phone number:");
				while (!isPhoneNumberValid(abonent.phoneNumber)) {
					if (abonent.phoneNumber != NULL) {
						free(abonent.phoneNumber);
					}
					
					printf("Invalid phone number.\n");
					abonent.phoneNumber = readline("Enter abonent phone number:");
				}
				

				printf("Enter last phone call date:\n");
				while (scanf("%d", &(abonent.timestamp)) != 1 || abonent.timestamp < 0) {
					while(getchar() != '\n') {}
					fflush(stdin);
					printf("Enter valid timestamp.\n"); 
				}

				arr[i] = abonent;
			}

			break;
		
		case 1:

			printf("Enter filename.\n");
			scanf("%s", filename);
			
			printf("Opening %s.\n", filename);
			file_ptr = fopen(filename, "r");
							
			if (file_ptr == NULL) {
				printf("Unable to open file %s.\n", filename);
				return NULL;
			}

			int in = fscanf(file_ptr, "%d", n);
			if (!in) {
				fclose(file_ptr);
				return NULL;
			}
			
			arr = (abonent_t *) malloc(sizeof(abonent_t) * ( * n));

			for (int i = 0; i < * n; i++) {

				abonent_t abonent;
				
				abonent.name = file_readline(file_ptr);

				if (abonent.name == NULL || strlen(abonent.name) == 0) {
					freeAbonentArr(arr, i);
					free(abonent.name);
					fclose(file_ptr);
					return NULL;
				}

				abonent.phoneNumber = file_readline(file_ptr);

				if (abonent.phoneNumber == NULL || strlen(abonent.phoneNumber) == 0) {
					freeAbonentArr(arr, i);
					free(abonent.name);
					free(abonent.phoneNumber);
					fclose(file_ptr);
					return NULL;
				}
				
				in = fscanf(file_ptr, "%d", &abonent.timestamp);
				if (!in) {
					freeAbonentArr(arr, i + 1);
					fclose(file_ptr);
					return NULL;
				}

				arr[i] = abonent;
				
			}

			fclose(file_ptr);

			break;

		case 2:

			printf("Enter filename.\n");
			scanf("%s", filename);
			
			printf("Opening %s.\n", filename);
			file_ptr = fopen(filename, "rb");
							
			if (file_ptr == NULL) {
				printf("Unable to open file %s.\n", filename);
				return NULL;
			}

			fread(n, sizeof(int), 1, file_ptr);

			arr = malloc(sizeof(abonent_t) * ( * n));
			
			for (int i = 0; i < *n; i++) {

				int nameLen;
				fread(&nameLen, sizeof(int), 1, file_ptr);
				char * name = malloc(sizeof(char) * (nameLen + 1));
				fread(name, sizeof(char), nameLen, file_ptr);
				name[nameLen] = '\0';

				int phoneLen;
				fread(&phoneLen, sizeof(int), 1, file_ptr);
				char * phoneNum = malloc(sizeof(char) * (phoneLen + 1));
				fread(phoneNum, sizeof(char), phoneLen, file_ptr);
				phoneNum[phoneLen] = '\0';

				int timestamp;
				fread(&timestamp, sizeof(int), 1, file_ptr);

				abonent_t abonent;
				abonent.name = name;
				abonent.phoneNumber = phoneNum;
				abonent.timestamp = timestamp;

				arr[i] = abonent;
				
			}
				
			fclose(file_ptr);

			break;

		case 3:
			* n = getRandomNumber(5, 10000);
			
			arr = malloc(sizeof(abonent_t) * ( * n));

			for (int i = 0; i < * n; i++) {
				char * name = getRandomString(97, 122, 100);
				char * phoneNumber = getRandomPhoneNumber();
				int timestamp = getRandomNumber(10, 1000);

				abonent_t abonent;
				abonent.name = name;
				abonent.phoneNumber = phoneNumber;
				abonent.timestamp = timestamp;
				arr[i] = abonent;
			}	
	}

	return arr;

}


// void generateRandomInput(int lower, int upper) {
// 	
// 	printf("Generating random data for in.txt\n");
// 
// 	FILE * file_ptr = fopen("in.txt", "w");
// 
// 	if (file_ptr == NULL) {
// 		printf("Unable to open file.\n");
// 		return;
// 	}
// 	
// 
// 	int len = getRandomNumber(lower, upper);
// 	fprintf(file_ptr, "%d\n", len);
// 	for (int i = 0; i < len; i++) {
// 		char * name = getRandomString(97, 122);
// 		char * phoneNumber = getRandomString(97, 122);
// 		int timestamp = getRandomNumber(10, 1000);
// 		fprintf(file_ptr, "%s\n%s\n%d\n", name, phoneNumber, timestamp);
// 		free(name);
// 		free(phoneNumber);
// 	}
// 
// 	fclose(file_ptr);
// }
