void neighbourkiller(LinkedList *ll)
{
	/* add your code here */
  ListNode *temp, *temp1, *temp2;
  int sum;
  for (int i = 1; i < ll->size; i++)
  {
    temp = findNode(ll, i);
    temp1 = findNode(ll,i-1);
    temp2 = findNode(ll,i+1);
    sum = temp1->item + temp2->item;

    if (sum == temp->item) removeNode(ll, i);

  }
}

ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}
