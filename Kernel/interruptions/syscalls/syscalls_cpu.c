#include <cpu_info.h>
#include <lib.h>

typedef struct CPUInfo{
    char *brandName, *brandDesc;
} CPUInfo;


char brandDescs[22][70] = {
    "This processor does not support the brand identification feature",
    "Intel(R) Celeron(R) processor",
    "Intel(R) Pentium(R) III processor",
    "Intel(R) Pentium(R) III Xeon(R) processor",
    "Intel(R) Pentium(R) III processor",
    "Mobile Intel(R) Pentium(R) III processor-M",
    "Mobile Intel(R) Celeron(R) processor",
    "Intel(R) Pentium(R) 4 processor",
    "Intel(R) Pentium(R) 4 processor",
    "Intel(R) Celeron(R) processor",
    "Intel(R) Xeon(R) processor",
    "Intel(R) Xeon(R) processor MP",
    "Mobile Intel(R) Pentium(R) 4 processor-M",
    "Mobile Intel(R) Celeron(R) processor",
    "Mobile Genuine Intel(R) processor",
    "Intel(R) Celeron(R) M processor",
    "Mobile Intel(R) Celeron(R) processor",
    "Intel(R) Celeron(R) processor",
    "Mobile Genuine Intel(R) processor",
    "Intel(R) Pentium(R) M processor",
    "Mobile Intel(R) Celeron(R) processor"
};


void sysCpuInfo(CPUInfo * info){

    getBrandName(info->brandName);
    
    memcpy(info->brandDesc, brandDescs[getBrandIndex()], 70);

}