#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

struct Element;

typedef struct Group{
	int groupNum;
	struct Group* previous;
	struct Group* next;
	struct Element* first;
	struct Element* last;
}Group;

typedef struct Period{
	int periodNum;
	struct Period* previous;
	struct Period* next;
	struct Element* first;
	struct Element* last;
}Period;

typedef struct Element{
	char* name;
	int atomicNum;
	struct Element* previous;
	struct Element* next;
	struct Element* previousGrpElement;
	struct Element* nextGrpElement;
	struct Element* previousPrdElement;
	struct Element* nextPrdElement;
	Period* period;
	Group* group;
}Element;

Group* groupHead = NULL;
Period* periodHead = NULL;
Element* elementHead = NULL;
//Element* verticalHead = NULL;
//Element* horizontalHead = NULL;

Group* groupLast = NULL;
Period* periodLast = NULL;
Element* elementLast = NULL;
//Element* verticalLast = NULL;
//Element* horizontalLast = NULL;

Element* atomicNumberOfElementExists(int);
Period* periodExists(int);
Group* groupExists(int);

void insertIntoTable(Element* newElement, int groupNumber, int periodNumber){
	Group* gptr = groupHead;
	Period* pptr = periodHead;

	if(gptr == NULL){
		Group* newGroup = (Group*)malloc(sizeof(Group));
		Period* newPeriod = (Period*)malloc(sizeof(Period));

		newGroup->groupNum = groupNumber;
		newGroup->first = newElement;
		groupHead = newGroup;
		groupLast = newGroup;
		newGroup->previous = NULL;
		newGroup->next = NULL;
		newGroup->last = newElement;

		newPeriod->periodNum = periodNumber;
		newPeriod->first = newElement;
		newPeriod->previous = NULL;
		newPeriod->next = NULL;
		periodHead = newPeriod;
		periodLast = newPeriod;
		newPeriod->last = newElement;

		newElement->period = newPeriod;
		newElement->group = newGroup;
		newElement->previousGrpElement = NULL;
		newElement->nextGrpElement = NULL;
		newElement->previous = NULL;
		newElement->next = NULL;
		newElement->nextPrdElement = NULL;
		newElement->previousPrdElement = NULL;
		elementHead = newElement;
		elementLast = newElement;

		/*verticalHead = first;
		horizontalHead = first;

		verticalLast = first;
		horizontalLast = first;*/
	}else{
		while(gptr != NULL){
			if(gptr->groupNum == groupNumber){

				gptr->last->nextGrpElement = newElement;
				newElement->previousGrpElement = gptr->last;
				newElement->nextGrpElement = NULL;
				gptr->last = newElement;

				newElement->group = gptr;
				break;
			}
			gptr = gptr->next;
		}

		if(gptr == NULL){
			Group* newGroup = (Group*)malloc(sizeof(Group));
			groupLast->next = newGroup;
			newGroup->previous = groupLast;
			newGroup->next = NULL;
			groupLast = newGroup;
			newGroup->groupNum = groupNumber;
			newGroup->first = newElement;
			newGroup->last = newElement;
			newElement->group = newGroup;
			newElement->previousGrpElement = NULL;
			newElement->nextGrpElement = NULL;

		}

		while(pptr != NULL){
			if(pptr->periodNum == periodNumber){

				pptr->last->nextPrdElement = newElement;
				newElement->previousPrdElement = pptr->last;
				newElement->nextPrdElement = NULL;
				pptr->last = newElement;

				newElement->period = pptr;
				break;
			}
			pptr = pptr->next;
		}

		if(pptr == NULL){
			Period* newPeriod = (Period*)malloc(sizeof(Period));
			periodLast->next = newPeriod;
			newPeriod->previous = periodLast;
			newPeriod->next = NULL;
			periodLast = newPeriod;
			newPeriod->periodNum = periodNumber;
			newPeriod->first = newElement;
			newPeriod->last = newElement;
			newElement->period = newPeriod;
			newElement->nextPrdElement = NULL;
			newElement->previousPrdElement = NULL;
		}

		elementLast->next = newElement;
		newElement->previous = elementLast;
		newElement->next = NULL;
		elementLast = newElement;

	}
}

