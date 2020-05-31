// void testMemDump(){

//     // Reserve 33 bytes and differ the last one
//     char *ptr = (char *) malloc(33);
// 	char *ptrDmp = (char *) malloc(33);
// 	ptrDmp[32] = ptr[32]+1;

//     // Do a dump of 32 bytes
// 	memDump(ptr, ptrDmp);
	
//     // Check that exactly 32 bytes are equal between addresses
// 	int i;
// 	for(i=0; ptr[i]==ptrDmp[i]; i++);
//     if(i!=32)
//         while(1);

// }


// void testGetTime(){

//     Time * time = malloc(sizeof(Time));
// 	getTime(time);

// 	printLine(itoa(time->hours));
// 	printLine(itoa(time->minutes));
// 	printLine(itoa(time->seconds));

// }


// void testCPUInfo(){

//     CPUInfo *info = malloc(sizeof(CPUInfo));
// 	info->brandName = malloc(50);
// 	info->brandDesc = malloc(70);
	
// 	cpuInfo(info);
// 	printLine(info->brandName);
// 	printLine(info->brandDesc);

// }


// void testRegDump(){
//     RegDump * dump = malloc(sizeof(RegDump));
// 	regDump(dump);
	
// 	printLine(itoa(dump->rax));
// 	printLine(itoa(dump->rbx));
// 	printLine(itoa(dump->rcx));
// }