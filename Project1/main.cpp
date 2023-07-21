#include<stdio.h>
#include<json-c/json.h>
#include<string.h>
int main(int argc, char** argv) {

	FILE* fp;
	char buffer[15000];
	char strYear[15];

	struct json_object* parsed_json;
	struct json_object* parsed_json2;
	struct json_object* keyword;
	struct json_object* title;
	struct json_object* year;
	struct json_object* rating;
	struct json_object* items;
	struct json_object* shows;

	int z = 0;
	int y = 1;
	int tamanho = 0;
	size_t n_shows;
	size_t i;


	fp = fopen("example.txt", "r");
	//if (!fp) {

		//fprintf(stderr, "Unable to open the file for reading!\n");

		//return -1;

	//}

	fread(buffer, 15000, 1, fp);
	fclose(fp);

	parsed_json = json_tokener_parse(buffer);
	parsed_json2 = json_tokener_parse(buffer);

	json_object_object_get_ex(parsed_json, "keyword", &keyword);
	json_object_object_get_ex(parsed_json, "items", &items);

	n_shows = json_object_array_length(items);
	printf("Found %zu shows related to %s\n", n_shows, json_object_get_string(keyword));

	for (i = 0; i < n_shows; i++) {
		shows = json_object_array_get_idx(items, i);
		parsed_json2 = json_object_array_get_idx(items, i);

		json_object_object_get_ex(parsed_json2, "title", &title);
		json_object_object_get_ex(parsed_json2, "year", &year);
		json_object_object_get_ex(parsed_json2, "imDbRating", &rating);

		strcpy(strYear, json_object_get_string(year));
		tamanho = strlen(strYear);
		for (y = 1; y <= tamanho - 2; y++) {
			if (strYear[y] != '2' && strYear[y] != '0' && strYear[y] != '1' && strYear[y] != '3' && strYear[y] != '4' && strYear[y] != '5' && strYear[y] != '6' && strYear[y] != '7' && strYear[y] != '8' && strYear[y] != '9') {//achar jeito aqui
				strYear[y] = '-';
			}
		}

		printf("%zu. %s %s Nota: %s\n ", i + 1, json_object_get_string(title), strYear, json_object_get_string(rating));
	}
	return 0;
}