int strCheck(char* ptr1, char* ptr2){
	int len1 = strlen(ptr1);
	int len2 = strlen(ptr2);

	int value1;
	int value2;

	if(len1 != len2){
		if(len1 < len2){
			len1 = len2;
		}
		for(int i = 0; i < len1; ++i){
			value1 = (int)(*(ptr1 + i));
			value2 = (int)(*(ptr2 + i));
			if(value1 == value2){
				continue;
			}
			return value1 - value2;
		}
	}else{
		for(int i = 0; i < len1; ++i){
			value1 = (int)(*(ptr1 + i));
			value2 = (int)(*(ptr2 + i));

			if(value1 == value2){
				continue;
			}else if((value1 >= 65) && (value1 <= 90) && (value2 >= 97) && (value2 <= 122)){
				if((value1 - value2) == -32){
					continue;
				}
			}else if((value2 >= 65) && (value2 <= 90) && (value1 >= 97) && (value1 <= 122)){
				if((value1 - value2) == 32){
					continue;
				}
			}
			return value1 - value2;
		}
		return 0;
	}

}

void printAsTheyWereEntered(){
	Element* tmp = elementHead;
	if(tmp == NULL){
		printf("No Elements are entered\n");
	}else{
		printf("\n");
		while(tmp != NULL){
			printf("Element: %s\n", tmp->name);
			printf("Atomic Number: %d\n", tmp->atomicNum);
			printf("Period: %d\n", tmp->period->periodNum);
			printf("Group: %d\n", tmp->group->groupNum);
			printf("..........\n");
			tmp = tmp->next;
		}
	}
	return;
}

void printPeriodWise(){
	Period* pptr = periodHead;
	if(pptr == NULL){
		printf("No Elements are entered");
	}else{
		printf("\nElementName(AtomicNumber)\n");
		while(pptr != NULL){
			printf("\nPeriod  %d :   ", pptr->periodNum);
			Element *current = pptr->first;
			while(current != NULL){
				printf("%s(%d)", current->name, current->atomicNum);
				if(current->nextPrdElement != NULL){
					printf(", ");
				}
				current = current->nextPrdElement;
			}
			pptr = pptr->next;
		}
	}
	return;
}

void printGroupWise(){
	Group* gptr = groupHead;
	if(gptr == NULL){
		printf("No Elements are entered");
	}else{
		printf("\nElementName(AtomicNumber)\n");
		while(gptr != NULL){
			printf("\nGroup  %d :   ", gptr->groupNum);
			Element *current = gptr->first;
			while(current != NULL){
				printf("%s(%d)",current->name, current->atomicNum);
				if(current->nextGrpElement != NULL){
					printf(", ");
				}
				current = current->nextGrpElement;
			}
			gptr = gptr->next;
		}
	}
	return;
}

