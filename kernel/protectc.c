#include <win16.h>
#include <dpmi.h>
extern void _cdecl printf (const char *format,...);

void WINAPI Copyright()
{
	printf("\n\rosFree Windows Kernel version 0.1\n\r" 
		   "Copyright (C) 2022 osFree=n\r"
		   "Based on HX DPMI loader, WINE and TWIN\n\r"
		   "Copyright (C) 1993-2022 Japheth\n\r"
		   "Copyright (C) 1993-2022 the Wine project authors\n\r"
		   "Copyright (C) 1997 Willows Software, Inc.\n\r"
		   "\n\r");
}

void(far * switchentry)(void);
//#pragma aux switchentry        = 
		//parm [ax] [es] value [ax];

void WINAPI DumpDPMIInfo()
{
	init_info ii;
	unsigned int mem;
	printf("DPMI Installation check\n\r");
	switchentry=DPMI_Init(&ii);
	if (!switchentry)
	{
		printf("DPMI not found\n\r");
	} else {
		printf("DPMI found\n\r");
		printf("DPMI version:\t\t%d.%d\n\r", ii.major_version, ii.minor_version);
		printf("CPU type: \t\t%d (", ii.processor_type);
		if(ii.processor_type == 2) printf("80286");
        else if(ii.processor_type == 3) printf("80386");
        else if(ii.processor_type == 4) printf("80486");
        else if(ii.processor_type == 5) printf("Pentium");
        else if(ii.processor_type == 6) printf("Pentium Pro");
		printf(")\n\r32-bit client support:\t%s\n\r", (ii.flags && 1)?"Present":"Not present");
		printf("DPMI Host memory:\t%d bytes\n\r", ii.host_mem*16);
		printf("Switch to Protected mode entry: %x:%x\n\r", SELECTOROF(ii.switchentry), OFFSETOF(ii.switchentry));
		//switchentry=MAKELP(OFFSETOF(switchentry), SELECTOROF(switchentry));
		mem=ii.host_mem;
		__asm {
			mov	bx, 20h
			mov	ah,48h
			int	21h
			mov es,ax
			xor ax,ax
		}
		switchentry();
		//printf("KERNEL in Protected mode\n\r");
	} 
}
