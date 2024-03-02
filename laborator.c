#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROFILES 100

struct Pharmacy
{
    char Name[50];
    int Amount;
    float Price;
    int Id;
};

void ReadPharmacy(struct Pharmacy *medicine)
{
    printf("Insert Medicine Name : ");
    scanf("%s", medicine->Name);
    printf("Insert Id: ");
    scanf("%d", &medicine->Id);
    printf("Insert Amount: ");
    scanf("%d", &medicine->Amount);
    printf("Insert Price : ");
    scanf("%f", &medicine->Price);
    getchar(); // to clear the input buffer
}

void ShowMedicine(struct Pharmacy profil)
{
    printf("\nName: %s\n", profil.Name);
    printf("Amount: %d\n", profil.Amount);
    printf("Price : %.2f MDL\n", profil.Price);
}

int SearchMedicine(struct Pharmacy medicine[], int Id, char name[])
{
    for (int i = 0; i < Id; i++)
    {
        if (strcmp(medicine[i].Name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

void SortByName(struct Pharmacy *medicine, int Id)
{
    struct Pharmacy temp;
    for (int i = 0; i < Id - 1; i++)
    {
        for (int j = 0; j < Id - i - 1; j++)
        {
            if (strcmp(medicine[j].Name, medicine[j + 1].Name) > 0)
            {
                temp = medicine[j];
                medicine[j] = medicine[j + 1];
                medicine[j + 1] = temp;
            }
        }
    }
}

void AddProfileAtTheBeginning(struct Pharmacy *medicine, int *Id)
{
    if (*Id < MAX_PROFILES)
    {
        struct Pharmacy profil;
        printf("\nInsert new medicine : \n");
        ReadPharmacy(&profil);
        for (int i = *Id; i > 0; i--)
        {
            medicine[i] = medicine[i - 1];
        }
        medicine[0] = profil;
        (*Id)++;
    }
    else
    {
        printf("\nMax number of medicine.\n");
    }
}

void AddMedicineAtTheEnd(struct Pharmacy *medicine, int *Id)
{
    if (*Id < MAX_PROFILES)
    {
        printf("\nInsert info about new medicine:\n");
        ReadPharmacy(&medicine[*Id]);
        (*Id)++;
    }
    else
    {
        printf("\nThe maximum number of medicines has been reached.\n");
    }
}

void InsertMedicineInPosition(struct Pharmacy *medicine, int *Id, int position)
{
    if (*Id < MAX_PROFILES && position >= 0 && position <= *Id)
    {
        struct Pharmacy Medicine;
        printf("\nInsert information about new medicine:\n");
        ReadPharmacy(&Medicine);
        for (int i = *Id; i > position; i--)
        {
            medicine[i] = medicine[i - 1];
        }
        medicine[position] = Medicine;
        (*Id)++;
    }
    else
    {
        printf("\nInsert new medicine is unavailable.\n");
    }
}

void DeleteMedicine(struct Pharmacy *medicine, int *id, int position)
{
    if (position >= 0 && position < *id)
    {
        for (int i = position; i < *id - 1; i++)
        {
            medicine[i] = medicine[i + 1];
        }
        (*id)--;
        printf("\nMedicine from position %d has been deleted.\n", position + 1);
    }
    else
    {
        printf("\nDelete medicine is invalid. Check position.\n");
    }
}

void MemFree(struct Pharmacy *medicine)
{
    free(medicine);
}

int main()
{
    struct Pharmacy *medicine = (struct Pharmacy *)malloc(MAX_PROFILES * sizeof(struct Pharmacy));
    int numProfiles = 0;
    int choice;

    if (medicine == NULL)
    {
        printf("Memory allocation error.");
        return 1;
    }

    do
    {
        printf("\n1. Add a profile at the beginning of the list\n");
        printf("2. Add a profile at the end of the list\n");
        printf("3. Insert a medicine in a certain position\n");
        printf("4. Delete a medicine from a certain position\n");
        printf("5. Show all profiles\n");
        printf("6. Search medicine by name\n");
        printf("7. Sort medicine by name\n");
        printf("8. Release memory and exit from program\n");
        printf("Insert option: ");
        scanf("%d", &choice);


        switch (choice)
        {
            case 1:
                AddProfileAtTheBeginning(medicine, &numProfiles);
                break;
            case 2:
                AddMedicineAtTheEnd(medicine, &numProfiles);
                break;
            case 3:
                if (numProfiles > 0)
                {
                    int position;
                    printf("\nEnter the insertion position: ");
                    scanf("%d", &position);
                    InsertMedicineInPosition(medicine, &numProfiles, position);
                }
                else
                {
                    printf("\nError to insert in a position.\n");
                }
                break;
            case 4:
                if (numProfiles > 0)
                {
                    int position;
                    printf("\nEnter position to delete: ");
                    scanf("%d", &position);
                    DeleteMedicine(medicine, &numProfiles, position);
                }
                else
                {
                    printf("\nThis position doesn't exist.\n");
                }
                break;
            case 5:
                printf("\nExisting medicine:\n");
                for (int i = 0; i < numProfiles; i++)
                {
                    ShowMedicine(medicine[i]);
                }
                break;
            case 6:
                if (numProfiles > 0)
                {
                    char searchName[50];
                    printf("\nEnter name of the medicine you search: ");
                    scanf("%s", searchName);
                    int position = SearchMedicine(medicine, numProfiles, searchName);
                    if (position != -1)
                    {
                        printf("\nMedicine with the name %s was found in position %d.\n", searchName, position + 1);
                    }
                    else
                    {
                        printf("\nMedicine with the name %s was not found.\n", searchName);
                    }
                }
                else
                {
                    printf("\nThere are no medicines to search.\n");
                }
                break;
            case 7:
                SortByName(medicine, numProfiles);
                printf("\nMedicine was sorted by name.\n");
                break;
            case 8:
                MemFree(medicine);
                printf("\nMemory has been released.\n");
                break;
            default:
                printf("\nInvalid option.\n");
        }
    } while (choice != 8);

    return 0;
}