void doTheChangesInThePeriodicWeb(Element* searchElement) {

	//takes care of element's previousPrdElement and nextPrdElement
	//for period
	if(1){
		//only one element in a period
		if((searchElement->previousPrdElement == NULL) && (searchElement->nextPrdElement == NULL)){
			//only one period in whole period link list
			if((searchElement->period->previous == NULL) && (searchElement->period->next == NULL)){
				free(searchElement->period);
				periodHead = NULL;
				periodLast = NULL;
			}
			//many periods and the period to be removed is the periodHead
			else if((searchElement->period->previous == NULL) && (searchElement->period->next != NULL)){
				periodHead = searchElement->period->next;
				searchElement->period->next->previous = NULL;
				free(searchElement->period);
			}
			//many periods and the period to be removed is the periodLast
			else if((searchElement->period->previous != NULL) && (searchElement->period->next == NULL)){
				periodLast = searchElement->period->previous;
				searchElement->period->previous->next = NULL;
				free(searchElement->period);
			}
			//many periods and the period to be removed is in between the period Linklist
			else if((searchElement->period->previous != NULL) && (searchElement->period->next != NULL)){
				searchElement->period->previous->next = searchElement->period->next;
				searchElement->period->next->previous = searchElement->period->previous;
				free(searchElement->period);
			}
		}

		//many elements in a period and the element found is first element in that period
		else if(searchElement->period->first == searchElement) {
			searchElement->period->first = searchElement->nextPrdElement;
			searchElement->nextPrdElement->previousPrdElement = NULL;
		}
		//many elements in a period and the element found is last element in that period
		else if(searchElement->period->last == searchElement){
			searchElement->period->last = searchElement->previousPrdElement;
			searchElement->previousPrdElement->nextPrdElement = NULL;
		}
		//many elements in a period and the element found is in between the elements of the same period
		else if((searchElement->period->first != searchElement) && (searchElement->period->last != searchElement)){
			searchElement->previousPrdElement->nextPrdElement = searchElement->nextPrdElement;
			searchElement->nextPrdElement->previousPrdElement = searchElement->previousPrdElement;
		}
	}

	//takes care of element's previousGrpElement and nextGrpElement
	//for group
	if(1){
		//only one element in a group
		if((searchElement->previousGrpElement == NULL) && (searchElement->nextGrpElement == NULL)){
			//only one group in whole group link list
			if((searchElement->group->previous == NULL) && (searchElement->group->next == NULL)){
				free(searchElement->group);
				groupHead = NULL;
				groupLast = NULL;
			}
			//many groups and the group to be removed is the groupHead
			else if((searchElement->group->previous == NULL) && (searchElement->group->next != NULL)){
				groupHead = searchElement->group->next;
				searchElement->group->next->previous = NULL;
				free(searchElement->group);
			}
			//many groups and the group to be removed is the groupLast
			else if((searchElement->group->previous != NULL) && (searchElement->group->next == NULL)){
				groupLast = searchElement->group->previous;
				searchElement->group->previous->next = NULL;
				free(searchElement->group);
			}
			//many groups and the group to be removed is in between the group Linklist
			else if((searchElement->group->previous != NULL) && (searchElement->group->next != NULL)){
				searchElement->group->previous->next = searchElement->group->next;
				searchElement->group->next->previous = searchElement->group->previous;
				free(searchElement->group);
			}
		}

		//many elements in a group and the element found is first element in that group
		else if(searchElement->group->first == searchElement) {
			searchElement->group->first = searchElement->nextGrpElement;
			searchElement->nextGrpElement->previousGrpElement = NULL;
		}
		//many elements in a group and the element found is last element in that group
		else if(searchElement->group->last == searchElement){
			searchElement->group->last = searchElement->previousGrpElement;
			searchElement->previousGrpElement->nextGrpElement = NULL;
		}
		//many elements in a group and the element found is in between the elements of the same group
		else if((searchElement->group->first != searchElement) && (searchElement->group->last != searchElement)){
			searchElement->previousGrpElement->nextGrpElement = searchElement->nextGrpElement;
			searchElement->nextGrpElement->previousGrpElement = searchElement->previousGrpElement;
		}
	}

	//takes care of element's next and previous
	//there is only one element in whole periodic table
	if((searchElement == elementHead) && (searchElement == elementLast)){
		elementHead = NULL;
		elementLast = NULL;
	}
	//there are many elements and the element to be removed is elementHead
	else if((searchElement == elementHead) && (searchElement != elementLast)){
		elementHead = searchElement->next;
		searchElement->next->previous = NULL;
	}
	//there are many elements and the element to be removed is elementLast
	else if((searchElement != elementHead) && (searchElement == elementLast)){
		elementLast = searchElement->previous;
		searchElement->previous->next = NULL;
	}
	//there are many elements and the element to be removed is neither elementHead nor elementLast
	else if((searchElement != elementHead) && (searchElement != elementLast)){
		searchElement->next->previous = searchElement->previous;
		searchElement->previous->next = searchElement->next;
	}
}

