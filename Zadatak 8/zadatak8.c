void append_child(position head) {
	int loop = 1;
	int letter = 0;
	position tmp = (position)malloc(sizeof(struct directory));
	tmp->next_child = NULL;
	printf("Unesite ime za direktorij:  ");
	scanf(" %[^\n]", tmp->name);

	
	while (loop == 1) {
		if (head->next_child != NULL) {
			while (loop == 1) {
				if (toupper(head->next_child->name[letter]) == toupper(tmp->name[letter])) {
					letter++;
					loop = 1;
				}
				
				else if (toupper(head->next_child->name[letter]) > toupper(tmp->name[letter])) {
					letter = 0;
					loop = 1;
				}
				else if (toupper(head->next_child->name[letter]) < toupper(tmp->name[letter])) {
					head = head->next_child;
					letter = 0;
					loop = 1;
				}	
			}
		}
		else {
			loop = 0;
		}
	}
	 /*
	tmp->next_child = head->next_child;
	head->next_child = tmp;
	tmp->next_child->prev_child = tmp;
	tmp->prev_child = head;
	*/

	if (head->next_child != NULL) {
		tmp->next_child = head->next_child;
		tmp->next_child->prev_child = tmp;
		tmp->prev_child = head;
		head->next_child = tmp;
	}
	else {
		head->next_child = tmp;
		tmp->prev_child = head;
	}
	


	printf("ggg");

}
