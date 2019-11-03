NAME : VINAYAKA M HEGDE
USN  : PES1201701600
SEC  : B


	                  				    INPUT :

1. The input for my program is the size of the cache.

	

								IMPLEMENTATION :

1. My program consists of 3 structures : NODE, RECORD AND HT.

		a. NODE structure consists of 'data' of type int and 'prev','next' pointers of type NODE.
		b. RECORD structure consists of a pointer 'pnode' which is a pointer to NODE.
		c. HT structure consists of array of RECORDS. Therefore, Hash Table consists of array of pointers to NODE.

2. The cache is a Queue which is implemented by Doubly Linked List. 

3. The FRONT end of the queue contains most recently used elements and the REAR end conatins least recently used elements. 



								CACHE HIT/MISS :

1. If it's a cache hit, I'm deleting the current-element and inserting at front end of queue.

2. If it's a cache miss, if the cache is not full, then I'm inserting at front end else if the cache is full, I'm deleting from the rear and inserting the current-element at the front end.  

								   OUTPUT :	

Output consists of:
	a. Current Element
	b. CACHE HIT/MISS
	c. The contents of the Cache
	d. The HASH-TABLE	
	e. HIT rate and MISS rate
	f. Timing of the whole sequence.