void updateOrDeleteTheElement(int atomic, char toDo){//toDo is 'u' for update, 'd' for delete
	Element* searchElement = atomicNumberOfElementExists(atomic);
	if(searchElement == NULL){
		printf("\nElement of atomic number %d does not exists",atomic);
	}else{
		int groupNumberOld = searchElement->group->groupNum;
		int periodNumberOld = searchElement->period->periodNum;

		if(toDo == 'u') {
			Element* updatedElement = (Element*)malloc(sizeof(Element));
			int groupNumberNew;
			int periodNumberNew;
			char newName[100];
			printf("\nEnter the new name of the element: ");
			scanf("%s",newName);
			updatedElement->name = (char*)malloc((strlen(newName) + 1) * sizeof(char));
			strcpy(updatedElement->name, newName);
			printf("Atomic Number of %s: ", newName);
			scanf("%d",&(updatedElement->atomicNum));
			printf("%s lies in which group: ", newName);
			scanf("%d",&groupNumberNew);
			printf("%s lies in which period: ", newName);
			scanf("%d",&periodNumberNew);

			if((groupNumberNew == groupNumberOld) && (periodNumberNew == periodNumberOld)){
				//Here the search element is itself the updated element
				free(updatedElement);
				return;
			}
			doTheChangesInThePeriodicWeb(searchElement);
			insertIntoTable(updatedElement, groupNumberNew, periodNumberNew);
			printf("Element %s(A: %d)(G: %d)(P: %d) is successfully updated to %s(A: %d)(G: %d)(P: %d)!", searchElement->name, searchElement->atomicNum,
							groupNumberOld, periodNumberOld, updatedElement->name, updatedElement->atomicNum, groupNumberNew, periodNumberNew);
		} else if (toDo == 'd') {
			doTheChangesInThePeriodicWeb(searchElement);
			printf("Element %s(A: %d)(G: %d)(P: %d) is successfully deleted!", searchElement->name, searchElement->atomicNum, groupNumberOld,
							periodNumberOld);
		}

		free(searchElement->name);
		free(searchElement);
	}
	return;
}

Element* nameOfElementExists(char* nameCheck){
	Element* searchElement = elementHead;
	if(searchElement == NULL){
		return NULL;
	}
	while(searchElement != NULL){
		if(strCheck(searchElement->name, nameCheck) == 0){
			return searchElement;
		}
		searchElement = searchElement->next;
	}
	return NULL;
}

void searchElementByName(char* currentName){
	Element* searchElement = nameOfElementExists(currentName);
	if(searchElement == NULL){
		printf("Element of name %s does not exist\n", currentName);
	}else{
		printf("\nElement: %s\n", searchElement->name);
		printf("Atomic Number: %d\n", searchElement->atomicNum);
		printf("Period: %d\n", searchElement->period->periodNum);
		printf("Group: %d\n", searchElement->group->groupNum);
	}
	return;
}

Element* atomicNumberOfElementExists(int atomic){
	Element* searchElement = elementHead;
	if(searchElement == NULL){
		return NULL;
	}
	while(searchElement != NULL){
		if(searchElement->atomicNum == atomic){
			return searchElement;
		}
		searchElement = searchElement->next;
	}
	return NULL;
}

int doesElementExistsFromNameAndAtomicNumberAndPeriodAndGroup(char* name, int atomicNumber, int periodNumber, int groupNumber) {
	Element* searchElement = elementHead;
	if(searchElement == NULL) {
		return 0;
	}
	while(searchElement != NULL) {
		if(strCheck(searchElement->name, name) == 0) {
			printf("Element of name %s already exists!\n", searchElement->name);
			return 1;
		}
		if(searchElement->atomicNum == atomicNumber) {
			printf("Element %s(A: %d) already exists!\n", searchElement->name, searchElement->atomicNum);
			return 1;
		}
		if((searchElement->group->groupNum == groupNumber) && (searchElement->period->periodNum == periodNumber)) {
			printf("Element %s(G: %d)(P: %d) already exists!\n", searchElement->name, groupNumber, periodNumber);
			return 1;
		}
		searchElement = searchElement->next;
	}
	return 0;
}

void searchElementByAtomicNumber(int atomic){
	Element* searchElement = atomicNumberOfElementExists(atomic);
	if(searchElement == NULL){
		printf("Element of atomic number %d does not exists\n", atomic);
	}else{
		printf("\nElement: %s\n", searchElement->name);
		printf("Atomic Number: %d\n", searchElement->atomicNum);
		printf("Period: %d\n", searchElement->period->periodNum);
		printf("Group: %d\n", searchElement->group->groupNum);
	}
	return;
}

