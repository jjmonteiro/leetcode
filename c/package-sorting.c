#include <stdio.h>
#include <stdlib.h>
#define MAX_STRING_LENGTH 6

struct package
{
	char* id;
	int weight;
};

typedef struct package package;

struct post_office
{
	int min_weight;
	int max_weight;
	package* packages;
	int packages_count;
};

typedef struct post_office post_office;

struct town
{
	char* name;
	post_office* offices;
	int offices_count;
};

typedef struct town town;

void print_all_packages(town t) {
    printf("%c:\n", *t.name);
    for (int i = 0; i < t.offices_count; i++)
    {
        printf("\t%d:\n", i);
        for(int j = 0; j < t.offices[i].packages_count; j++)
        {
            printf("\t\t%c\n", *t.offices[i].packages[j].id);
        }
    }
}

void add_package(town* t, int office, package* pkg) 
{
    int total_pkgs = t->offices[office].packages_count;

    t->offices[office].packages = realloc(t->offices[office].packages,
        (total_pkgs + 1) * sizeof(package));

    t->offices[office].packages[total_pkgs].id = pkg->id;
    t->offices[office].packages[total_pkgs].weight = pkg->weight;

    t->offices[office].packages_count++;
}

void rm_package(town* t, int office, char* package_id) 
{
    for (int h = 0; h < t->offices[office].packages_count; h++) 
    {
        if (*t->offices[office].packages[h].id == *package_id) 
        {
            for (int i = h; i < t->offices[office].packages_count - 1; i++) 
            {
                t->offices[office].packages[i] = t->offices[office].packages[i + 1];
            }
            t->offices[office].packages_count--;

            t->offices[office].packages = realloc(t->offices[office].packages, t->offices[office].packages_count * sizeof(package));
        }
    }
}

void send_all_acceptable_packages(town* source, int source_office_index, town* target, int target_office_index) {	
    int max_tgt_weight = target->offices[target_office_index].max_weight;
    int min_tgt_weight = target->offices[target_office_index].min_weight;
    
    for (int i = 0; i < source->offices[source_office_index].packages_count; i++)
    {
        int src_pkg_weight = source->offices[source_office_index].packages[i].weight;
        
        if ((min_tgt_weight <= src_pkg_weight)&&(max_tgt_weight >= src_pkg_weight))
        {
            package* pkg = &source->offices[source_office_index].packages[i];
            
            add_package(target, target_office_index, pkg);
            rm_package(source, source_office_index, pkg->id);
            
            i = 0;
        }
    }
}

town town_with_most_packages(town* towns, int towns_count) {
    int packs = 0;
    town* tp_town = towns;
    for (int j = 0; j < towns_count; j++) 
    {
        for (int i = 0; i < towns[j].offices_count; i++)
        {
            if (towns[j].offices[i].packages_count > packs)
            {
                packs = towns[j].offices[i].packages_count;
                tp_town = &towns[j];
            }
        }
    }
    return *tp_town;
}

town* find_town(town* towns, int towns_count, char* name) {
    town* tp_town = &towns[0];
    for (int j = 0; j < towns_count; j++) 
    {
        if (*towns[j].name == *name)
        {
            tp_town = &towns[j];
        }
    }
    return tp_town;
}

int main()
{
	int towns_count;
	scanf("%d", &towns_count);
	town* towns = malloc(sizeof(town)*towns_count);
	for (int i = 0; i < towns_count; i++) {
		towns[i].name = malloc(sizeof(char) * MAX_STRING_LENGTH);
		scanf("%s", towns[i].name);
		scanf("%d", &towns[i].offices_count);
		towns[i].offices = malloc(sizeof(post_office)*towns[i].offices_count);
		for (int j = 0; j < towns[i].offices_count; j++) {
			scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
			towns[i].offices[j].packages = malloc(sizeof(package)*towns[i].offices[j].packages_count);
			for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
				towns[i].offices[j].packages[k].id = malloc(sizeof(char) * MAX_STRING_LENGTH);
				scanf("%s", towns[i].offices[j].packages[k].id);
				scanf("%d", &towns[i].offices[j].packages[k].weight);
			}
		}
	}
	int queries;
	scanf("%d", &queries);
	char town_name[MAX_STRING_LENGTH];
	while (queries--) {
		int type;
		scanf("%d", &type);
		switch (type) {
		case 1:
			scanf("%s", town_name);
			town* t = find_town(towns, towns_count, town_name);
			print_all_packages(*t);
			break;
		case 2:
			scanf("%s", town_name);
			town* source = find_town(towns, towns_count, town_name);
			int source_index;
			scanf("%d", &source_index);
			scanf("%s", town_name);
			town* target = find_town(towns, towns_count, town_name);
			int target_index;
			scanf("%d", &target_index);
			send_all_acceptable_packages(source, source_index, target, target_index);
			break;
		case 3:
			printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count).name);
			break;
		}
	}
	return 0;
}
