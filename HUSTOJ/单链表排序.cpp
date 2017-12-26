void Sort(List &L,int m)
{
	Position p, q;
	int t;
	for (p = L->Next; p; p = p->Next)
	{
		for (q = p->Next; q; q = q->Next)
		{
			if (p->Number < q->Number)
			{
				t = q->k;
				q->k = p->k;
				p->k = t;
			}
		}
	}
}