Period* periodExists(int periodNumber){
	Period* pptr = periodHead;
	if(pptr == NULL){
		return NULL;
	}
	while(pptr != NULL){
		if(pptr->periodNum == periodNumber){
			return pptr;
		}
		pptr = pptr->next;
	}
	return NULL;
}

void getPeriodElements(int periodNumber){
	Period* pptr = periodExists(periodNumber);
	if(pptr == NULL){
		printf("Elements of %d period does not exist\n", periodNumber);
		return;
	}
	Element *current = pptr->first;
	printf("Period: %d\n\n", pptr->periodNum);
	while(current != NULL){
		printf("Element: %s\n", current->name);
		printf("Atomic Number: %d\n", current->atomicNum);
		printf("..........\n");
		current = current->nextPrdElement;
	}
}

Group* groupExists(int groupNumber){
	Group* gptr = groupHead;
	if(gptr == NULL){
		return NULL;
	}
	while(gptr != NULL){
		if(gptr->groupNum == groupNumber){
			return gptr;
		}
		gptr = gptr->next;
	}
	return NULL;
}

void getGroupElements(int groupNumber){
	Group* gptr = groupExists(groupNumber);
	if(gptr == NULL){
		printf("Elements of %d group does not exists\n",groupNumber);
		return;
	}
	Element *current = gptr->first;
	printf("Group: %d\n\n",gptr->groupNum);
	while(current != NULL){
		printf("Element: %s\n",current->name);
		printf("Atomic Number: %d\n",current->atomicNum);
		printf("..........\n");
		current = current->nextGrpElement;
	}
}

void main(){
	int choice;
	system("cls");
	do{
		printf("\n\nPeriodic Table\n\n");
		printf("0.Exit\n");
		printf("1.Enter an element\n");
		printf("2.Read from file(.txt)\n");
		printf("3.Save to file(.txt)\n");
		printf("4.Print the Elements\n");
		printf("5.Update the details of an element(search by atomic number)\n");
		printf("6.Delete an element\n");
		printf("7.Search an element\n");
		printf("8.Get elements of a particular period\n");
		printf("9.Get elements of a particular group\n\n");
		printf("Enter your choice: ");
		scanf("%d",&choice);
		switch(choice){
			case 0: {
				system("cls");
				break;
			}

			case 1: {
				Element* e = (Element*)malloc(sizeof(Element));
				int period, group;
				char ary[100];
				printf("Enter the name of the element: ");
				scanf("%s",ary);
				e->name = (char*)malloc((strlen(ary) + 1) * sizeof(char));
				strcpy(e->name,ary);
				printf("Atomic Number of %s: ", ary);
				scanf("%d",&(e->atomicNum));
				printf("%s lies in which group: ", ary);
				scanf("%d",&group);
				printf("%s lies in which period: ", ary);
				scanf("%d",&period);
				if(doesElementExistsFromNameAndAtomicNumberAndPeriodAndGroup(e->name, e->atomicNum, period, group)) {
					printf("Element %s not added due to above contradictory result found!", e->name);
					free(e->name);
					free(e);
				} else {
					insertIntoTable(e,group,period);
				}
				printf("\n\n...Press any key to continue...");
				getch();
				system("cls");
				break;
			}

			case 2: {
				//file should be in this manner: AtomicNumber	ElementName	GroupNumber	PeriodNumber
				int fscanfCount = 0;
				char fileName[100];
				printf("Enter the file name from which elements are to be stored in periodic table: ");
				scanf("%s", fileName);
				FILE* fp = fopen(fileName, "r");
				while(1) {
					Element* e = (Element*)malloc(sizeof(Element));
					char name[100];
					int period;
					int group;
					fscanfCount = fscanf(fp, "%d %s %d %d", &(e->atomicNum), name, &group, &period);
					if(fscanfCount != -1) {
						e->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
						strcpy(e->name, name);
						if(doesElementExistsFromNameAndAtomicNumberAndPeriodAndGroup(e->name, e->atomicNum, period, group)) {
							printf("Element %s(A: %d)(G: %d)(P: %d) is not added due to the above contradictory result found!\n\n", e->name, e->atomicNum,
											group, period);
							free(e->name);
							free(e);
						} else {
							insertIntoTable(e, group, period);
						}
					} else {
						//if fscanfCount == -1, it means end of file EOF
						free(e);
						break;
					}
				}
				fclose(fp);
				printf("File read successfully!\nAll elements stored!");
				printf("\n\n...Press any key to continue...");
				getch();
				system("cls");
				break;
			}

			case 3: {
				//Printed in this manner: AtomicNumber	ElementName	GroupNumber	PeriodNumber
				char fileName[100];
				printf("Enter the file name in which the elements are to be printed: ");
				scanf("%s", fileName);
				FILE* fp = fopen(fileName, "w");
				Element* tmp = elementHead;
				while(tmp != NULL) {
					fprintf(fp,"%d\t%s\t%d\t%d\n", tmp->atomicNum, tmp->name, tmp->group->groupNum, tmp->period->periodNum);
					tmp = tmp->next;
				}
				fclose(fp);
				printf("Successfully printed the elements in the file");
				printf("\n\n...Press any key to continue...");
				getch();
				system("cls");
				break;
			}

			case 4: {
				system("cls");
				int printChoice;
				printf("1.Print the Elements in the same order as they were Entered\n");
				printf("2.Print the Elements Period-Wise\n");
				printf("3.Print the Elements Group-Wise\n\n");
				printf("Enter your choice: ");
				scanf("%d",&printChoice);
				switch(printChoice){
					case 1: {
						printAsTheyWereEntered();
						printf("\n\n...Press any key to continue...");
						getch();
						system("cls");
						break;
					}

					case 2: {
						printPeriodWise();
						printf("\n\n...Press any key to continue...");
						getch();
						system("cls");
						break;
					}

					case 3: {
						printGroupWise();
						printf("\n\n...Press any key to continue...");
						getch();
						system("cls");
						break;
					}
					default: {
						printf("...Incorrect choice...");
						printf("\n\n...Press any key to exit...");
						getch();
						system("cls");
						break;
					}
				}
				break;
			}

			case 5: {
				int atomicNumberOld;
				printf("Enter the Atomic Number of the Element which you want to update: ");
				scanf("%d",&atomicNumberOld);
				updateOrDeleteTheElement(atomicNumberOld, 'u');
				printf("\n\n...Press any key to continue...");
				getch();
				system("cls");
				break;
			}

			case 6: {
				int atomicNumber;
				printf("Enter the Atomic Number of the Element which you want to delete: ");
				scanf("%d", &atomicNumber);
				updateOrDeleteTheElement(atomicNumber, 'd');
				printf("\n\n...Press any key to continue...");
				getch();
				system("cls");
				break;
			}

			case 7: {
				system("cls");
				int searchChoice;
				printf("1.Search by name\n");
				printf("2.Search by atomic number\n\n");
				printf("Enter your choice: ");
				scanf("%d",&searchChoice);
				switch(searchChoice){
					case 1: {
						char currentName[100];
						printf("Enter the name of the element: ");
						scanf("%s",currentName);
						searchElementByName(currentName);
						printf("\n\n...Press any key to continue...");
						getch();
						system("cls");
						break;
					}

					case 2: {
						int atomicNumber;
						printf("Enter the atomic number of the element: ");
						scanf("%d",&atomicNumber);
						searchElementByAtomicNumber(atomicNumber);
						printf("\n\n...Press any key to continue...");
						getch();
						system("cls");
						break;
					}

					default: {
						printf("...Incorrect choice...");
						printf("\n\n...Press any key to exit...");
						getch();
						system("cls");
						break;
					}
				}
				break;
			}

			case 8: {
				int period;
				printf("Enter the period number: ");
				scanf("%d",&period);
				getPeriodElements(period);
				printf("\n\n...Press any key to continue...");
				getch();
				system("cls");
				break;
			}

			case 9: {
				int group;
				printf("Enter the group number: ");
				scanf("%d",&group);
				getGroupElements(group);
				printf("\n\n...Press any key to continue...");
				getch();
				system("cls");
				break;
			}

			default: {
				printf("...Incorrect choice...");
				printf("\n\n...Press any key to exit...");
				getch();
				system("cls");
				break;
			}
		}

	}while(choice != 0);
}
